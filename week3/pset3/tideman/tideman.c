#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void merge_sort(pair arr[], int len, int off);
void sort_pairs(void);
bool creates_loop(int root, int end);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If name match (non-case-senstitve) set rank
        if (strcasecmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop through ranks array (ignoring last place)
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // For each preference loop through candidates less preferred (i.e. lower down in rakings)
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Update h2h preferences array
            int winner = ranks[i];
            int loser = ranks[j];
            preferences[winner][loser]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Initialize global pair count
    pair_count = 0;

    // Loop through preferences array
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // If one candidate preferred over another add to pairs array (ignore ties)
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    merge_sort(pairs, pair_count, 0);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Look through sorted pairs
    for (int i = 0; i < pair_count; i++)
    {
        pair p = pairs[i];

        int start = p.winner;
        int end = p.loser;

        // Lock pair if connection does not create a loop
        if (!creates_loop(start, end))
        {
            locked[start][end] = true;
        }
    }

    return;
}

// Check if connection between root and end will create a loop
bool creates_loop(int root, int end)
{
    // If inverse is locked loop created
    if (locked[end][root])
    {
        return true;
    }

    // Else check loser other pairs
    for (int i = 0; i < candidate_count; i++)
    {
        // Only need to check loser pairs if locked
        if (locked[end][i])
        {
            // Recursively check new loser against root
            // NB: only want to return/exit if recursion returns true
            // NB: blanket return here would also force exit even no loops found, preventing join
            if (creates_loop(root, i))
            {
                return true;
            }
        }
    }

    // If no loop return false
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Initialize wins/losses
        int wins = 0;
        int losses = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }

            if (locked[i][j])
            {
                // Increment win count
                wins++;
            }
            else if (locked[j][i])
            {
                // Increment loss count
                losses++;
            }
        }

        // Candidate at source of graph will have 1 or more wins with no losses 
        if (wins > 0 && losses == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}


// Implement merge sort on array arr of length len
// Off is an offset to map arr index overwrites to correct locations (not strictly necessary)
void merge_sort(pair arr[], int len, int off)
{
    // If array has only one value return (end of halving)
    if (len == 1)
    {
        return;
    }

    // Get middle index of array
    int mid = len / 2;

    // Get lengths of left and right halves
    int llen = mid;
    int rlen = len - mid;

    // Initialize arrays to hold halves
    pair left[llen];
    pair right[rlen];

    // Populate left half
    for (int i = 0; i < llen; i++)
    {
        left[i] = arr[i];
    }

    // Populate right half
    for (int i = 0; i < rlen; i++)
    {
        right[i] = arr[mid + i];
    }

    // Recursively pass left and right halves
    merge_sort(left, llen, off);
    merge_sort(right, rlen, off + mid);

    // Initialize sorting variables
    int k = 0;
    int li = 0;
    int ri = 0;

    // While within arr bounds
    while (k < rlen + llen)
    {
        if (li >= llen)
        {
            // if left depleted add remaining from right
            for (int i = 0; i < rlen - ri; i++)
            {
                // printf("Setting arr[%i] to %i\n", k + off, right[ri + i]);
                arr[k] = right[ri + i];
                k++;
            }
        }
        else if (ri >= rlen)
        {
            // if right depleted add remaining from left
            for (int i = 0; i < llen - li; i++)
            {
                // printf("Setting arr[%i] to %i\n", k + off, left[li + i]);
                arr[k] = left[li + i];
                k++;
            }
        }
        else
        {
            int votesA = preferences[left[li].winner][left[li].loser];
            int votesB = preferences[right[ri].winner][right[ri].loser];

            // Compare values in left and right arrays
            // if (left[li] > right[ri])
            if (votesA > votesB)
            {
                // If left < right sort left value, increment index in left array
                arr[k] = left[li];
                // printf("Setting arr[%i] to %i\n", k + off, left[li]);
                li++;
            }
            else
            {
                // If right < left sort right value, increment index in right array
                arr[k] = right[ri];
                // printf("Setting arr[%i] to %i\n", k + off, right[ri]);
                ri++;
            }
            k++;
        }
    }
}