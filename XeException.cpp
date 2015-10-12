#include "XeException.hpp"
#include <stdio.h>
#include <memory>



XeException::XeException(char * msg) : _msg(msg)
{
	// Alle Zuweisungen finden in der Initialisiererliste statt
}

XeException::XeException(char * msg, long code) : _msg(msg), _code(code)
{
	// Alle Zuweisungen finden in der Initialisiererliste statt
}

XeException::XeException(char * msg, long code, char * func, char * file, __int32 line) : _msg(msg), _code(code),
_file(file), _func(func)
{
	// Alle Zuweisungen bis auf _line in der Initialisiererliste
	// Für _line Speicher anfordern und den Wert von line zuweisen
	_line = malloc(sizeof(__int32));
	*((__int32*)_line) = line;
}

XeException::XeException(char * msg, long code, char * func, char * file, __int32 line, void ** args) : _msg(msg), _code(code),
_file(file), _func(func), _args(args)
{
	// Alle Zuweisungen bis auf _line in der Initialisiererliste
	// Für _line Speicher anfordern und den Wert von line zuweisen
	_line = malloc(sizeof(__int32));
	*(__int32*)_line = line;
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
