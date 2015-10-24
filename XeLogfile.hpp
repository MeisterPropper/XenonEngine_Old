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
/* Inhalt		 <Implementation der XeLogfile-Klasse, die für das Speichern von			*/
/*			      Meldungen im Logfile verantwortlich ist>								*/
/* ------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------ */

#pragma once

#include <fstream>

// Dll-Export
#define XeDll __declspec(dllexport)

const __int16 XeLogBufferSize1k = 1024;
const __int16 XeLogBufferSize2k = 2048;
const __int16 XeLogBufferSize4k = 4096;
const __int16 XeLogBufferSize8k = 8192;

const __int16 XeLogBufferSize = XeLogBufferSize4k; // Die Puffergröße, die verwendet werden soll

class XeLogfile
{
public:
	XeDll XeLogfile(const char* );
	XeDll ~XeLogfile();

	// Schreibt einen String in das Logfile
	XeDll void writeStr(const char*);
	// Schreibt einen String sowie beliebig viele Zusätzliche
	// Argumente in das Logfile
	XeDll void write(const char*, ...);


private:
	char _buffer[XeLogBufferSize];	// Puffer, der erst in die Datei geschrieben wird, 
									// wenn er voll ist
	char*	_path;					// Der Pfad zum Logfile
	FILE*	_fileptr;				// Der Zeiger auf die Datei
	__int16 _bufsize;				// Menge der Zeichen im Puffer

private:
	XeDll void pfnc_clearbuffer();
	XeDll void pfnc_writebuffer();
	XeDll long pfnc_checkpath(const char*);
};


