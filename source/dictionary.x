#ifndef STANDARD_DICTIONARY_X_0
#define STANDARD_DICTIONARY_X_0

struct Dictionary;

// Constructor.
void CreateDictionary(struct Dictionary **ret);

// Destructor.  The user is responsible for any data inside the dictionary.
void DestroyDictionary(struct Dictionary **dictionary_address);

// Adds the given key, value pair to the dictionary.
void DictionaryAdd(struct Dictionary *dictionary, char *key, void *value);

// Gets the value associated with the given key in the dictionary.
void DictionaryGet(struct Dictionary *dictionary, char *key, void **ret);

// Removes the
void DictionaryRemove(struct Dictionary *dictionary, char *key, void **ret);

#endif // STANDARD_DICTIONARY_X_0