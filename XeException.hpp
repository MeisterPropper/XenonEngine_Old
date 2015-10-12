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
/* Inhalt		 <Deklaration von XeException sowie Unterklassen und Exceptioncodes>	*/
/* ------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------ */

#pragma once

// Dll-Export
#define XeDll __declspec(dllexport)

// Vorwärtsdeklaration
class XeErrorHandler;

// Makro für das Werfen von XeExceptions
#define XeThrowException(_type, _msg, _code) throw((_type(_msg, _code, __FUNCTION__, __FILE__, __LINE__)));

class XeException
{
public:
	XeDll XeException(char*);
	XeDll XeException(char*, long);
	XeDll XeException(char*, long, char*, char*, __int32);
	XeDll XeException(char*, long, char*, char*, __int32, void**);
	XeDll virtual ~XeException();

	XeDll virtual const char* what() const;	// Gibt einen Zeiger auf _msg zurück
	XeDll virtual const long  code() const;	// Gibt eine Kopie von _code zurück

private:
	long	_code;	// Wenn die Exception an den ErrorHandler weitergegeben wird, entscheidet dieser anhand
					// von _code, wie weiter vorgegangen werden soll
	char*	_msg;	// Nachricht, die eine Beschreibung des Problems beeinhaltet
	void*   _func;	// Enthält, in welcher Funktion die Exception gewurfen wurde
	void*	_file;	// Enthält, in welcher Datei die Exception gewurfen wurde
	void*   _line;	// Enthält, in welcher Zeile die Exception gewurfen wurde
	void**  _args;	// Zusätzliche Parameter, wie z.B. Zeiger auf Speicher, der
					// alloziert werden soll

	friend class XeErrorHandler;	// Den ErrorHandler als Friend markieren
};

class XeExcBadAlloc : public XeException
{
public: XeDll XeExcBadAlloc(char* p) : XeException(p) {};
public: XeDll XeExcBadAlloc(char* p, long l) : XeException(p, l) {};
public: XeDll XeExcBadAlloc(char* p1, long l, char* p2, char* p3, __int32 i) : XeException(p1, l, p2, p3, i) {};
public: XeDll XeExcBadAlloc(char* p1, long l, char* p2, char* p3, __int32 i, void** pp) : XeException(p1, l, p2, p3, i, pp) {};
};
class XeExcNullPtr : public XeException
{
public: XeDll XeExcNullPtr(char* p) : XeException(p) {};
public: XeDll XeExcNullPtr(char* p, long l) : XeException(p, l) {};
public: XeDll XeExcNullPtr(char* p1, long l, char* p2, char* p3, __int32 i) : XeException(p1, l, p2, p3, i) {};
public: XeDll XeExcNullPtr(char* p1, long l, char* p2, char* p3, __int32 i, void** pp) : XeException(p1, l, p2, p3, i, pp) {};
};
class XeExcBadFile : public XeException
{
public: XeDll XeExcBadFile(char* p) : XeException(p) {};
public: XeDll XeExcBadFile(char* p, long l) : XeException(p, l) {};
public: XeDll XeExcBadFile(char* p1, long l, char* p2, char* p3, __int32 i) : XeException(p1, l, p2, p3, i) {};
public: XeDll XeExcBadFile(char* p1, long l, char* p2, char* p3, __int32 i, void** pp) : XeException(p1, l, p2, p3, i, pp) {};
};

enum XeExceptionCode
{
	XeExc_Pass	= 0x1,	// Lässt das Programm ohne Änderung weiterlaufen 
	XeExc_Log	= 0x2,	// Schreibt in das Logfile
	XeExc_Abort = 0x3,	// Beendet das Programm + Logeintrag
	XeExc_Msg	= 0x4,	// Ruft eine MsgBox auf + Logeintrag
	XeExc_Call	= 0x5,	// Ruft die Funktion erneut auf 
	XeExc_Alloc = 0x6,	// Alloziert erneut Speicher + Logeintrag
	XeExc_Try	= 0x7	// Ruft die Funktion erneut auf + Logeintrag
};


