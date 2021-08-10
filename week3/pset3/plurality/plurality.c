#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

void bubble_sort(candidate candidate_array[], int n);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Linear search (as candidate array is not sorted)
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Sort by most votes
    // Using bubble sort (merge sort is overkill for such a small array)
    bubble_sort(candidates, candidate_count);

    // Find candidate(s) with most votes (at end of array)
    int most_votes = candidates[candidate_count - 1].votes;

    // Loop backwards through array
    int i = candidate_count - 1;
    while (candidates[i].votes == most_votes)
    {
        // Print candidate(s) with most votes
        printf("%s\n", candidates[i].name);
        i--;
    }
}

// Implement bubble sort on candidate array of length n
void bubble_sort(candidate candidate_array[], int n)
{
    int swaps = 0;

    for (int i = 0; i < n - 1; i++)
    {
        if (candidate_array[i + 1].votes < candidate_array[i].votes)
        {
            candidate tmp = candidate_array[i];
            candidate_array[i] = candidate_array[i + 1];
            candidate_array[i + 1] = tmp;
            swaps++;
        }
    }

    if (swaps == 0)
    {
        return;
    }
    else
    {
        bubble_sort(candidate_array, n - 1);
    }
}
