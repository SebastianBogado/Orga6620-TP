#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define EMPTY 0
#define SHARK 1
#define FISH  2

struct animal {
	char kind;     /* SHARK o FISH */
	unsigned char age;      /* Edad del animal. */
	unsigned char hunger;   /* Turnos que lleva sin comer un tiburón */
	char todo;     /* ? */
}animal;

#define MAXI 32
#define MAXJ 32
int HBRUT, FBRUT, FASTEN;

struct animal wator[MAXI][MAXJ] ;

#define REST -1
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

int ni (int i, int dir)
{
	switch (dir) {
	case NORTH:
		return (i+MAXI-1) % MAXI;
	case SOUTH:
		return (i+1) % MAXI;
	case EAST:
	case WEST:
		return i;
	default:
		assert (0);
	}
	return -1;
}

int nj (int j, int dir)
{
	switch (dir) {
	case NORTH:
	case SOUTH:
		return j;
	case EAST:
		return (j+MAXJ-1) % MAXJ;
	case WEST:
		return (j+1) % MAXJ;
	default:
		assert (0);
	}
	return -1;
}

int newcount = 0;

void new_animal (int i, int j, char kind)
{
	struct animal *t = & wator[i][j] ;
	assert (wator[i][j].kind == EMPTY);
	assert ((kind == FISH) || (kind == SHARK));
	t->kind = kind;
	t->age = 0;
	t->hunger = 0;
	t->todo = 0;
	newcount++;
}

int myrand (int max)
{
	return rand () % max;
}

int choose_fish (int i, int j)
{
	int k = 0;
	int dir;
	int dirs[4];
	for (dir=0; dir < 4; dir++) {
		int npi = ni (i, dir);
		int npj = nj (j, dir);
		struct animal * t = &wator[npi][npj];
		if  (t->kind == FISH) {
			dirs[k] = dir;
			k++;
		}
	}
	if (k == 0)
		return REST;
	return dirs[myrand (k)];
}

int choose_empty (int i, int j)
{
	int k = 0;
	int dir;
	int dirs[4];
	for (dir=0; dir < 4; dir++) {
		int npi = ni (i, dir);
		int npj = nj (j, dir);
		struct animal * t = &wator[npi][npj];
		if (t->kind == EMPTY) {
			dirs[k] = dir;
			k++;
		}
	}
	if (k == 0)
		return REST;
	return dirs[myrand (k)];
}

int freecount = 0;

int move_to_fish (int i, int j)
{
	int npi, npj;
	int dir;
	struct animal * t;

	t = &wator[i][j];
	assert (t->kind == SHARK);

	dir = choose_fish (i, j);
	if (dir == REST)
		return 0;
	npi = ni (i, dir);
	npj = nj (j, dir);
	assert (wator[npi][npj].kind == FISH);
	freecount++;
	memcpy  (&wator[npi][npj], t,sizeof(animal));
	wator[i][j].kind = EMPTY;
	wator[npi][npj].hunger = 0;
	if (wator[npi][npj].age >= HBRUT) {
		wator[i][j].age = 0;
		new_animal (i, j, SHARK);
	}
	return 1;
}

int move_to_empty (int i, int j)
{
	int npi, npj;
	int dir;
	struct animal * t;

	t = &wator[i][j];
	assert ((t->kind == SHARK) || (t->kind == FISH)); 

	dir = choose_empty (i, j);
	if (dir == REST)
		return 0;
	npi = ni (i, dir);
	npj = nj (j, dir);
	assert (wator[npi][npj].kind == EMPTY);
	memcpy(&wator[npi][npj], t, sizeof(animal));
	wator[i][j].kind = EMPTY;
	if ((wator[npi][npj].kind == FISH) && (wator[npi][npj].age >= FBRUT)) {
		wator[npi][npj].age = 0;
		new_animal (i, j, FISH);
	}
	if ((wator[npi][npj].kind == SHARK) && (wator[npi][npj].age >= HBRUT)) {
		wator[npi][npj].age = 0;
		new_animal (i, j, SHARK);
	}
	return 1;
}

void move (int i, int j)
{
	struct animal * t;

	t = &wator[i][j];
	assert ((t->kind == SHARK) || (t->kind == FISH));

	t->age++;
	if (t->kind == SHARK) {
		t->hunger++;
		if (t->hunger >= FASTEN) {
			wator[i][j].kind = EMPTY;
			freecount++;
			return;
		}
		if (move_to_fish (i, j))
			return;
	}
	move_to_empty (i, j);
}

int fd = -1;

void show_wator ()
{
	int i, j;
	int shark = 0, fish = 0;
	for (i=0; i<MAXI; ++i) {
		for (j=0; j<MAXJ; ++j) {
			if (wator[i][j].kind != EMPTY) {
				if (wator[i][j].kind == SHARK) {
					printf ("X");
					shark++;
				} else {
					printf ("*");
					fish++;
				}
			} else {
				printf (".");
			}
		}
		printf ("\n");
	}
	printf ("SHARKS: %d, FISH: %d NEW: %d, FREE: %d\n\n", shark, fish, newcount, freecount);
	if (fd >= 0) {
		char buf[100];
		int ret;
		static int tick = 0;
		sprintf (buf, "%d %d %d\n", tick, shark, fish);
		tick++;
		ret = write (fd, buf, strlen (buf));
		if (ret != strlen (buf)) {
			fprintf (stderr, "Write to output file failed\n");
			exit (2);
		}
	}
	newcount = freecount = 0;
}

void init_wator (int maxi, int maxj, int hbrut, int fbrut, int fasten)
{
	int i, j;
	HBRUT = hbrut;
	FBRUT = fbrut;
	FASTEN = fasten;
	assert (hbrut > FASTEN);
	for (i=0; i<MAXI; ++i) {
		for (j=0; j<MAXJ; ++j) {
			int res = myrand (30);
			wator[i][j].kind = EMPTY;
			switch (res) {
			case 0:
				new_animal (i, j, SHARK);
				break;
			case 1 ... 11:
				new_animal (i, j, FISH);
				break;
			}
		}
	}
}

void moveall ()
{
	int i, j;
	for (i=0; i<MAXI; ++i) {
		for (j=0; j<MAXJ; ++j) {
			if (wator[i][j].kind !=EMPTY) {
				wator[i][j].todo = 1;
			}
		}
	}
	for (i=0; i<MAXI; ++i) {
		for (j=0; j<MAXJ; ++j) {
			if ((wator[i][j].kind !=EMPTY) && (wator[i][j].todo)) {
				wator[i][j].todo = 0;
				move (i, j);
			}
		}
	}
}

int main (int argc, char * argv[])
{
	char ch;
	int i;
	srand (time (NULL));
	fd = -1;
	if (argc > 2) {
		fprintf (stderr, "usage: wator [ file ]\n");
		exit (1);
	}
	if (argc == 2) {
		fd = open (argv[1], O_WRONLY|O_TRUNC|O_CREAT, 0600);
		if (fd < 0) {
			perror ("open");
			exit (1);
		}
	}
//	init_wator (MAXI, MAXJ, 10, 3, 5);
	
	init_wator (MAXI, MAXJ, 10, 3, 3);
	show_wator ();
	for (i=0;i<1000;i++) {
		moveall ();
		show_wator ();
/*		ch = getchar ();
		if (ch < 0)
			break; */
	}
	return 0;
}
