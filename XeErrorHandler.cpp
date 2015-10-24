#include "XeErrorHandler.hpp"
#include "XeException.hpp"
#include "XeLogfile.hpp"
#include "XeInterface.hpp"
#include <assert.h>
#include <string>
#include <Windows.h>

XeErrorHandler::XeErrorHandler() : _excnum(0), _passnum(0)
{
	// Alle Zuweisungen in der Initialisiererliste
}

XeErrorHandler::~XeErrorHandler()
{
	// Schlussnachricht in das Logfile schreiben
	const_cast<XeLogfile*>(XeInterface::getInterface_internal()->log())->write("ErrorHandler wird heruntergefahren\n\t\tExceptions insgesamt %d\n\t\tDavon unbehandelt: %d", this->_excnum, this->_passnum);
}

void XeErrorHandler::handle(XeException & exception)
{
	++_excnum;	// Anzahl der gemeldeten Exception erhöhen

	__int32 i = *(__int32*)exception._line;

	switch (exception._code)
	{
	case XeExc_Pass:
	{
		// Nichts weiter machen, Zweck ist,
		// die Exception als "behandelt" zu sehen
		// Anzahl der durchgelassenen Exceptions erhöhen
		++_passnum;
	}break;
	case XeExc_Log:
	{
		// Nachricht in das Logfile
		const_cast<XeLogfile*>(XeInterface::getInterface_internal()->log())->write("Eine Exception %s wurde gewurfen: %s", (char*)exception._type, exception._msg);
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
		// MessageBox
		MessageBoxA(nullptr, exception._msg, "Exception", MB_OK | MB_ICONWARNING);
		// Nachricht in das Logfile schreiben
		const_cast<XeLogfile*>(XeInterface::getInterface_internal()->log())->write("Eine Exception %s wurde gewurfen: %s", (char*)exception._type, exception._msg);
	}break;
	case XeExc_Call:
	{
		// TODO:
		// Die Funktion erneut aufrufen
	}break;
	case XeExc_Alloc:
	{
		// TODO:
		// 1. Erneut versuchen, Speicher zu reservieren
		// Nachricht in das Logfile schreiben
		const_cast<XeLogfile*>(XeInterface::getInterface_internal()->log())->write("Eine Exception %s wurde gewurfen: %s", (char*)exception._type, exception._msg);
	}break;
	case XeExc_Try:
	{
		// TODO:
		// 1. Die Funktion erneut aufrufen
		// Nachricht in das Logfile schreiben
		const_cast<XeLogfile*>(XeInterface::getInterface_internal()->log())->write("Eine Exception %s wurde gewurfen: %s", (char*)exception._type, exception._msg);
		++_excnum;	// Anzahl der gemeldeten Exception erhöhen
	}break;
	default:
	{
		// Nachricht in das Logfile schreiben
		const_cast<XeLogfile*>(XeInterface::getInterface_internal()->log())->write("Eine Exception %s wurde gewurfen: %s", (char*)exception._type, exception._msg);
	}break;
	}

	return;
}
