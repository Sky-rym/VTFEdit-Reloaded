/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VTFDXTN_H
#define VTFDXTN_H

#include "stdafx.h"

//-----------------------------------------------------------------------------
//
// VTFDXTn.h - contains structures and definitions used in dealing with DXTn
// compressed image data.
// 
// Much of this code is based on examples on Microsofts website and from the
// Developers Image Library (http://www.imagelib.org) (c) Denton Woods.
//
//-----------------------------------------------------------------------------

// RGBA Pixel type
typedef struct Colour8888
{
	vlByte r;		// change the order of names to change the 
	vlByte g;		// order of the output ARGB or BGRA, etc...
	vlByte b;		// Last one is MSB, 1st is LSB.
	vlByte a;
} Colour8888;

// RGB Pixel type
typedef struct Colour888
{
	vlByte r;		// change the order of names to change the 
	vlByte g;		// order of the output ARGB or BGRA, etc...
	vlByte b;		// Last one is MSB, 1st is LSB.
} Colour888;

// BGR565 Pixel type
typedef struct Colour565
{
	vlUInt nBlue	: 5;		// order of names changes
	vlUInt nGreen	: 6;		// byte order of output to 32 bit
	vlUInt nRed		: 5;
} Colour565;

// DXTn Colour block type
typedef struct DXTColBlock
{
	vlShort col0;
	vlShort col1;
	vlChar	row[4];		// no bit fields - use bytes
} DXTColBlock;

// DXTn Alpha block types
typedef struct DXTAlphaBlockExplicit
{
	vlShort row[4];
} DXTAlphaBlockExplicit;

typedef struct DXTAlphaBlock3BitLinear
{
	vlChar alpha0;
	vlChar alpha1;
	vlChar stuff[6];
} DXTAlphaBlock3BitLinear;

#endif // VTFDXTN_H