// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define HASH_MAX 100

// Prototypes
unsigned int hash(const char *word);
bool load(const char *dictionary);
bool check(const char *word);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
