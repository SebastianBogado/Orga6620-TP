CFLAGS=-std=c99  -Wall
SOURCES=stoogesort.S strcmp.S sort.c parseManager.c
CSOURCES=stoogesort.c strcmp.S sort.c parseManager.c

all:
	$(CC) $(CFLAGS) main.c $(SOURCES) -o tp1
cdebug:
	$(CC) $(CFLAGS) -g main.c $(CSOURCES) -o tp1_c
debug:
	$(CC) $(CFLAGS) -g main.c $(SOURCES) -o tp1
gprof:
	$(CC) $(CFLAGS) -pg main.c $(SOURCES) -o tp1
clean:
	rm *.o tp1 tp1_c 
