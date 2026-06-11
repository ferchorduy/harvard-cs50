// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define BUCKETS 17576

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table (#define BUCKETS)
// const unsigned int buckets = 74;
unsigned int dict_size = 0;

// Hash table
node *table[BUCKETS];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int bucket = hash(word);
    node *ptr = table[bucket];
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0) return true;
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (!isalpha(word[0])) return 0;
    int i = tolower(word[0]) - 'a';
    int j = (strlen(word) > 1 && isalpha(word[1])) ? tolower(word[1]) - 'a' : 0;
    int k = (strlen(word) > 2 && isalpha(word[2])) ? tolower(word[2]) - 'a' : 0;
    return i * 676 + j * 26 + k;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Error opening file.\n");
        return false;
    }

    char word_buffer[LENGTH + 1];

    while (fgets(word_buffer, LENGTH + 1, dict) != NULL)
    {
        node *word = malloc(sizeof(node));
        if (word == NULL)
        {
            return false;
        }
        word_buffer[strcspn(word_buffer, "\n")] = '\0';
        strcpy(word->word, word_buffer);
        unsigned int bucket = hash(word->word);
        word->next = table[bucket];
        table[bucket] = word;
        dict_size++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < BUCKETS; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
