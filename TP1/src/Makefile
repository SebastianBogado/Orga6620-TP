CFLAGS=-std=c99  -Wall
SOURCES=stoogesort.S strcmp.S sort.c parseManager.c
CSOURCES=stoogesort.c strcmp.S sort.c parseManager.c

all:
	$(CC) $(CFLAGS) main.c $(SOURCES) -o tp1
cdebug:
	$(CC) $(CFLAGS) -g main.c $(CSOURCES) -o tp1_c
debug:
	$(CC) $(CFLAGS) -g main.c $(SOURCES) -o tp1
asm:
	$(CC) $(CFLAGS) -S main.c $(SOURCES)	
gprof:
	$(CC) $(CFLAGS) -pg main.c $(SOURCES) -o tp1
test:
	$(CC) $(CFLAGS) -g strcmp.S strcmpTest.c -o strcmpTest
clean:
	rm *.o tp1 
