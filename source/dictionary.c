#include <stdlib.h>
#include <string.h>

#include "dictionary.x"

static const int NONE = 0;
static const int BUILD = 0b1;

struct CharacterNode
{
    struct CharacterNode *parent;
    struct CharacterNode *children[256];
    char *value;
};

struct Dictionary
{
    struct CharacterNode *root;
};

static void _CreateCharacterNode(struct CharacterNode **ret)
{
    (*ret) = malloc(sizeof(**ret));
    (*ret)->parent = NULL;
    memset((*ret)->children, 0, 256 * sizeof(*((*ret)->children)));
    (*ret)->value = NULL;
}

static void _DestroyCharacterNode(struct CharacterNode **character_node_address)
{
    if (character_node_address == NULL || *character_node_address == NULL)
    {
        goto skip;
    }
    struct CharacterNode *node = (*character_node_address);
    for (int i = 0; i < 256; i++)
    {
        if (node->children[i] != NULL)
        {
            _DestroyCharacterNode(&(node->children[i]));
        }
    }
    free(node->value);
    free(node);
    (*character_node_address) = NULL;
skip:
    return;
}

static void _CharacterNodeSetValue(struct CharacterNode *character_node, char *value)
{
    free(character_node->value);
    character_node->value = strdup(value);
}

static void _CharacterNodeGetValue(struct CharacterNode *character_node, char **ret)
{
    (*ret) = strdup(character_node->value);
}

void CreateDictionary(struct Dictionary **ret)
{
    (*ret) = malloc(sizeof(**ret));
    _CreateCharacterNode(&((*ret)->root));
}

void DestroyDictionary(struct Dictionary **dictionary_address)
{
    _DestroyCharacterNode(&((*dictionary_address)->root));
    free(*dictionary_address);
    *dictionary_address = NULL;
}

void _DictionaryNavigate(struct Dictionary *dictionary, char *key, int flags, struct CharacterNode **ret)
{
    struct CharacterNode *current = dictionary->root;
    char *remaining_key = key;
    while (1)
    {
        unsigned char child_index = *((unsigned char *)remaining_key);
        if (child_index == 0)
        {
            // We are at the end.
            goto key_end;
        }

        struct CharacterNode **next_child = &(current->children[child_index]);
        if (*next_child == NULL)
        {
            if (flags && BUILD)
            {
                // Add new child
                _CreateCharacterNode(next_child);
                (*next_child)->parent = current;
            }
            else
            {
                // No key entry
                goto no_key_entry;
            }
        }

        current = *next_child;
        remaining_key++;
    }

no_key_entry:
    (*ret) = NULL;
    goto end;
key_end:
    (*ret) = current;
    goto end;

end:
    return;
}

void DictionaryAdd(struct Dictionary *dictionary, char *key, char *value)
{
    struct CharacterNode *character_node = NULL;
    _DictionaryNavigate(dictionary, key, BUILD, &character_node);
    _CharacterNodeSetValue(character_node, value);
}

void DictionaryGet(struct Dictionary *dictionary, char *key, char **ret)
{
    struct CharacterNode *character_node = NULL;
    _DictionaryNavigate(dictionary, key, NONE, &character_node);
    if (character_node)
    {
        _CharacterNodeGetValue(character_node, ret);
    }
    else
    {
        (*ret) = NULL;
    }
}

void DictionaryRemove(struct Dictionary *dictionary, char *key, char **ret)
{
    struct CharacterNode *character_node = NULL;
    _DictionaryNavigate(dictionary, key, NONE, &character_node);
    if (ret != NULL && character_node)
    {
        _CharacterNodeGetValue(character_node, ret);
    }

again:
    if (character_node)
    {
        free(character_node->value);
        character_node->value = NULL;
        int has_child = 0;
        for (int i = 0; i < 256; i++)
        {
            if (character_node->children[i] != NULL)
            {
                has_child = 1;
                break;
            }
        }
        if (has_child == 0)
        {
            struct CharacterNode *parent = character_node->parent;
            struct CharacterNode **child_address = NULL;
            for (int i = 0; i < 256; i++)
            {
                if (parent->children[i] == character_node)
                {
                    child_address = &(parent->children[i]);
                }
            }
            _DestroyCharacterNode(child_address);
            character_node = parent;
            goto again;
        }
    }
}