// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = HASH_MAX;
int countWord = 0;
bool loaded = false;
// Hash table
node *table[100];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hashing word to get index for comparing word in dict
    int i = hash(word);
    bool flag = false;
    node *tmp = table[i];
    while(tmp != NULL) {
        if(strcasecmp(tmp->word, word) == 0) {
            flag = true;
        }
        tmp = tmp->next;
    }
    if(flag)
        return true;
    else
        return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    for(int i = 0; word[i] != '\0'; i++) {
        sum += toupper(word[i]); // to make sure lower-case and upper-case have the same value
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL) return false;

    // read each character in dict file and store in word
    char ch;
    char word[LENGTH + 1];
    int indexTable;
    // create pointer to point a new space for storing new words
    node *newNode;
    // read character until reaching end of file
    while(fscanf(dict, "%s", word) != EOF) {
        indexTable = hash(word);
        newNode = malloc(sizeof(node));
        if(newNode == NULL) return false;
        strcpy(newNode->word, word);

        newNode->next = table[indexTable];
        table[indexTable] = newNode;
        // count number of words in dictionary
        countWord++;
    }

    if(fscanf(dict, "%s", word) == EOF) {
        loaded = true;
        fclose(dict);
        return true;
    }
    fclose(dict);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if(loaded)
        return countWord;
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *p;
    int flag = 0;
    for(int i = 0; i < N; i++) {
        p = table[i];
        node *tmp;
        while(p != NULL) {
            tmp = p->next;
            free(p);
            p = tmp;
        }
        flag++;
    }
    if(flag == N)
        return true;
    return false;
}
