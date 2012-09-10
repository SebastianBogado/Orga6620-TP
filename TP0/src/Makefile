# Ale, agregá los fuentes o targets que necesites

CFLAGS=-std=c99 -Werror -Wall
SOURCES=stoogesort.c quicksort.c sort.c

all:
	$(CC) $(CFLAGS) main.c $(SOURCES) -o tp0
test:
	$(CC) $(CFLAGS) test.c $(SOURCES) -o test
clean:
	rm *.o tp0 test
