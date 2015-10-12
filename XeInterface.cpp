#include "XeInterface.hpp"
#include "XeException.hpp"
#include "XeErrorHandler.hpp"


XeInterface::XeInterface()
{
	// ErrorHandler initialisieren
	_error_handler = new XeErrorHandler();
}


XeInterface::~XeInterface()
{
}

XeInterface * XeInterface::getInterface()
{
	// Wenn noch keine Instanz vorhanden ist,
	// eine neue erstellen
	if (!_interface)
	{
		_interface = new XeInterface();
	}

	// Zeiger auf die Instanz zurückgeben
	return _interface;

}


// Statische Variablen
XeInterface* XeInterface::_interface = nullptr;
