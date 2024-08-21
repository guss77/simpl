/*
This is an example of a C-based simpl receiver
*/

#include <stdio.h>
#include <stdlib.h>
#include <simpl.h>

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
	
int main()
{
char *sender;
char mem[1024];
int n;
OUT1 *in1;
OUT2 *in2;
OUT3 *in3;
int *token;

if (name_attach("receiver", NULL) == -1)
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
		continue;
		}
	
	token = (int *)mem;
	
	switch (*token)
		{
		case 10:
			in1 = (OUT1 *)mem;		
			printf("token=%d var1=%d var2=%d var3=%d\n",
				in1->token,
				in1->var1,
				in1->var2,
				in1->var3);
			break;

		case 20:
			in2 = (OUT2 *)mem;		
			printf("token=%d var1=%f\n",
				in2->token,
				in2->var1);
			break;

		case 30:
			in3 = (OUT3 *)mem;		
			printf("token=%d var1=%d var2=%32s\n",
				in3->token,
				in3->var1,
				in3->var2);
			break;

		default:
			printf("unknown token=%d\n", *token);

		}

	Reply(sender, NULL, 0);
	}

return(0);
}
