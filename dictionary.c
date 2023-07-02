// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <strings.h>
#include <math.h>

#include "dictionary.h"

//  Global variable representing the number of words loaded into the dico.
unsigned int word_amount = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Prototype
bool free_list(node *p);

// TODO: Choose number of buckets in hash table
const unsigned int N = 5000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get key for this word

    unsigned int key = hash(word);

    //  Go to key index in hash table and get the pointer to the first node in that linked list.
    //  If that pointer contains a 0 at this index, it means there is no LL and i.e. no words there, meaning the word is not in the dico.

    node *p = table[key];
    if (p == 0)
    {
        return false;
    }

    //  If there is pointer to a LL at that location in the hash table, search that LL. Compare the value of word with node->word. If there's a match, return 1
    //  If the end of the LL is reached (i.e. node->next == NULL), and no match was found, return 0.
    else
    {
        node *cursor = p;
        while (cursor->next != NULL)
        {
            if (strcasecmp(word, cursor->word) == 0)
            {
                return true;
            }
            cursor = cursor->next;
        }
        //  Handle the case where we reached the end of the LL.
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //  Algorithm  that  uses the ASCII values of each charachter and also takes into account the position of the charachter in that word.
    //  This algorithm insîred me after watching this video on hash functions  (https://www.youtube.com/watch?v=jtMwp0FqEcg).
    //  Then, by playing with the size of the hash table (N), we obtain pretty good results for the computing times.

    int length = strlen(word);
    int h = 0;

    for (int i = 0; i < length; i++)
    {
        h += (int) tolower(word[i]) * (i + 1);
    }
    return round(h % N);

    // OG algorithm
    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Initialise hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = 0;
    }
    //  Open the dictionary file, if it's empty return error.
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Couldn't open %s.\n", dictionary);
        fclose(file);
        return false;
    }

    //  Read strings from the dictionary one at the time.
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        //  For each word read, create a new node and copy that word into the new node. If the node returns NULL, return 1.
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        //  Copy word to node and set it's pointer to the next node to NULL.
        strcpy(n->word, word);
        n->next = NULL;

        //  Hash word to obtain hash value and to know to which linked list to add it (i.e. what the index in the hashtable that points the the linked list where
        // to add the word?)
        int table_index = hash(word);

        //  If there's not yet a LL starting at the index in the table, create a new LL.

        if (table[table_index] == 0)
        {
            table[table_index] = n;
        }

        // If there's already a linked list at that location in the table, insert the word to the linked list.
        else
        {
            n->next = table[table_index];
            table[table_index] = n;
        }
        word_amount ++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_amount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int amount_freed = 0;
    int amount_not_freed = 0;
    //  Iterate over the hash table, and for every element in the table that is not null, free the linked list associated with it.
    for (int i = 0; i < N; i++)
    {
        bool b = free_list(table[i]);
        if (b == true)
        {
            amount_freed ++;
        }
        else
        {
            amount_not_freed ++;
        }
    }
    if (amount_not_freed != 0)
    {
        return false;
    }

    return true;
}

bool free_list(node *p)
{
    //  Handle base case
    if (p == NULL)
    {
        return true;
    }
    //  If this isn't the last node in the list, free the next node.
    if (p->next != NULL)
    {
        free_list(p->next);
    }

    //  If this is the last node in the list, free it
    else if (p->next == NULL)
    {
        free(p);
        return true;
    }
    //  Once all the next nodes are freed, free the current node.
    free(p);
    return true;
}