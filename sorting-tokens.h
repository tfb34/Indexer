#ifndef  SORTINGTOKENS_H
#define SORTINGTOKENS_H
/* 
 *   sorting-tokens.h
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node{
   char *tokenName;
   struct Node *next;
};
typedef struct Node* Node;

struct Tokenlist{
   Node root;

};
typedef struct Tokenlist* Tokenlist;


Node create_node(char *token);
Tokenlist create_tokenlist();
void add_to_list(Tokenlist list, char *token);
void DestroyTKL(Tokenlist list);
void print_tkl(Tokenlist list);










#endif