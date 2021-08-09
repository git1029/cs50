#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int get_clindex(string text);

int main(void)
{
    // Get text from user
    string text = get_string("Text: ");

    // Calculate Coleman-Liau index
    int index = get_clindex(text);

    // Print reading level
    if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (index < 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

// Calculate Coleman-Liau index for given string
int get_clindex(string text)
{
    // Initalize index value and counters
    int letters = 0;
    int words = 1;
    int sentences = 0;

    // Loop through characters in text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];

        // If alphabetic add to letter count
        if (isalpha(c))
        {
            letters++;
        }

        // If space add to word count (exception for last word in sentence, therefore start words couner at 1)
        // Can assume sentences will not start or end with a space nor have multiple spaces in a row
        if (c == ' ')
        {
            words++;
        }

        // If period, exclamation point, or question mark add to sentence count
        // Can assume any seq. of chars ending with period, exclamaiton, or question mark to be a sentence
        if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }

    // printf("%i letters(s)\n", letters);
    // printf("%i words(s)\n", words);
    // printf("%i sentences(s)\n", sentences);

    // Calculate index and round to nearest whole number
    float L = letters * (100.0 / words);
    float S = sentences * (100.0 / words);
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}