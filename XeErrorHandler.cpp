#include "XeErrorHandler.hpp"
#include "XeException.hpp"
#include <assert.h>
#include <string>
#include <Windows.h>

XeErrorHandler::XeErrorHandler() : _excnum(0)
{
	// Alle Zuweisungen in der Initialisiererliste
}

XeErrorHandler::~XeErrorHandler()
{
	// TODO:
	// Logfileeintrag schreiben
}

void XeErrorHandler::handle(XeException & exception)
{
	++_excnum;	// Anzahl der gemeldeten Exception erhöhen

	__int32 i = *(__int32*)exception._line;

	switch (exception._code)
	{
	case XeExc_Pass:
	{
		// Nichts weiter machen, ist dazu da,
		// die Exception als "behandelt" zu sehen
		// Anzahl der durchgelassenen Exceptions erhöhen
		++_passnum;
	}break;
	case XeExc_Log:
	{
		// TODO:
		// Eintrag in das Logfile schreiben
		++_excnum;	// Anzahl der gemeldeten Exception erhöhen
	}break;
	case XeExc_Abort:
	{
		// Das Programm beenden
		/* Stringumwandlung */
		size_t cSize1 = strlen(exception._msg) + 1;
		std::wstring wc1(cSize1, L'#');
		mbstowcs_s(&cSize1, &wc1[0], cSize1, exception._msg, cSize1);
		size_t cSize2 = strlen((char*)exception._file) + 1;
		std::wstring wc2(cSize2, L'#');
		mbstowcs_s(&cSize2, &wc2[0], cSize2, (char*)exception._file, cSize2);
		/* Stringumwandlung */
		// Assert
		_wassert(wc1.c_str(), wc2.c_str(), *(unsigned __int32*)exception._line);
	}break;
	case XeExc_Msg:
	{
		MessageBoxA(nullptr, exception._msg, "Exception", MB_OK | MB_ICONWARNING);
		// TODO:
		// 1. Nachricht in Form einer MessageBox ausgeben
		// 2. Eintrag in das Logfile schreiben
	}break;
	case XeExc_Call:
	{
		// TODO:
		// Die Funktion erneut aufrufen
		++_excnum;	// Anzahl der gemeldeten Exception erhöhen
	}break;
	case XeExc_Alloc:
	{
		// TODO:
		// 1. Erneut versuchen, Speicher zu reservieren
		// 2. Eintrag in das Logfile schreiben
		++_excnum;	// Anzahl der gemeldeten Exception erhöhen
	}break;
	case XeExc_Try:
	{
		// TODO:
		// 1. Die Funktion erneut aufrufen
		// 2. Eintrag in das Logbuch schreiben
		++_excnum;	// Anzahl der gemeldeten Exception erhöhen
	}break;
	default:
	{
		++_excnum;	// Anzahl der gemeldeten Exception erhöhen
	}break;
	}

	return;
}
