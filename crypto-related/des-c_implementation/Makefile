CFLAGS += -std=c99 


.PHONY: all

all: DES

DES: DESKeyGen.o DESengine.o
	$(CC) $^ -o DES -lm -ggdb3

DESengine.o: DESengine.c
	$(CC) -c $^ -o DESengine.o -ggdb3 

DESKeyGen.o: DESKeyGen.c
	$(CC) -c  $^ -o DESKeyGen.o -ggdb3

clean: 
	rm -f *.o
	rm -f DES
