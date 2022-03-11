// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Number of words in dictionary
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_value = hash(word); // get the hash value of the word
    node *cursor = table[hash_value]; // point to the node in hash table
    
    while (cursor != NULL) // while cursor is not NULL
    {
        if (strcasecmp(cursor->word, word) == 0) // if word matches the word in cursor node
        {
            return true; // return true
        }
        cursor = cursor->next; // move to the next node
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c = 0;
    while (c == toupper(*word++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c ;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char str[LENGTH + 1]; // word to assigned when loading dictionary

    FILE *dict = fopen(dictionary, "r"); // open the dictionary (file) for reading
    if (dict == NULL) // if cannot open, terminate the function
    {
        printf("Failed to open the dictionary!\n");
        return 1;
    }
    while (fscanf(dict, "%s", str) != EOF) // scan/read the dictionary one string at a time assigning each string to str variable
    {
        node *n = malloc(sizeof(node)); // allocate memory for temporary node
        if (n == NULL) // if cannot allocate, terminate the function
        {
            printf("Failed to allocate memory for new node!\n");
            return 2;
        }

        strcpy(n->word, str); // copy str (word) from dictionary to word field in n node
        int i = hash(str); // get the hash value of str (word) 
        n->next = table[i]; // set new pointer
        table[i] = n; // set head to new pointer

        word_count++; // increment word count
    }
    fclose(dict); // close the dictionary (file)
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0) // if any words exist
    {
        return word_count; // return word count
    }
    else // if not
    {
        return 0; // return 0
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) // iterate through buckets
    {
        node *cursor = table[i]; // set cursor to current bucket 
        while (cursor != NULL) // while cursor is not NULL
        {
            node *tmp = cursor; // store current node in tmp variable
            cursor = cursor->next; // move cursor to the next node
            free(tmp); // free tmp (current node)
        }
        if (i == N - 1 && cursor == NULL) // if the end of table and cursor is NULL
        {
            return true;
        }
    }
    return false;
}
