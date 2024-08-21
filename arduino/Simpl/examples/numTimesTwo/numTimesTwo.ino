/*
This is a very straightforward example of a SIMPL sender that merely sends a
long integer number to a remote SIMPL receiver replies the doubled number.The
receiver program provided was written in C. Note that the receiver program could
be written in Python, Tcl, Java or some other language which supports SIMPL.
Also note that realistic messages are usually more complex and contain various
data types like characters, floating point numbers, strings and so on.
*/

#include <SPI.h>
#include <Ethernet.h>
#include <Simpl.h>

// structure definition of the received/replied message
typedef struct
  {
  long num;
  } MY_MSG;

EthernetClient client;
long receiverId;

void setup()
{
const unsigned port = 8000;
char *serverName = "www.icanprogram.ca";
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x0D, 0x77};

// start serial messaging to a local monitor 
Serial.begin(9600);
Serial.println();
Serial.println("starting up");

// start ethernet
if (!Ethernet.begin(mac))
  {
  Serial.println("error on ethernet");
  while(1);
  }

// give the ethernet shield hardware an opportunity to initialize
delay(1000);

// remotely SIMPL name attach to the designated server and port
if (nameAttach(serverName, port, &client, "SENDER") == -1)
  {
  Serial.println(whatsMyError());
  client.stop();
  while(1);
  }

// remotely SIMPL name locate the receiver process desired for messaging
receiverId = nameLocate(&client, "NUMRECEIVER");
if (receiverId == -1)
  {
  Serial.println(whatsMyError());
  nameDetach(&client);
  client.stop();
  while(1);
  }

Serial.println("Initialization is complete.");
}

void loop()
{
int ret;
MY_MSG msg;

// send numbers 1-100 and receive their doubled value
for (int i = 1; i <= 100; i++)
  {
  msg.num = i;
  ret = Send(&client, &receiverId, &msg, &msg, sizeof(MY_MSG), sizeof(MY_MSG)); 
  if (ret == -1)
    {
    Serial.println(whatsMyError());
    break;
    }
  
  Serial.print("sent ");
  Serial.println(i);
  Serial.print("received ");
  Serial.println(msg.num);
  } 

// disconnect from the remote host
nameDetach(&client);
Serial.println("program finished ... going to spin now");
while(1);
}
