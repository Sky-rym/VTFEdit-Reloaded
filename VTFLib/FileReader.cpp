/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include "VTFLib.h"
#include "FileReader.h"

using namespace VTFLib;
using namespace VTFLib::IO::Readers;

CFileReader::CFileReader(const vlChar* cFileName)
{
	this->hFile = NULL;

	this->cFileName = new vlChar[strlen(cFileName) + 1];
	strcpy(this->cFileName, cFileName);
}

CFileReader::~CFileReader()
{
	this->Close();

	delete[]this->cFileName;
}

vlBool CFileReader::Opened() const
{
	return this->hFile != NULL;
}

vlBool CFileReader::Open()
{
	this->Close();

	this->hFile = fopen(this->cFileName, "rb"); // CreateFile(this->cFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (!this->hFile)
	{
		this->hFile = NULL;

		LastError.Set("Error opening file.", vlTrue);

		return vlFalse;
	}

	return vlTrue;
}

vlVoid CFileReader::Close()
{
	if (this->hFile != NULL)
	{
		fclose(this->hFile);
		this->hFile = NULL;
	}
}

vlUInt CFileReader::GetStreamSize() const
{
	if (this->hFile == NULL)
	{
		return 0;
	}

	long oldpos = ftell(this->hFile);
	fseek(this->hFile, 0, SEEK_END);
	long pos = ftell(this->hFile);
	fseek(this->hFile, oldpos, SEEK_SET);
	return pos;
}

vlUInt CFileReader::Seek(vlLong lOffset, vlUInt uiMode)
{
	if (this->hFile == NULL)
	{
		return 0;
	}

	fseek(this->hFile, lOffset, uiMode);
	return ftell(this->hFile);
}

vlBool CFileReader::Read(vlChar& cChar)
{
	if (this->hFile == NULL)
	{
		return vlFalse;
	}

	size_t numRead = fread(&cChar, sizeof(vlChar), 1, this->hFile);

	if (numRead != 1)
	{
		LastError.Set("fread() failed.", vlTrue);
	}

	return numRead == 1;
}

vlUInt CFileReader::Read(vlVoid* vData, vlUInt uiBytes)
{
	if (this->hFile == NULL)
	{
		return 0;
	}

	size_t numRead = fread(vData, uiBytes, 1, this->hFile);

	if (numRead != 1)
	{
		LastError.Set("fread() failed.", vlTrue);
	}

	return numRead * uiBytes;
}