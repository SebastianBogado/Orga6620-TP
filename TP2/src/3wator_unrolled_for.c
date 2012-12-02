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
	char kind;      	/* SHARK o FISH */
	unsigned char age;      /* Edad del animal. */
	unsigned char hunger;   /* Turnos que lleva sin comer un tiburón */
	char todo;     		/* padding   */
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

int choose (int i, int j, char kind)
{
	int k = 0;
	int dir;
	int dirs[4];
	for (dir=0; dir < 4; dir++) {
		int npi = ni (i, dir);
		int npj = nj (j, dir);
		struct animal * t = &wator[npi][npj];
		if (t->kind == kind) {
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

	dir = choose (i, j, FISH);
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

	dir = choose (i, j, EMPTY);
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
/*	int i, j;

	for (i=0; i<MAXI; ++i) {
		for (j=0; j<MAXJ; ++j) {
			if (wator[i][j].kind !=EMPTY) {
				move (i,j);
			}
		}
	}
*/

	if (wator[0][0].kind != EMPTY) move(0, 0);
	if (wator[0][1].kind != EMPTY) move(0, 1);
	if (wator[0][2].kind != EMPTY) move(0, 2);
	if (wator[0][3].kind != EMPTY) move(0, 3);
	if (wator[0][4].kind != EMPTY) move(0, 4);
	if (wator[0][5].kind != EMPTY) move(0, 5);
	if (wator[0][6].kind != EMPTY) move(0, 6);
	if (wator[0][7].kind != EMPTY) move(0, 7);
	if (wator[0][8].kind != EMPTY) move(0, 8);
	if (wator[0][9].kind != EMPTY) move(0, 9);
	if (wator[0][10].kind != EMPTY) move(0, 10);
	if (wator[0][11].kind != EMPTY) move(0, 11);
	if (wator[0][12].kind != EMPTY) move(0, 12);
	if (wator[0][13].kind != EMPTY) move(0, 13);
	if (wator[0][14].kind != EMPTY) move(0, 14);
	if (wator[0][15].kind != EMPTY) move(0, 15);
	if (wator[0][16].kind != EMPTY) move(0, 16);
	if (wator[0][17].kind != EMPTY) move(0, 17);
	if (wator[0][18].kind != EMPTY) move(0, 18);
	if (wator[0][19].kind != EMPTY) move(0, 19);
	if (wator[0][20].kind != EMPTY) move(0, 20);
	if (wator[0][21].kind != EMPTY) move(0, 21);
	if (wator[0][22].kind != EMPTY) move(0, 22);
	if (wator[0][23].kind != EMPTY) move(0, 23);
	if (wator[0][24].kind != EMPTY) move(0, 24);
	if (wator[0][25].kind != EMPTY) move(0, 25);
	if (wator[0][26].kind != EMPTY) move(0, 26);
	if (wator[0][27].kind != EMPTY) move(0, 27);
	if (wator[0][28].kind != EMPTY) move(0, 28);
	if (wator[0][29].kind != EMPTY) move(0, 29);
	if (wator[0][30].kind != EMPTY) move(0, 30);
	if (wator[0][31].kind != EMPTY) move(0, 31);
	if (wator[1][0].kind != EMPTY) move(1, 0);
	if (wator[1][1].kind != EMPTY) move(1, 1);
	if (wator[1][2].kind != EMPTY) move(1, 2);
	if (wator[1][3].kind != EMPTY) move(1, 3);
	if (wator[1][4].kind != EMPTY) move(1, 4);
	if (wator[1][5].kind != EMPTY) move(1, 5);
	if (wator[1][6].kind != EMPTY) move(1, 6);
	if (wator[1][7].kind != EMPTY) move(1, 7);
	if (wator[1][8].kind != EMPTY) move(1, 8);
	if (wator[1][9].kind != EMPTY) move(1, 9);
	if (wator[1][10].kind != EMPTY) move(1, 10);
	if (wator[1][11].kind != EMPTY) move(1, 11);
	if (wator[1][12].kind != EMPTY) move(1, 12);
	if (wator[1][13].kind != EMPTY) move(1, 13);
	if (wator[1][14].kind != EMPTY) move(1, 14);
	if (wator[1][15].kind != EMPTY) move(1, 15);
	if (wator[1][16].kind != EMPTY) move(1, 16);
	if (wator[1][17].kind != EMPTY) move(1, 17);
	if (wator[1][18].kind != EMPTY) move(1, 18);
	if (wator[1][19].kind != EMPTY) move(1, 19);
	if (wator[1][20].kind != EMPTY) move(1, 20);
	if (wator[1][21].kind != EMPTY) move(1, 21);
	if (wator[1][22].kind != EMPTY) move(1, 22);
	if (wator[1][23].kind != EMPTY) move(1, 23);
	if (wator[1][24].kind != EMPTY) move(1, 24);
	if (wator[1][25].kind != EMPTY) move(1, 25);
	if (wator[1][26].kind != EMPTY) move(1, 26);
	if (wator[1][27].kind != EMPTY) move(1, 27);
	if (wator[1][28].kind != EMPTY) move(1, 28);
	if (wator[1][29].kind != EMPTY) move(1, 29);
	if (wator[1][30].kind != EMPTY) move(1, 30);
	if (wator[1][31].kind != EMPTY) move(1, 31);
	if (wator[2][0].kind != EMPTY) move(2, 0);
	if (wator[2][1].kind != EMPTY) move(2, 1);
	if (wator[2][2].kind != EMPTY) move(2, 2);
	if (wator[2][3].kind != EMPTY) move(2, 3);
	if (wator[2][4].kind != EMPTY) move(2, 4);
	if (wator[2][5].kind != EMPTY) move(2, 5);
	if (wator[2][6].kind != EMPTY) move(2, 6);
	if (wator[2][7].kind != EMPTY) move(2, 7);
	if (wator[2][8].kind != EMPTY) move(2, 8);
	if (wator[2][9].kind != EMPTY) move(2, 9);
	if (wator[2][10].kind != EMPTY) move(2, 10);
	if (wator[2][11].kind != EMPTY) move(2, 11);
	if (wator[2][12].kind != EMPTY) move(2, 12);
	if (wator[2][13].kind != EMPTY) move(2, 13);
	if (wator[2][14].kind != EMPTY) move(2, 14);
	if (wator[2][15].kind != EMPTY) move(2, 15);
	if (wator[2][16].kind != EMPTY) move(2, 16);
	if (wator[2][17].kind != EMPTY) move(2, 17);
	if (wator[2][18].kind != EMPTY) move(2, 18);
	if (wator[2][19].kind != EMPTY) move(2, 19);
	if (wator[2][20].kind != EMPTY) move(2, 20);
	if (wator[2][21].kind != EMPTY) move(2, 21);
	if (wator[2][22].kind != EMPTY) move(2, 22);
	if (wator[2][23].kind != EMPTY) move(2, 23);
	if (wator[2][24].kind != EMPTY) move(2, 24);
	if (wator[2][25].kind != EMPTY) move(2, 25);
	if (wator[2][26].kind != EMPTY) move(2, 26);
	if (wator[2][27].kind != EMPTY) move(2, 27);
	if (wator[2][28].kind != EMPTY) move(2, 28);
	if (wator[2][29].kind != EMPTY) move(2, 29);
	if (wator[2][30].kind != EMPTY) move(2, 30);
	if (wator[2][31].kind != EMPTY) move(2, 31);
	if (wator[3][0].kind != EMPTY) move(3, 0);
	if (wator[3][1].kind != EMPTY) move(3, 1);
	if (wator[3][2].kind != EMPTY) move(3, 2);
	if (wator[3][3].kind != EMPTY) move(3, 3);
	if (wator[3][4].kind != EMPTY) move(3, 4);
	if (wator[3][5].kind != EMPTY) move(3, 5);
	if (wator[3][6].kind != EMPTY) move(3, 6);
	if (wator[3][7].kind != EMPTY) move(3, 7);
	if (wator[3][8].kind != EMPTY) move(3, 8);
	if (wator[3][9].kind != EMPTY) move(3, 9);
	if (wator[3][10].kind != EMPTY) move(3, 10);
	if (wator[3][11].kind != EMPTY) move(3, 11);
	if (wator[3][12].kind != EMPTY) move(3, 12);
	if (wator[3][13].kind != EMPTY) move(3, 13);
	if (wator[3][14].kind != EMPTY) move(3, 14);
	if (wator[3][15].kind != EMPTY) move(3, 15);
	if (wator[3][16].kind != EMPTY) move(3, 16);
	if (wator[3][17].kind != EMPTY) move(3, 17);
	if (wator[3][18].kind != EMPTY) move(3, 18);
	if (wator[3][19].kind != EMPTY) move(3, 19);
	if (wator[3][20].kind != EMPTY) move(3, 20);
	if (wator[3][21].kind != EMPTY) move(3, 21);
	if (wator[3][22].kind != EMPTY) move(3, 22);
	if (wator[3][23].kind != EMPTY) move(3, 23);
	if (wator[3][24].kind != EMPTY) move(3, 24);
	if (wator[3][25].kind != EMPTY) move(3, 25);
	if (wator[3][26].kind != EMPTY) move(3, 26);
	if (wator[3][27].kind != EMPTY) move(3, 27);
	if (wator[3][28].kind != EMPTY) move(3, 28);
	if (wator[3][29].kind != EMPTY) move(3, 29);
	if (wator[3][30].kind != EMPTY) move(3, 30);
	if (wator[3][31].kind != EMPTY) move(3, 31);
	if (wator[4][0].kind != EMPTY) move(4, 0);
	if (wator[4][1].kind != EMPTY) move(4, 1);
	if (wator[4][2].kind != EMPTY) move(4, 2);
	if (wator[4][3].kind != EMPTY) move(4, 3);
	if (wator[4][4].kind != EMPTY) move(4, 4);
	if (wator[4][5].kind != EMPTY) move(4, 5);
	if (wator[4][6].kind != EMPTY) move(4, 6);
	if (wator[4][7].kind != EMPTY) move(4, 7);
	if (wator[4][8].kind != EMPTY) move(4, 8);
	if (wator[4][9].kind != EMPTY) move(4, 9);
	if (wator[4][10].kind != EMPTY) move(4, 10);
	if (wator[4][11].kind != EMPTY) move(4, 11);
	if (wator[4][12].kind != EMPTY) move(4, 12);
	if (wator[4][13].kind != EMPTY) move(4, 13);
	if (wator[4][14].kind != EMPTY) move(4, 14);
	if (wator[4][15].kind != EMPTY) move(4, 15);
	if (wator[4][16].kind != EMPTY) move(4, 16);
	if (wator[4][17].kind != EMPTY) move(4, 17);
	if (wator[4][18].kind != EMPTY) move(4, 18);
	if (wator[4][19].kind != EMPTY) move(4, 19);
	if (wator[4][20].kind != EMPTY) move(4, 20);
	if (wator[4][21].kind != EMPTY) move(4, 21);
	if (wator[4][22].kind != EMPTY) move(4, 22);
	if (wator[4][23].kind != EMPTY) move(4, 23);
	if (wator[4][24].kind != EMPTY) move(4, 24);
	if (wator[4][25].kind != EMPTY) move(4, 25);
	if (wator[4][26].kind != EMPTY) move(4, 26);
	if (wator[4][27].kind != EMPTY) move(4, 27);
	if (wator[4][28].kind != EMPTY) move(4, 28);
	if (wator[4][29].kind != EMPTY) move(4, 29);
	if (wator[4][30].kind != EMPTY) move(4, 30);
	if (wator[4][31].kind != EMPTY) move(4, 31);
	if (wator[5][0].kind != EMPTY) move(5, 0);
	if (wator[5][1].kind != EMPTY) move(5, 1);
	if (wator[5][2].kind != EMPTY) move(5, 2);
	if (wator[5][3].kind != EMPTY) move(5, 3);
	if (wator[5][4].kind != EMPTY) move(5, 4);
	if (wator[5][5].kind != EMPTY) move(5, 5);
	if (wator[5][6].kind != EMPTY) move(5, 6);
	if (wator[5][7].kind != EMPTY) move(5, 7);
	if (wator[5][8].kind != EMPTY) move(5, 8);
	if (wator[5][9].kind != EMPTY) move(5, 9);
	if (wator[5][10].kind != EMPTY) move(5, 10);
	if (wator[5][11].kind != EMPTY) move(5, 11);
	if (wator[5][12].kind != EMPTY) move(5, 12);
	if (wator[5][13].kind != EMPTY) move(5, 13);
	if (wator[5][14].kind != EMPTY) move(5, 14);
	if (wator[5][15].kind != EMPTY) move(5, 15);
	if (wator[5][16].kind != EMPTY) move(5, 16);
	if (wator[5][17].kind != EMPTY) move(5, 17);
	if (wator[5][18].kind != EMPTY) move(5, 18);
	if (wator[5][19].kind != EMPTY) move(5, 19);
	if (wator[5][20].kind != EMPTY) move(5, 20);
	if (wator[5][21].kind != EMPTY) move(5, 21);
	if (wator[5][22].kind != EMPTY) move(5, 22);
	if (wator[5][23].kind != EMPTY) move(5, 23);
	if (wator[5][24].kind != EMPTY) move(5, 24);
	if (wator[5][25].kind != EMPTY) move(5, 25);
	if (wator[5][26].kind != EMPTY) move(5, 26);
	if (wator[5][27].kind != EMPTY) move(5, 27);
	if (wator[5][28].kind != EMPTY) move(5, 28);
	if (wator[5][29].kind != EMPTY) move(5, 29);
	if (wator[5][30].kind != EMPTY) move(5, 30);
	if (wator[5][31].kind != EMPTY) move(5, 31);
	if (wator[6][0].kind != EMPTY) move(6, 0);
	if (wator[6][1].kind != EMPTY) move(6, 1);
	if (wator[6][2].kind != EMPTY) move(6, 2);
	if (wator[6][3].kind != EMPTY) move(6, 3);
	if (wator[6][4].kind != EMPTY) move(6, 4);
	if (wator[6][5].kind != EMPTY) move(6, 5);
	if (wator[6][6].kind != EMPTY) move(6, 6);
	if (wator[6][7].kind != EMPTY) move(6, 7);
	if (wator[6][8].kind != EMPTY) move(6, 8);
	if (wator[6][9].kind != EMPTY) move(6, 9);
	if (wator[6][10].kind != EMPTY) move(6, 10);
	if (wator[6][11].kind != EMPTY) move(6, 11);
	if (wator[6][12].kind != EMPTY) move(6, 12);
	if (wator[6][13].kind != EMPTY) move(6, 13);
	if (wator[6][14].kind != EMPTY) move(6, 14);
	if (wator[6][15].kind != EMPTY) move(6, 15);
	if (wator[6][16].kind != EMPTY) move(6, 16);
	if (wator[6][17].kind != EMPTY) move(6, 17);
	if (wator[6][18].kind != EMPTY) move(6, 18);
	if (wator[6][19].kind != EMPTY) move(6, 19);
	if (wator[6][20].kind != EMPTY) move(6, 20);
	if (wator[6][21].kind != EMPTY) move(6, 21);
	if (wator[6][22].kind != EMPTY) move(6, 22);
	if (wator[6][23].kind != EMPTY) move(6, 23);
	if (wator[6][24].kind != EMPTY) move(6, 24);
	if (wator[6][25].kind != EMPTY) move(6, 25);
	if (wator[6][26].kind != EMPTY) move(6, 26);
	if (wator[6][27].kind != EMPTY) move(6, 27);
	if (wator[6][28].kind != EMPTY) move(6, 28);
	if (wator[6][29].kind != EMPTY) move(6, 29);
	if (wator[6][30].kind != EMPTY) move(6, 30);
	if (wator[6][31].kind != EMPTY) move(6, 31);
	if (wator[7][0].kind != EMPTY) move(7, 0);
	if (wator[7][1].kind != EMPTY) move(7, 1);
	if (wator[7][2].kind != EMPTY) move(7, 2);
	if (wator[7][3].kind != EMPTY) move(7, 3);
	if (wator[7][4].kind != EMPTY) move(7, 4);
	if (wator[7][5].kind != EMPTY) move(7, 5);
	if (wator[7][6].kind != EMPTY) move(7, 6);
	if (wator[7][7].kind != EMPTY) move(7, 7);
	if (wator[7][8].kind != EMPTY) move(7, 8);
	if (wator[7][9].kind != EMPTY) move(7, 9);
	if (wator[7][10].kind != EMPTY) move(7, 10);
	if (wator[7][11].kind != EMPTY) move(7, 11);
	if (wator[7][12].kind != EMPTY) move(7, 12);
	if (wator[7][13].kind != EMPTY) move(7, 13);
	if (wator[7][14].kind != EMPTY) move(7, 14);
	if (wator[7][15].kind != EMPTY) move(7, 15);
	if (wator[7][16].kind != EMPTY) move(7, 16);
	if (wator[7][17].kind != EMPTY) move(7, 17);
	if (wator[7][18].kind != EMPTY) move(7, 18);
	if (wator[7][19].kind != EMPTY) move(7, 19);
	if (wator[7][20].kind != EMPTY) move(7, 20);
	if (wator[7][21].kind != EMPTY) move(7, 21);
	if (wator[7][22].kind != EMPTY) move(7, 22);
	if (wator[7][23].kind != EMPTY) move(7, 23);
	if (wator[7][24].kind != EMPTY) move(7, 24);
	if (wator[7][25].kind != EMPTY) move(7, 25);
	if (wator[7][26].kind != EMPTY) move(7, 26);
	if (wator[7][27].kind != EMPTY) move(7, 27);
	if (wator[7][28].kind != EMPTY) move(7, 28);
	if (wator[7][29].kind != EMPTY) move(7, 29);
	if (wator[7][30].kind != EMPTY) move(7, 30);
	if (wator[7][31].kind != EMPTY) move(7, 31);
	if (wator[8][0].kind != EMPTY) move(8, 0);
	if (wator[8][1].kind != EMPTY) move(8, 1);
	if (wator[8][2].kind != EMPTY) move(8, 2);
	if (wator[8][3].kind != EMPTY) move(8, 3);
	if (wator[8][4].kind != EMPTY) move(8, 4);
	if (wator[8][5].kind != EMPTY) move(8, 5);
	if (wator[8][6].kind != EMPTY) move(8, 6);
	if (wator[8][7].kind != EMPTY) move(8, 7);
	if (wator[8][8].kind != EMPTY) move(8, 8);
	if (wator[8][9].kind != EMPTY) move(8, 9);
	if (wator[8][10].kind != EMPTY) move(8, 10);
	if (wator[8][11].kind != EMPTY) move(8, 11);
	if (wator[8][12].kind != EMPTY) move(8, 12);
	if (wator[8][13].kind != EMPTY) move(8, 13);
	if (wator[8][14].kind != EMPTY) move(8, 14);
	if (wator[8][15].kind != EMPTY) move(8, 15);
	if (wator[8][16].kind != EMPTY) move(8, 16);
	if (wator[8][17].kind != EMPTY) move(8, 17);
	if (wator[8][18].kind != EMPTY) move(8, 18);
	if (wator[8][19].kind != EMPTY) move(8, 19);
	if (wator[8][20].kind != EMPTY) move(8, 20);
	if (wator[8][21].kind != EMPTY) move(8, 21);
	if (wator[8][22].kind != EMPTY) move(8, 22);
	if (wator[8][23].kind != EMPTY) move(8, 23);
	if (wator[8][24].kind != EMPTY) move(8, 24);
	if (wator[8][25].kind != EMPTY) move(8, 25);
	if (wator[8][26].kind != EMPTY) move(8, 26);
	if (wator[8][27].kind != EMPTY) move(8, 27);
	if (wator[8][28].kind != EMPTY) move(8, 28);
	if (wator[8][29].kind != EMPTY) move(8, 29);
	if (wator[8][30].kind != EMPTY) move(8, 30);
	if (wator[8][31].kind != EMPTY) move(8, 31);
	if (wator[9][0].kind != EMPTY) move(9, 0);
	if (wator[9][1].kind != EMPTY) move(9, 1);
	if (wator[9][2].kind != EMPTY) move(9, 2);
	if (wator[9][3].kind != EMPTY) move(9, 3);
	if (wator[9][4].kind != EMPTY) move(9, 4);
	if (wator[9][5].kind != EMPTY) move(9, 5);
	if (wator[9][6].kind != EMPTY) move(9, 6);
	if (wator[9][7].kind != EMPTY) move(9, 7);
	if (wator[9][8].kind != EMPTY) move(9, 8);
	if (wator[9][9].kind != EMPTY) move(9, 9);
	if (wator[9][10].kind != EMPTY) move(9, 10);
	if (wator[9][11].kind != EMPTY) move(9, 11);
	if (wator[9][12].kind != EMPTY) move(9, 12);
	if (wator[9][13].kind != EMPTY) move(9, 13);
	if (wator[9][14].kind != EMPTY) move(9, 14);
	if (wator[9][15].kind != EMPTY) move(9, 15);
	if (wator[9][16].kind != EMPTY) move(9, 16);
	if (wator[9][17].kind != EMPTY) move(9, 17);
	if (wator[9][18].kind != EMPTY) move(9, 18);
	if (wator[9][19].kind != EMPTY) move(9, 19);
	if (wator[9][20].kind != EMPTY) move(9, 20);
	if (wator[9][21].kind != EMPTY) move(9, 21);
	if (wator[9][22].kind != EMPTY) move(9, 22);
	if (wator[9][23].kind != EMPTY) move(9, 23);
	if (wator[9][24].kind != EMPTY) move(9, 24);
	if (wator[9][25].kind != EMPTY) move(9, 25);
	if (wator[9][26].kind != EMPTY) move(9, 26);
	if (wator[9][27].kind != EMPTY) move(9, 27);
	if (wator[9][28].kind != EMPTY) move(9, 28);
	if (wator[9][29].kind != EMPTY) move(9, 29);
	if (wator[9][30].kind != EMPTY) move(9, 30);
	if (wator[9][31].kind != EMPTY) move(9, 31);
	if (wator[10][0].kind != EMPTY) move(10, 0);
	if (wator[10][1].kind != EMPTY) move(10, 1);
	if (wator[10][2].kind != EMPTY) move(10, 2);
	if (wator[10][3].kind != EMPTY) move(10, 3);
	if (wator[10][4].kind != EMPTY) move(10, 4);
	if (wator[10][5].kind != EMPTY) move(10, 5);
	if (wator[10][6].kind != EMPTY) move(10, 6);
	if (wator[10][7].kind != EMPTY) move(10, 7);
	if (wator[10][8].kind != EMPTY) move(10, 8);
	if (wator[10][9].kind != EMPTY) move(10, 9);
	if (wator[10][10].kind != EMPTY) move(10, 10);
	if (wator[10][11].kind != EMPTY) move(10, 11);
	if (wator[10][12].kind != EMPTY) move(10, 12);
	if (wator[10][13].kind != EMPTY) move(10, 13);
	if (wator[10][14].kind != EMPTY) move(10, 14);
	if (wator[10][15].kind != EMPTY) move(10, 15);
	if (wator[10][16].kind != EMPTY) move(10, 16);
	if (wator[10][17].kind != EMPTY) move(10, 17);
	if (wator[10][18].kind != EMPTY) move(10, 18);
	if (wator[10][19].kind != EMPTY) move(10, 19);
	if (wator[10][20].kind != EMPTY) move(10, 20);
	if (wator[10][21].kind != EMPTY) move(10, 21);
	if (wator[10][22].kind != EMPTY) move(10, 22);
	if (wator[10][23].kind != EMPTY) move(10, 23);
	if (wator[10][24].kind != EMPTY) move(10, 24);
	if (wator[10][25].kind != EMPTY) move(10, 25);
	if (wator[10][26].kind != EMPTY) move(10, 26);
	if (wator[10][27].kind != EMPTY) move(10, 27);
	if (wator[10][28].kind != EMPTY) move(10, 28);
	if (wator[10][29].kind != EMPTY) move(10, 29);
	if (wator[10][30].kind != EMPTY) move(10, 30);
	if (wator[10][31].kind != EMPTY) move(10, 31);
	if (wator[11][0].kind != EMPTY) move(11, 0);
	if (wator[11][1].kind != EMPTY) move(11, 1);
	if (wator[11][2].kind != EMPTY) move(11, 2);
	if (wator[11][3].kind != EMPTY) move(11, 3);
	if (wator[11][4].kind != EMPTY) move(11, 4);
	if (wator[11][5].kind != EMPTY) move(11, 5);
	if (wator[11][6].kind != EMPTY) move(11, 6);
	if (wator[11][7].kind != EMPTY) move(11, 7);
	if (wator[11][8].kind != EMPTY) move(11, 8);
	if (wator[11][9].kind != EMPTY) move(11, 9);
	if (wator[11][10].kind != EMPTY) move(11, 10);
	if (wator[11][11].kind != EMPTY) move(11, 11);
	if (wator[11][12].kind != EMPTY) move(11, 12);
	if (wator[11][13].kind != EMPTY) move(11, 13);
	if (wator[11][14].kind != EMPTY) move(11, 14);
	if (wator[11][15].kind != EMPTY) move(11, 15);
	if (wator[11][16].kind != EMPTY) move(11, 16);
	if (wator[11][17].kind != EMPTY) move(11, 17);
	if (wator[11][18].kind != EMPTY) move(11, 18);
	if (wator[11][19].kind != EMPTY) move(11, 19);
	if (wator[11][20].kind != EMPTY) move(11, 20);
	if (wator[11][21].kind != EMPTY) move(11, 21);
	if (wator[11][22].kind != EMPTY) move(11, 22);
	if (wator[11][23].kind != EMPTY) move(11, 23);
	if (wator[11][24].kind != EMPTY) move(11, 24);
	if (wator[11][25].kind != EMPTY) move(11, 25);
	if (wator[11][26].kind != EMPTY) move(11, 26);
	if (wator[11][27].kind != EMPTY) move(11, 27);
	if (wator[11][28].kind != EMPTY) move(11, 28);
	if (wator[11][29].kind != EMPTY) move(11, 29);
	if (wator[11][30].kind != EMPTY) move(11, 30);
	if (wator[11][31].kind != EMPTY) move(11, 31);
	if (wator[12][0].kind != EMPTY) move(12, 0);
	if (wator[12][1].kind != EMPTY) move(12, 1);
	if (wator[12][2].kind != EMPTY) move(12, 2);
	if (wator[12][3].kind != EMPTY) move(12, 3);
	if (wator[12][4].kind != EMPTY) move(12, 4);
	if (wator[12][5].kind != EMPTY) move(12, 5);
	if (wator[12][6].kind != EMPTY) move(12, 6);
	if (wator[12][7].kind != EMPTY) move(12, 7);
	if (wator[12][8].kind != EMPTY) move(12, 8);
	if (wator[12][9].kind != EMPTY) move(12, 9);
	if (wator[12][10].kind != EMPTY) move(12, 10);
	if (wator[12][11].kind != EMPTY) move(12, 11);
	if (wator[12][12].kind != EMPTY) move(12, 12);
	if (wator[12][13].kind != EMPTY) move(12, 13);
	if (wator[12][14].kind != EMPTY) move(12, 14);
	if (wator[12][15].kind != EMPTY) move(12, 15);
	if (wator[12][16].kind != EMPTY) move(12, 16);
	if (wator[12][17].kind != EMPTY) move(12, 17);
	if (wator[12][18].kind != EMPTY) move(12, 18);
	if (wator[12][19].kind != EMPTY) move(12, 19);
	if (wator[12][20].kind != EMPTY) move(12, 20);
	if (wator[12][21].kind != EMPTY) move(12, 21);
	if (wator[12][22].kind != EMPTY) move(12, 22);
	if (wator[12][23].kind != EMPTY) move(12, 23);
	if (wator[12][24].kind != EMPTY) move(12, 24);
	if (wator[12][25].kind != EMPTY) move(12, 25);
	if (wator[12][26].kind != EMPTY) move(12, 26);
	if (wator[12][27].kind != EMPTY) move(12, 27);
	if (wator[12][28].kind != EMPTY) move(12, 28);
	if (wator[12][29].kind != EMPTY) move(12, 29);
	if (wator[12][30].kind != EMPTY) move(12, 30);
	if (wator[12][31].kind != EMPTY) move(12, 31);
	if (wator[13][0].kind != EMPTY) move(13, 0);
	if (wator[13][1].kind != EMPTY) move(13, 1);
	if (wator[13][2].kind != EMPTY) move(13, 2);
	if (wator[13][3].kind != EMPTY) move(13, 3);
	if (wator[13][4].kind != EMPTY) move(13, 4);
	if (wator[13][5].kind != EMPTY) move(13, 5);
	if (wator[13][6].kind != EMPTY) move(13, 6);
	if (wator[13][7].kind != EMPTY) move(13, 7);
	if (wator[13][8].kind != EMPTY) move(13, 8);
	if (wator[13][9].kind != EMPTY) move(13, 9);
	if (wator[13][10].kind != EMPTY) move(13, 10);
	if (wator[13][11].kind != EMPTY) move(13, 11);
	if (wator[13][12].kind != EMPTY) move(13, 12);
	if (wator[13][13].kind != EMPTY) move(13, 13);
	if (wator[13][14].kind != EMPTY) move(13, 14);
	if (wator[13][15].kind != EMPTY) move(13, 15);
	if (wator[13][16].kind != EMPTY) move(13, 16);
	if (wator[13][17].kind != EMPTY) move(13, 17);
	if (wator[13][18].kind != EMPTY) move(13, 18);
	if (wator[13][19].kind != EMPTY) move(13, 19);
	if (wator[13][20].kind != EMPTY) move(13, 20);
	if (wator[13][21].kind != EMPTY) move(13, 21);
	if (wator[13][22].kind != EMPTY) move(13, 22);
	if (wator[13][23].kind != EMPTY) move(13, 23);
	if (wator[13][24].kind != EMPTY) move(13, 24);
	if (wator[13][25].kind != EMPTY) move(13, 25);
	if (wator[13][26].kind != EMPTY) move(13, 26);
	if (wator[13][27].kind != EMPTY) move(13, 27);
	if (wator[13][28].kind != EMPTY) move(13, 28);
	if (wator[13][29].kind != EMPTY) move(13, 29);
	if (wator[13][30].kind != EMPTY) move(13, 30);
	if (wator[13][31].kind != EMPTY) move(13, 31);
	if (wator[14][0].kind != EMPTY) move(14, 0);
	if (wator[14][1].kind != EMPTY) move(14, 1);
	if (wator[14][2].kind != EMPTY) move(14, 2);
	if (wator[14][3].kind != EMPTY) move(14, 3);
	if (wator[14][4].kind != EMPTY) move(14, 4);
	if (wator[14][5].kind != EMPTY) move(14, 5);
	if (wator[14][6].kind != EMPTY) move(14, 6);
	if (wator[14][7].kind != EMPTY) move(14, 7);
	if (wator[14][8].kind != EMPTY) move(14, 8);
	if (wator[14][9].kind != EMPTY) move(14, 9);
	if (wator[14][10].kind != EMPTY) move(14, 10);
	if (wator[14][11].kind != EMPTY) move(14, 11);
	if (wator[14][12].kind != EMPTY) move(14, 12);
	if (wator[14][13].kind != EMPTY) move(14, 13);
	if (wator[14][14].kind != EMPTY) move(14, 14);
	if (wator[14][15].kind != EMPTY) move(14, 15);
	if (wator[14][16].kind != EMPTY) move(14, 16);
	if (wator[14][17].kind != EMPTY) move(14, 17);
	if (wator[14][18].kind != EMPTY) move(14, 18);
	if (wator[14][19].kind != EMPTY) move(14, 19);
	if (wator[14][20].kind != EMPTY) move(14, 20);
	if (wator[14][21].kind != EMPTY) move(14, 21);
	if (wator[14][22].kind != EMPTY) move(14, 22);
	if (wator[14][23].kind != EMPTY) move(14, 23);
	if (wator[14][24].kind != EMPTY) move(14, 24);
	if (wator[14][25].kind != EMPTY) move(14, 25);
	if (wator[14][26].kind != EMPTY) move(14, 26);
	if (wator[14][27].kind != EMPTY) move(14, 27);
	if (wator[14][28].kind != EMPTY) move(14, 28);
	if (wator[14][29].kind != EMPTY) move(14, 29);
	if (wator[14][30].kind != EMPTY) move(14, 30);
	if (wator[14][31].kind != EMPTY) move(14, 31);
	if (wator[15][0].kind != EMPTY) move(15, 0);
	if (wator[15][1].kind != EMPTY) move(15, 1);
	if (wator[15][2].kind != EMPTY) move(15, 2);
	if (wator[15][3].kind != EMPTY) move(15, 3);
	if (wator[15][4].kind != EMPTY) move(15, 4);
	if (wator[15][5].kind != EMPTY) move(15, 5);
	if (wator[15][6].kind != EMPTY) move(15, 6);
	if (wator[15][7].kind != EMPTY) move(15, 7);
	if (wator[15][8].kind != EMPTY) move(15, 8);
	if (wator[15][9].kind != EMPTY) move(15, 9);
	if (wator[15][10].kind != EMPTY) move(15, 10);
	if (wator[15][11].kind != EMPTY) move(15, 11);
	if (wator[15][12].kind != EMPTY) move(15, 12);
	if (wator[15][13].kind != EMPTY) move(15, 13);
	if (wator[15][14].kind != EMPTY) move(15, 14);
	if (wator[15][15].kind != EMPTY) move(15, 15);
	if (wator[15][16].kind != EMPTY) move(15, 16);
	if (wator[15][17].kind != EMPTY) move(15, 17);
	if (wator[15][18].kind != EMPTY) move(15, 18);
	if (wator[15][19].kind != EMPTY) move(15, 19);
	if (wator[15][20].kind != EMPTY) move(15, 20);
	if (wator[15][21].kind != EMPTY) move(15, 21);
	if (wator[15][22].kind != EMPTY) move(15, 22);
	if (wator[15][23].kind != EMPTY) move(15, 23);
	if (wator[15][24].kind != EMPTY) move(15, 24);
	if (wator[15][25].kind != EMPTY) move(15, 25);
	if (wator[15][26].kind != EMPTY) move(15, 26);
	if (wator[15][27].kind != EMPTY) move(15, 27);
	if (wator[15][28].kind != EMPTY) move(15, 28);
	if (wator[15][29].kind != EMPTY) move(15, 29);
	if (wator[15][30].kind != EMPTY) move(15, 30);
	if (wator[15][31].kind != EMPTY) move(15, 31);
	if (wator[16][0].kind != EMPTY) move(16, 0);
	if (wator[16][1].kind != EMPTY) move(16, 1);
	if (wator[16][2].kind != EMPTY) move(16, 2);
	if (wator[16][3].kind != EMPTY) move(16, 3);
	if (wator[16][4].kind != EMPTY) move(16, 4);
	if (wator[16][5].kind != EMPTY) move(16, 5);
	if (wator[16][6].kind != EMPTY) move(16, 6);
	if (wator[16][7].kind != EMPTY) move(16, 7);
	if (wator[16][8].kind != EMPTY) move(16, 8);
	if (wator[16][9].kind != EMPTY) move(16, 9);
	if (wator[16][10].kind != EMPTY) move(16, 10);
	if (wator[16][11].kind != EMPTY) move(16, 11);
	if (wator[16][12].kind != EMPTY) move(16, 12);
	if (wator[16][13].kind != EMPTY) move(16, 13);
	if (wator[16][14].kind != EMPTY) move(16, 14);
	if (wator[16][15].kind != EMPTY) move(16, 15);
	if (wator[16][16].kind != EMPTY) move(16, 16);
	if (wator[16][17].kind != EMPTY) move(16, 17);
	if (wator[16][18].kind != EMPTY) move(16, 18);
	if (wator[16][19].kind != EMPTY) move(16, 19);
	if (wator[16][20].kind != EMPTY) move(16, 20);
	if (wator[16][21].kind != EMPTY) move(16, 21);
	if (wator[16][22].kind != EMPTY) move(16, 22);
	if (wator[16][23].kind != EMPTY) move(16, 23);
	if (wator[16][24].kind != EMPTY) move(16, 24);
	if (wator[16][25].kind != EMPTY) move(16, 25);
	if (wator[16][26].kind != EMPTY) move(16, 26);
	if (wator[16][27].kind != EMPTY) move(16, 27);
	if (wator[16][28].kind != EMPTY) move(16, 28);
	if (wator[16][29].kind != EMPTY) move(16, 29);
	if (wator[16][30].kind != EMPTY) move(16, 30);
	if (wator[16][31].kind != EMPTY) move(16, 31);
	if (wator[17][0].kind != EMPTY) move(17, 0);
	if (wator[17][1].kind != EMPTY) move(17, 1);
	if (wator[17][2].kind != EMPTY) move(17, 2);
	if (wator[17][3].kind != EMPTY) move(17, 3);
	if (wator[17][4].kind != EMPTY) move(17, 4);
	if (wator[17][5].kind != EMPTY) move(17, 5);
	if (wator[17][6].kind != EMPTY) move(17, 6);
	if (wator[17][7].kind != EMPTY) move(17, 7);
	if (wator[17][8].kind != EMPTY) move(17, 8);
	if (wator[17][9].kind != EMPTY) move(17, 9);
	if (wator[17][10].kind != EMPTY) move(17, 10);
	if (wator[17][11].kind != EMPTY) move(17, 11);
	if (wator[17][12].kind != EMPTY) move(17, 12);
	if (wator[17][13].kind != EMPTY) move(17, 13);
	if (wator[17][14].kind != EMPTY) move(17, 14);
	if (wator[17][15].kind != EMPTY) move(17, 15);
	if (wator[17][16].kind != EMPTY) move(17, 16);
	if (wator[17][17].kind != EMPTY) move(17, 17);
	if (wator[17][18].kind != EMPTY) move(17, 18);
	if (wator[17][19].kind != EMPTY) move(17, 19);
	if (wator[17][20].kind != EMPTY) move(17, 20);
	if (wator[17][21].kind != EMPTY) move(17, 21);
	if (wator[17][22].kind != EMPTY) move(17, 22);
	if (wator[17][23].kind != EMPTY) move(17, 23);
	if (wator[17][24].kind != EMPTY) move(17, 24);
	if (wator[17][25].kind != EMPTY) move(17, 25);
	if (wator[17][26].kind != EMPTY) move(17, 26);
	if (wator[17][27].kind != EMPTY) move(17, 27);
	if (wator[17][28].kind != EMPTY) move(17, 28);
	if (wator[17][29].kind != EMPTY) move(17, 29);
	if (wator[17][30].kind != EMPTY) move(17, 30);
	if (wator[17][31].kind != EMPTY) move(17, 31);
	if (wator[18][0].kind != EMPTY) move(18, 0);
	if (wator[18][1].kind != EMPTY) move(18, 1);
	if (wator[18][2].kind != EMPTY) move(18, 2);
	if (wator[18][3].kind != EMPTY) move(18, 3);
	if (wator[18][4].kind != EMPTY) move(18, 4);
	if (wator[18][5].kind != EMPTY) move(18, 5);
	if (wator[18][6].kind != EMPTY) move(18, 6);
	if (wator[18][7].kind != EMPTY) move(18, 7);
	if (wator[18][8].kind != EMPTY) move(18, 8);
	if (wator[18][9].kind != EMPTY) move(18, 9);
	if (wator[18][10].kind != EMPTY) move(18, 10);
	if (wator[18][11].kind != EMPTY) move(18, 11);
	if (wator[18][12].kind != EMPTY) move(18, 12);
	if (wator[18][13].kind != EMPTY) move(18, 13);
	if (wator[18][14].kind != EMPTY) move(18, 14);
	if (wator[18][15].kind != EMPTY) move(18, 15);
	if (wator[18][16].kind != EMPTY) move(18, 16);
	if (wator[18][17].kind != EMPTY) move(18, 17);
	if (wator[18][18].kind != EMPTY) move(18, 18);
	if (wator[18][19].kind != EMPTY) move(18, 19);
	if (wator[18][20].kind != EMPTY) move(18, 20);
	if (wator[18][21].kind != EMPTY) move(18, 21);
	if (wator[18][22].kind != EMPTY) move(18, 22);
	if (wator[18][23].kind != EMPTY) move(18, 23);
	if (wator[18][24].kind != EMPTY) move(18, 24);
	if (wator[18][25].kind != EMPTY) move(18, 25);
	if (wator[18][26].kind != EMPTY) move(18, 26);
	if (wator[18][27].kind != EMPTY) move(18, 27);
	if (wator[18][28].kind != EMPTY) move(18, 28);
	if (wator[18][29].kind != EMPTY) move(18, 29);
	if (wator[18][30].kind != EMPTY) move(18, 30);
	if (wator[18][31].kind != EMPTY) move(18, 31);
	if (wator[19][0].kind != EMPTY) move(19, 0);
	if (wator[19][1].kind != EMPTY) move(19, 1);
	if (wator[19][2].kind != EMPTY) move(19, 2);
	if (wator[19][3].kind != EMPTY) move(19, 3);
	if (wator[19][4].kind != EMPTY) move(19, 4);
	if (wator[19][5].kind != EMPTY) move(19, 5);
	if (wator[19][6].kind != EMPTY) move(19, 6);
	if (wator[19][7].kind != EMPTY) move(19, 7);
	if (wator[19][8].kind != EMPTY) move(19, 8);
	if (wator[19][9].kind != EMPTY) move(19, 9);
	if (wator[19][10].kind != EMPTY) move(19, 10);
	if (wator[19][11].kind != EMPTY) move(19, 11);
	if (wator[19][12].kind != EMPTY) move(19, 12);
	if (wator[19][13].kind != EMPTY) move(19, 13);
	if (wator[19][14].kind != EMPTY) move(19, 14);
	if (wator[19][15].kind != EMPTY) move(19, 15);
	if (wator[19][16].kind != EMPTY) move(19, 16);
	if (wator[19][17].kind != EMPTY) move(19, 17);
	if (wator[19][18].kind != EMPTY) move(19, 18);
	if (wator[19][19].kind != EMPTY) move(19, 19);
	if (wator[19][20].kind != EMPTY) move(19, 20);
	if (wator[19][21].kind != EMPTY) move(19, 21);
	if (wator[19][22].kind != EMPTY) move(19, 22);
	if (wator[19][23].kind != EMPTY) move(19, 23);
	if (wator[19][24].kind != EMPTY) move(19, 24);
	if (wator[19][25].kind != EMPTY) move(19, 25);
	if (wator[19][26].kind != EMPTY) move(19, 26);
	if (wator[19][27].kind != EMPTY) move(19, 27);
	if (wator[19][28].kind != EMPTY) move(19, 28);
	if (wator[19][29].kind != EMPTY) move(19, 29);
	if (wator[19][30].kind != EMPTY) move(19, 30);
	if (wator[19][31].kind != EMPTY) move(19, 31);
	if (wator[20][0].kind != EMPTY) move(20, 0);
	if (wator[20][1].kind != EMPTY) move(20, 1);
	if (wator[20][2].kind != EMPTY) move(20, 2);
	if (wator[20][3].kind != EMPTY) move(20, 3);
	if (wator[20][4].kind != EMPTY) move(20, 4);
	if (wator[20][5].kind != EMPTY) move(20, 5);
	if (wator[20][6].kind != EMPTY) move(20, 6);
	if (wator[20][7].kind != EMPTY) move(20, 7);
	if (wator[20][8].kind != EMPTY) move(20, 8);
	if (wator[20][9].kind != EMPTY) move(20, 9);
	if (wator[20][10].kind != EMPTY) move(20, 10);
	if (wator[20][11].kind != EMPTY) move(20, 11);
	if (wator[20][12].kind != EMPTY) move(20, 12);
	if (wator[20][13].kind != EMPTY) move(20, 13);
	if (wator[20][14].kind != EMPTY) move(20, 14);
	if (wator[20][15].kind != EMPTY) move(20, 15);
	if (wator[20][16].kind != EMPTY) move(20, 16);
	if (wator[20][17].kind != EMPTY) move(20, 17);
	if (wator[20][18].kind != EMPTY) move(20, 18);
	if (wator[20][19].kind != EMPTY) move(20, 19);
	if (wator[20][20].kind != EMPTY) move(20, 20);
	if (wator[20][21].kind != EMPTY) move(20, 21);
	if (wator[20][22].kind != EMPTY) move(20, 22);
	if (wator[20][23].kind != EMPTY) move(20, 23);
	if (wator[20][24].kind != EMPTY) move(20, 24);
	if (wator[20][25].kind != EMPTY) move(20, 25);
	if (wator[20][26].kind != EMPTY) move(20, 26);
	if (wator[20][27].kind != EMPTY) move(20, 27);
	if (wator[20][28].kind != EMPTY) move(20, 28);
	if (wator[20][29].kind != EMPTY) move(20, 29);
	if (wator[20][30].kind != EMPTY) move(20, 30);
	if (wator[20][31].kind != EMPTY) move(20, 31);
	if (wator[21][0].kind != EMPTY) move(21, 0);
	if (wator[21][1].kind != EMPTY) move(21, 1);
	if (wator[21][2].kind != EMPTY) move(21, 2);
	if (wator[21][3].kind != EMPTY) move(21, 3);
	if (wator[21][4].kind != EMPTY) move(21, 4);
	if (wator[21][5].kind != EMPTY) move(21, 5);
	if (wator[21][6].kind != EMPTY) move(21, 6);
	if (wator[21][7].kind != EMPTY) move(21, 7);
	if (wator[21][8].kind != EMPTY) move(21, 8);
	if (wator[21][9].kind != EMPTY) move(21, 9);
	if (wator[21][10].kind != EMPTY) move(21, 10);
	if (wator[21][11].kind != EMPTY) move(21, 11);
	if (wator[21][12].kind != EMPTY) move(21, 12);
	if (wator[21][13].kind != EMPTY) move(21, 13);
	if (wator[21][14].kind != EMPTY) move(21, 14);
	if (wator[21][15].kind != EMPTY) move(21, 15);
	if (wator[21][16].kind != EMPTY) move(21, 16);
	if (wator[21][17].kind != EMPTY) move(21, 17);
	if (wator[21][18].kind != EMPTY) move(21, 18);
	if (wator[21][19].kind != EMPTY) move(21, 19);
	if (wator[21][20].kind != EMPTY) move(21, 20);
	if (wator[21][21].kind != EMPTY) move(21, 21);
	if (wator[21][22].kind != EMPTY) move(21, 22);
	if (wator[21][23].kind != EMPTY) move(21, 23);
	if (wator[21][24].kind != EMPTY) move(21, 24);
	if (wator[21][25].kind != EMPTY) move(21, 25);
	if (wator[21][26].kind != EMPTY) move(21, 26);
	if (wator[21][27].kind != EMPTY) move(21, 27);
	if (wator[21][28].kind != EMPTY) move(21, 28);
	if (wator[21][29].kind != EMPTY) move(21, 29);
	if (wator[21][30].kind != EMPTY) move(21, 30);
	if (wator[21][31].kind != EMPTY) move(21, 31);
	if (wator[22][0].kind != EMPTY) move(22, 0);
	if (wator[22][1].kind != EMPTY) move(22, 1);
	if (wator[22][2].kind != EMPTY) move(22, 2);
	if (wator[22][3].kind != EMPTY) move(22, 3);
	if (wator[22][4].kind != EMPTY) move(22, 4);
	if (wator[22][5].kind != EMPTY) move(22, 5);
	if (wator[22][6].kind != EMPTY) move(22, 6);
	if (wator[22][7].kind != EMPTY) move(22, 7);
	if (wator[22][8].kind != EMPTY) move(22, 8);
	if (wator[22][9].kind != EMPTY) move(22, 9);
	if (wator[22][10].kind != EMPTY) move(22, 10);
	if (wator[22][11].kind != EMPTY) move(22, 11);
	if (wator[22][12].kind != EMPTY) move(22, 12);
	if (wator[22][13].kind != EMPTY) move(22, 13);
	if (wator[22][14].kind != EMPTY) move(22, 14);
	if (wator[22][15].kind != EMPTY) move(22, 15);
	if (wator[22][16].kind != EMPTY) move(22, 16);
	if (wator[22][17].kind != EMPTY) move(22, 17);
	if (wator[22][18].kind != EMPTY) move(22, 18);
	if (wator[22][19].kind != EMPTY) move(22, 19);
	if (wator[22][20].kind != EMPTY) move(22, 20);
	if (wator[22][21].kind != EMPTY) move(22, 21);
	if (wator[22][22].kind != EMPTY) move(22, 22);
	if (wator[22][23].kind != EMPTY) move(22, 23);
	if (wator[22][24].kind != EMPTY) move(22, 24);
	if (wator[22][25].kind != EMPTY) move(22, 25);
	if (wator[22][26].kind != EMPTY) move(22, 26);
	if (wator[22][27].kind != EMPTY) move(22, 27);
	if (wator[22][28].kind != EMPTY) move(22, 28);
	if (wator[22][29].kind != EMPTY) move(22, 29);
	if (wator[22][30].kind != EMPTY) move(22, 30);
	if (wator[22][31].kind != EMPTY) move(22, 31);
	if (wator[23][0].kind != EMPTY) move(23, 0);
	if (wator[23][1].kind != EMPTY) move(23, 1);
	if (wator[23][2].kind != EMPTY) move(23, 2);
	if (wator[23][3].kind != EMPTY) move(23, 3);
	if (wator[23][4].kind != EMPTY) move(23, 4);
	if (wator[23][5].kind != EMPTY) move(23, 5);
	if (wator[23][6].kind != EMPTY) move(23, 6);
	if (wator[23][7].kind != EMPTY) move(23, 7);
	if (wator[23][8].kind != EMPTY) move(23, 8);
	if (wator[23][9].kind != EMPTY) move(23, 9);
	if (wator[23][10].kind != EMPTY) move(23, 10);
	if (wator[23][11].kind != EMPTY) move(23, 11);
	if (wator[23][12].kind != EMPTY) move(23, 12);
	if (wator[23][13].kind != EMPTY) move(23, 13);
	if (wator[23][14].kind != EMPTY) move(23, 14);
	if (wator[23][15].kind != EMPTY) move(23, 15);
	if (wator[23][16].kind != EMPTY) move(23, 16);
	if (wator[23][17].kind != EMPTY) move(23, 17);
	if (wator[23][18].kind != EMPTY) move(23, 18);
	if (wator[23][19].kind != EMPTY) move(23, 19);
	if (wator[23][20].kind != EMPTY) move(23, 20);
	if (wator[23][21].kind != EMPTY) move(23, 21);
	if (wator[23][22].kind != EMPTY) move(23, 22);
	if (wator[23][23].kind != EMPTY) move(23, 23);
	if (wator[23][24].kind != EMPTY) move(23, 24);
	if (wator[23][25].kind != EMPTY) move(23, 25);
	if (wator[23][26].kind != EMPTY) move(23, 26);
	if (wator[23][27].kind != EMPTY) move(23, 27);
	if (wator[23][28].kind != EMPTY) move(23, 28);
	if (wator[23][29].kind != EMPTY) move(23, 29);
	if (wator[23][30].kind != EMPTY) move(23, 30);
	if (wator[23][31].kind != EMPTY) move(23, 31);
	if (wator[24][0].kind != EMPTY) move(24, 0);
	if (wator[24][1].kind != EMPTY) move(24, 1);
	if (wator[24][2].kind != EMPTY) move(24, 2);
	if (wator[24][3].kind != EMPTY) move(24, 3);
	if (wator[24][4].kind != EMPTY) move(24, 4);
	if (wator[24][5].kind != EMPTY) move(24, 5);
	if (wator[24][6].kind != EMPTY) move(24, 6);
	if (wator[24][7].kind != EMPTY) move(24, 7);
	if (wator[24][8].kind != EMPTY) move(24, 8);
	if (wator[24][9].kind != EMPTY) move(24, 9);
	if (wator[24][10].kind != EMPTY) move(24, 10);
	if (wator[24][11].kind != EMPTY) move(24, 11);
	if (wator[24][12].kind != EMPTY) move(24, 12);
	if (wator[24][13].kind != EMPTY) move(24, 13);
	if (wator[24][14].kind != EMPTY) move(24, 14);
	if (wator[24][15].kind != EMPTY) move(24, 15);
	if (wator[24][16].kind != EMPTY) move(24, 16);
	if (wator[24][17].kind != EMPTY) move(24, 17);
	if (wator[24][18].kind != EMPTY) move(24, 18);
	if (wator[24][19].kind != EMPTY) move(24, 19);
	if (wator[24][20].kind != EMPTY) move(24, 20);
	if (wator[24][21].kind != EMPTY) move(24, 21);
	if (wator[24][22].kind != EMPTY) move(24, 22);
	if (wator[24][23].kind != EMPTY) move(24, 23);
	if (wator[24][24].kind != EMPTY) move(24, 24);
	if (wator[24][25].kind != EMPTY) move(24, 25);
	if (wator[24][26].kind != EMPTY) move(24, 26);
	if (wator[24][27].kind != EMPTY) move(24, 27);
	if (wator[24][28].kind != EMPTY) move(24, 28);
	if (wator[24][29].kind != EMPTY) move(24, 29);
	if (wator[24][30].kind != EMPTY) move(24, 30);
	if (wator[24][31].kind != EMPTY) move(24, 31);
	if (wator[25][0].kind != EMPTY) move(25, 0);
	if (wator[25][1].kind != EMPTY) move(25, 1);
	if (wator[25][2].kind != EMPTY) move(25, 2);
	if (wator[25][3].kind != EMPTY) move(25, 3);
	if (wator[25][4].kind != EMPTY) move(25, 4);
	if (wator[25][5].kind != EMPTY) move(25, 5);
	if (wator[25][6].kind != EMPTY) move(25, 6);
	if (wator[25][7].kind != EMPTY) move(25, 7);
	if (wator[25][8].kind != EMPTY) move(25, 8);
	if (wator[25][9].kind != EMPTY) move(25, 9);
	if (wator[25][10].kind != EMPTY) move(25, 10);
	if (wator[25][11].kind != EMPTY) move(25, 11);
	if (wator[25][12].kind != EMPTY) move(25, 12);
	if (wator[25][13].kind != EMPTY) move(25, 13);
	if (wator[25][14].kind != EMPTY) move(25, 14);
	if (wator[25][15].kind != EMPTY) move(25, 15);
	if (wator[25][16].kind != EMPTY) move(25, 16);
	if (wator[25][17].kind != EMPTY) move(25, 17);
	if (wator[25][18].kind != EMPTY) move(25, 18);
	if (wator[25][19].kind != EMPTY) move(25, 19);
	if (wator[25][20].kind != EMPTY) move(25, 20);
	if (wator[25][21].kind != EMPTY) move(25, 21);
	if (wator[25][22].kind != EMPTY) move(25, 22);
	if (wator[25][23].kind != EMPTY) move(25, 23);
	if (wator[25][24].kind != EMPTY) move(25, 24);
	if (wator[25][25].kind != EMPTY) move(25, 25);
	if (wator[25][26].kind != EMPTY) move(25, 26);
	if (wator[25][27].kind != EMPTY) move(25, 27);
	if (wator[25][28].kind != EMPTY) move(25, 28);
	if (wator[25][29].kind != EMPTY) move(25, 29);
	if (wator[25][30].kind != EMPTY) move(25, 30);
	if (wator[25][31].kind != EMPTY) move(25, 31);
	if (wator[26][0].kind != EMPTY) move(26, 0);
	if (wator[26][1].kind != EMPTY) move(26, 1);
	if (wator[26][2].kind != EMPTY) move(26, 2);
	if (wator[26][3].kind != EMPTY) move(26, 3);
	if (wator[26][4].kind != EMPTY) move(26, 4);
	if (wator[26][5].kind != EMPTY) move(26, 5);
	if (wator[26][6].kind != EMPTY) move(26, 6);
	if (wator[26][7].kind != EMPTY) move(26, 7);
	if (wator[26][8].kind != EMPTY) move(26, 8);
	if (wator[26][9].kind != EMPTY) move(26, 9);
	if (wator[26][10].kind != EMPTY) move(26, 10);
	if (wator[26][11].kind != EMPTY) move(26, 11);
	if (wator[26][12].kind != EMPTY) move(26, 12);
	if (wator[26][13].kind != EMPTY) move(26, 13);
	if (wator[26][14].kind != EMPTY) move(26, 14);
	if (wator[26][15].kind != EMPTY) move(26, 15);
	if (wator[26][16].kind != EMPTY) move(26, 16);
	if (wator[26][17].kind != EMPTY) move(26, 17);
	if (wator[26][18].kind != EMPTY) move(26, 18);
	if (wator[26][19].kind != EMPTY) move(26, 19);
	if (wator[26][20].kind != EMPTY) move(26, 20);
	if (wator[26][21].kind != EMPTY) move(26, 21);
	if (wator[26][22].kind != EMPTY) move(26, 22);
	if (wator[26][23].kind != EMPTY) move(26, 23);
	if (wator[26][24].kind != EMPTY) move(26, 24);
	if (wator[26][25].kind != EMPTY) move(26, 25);
	if (wator[26][26].kind != EMPTY) move(26, 26);
	if (wator[26][27].kind != EMPTY) move(26, 27);
	if (wator[26][28].kind != EMPTY) move(26, 28);
	if (wator[26][29].kind != EMPTY) move(26, 29);
	if (wator[26][30].kind != EMPTY) move(26, 30);
	if (wator[26][31].kind != EMPTY) move(26, 31);
	if (wator[27][0].kind != EMPTY) move(27, 0);
	if (wator[27][1].kind != EMPTY) move(27, 1);
	if (wator[27][2].kind != EMPTY) move(27, 2);
	if (wator[27][3].kind != EMPTY) move(27, 3);
	if (wator[27][4].kind != EMPTY) move(27, 4);
	if (wator[27][5].kind != EMPTY) move(27, 5);
	if (wator[27][6].kind != EMPTY) move(27, 6);
	if (wator[27][7].kind != EMPTY) move(27, 7);
	if (wator[27][8].kind != EMPTY) move(27, 8);
	if (wator[27][9].kind != EMPTY) move(27, 9);
	if (wator[27][10].kind != EMPTY) move(27, 10);
	if (wator[27][11].kind != EMPTY) move(27, 11);
	if (wator[27][12].kind != EMPTY) move(27, 12);
	if (wator[27][13].kind != EMPTY) move(27, 13);
	if (wator[27][14].kind != EMPTY) move(27, 14);
	if (wator[27][15].kind != EMPTY) move(27, 15);
	if (wator[27][16].kind != EMPTY) move(27, 16);
	if (wator[27][17].kind != EMPTY) move(27, 17);
	if (wator[27][18].kind != EMPTY) move(27, 18);
	if (wator[27][19].kind != EMPTY) move(27, 19);
	if (wator[27][20].kind != EMPTY) move(27, 20);
	if (wator[27][21].kind != EMPTY) move(27, 21);
	if (wator[27][22].kind != EMPTY) move(27, 22);
	if (wator[27][23].kind != EMPTY) move(27, 23);
	if (wator[27][24].kind != EMPTY) move(27, 24);
	if (wator[27][25].kind != EMPTY) move(27, 25);
	if (wator[27][26].kind != EMPTY) move(27, 26);
	if (wator[27][27].kind != EMPTY) move(27, 27);
	if (wator[27][28].kind != EMPTY) move(27, 28);
	if (wator[27][29].kind != EMPTY) move(27, 29);
	if (wator[27][30].kind != EMPTY) move(27, 30);
	if (wator[27][31].kind != EMPTY) move(27, 31);
	if (wator[28][0].kind != EMPTY) move(28, 0);
	if (wator[28][1].kind != EMPTY) move(28, 1);
	if (wator[28][2].kind != EMPTY) move(28, 2);
	if (wator[28][3].kind != EMPTY) move(28, 3);
	if (wator[28][4].kind != EMPTY) move(28, 4);
	if (wator[28][5].kind != EMPTY) move(28, 5);
	if (wator[28][6].kind != EMPTY) move(28, 6);
	if (wator[28][7].kind != EMPTY) move(28, 7);
	if (wator[28][8].kind != EMPTY) move(28, 8);
	if (wator[28][9].kind != EMPTY) move(28, 9);
	if (wator[28][10].kind != EMPTY) move(28, 10);
	if (wator[28][11].kind != EMPTY) move(28, 11);
	if (wator[28][12].kind != EMPTY) move(28, 12);
	if (wator[28][13].kind != EMPTY) move(28, 13);
	if (wator[28][14].kind != EMPTY) move(28, 14);
	if (wator[28][15].kind != EMPTY) move(28, 15);
	if (wator[28][16].kind != EMPTY) move(28, 16);
	if (wator[28][17].kind != EMPTY) move(28, 17);
	if (wator[28][18].kind != EMPTY) move(28, 18);
	if (wator[28][19].kind != EMPTY) move(28, 19);
	if (wator[28][20].kind != EMPTY) move(28, 20);
	if (wator[28][21].kind != EMPTY) move(28, 21);
	if (wator[28][22].kind != EMPTY) move(28, 22);
	if (wator[28][23].kind != EMPTY) move(28, 23);
	if (wator[28][24].kind != EMPTY) move(28, 24);
	if (wator[28][25].kind != EMPTY) move(28, 25);
	if (wator[28][26].kind != EMPTY) move(28, 26);
	if (wator[28][27].kind != EMPTY) move(28, 27);
	if (wator[28][28].kind != EMPTY) move(28, 28);
	if (wator[28][29].kind != EMPTY) move(28, 29);
	if (wator[28][30].kind != EMPTY) move(28, 30);
	if (wator[28][31].kind != EMPTY) move(28, 31);
	if (wator[29][0].kind != EMPTY) move(29, 0);
	if (wator[29][1].kind != EMPTY) move(29, 1);
	if (wator[29][2].kind != EMPTY) move(29, 2);
	if (wator[29][3].kind != EMPTY) move(29, 3);
	if (wator[29][4].kind != EMPTY) move(29, 4);
	if (wator[29][5].kind != EMPTY) move(29, 5);
	if (wator[29][6].kind != EMPTY) move(29, 6);
	if (wator[29][7].kind != EMPTY) move(29, 7);
	if (wator[29][8].kind != EMPTY) move(29, 8);
	if (wator[29][9].kind != EMPTY) move(29, 9);
	if (wator[29][10].kind != EMPTY) move(29, 10);
	if (wator[29][11].kind != EMPTY) move(29, 11);
	if (wator[29][12].kind != EMPTY) move(29, 12);
	if (wator[29][13].kind != EMPTY) move(29, 13);
	if (wator[29][14].kind != EMPTY) move(29, 14);
	if (wator[29][15].kind != EMPTY) move(29, 15);
	if (wator[29][16].kind != EMPTY) move(29, 16);
	if (wator[29][17].kind != EMPTY) move(29, 17);
	if (wator[29][18].kind != EMPTY) move(29, 18);
	if (wator[29][19].kind != EMPTY) move(29, 19);
	if (wator[29][20].kind != EMPTY) move(29, 20);
	if (wator[29][21].kind != EMPTY) move(29, 21);
	if (wator[29][22].kind != EMPTY) move(29, 22);
	if (wator[29][23].kind != EMPTY) move(29, 23);
	if (wator[29][24].kind != EMPTY) move(29, 24);
	if (wator[29][25].kind != EMPTY) move(29, 25);
	if (wator[29][26].kind != EMPTY) move(29, 26);
	if (wator[29][27].kind != EMPTY) move(29, 27);
	if (wator[29][28].kind != EMPTY) move(29, 28);
	if (wator[29][29].kind != EMPTY) move(29, 29);
	if (wator[29][30].kind != EMPTY) move(29, 30);
	if (wator[29][31].kind != EMPTY) move(29, 31);
	if (wator[30][0].kind != EMPTY) move(30, 0);
	if (wator[30][1].kind != EMPTY) move(30, 1);
	if (wator[30][2].kind != EMPTY) move(30, 2);
	if (wator[30][3].kind != EMPTY) move(30, 3);
	if (wator[30][4].kind != EMPTY) move(30, 4);
	if (wator[30][5].kind != EMPTY) move(30, 5);
	if (wator[30][6].kind != EMPTY) move(30, 6);
	if (wator[30][7].kind != EMPTY) move(30, 7);
	if (wator[30][8].kind != EMPTY) move(30, 8);
	if (wator[30][9].kind != EMPTY) move(30, 9);
	if (wator[30][10].kind != EMPTY) move(30, 10);
	if (wator[30][11].kind != EMPTY) move(30, 11);
	if (wator[30][12].kind != EMPTY) move(30, 12);
	if (wator[30][13].kind != EMPTY) move(30, 13);
	if (wator[30][14].kind != EMPTY) move(30, 14);
	if (wator[30][15].kind != EMPTY) move(30, 15);
	if (wator[30][16].kind != EMPTY) move(30, 16);
	if (wator[30][17].kind != EMPTY) move(30, 17);
	if (wator[30][18].kind != EMPTY) move(30, 18);
	if (wator[30][19].kind != EMPTY) move(30, 19);
	if (wator[30][20].kind != EMPTY) move(30, 20);
	if (wator[30][21].kind != EMPTY) move(30, 21);
	if (wator[30][22].kind != EMPTY) move(30, 22);
	if (wator[30][23].kind != EMPTY) move(30, 23);
	if (wator[30][24].kind != EMPTY) move(30, 24);
	if (wator[30][25].kind != EMPTY) move(30, 25);
	if (wator[30][26].kind != EMPTY) move(30, 26);
	if (wator[30][27].kind != EMPTY) move(30, 27);
	if (wator[30][28].kind != EMPTY) move(30, 28);
	if (wator[30][29].kind != EMPTY) move(30, 29);
	if (wator[30][30].kind != EMPTY) move(30, 30);
	if (wator[30][31].kind != EMPTY) move(30, 31);
	if (wator[31][0].kind != EMPTY) move(31, 0);
	if (wator[31][1].kind != EMPTY) move(31, 1);
	if (wator[31][2].kind != EMPTY) move(31, 2);
	if (wator[31][3].kind != EMPTY) move(31, 3);
	if (wator[31][4].kind != EMPTY) move(31, 4);
	if (wator[31][5].kind != EMPTY) move(31, 5);
	if (wator[31][6].kind != EMPTY) move(31, 6);
	if (wator[31][7].kind != EMPTY) move(31, 7);
	if (wator[31][8].kind != EMPTY) move(31, 8);
	if (wator[31][9].kind != EMPTY) move(31, 9);
	if (wator[31][10].kind != EMPTY) move(31, 10);
	if (wator[31][11].kind != EMPTY) move(31, 11);
	if (wator[31][12].kind != EMPTY) move(31, 12);
	if (wator[31][13].kind != EMPTY) move(31, 13);
	if (wator[31][14].kind != EMPTY) move(31, 14);
	if (wator[31][15].kind != EMPTY) move(31, 15);
	if (wator[31][16].kind != EMPTY) move(31, 16);
	if (wator[31][17].kind != EMPTY) move(31, 17);
	if (wator[31][18].kind != EMPTY) move(31, 18);
	if (wator[31][19].kind != EMPTY) move(31, 19);
	if (wator[31][20].kind != EMPTY) move(31, 20);
	if (wator[31][21].kind != EMPTY) move(31, 21);
	if (wator[31][22].kind != EMPTY) move(31, 22);
	if (wator[31][23].kind != EMPTY) move(31, 23);
	if (wator[31][24].kind != EMPTY) move(31, 24);
	if (wator[31][25].kind != EMPTY) move(31, 25);
	if (wator[31][26].kind != EMPTY) move(31, 26);
	if (wator[31][27].kind != EMPTY) move(31, 27);
	if (wator[31][28].kind != EMPTY) move(31, 28);
	if (wator[31][29].kind != EMPTY) move(31, 29);
	if (wator[31][30].kind != EMPTY) move(31, 30);
	if (wator[31][31].kind != EMPTY) move(31, 31);
	
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
	}
	return 0;
}
