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
/* Inhalt		 <Klassen und Funktionen für Zeit>										*/
/* ------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------ */

#include <chrono>
#include <time.h>
#include <string>

#pragma once

// Dll-Export
#define XeDll __declspec(dllexport)

// Typedef
typedef struct tm XeTime;

class XeClock
{
public:
	// Konstruktor
	XeDll XeClock();
	// Destruktor
	XeDll ~XeClock();

	// Aktualisiert die Uhr
	XeDll time_t		updateTime();
	// Wandelt die Uhrzeit in einen String vom Format
	// [Stunde:Minute:Sekunde] um
	XeDll std::string	toString();
	// Wandelt die Uhrzeit in einen Benutzerdefinierten String um
	XeDll std::string	toString(char*);


private:
	std::chrono::system_clock			_sys_clock;		// Systemuhr
	std::chrono::steady_clock			_steady_clock;	// Statische Uhr
	std::chrono::high_resolution_clock	_hr_clock;		// Uhr mit hoher präzision
	time_t								_time;			// Zeit in Sek seit Greenwich
	XeTime								_tm;			// Struktur mit allen Daten zu Uhrzeit und 
														// Datum

};


