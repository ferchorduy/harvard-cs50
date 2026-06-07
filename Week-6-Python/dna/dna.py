import csv
import sys


def main():

    if len(sys.argv) != 3:
        print("Usage: dna.py [CSV file] [TXT file]")
        sys.exit(1)

    people = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for person in reader:
            people.append(person)
    
    dna = ""
    with open(sys.argv[2]) as file:
        reader = csv.reader(file)
        for line in reader:
            dna = line[0]

    subsequences = []
    for key in people[0]:
        if key == 'name': continue
        else: subsequences.append(key)

    match = 0
    repetitions = []
    for subsequence in subsequences:
        match = longest_match(dna, subsequence)
        repetitions.append(str(match))

    for person in people:
        for subsequence in subsequences:
            if person[subsequence] != repetitions[subsequences.index(subsequence)]: break
        else:
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
