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
#include "MemoryReader.h"

using namespace VTFLib;
using namespace VTFLib::IO::Readers;

CMemoryReader::CMemoryReader(const vlVoid* vData, vlUInt uiBufferSize)
{
	this->bOpened = vlFalse;
	this->uiPointer = 0;

	this->vData = vData;
	this->uiBufferSize = uiBufferSize;
}

CMemoryReader::~CMemoryReader()
{

}

vlBool CMemoryReader::Opened() const
{
	return this->bOpened;
}

vlBool CMemoryReader::Open()
{
	if (vData == 0)
	{
		LastError.Set("Memory stream is null.");
		return vlFalse;
	}

	this->uiPointer = 0;

	this->bOpened = vlTrue;

	return vlTrue;
}

vlVoid CMemoryReader::Close()
{
	this->bOpened = vlFalse;
}

vlUInt CMemoryReader::GetStreamSize() const
{
	if (!this->bOpened)
	{
		return 0;
	}

	return this->uiBufferSize;
}

vlUInt CMemoryReader::GetStreamPointer() const
{
	if (!this->bOpened)
	{
		return 0;
	}

	return this->uiPointer;
}

vlUInt CMemoryReader::Seek(vlLong lOffset, vlUInt uiMode)
{
	if (!this->bOpened)
	{
		return 0;
	}

	switch (uiMode)
	{
	case SEEK_SET:
		this->uiPointer = 0;
		break;
	case SEEK_CUR:

		break;
	case SEEK_END:
		this->uiPointer = this->uiBufferSize;
		break;
	}

	vlLong lPointer = (vlLong)this->uiPointer + lOffset;

	if (lPointer < 0)
	{
		lPointer = 0;
	}

	if (lPointer > (vlLong)this->uiBufferSize)
	{
		lPointer = (vlLong)this->uiBufferSize;
	}

	this->uiPointer = (vlUInt)lPointer;

	return this->uiPointer;
}

vlBool CMemoryReader::Read(vlChar& cChar)
{
	if (!this->bOpened)
	{
		return vlFalse;
	}

	if (this->uiPointer == this->uiBufferSize)
	{
		LastError.Set("End of memory stream.");

		return vlFalse;
	}
	else
	{
		cChar = *((vlChar*)this->vData + this->uiPointer++);

		return vlTrue;
	}
}

vlUInt CMemoryReader::Read(vlVoid* vData, vlUInt uiBytes)
{
	if (!this->bOpened)
	{
		return 0;
	}

	if (this->uiPointer == this->uiBufferSize)
	{
		return 0;
	}
	else if (this->uiPointer + uiBytes > this->uiBufferSize) // This right?
	{
		uiBytes = this->uiBufferSize - this->uiPointer;

		memcpy(vData, (vlByte*)this->vData + this->uiPointer, uiBytes);

		this->uiPointer = this->uiBufferSize;

		LastError.Set("End of memory stream.");

		return uiBytes;
	}
	else
	{
		memcpy(vData, (vlByte*)this->vData + this->uiPointer, uiBytes);

		this->uiPointer += uiBytes;

		return uiBytes;
	}
}