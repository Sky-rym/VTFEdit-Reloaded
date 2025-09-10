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
using namespace System::Text::RegularExpressions;

enum EToken
{
	TOKEN_EOF = 0,			// No more tokens to read.
	TOKEN_NEWLINE,			// Token is a newline (\n).
	TOKEN_WHITESPACE,		// Token is any whitespace other than a newline.
	TOKEN_FORWARD_SLASH,	// Token is a forward slash (/).
	TOKEN_QUOTE,			// Token is a quote (").
	TOKEN_OPEN_BRACE,		// Token is an open brace ({).
	TOKEN_CLOSE_BRACE,		// Token is a close brace (}).
	TOKEN_CHAR,				// Token is a char (any char).  Use GetChar().
	TOKEN_STRING,			// Token is a string.  Use GetString().
	TOKEN_SPECIAL			// Token is a specified special char.
};

namespace VTFEdit
{
	public ref class CVMTFileUtility
	{
	public:
		static System::String ^ GetTexturePathFromSystemPath(System::String ^ sTexture)
		{
			if(sTexture->Length == 0)
				return "";

			System::String ^ sExtension = ".vtf";
			System::String ^ sMaterials = "materials";

			sTexture = sTexture->Trim();
			sTexture = sTexture->Replace("\\", "/");
			sTexture = sTexture->Replace("//", "/");
			if(sTexture->Length >= 4 && String::Compare(sTexture, sTexture->Length - sExtension->Length, sExtension, 0, sExtension->Length, true) == 0)
			{
				sTexture = sTexture->Substring(0, sTexture->Length - sExtension->Length);
				sTexture = sTexture->Trim();
			}

			int index = sTexture->IndexOf(":");
			if(index != -1)
			{
				sTexture = sTexture->Substring(index + 1);
			}

			for(int i = 0; i <= sTexture->Length - sMaterials->Length; i++)
			{
				if(String::Compare(sTexture, i, sMaterials, 0, sMaterials->Length, true) == 0)
				{
					sTexture = sTexture->Substring(i + sMaterials->Length);
					i = 0;
				}
			}

			while(sTexture->StartsWith("/"))
			{
				sTexture = sTexture->Substring(1);
			}

			while(sTexture->EndsWith("/"))
			{
				sTexture = sTexture->Substring(0, sTexture->Length - 1);
			}

			return sTexture;
		}

		static bool CreateDefaultMaterial(System::String ^ sVTFFile, System::String ^ sShader)
		{
			return CVMTFileUtility::CreateDefaultMaterial(sVTFFile, sShader, false);
		}

		static bool CreateDefaultMaterial(System::String ^ sVTFFile, System::String ^ sShader, bool bHasAlpha)
		{
			System::String ^ sVMTFile = sVTFFile;

			if(sVMTFile->Length < 4 || String::Compare(sVMTFile, sVMTFile->Length - 4, ".vtf", 0, 4, true) != 0)
			{
				return false;
			}

			sVMTFile = String::Concat(sVMTFile->Substring(0, sVMTFile->Length - 4), ".vmt");

			if(System::IO::File::Exists(sVMTFile))
			{
				return false;
			}

			vlBool bResult;
			char *cTemp0, *cTemp1;
			VTFLib::CVMTFile VMTFile;

			cTemp0 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sShader).ToPointer();
			VMTFile.Create(cTemp0);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp0);

