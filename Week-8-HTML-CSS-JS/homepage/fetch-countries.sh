#!/bin/bash

# fetch_countries.sh
# Fetches SVG path data for given country codes from the Mapsicon GitHub repo,
# cleans it (collapses newlines -> single space, converts double quotes ->
# single quotes), automatically splits long results into smaller chunks
# (to avoid VS Code's long-line issues), and writes everything into a JSON
# file ready to merge into your countries-paths.json.
#
# USAGE:
#   ./fetch_countries.sh us mx ca bs
#
# OUTPUT:
#   Writes fetched_countries.json in the current directory, formatted like:
#   {
#       "us": ["<path .../>"],
#       "ca": ["<path .../> ...", "...more chunks..."]
#   }

CHUNK_SIZE=4000   # max characters per array chunk -- adjust if needed

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <country_code1> <country_code2> ..."
    echo "Example: $0 us mx ca bs"
    exit 1
fi

OUTPUT_FILE="data/fetched-countries.json"
echo "{" > "$OUTPUT_FILE"

first_country=true

for code in "$@"; do
    lower_code=$(echo "$code" | tr '[:upper:]' '[:lower:]')

    echo "Fetching $lower_code..."

    url="https://raw.githubusercontent.com/djaiss/mapsicon/master/all/${lower_code}/vector.svg"

    raw_svg=$(curl -s "$url")

    if [[ "$raw_svg" != *"<svg"* ]]; then
        echo "  WARNING: Could not fetch valid SVG for '$lower_code'. Skipping."
        echo "  (Response was: ${raw_svg:0:80})"
        continue
    fi

    # Save raw svg temporarily so grep -P (Perl regex, multi-line) can process it as a file
    tmp_svg="/tmp/${lower_code}_raw.svg"
    echo "$raw_svg" > "$tmp_svg"

    # Extract all <path .../> elements, even ones spanning multiple lines.
    # Using perl here instead of grep -P, since macOS's built-in grep (BSD grep)
    # does not support -P (Perl regex mode), but perl itself ships by default
    # on macOS and Linux, so this works cross-platform.
    paths_only=$(perl -0777 -ne 'print "$1\n" while /(<path[^>]*\/>)/gs' "$tmp_svg")

    if [ -z "$paths_only" ]; then
        echo "  WARNING: No <path> elements found for '$lower_code'. Skipping."
        rm -f "$tmp_svg"
        continue
    fi

    # Collapse all newlines and extra whitespace into single spaces,
    # then convert double quotes to single quotes
    cleaned=$(echo "$paths_only" | tr '\n' ' ' | sed 's/  */ /g' | sed "s/\"/'/g")
    cleaned=$(echo "$cleaned" | sed 's/^ *//;s/ *$//')

    rm -f "$tmp_svg"

    total_length=${#cleaned}
    echo "  Fetched and cleaned. Total length: $total_length characters."

    # Split into chunks if needed, breaking only at a space (never mid-path)
    # so each chunk is still valid, joinable text.
    chunks=()
    remaining="$cleaned"

    while [ ${#remaining} -gt "$CHUNK_SIZE" ]; do
        # Take a slice up to CHUNK_SIZE, then trim back to the last space
        # so we don't cut a path's coordinate data in half.
        slice="${remaining:0:$CHUNK_SIZE}"
        last_space=$(echo "$slice" | grep -bo ' ' | tail -1 | cut -d: -f1)

        if [ -z "$last_space" ]; then
            # no space found, just take the full chunk size (rare edge case)
            last_space=$CHUNK_SIZE
        fi

        chunk="${remaining:0:$last_space}"
        chunks+=("$chunk")
        remaining="${remaining:$((last_space + 1))}"
    done
    chunks+=("$remaining")

    echo "  Split into ${#chunks[@]} chunk(s)."

    # Write this country's entry to the output file
    if [ "$first_country" = true ]; then
        first_country=false
    else
        echo "," >> "$OUTPUT_FILE"
    fi

    printf '    "%s": [\n' "$lower_code" >> "$OUTPUT_FILE"

    for i in "${!chunks[@]}"; do
        printf '        "%s"' "${chunks[$i]}" >> "$OUTPUT_FILE"
        if [ "$i" -lt $((${#chunks[@]} - 1)) ]; then
            echo "," >> "$OUTPUT_FILE"
        else
            echo "" >> "$OUTPUT_FILE"
        fi
    done

    printf '    ]' >> "$OUTPUT_FILE"
done

echo "" >> "$OUTPUT_FILE"
echo "}" >> "$OUTPUT_FILE"

echo ""
echo "All done. Output written to: $OUTPUT_FILE"
echo "Open it, review the formatting, then merge the entries into your real countries-paths.json"
echo "Remember: in your JavaScript, join chunks with ' ', a space."