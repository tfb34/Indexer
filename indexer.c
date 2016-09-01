#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>  /* Many POSIX functions (but not all, by a large margin) */
#include <fcntl.h>   /* open(), creat() - and fcntl() */
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.h"
#include "tokenizer.h"
#include "path.h"
#include "sorting-tokens.h"

int main (int argc , char **argv)
{
    if(argc!=3){
	   puts("Invalid number of arguments.");
	   return 1;
	}
	
	// the indexed file and file/directory can't be the same
    if (strcmp(argv[1], argv[2]) == 0) {
        printf("Index file: %s and file/directory: %s cannot be the same\n", argv[1], argv[2]);
        return 1;
    }
	//Testing for the Existence of <inverted-index file name>
	int result = access(argv[1], F_OK);
	 if (result != -1) {
        fprintf(stderr, "ERROR:  index file '%s' already exists\n", argv[1]);
        return 1;
    }
	
	  // Open the index file for writing
	  FILE *indexfile;
    indexfile = fopen(argv[1], "w");
    if (!indexfile) {
        fprintf(stderr,"ERROR: failed to open index file '%s' for writing\n",argv[1]);
        return 1;
    }
	
	HashTable h = create_HT();
	Tokenlist t = create_tokenlist();
	
	if(is_directory(argv[2]) == 1){
	    index_dir(h, t, argv[2]);
	}
    else if(is_file(argv[2]) == 1){
	   index_file(h, t, argv[2]);
	}
	else{
	    fprintf(stderr,"ERROR: '%s' is not a regular file or directory\n ",argv[2]);
        return 1;
	}
	
   /* write to file */
   if( (write_file( h,  t, indexfile)) == 0){
        printf("%s was successfully written to. \n", argv[1]);
   }
   else{
       printf("%s was NOT successfully written to. \n", argv[1]);
   }
	
  return 0;
}