#include "XeInterface.hpp"
#include "XeException.hpp"
#include "XeErrorHandler.hpp"
#include <Windows.h>
#include "XeLogfile.hpp"
#include "XeError.hpp"
#include "XeTime.hpp"

XeInterface::XeInterface()
{
	// Engineuhr initialisieren
	_clock = new XeClock();
	// Logfile initialisieren
	_logfile = new XeLogfile("Logs/Tmp.log");
	// Wenn das Logfile nicht initialisiert wurde, 
	// Fehlermeldung ausgeben und beenden
	if (!_logfile)
	{
		xefnc_messagebox(nullptr, "Logfile wurde nicht korrekt initialisiert", "Fehler - XeInterface", MB_OK | MB_ICONERROR);
		this->quit();
	}
	// ErrorHandler initialisieren
	_error_handler = new XeErrorHandler();
	// Wenn der ErrorHandler nicht initialisiert wurde, 
	// Fehlermeldung ausgeben und beenden
	if (!_logfile)
	{
		xefnc_messagebox(nullptr, "ErrorHandler wurde nicht korrekt initialisiert", "Fehler - XeInterface", MB_OK | MB_ICONERROR);
		this->quit();
	}
}


XeInterface::~XeInterface()
{
	// Alle Member löschen
	delete _error_handler;
	_error_handler = nullptr;
	delete _logfile;
	_logfile = nullptr;
	delete _clock;
	_clock = nullptr;
}

XeInterface * XeInterface::getInterface()
{
	// Wenn noch keine Instanz vorhanden ist,
	// eine neue erstellen
	if (!_interface)
	{
		_interface = new XeInterface();
		// Überprüfen
		if (!_interface)
		{
			// Fehler
			xefnc_messagebox(nullptr, "Interface konnte nicht erstellt werden", "Fehler - XeInterface", MB_OK | MB_ICONERROR);
			// Engine herunterfahren
			ExitProcess(0x1);
		}
		// Nachricht in das Log schreiben
		_interface->_logfile->writeStr("XeLogfile wurde vollständig initialisiert...");
		// Nachricht in das Log schreiben
		_interface->_logfile->writeStr("XeErrorHandler wurde vollständig initialisiert...");
		// Wenn alles geklappt hat, Nachricht in das Logfile schreiben
		_interface->_logfile->writeStr("Präinitialisierung abgeschlossen...");

		// Postinitialisierung starten
		if (long res = _interface->pfnc_postinit() != XeSuccess)
		{
			// Postinitialisierung fehlgeschlagen
			
			// Messagebox
			xefnc_messagebox(nullptr, "Interface konnte nicht erstellt werden", "Fehler - XeInterface", MB_OK | MB_ICONERROR);
			// Logeintrag
			_interface->_logfile->write("Postinitialisierung fehlgeschlagen: Fehlercode %d", res);
			// Engine herunterfahren
			ExitProcess(0x1);
		}

		// Initialisierung abgeschlossen
		_interface->_logfile->writeStr("Postinitialisierung abgeschlossen...");
		_interface->_logfile->writeStr("XenonEngine wurde vollständig initialisiert...");
	}

	// Zeiger auf die Instanz zurückgeben
	return _interface;

}

XeDll void XeInterface::quit()
{
	// Schlussnachricht
	_logfile->writeStr("XenonEngine wird heruntergefahren...");
	// Wenn das Interface bereits initialisiert wurde, löschen
	if (_interface)
	{
		// Löschen des Speichers
		delete _interface;
		_interface = nullptr;
	}
	
	ExitProcess(0);
}

XeDll XeInterface * XeInterface::getInterface_internal()
{
	// Zeiger auf _interface zurückgeben
	return _interface;
}

XeDll const XeLogfile *	XeInterface::log()
{
	return this->_logfile;
}

XeDll void XeInterface::log(const char * msg)
{
	// Schreibt msg in das Logfile
	this->_logfile->writeStr(msg);
}

long XeInterface::pfnc_postinit()
{
	return XeSuccess;
}


// Statische Variablen
XeInterface* XeInterface::_interface = nullptr;
