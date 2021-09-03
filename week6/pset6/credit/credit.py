# Port of credit.c
import re
from cs50 import get_string


def main():
    # Prompt user for card number
    number = get_string("Number: ")

    # Validate user input (using) str.isdecimal()
    # while not number.isdecimal():
    #     number = get_string("Number: ")

    # Validate user input (using regex)
    while not re.match("^[0-9]+$", number):
        number = get_string("Number: ")

    # Check if number is valid
    check = check_number(number)

    # If valid determine card issuer
    if check:
        if number[0:2] in ["34", "37"]:
            print("AMEX")
        elif number[0] == "4":
            print("VISA")
        elif 51 <= int(number[0:2]) <= 55:
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


def check_number(num):
    """Perform Luhn algorithm on card number."""

    # Get number length and initialize total
    n = len(num)
    total = 0

    # Loop over every other digits from second-to-last
    for i in range(n - 2, -1, -2):
        digit = int(num[i])

        if digit * 2 < 10:
            total += digit * 2
        else:
            total += (digit * 2) % 10
            total += 1

    # Add remaining digits
    for i in range(n - 1, -1, -2):
        digit = int(num[i])
        total += digit

    # If last digit of total is 0 valid else invalid
    return True if total % 10 == 0 else False


if __name__ == "__main__":
    main()