// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 7919;

// Number of words in dictionary
int words = 0;

// Hash table
node *table[N];

// Prototypes
void free_word(node *word, int *word_count);
void table_stats(void);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get hash of word
    int hash_word = hash(word);

    // Get linked list from table
    node *word_dict = table[hash_word];

    // Loop through word(s) in linked list
    while (word_dict != NULL)
    {
        // If words match return true
        if (strcasecmp(word, word_dict->word) == 0)
        {
            return true;
        }

        // Move to next word node in list
        word_dict = word_dict->next;
    }

    // No match
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Can assume dictionary word will only contain lowercase alphabetical characters or apostrophes (but not at start)
    // return tolower(word[0]) - 97;

    // djb2 hash function
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))
    {
        c = tolower(c);
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }

    // Initialize node table to NULL pointers
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Prepare to load words
    int index = 0;
    node *word = NULL;

    // Read each word in dictionary
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        // If start of new word allocate memory for new node
        if (index == 0)
        {
            word = malloc(sizeof(node));
            if (word == NULL)
            {
                printf("Unable to allocate memory for new dictionary word\n");
                return false;
            }
        }

        // Allow only alphabetical characters and apostrophes (can assume no words begin with apostrophes)
        if (isalpha(c) || c == '\'')
        {
            // Append character to word
            word->word[index] = c;
            index++;
        }

        // We must have found a whole word (reached \0 or newline)
        else if (index > 0)
        {
            // Terminate current word
            word->word[index] = '\0';

            // Get hash of new word
            int hash_word = hash(word->word);

            // Set new word to point current start of linked list
            word->next = table[hash_word];

            // Insert new word at start of linked list
            table[hash_word] = word;

            // Update counter
            words++;

            // Prepare for next word
            index = 0;
        }
    }

    // Check whether there was an error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", dictionary);
        return false;
    }

    // Close dictionary
    fclose(file);

    // Load successful
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // table_stats();

    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Make copy of word count
    int word_count = words;

    // Loop through hash table
    for (int i = 0; i < N; i++)
    {
        // Get linked list
        node *list = table[i];

        // Free list
        free_word(list, &word_count);
    }

    // If some words not free'd return false
    if (word_count > 0)
    {
        return false;
    }

    // If successfully unloaded
    return true;
}

// Free nodes in linked list
void free_word(node *list, int *word_count)
{
    // Handle base case
    if (list == NULL)
    {
        return;
    }

    // Free next
    free_word(list->next, word_count);

    // Free node
    free(list);

    // Decrement word count
    *word_count = *word_count - 1;
}

// Get hash table stats
void table_stats(void)
{
    int avg = 0, min = 0, max = 0;

    for (int i = 0; i < N; i++)
    {
        // Get linked list from table
        node *list = table[i];

        int count = 0;

        // Loop through word(s) in linked list
        while (list != NULL)
        {
            count++;
            list = list->next;
        }

        if (count > max)
        {
            max = count;
        }

        if (i == 0 || count < min)
        {
            min = count;
        }

        avg += count;
    }

    avg /= N;

    printf("Table size %i\n", N);
    printf("Avg list length: %i\n", avg);
    printf("Min list length: %i\n", min);
    printf("Max list length: %i\n", max);
}
