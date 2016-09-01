/* 
 *hash.c
 */
 
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include "hash.h"
 #include "sorting-tokens.h"
 
 #define HASH_SIZE 100
 
 
 HashTable create_HT(){   /* 1 */
    HashTable h = (HashTable)malloc(sizeof(struct HashTable));
	if(h == NULL){
	  puts("Error: malloc not successful");
	  return NULL;
	}
	
	int index;
	for(index = 0; index < HASH_SIZE; index++){
	     h->table[index]=NULL;
	}
	
    
    return h;
 }
 
 Item create_Item(char *file){  /* 2 */
      
	  Item newItem = (Item)malloc((sizeof(struct Item)));
	  if(newItem == NULL){
	    puts("Error: malloc not successful");
		return NULL;
	  }
	  
	  newItem->fileName = file;
	  newItem->frequency = 1;
	  newItem->prev = NULL;
	  newItem->next = NULL;
	  
	  return newItem;
}  

Token create_Token(char *tokenName){
  Token t = (Token)malloc(sizeof( struct Token));
  if( t == NULL){
    puts("ERROR: malloc not successful");
	return NULL;
  }
  t->token = tokenName;
  t->root = NULL;
  t->next = NULL;
  
  return t;
}


 int hash(char *key){  /* 3 */
      int index=0;
      int i;
      for(i=0; i< strlen(key); i++){
        index=index + (int)key[i];//add the decimal value of each character in key 
      }
      index=index%HASH_SIZE;   //for now the size of the hash table is 10
 
      return index;
}

/*adds 'newToken' in before 'current' item*/
void connect_items(Item current, Item newToken){

 Item beforeCurrent = current->prev;
 beforeCurrent->next = newToken;
 newToken->prev = beforeCurrent;
 current->prev = newToken;
 newToken->next = current;
 
 return;
 
}

/*an item that is given to insert should not be in the list */
void Insert( Token token , Item newToken){// could pass root instead of key and hashtable
   
   if(newToken == NULL || token == NULL){
       puts("ERROR: Given list or item you are trying to insert does not exist");
	   return;
   }
   
  /* CASE 1: add newToken to empty list */
   if(token->root == NULL){
      token->root = newToken;                                         // add newToken to list beginning of list
	  //printf("token was added to empty list\n");
	  return;
   }
   /* case 2: list is NOT empty but since newToken has >= frequency than first item in list we need to add newToken to front of list*/
   Item current = token->root;
   if( current->frequency <= newToken->frequency){                   /* newToken is added to front of list if it has a >= frequency */
         token->root = newToken;
		 newToken->next = current;
		 current->prev = newToken;
		 return;
   }
  /*CASE 3: traverse list until spot is found*/
                         /* since root is > newToken's frequency we check the next item in list*/
   
   
   while( current->next!=NULL){
	  
      if(current->frequency <= newToken->frequency ){      /* if true then add newToken before current*/
	      connect_items(current, newToken);
		 /*insertion complete */
		  return;
	    }
        
	current = current->next;
   }
   if(current->frequency <= newToken->frequency ){      /* if true then add newToken before current*/
          connect_items(current, newToken);
         /*insertion complete */
    }
   else{
    /* CASE 4: we are at end of list so add newToken to the end */
      current->next = newToken;
	  newToken->prev = current;
    }
	
	
return;

}
   
   
   
 /*finding an 'item' by comparing file names */
Item find(Item root, char *file){
    
if(root == NULL){
  puts("ERROR:find(Item root, char *file). root==NULL , empty list");
  return NULL;
}

Item current=root;

while(current!=NULL){
    if(strcmp(current->fileName,file) ==  0){        //current->fileName == file
    return current;
    }
current = current->next;
}

return NULL;

}
/*Parameters: name of token and hashtable  RETURNS: type Token*/
Token find_Token(HashTable h, char *token){
  int key = hash(token);
  if(h->table[key] == NULL){
      return NULL;
  }
  
  Token current = h->table[key];
  while(current!=NULL){
     if(strcmp(current->token, token) ==  0){   //current->token == token
	    return current;
	 }
	 current = current->next;
  
  }
  return NULL;

}

