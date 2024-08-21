// remReceiver.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <simpl.h>

#define TCP_PROXY	5
#define TCP_X_PROXY	999

char mem[1024];

int main(int argc, char **argv)
{
const char *me = "remoteReceiver";
char *sender;
int n;
int proxyValue;

if (name_attach(argv[1], NULL) == -1)
	{
	printf("%s: cannot attach name-%s\n", me, whatsMyError());
	exit(-1);
	}

while (1)
	{
	n = Receive(&sender, mem, 1024);
	if (n == -1)
		{
		printf("%s: Receive error-%s\n", me, whatsMyError());
		exit(-1);
		}

	if (n < -1)
		{
		// proxy
		proxyValue = returnProxy(n);

		switch (proxyValue)
			{
			case TCP_PROXY: 
				printf("%s: TCP proxy\n", me);
				break;
		
			case TCP_X_PROXY: 
				printf("%s: TCP_X proxy\n", me);
				break;

			default:
				printf("%s: unknown proxy\n", me);
				exit(-1);
			}
		}
	else
		{
		printf("%s: received message size %d\n", me, n);
	
		if (Reply(sender, mem, n) == -1)
			{
			printf("%s: Reply error-%s\n", me, whatsMyError());
			exit(-1);
			}
		}
	}

return(0);
}
