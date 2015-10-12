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

// Vorw�rtsdeklaration
class XeErrorHandler;

class XeInterface
{
public:
	XeDll XeInterface();
	XeDll ~XeInterface();
	XeDll static XeInterface* getInterface();

private:
	static XeInterface* _interface;

public:
	XeErrorHandler*     _error_handler;
};
