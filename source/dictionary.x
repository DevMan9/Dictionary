#ifndef STANDARD_DICTIONARY_X_0
#define STANDARD_DICTIONARY_X_0

struct Dictionary;

void CreateDictionary(struct Dictionary **ret);
void DestroyDictionary(struct Dictionary **dictionary_address);

void DictionaryAdd(struct Dictionary *dictionary, char *key, char *value);
void DictionaryGet(struct Dictionary *dictionary, char *key, char **ret);
void DictionaryRemove(struct Dictionary *dictionary, char *key, char **ret);

#endif // STANDARD_DICTIONARY_X_0