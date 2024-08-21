/*
a C SIMPL sender working with Receiver.java.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char mem1[1024];
char mem2[1024];

void buildMsg(void);
void printit(int);

int main()
{
int receiver;
int ret;

if (name_attach("SENDER", NULL) == -1)
	{
	printf("cannot attach name: %s\n", whatsMyError());
	exit(-1);
	}

receiver = name_locate("RECEIVER");
if (receiver == -1)
	{
	printf("cannot locate receiver: %s\n", whatsMyError());
	exit(-1);
	}

buildMsg();

printf("\nC Sender: sent message  ********************************\n");
printit(1);
printf("**********************************************************\n");

ret = Send(receiver, mem1, mem2, sizeof(TESTER), 1024);
if (ret == -1)
	{
	printf("Send error: %s\n", whatsMyError());
	exit(-1);
	}

printf("C Sender: replied message ********************************\n");
printit(2);
printf("**********************************************************\n");

return(0);
}

void buildMsg()
{
TESTER *ptr = (TESTER *)mem1;

ptr->a = 1;
ptr->b = 80;
ptr->c = 81;
ptr->d = 4;
ptr->e = 82;
ptr->f = 6;
ptr->g = 83;
ptr->h[0] = 66;
ptr->h[1] = 0;
memcpy(ptr->z, "We are the knights who say nee!", 31);
ptr->i = 8;
ptr->j = 9;
ptr->k = 10;
ptr->l = 11;
ptr->m[0] = 77;
ptr->m[1] = 0;
ptr->n = 5;
memcpy(ptr->o, "We", 2);
ptr->p[0] = 97;
ptr->p[1] = 98;
ptr->p[2] = 99;
ptr->p[3] = 100;
ptr->p[4] = 101;
ptr->p[5] = 102;
ptr->p[6] = 103;
ptr->p[7] = 104;
ptr->p[8] = 105;
ptr->p[9] = 106;
ptr->q[0].a[0] = 66;
ptr->q[0].a[1] = 0;
ptr->q[1].a[0] = 67;
ptr->q[1].a[1] = 0;
ptr->q[2].a[0] = 68;
ptr->q[2].a[1] = 0;
ptr->r[0] = 50;
ptr->r[1] = 51;
ptr->r[2] = 52;
ptr->r[3] = 53;
ptr->r[4] = 54;
ptr->r[5] = 55;
ptr->r[6] = 56;
ptr->s[0] = 201;
ptr->s[1] = 301;
ptr->s[2] = 401;
ptr->s[3] = 501;
ptr->s[4] = 601;
ptr->t[0] = -201;
ptr->t[1] = -301;
ptr->t[2] = -401;
ptr->t[3] = -501;
ptr->t[4] = -601;
ptr->u[0] = 10000;
ptr->u[1] = 20000;
ptr->u[2] = 30000;
ptr->v[0] = -200;
ptr->v[1] = -100;
ptr->v[2] =  0;
ptr->v[3] = 100;
ptr->v[4] = 200;
}

void printit(int w)
{
TESTER *ptr;

if (w == 1)
	{
	ptr = (TESTER *)mem1;
	}
else
	{
	ptr = (TESTER *)mem2;
	}


printf("a=%d\n", ptr->a);
printf("b=%c\n", ptr->b);
printf("c=%c\n", ptr->c);
printf("d=%f\n", ptr->d);
printf("e=%c\n", ptr->e);
printf("f=%ld\n", ptr->f);
printf("g=%c\n", ptr->g);
printf("h=%c %c\n", ptr->h[0], ptr->h[1]);
printf("z=%.31s\n", ptr->z);
printf("i=%d\n", ptr->i);
printf("j=%d\n", ptr->j);
printf("k=%ld\n", ptr->k);
printf("l=%f\n", ptr->l);
printf("m=%c %c\n", ptr->m[0], ptr->m[1]);
printf("n=%ld\n", ptr->n);
printf("o=%.2s\n", ptr->o);
printf("p=%c %c %c %c %c %c %c %c %c %c\n", ptr->p[0], ptr->p[1], ptr->p[2],
ptr->p[3], ptr->p[4], ptr->p[5], ptr->p[6], ptr->p[7], ptr->p[8], ptr->p[9]);
printf("q=%c%c %c%c %c%c\n", ptr->q[0].a[0], ptr->q[0].a[1], ptr->q[1].a[0],
ptr->q[1].a[1], ptr->q[2].a[0], ptr->q[2].a[1]);
printf("r=%d,%d,%d,%d,%d,%d,%d\n", ptr->r[0], ptr->r[1], ptr->r[2], ptr->r[3],
ptr->r[4], ptr->r[5], ptr->r[6]);
printf("s=%d,%d,%d,%d,%d\n", ptr->s[0], ptr->s[1], ptr->s[2], ptr->s[3],
ptr->s[4]);
printf("t=%ld,%ld,%ld,%ld,%ld\n", ptr->t[0], ptr->t[1], ptr->t[2], ptr->t[3],
ptr->t[4]);
printf("u=%f,%f,%f\n", ptr->u[0], ptr->u[1], ptr->u[2]);
printf("v=%f,%f,%f,%f,%f\n",  ptr->v[0], ptr->v[1], ptr->v[2], ptr->v[3],
ptr->v[4]);
fflush(stdout);
}
