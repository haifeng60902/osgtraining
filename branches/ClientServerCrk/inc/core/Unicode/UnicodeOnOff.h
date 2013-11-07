#ifndef _UNICODE_ON_OFF_H
#define _UNICODE_ON_OFF_H

#include <io.h>
#include <fcntl.h>

class UnicodeOnOff
{
public:
	UnicodeOnOff()
	{
		//for output Unicode text purpose
		_setmode(_fileno(stdout), _O_WTEXT);	//_O_WTEXT	_O_TEXT
	};
	~UnicodeOnOff()
	{
		//for output ansi text purpose
		_setmode(_fileno(stdout), _O_TEXT);	//_O_WTEXT	_O_TEXT
	}
};

#endif	_UNICODE_ON_OFF_H