			cTemp0 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi("$basetexture").ToPointer();
			cTemp1 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(CVMTFileUtility::GetTexturePathFromSystemPath(sVTFFile)).ToPointer();
			VMTFile.GetRoot()->AddStringNode(cTemp0, cTemp1);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp1);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp0);

			if(bHasAlpha)
			{
				cTemp0 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi("$translucent").ToPointer();
				VMTFile.GetRoot()->AddIntegerNode(cTemp0, 1);
				System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp0);
			}

			cTemp0 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sVMTFile).ToPointer();
			bResult = VMTFile.Save(cTemp0);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp0);

			return bResult != 0;
		}

		// Tokenizes multi byte tokens.
		// Disabled for performance reasons.
		//ref class CSyntaxHilighter
		//{
		//private:
		//	String ^ sOldText;
		//	System::Windows::Forms::RichTextBox ^ TextBox;

		//public:
		//	CSyntaxHilighter(System::Windows::Forms::RichTextBox ^ TextBox) : sOldText(""), TextBox(TextBox)
		//	{
		//		Enabled = false;
		//	}

		//public:
		//	property bool Enabled;

		//	void Purge()
		//	{
		//		sOldText = "";
		//	}

		//	void Process()
		//	{
		//		if (!this->Enabled)
		//			return;

		//		int iSelectionStart = this->TextBox->SelectionStart;
		//		int iSelectionLength = this->TextBox->SelectionLength;

		//		HWND Handle = (HWND)this->TextBox->Handle.ToPointer();

		//		SendMessage(Handle, WM_SETREDRAW, FALSE, 0);
		//		LRESULT EventMask = SendMessage(Handle, EM_SETEVENTMASK, 0, 0);

		//		POINT ScrollLocation;
		//		SendMessage(Handle, EM_GETSCROLLPOS, 0, (LPARAM)&ScrollLocation);

		//		TextBox->Select(0, TextBox->Text->Length);
		//		array<Int32>^ tabs = gcnew array<Int32>(4);
		//		// Consolas has a font-width of 55%
		//		// The thing is 10px...
		//		tabs[0] = 9 * 4;
		//		for (int i = 1; i < 4; i++)
		//		{
		//			tabs[i] = tabs[0] * (i + 1);
		//		}
		//		TextBox->SelectionTabs = tabs;
		//		
		//		bool quoted = false;
		//		bool key = true;
		//		bool hadCharThisLine = false;
		//		bool comment = false;
		//		char lastChar = '\0';
		//		for (int i = 0; i < TextBox->Text->Length; i++)
		//		{
		//			char character = char(TextBox->Text[i]);
		//			char nextCharacter = char((i + 1) != TextBox->Text->Length ? TextBox->Text[i + 1] : '\0');
		//			bool validQuote = character == '"' && lastChar != '\\';
		//			if (validQuote)
		//				quoted = !quoted;

		//			if ((character == ' ' || character == '\t') && !quoted && hadCharThisLine)
		//				key = !key;

		//			if (character == '\n')
		//			{
		//				hadCharThisLine = false;
		//				key = true;
		//				comment = false;
		//			}

		//			comment |= character == '/' && nextCharacter == '/';

		//			this->TextBox->Select(i, 1);
		//			this->TextBox->SelectionFont = this->TextBox->Font;
		//			if (comment)
		//				this->TextBox->SelectionColor = System::Drawing::Color::FromArgb(181, 189, 104);
		//			else if (character == '{' || character == '}' || validQuote)
		//				this->TextBox->SelectionColor = System::Drawing::Color::FromArgb(197, 200, 198);
		//			else if (key)
		//			{
		//				if (character == '$' && (!hadCharThisLine || (lastChar == '"')))
		//					this->TextBox->SelectionColor = System::Drawing::Color::FromArgb(222, 147, 144);
		//				else if (character == '%' && (!hadCharThisLine || (lastChar == '"')))
		//					this->TextBox->SelectionColor = System::Drawing::Color::FromArgb(138, 190, 183);
		//				else
		//					this->TextBox->SelectionColor = System::Drawing::Color::FromArgb(204, 102, 102);
		//			}
		//			else
		//			{
		//				if (character == '[' || character == ']')
		//					this->TextBox->SelectionColor = System::Drawing::Color::FromArgb(197, 200, 198);
		//				else
		//					this->TextBox->SelectionColor = System::Drawing::Color::FromArgb(129, 162, 190);
		//			}

		//			hadCharThisLine = hadCharThisLine || !(character == ' ' || character == '\t' || character == '\n');

		//			lastChar = character;
		//		}

		//		this->TextBox->Select(iSelectionStart, iSelectionLength);

		//		SendMessage(Handle, EM_SETSCROLLPOS, 0, (LPARAM)&ScrollLocation);

		//		SendMessage(Handle, EM_SETEVENTMASK, 0, EventMask);
		//		SendMessage(Handle, WM_SETREDRAW, TRUE, 0);

		//		RedrawWindow(Handle, NULL, NULL, RDW_INVALIDATE);
		//	}
		//};
	};
}