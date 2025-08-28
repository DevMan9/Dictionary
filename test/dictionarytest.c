#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../source/dictionary.x"

int main()
{
    struct Dictionary *dictionary = NULL;
    CreateDictionary(&dictionary);

    DictionaryAdd(dictionary, "patrick", "the ugly barnacle");
    DictionaryAdd(dictionary, "--version", "");
    DictionaryAdd(dictionary, "--help", "");
    DictionaryAdd(dictionary, "key", "value");

    char *key = NULL;
    char *value = NULL;

    key = "patrick";
    DictionaryGet(dictionary, key, &value);
    printf("(%s, %s)\n", key, value);
    free(value);

    key = "--help";
    DictionaryGet(dictionary, key, &value);
    printf("(%s, %s)\n", key, value);
    free(value);

    key = "key";
    DictionaryGet(dictionary, key, &value);
    printf("(%s, %s)\n", key, value);
    free(value);

    key = "patrick";
    DictionaryRemove(dictionary, key, NULL);
    DictionaryGet(dictionary, key, &value);
    printf("(%s, %s)\n", key, value);
    free(value);

    key = "--version";
    DictionaryRemove(dictionary, key, NULL);
    DictionaryGet(dictionary, key, &value);
    printf("(%s, %s)\n", key, value);
    free(value);

    DestroyDictionary(&dictionary);

    return 0;
}