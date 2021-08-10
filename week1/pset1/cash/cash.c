#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for amount of change owed
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);
    int cents = round(change * 100);

    // Calculate min number of coins to make change
    int count = 0;
    int coins[4] = {25, 10, 5, 1};

    // If still change to give check quarters
    int i = 0;
    while (cents > 0)
    {
        count += cents / coins[i];
        cents = cents % coins[i];
        i++;
    }

    // Print min number of coins
    printf("%i\n", count);
}