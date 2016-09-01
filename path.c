/*
 *  path.c
 */


#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "path.h"
#include "hash.h"
#include "tokenizer.h"
#include "sorting-tokens.h"


//returns positive number if filename is a regular file.Otherwise returns 0
int is_file(const char *filename){
  FILE *file = fopen(filename, "r");
  if(file){
    fclose(file);
	return 1;
  }
  else{
     return 0;
  }
}

//returns positive number if dir is a directory.Otherwise returns 0
int is_directory(const char *dir){
  DIR *directory = opendir(dir);
  if(directory){
    closedir(directory);
    return 1;
  }
  else{
  return 0;
  }
}

void index_file(HashTable h, Tokenlist t, const char *filename){
   // Open file to read
	FILE *file;
	file = fopen(filename, "r");
	if(!file){
	 printf("ERROR: Failed to open %s \n", filename);
	 return;
	}
	
	//Read in the file one line at a time
	
	
	
	char str[100];
	while(fgets(str, 100, file)){
	  TokenizerT *tokenizer = TKCreate(str);
	  char *token;
	  if(tokenizer){
	      while( (token=TKGetNextToken(tokenizer)) != NULL){
	       normalize(token);
		   //printf("%s\n",token);
		   //printf("*******************\n");
		   add_Token(h, t, token, (char *)filename);
	      }
		TKDestroy(tokenizer);
	   }
	   else{
	     puts("ERROR: allocating memory failure");
	   }
	   
	}
	fclose(file);
	
}






void index_dir(HashTable h, Tokenlist t, const char *dirname) {
    DIR *dir;
    struct dirent *dent;

    dir = opendir(dirname);
    if (!dir) {
        fprintf(stderr,
                "Failed to open directory '%s' for indexing.\n",
                dirname);
		
    }
    else {
       
        while ((dent = readdir(dir))) {
            size_t size = strlen(dent->d_name) + strlen(dirname) + 2;
            char *name = calloc(size, sizeof(char));      //need to initialize memory
            snprintf(name, size, "%s/%s", dirname, dent->d_name);

            if (strncmp(dent->d_name, ".", sizeof(char)) == 0) {
                // Hidden file
                continue;
            }
            else if (is_directory(name)) {
               
                index_dir(h, t, name);
            }
            else if(is_file(name)) {
              
                index_file(h, t, name);
            }
        }
        closedir(dir);
    }
}


int write_file(HashTable h, Tokenlist t, FILE *f){
    
	
	/*file is opened and ready to be written in*/
	
	if(t == NULL){
	  puts("There are no tokens");
	  return 1;
	}
	/*traverse the sorted list of tokens(or Node to be exact) and look each one up in the hashtable */
	Node token = t->root; //points to first token in Tokenlist t
	int counter;
    while(token != NULL){ // for each token print at most the top 5 files it appears in 
	    /*find token in hashtable*/
	     Token hashedtoken =  find_Token(h, token->tokenName); //finds the "address" of the given token 
		 Item current = hashedtoken->root;   //current points to the first item in list. type item has filename and frequency data
		 if(current == NULL){
		    puts("ERROR: write_file() item cannot be found");
			return 1;
		 }
		  
          counter = 0;
		 fprintf(f, "<list> %s\n", token->tokenName);
		 while(current!=NULL){  
		     if(counter == 5){
			    fprintf(f, "\n");
				counter = 0;
			 }
		     fprintf(f, " %s %d", current->fileName, current->frequency);
			 current =current->next;
			 counter++;
		 }
		 fprintf(f, "\n</list>\n");
		 token = token->next;
	}
	fclose(f);
	return 0;
}


