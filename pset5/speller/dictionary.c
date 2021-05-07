// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 280000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lc_word[strlen(word)];
    for (int i = 0; i <= strlen(word); i++)
    {
        if (islower(word[i]))
        {
            lc_word[i] = word[i];
        }
        else
        {
            lc_word[i] = tolower(word[i]);
        }
    }
    unsigned int index = hash(lc_word);
    if (table[index] == NULL)
    {
        return false;
    }
    else if (strcasecmp(table[index]->word, word) == 0)
    {
        return true;
    }
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
//  I have used the djb1 hash functions by Dan Bernstein. The C version I used was obtained from https://gist.github.com/MohamedTaha98/ccdf734f13299efb73ff0b12f7ce429f
unsigned int hash(const char *key)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c;    /* hash * 33 + c */
    }
    return hash % N;
}
int word_count = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, buffer);
        n->next = NULL;
        unsigned int index = hash(n->word);
        if (table[index] != NULL)
        {
            n->next = table[index];
            table[index] = n;
        }
        else
        {
            table[index] = n;
        }
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}

