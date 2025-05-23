import csv
import sys


def main():


    if(len(sys.argv) != 3):
        print("Usage: script.py file.csv file.txt")
    
    databaseFile = sys.argv[1]
    sequenceFile = sys.argv[2]

    rows = []
    str_list = []

    with open(databaseFile) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)
        str_list = reader.fieldnames[1:]
        
    with open(sequenceFile) as file:
        conteudo = file.read()
    
    sequenceCount = {}
    for i in str_list:
        sequenceCount[i] = longest_match(conteudo, i)
    
    # TODO: Check database for matching profiles
    for dict in rows:
        match = True
        for i, seq in enumerate(str_list):
            if int(dict[seq]) != sequenceCount[seq]:
                match = False
                break
        if match:
            print(f"{dict["name"]}")
            break
    else:
        print("No match")
    

    return


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
