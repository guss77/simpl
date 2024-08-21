/*
Usage: sender senderName receiverName tokenType(10/20/30)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <simpl.h>

#define LIMIT	1

typedef struct
	{
	int token;
	int var1;
	int var2;
	int var3;
	} OUT1;
	
typedef struct
	{
	int token;
	float var1;
	} OUT2;
	
typedef struct
	{
	int token;
	int var1;
	char var2[34];
	} OUT3;
	
int main(int argc, char **argv)
{
int receiver;
char mem[1024];
int ret;
int i;
int size;
int type;
OUT1 *out1;
OUT2 *out2;
OUT3 *out3;
void *ptr;

if (argc != 4)
	{
	printf("incorrect command line\n");
	exit(-1);
	}

type = atoi(argv[3]);

if (type == 10)
	{
	out1 = (OUT1 *)mem;
	out1->token = 10;
	out1->var1 = 99;
	out1->var2 = 999;
	out1->var3 = 9999;
	ptr = out1;
	size = sizeof(OUT1);
	}
else if (type == 20)
	{
	out2 = (OUT2 *)mem;
	out2->token = 20;
	out2->var1 = 3.1415;
	ptr = out2;
	size = sizeof(OUT2);
	}
else if (type == 30)
	{
	out3 = (OUT3 *)mem;
	out3->token = 30;
	out3->var1 = 34;
	memcpy(out3->var2, "this is the castle of my master...", 34);
	ptr = out3;
	size = sizeof(OUT3);
	}
else
	{
	printf("incorrect command type\n");
	exit(-1);
	}

if (name_attach(argv[1], NULL) == -1)
	{
	printf("cannot attach name: %s\n", whatsMyError());
	exit(-1);
	}

receiver = name_locate(argv[2]);
if (receiver == -1)
	{
	printf("cannot locate receiver: %s\n", whatsMyError());
	exit(-1);
	}

for (i = 1; i <= LIMIT; i++)
	{
	printf("size=%d\n", size);
	ret = Send(receiver, ptr, NULL, size, 0);
	if (ret == -1)
		{
		printf("send error: %s\n", whatsMyError());
		exit(-1);
		}
	}

return(0);
}
