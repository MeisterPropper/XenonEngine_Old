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
/* Inhalt		 <Interface der XenonEngine>											*/
/* ------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------ */
#pragma once

// Dll-Export
#define XeDll __declspec(dllexport)

// Code zu String
#define NameToString(x)	#x
// Vorwärtsdeklaration
class XeErrorHandler;
class XeLogfile;
class XeClock;

class XeInterface
{
public:
	// Konstruktor
	XeDll XeInterface();
	// Destruktor
	XeDll ~XeInterface();
	// Methode zum Initialisieren der Engine. Liefert einen Zeiger auf den statischen
	// Member _interface zurück, der, wenn er noch nicht initialisiert wurde, hier 
	// wird initialisiert
	XeDll static XeInterface*	getInterface();
	// Fährt die Engine runter. Hierbei wird standardmäßig der Exitcode 0 verwendet.
	// Die Methode sollte nur verwendet werden, wenn es nicht anders geht, da sie das 
	// Zurückkehren aus der main() umgeht
	XeDll void					quit();
	// Gibt einen Zeiger auf _interafce zurück, ohne auf 0 zu überprüfen. Sollte nur von 
	// Engine-internen Funktionen aufgerufen werden, da es sonst zu Fehlern kommen kann
	// WICHTIG: Darf nicht im Konstruktor von XeInterface verwendet werden
	XeDll static XeInterface*	getInterface_internal();
	// Gibt einen konstanten Zeiger auf das Logfile zurück
	XeDll const XeLogfile *		log();
	// Schreibt einen String in das Logfile
	XeDll void					log(const char*);

private:
	static XeInterface* _interface;
	XeLogfile*			_logfile;

public:
	XeErrorHandler*     _error_handler;
	XeClock*			_clock;

private:
	long				pfnc_postinit();
};

