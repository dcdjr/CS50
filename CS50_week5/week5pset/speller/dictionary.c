// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Assigns memory to store a word from fscanf
char word_buffer[LENGTH + 1];

// Stores number of words loaded into dictionary
int numWords = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Initializes int with hash index of word
    int index = hash(word);

    // Creates a node pointer called cursor that points to the head of the word's linked list
    node *cursor = table[index];

    // While loop traverses linked list
    while (cursor != NULL)
    {
        // Conditional determines if the current node matches the word parameter
        // If yes, check() returns true, else, we move to the next pointer
        // Until cursor equals NULL, aka the end of the linked list
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Bucketizes based on the first two letters of the given word
    return (((toupper(word[0]) - 'A') * 26) + (toupper(word[1]) - 'A')) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opens the dictionary file
    FILE *dict = fopen(dictionary, "r");

    // Checks if dictionary file exists
    if (dict == NULL)
    {
        return false;
    }

    // Stores hashed value
    int index;

    // Iterates until fscanf() reaches EOF
    while (fscanf(dict, "%s", word_buffer) != EOF)
    {
        // Allocates memory for the new node to be added to the linked list at location index
        node *n = malloc(sizeof(node));

        // Checks if memory was correctly allocated
        if (n == NULL)
        {
            return false;
        }

        // Increments numWords for size() function
        numWords++;

        // Copies word gotten from fscanf() from word_buffer to the current node's word field
        strcpy(n->word, word_buffer);

        // Gives variable index the value (where to insert the next node in the hash table)
        index = hash(n->word);

        // Sets the current node's next field to the head of the linked list it is to be inserted into
        n->next = table[index];

        // Sets the pointer in location index to the new head of the linked list at that location,
        // the current node n.
        table[index] = n;
    }

    // Closes dictionary file pointer
    fclose(dict);

    // load() returns true if successfully loaded
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return numWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Creates node pointers cursor and tmp
    node *cursor;
    node *tmp;

    // Iterates over buckets of hash table
    for (int i = 0; i < N; i++)
    {
        // Sets the cursor to the head of the ith linked list
        cursor = table[i];

        // Traverses ith linked list
        while (cursor != NULL)
        {
            // Sets temporary pointer to current node
            tmp = cursor;

            // Moves cursor to next node in the ith linked list
            cursor = cursor->next;

            // Frees the memory at the temporary pointer, conserving access to the remaining nodes
            free(tmp);
        }
    }
    return true;
}
