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
#include "MemoryWriter.h"

using namespace VTFLib;
using namespace VTFLib::IO::Writers;

CMemoryWriter::CMemoryWriter(vlVoid* vData, vlUInt uiBufferSize)
{
	this->bOpened = vlFalse;

	this->vData = vData;
	this->uiBufferSize = uiBufferSize;

	this->uiPointer = 0;
	this->uiLength = 0;
}

CMemoryWriter::~CMemoryWriter()
{

}

vlBool CMemoryWriter::Opened() const
{
	return this->bOpened;
}

vlBool CMemoryWriter::Open()
{
	if (vData == 0)
	{
		LastError.Set("Memory stream is null.");
		return vlFalse;
	}

	this->uiPointer = 0;
	this->uiLength = 0;

	this->bOpened = vlTrue;

	return vlTrue;
}

vlVoid CMemoryWriter::Close()
{
	this->bOpened = vlFalse;
}

vlUInt CMemoryWriter::GetStreamSize() const
{
	/*if(!this->bOpened)
	{
		return 0;
	}*/

	return this->uiLength;
}

vlUInt CMemoryWriter::GetStreamPointer() const
{
	if (!this->bOpened)
	{
		return 0;
	}

	return this->uiPointer;
}

vlUInt CMemoryWriter::Seek(vlLong lOffset, vlUInt uiMode)
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
		this->uiPointer = this->uiLength;
		break;
	}

	vlLong lPointer = (vlLong)this->uiPointer + lOffset;

	if (lPointer < 0)
	{
		lPointer = 0;
	}

	if (lPointer > (vlLong)this->uiLength)
	{
		lPointer = (vlLong)this->uiLength;
	}

	this->uiPointer = (vlUInt)lPointer;

	return this->uiPointer;
}

vlBool CMemoryWriter::Write(vlChar cChar)
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
		*((vlChar*)this->vData + this->uiPointer++) = cChar;

		this->uiLength++;

		return vlTrue;
	}
}

vlUInt CMemoryWriter::Write(vlVoid* vData, vlUInt uiBytes)
{
	if (!this->bOpened)
	{
		return 0;
	}

	if (this->uiPointer == this->uiBufferSize)
	{
		return 0;
	}
	else if (this->uiPointer + uiBytes > this->uiBufferSize)
	{
		uiBytes = this->uiBufferSize - this->uiPointer;

		memcpy((vlByte*)this->vData + this->uiPointer, vData, uiBytes);

		this->uiLength += uiBytes;

		this->uiPointer = this->uiBufferSize;

		LastError.Set("End of memory stream.");

		return uiBytes;
	}
	else
	{
		memcpy((vlByte*)this->vData + this->uiPointer, vData, uiBytes);

		this->uiLength += uiBytes;

		this->uiPointer += uiBytes;

		return uiBytes;
	}
}