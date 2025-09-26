/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <vtflib/Proc.h>

using namespace VTFLib;

namespace VTFLib
{
	PReadCloseProc pReadCloseProc = 0;
	PReadOpenProc pReadOpenProc = 0;
	PReadReadProc pReadReadProc = 0;
	PReadSeekProc pReadSeekProc = 0;
	PReadSizeProc pReadSizeProc = 0;
	PReadTellProc pReadTellProc = 0;

	PWriteCloseProc pWriteCloseProc = 0;
	PWriteOpenProc pWriteOpenProc = 0;
	PWriteWriteProc pWriteWriteProc = 0;
	PWriteSeekProc pWriteSeekProc = 0;
	PWriteSizeProc pWriteSizeProc = 0;
	PWriteTellProc pWriteTellProc = 0;
}

VTFLIB_API vlVoid vlSetProc(VLProc Proc, vlVoid *pProc)
{
	switch(Proc)
	{
	case PROC_READ_CLOSE:
		pReadCloseProc = (PReadCloseProc)pProc;
		break;
	case PROC_READ_OPEN:
		pReadOpenProc = (PReadOpenProc)pProc;
		break;
	case PROC_READ_READ:
		pReadReadProc = (PReadReadProc)pProc;
		break;
	case PROC_READ_SEEK:
		pReadSeekProc = (PReadSeekProc)pProc;
		break;
	case PROC_READ_SIZE:
		pReadSizeProc = (PReadSizeProc)pProc;
		break;
	case PROC_READ_TELL:
		pReadTellProc = (PReadTellProc)pProc;
		break;
	case PROC_WRITE_CLOSE:
		pWriteCloseProc = (PWriteCloseProc)pProc;
		break;
	case PROC_WRITE_OPEN:
		pWriteOpenProc = (PWriteOpenProc)pProc;
		break;
	case PROC_WRITE_WRITE:
		pWriteWriteProc = (PWriteWriteProc)pProc;
		break;
	case PROC_WRITE_SEEK:
		pWriteSeekProc = (PWriteSeekProc)pProc;
		break;
	case PROC_WRITE_SIZE:
		pWriteSizeProc = (PWriteSizeProc)pProc;
		break;
	case PROC_WRITE_TELL:
		pWriteTellProc = (PWriteTellProc)pProc;
		break;
	}
}

VTFLIB_API vlVoid *vlGetProc(VLProc Proc)
{
	switch(Proc)
	{
	case PROC_READ_CLOSE:
		return pReadCloseProc;
	case PROC_READ_OPEN:
		return pReadOpenProc;
	case PROC_READ_READ:
		return pReadReadProc;
	case PROC_READ_SEEK:
		return pReadSeekProc;
	case PROC_READ_SIZE:
		return pReadSizeProc;
	case PROC_READ_TELL:
		return pReadTellProc;
	case PROC_WRITE_CLOSE:
		return pWriteCloseProc;
	case PROC_WRITE_OPEN:
		return pWriteOpenProc;
	case PROC_WRITE_WRITE:
		return pWriteWriteProc;
	case PROC_WRITE_SEEK:
		return pWriteSeekProc;
	case PROC_WRITE_SIZE:
		return pWriteSizeProc;
	case PROC_WRITE_TELL:
		return pWriteTellProc;
	default:
		return 0;
	}
}