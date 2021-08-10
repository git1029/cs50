#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If name match (non-case-senstitve) set preference
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loop through voter preferences
    for (int i = 0; i < voter_count; i++)
    {
        int vote_count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            int preference = preferences[i][j];

            // Find first non-eliminated preference and increment candidate votes
            if (!candidates[preference].eliminated && vote_count == 0)
            {
                candidates[preference].votes++;
                vote_count++;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Get number of votes to win (50% of voters)
    float votes_to_win = voter_count / 2.0;
    int winner_count = 0;

    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate has enough votes to win print candidate name
        if (candidates[i].votes > votes_to_win)
        {
            printf("%s\n", candidates[i].name);
            winner_count++;
        }
    }

    // If there are winners
    if (winner_count > 0)
    {
        return true;
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialize min votes with max votes candidate can have
    int min_votes = voter_count;

    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate not eliminated and has less votes than current min set min to their vote count
        if (!candidates[i].eliminated && (candidates[i].votes < min_votes))
        {
            min_votes = candidates[i].votes;
        }
    }

    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int not_eliminated = 0;
    int has_min_votes = 0;

    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate is not elminiated
        if (!candidates[i].eliminated)
        {
            not_eliminated++;

            // Check if votes equal to min votes
            if (candidates[i].votes == min)
            {
                has_min_votes++;
            }
        }
    }

    // If all non eliminated canidates have equal number of votes is a tie
    if (not_eliminated == has_min_votes)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If not already eliminated and has min votes eliminate
        if (!candidates[i].eliminated && (candidates[i].votes == min))
        {
            // printf("With %i votes %s has been eliminated\n", candidates[i].votes, candidates[i].name);
            candidates[i].eliminated = true;
        }
    }
    return;
}
