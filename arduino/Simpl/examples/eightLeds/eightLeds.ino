/*
Turn on/off each of a bank of eight LEDs according to a message received from
a remote sender program. Note that the sender program may be a program written
in C, Tcl, Python, PHP, Java or any other language/platform that supports SIMPL.
*/

#include <SPI.h>
#include <Ethernet.h>
#include <Simpl.h>

// message token definition
#define BRINKY_RITE  0

// structure definition of the received/replied message
typedef struct
  {
  unsigned short token; // message token indicating what to do
  unsigned char state; // state of the LEDs; on/off
  } MSG;

EthernetClient client;

void setup()
{
const unsigned port = 8000; // port that the tclSurrogate is waiting on
char *serverName = "www.icanprogram.ca"; // host where tclSurrogate lives
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x0D, 0x77}; // ethernet MAC address

// start serial messaging
Serial.begin(9600);
Serial.println();
Serial.println("starting up");

// start ethernet
if (!Ethernet.begin(mac))
  {
  Serial.println("error on ethernet");
  while(1);
  }

// give the ethernet shield a chance to initialize
delay(1000);

// remotely SIMPL name attach the name "ARDUINO" to designated server
if (nameAttach(serverName, port, &client, "ARDUINO") == -1)
  {
  Serial.println(whatsMyError());
  client.stop();
  while(1);
  }
  
// initialize the digital pins as an output
for (int ledPin = 2; ledPin <= 9; ledPin++)
  {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  }
delay(3000);
for (int ledPin = 2; ledPin <= 9; ledPin++)
  {
  digitalWrite(ledPin, LOW);
  }
Serial.println("Initialization complete.");
}

void loop()
{
long senderId;	        // the unique id of the sending program
MSG msg;        	// incoming/outgoing message variable
int ret;	        // function return value
unsigned char state;	// 8 led state masking variable

// check for an incoming message
ret = Receive(&client, &senderId, &msg, sizeof(MSG));
if (ret == -1) // problem
  {
  Serial.println(whatsMyError());
  nameDetach(&client);
  while(1);
  }
else if (ret > 0) // incoming message
  {
  // reply instantly to the remote sender	
 // if (Reply(&client, &senderId, &msg, sizeof(MSG)) == -1)
  if (Reply(&client, &senderId, NULL, 0) == -1)
     {
    Serial.println(whatsMyError());
    nameDetach(&client);
    while(1);
    }

  // check the message token for veracity
  if (msg.token != BRINKY_RITE)
    {
    Serial.println("Incorrect msg token");
    nameDetach(&client);
    while(1);
    }
  
  // set the blinky lights according to the message state variable
  for (int ledPin = 2, state = 1; ledPin <= 9; ledPin++, state <<= 1)
    {
    digitalWrite(ledPin, msg.state & state);
    }
  }
else
  {
   // 0 returned ==> nothing pending so carry on looping
  }
}

