/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef READER_H
#define READER_H

#include "stdafx.h"

namespace VTFLib
{
	namespace IO
	{
		namespace Readers
		{
			class IReader
			{
			public:
				virtual vlBool Opened() const = 0;

				virtual vlBool Open() = 0;
				virtual vlVoid Close() = 0;

				virtual vlUInt GetStreamSize() const = 0;
				virtual vlUInt GetStreamPointer() const = 0;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode) = 0;

				virtual vlBool Read(vlChar &cChar) = 0;
				virtual vlUInt Read(vlVoid *vData, vlUInt uiBytes) = 0;
			};
		}
	}
}

#endif