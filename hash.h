#ifndef HASH_H
#define HASH_H
/* 
 *   hash.h
 */
#include <stdlib.h>
#include <string.h>
#include "sorting-tokens.h"

#define HASH_SIZE 100

/*linked lists for separate chaining */
struct Item{
   char *fileName;
   int frequency;
   struct Item *next;
   struct Item *prev;
};
typedef struct Item* Item;



struct Token{
    char *token;         
	struct Item *root;   //root points to first item in list ..Token->root
	struct Token *next;

};
typedef struct Token* Token;

struct HashTable{
  Token table[HASH_SIZE];
  
};
typedef struct HashTable* HashTable;


HashTable create_HT();
Item create_Item(char *file); 
Token create_Token(char *tokenName);
int hash(char *key);


void connect_items(Item current, Item newToken);



/*Used to insert an item in a double linked list. 
Parameters: the hashtable, a valid index, and the item we need to insert in the list*/
void Insert( Token token, Item newToken);

/*Used find a particular file in a given list */
Item find(Item root, char *file);

Token find_Token(HashTable h, char *token);



//delete()
void remove_item(Token token, Item rmFile); //ITem root later on will be switched to Token root// we need h->table[key];



//update(Item t);

//void update(Item t)


  

/*Used to print a given hashtable*/
//void print_table(HashTable h);


/*frees a list of Items*/
void free_items(Item root);

void Update(Token currentToken, Item currentItem );



void add_Token(HashTable h, Tokenlist t, char *token, char *filename);// might change it to int instead of void




void print_table(HashTable h);








#endif