/*
a C SIMPL receiver
*/

#include <stdio.h>
#include <stdlib.h>
#include <simpl.h>

typedef struct
	{
	char a;
	double b;
	short c;
	char d;
	long e;
	char f;
	float g;
	int h;
	char i[31];
	short k[9];
	int l[9];
	long m[9];
	float n[9];
	double o[7];
	} TESTER;

void printit(void);
char mem[1024];

int main()
{
char *sender;
int n;
int i = 0;

if (name_attach("RECEIVER_B", NULL) == -1)
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

printf("a=%p %c\n", &(out->a), out->a);
printf("b=%p %f\n", &(out->b), out->b);
printf("c=%p %d\n", &(out->c), out->c);
printf("d=%p %c\n", &(out->d), out->d);
printf("e=%p %ld\n", &(out->e), out->e);
printf("f=%p %c\n", &(out->f), out->f);
printf("g=%p %f\n", &(out->g), out->g);
printf("h=%p %d\n", &(out->h), out->h);
printf("i=%p %.31s\n", &(out->i), out->i);
printf("k=%p %d,%d,%d,%d,%d,%d,%d,%d,%d\n", &(out->k), out->k[0], out->k[1],
out->k[2], out->k[3], out->k[4], out->k[5], out->k[6], out->k[7], out->k[8]);
printf("l=%p %d,%d,%d,%d,%d,%d,%d,%d,%d\n", &(out->l), out->l[0], out->l[1],
out->l[2], out->l[3], out->l[4], out->l[5], out->l[6], out->l[7], out->l[8]);
printf("m=%p %ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld\n", &(out->m), out->m[0],
out->m[1], out->m[2], out->m[3], out->m[4], out->m[5], out->m[6], out->m[7],
out->m[8]);
printf("n=%p %f,%f,%f,%f,%f,%f,%f,%f,%f\n", &(out->n), out->n[0], out->n[1],
out->n[2], out->n[3], out->n[4], out->n[5], out->n[6], out->n[7], out->n[8]);
printf("o=%p %f,%f,%f,%f,%f,%f,%f\n", &(out->o), out->o[0], out->o[1],
out->o[2], out->o[3], out->o[4], out->o[5], out->o[6]);
fflush(stdout);
}