void remove_item(Token token, Item rmFile){
Item current = token->root;
  if(current == NULL){
     puts("ERROR: hash.c 182 remove_item(). list is empty");
	 return;
  }
  
  if(strcmp(current->fileName, rmFile->fileName) ==  0){   /*CASE 1: remove in the beginning of list of items  */       //current->fileName == rmFile->fileName
       token->root = current->next;
	   if(token->root != NULL){
	       Item temp = token->root;
		   temp->prev = NULL;
		   current->next = NULL;
	   }
	   
  }
  else{
   current = current->next;                /*CASE 2: traverse list*/
  while(current!=NULL){
       if(strcmp(current->fileName, rmFile->fileName) ==  0){ 
	       Item temp = current->prev;
		   temp->next = current->next;
		   current->prev = NULL;
		   if(current->next != NULL){
		       Item n =current->next;
			   n->prev = temp;
			   current->next = NULL;
		   }
		   return;
	   }
	   current = current->next;
  
    }                                           /*CASE 3: 'rmFile' does not exist in list*/
 
 }
  
  return;                                   
}









/*Given an item list, it will traverse the list and free each item*/
void free_items(Item root){ 
Item head = root;
Item temp;
while( head!=NULL){
   temp =  head;
   head = head->next;
   free(temp);
   puts("freed");
 }
 root = NULL;
 puts("list is empty");
  return;
}


void Update(Token currentToken, Item currentItem){

    currentItem->frequency +=1;       //increment frequency
	remove_item(currentToken, currentItem);
	
	Insert(currentToken, currentItem);
	

}



void add_Token(HashTable h, Tokenlist t, char *token, char *filename){//perhaps used by hidden function not in main
   int index = hash(token);
   
 if(h->table[index] == NULL){                                /* CASE 1:  no Tokens exist  */
       Token newToken = create_Token(token);                 // when a new token is created add to tokenlist
	   add_to_list(t, token);
       Item newItem = create_Item(filename);                    /* create a token and a new Item */
	   
	   newToken->root = newItem;                               /*newItem is added to newToken's list(or double linked list) of items */
	   h->table[index] = newToken;                             /*we add newToken and its item to the HashTable*/                  
	   return;
   }
 else{                                                      /*there is a list of tokens*/     
    Token currentToken = find_Token(h, token);             /*traverses list of Tokens and looks for 'token'*/   
            if(currentToken == NULL){                                /*CASE 2: 'token' does not exist so we need to create a token, an item, and attach token to the front of list*/
		       Token newToken = create_Token(token);
			   add_to_list(t, token);
		       Item newItem = create_Item(filename);
		   
		       newToken->root = newItem;                          /*add item to newToken's list*/
		       newToken->next = h->table[index];                   /*add 'token' to front of token list*/
		       h->table[index] = newToken;                         /*add 'token' to hashtable*/
		       return;
		    }
		
	Item currentItem = find(currentToken->root, filename);
	        if(currentItem  == NULL){                                //'filename' does not exist so create a new Item and insert 
                Item newItem = create_Item(filename);
				Insert(currentToken, newItem);
            }
			else{
			    Update(currentToken, currentItem);                        /*update() increments an Item's frequency and calls remove_item() and Insert(); */
			
			}
		
    }
 return;	
} 






void print_table(HashTable h){
int index;
Token t;
Item current;
for(index=0; index<HASH_SIZE; index++){
   t= h->table[index];
   if(t==NULL){
   puts("NULL");
   }
   if(t!=NULL){
      puts("Key: ");
   }
   while(t!=NULL){
      printf("   Token %s      ", t->token);
	  if(t->root == NULL){
	   puts("ERROR: token was mapped but not its item");
	  }
	  else{
      current = t->root;
	  while(current!=NULL){
	     printf("(%s, %d)  =>  ", current->fileName, current->frequency );
		 current=current->next;
	  }
	  t=t->next;
	  printf("\n");
	  }
   }

}

}






