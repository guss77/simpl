/*
A C SIMPL remote receiver getting an integer from an arduino and replying its
doubled value.
*/

#include <stdio.h>
#include <stdlib.h>
#include <simpl.h>

typedef struct
	{
	int num;
	} MSG;

int main()
{
char *sender;
MSG msg;

// SIMPL name attach so that SIMPL senders may name locate
if (name_attach("NUMRECEIVER", NULL) == -1)
	{
	printf("receiver: cannot attach name: %s\n", whatsMyError());
	exit(-1);
	}

// receive and reply forever
while (1)
	{
	// receive a SIMPL message
	if (Receive(&sender, &msg, sizeof(int)) == -1)
		{
		printf("receiver: Receive error: %s\n", whatsMyError());
		exit(-1);
		}

	// double the incoming number
	msg.num <<= 1;

	// reply the result to the sender
	if (Reply(sender, &msg, sizeof(int) == -1))
		{
		printf("receiver: Reply error: %s\n", whatsMyError());
		exit(-1);
		}
	}

return(0);
}
