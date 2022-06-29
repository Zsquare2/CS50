// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

//included by me
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <strings.h>
#include <math.h>

unsigned int word_counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// TODO: Choose number of buckets in hash table
const unsigned int N = 1000000;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_number = hash(word);
    //make a constat word
    node *cursor = table[hash_number];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    //just sum random hash when its enough memory
    int lenght = strlen(word);
    unsigned long hashed = 0;
    for (int i = 0; i < lenght; i++)
    {
        hashed += (toupper(word[i]) * (i + 26));
    }
    return hashed;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //open a dictioanary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %c.\n", *dictionary);
        return false;
    }

    //read dictioanary file, stings from file

    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        //crate a new node
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }
        //copy form buffer to node's "word"
        strcpy(new->word, buffer);

        //use has function to get tables number
        int hash_table_number = hash(new->word);

        //insert new node into hash table
        new->next = table[hash_table_number];
        table[hash_table_number] = new;

        //count words for other function
        word_counter++;
    }
    //close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //returns form load function
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    //unloads with temp
    for (int i = 0; i <= N; i++)
    {
        // set coursor to point what to free
        node *cursor = table[i];

        //make a loop for all linear search
        while (cursor != NULL)
        {
            //set temp to not lose data that's left
            node *temp = cursor->next;
            //free data
            free(cursor);
            //set cursor to next pointer
            cursor = temp;
        }
    }
    return true;
}
