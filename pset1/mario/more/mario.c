#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for pyramid height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Draw pyramid
    for (int i = 0; i < height; i++)
    {
        // Draw spaces
        for (int j = height - i - 1; j > 0; j--)
        {
            printf(" ");
        }
        // Draw hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // Draw spaces
        for (int j = 0; j < 2; j++)
        {
            printf(" ");
        }
        // Draw hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}