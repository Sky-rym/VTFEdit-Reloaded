/*
 * VTFEdit
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

#pragma once

#include "stdafx.h"

using namespace System;

namespace VTFEdit
{
	public ref class CUtility
	{
	public:
		static void StringToCharPointer(String ^ sString, char *cString, int iLength)
		{
			char *cTemp;

			cTemp = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sString)).ToPointer();

			strncpy_s(cString, iLength, cTemp, iLength);
			cString[iLength - 1]= '\0';

			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp);
		}
	};
}