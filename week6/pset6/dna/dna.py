import csv
import sys


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE SEQUENCE")

    # Read DNA database into memory
    database = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # Get list of STRs from database
    strs = list(database[0])[1:]

    # Read DNA sequence into memory
    with open(sys.argv[2], "r") as file:
        sequence = file.read().rstrip()

    # Get STR repetition count in sequence
    seq_count = {}
    for str_type in strs:
        seq_count[str_type] = str_count(sequence, str_type)

    # Check for match in database
    for data in database:
        # Initialize match bool/count
        match = False
        match_count = 0

        # Check STR count against data count
        for str_type in strs:
            if int(data[str_type]) == seq_count[str_type]:
                match_count += 1

        if match_count == len(strs):
            # if all STR counts match print name
            match = True
            print(data["name"])
            break

    if not match:
        # else no match
        print("No match")


def str_count(seq, str_type):
    """Count highest back-to-back sequence of STR str_type in DNA sequence seq."""

    # Initialize count and index
    counts = [0]
    count = 0

    # Loop through sequence
    while len(seq) > 0:
        # Get index of next occuring STR in seq
        index = seq.find(str_type)

        if index == -1:
            # if STR not found break out of loop
            if count > 0:
                counts.append(count)
            break

        if index == 0:
            # if STR found at start of seq increment repetition count, slice seq
            count += 1
            seq = seq[index + len(str_type):]
        else:
            # else restart rep count, slice seq to next STR occurence
            if count > 0:
                counts.append(count)
                count = 0
            seq = seq[index:]

        if len(seq) == 0:
            # if reach end of seq append count (handle seq ending with STR)
            if count > 0:
                counts.append(count)

    # Return STR max repetition count
    return max(counts)


if __name__ == "__main__":
    main()