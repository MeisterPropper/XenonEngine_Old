#include "XeLogfile.hpp"
#include "XeException.hpp"
#include "XeInterface.hpp"
#include "XeErrorHandler.hpp"
#include <Windows.h>
#include "XeError.hpp"
#include <varargs.h>
#include "XeTime.hpp"

XeLogfile::XeLogfile(const char * ppath)
{
	//XeClock clock;

	// Überprüfen, ob der Pfad existiert
	if (pfnc_checkpath(ppath))
	{	
		// Wenn nicht, dann einen gültigen zuweisen
		_path = "Logs/Log.xelog";
	}
	else
	{
		// Länge von ppath ermitteln
		size_t tmp_len = strlen(ppath);

		// Speicher reservieren
		_path = (char*)malloc(strlen(ppath) + 1);

		// Zuweisung
		strcpy_s(_path, strlen (ppath) + 1, ppath);
	}

	// Datei öffnen
	fopen_s(&_fileptr, _path, "w");

	// Überfrüfung
	if (!_fileptr)
	{
		// Datei konnte nich geöffnet werden
		xefnc_messagebox(nullptr, "Die Logfiledatei konnte nicht geöffnet werden: %s", "Fehler - Logfile 1. Chance", MB_OK | MB_ICONERROR, _path);
		// Zweiter Versuch - Datei öffnen
		fopen_s(&_fileptr, _path, "w");
		// Überfrüfung - 2. Chance
		if (!_fileptr)
		{
			xefnc_messagebox(nullptr, "Die Logfiledatei konnte nicht geöffnet werden: %s\nProgramm wird beendet", "Fehler - Logfile 2. Chance", MB_OK | MB_ICONERROR, _path);
			// Engine herunterfahren
			XeInterface::getInterface_internal()->quit();
		}
	}
}

XeLogfile::~XeLogfile()
{
	// Den Puffer in die Datei schreiben
	pfnc_writebuffer();

	// Logfile schließen
	fclose(_fileptr);
}

XeDll void XeLogfile::writeStr(const char * msg)
{
	// Länge des Strings zwischenspeichern
	// Länge der Nachricht + Länge der Uhrzeit + Nullterminierung
	size_t tmp_len = strlen(msg) + strlen(XeInterface::getInterface_internal()->_clock->toString("[%H:%M:%S]").c_str()) + 1;

	// **String zusammensetzen** 

	// Puffer erstellen
	char* msg_buffer = (char*)malloc(tmp_len);

	// Zusammensetzen
	sprintf_s(msg_buffer, tmp_len, "%s%s", XeInterface::getInterface_internal()->_clock->toString("[%H:%M:%S]").c_str(), msg);

	// Überprüfen, ob der String in den Puffer passt
	if (_bufsize + tmp_len > XeLogBufferSize4k)
	{
		if (tmp_len > XeLogBufferSize4k)
		{
			// Wenn der String insgesamt zu lang für den Buffer ist,
			// dann muss er direkt in die Datei geschrieben werden
			fwrite(msg_buffer, sizeof(char), tmp_len, _fileptr);
		}
		else
		{
			// Wenn der Puffer zu klein ist, dann muss er geleert werden
			pfnc_writebuffer();
		}
	}

	// Wenn alles in den Puffer passt, dann in den Puffer übertragen
	memcpy_s(&_buffer[_bufsize], XeLogBufferSize4k, msg_buffer, tmp_len);

	// Neue Länge des Puffers eintragen 
	_bufsize += static_cast<__int16>(tmp_len);
}

XeDll void XeLogfile::write(const char * msg, ...)
{
	// Länge des Strings zwischenspeichern
	// Länge der Nachricht + Länge der Uhrzeit + Nullterminierung
	size_t tmp_len = strlen(msg) + strlen(XeInterface::getInterface_internal()->_clock->toString("[%H:%M:%S]").c_str()) + 1;

	// Puffer erstellen
	char* msg_buffer = (char*)malloc(tmp_len);

	// Zusammensetzen
	sprintf_s(msg_buffer, tmp_len, "%s%s", XeInterface::getInterface_internal()->_clock->toString("[%H:%M:%S]").c_str(), msg);

	// Puffer erstellen
	char* tmp_buffer = (char*)malloc(8096);

	// Liste der variablen Argumente
	va_list valist;
	// Anfang der Liste
	va_start(valist, msg);
	// Den String in den Puffer schreiben
	vsprintf_s(tmp_buffer, 8096, msg_buffer, valist);
	// Ende der Liste
	va_end(valist);

	// Länge des Strings zwischenspeichern
	tmp_len = strlen(tmp_buffer) + 1;

	// Überprüfen, ob der String in den Puffer passt
	if (_bufsize + tmp_len > XeLogBufferSize4k)
	{
		if (tmp_len > XeLogBufferSize4k)
		{
			// Wenn der String insgesamt zu lang für den Buffer ist,
			// dann muss er direkt in die Datei geschrieben werden
			fwrite(tmp_buffer, sizeof(char), tmp_len, _fileptr);
		}
		else
		{
			// Wenn der Puffer zu klein ist, dann muss er geleert werden
			pfnc_writebuffer();
		}
	}

	// Wenn alles in den Puffer passt, dann in den Puffer übertragen
	memcpy_s(&_buffer[_bufsize], XeLogBufferSize4k, tmp_buffer, tmp_len);

	// Neue Länge des Puffers eintragen 
	_bufsize += static_cast<__int16>(tmp_len);

	// Speicher freigeben
	free(msg_buffer);
	free(tmp_buffer);
}

void XeLogfile::pfnc_clearbuffer()
{
	for (__int16 iterator = 0; iterator != XeLogBufferSize; ++iterator)
	{
		// Puffer mit Nullen füllen
		_buffer[iterator] = (char)0;
	}
}

void XeLogfile::pfnc_writebuffer()
{
	// Puffer nach Nullterminierungen durchsuchen
	for (__int16 iterator = 0; iterator != _bufsize; ++iterator)
	{
		// Wenn eine Nullterminierung gefunden wurde, durch Newline ersetzen
		if (_buffer[iterator] == (char)0)
		{
			_buffer[iterator] = '\n';
		}
	}
	// Puffer in das Logfile schreiben
	fwrite(&_buffer[0], sizeof(char), _bufsize, _fileptr);
	// _bufsize wieder auf 0 setzen
	_bufsize = 0;
	// Puffer leeren
	pfnc_clearbuffer();
}

long XeLogfile::pfnc_checkpath(const char* ppath)
{
	return XeSuccess;
}
