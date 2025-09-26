/*
 * VTFCmd
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef STDAFX_H
#define STDAFX_H

#if _MSC_VER >= 1400
#	define _CRT_SECURE_NO_WARNINGS
#	define _CRT_NONSTDC_NO_DEPRECATE
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>			// For FindFirstFile()

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "..\lib\VTFLib.h"
#ifdef _DEBUG
#	ifdef _WIN64
#		pragma comment(lib, "../VTFLib/x64/Debug/VTFLib.lib")
#	else
#		pragma comment(lib, "../VTFLib/Win32/Debug/VTFLib.lib")
#	endif
#else
#	ifdef _WIN64
#		pragma comment(lib, "../VTFLib/x64/Release/VTFLib.lib")
#	else
#		pragma comment(lib, "../VTFLib/Win32/Release/VTFLib.lib")
#	endif
#endif

#include "IL\il.h"
#pragma comment(lib, "DevIL.lib")

#endif