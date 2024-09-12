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

// Number of buckets in hash table
const unsigned int N = 50000;

// Prime number to be used in hash function
const unsigned int PRIME = 31;

// Hash table
node *table[N];

// Initalize global variables
int hash_value;
int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Calculates hash value of word being checked in dictionary
    hash_value = hash(word);

    // Access linked lists in hash table at hash value's location
    node *cursor = table[hash_value];

    // While linked lists remain
    while (cursor != NULL)
    {
        // If word is in dictionary
        if (strcasecmp(cursor->word, word) == 0)
        {
            // Return true
            return true;
        }

        // Point cursor to next node if words do not match
        cursor = cursor->next;
    }

    // If word is not in dictionary return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Initialize hash total
    unsigned long hash_total = 97;

    // For every letter of word
    for (int i = 1; i <= strlen(word); i++)
    {
        // Store values 1-26 corresponding to each letter
        int letter = toupper(word[i]) - 'A' + 1;

        // Multiply hash total by a prime number, add to letter values, add total number of letters,
        // and take the remainder divided by the number of buckets
        hash_total = (hash_total * PRIME + letter + strlen(word)) % N;
    }

    // Return hash total
    return hash_total;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    // Return false if dictionary fails to open
    if (source == NULL)
    {
        return false;
    }

    // Initialize variable of max length to store each word
    char word[LENGTH + 1];

    // Read each word in the file
    while (fscanf(source, "%s", word) != EOF)
    {
        // Create node for each word
        node *n = malloc(sizeof(node));

        // If not enough memory
        if (n == NULL)
        {
            // Close file
            fclose(source);

            // Free memory
            unload();

            // Return false
            return false;
        }

        // Copy string into the word field of new node
        strcpy(n->word, word);

        // Hash value of word
        hash_value = hash(word);

        // Set node's next pointer to the hash table's location at the hash value
        n->next = table[hash_value];

        // Insert node into hash table
        table[hash_value] = n;

        // Increment word count
        word_count++;
    }

    // Close the dictionary file
    fclose(source);

    // Return true if successful
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // If dictionary is loaded
    if (word_count > 0)
    {
        // Returns number of words in dictionary
        return word_count;
    }

    // If dictionary is not loaded returns 0
    return 0;
}

// Unloads dictionary from memory, returning true if successful
bool unload(void)
{
    // Loop through buckets in hash table
    for (int i = 0; i < N; i++)
    {
        // Set cursor to current head of linked list
        node *cursor = table[i];

        // While a linked list remains
        while (cursor != NULL)
        {
            // Store current linked list into tmp
            node *tmp = cursor;

            // Set cursor to next linked list
            cursor = cursor->next;

            // Free tmp (previous linked list)
            free(tmp);
        }
    }

    // Return true after freeing all memory
    return true;
}
