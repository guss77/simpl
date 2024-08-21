/*
a C SIMPL receiver working with Sender1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <simpl.h>

typedef union
	{
	signed char a[2];
	short b;
	} NEE;

typedef struct
	{
	short a;
	char b;
	char c;
	double d;
	char e;
	long f;
	char g;
	char h[2];
	char z[31];
	short i;
	int j;
	long k;
	float l;
	char m[2];
	long n;
	char o[2];
	char p[10];
	NEE q[3];
	short r[7];
	int s[5];
	long t[5];
	float u[3];
	double v[5];
	} TESTER;

void printit(void);
char mem[1024];

int main()
{
char *sender;
int n;
int i = 0;

if (name_attach("RECEIVER", NULL) == -1)
	{
	printf("receiver: cannot attach name: %s\n", whatsMyError());
	exit(-1);
	}

while (1)
	{
	n = Receive(&sender, mem, 1024);
	if (n == -1)
		{
		printf("receiver: Receive error: %s\n", whatsMyError());
		exit(-1);
		}

	printf("\nReceiver: received message %d size=%d\n", ++i, n);
	printit();
	printf("***********************************************************\n");

	if (Reply(sender, mem, n) == -1)
		{
		printf("receiver: Reply error: %s\n", whatsMyError());
		exit(-1);
		}
	}

return(0);
}

void printit()
{
TESTER *out = (TESTER *)mem;

printf("a=%p %d\n", &(out->a), out->a);
printf("b=%p %c\n", &(out->b), out->b);
printf("c=%p %c\n", &(out->c), out->c);
printf("d=%p %f\n", &(out->d), out->d);
printf("e=%p %c\n", &(out->e), out->e);
printf("f=%p %ld\n", &(out->f), out->f);
printf("g=%p %c\n", &(out->g), out->g);
printf("h=%p %c %c\n", &(out->h), out->h[0], out->h[1]);
printf("z=%p %.31s\n", &(out->z), out->z);
printf("i=%p %d\n", &(out->i), out->i);
printf("j=%p %d\n", &(out->j), out->j);
printf("k=%p %ld\n", &(out->k), out->k);
printf("l=%p %f\n", &(out->l), out->l);
printf("m=%p %c %c\n", &(out->m), out->m[0], out->m[1]);
printf("n=%p %ld\n", &(out->n), out->n);
printf("o=%p %.2s\n", &(out->o), out->o);
printf("p=%p %c %c %c %c %c %c %c %c %c %c\n", &(out->p), out->p[0],
out->p[1], out->p[2], out->p[3], out->p[4], out->p[5], out->p[6], out->p[7],
out->p[8], out->p[9]);
printf("q=%p %c%c %c%c %c%c\n", &(out->q), out->q[0].a[0], out->q[0].a[1],
out->q[1].a[0], out->q[1].a[1], out->q[2].a[0], out->q[2].a[1]);
printf("r=%p %d,%d,%d,%d,%d,%d,%d\n", &(out->r), out->r[0], out->r[1],
out->r[2], out->r[3], out->r[4], out->r[5], out->r[6]);
printf("s=%p %d,%d,%d,%d,%d\n", &(out->s), out->s[0], out->s[1],
out->s[2], out->s[3], out->s[4]);
printf("t=%p %ld,%ld,%ld,%ld,%ld\n", &(out->t), out->t[0], out->t[1],
out->t[2], out->t[3], out->t[4]);
printf("u=%p %f,%f,%f\n", &(out->u), out->u[0], out->u[1], out->u[2]);
printf("v=%p %f,%f,%f,%f,%f\n", &(out->v), out->v[0], out->v[1], out->v[2],
out->v[3], out->v[4]);
fflush(stdout);
}
