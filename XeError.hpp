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
/* Inhalt		 <Fehlerzubehör für die Laufzeit>										*/
/* ------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------ */

#pragma once

// Fehlercodes
enum XeErrorCodes
{
	XeSuccess =			0x0,	// Alles hat funktioniert
	XeError =			0x1,	// Ein Fehler ist aufgetreten
	XeNullptr =			0x2,	// Ein Nullzeiger wurde verwendet
	XeNotFound =		0x4,	// Element wurde nich gefunden
	XeAbort =			0x5,	// Aktion wurde abgebrochen
	XeArithmeticError = 0x6,	// Mathematischer Fehler
	XeIOError =			0x7,	// Input-Output-Fehler

	XeZeroDevision =	0x50,	// Division durch 0

	XeFileNotFound =	0x60,	// Datei wurde nicht gefunden
	XeBadFilePtr   =    0x61,	// Der Dateizeiger wurde korumpiert
	XeBadProtection =   0x62,	// Die Datei ist geschützt
	XeFileNameChanged = 0x63	// Dateiname wurde verändert
};

// Vorwärtsdeklaration
struct HWND__;
typedef HWND__ *HWND;
typedef unsigned int UINT;

// Windows-Style MessageBoxA mit variabler Argumentanzahl
void xefnc_messagebox(HWND, char*, char*, UINT, ...);

class XeError
{

};
