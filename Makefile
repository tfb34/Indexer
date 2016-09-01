#declare the variables CC and CFLAGS
#call the variables with format  $(variable)
CC=gcc
CFLAGS= -g -Wall
 
all: index

index: indexer.o tokenizer.o path.o sorting-tokens.o hash.o
	$(CC) $(CFLAGS) -o index indexer.o tokenizer.o path.o sorting-tokens.o hash.o

indexer.o:  
	$(CC) $(CFLAGS) -c indexer.c 

tokenizer.o:
	$(CC) $(CFLAGS) -c tokenizer.c

path.o: 
	$(CC) $(CFLAGS) -c path.c

sorting-tokens.o: 
	$(CC) $(CFLAGS) -c sorting-tokens.c

hash.o:
	$(CC) $(CFLAGS) -c hash.c

clean:
	rm -rf *.o index
