#include <stdio.h>
#include <stdlib.h>
#include"phonebook.h"

struct TrieNode *getNode()  //makes new node
{
    struct TrieNode *pNode = NULL;
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (pNode)
    {
        int i;
        pNode->isEndOfWord = false; //confirms initialised to null
        for (i = 0; i < ALPHABET_SIZE; i++)
           { pNode->children[i] = NULL;
           }
    }

    return pNode;
}

bool isLeafNode(struct TrieNode* root)
{
    return root->isEndOfWord != false;
}

void loadtofile(int key)     //insert
{
 FILE *fp;
 fp=fopen("storage.txt","a+");
 if(fp==NULL)
 {
  printf("Can't create file");
  return;
 }
 fwrite(&list[key],sizeof(struct contact),1,fp);
 fclose(fp);
}

void loadfromfile(struct TrieNode *root)  //search
{
 FILE *f;
 f=fopen("storage.txt","r");
 if(f==NULL)
 {
  printf("Can't read file");
  return;
 }
 fseek(f, 0, SEEK_SET);
 while(fread(&l,sizeof(struct contact),1,f))
 {
  insert(root,l.name);
 }
 fclose(f);
}
void sfull(char ar[])
{
 FILE *q;
 q=fopen("storage.txt","r");
 if(q==NULL)
 {
  printf("Can't read file");
  return;
 }
 fseek(q, 0, SEEK_SET);
 while(fread(&l,sizeof(struct contact),1,q))
 {
  if(strcmp(l.name,ar)==0)
  {
   printf("\nName: %s",l.name);
   printf("\nPhone number 1: %d",l.phno1);
   printf("\nPhone number 2:%d",l.phno2);
   printf("\nDiscription: %s",l.disp);
 }
}
 fclose(q);
}
void display(struct TrieNode* root, char str[], int level)
{
     int i;

    if (isLeafNode(root))
    {
        str[level] = '\0';
        printf("\n%s",str);
    }


    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            display(root->children[i], str, level + 1);
        }
    }
}
void insert(struct TrieNode *root, char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }


    pCrawl->isEndOfWord = true;
}


void displayContactsUtil(struct TrieNode *curNode, char suffix[])
{

   for (char i = 'a'; i <= 'z'; i++)
    {
        struct TrieNode *nextNode = curNode->children[i];
        if (nextNode != NULL)
            displayContactsUtil(nextNode, suffix + (char)i);
    }


    if(curNode->isEndOfWord)
        printf("\n%s",suffix);
}

void disp(struct TrieNode *root,char str[])
{
 int i;
 char* suffix="";
 struct TrieNode *prevNode = root;
 struct TrieNode *sub;
 int len,index;
 len=strlen(str);
 printf("%s",str);
// TrieNode *curNode = prevNode->child[];
  for(i=0;i<len;i++)
  {
   index = CHAR_TO_INDEX(str[i]);
   sub=prevNode->children[index] ;
   suffix += (char)str[i];
   printf("%s",suffix);
   prevNode=sub;
  }
  printf("%s",suffix);
  displayContactsUtil(prevNode,suffix);
}
// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}
int haveChildren(struct TrieNode* curr)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (curr->children[i])
			return 1;

	return 0;
}

int deletion(struct TrieNode **curr, char* str)
{

	if (*curr == NULL)
		return 0;


	if (*str)
	{

		if (*curr != NULL && (*curr)->children[*str - 'a'] != NULL &&
			deletion(&((*curr)->children[*str - 'a']), str + 1) &&
			(*curr)->isEndOfWord == 0)
		{
			if (!haveChildren(*curr))
			{
				free(*curr);
				(*curr) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}


	if (*str == '\0' && (*curr)->isEndOfWord)
	{

		if (!haveChildren(*curr))
		{
			free(*curr); // delete current node
			(*curr) = NULL;
			return 1; // delete non-leaf parent nodes
		}


		else
		{
			(*curr)->isEndOfWord= 0;
			return 0;
	}
	}
		//del(str);

	return 0;
}
