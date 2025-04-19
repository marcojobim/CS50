// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 200003

// Hash table
node *table[N];

// Size
int hash_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *ptr = table[index];

    while (ptr != NULL)
    {
        int len1 = strlen(ptr->word);
        int len2 = strlen(word);

        if (len1 == len2)
        {

            bool cmp = true;
            for (int i = 0; i < len1; i++)
            {
                if (tolower(word[i]) != tolower(ptr->word[i]))
                {
                    cmp = false;
                    break;
                }
            }

            if (cmp)
                return true;
        }

        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381; // Try 33 and 17 later

    int i = 0;
    while (word[i] != '\0')
    {
        hash = hash * 33 + tolower(word[i]);
        i++;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
        return false;

    char word[LENGTH + 1];
    while (fscanf(input, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(input);
            return false;
        }

        strcpy(n->word, word);

        int index = hash(n->word);
        n->next = table[index];
        table[index] = n;
        hash_size++;
    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return hash_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return true;
}
