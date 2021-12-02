// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

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

// Number of words in Dictionary
int unsigned dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_value = hash(word);
    node *cursor = malloc(sizeof(node));

    cursor = table[hash_value];
    
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0) 
        {
            free(cursor);
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int str_len = strlen(word);
    int value = 0;
    for (int i = 0; i < str_len; i++)
    {
        value += word[i];
        //printf("%c\n", word[i]);
    }
    value %= N;
    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
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
        dict_size++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = malloc(sizeof(node));
    node *tmp = malloc(sizeof(node));
    for (int i = 0; i < N; i++)
    {
        while(table[i] != NULL)
        {
            cursor = table[i]->next;
            tmp = table[i];
            free(tmp);
            table[i] = cursor;
        }
    }
    free(cursor);
    free(tmp);
    return true;
}
