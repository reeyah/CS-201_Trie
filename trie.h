#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ========== DECLARATIONS ==========

// ---------- some constants ----------

#define NUMBER_OF_CHILDREN 26

// ---------- miscellenious ----------

char **allocate_str_array(int sz, int n);
void deallocate_str_array(char** s, int n);
void print_str_array(char** s, int n);

// ---------- Types ----------

typedef struct _Node Node;
typedef Node* NodePtr;
typedef struct _Trie Trie;

// ---------- Functions regarding NodePtr ----------

NodePtr initNodePtr();  // #
void deleteNodePtr(NodePtr root);   // #
int node_insert(NodePtr root, const char *str); // #
NodePtr move_upto(NodePtr root, const char *str);   // #
int get_str(NodePtr head, char str[], int index, char **s, int upto, int first);    // #

// ---------- Functions regarding Trie ----------

Trie initTrie();    // #
void deleteTrie(Trie *self);    // #
void insert(Trie *self, const char *str);   // #
void insert_strings(Trie *self, char **ss, int n);  // #
int search(Trie *self, const char *str);    // #
void remove_str(Trie *self, const char *str);   // #
int count(Trie *self);  // #
void print_trie(Trie *self);    // #
char **get_upto(Trie *self, int sz);    // #
char **get_all(Trie *self); // #
int prefix_search(Trie *self, const char *str); // #
void clear(Trie *self); // #
void trie_copy(Trie *dest, Trie *src);  // #
char **sort_strings(char **s, int n);   // #

// ========== DEFINITIONS ==========

// ---------- miscellenious ----------

// returns char ** 
// each string of size sz
// and number of string is n
char **allocate_str_array(int sz, int n)
{
    char** strings = (char**)calloc(n, sizeof(char*));
    for (int i=0; i<n; i++)
        strings[i] = (char*)calloc(sz, sizeof(char));
    return strings;
}

// deallocate a given string array of size n
void deallocate_str_array(char** s, int n)
{
    for (int i=0; i<n; i++)
        free(s[i]);
    free(s);
}

// print the given string array
void print_str_array(char** s, int n)
{
    for (int i=0; i<n; i++)
    {
        if (s[i][0] == 0)
            continue;
        printf("%s\n", s[i]);
    }
}

// ---------- Types ----------

struct _Node
{
    struct _Node *child[NUMBER_OF_CHILDREN];
    int is_leaf;
};

struct _Trie
{
    NodePtr root;   // root pointer
    int nos;        // nos -> number of string in this trie
    int slw;        // slw -> size of the longest word
};

// ---------- Functions regarding NodePtr ----------

// initializes or returns allocated NodePtr 
NodePtr initNodePtr()
{
    NodePtr node = (NodePtr)calloc(1, sizeof(Node));    // calloc initializes every memory block with 0
    return node;
}

// delete all nodes from here
void deleteNodePtr(NodePtr root)
{
    if (root == NULL)
        return;
    for (int i=0; i<NUMBER_OF_CHILDREN; i++)
        deleteNodePtr(root->child[i]);
    free(root);
}

// insert the given string from taking root as the starting pointer
// returns the length of the inserted string
int node_insert(NodePtr root, const char *str)
{
    int i = 0;
    for (i=0; str[i]; i++)
    {
        if (root->child[str[i] - 'a'] == NULL)
            root->child[str[i] - 'a'] = initNodePtr();
        root = root->child[str[i] - 'a'];
    }
    if (root->is_leaf == 1)
        return 0;           // i.e. the string was already present
    root->is_leaf = 1;
    return i;
}

// move upto a given string 
// i.e. lets say we have a root and a string is given "abc"
// now root will move in such a way that the root is the same pointer as "c"
// returns NULL if that string doesnot exist
NodePtr move_upto(NodePtr root, const char *str)
{
    for (int i=0; str[i]; i++)
    {
        if (root->child[str[i] - 'a'])
            root = root->child[str[i] - 'a'];
        else
            return NULL;
    }
    return root;
}

// here str is used for temporary memory for string 
// here all the strings are stored in s
// "first" checks if the functions is called for first time
// returns the number of strings
int get_str(NodePtr head, char str[], int index, char **s, int upto, int first)
{
    static int NOW = 0;
    if (first)
        NOW = 0;
    if (head == NULL)
        return 0;
    if (head->is_leaf)
    {
        str[index] = '\0';
        strcpy(s[NOW++], str);
        if (upto == NOW)
            return NOW;
    }
    for (int i=0; i < NUMBER_OF_CHILDREN; i++)
    {
        if (head->child[i])
        {
            if (upto == NOW)
                return NOW;
            str[index] = i + 'a';
            get_str(head->child[i], str, index + 1, s, upto, 0);
        }
    }
    return NOW;
}

