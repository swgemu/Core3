/*************************************************************************\
* LOGGING FUNCTIONS                                                       *
*-------------------------------------------------------------------------*
* This are just some temporary log functions. We can replace them or      *
* leave them. Just like you want it.                                      *
*                                                                         *
* log.h - last updated on 19th May 2005 by ProfEich                       *
\*************************************************************************/

//------------------------------------------------------------------
// Defining parameters for the flags
//------------------------------------------------------------------
#define LOG_NO_OUTPUT			0x00					// Doesn't save anything into a file
#define LOG_CORE_SERVER		0x01					// Save to the LoginServer file
//#define LOG_CHARACTER_SERVER	0x02					// Save to the CharServer file
//#define LOG_FATAL_ERRORS		0x0F					// Save to the Errors file

#define LOG_NO_TIMESTAMP		0x20					// Don't add the timestamp to the line
#define LOG_PRINT				0x40					// Print the message into the console
#define LOG_NO_NEWROW			0x80					// Don't add a NEWLINE char at the end

extern unsigned char LOG_THISSERVER;					// Save to the current server logfile.

//------------------------------------------------------------------
// This should be replaced by a variable in a config file, later
//------------------------------------------------------------------
#ifdef WIN32
#define LOG_DIRECTORY "logs/"
#else
#define LOG_DIRECTORY "./log/"
#endif

//------------------------------------------------------------------
// Log filenames
//------------------------------------------------------------------
#define LOG_FILENAME_COREFILE  "zoneserver.log"
//#define LOG_FILENAME_CHARFILE   "charserver.log"
//#define LOG_FILENAME_ERRORFILE  "errors.log"

//------------------------------------------------------------------
// Logging function
//------------------------------------------------------------------
void Log( unsigned char Flags, void *Reserved, char *Format, ... );
//Examples:
//Log( LOG_PRINT | LOG_NO_OUTPUT, NULL, "Starting Server...");
//Log( LOG_PRINT | LOG_CORE_SERVER, NULL, "Server Sucsessfully Stopped.");

//------------------------------------------------------------------
