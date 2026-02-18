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
#include "FileWriter.h"

using namespace VTFLib;
using namespace VTFLib::IO::Writers;

CFileWriter::CFileWriter(const vlChar* cFileName)
{
	this->hFile = NULL;

	this->cFileName = new vlChar[strlen(cFileName) + 1];
	strcpy(this->cFileName, cFileName);
}

CFileWriter::~CFileWriter()
{
	this->Close();

	delete[]this->cFileName;
}

vlBool CFileWriter::Opened() const
{
	return this->hFile != NULL;
}

vlBool CFileWriter::Open()
{
	this->Close();

	this->hFile = fopen(this->cFileName, "wb");

	if (this->hFile == NULL)
	{
		LastError.Set("Error opening file.", vlTrue);
		return vlFalse;
	}
	return vlTrue;
}

vlVoid CFileWriter::Close()
{
	if (this->hFile != NULL)
	{
		fclose(this->hFile);
		this->hFile = NULL;
	}
}

vlUInt CFileWriter::GetStreamSize() const
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

vlUInt CFileWriter::Seek(vlLong lOffset, vlUInt uiMode)
{
	if (this->hFile == NULL)
	{
		return 0;
	}

	fseek(this->hFile, lOffset, uiMode);
	return ftell(this->hFile);
}

vlBool CFileWriter::Write(vlChar cChar)
{
	if (this->hFile == NULL)
	{
		return vlFalse;
	}

	size_t numWritten = fwrite(&cChar, sizeof(vlChar), 1, this->hFile);
	if (numWritten != 1)
	{
		LastError.Set("fwrite() failed.", vlTrue);
	}

	return numWritten == 1;
}

vlUInt CFileWriter::Write(vlVoid* vData, vlUInt uiBytes)
{
	if (this->hFile == NULL)
	{
		return 0;
	}

	size_t numWritten = fwrite(vData, uiBytes, 1, this->hFile);
	if (numWritten != 1)
	{
		LastError.Set("WriteFile() failed.", vlTrue);
	}

	return numWritten * uiBytes;
}