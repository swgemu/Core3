/*************************************************************************\
* LOGGING FUNCTIONS                                                       *
*-------------------------------------------------------------------------*
* This are just some temporary log functions. We can replace them or      *
* leave them. Just like you want it.                                      *
*                                                                         *
* log.cpp - last updated on 19th May 2005 by ProfEich                     *
\*************************************************************************/
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include "log.h"

unsigned char LOG_THISSERVER = 0;

//-----------------------------------------------------------------------------------------
// This private function opens a log file, depending on the given flags
//-----------------------------------------------------------------------------------------
FILE *lgOpenLogFile( unsigned char Flags )
{
	FILE *fh = NULL;
	
	// Open needed file for logging.
	switch ( Flags & 0x0F )
	{
	case LOG_CORE_SERVER:
		fh = fopen( LOG_DIRECTORY LOG_FILENAME_COREFILE,  "a+" );
		break;
	/*case LOG_CHARACTER_SERVER:
		fh = fopen( LOG_DIRECTORY LOG_FILENAME_CHARFILE,   "a+" );
		break;*/
	/*case LOG_FATAL_ERRORS:
		fh = fopen( LOG_DIRECTORY LOG_FILENAME_ERRORFILE,  "a+" );
		break;*/
	}
	
	return fh;
}

//-----------------------------------------------------------------------------------------
// This private functions adds time and date to the file/console
//-----------------------------------------------------------------------------------------
void lgSaveTimeStamp( FILE *fh, unsigned char Flags )
{
	// Get time/date and write it to the beginning of the row
	time_t rawtime;							// For time
	struct tm* timeinfo;					//    "
	char *timestr;

	time	  ( &rawtime );
	timeinfo  = localtime( &rawtime );
	timestr   = asctime( timeinfo );

	timestr[24] = '\0';

	if ( fh != NULL )			fprintf ( fh, "%s: ", timestr );
	if ( Flags & LOG_PRINT )	printf( "%s: ", timestr );
}

//-----------------------------------------------------------------------------------------
// This function logs a line depending on the flags.
//-----------------------------------------------------------------------------------------
void Log( unsigned char Flags, void *Reserved, char *Format, ... )
{
	va_list ap;						// For arguments
	
	FILE *fh = lgOpenLogFile( Flags );
	
	// Add timestamp to the file
	if ( !(Flags & LOG_NO_TIMESTAMP) )
		lgSaveTimeStamp( fh, Flags );
	
	// Write informations in file
	va_start( ap, Format );
	
	if ( fh != NULL )			vfprintf( fh, Format, ap );
	if ( Flags & LOG_PRINT )	vprintf( Format, ap );
	
	va_end  ( ap );
	
	// Jump to next row, if wanted
	if ( (Flags & LOG_NO_NEWROW) == 0 )
	{
		if ( fh != NULL )			fputc( '\n', fh );
		if ( Flags & LOG_PRINT )	printf("\n");
	}
	
	// Close file
	if ( fh != NULL ) fclose( fh );
}

//-----------------------------------------------------------------------------------------

