#include "XeInterface.hpp"
#include "XeException.hpp"


XeInterface::XeInterface()
{
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

	XeThrowException(XeExcBadAlloc, "Hallo", 0x0);
	// Zeiger auf die Instanz zurückgeben
	return _interface;

}


// Statische Variablen
XeInterface* XeInterface::_interface = nullptr;
