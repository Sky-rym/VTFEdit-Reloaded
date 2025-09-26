/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef FILEREADER_H
#define FILEREADER_H

#include "stdafx.h"
#include "Reader.h"

namespace VTFLib
{
	namespace IO
	{
		namespace Readers
		{
			class CFileReader : public IReader
			{
			private:
				HANDLE hFile;
				vlChar *cFileName;

			public:
				CFileReader(const vlChar *cFileName);
				~CFileReader();

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