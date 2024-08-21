#ifndef _SIMPL_H
#define _SIMPL_H

#define COMM_TIMEOUT	500 // 500 ms delay in testing for client availability
#define COMM_TRY		10	// times to look for client availability
#define	CONNECT_TRY		10	// times to try for a socket connection
#define	MAX_NAME_LEN	19	// max simpl name length for name attaching/locating

// tclSurrogate message tokens
typedef enum
	{
	SG_NAME_ATTACH,
	SG_NAME_DETACH,
	SG_NAME_LOCATE,
	SG_SEND_IT,
	SG_REPLY_IT,
	SG_RELAY_IT,
	MAX_TOKENS
	} SG_TOKEN;

// message to tclSurrogate used for remote name attach
typedef struct
	{
	unsigned short token;
	unsigned short nbytes;
	long whom;
	char myName[MAX_NAME_LEN + 1];
	long myPid;
	long mySlot;
	} SG_NAME_ATTACH_MSG;

// message to tclSurrogate used for name name detach
typedef struct
	{
	unsigned short token;
	unsigned short nbytes;
	} SG_NAME_DETACH_MSG;


// message to tclSurrogate used for name locating remote process
typedef struct
	{
	unsigned short token;
	unsigned short nbytes;
	long whom;
	char thisName[MAX_NAME_LEN + 1];
	long rc;
	} SG_NAME_LOCATE_MSG;

// header of messages for send/receive/reply
typedef struct
	{
	unsigned short token;
	unsigned short nbytes;
	long whom;
	}SG_MSG;

// function protoypes
int nameAttach(char *, unsigned, EthernetClient *, char *);
int nameDetach(EthernetClient *);
long nameLocate(EthernetClient *, char *);
int Send(EthernetClient *, long *, void *, void *, unsigned, unsigned);
int Receive(EthernetClient *, long *, void *, unsigned);
int Reply(EthernetClient *, long *, void *, unsigned);
char *whatsMyError(void);
int commDelay(EthernetClient *client);

// a useful string for reporting program failures/info
#ifdef PRIMARY
char simpl_errstr[80] = "No error.";
#else
extern char *simpl_errstr;
#endif

#endif

