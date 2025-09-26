/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <vtflib/Error.h>

using namespace VTFLib::Diagnostics;

CError::CError()
{
	this->cErrorMessage = 0;
}

CError::~CError()
{
	delete []this->cErrorMessage;
}

vlVoid CError::Clear()
{
	delete []this->cErrorMessage;
	this->cErrorMessage = 0;
}

const vlChar *CError::Get() const
{
	return this->cErrorMessage != 0 ? this->cErrorMessage : "";
}

vlVoid CError::SetFormatted(const vlChar *cFormat, ...)
{
	vlChar cBuffer[2048];

	va_list ArgumentList;
	va_start(ArgumentList, cFormat);
	vsprintf(cBuffer, cFormat, ArgumentList);
	va_end(ArgumentList);

	this->Set(cBuffer, vlFalse);
}

vlVoid CError::Set(const vlChar *cErrorMessage, vlBool bSystemError)
{
	vlChar cBuffer[2048];
	if(bSystemError)
	{
		LPSTR lpMessage = NULL;
		vlUInt uiLastError = GetLastError(); 

		if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, uiLastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMessage, 0, NULL))
		{
			sprintf(cBuffer, "Error:\n%s\n\nSystem Error: 0x%.8x:\n%s", cErrorMessage, uiLastError, lpMessage); 

			LocalFree(lpMessage);
		}
		else
		{
			sprintf(cBuffer, "Error:\n%s\n\nSystem Error: 0x%.8x.", cErrorMessage, uiLastError); 
		}

		
	}
	else
	{
		sprintf(cBuffer, "Error:\n%s", cErrorMessage); 
	}
	
	this->cErrorMessage = new vlChar[strlen(cBuffer) + 1];
	strcpy(this->cErrorMessage, cBuffer);
}