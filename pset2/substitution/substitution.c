#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int check_usage(int argc, string argv[]);
void encrypt_text(string text, string key);

int main(int argc, string argv[])
{
    // Check for incorrect usage
    int check_fail = check_usage(argc, argv);
    if (check_fail)
    {
        return 1;
    }

    // Prompt user for plaintext string
    string plaintext = get_string("plaintext: ");

    // Print ciphertext
    printf("ciphertext: ");
    encrypt_text(plaintext, argv[1]);

    return 0;
}

// Encrypt text using substitution cipher
void encrypt_text(string text, string key)
{
    // Loop through chars in plaintext
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Get char
        char c = text[i];

        // Shift alphabetic char
        if (isalpha(c))
        {
            if (isupper(c))
            {
                c -= 'A';
                c = toupper(key[(int) c]);
            }
            else
            {
                c -= 'a';
                c = tolower(key[(int) c]);
            }
        }

        printf("%c", c);
    }
    printf("\n");
}

// Check for incorrect usage
int check_usage(int argc, string argv[])
{
    // Check for incorrect number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // Get key string
        string key = argv[1];

        // Check for incorrect key length
        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters\n");
            return 1;
        }

        // Initialize char counter
        int count[26] = {0};

        // Check for non-alphabetic chars
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if (!isalpha(key[i]))
            {
                printf("Key must be composed of alphabetic characters only\n");
                return 1;
            }

            // If alphabetic increment counter array
            int offset = 0;
            if (isupper(key[i]))
            {
                offset = 'A';
            }
            else
            {
                offset = 'a';
            }
            count[key[i] - offset]++;
        }

        // Check for duplicated chars
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            int offset = 0;
            if (isupper(key[i]))
            {
                offset = 'A';
            }
            else
            {
                offset = 'a';
            }

            if (count[key[i] - offset] != 1)
            {
                printf("Key must be composed of unique alphabetic characters\n");
                return 1;
            }
        }
    }

    return 0;
}