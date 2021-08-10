#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void encrypt_text(string text, int key);

int main(int argc, string argv[])
{
    // Check for incorrect usage
    if (argc != 2)
    {
        // If not correct number of arguments
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // If not all-numeric second argument
        string key = argv[1];

        for (int i = 0, n = strlen(key); i < n; i++)
        {
            char c = key[i];

            if (!isdigit(c))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    // Get integer key from command-line arguments
    int key = atoi(argv[1]);

    // Get plaintext from user
    string plaintext = get_string("plaintext: ");

    // Get ciphertext
    printf("ciphertext: ");
    encrypt_text(plaintext, key);

    return 0;
}

void encrypt_text(string text, int key)
{
    // Loop over chars in text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];

        // Only shift alphabetic chars
        if (isalpha(c))
        {
            // Shift chars preserving case
            if (isupper(c))
            {
                c = (((c - 'A') + key) % 26) + 'A';
            }
            else
            {
                c = (((c - 'a') + key) % 26) + 'a';
            }
        }

        // Print character
        printf("%c", c);
    }
    printf("\n");
}