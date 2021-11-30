// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 500;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0; word[i] != "\0"; i++)
    {
        sum += word[i];
    }
    return sum % LENGTH;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Failed to open the dictionary!\n");
        return 1;
    }
    while (true)
    {
        char *str;
        fscanf(dict, "%s", str);
        if (fscanf(dict, "%s", str) == EOF)
        {
            break;
        }
        else
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                printf("Failed to allocate memory for new node!\n");
                return 2;
            }
            int i = hash(str);
            if (table[i] == NULL)
            {
                strcpy(table[i]->word, str);
            }
            else
            {
                n->next = table[i];
                table[i]->next = n;
            }
            
        }
    }
    
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
