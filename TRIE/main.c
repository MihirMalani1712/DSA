#include<stdio.h>
#include<stdlib.h>
#include "phonebook.c"



int main()
{
 struct TrieNode *root = getNode();
 char opt,str[20];
 int ch,scr,level=0;
 char word[20],dscr[20],scrword[20],delword[20];
 char output[][32] = {"Not present in trie", "Present in trie"};
 bool result;
 do
 {
  printf("\n\t\t\t\t\t--------------------------------------------------------------------------------------------------------------------------");
  printf("\n\t\t\t\t\t*                                                                                                                        *");
  printf("\n\t\t\t\t\t******************************************WELCOME TO PHONEBOOK DIRECTORY**************************************************");;
  printf("\n\t\t\t\t\t*                                                                                                                        *");
  printf("\n\t\t\t\t\t--------------------------------------------------------------------------------------------------------------------------");
  printf("\n\n1. Add a contact \n2. Search for a contact \n3. Delete a contact \n4. Display contacts\n5. Display contacts until\n6. Exit \n\nEnter your choice: ");
  scanf("%d",&ch);
  switch(ch)
  {
    case 1:

printf("\n**************************************************************************");
                  printf("\nEnter the name to be inserted: ");
                  scanf("%s",word);
                  strcpy(list[key].name,word);
printf("\n**************************************************************************");
		  printf("\nEnter Phone number 1:");
                  scanf("%d",&list[key].phno1);
		  printf("\nDo you want to add another phone number?");
		  scanf("\n%c",&opt);
		  if(opt=='Y' || opt=='y')
                  {
		   printf("\nEnter Phone number 2:");
                   scanf("%d",&list[key].phno2);
		  }
printf("\n**************************************************************************");
		  printf("\nEnter discription");
		  scanf("%s",list[key].disp);
                  loadtofile(key);
printf("\n**************************************************************************");
                  printf("\nInsertion successful!\n");
printf("\n**************************************************************************");
		  key++;
                  break;
    case 2:
                 loadfromfile(root);
printf("\n**************************************************************************");
                 printf("\nEnter the name to be searched: ");
		 scanf("%s",scrword);
printf("\n**************************************************************************");
		 result=search(root,scrword);
                 printf("\n%s",output[result]);
		 if(result)
		 sfull(scrword);
printf("\n**************************************************************************");
                 break;
   case 3:
printf("\n**************************************************************************");
		  printf("\nEnter the name to be deleted: ");
		  scanf("%s",delword);
printf("\n**************************************************************************");
		  if (&root == NULL)
		   printf("Trie empty!!\n");
printf("\n**************************************************************************");
		  deletion(&root,delword);
		  printf("\nContact deleted");
                  break;
  case 4:
		  level=0;
		  loadfromfile(root);
printf("\n**************************************************************************");
		  printf("\nTotal contacts : %d",key);
		  display(root,str,level);
printf("\n**************************************************************************");
		  break;
  case 5:
printf("\n**************************************************************************");
		  printf("\nEnter name to search");
		  scanf("%s",dscr);
printf("\n**************************************************************************");
 		  disp(root, dscr);
		  break;
  case 6:
		  break;

 default:
		  printf("\nInvalid choice");
  }
}
 while(ch!=6);
return 0;
}
