#pragma once

enum ErrCode
{
	EC_Success		=	0, // Success
	EC_Quit			=	1, // WM_QUIT was in message loop (application exiting)

	EC_EOutOfMemory	=	5, // Out of memory

	EC_NoDir		=	10, // The directory doesn't exist

	EC_ParsingXML	=	15, // Error parsing the XML string
	EC_WritingXML	=	16, // Error writing the XML string

	EC_NoValue		=	25, // Generic error, no additional description available

	EC_IO			=	30, // Error performing an I/O operation
};
