#include <cs50.h>
#include <math.h>
#include <stdio.h>

void checkCard(long number);

int main(void)
{
    // Prompt user for card number
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    checkCard(number);

    // long test[16] = {
    //     378282246310005,
    //     371449635398431,
    //     378734493671000,
    //     30569309025904,
    //     6011111111111117,
    //     6011000990139424,
    //     3530111333300000,
    //     3566002020360505,
    //     2221000000000009,
    //     2223000048400011,
    //     2223016768739313,
    //     5555555555554444,
    //     5105105105105100,
    //     4111111111111111,
    //     4012888888881881,
    //     4222222222222
    // };

    // for (int i = 0; i < 16; i++)
    // {
    //     checkCard(test[i]);
    // }
}

// Check card number using Luhn's Algorithm
void checkCard(long number)
{
    // Store number in new variable
    long num = number;

    // Initialize algorithm sum
    int sum = 0;

    // Initialize variable for card number length
    int len = 0;

    // Loop through digits
    while (num > 0)
    {
        // Get digit (from right)
        int digit = num % 10;

        if (len % 2 == 0)
        {
            // If digit position even add digit value to sum
            sum += digit;
        }
        else
        {
            // if digit position odd double and add result digits
            digit *= 2;
            sum += digit / 10 + digit % 10;
        }

        num /= 10;
        len++;
    }

    // Check algorithm sum and number length is valid
    if (sum % 10 == 0 && (len == 13 || len == 15 || len == 16))
    {
        // Get first 2 digits of number
        int start = number / pow(10, len - 2);

        // Check card type
        if (len == 13 || len == 16)
        {
            if (start / 10 == 4)
            {
                printf("VISA\n");
            }
            else if (start >= 51 && start <= 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (len == 15)
        {
            if (start == 34 || start == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}