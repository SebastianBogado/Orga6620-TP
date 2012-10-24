CFLAGS=-std=c99 -Werror -Wall
SOURCES=stoogesort.c sort.c parseManager.c

all:
	$(CC) $(CFLAGS) main.c $(SOURCES) -o tp1
debug:
	$(CC) $(CFLAGS) -g main.c $(SOURCES) -o tp1
asm:
	$(CC) $(CFLAGS) -S main.c $(SOURCES)	
gprof:
	$(CC) $(CFLAGS) -pg main.c $(SOURCES) -o tp1
test:
	$(CC) $(CFLAGS) strcmp.S strcmpTest.c -o strcmpTest
clean:
	rm *.s *.o tp1 
