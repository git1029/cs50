# Port of readability.c
from cs50 import get_string


def main():
    # Prompt user for text
    text = get_string("Text: ")
    while len(text) < 1:
        text = get_string("Text: ")

    # Calculate Coleman-Liau index
    index = calculate_cl(text)

    # Print grade
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


def calculate_cl(text):
    """Calculate Coleman-Liau index on text."""

    # Initialize counters
    letters = 0
    words = 1
    sentences = 0

    # Loop over text
    for char in text:
        if char.isalpha():
            letters += 1
        elif char in [".", "!", "?"]:
            sentences += 1
        elif char == " ":
            words += 1

    # Calculate index parameters
    L = 100 * letters / words
    S = 100 * sentences / words

    # Return index
    return 0.0588 * L - 0.296 * S - 15.8


if __name__ == "__main__":
    main()