#pragma once

class XeInterface
{
public:
	XeInterface();
	~XeInterface();
	static XeInterface* getInterface();

private:
	static XeInterface* _interface;
};

