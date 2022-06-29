import csv
import sys


def main():

    # TODO: Check for command-line usage

    # ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: pythin data.csv sequennce.txt")

    # TODO: Read database file into a variable
    # get filename
    dataFile = sys.argv[1]
    persons = []

    # open the file
    with open(dataFile) as file:
        # read data to from file
        reader = csv.DictReader(file)

        # write to dic persons
        for person in reader:
            persons.append(person)

        # gets all names of str's reads fieldnames start from 1
        str_names = reader.fieldnames[1:]

    # TODO: Read DNA sequence file into a variable
    # get file name for txt with sequence
    sequenceFile = sys.argv[2]

    # open txt file
    with open(sequenceFile) as file:

        # get dna sequence that we need to check
        sequence = file.readline()

    # TODO: Find longest match of each STR in DNA sequence
    # make dict with all str values form dna that we need to check
    given_dna = {}
    # getting that with loop
    for str in str_names:
        given_dna[str] = int(longest_match(sequence, str))

    # TODO: Check database for matching profiles
    # check every person if his dna maches given dna in txt
    # for that create check_dna function
    for person in persons:
        if check_dna(person, given_dna):
            # if yes print who is it
            print(person['name'])
            return
    else:
        print("No match")
    return


# checks if dna matches
def check_dna(person, given_dna):
    # checks if every str matches
    for str in given_dna:
        # to compare we need that to be ints
        txt_str = int(given_dna[str])
        csv_str = int(person[str])
        # if matching fails returns False
        if csv_str != txt_str:
            return False
    # if all strs matches it means that this persons dna matches given dna in txt
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
