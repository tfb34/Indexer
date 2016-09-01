#ifndef PATH_H
#define PATH_H
/* 
 *   path.h
 */
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.h"
#include "tokenizer.h"
#include "sorting-tokens.h"

/*used in main(). returns 1 if 'filename' is a regular file. Returns 0 if not*/
int is_file(const char *filename);

/*used in main(). returns 1 if 'dir' is a directory. Returns 0 otherwise */
int is_directory(const char *dir);

void index_file(HashTable h, Tokenlist t, const char *filename);

void index_dir(HashTable h, Tokenlist t, const char *dirname);

int write_file(HashTable h, Tokenlist t, FILE *f);








#endif