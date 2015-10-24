/* ------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------ */
/* Diese Software wird im �ffentlichen Raum als "wie sie ist" verbreitet. Es wird		*/
/* weder technischer Support gew�hrleistet, noch die vollst�ndige Funktionst�chtigkeit.	*/
/* F�r jeglichen Schaden, der durch die Benutzung dieser Software entsteht, wird keine  */
/* Verantwortung durch den Autor des Quelltextes �bernommen.							*/
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
// Vorw�rtsdeklaration
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
	// Member _interface zur�ck, der, wenn er noch nicht initialisiert wurde, hier 
	// wird initialisiert
	XeDll static XeInterface*	getInterface();
	// F�hrt die Engine runter. Hierbei wird standardm��ig der Exitcode 0 verwendet.
	// Die Methode sollte nur verwendet werden, wenn es nicht anders geht, da sie das 
	// Zur�ckkehren aus der main() umgeht
	XeDll void					quit();
	// Gibt einen Zeiger auf _interafce zur�ck, ohne auf 0 zu �berpr�fen. Sollte nur von 
	// Engine-internen Funktionen aufgerufen werden, da es sonst zu Fehlern kommen kann
	// WICHTIG: Darf nicht im Konstruktor von XeInterface verwendet werden
	XeDll static XeInterface*	getInterface_internal();
	// Gibt einen konstanten Zeiger auf das Logfile zur�ck
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

