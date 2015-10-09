#include "XeException.hpp"
#include <stdio.h>
#include <memory>



XeException::XeException(char * _msg) : _msg(_msg)
{
	// Alle Zuweisungen finden in der Initialisiererliste statt
}

XeException::XeException(char * _msg, long _code) : _msg(_msg), _code(_code)
{
	// Alle Zuweisungen finden in der Initialisiererliste statt
}

XeException::XeException(char * _msg, long _code, char * _func, char * _file, __int32 _line) : _code(_code)
{
	// Puffer für die formatierte Nachricht
	char * buf = (char*)malloc(1024);
	// Nachricht vormatieren
	__int32 i = sprintf_s(buf, 1024, "%s in %s in %s in Zeile %d", _msg, _func, _file, _line);
#ifdef _DEBUG
	if (i < 0)
	{
		// Wenn kein Speicher reserviert wurde, Exception werfen
		throw(XeExcNullPtr("Fehler beim Werfen einer Exception wegen Speicherproblemen", -1));
	}
#endif
	// Zuweisen
	this->_msg = buf;
}


XeException::~XeException()
{
}

const char * XeException::what() const
{
	return _msg;
}

const long XeException::code() const
{
	return _code;
}
