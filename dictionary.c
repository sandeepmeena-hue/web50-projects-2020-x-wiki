// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

long count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 678;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    int m = hash(word);
    for (node *tmp = table[m]; tmp != NULL; tmp = tmp -> next)
    {
        if (strcasecmp(word,tmp -> word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    for (int i = 0; i < 26; i++)
    {   for (int j = 0; j < 26; j++)
        {
            if (strcasecmp(word,"a") == 0)
            {
                return 0;
            }
            if (((word[0] == 97 + i) || (word[0] == 65 + i)) && (isalpha(word[1]) == 0))
            {
                return 1;
            }
            if (((word[0] == 97 + i) || (word[0] == 65 + i)) && ((word[1] == 97 + j) || (word[1] == 65 + j)))
            {
                return 26*i + j + 2;
            }
        }
    }
    return -1;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary,"r");
    if (file == NULL)
    {
        printf("file could not open\n");
        return 1;
    }
    char *str = malloc(143092);
    while(fscanf(file,"%s",str) != EOF)
    {
        int m = hash(str);
        if (table[m] == NULL)
        {
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return 1;
            }
            strcpy(n -> word,str);
            n -> next = NULL;
            table[m] = n;
            count += 1;
        }
        else if (table[m] != NULL)
        {
            node *n = malloc(sizeof(node));
            strcpy(n -> word,str);
            n -> next = table[m];
            table[m] = n;
            count += 1;
        }
        else
        {
            return false;
        }
    }
    fclose(file);
    free(str);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < 678; i++)
    {
        while(table[i] != NULL)
        {
            node *tmp = table[i] -> next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
