#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    DictionaryGet(dictionary, key, (void **)&value);
    printf("(%s, %s)\n", key, value);
    assert(strcmp(value, "the ugly barnacle") == 0);

    key = "--help";
    DictionaryGet(dictionary, key, (void **)&value);
    printf("(%s, %s)\n", key, value);
    assert(strcmp(value, "") == 0);

    key = "key";
    DictionaryGet(dictionary, key, (void **)&value);
    printf("(%s, %s)\n", key, value);
    assert(strcmp(value, "value") == 0);

    key = "patrick";
    DictionaryRemove(dictionary, key, NULL);
    DictionaryGet(dictionary, key, (void **)&value);
    printf("(%s, %s)\n", key, value);
    assert(value == NULL);

    key = "--version";
    DictionaryRemove(dictionary, key, NULL);
    DictionaryGet(dictionary, key, (void **)&value);
    printf("(%s, %s)\n", key, value);
    assert(value == NULL);

    key = "structure";
    void *custom_pointer = malloc(16);
    void *value2 = NULL;

    DictionaryAdd(dictionary, key, custom_pointer);
    DictionaryGet(dictionary, key, &value2);
    assert(value2 == custom_pointer);
    free(custom_pointer);

    DestroyDictionary(&dictionary);

    printf("All tests passed!\n");
    return 0;
}