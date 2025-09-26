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

#define _WIN32_WINNT 0x501
#include <objbase.h>
#include <stdio.h> 

#using <mscorlib.dll>
using namespace System;

#include "stdafx.h"
#include "VTFEdit.h"

[STAThread]
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	Application::EnableVisualStyles();
	Application::DoEvents();

	if(vlGetVersion() != VL_VERSION)
	{
		MessageBox::Show("Invalid VTFLib.dll version number.", Application::ProductName, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
		return 1;
	}

	// Re-enable if Wad conversion is fixed as HLLib is only used for that purpose in this program.
	//if(hlGetInteger(HL_VERSION) != HL_VERSION_NUMBER)
	//{
	//	MessageBox::Show("Invalid HLLib.dll version number.", Application::ProductName, System::Windows::Forms::MessageBoxButtons::OK, //System::Windows::Forms::MessageBoxIcon::Error);
	//	return 1;
	//}

	ILuint uiImage;

	// Initialize DevIL.
	ilInit();

	ilEnable(IL_FILE_OVERWRITE);

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

	ilGenImages(1, &uiImage);
	ilBindImage(uiImage);

	Application::Run(gcnew VTFEdit::CVTFEdit());

	// Shutdown DevIL.
	ilDeleteImages(1, &uiImage);
	ilShutDown();

	return 0;
}