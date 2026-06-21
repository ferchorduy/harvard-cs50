#!/bin/bash

# fetch_countries.sh
#
# Fetches SVG path data for given country codes from the Mapsicon GitHub repo,
# cleans it, splits it into chunks (joinable with ' ' in your JS), and merges
# the result into your EXISTING countries-paths.json file -- without
# overwriting countries you've already added.
#
# USAGE:
#   ./fetch_countries.sh us mx ca bs
#
# By default this looks for / creates: data/countries-paths.json
# (relative to wherever you run the script from)
#
# BEHAVIOR:
#   - If the target JSON file doesn't exist yet, it creates it.
#   - If a country code is already in the file, it skips it and tells you.
#   - If a country code is new, it fetches, cleans, chunks, and adds it.
#   - Every other entry already in the file is left completely untouched.

CHUNK_SIZE=4000
TARGET_FILE="data/fetched-countries-paths.json"

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <country_code1> <country_code2> ..."
    echo "Example: $0 us mx ca bs"
    exit 1
fi

# Make sure the data/ directory exists
mkdir -p "$(dirname "$TARGET_FILE")"

# If the target file doesn't exist yet, start it as an empty JSON object
if [ ! -f "$TARGET_FILE" ]; then
    echo "{}" > "$TARGET_FILE"
    echo "Created new file: $TARGET_FILE"
fi

for code in "$@"; do
    lower_code=$(echo "$code" | tr '[:upper:]' '[:lower:]')

    # Check if this code already exists in the file using Python
    # (much more reliable than trying to grep/parse JSON with bash)
    already_exists=$(python3 -c "
import json
with open('$TARGET_FILE') as f:
    data = json.load(f)
print('yes' if '$lower_code' in data else 'no')
")

    if [ "$already_exists" = "yes" ]; then
        echo "$lower_code already exists in $TARGET_FILE -- skipping."
        continue
    fi

    echo "Fetching $lower_code..."

    url="https://raw.githubusercontent.com/djaiss/mapsicon/master/all/${lower_code}/vector.svg"
    raw_svg=$(curl -s "$url")

    if [[ "$raw_svg" != *"<svg"* ]]; then
        echo "  WARNING: Could not fetch valid SVG for '$lower_code'. Skipping."
        echo "  (Response was: ${raw_svg:0:80})"
        continue
    fi

    tmp_svg="/tmp/${lower_code}_raw.svg"
    echo "$raw_svg" > "$tmp_svg"

    # Extract all <path .../> elements, even multi-line ones.
    # Using perl (not grep -P) for cross-platform support -- works on both
    # macOS (BSD grep, no -P support) and Linux.
    paths_only=$(perl -0777 -ne 'print "$1\n" while /(<path[^>]*\/>)/gs' "$tmp_svg")

    if [ -z "$paths_only" ]; then
        echo "  WARNING: No <path> elements found for '$lower_code'. Skipping."
        rm -f "$tmp_svg"
        continue
    fi

    cleaned=$(echo "$paths_only" | tr '\n' ' ' | sed 's/  */ /g' | sed "s/\"/'/g")
    cleaned=$(echo "$cleaned" | sed 's/^ *//;s/ *$//')

    rm -f "$tmp_svg"

    total_length=${#cleaned}
    echo "  Fetched and cleaned. Total length: $total_length characters."

    # Split into chunks at space boundaries. Each chunk (except possibly the
    # last) keeps its trailing space, so joining with ' ' in JS reconstructs
    # the original spacing correctly without doubling or losing any spaces.
    chunks=()
    remaining="$cleaned"

    while [ ${#remaining} -gt "$CHUNK_SIZE" ]; do
        slice="${remaining:0:$CHUNK_SIZE}"
        last_space=$(echo "$slice" | grep -bo ' ' | tail -1 | cut -d: -f1)

        if [ -z "$last_space" ]; then
            last_space=$CHUNK_SIZE
        fi

        chunk="${remaining:0:$last_space}"
        chunks+=("$chunk")
        remaining="${remaining:$((last_space + 1))}"
    done
    chunks+=("$remaining")

    echo "  Split into ${#chunks[@]} chunk(s)."

    # Build a JSON array of these chunks, then hand off to Python to merge
    # it into the existing file safely (proper JSON parsing, not text hacks).
    chunks_json="["
    for i in "${!chunks[@]}"; do
        # Escape backslashes and double quotes for safe JSON embedding,
        # then convert single quotes is not needed since we already use them
        escaped_chunk=$(printf '%s' "${chunks[$i]}" | python3 -c "import sys, json; print(json.dumps(sys.stdin.read()))")
        chunks_json+="$escaped_chunk"
        if [ "$i" -lt $((${#chunks[@]} - 1)) ]; then
            chunks_json+=","
        fi
    done
    chunks_json+="]"

    python3 -c "
import json

with open('$TARGET_FILE') as f:
    data = json.load(f)

data['$lower_code'] = json.loads('''$chunks_json''')

with open('$TARGET_FILE', 'w') as f:
    json.dump(data, f, indent=4)
    f.write('\n')

print('  Added \"$lower_code\" to $TARGET_FILE')
"
done

echo ""
echo "Done. Current contents of $TARGET_FILE:"
python3 -c "
import json
with open('$TARGET_FILE') as f:
    data = json.load(f)
print('Countries in file:', list(data.keys()))
"