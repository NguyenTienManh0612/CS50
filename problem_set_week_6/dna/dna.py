import csv
import sys

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py [databases] [sequences]")
        sys.exit(1)

    # TODO: Read database file into a variable
    databases = []
    with open(sys.argv[1]) as fileDatabase:
        reader = csv.DictReader(fileDatabase)
        for data in reader:
            databases.append(data)
    # Note: value in each line of databases is string, not int
    # TODO: Read DNA sequence file into a variable
    fileSequence = open(sys.argv[2], 'r')
    sequence = fileSequence.read()

    # TODO: Find longest match of each STR in DNA sequence
    STRsList = databases[0] #dictionary, get type of STR
    longest_match_STRs_list = []
    longest_STRs_dict = dict()
    for STR in STRsList:
        longestSequence = longest_match(sequence, STR)
        # store the length of longest match STR
        longest_STRs_dict.update({STR : longestSequence})
    longest_match_STRs_list.append(longest_STRs_dict)

    # TODO: Check database for matching profiles
    for data in databases:
        if compare_dicts(longest_STRs_dict, data):
            print(data["name"])
            sys.exit(0)
    print("No match")

def compare_dicts(dict1, dict2):
    # get 2 dict started from second key
    keys1 = list(dict1.keys())[1:]
    keys2 = list(dict2.keys())[1:]

    for key in keys1:
        # check key in both dicts
        if key in keys2:
            if int(dict1[key]) != int(dict2[key]):
                return False
        else:
            return False
    return True

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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
