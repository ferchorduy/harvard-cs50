import csv
import sys


def main():

    if len(sys.argv) != 3:
        print("Usage: dna.py [CSV file] [TXT file]")
        sys.exit(1)

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        people = list(reader)
        subsequences = reader.fieldnames[1:]
    
    with open(sys.argv[2]) as file:
        dna = file.read().strip()

    repetitions = {}
    for subsequence in subsequences:
        repetitions[subsequence] = str(longest_match(dna, subsequence))

    for person in people:
        if all(person[subsequence] == repetitions[subsequence] for subsequence in subsequences):
            print(person['name'])
            sys.exit()
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
