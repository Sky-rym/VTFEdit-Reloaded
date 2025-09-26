/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef PROCREADER_H
#define PROCREADER_H

#include "stdafx.h"
#include "Reader.h"

namespace VTFLib
{
	namespace IO
	{
		namespace Readers
		{
			class CProcReader : public IReader
			{
			private:
				vlBool bOpened;
				vlVoid *pUserData;

			public:
				CProcReader(vlVoid *pUserData);
				~CProcReader();

			public:
				virtual vlBool Opened() const;

				virtual vlBool Open();
				virtual vlVoid Close();

				virtual vlUInt GetStreamSize() const;
				virtual vlUInt GetStreamPointer() const;

				virtual vlUInt Seek(vlLong lOffset, vlUInt uiMode);

				virtual vlBool Read(vlChar &cChar);
				virtual vlUInt Read(vlVoid *vData, vlUInt uiBytes);
			};
		}
	}
}

#endif