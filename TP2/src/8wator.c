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
		return ((i+MAXI-1) & 0x1F);  // X % 32
	case SOUTH:
		return ((i+1) & 0x1F); // x % 32
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
		return ((j+MAXJ-1) & 0x1F ); // x % 32
	case WEST:
		return ((j+1) & 0x1F ); // x % 32
	default:
		assert (0);
	}
	return -1;
}

int newcount = 0;

void new_animal (struct animal* t , char kind)
{
	assert (t->kind == EMPTY); 
	assert ((kind - FISH == 0) || (kind - SHARK == 0));
	t->kind = kind;
	t->age = 0;
	t->hunger = 0;
	t->todo = 0;
	++newcount;
}

inline int myrand (int max)
{
	//return rand () % max;
	return ( (max & 0x01) ? (rand() % max)  : (rand() & (max-1)) );
}

int choose_fish (int i, int j)
{
	register int k = 0;
	register int dir = 0;
	int dirs[4];
	
	//primer ciclo, dir = 0 => NORTH
	register struct animal * t = &wator[((i+MAXI-1) & 0x1F )][j];
	if (t->kind - FISH == 0)
		dirs[k++] = dir;

	//segundo ciclo, dir = 1 => SOUTH
	++dir;
 	t = &wator[((i+1) & 0x1F )][j];
	if (t->kind - FISH == 0) 
		dirs[k++] = dir;

	//tercer ciclo, dir = 2 => EAST
	++dir;
	t = &wator[i][((j+MAXJ-1) & 0x1F )];
	if (t->kind - FISH == 0) 
		dirs[k++] = dir;

	//cuarto ciclo, dir = 3 => WEST
	++dir;
	t = &wator[i][((j+1) & 0x1F )];
	if (t->kind - FISH == 0) 
		dirs[k++] = dir;
			
//	if (k == 0)
//		return REST;
//	return dirs[myrand (k)];
	return ((k==0) ? REST : dirs[myrand(k)] );
}

int choose_empty (int i, int j)
{
	register int k = 0;
	register int dir = 0;
	int dirs[4];
	
	//primer ciclo, dir = 0 => NORTH
	register struct animal * t = &wator[((i+MAXI-1) & 0x1F )][j];
	if (t->kind == EMPTY )
		dirs[k++] = dir;

	//segundo ciclo, dir = 1 => SOUTH
	++dir;
	t = &wator[((i+1) & 0x1F )][j];
	if (t->kind == EMPTY )
		dirs[k++] = dir;

	//tercer ciclo, dir = 2 => EAST
	++dir;
	t = &wator[i][((j+MAXJ-1) & 0x1F )];
	if (t->kind == EMPTY )
		dirs[k++] = dir;

	//cuarto ciclo, dir = 3 => WEST
	++dir;
	t = &wator[i][((j+1) & 0x1F )];
	if (t->kind == EMPTY )
		dirs[k++] = dir;

	//if (k == 0)
	//	return REST;
	//return dirs[myrand (k)];
	return ((k==0) ? REST : dirs[myrand(k)]);
}

int freecount = 0;

int move_to_fish (struct animal* t, int i, int j)
{
	register int dir;
	assert (t->kind - SHARK == 0);

	dir = choose_fish(i, j);
	if (dir - REST == 0)
		return 0;

    	register struct animal * s = &wator[ ni(i, dir) ][ nj(j, dir) ];
	assert (s->kind - FISH == 0);
	++freecount;
	
	memcpy  (s, t, sizeof(animal));
	t->kind = EMPTY;
	s->hunger = 0;
	
	if (s->age - HBRUT >= 0) {
		t->age = 0;
		new_animal(t, SHARK);
	}
	return 1;
}

int move_to_empty (struct animal* t ,int i, int j)
{
	register int dir;

	assert ((t->kind - SHARK == 0) || (t->kind - FISH == 0)); 

	dir = choose_empty(i, j);
	if (dir - REST == 0)
		return 0;
	
	register struct animal * s = &wator[ ni(i, dir) ][ nj(j, dir) ];

	assert (s->kind == 0 );
	memcpy(s, t, sizeof(animal));
	t->kind = EMPTY;
	
	if ((s->kind - FISH == 0) && (s->age - FBRUT >= 0)) {
		s->age = 0;
		new_animal (t, FISH);
	}
	if ((s->kind - SHARK == 0) && (s->age - HBRUT >= 0)) {
		s->age = 0;
		new_animal (t, SHARK);
	}
	return 1;
}

void move (struct animal* t, int i, int j)
{
	assert ((t->kind - SHARK == 0) || (t->kind - FISH == 0));

	t->age++;
	if (t->kind - SHARK == 0) {
		t->hunger++;
		if (t->hunger - FASTEN >= 0) {
			t->kind = EMPTY;
			++freecount;
			return;
		}
		if (move_to_fish (t, i, j))
			return;
	}
	move_to_empty (t, i, j);
}

int fd = -1;

void show_wator ()
{
	register int i, j, kind;
	register int shark = 0, fish = 0;
	
	register struct animal *v = &(wator[0][0]);
	
	for (i=0; i<MAXI; ++i) {
		for (j=0; j<MAXJ; ++j) {
			kind = v->kind;
			if ( kind ) {  // kind != EMPTY
				if (kind - SHARK == 0) {  // kind == SHARK
					printf ("X");
					++shark;
				} else {
					printf ("*");
					++fish;
				}
			} else {
				printf (".");
			}
		
			v++;
		
		}
		printf ("\n");
	}
	printf ("SHARKS: %d, FISH: %d NEW: %d, FREE: %d\n\n", shark, fish, newcount, freecount);
	if (fd >= 0) {
		char buf[100];
		int ret;
		static int tick = 0;
		sprintf (buf, "%d %d %d\n", tick, shark, fish);
		++tick;
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
	register int i, j, res;
	register struct animal *v = &(wator[0][0]);

	HBRUT = hbrut;
	FBRUT = fbrut;
	FASTEN = fasten;
	assert (hbrut - FASTEN> 0);

 	for (i=0; i<MAXI; ++i) {
		for (j=0; j<MAXJ; ++j) {
			res = myrand (30);
			v->kind = EMPTY;
			switch (res) {
			case 0:
				new_animal ( v ,SHARK);//i, j, SHARK);
				break;
			case 1 ... 11:
				new_animal ( v ,FISH);//i, j, FISH);
				break;
			}
			
			v++;
		}
	}
}

void moveall ()
{
	int i, j;
	struct animal * v = &(wator[0][0]);

	for (i=0; i<MAXI; ++i) {
		for (j=0; j<MAXJ; ++j) {
			if ( v->kind ) {  // kind != EMPTY
				move ( v, i,j);
			}
			v++;
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
	for (i=0;i<1000;++i) {
		moveall ();
		show_wator ();
	}
	return 0;
}
