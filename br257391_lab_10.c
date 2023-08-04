#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
typedef struct TrieNode 
{
    struct TrieNode *children[26];
    int cntr;
} TrieNode;

// Trie structure
typedef struct Trie 
{
    TrieNode *root;
} Trie;

// Creates a new Trie node
TrieNode *createTrieNode()
{
    TrieNode *nd = (TrieNode *)malloc(sizeof(TrieNode));
    if (nd)
    {
        nd->cntr = 0;
        for (int i = 0; i < 26; i++)
        {
            nd->children[i] = NULL;
        }
    }
    return nd;
}

// Initializes a trie structure
Trie *createTrie()
{
    Trie *pTrie = (Trie *)malloc(sizeof(Trie));
    if (pTrie != NULL)
    {
        pTrie->root = createTrieNode();
    }
    return pTrie;
}

// Inserts the word to the trie structure
void insert(Trie *pTrie, char *word)
{
    TrieNode *curr = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int place = word[i] - 'a';
        if (curr->children[place] == NULL)
        {
            curr->children[place] = createTrieNode();
        }
        curr = curr->children[place];
    }

    curr->cntr += 1;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(Trie *pTrie, char *word)
{
    TrieNode *curr = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int place = word[i] - 'a';
        if (curr->children[place] == NULL)
        {
            return 0;
        }
        curr = curr->children[place];
    }
    return curr->cntr;
}

// Deallocates the trie nodes
void deallocateTrieNodes(TrieNode *node)
{
    if (node)
    {
        for (int i = 0; i < 26; i++)
        {
            deallocateTrieNodes(node->children[i]);
        }
        free(node);
    }
}

// Deallocate the trie structure
void deallocateTrie(Trie *pTrie)
{
    if (pTrie != NULL)
    {
        if (pTrie->root != NULL)
        {
            deallocateTrieNodes(pTrie->root);
        }
        free(pTrie);
    }
}

// Function to read dictionary and return number of words
int readDictionary(char *filename, char **pInWords)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        exit(1);
    }

    int num = 0;
    char word[256];
    while (fscanf(f, "%s", word) != EOF)
    {
        pInWords[num] = strdup(word);
        num += 1;
    }
    fclose(f);
    return num;
}

int main(void)
{
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // Parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    deallocateTrie(pTrie);

    // Deallocate memory for input words
    for (int i = 0; i < numWords; ++i)
    {
        free(inWords[i]);
    }

    return 0;
}
