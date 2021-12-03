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

// Hash table
node *table[N];

// Number of words in Dictionary
int unsigned word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    printf("checking\n");
    int hash_value = hash(word);
    node *cursor = table[hash_value];
    
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0) return true;
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    printf("hashing\n");
    unsigned long hash = 5381;
    int c = 0;
    while (c == toupper(*word++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c ;
    }
        //printf("%c\n", word[i]);
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    printf("loading\n");
    char str[LENGTH + 1]; 

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Failed to open the dictionary!\n");
        return 1;
    }
    while (fscanf(dict, "%s", str) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Failed to allocate memory for new node!\n");
            return 2;
        }

        strcpy(n->word, str);
        n->next = NULL;
        int i = hash(str);

        if (table[i] == NULL)
        {
            table[i] = n;
        }
        else
        {
            n->next = table[i];
            table[i] = n;
        }
        free(n);
        word_count++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0) 
    {
        return word_count;
    }
    else 
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    printf("unloading\n");
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (table[i] != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
