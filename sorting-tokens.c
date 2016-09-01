#include <stdio.h>
#include <stdlib.h>
#include "sorting-tokens.h"
#include <string.h>




/*creates and initializes a node for given token*/
Node create_node(char *token){
   Node newToken = (Node)malloc(sizeof(struct Node));
   if(newToken == NULL){
      puts("ERROR: Node create_node(). memory allocation failed");
	  return NULL;
   }
   else{
      newToken->tokenName = token;
	  newToken->next = NULL;
   
   }
   return newToken;
}


/*create and initializes an empty tokenlist*/
Tokenlist create_tokenlist(){
    Tokenlist newList = (Tokenlist)malloc(sizeof(struct Tokenlist));
    if(newList == NULL){
	   puts("ERROR: Node create_tokenlist(). memory allocation failed");
	   return NULL;
	}
	else{
	   newList->root = NULL;
	   return newList;
	}
}


void add_to_list(Tokenlist list, char *token){
   
   if(list == NULL){                         
    puts("ERROR: void add_to_list(). list does not exist");
	return;
   }
   Node newToken = create_node(token);
   if(newToken == NULL){
      puts("ERROR: memory allocation failed");
	  return;
   }
   /*CASE 1: empty list*/
   if(list->root == NULL){
       list->root = newToken;
	   return;
   }
   /*CASE 2: insert token in beginning of non-empty list*/
   if( (strcmp(token, list->root->tokenName)) <0){           /*return -1 or <0 if p1< p2, this is the case for ex. p1: A  p2: B*/
       newToken->next = list->root;
	   list->root = newToken;
	   return;
   }
   /*CASE 3: insert token somewhere in the list*/
   Node prev = list->root; // points to first node in list
   Node current = prev->next; // points to second node in list
   
   while(current!=NULL){
      if((strcmp(token, current->tokenName)) <0){ // compares strings
	      newToken->next = current;
		  prev->next = newToken;
		  return;
	  }
	  prev = current;
	  current = current->next;
   }
  /*Case 4: newtoken is inserted at the end of list*/
  prev->next = newToken;  // end of list is reached and newToken is inserted
   return;
}


void DestroyTKL(Tokenlist list){
   if(list == NULL){
     return;
   }
   if(list->root == NULL){
       free(list);
	   return;
   }
   Node current = list->root;  //current points to first node in list
   Node temp = list->root->next; //  points to second node in list
   free(current);
   while(temp!=NULL){
      current = temp;     
      temp = temp->next;
	  free(current);
   }
   //freed all nodes in list. 
   free(list);
   
}


void print_tkl(Tokenlist list){
  if(list == NULL){
    puts("List does not exist");
  }
  else if(list->root == NULL){
    puts("List is empty");
  }
  else{
     Node current = list->root;
	 while(current!=NULL){
	    printf("%s => ", current->tokenName);
		current= current->next;
	 }
  
  }
  printf("\n");
  return;
}








