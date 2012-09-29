CFLAGS=-std=c99 -Werror -Wall
SOURCES=stoogesort.c quicksort.c sort.c parseManager.c

all:
	$(CC) $(CFLAGS) main.c $(SOURCES) -o tp0
debug:
	$(CC) $(CFLAGS) -g main.c $(SOURCES) -o tp0
asm:
	$(CC) $(CFLAGS) -S main.c $(SOURCES)	
gprof:
	$(CC) $(CFLAGS) -pg main.c $(SOURCES) -o tp0
clean:
	rm *.s *.o tp0 test
