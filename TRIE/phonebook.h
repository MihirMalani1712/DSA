#ifndef PHONEBOOK_H_INCLUDED
#define PHONEBOOK_H_INCLUDED
#include <string.h>
#include <stdbool.h>

struct contact

{
 int phno1;
 int phno2;
 char name[20];
 char disp[100];
};

struct contact c;
struct contact l;
int key=0;
int chk=0;

struct contact list[100];
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

struct TrieNode *getNode();
bool isLeafNode(struct TrieNode* root);
void loadtofile(int key);
void loadfromfile(struct TrieNode *root);
void sfull(char ar[]);
void display(struct TrieNode* root, char str[], int level);
void insert(struct TrieNode *root, char *key);
void displayContactsUtil(struct TrieNode *curNode, char suffix[]);
void disp(struct TrieNode *root,char str[]);
bool search(struct TrieNode *root, const char *key);
int haveChildren(struct TrieNode* curr);
int deletion(struct TrieNode **curr, char* str);



#endif // PHONEBOOK_H_INCLUDED
