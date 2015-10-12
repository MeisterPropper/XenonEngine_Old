/* ------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------ */
/* Diese Software wird im öffentlichen Raum als "wie sie ist" verbreitet. Es wird		*/
/* weder technischer Support gewährleistet, noch die vollständige Funktionstüchtigkeit.	*/
/* Für jeglichen Schaden, der durch die Benutzung dieser Software entsteht, wird keine  */
/* Verantwortung durch den Autor des Quelltextes übernommen.							*/
/* Der Quelltext sowie die Software werden unter der 									*/
/* GNU General Public License weitergegeben.											*/
/* ------------------------------------------------------------------------------------ */
/* Copyright (c) <2015 Luc Arne Wengoborski l.wengoborski@web.de>						*/
/* Autor		 <Luc Arne Wengoborski>													*/
/*																						*/
/* Diese Datei ist Teil der Software: XenonEngine										*/
/* Inhalt		 <Implementation des XeErrorHandlers, welcher sich um die Verwaltung	*/
/*				  und Verarbeitung aller geworfenen Exceptions kümmert>					*/
/* ------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------ */

#pragma once

// Dll-Export
#define XeDll __declspec(dllexport)

// Vorwärtsdeklarationen
class XeException;

class XeErrorHandler
{
public:
	XeDll XeErrorHandler();
	XeDll ~XeErrorHandler();
	XeDll void handle(XeException&);

private:
	__int16	_excnum;	// Anzahl der gemeldeten Exceptions
	__int16 _passnum;   // Anzahl der gemeldeten Exceptions mit _code == Exc_Pass

};

#define XeCatch catch(XeException & e){ XeInterface::getInterface()->_error_handler->handle(e); }
