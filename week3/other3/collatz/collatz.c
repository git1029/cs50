#include <stdio.h>
#include <cs50.h>

int collatz(int n);


int main(void)
{
    int start[] = {1, 2, 3, 4, 5, 6, 7, 8, 15, 27, 50};

    for (int i = 0; i < 11; i++)
    {
        int n = start[i];
        printf("n: %i, steps: %i\n", n, collatz(n));
    }
}

int collatz(int n)
{
    if (n == 1)
        return 0;
    else if (n % 2 == 0)
        return 1 + collatz(n / 2);
    else
        return 1 + collatz(3 * n + 1);
}