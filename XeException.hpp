#pragma once

class XeException
{
public:
	XeException(char*);
	XeException(char*, long);
	XeException(char*, long, char*, char*, __int32);
	virtual ~XeException();

	virtual const char* what() const;	// Gibt einen Zeiger auf _msg zurück
	virtual const long	code() const;	// Gibt eine Kopie von _code zurück

private:
	long	_code;	// Wenn die Exception an den ErrorHandler weitergegeben wird, entscheidet dieser anhand
					// von _code, wie weiter vorgegangen werden soll
	char*	_msg;	// Nachricht, die eine Beschreibung des Problems beeinhaltet
};

class XeExcBadAlloc : public XeException 
{
public: XeExcBadAlloc(char* p) : XeException(p) {};
public: XeExcBadAlloc(char* p, long l) : XeException(p, l) {};
public: XeExcBadAlloc(char* p1, long l, char* p2, char* p3, __int32 i) : XeException(p1, l, p2, p3, i) {};
};
class XeExcNullPtr : public XeException 
{
public: XeExcNullPtr(char* p) : XeException(p) {};
public: XeExcNullPtr(char* p, long l) : XeException(p, l) {};
public: XeExcNullPtr(char* p1, long l, char* p2, char* p3, __int32 i) : XeException(p1, l, p2, p3, i) {};
};
class XeExcBadFile : public XeException 
{
public: XeExcBadFile(char* p) : XeException(p) {};
public: XeExcBadFile(char* p, long l) : XeException(p, l) {};
public: XeExcBadFile(char* p1, long l, char* p2, char* p3, __int32 i) : XeException(p1, l, p2, p3, i) {};
};

#define XeThrowException(_type, _msg, _code) throw((_type(_msg, _code, __FUNCTION__, __FILE__, __LINE__)));

