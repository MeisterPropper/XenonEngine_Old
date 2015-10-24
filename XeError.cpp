#include "XeError.hpp"
#include <Windows.h>
#include <varargs.h>
#include <iostream>

void xefnc_messagebox(HWND hWnd, char* msg, char* title, UINT style, ...)
{
	// Puffer für den fertigen String
	char tmp_buffer[2048];

	// Variable Argumente Liste
	va_list valist;

	// Start der Variablen Argumente
	va_start(valist, style);

	// Den String zusammen setzen
	vsprintf_s(tmp_buffer, msg, valist);

	// Ende der Liste
	va_end(valist);

	// Erstellen der MessageBoxA
	MessageBoxA(hWnd, tmp_buffer, title, style);
}