// ---------- Functions regarding Trie ----------

Trie initTrie()
{
    Trie t;
    t.root = initNodePtr();
    t.nos = t.slw = 0;
    return t;
}

// delete the whole Trie
void deleteTrie(Trie *self)
{
    deleteNodePtr(self->root);
    self->root = NULL;
    self->nos = 0;
    self->slw = 0;
}

// insert the given string into the trie
void insert(Trie *self, const char *str)
{
    if (self->root == NULL)
        *self = initTrie();
    int len = node_insert(self->root, str);
    if (len == 0)   // i.e. this string was already present
        return;
    self->nos += 1;     // increase the number of strings stored in trie by 1
    self->slw = (len > self->slw) ? len: self->slw; // if len > slw, slw = len
}

// insert string array into Trie
void insert_strings(Trie *self, char **ss, int n)
{
    for (int i=0; i<n; i++)
        insert(self, ss[i]);
}

// print all the strings present in this trie
void print_trie(Trie *self)
{
    char **strings = get_all(self);
    printf("The strings in this trie are:\n[");
    for (int i=0; i<self->nos; i++)
    {
        printf("%s", strings[i]);
        if ((self->nos - 1) == i)
            break;
        printf(" ");
    }
    printf("]\n");
    deallocate_str_array(strings, self->nos);
}

// search for a given string in the trie
// if found return 1, else return 0
int search(Trie *self, const char *str)
{
    if (str == NULL || str[0] == 0)
        return 0;
    NodePtr ptr = move_upto(self->root, str);
    if (ptr == NULL)
        return 0;
    return ptr->is_leaf;
}

// remove a given string from the given trie
void remove_str(Trie *self, const char *str)
{
    if (str == NULL || str[0] == 0)
        return;
    NodePtr ptr = move_upto(self->root, str);
    if (ptr == NULL)
        return;
    if (ptr->is_leaf)
    {
        ptr->is_leaf = 0;   
        self->nos -= 1;     // decrease the number of string by one
    }
}

// returns the number of string in the trie
int count(Trie *self)
{
    return self->nos;
}

// get string array of size sz, in lexicographically acending order.
char **get_upto(Trie *self, int sz)
{
    char s[self->slw + 1];
    char **ss = allocate_str_array(self->slw + 1, count(self));
    get_str(self->root, s, 0, ss, sz, 1);
    return ss;
}

// get all the strings in the trie
char **get_all(Trie *self)
{
    return get_upto(self, count(self));
}

// this function is only used for prefix search
int _only_for_prefix_search(NodePtr root)
{
    if (root == NULL)
        return 0;
    if (root->is_leaf == 1)
        return 1;
    int val;
    for (int i=0; i<NUMBER_OF_CHILDREN; i++)
    {
        val = _only_for_prefix_search(root->child[i]);
        if (val == 1)
            return 1;
    }
    return 0;
}
// checks if there is any string in the trie whose prefix is the given string
// returns 1 if found, else 0
int prefix_search(Trie *self, const char *str)
{
    if (str == NULL || str[0] == 0)
        return 1;
    NodePtr ptr = move_upto(self->root, str);
    return _only_for_prefix_search(ptr);
}

// get array of string whose prefix is the given string
// n signifies the number of array required
char **autocomplete(Trie *self, const char *str, int n)
{
    if (str == NULL || str[0] == 0)
        return get_upto(self, n);

    NodePtr ptr = move_upto(self->root, str);
    char s[self->slw + 1];
    strcpy(s, str);
    char **ss = allocate_str_array(self->slw + 1, n);
    get_str(ptr, s, strlen(str), ss, n, 1);
    return ss;
}

// used only for clearing
void _only_for_clear(NodePtr root)
{
    if (root == NULL)
        return;
    for (int i=0; i<NUMBER_OF_CHILDREN; i++)
    {
        _only_for_clear(root->child[i]);
    }
    root->is_leaf = 0;
}
// clear all the nodes
void clear(Trie *self)
{
    _only_for_clear(self->root);
    self->nos = self->slw = 0;
}

// copy a trie from a source trie
void trie_copy(Trie *dest, Trie *src)
{
    clear(dest);
    char **ss = get_all(src);
    insert_strings(dest, ss, src->nos);
}

// sort the given string in lexicographically acending order
char **sort_strings(char *ss[], int n)
{
    Trie t = initTrie();
    insert_strings(&t, ss, n);
    char **sorted = get_all(&t);
    return sorted;
}

#endif