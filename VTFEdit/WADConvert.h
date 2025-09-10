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
#include "VTFOptions.h"
#include "VMTCreate.h"
#include "VMTFileUtility.h"
#include "VTFFileUtility.h"
#include <string>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace VTFEdit
{
	public ref class CWADConvert : public System::Windows::Forms::Form
	{
	private:
		CVTFOptions ^Options;
	private: System::Windows::Forms::Label^ lblProgress;

		   CVMTCreate^ VMTOptions;

	public: 
		CWADConvert(CVTFOptions ^Options, CVMTCreate ^VMTOptions)
		{
			this->Options = Options;
			this->VMTOptions = VMTOptions;

			this->InitializeComponent();
		}

	public: System::String^ VMTShader;
	private: System::Windows::Forms::GroupBox ^  grpOptions;
	private: System::Windows::Forms::Button ^  btnConvert;
	private: System::Windows::Forms::GroupBox ^  grpProgress;
	private: System::Windows::Forms::Label ^  lblWADFile;
	private: System::Windows::Forms::TextBox ^  txtWADFile;
	private: System::Windows::Forms::Button ^  btnWADFileBrowse;
	private: System::Windows::Forms::Button ^  btnOutputFolderBrowse;
	private: System::Windows::Forms::TextBox ^  txtOutputFolder;
	private: System::Windows::Forms::Label ^  lblOutputFolder;
	private: System::Windows::Forms::ProgressBar ^  barProgress;
	private: System::Windows::Forms::OpenFileDialog ^  dlgOpenWADFile;
	private: System::Windows::Forms::FolderBrowserDialog ^  dlgOpenFolder;
	private: System::Windows::Forms::Button ^  btnOptions;
	private: System::Windows::Forms::GroupBox ^  grpLog;
	private: System::Windows::Forms::RichTextBox ^  txtLog;
	private: System::Windows::Forms::Button ^  btnClose;
	private: System::Windows::Forms::CheckBox ^  chkCreateVMTFiles;
	private: System::Windows::Forms::ToolTip ^  tipMain;
	private: System::Windows::Forms::Button^ btnVMTOptions;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CWADConvert::typeid));
			this->grpOptions = (gcnew System::Windows::Forms::GroupBox());
			this->chkCreateVMTFiles = (gcnew System::Windows::Forms::CheckBox());
			this->btnOutputFolderBrowse = (gcnew System::Windows::Forms::Button());
			this->txtOutputFolder = (gcnew System::Windows::Forms::TextBox());
			this->lblOutputFolder = (gcnew System::Windows::Forms::Label());
			this->btnWADFileBrowse = (gcnew System::Windows::Forms::Button());
			this->txtWADFile = (gcnew System::Windows::Forms::TextBox());
			this->lblWADFile = (gcnew System::Windows::Forms::Label());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->btnConvert = (gcnew System::Windows::Forms::Button());
			this->grpProgress = (gcnew System::Windows::Forms::GroupBox());
			this->barProgress = (gcnew System::Windows::Forms::ProgressBar());
			this->dlgOpenWADFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->dlgOpenFolder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->btnOptions = (gcnew System::Windows::Forms::Button());
			this->grpLog = (gcnew System::Windows::Forms::GroupBox());
			this->txtLog = (gcnew System::Windows::Forms::RichTextBox());
			this->tipMain = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->btnVMTOptions = (gcnew System::Windows::Forms::Button());
			this->lblProgress = (gcnew System::Windows::Forms::Label());
			this->grpOptions->SuspendLayout();
			this->grpProgress->SuspendLayout();
			this->grpLog->SuspendLayout();
			this->SuspendLayout();
			// 
			// grpOptions
			// 
			this->grpOptions->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpOptions->Controls->Add(this->chkCreateVMTFiles);
			this->grpOptions->Controls->Add(this->btnOutputFolderBrowse);
			this->grpOptions->Controls->Add(this->txtOutputFolder);
			this->grpOptions->Controls->Add(this->lblOutputFolder);
			this->grpOptions->Controls->Add(this->btnWADFileBrowse);
			this->grpOptions->Controls->Add(this->txtWADFile);
			this->grpOptions->Controls->Add(this->lblWADFile);
			this->grpOptions->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpOptions->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->grpOptions->Location = System::Drawing::Point(6, 6);
			this->grpOptions->Name = L"grpOptions";
			this->grpOptions->Size = System::Drawing::Size(370, 76);
			this->grpOptions->TabIndex = 2;
			this->grpOptions->TabStop = false;
			this->grpOptions->Text = L"Options:";
			// 
			// chkCreateVMTFiles
			// 
			this->chkCreateVMTFiles->Checked = true;
			this->chkCreateVMTFiles->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkCreateVMTFiles->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkCreateVMTFiles->Location = System::Drawing::Point(80, 55);
			this->chkCreateVMTFiles->Name = L"chkCreateVMTFiles";
			this->chkCreateVMTFiles->Size = System::Drawing::Size(101, 19);
			this->chkCreateVMTFiles->TabIndex = 6;
			this->chkCreateVMTFiles->Text = L"Create &VMT Files";
			this->tipMain->SetToolTip(this->chkCreateVMTFiles, L"Generate .vmt files for .vtf files. Ouput folder should be a material folder.");
			// 
			// btnOutputFolderBrowse
			// 
			this->btnOutputFolderBrowse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnOutputFolderBrowse->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnOutputFolderBrowse->Location = System::Drawing::Point(346, 36);
			this->btnOutputFolderBrowse->Name = L"btnOutputFolderBrowse";
			this->btnOutputFolderBrowse->Size = System::Drawing::Size(15, 16);
			this->btnOutputFolderBrowse->TabIndex = 5;
			this->btnOutputFolderBrowse->Text = L"...";
			this->btnOutputFolderBrowse->Click += gcnew System::EventHandler(this, &CWADConvert::btnOutputFolderBrowse_Click);
			// 
			// txtOutputFolder
			// 
			this->txtOutputFolder->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtOutputFolder->Location = System::Drawing::Point(80, 34);
			this->txtOutputFolder->Name = L"txtOutputFolder";
			this->txtOutputFolder->Size = System::Drawing::Size(260, 20);
			this->txtOutputFolder->TabIndex = 4;
			this->tipMain->SetToolTip(this->txtOutputFolder, L"Destination image folder.");
			// 
			// lblOutputFolder
			// 
			this->lblOutputFolder->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblOutputFolder->Location = System::Drawing::Point(6, 37);
			this->lblOutputFolder->Name = L"lblOutputFolder";
			this->lblOutputFolder->Size = System::Drawing::Size(75, 20);
			this->lblOutputFolder->TabIndex = 3;
			this->lblOutputFolder->Text = L"Output Folder:";
			// 
			// btnWADFileBrowse
			// 
			this->btnWADFileBrowse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnWADFileBrowse->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnWADFileBrowse->Location = System::Drawing::Point(346, 15);
			this->btnWADFileBrowse->Name = L"btnWADFileBrowse";
			this->btnWADFileBrowse->Size = System::Drawing::Size(15, 17);
			this->btnWADFileBrowse->TabIndex = 2;
			this->btnWADFileBrowse->Text = L"...";
			this->btnWADFileBrowse->Click += gcnew System::EventHandler(this, &CWADConvert::btnWADFileBrowse_Click);
			// 
			// txtWADFile
			// 
			this->txtWADFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtWADFile->Location = System::Drawing::Point(80, 15);
			this->txtWADFile->Name = L"txtWADFile";
			this->txtWADFile->Size = System::Drawing::Size(260, 20);
			this->txtWADFile->TabIndex = 1;
			this->tipMain->SetToolTip(this->txtWADFile, L"Source .wad file.");
			// 
			// lblWADFile
			// 
			this->lblWADFile->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblWADFile->Location = System::Drawing::Point(6, 18);
			this->lblWADFile->Name = L"lblWADFile";
			this->lblWADFile->Size = System::Drawing::Size(60, 19);
			this->lblWADFile->TabIndex = 0;
			this->lblWADFile->Text = L"WAD File:";
			// 
			// btnClose
			// 
			this->btnClose->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnClose->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnClose->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnClose->Location = System::Drawing::Point(318, 334);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(60, 22);
			this->btnClose->TabIndex = 1;
			this->btnClose->Text = L"&Close";
			this->btnClose->Click += gcnew System::EventHandler(this, &CWADConvert::btnClose_Click);
			// 
			// btnConvert
			// 
			this->btnConvert->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnConvert->Enabled = true;
			this->btnConvert->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnConvert->Location = System::Drawing::Point(252, 334);
			this->btnConvert->Name = L"btnConvert";
			this->btnConvert->Size = System::Drawing::Size(60, 22);
			this->btnConvert->TabIndex = 0;
			this->btnConvert->Text = L"Con&vert";
			this->btnConvert->Click += gcnew System::EventHandler(this, &CWADConvert::btnConvert_Click);
			// 
			// grpProgress
			// 
			this->grpProgress->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpProgress->Controls->Add(this->lblProgress);
			this->grpProgress->Controls->Add(this->barProgress);
			this->grpProgress->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpProgress->Location = System::Drawing::Point(6, 88);
			this->grpProgress->Name = L"grpProgress";
			this->grpProgress->Size = System::Drawing::Size(370, 41);
			this->grpProgress->TabIndex = 3;
			this->grpProgress->TabStop = false;
			this->grpProgress->Text = L"Progress:";
			// 
			// barProgress
			// 
			this->barProgress->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->barProgress->Location = System::Drawing::Point(6, 16);
			this->barProgress->Name = L"barProgress";
			this->barProgress->Size = System::Drawing::Size(300, 19);
			this->barProgress->TabIndex = 0;
			// 
			// dlgOpenWADFile
			// 
			this->dlgOpenWADFile->Filter = L"WAD Files (*.wad)|*.wad";
			this->dlgOpenWADFile->Title = L"Open WAD File";
			// 
			// dlgOpenFolder
			// 
			this->dlgOpenFolder->Description = L"Select a folder:";
			// 
			// btnOptions
			// 
			this->btnOptions->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->btnOptions->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnOptions->Location = System::Drawing::Point(6, 334);
			this->btnOptions->Name = L"btnOptions";
			this->btnOptions->Size = System::Drawing::Size(72, 22);
			this->btnOptions->TabIndex = 5;
			this->btnOptions->Text = L"VT&F Options";
			this->btnOptions->Click += gcnew System::EventHandler(this, &CWADConvert::btnOptions_Click);
			// 
			// grpLog
			// 
			this->grpLog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpLog->Controls->Add(this->txtLog);
			this->grpLog->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpLog->Location = System::Drawing::Point(6, 133);
			this->grpLog->Name = L"grpLog";
			this->grpLog->Size = System::Drawing::Size(370, 196);
			this->grpLog->TabIndex = 4;
			this->grpLog->TabStop = false;
			this->grpLog->Text = L"Log:";
			// 
			// txtLog
			// 
			this->txtLog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtLog->DetectUrls = false;
			this->txtLog->Location = System::Drawing::Point(6, 14);
			this->txtLog->Name = L"txtLog";
			this->txtLog->ReadOnly = true;
			this->txtLog->Size = System::Drawing::Size(358, 176);
			this->txtLog->TabIndex = 0;
			this->txtLog->Text = L"";
			// 
			// tipMain
			// 
			this->tipMain->AutoPopDelay = 20000;
			this->tipMain->InitialDelay = 500;
			this->tipMain->ReshowDelay = 100;
			this->tipMain->ShowAlways = true;
			// 
			// btnVMTOptions
			// 
			this->btnVMTOptions->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->btnVMTOptions->Location = System::Drawing::Point(86, 334);
			this->btnVMTOptions->Name = L"btnVMTOptions";
			this->btnVMTOptions->Size = System::Drawing::Size(80, 22);
			this->btnVMTOptions->TabIndex = 6;
			this->btnVMTOptions->Text = L"VM&T Options";
			this->btnVMTOptions->UseVisualStyleBackColor = true;
			this->btnVMTOptions->Click += gcnew System::EventHandler(this, &CWADConvert::btnVMTOptions_Click);
			// 
			// lblProgress
			// 
			this->lblProgress->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->lblProgress->BackColor = System::Drawing::Color::Transparent;
			this->lblProgress->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblProgress->Location = System::Drawing::Point(311, 16);
			this->lblProgress->Name = L"lblProgress";
			this->lblProgress->Size = System::Drawing::Size(55, 21);
			this->lblProgress->TabIndex = 1;
			this->lblProgress->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// CWADConvert
			// 
			this->AcceptButton = this->btnConvert;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->CancelButton = this->btnClose;
			this->ClientSize = System::Drawing::Size(384, 361);
			this->Controls->Add(this->btnVMTOptions);
			this->Controls->Add(this->btnOptions);
			this->Controls->Add(this->grpProgress);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->btnConvert);
			this->Controls->Add(this->grpOptions);
			this->Controls->Add(this->grpLog);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(400, 400);
			this->Name = L"CWADConvert";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Convert WAD File";
			this->grpOptions->ResumeLayout(false);
			this->grpOptions->PerformLayout();
			this->grpProgress->ResumeLayout(false);
			this->grpLog->ResumeLayout(false);
			this->ResumeLayout(false);

		}
		public: property System::String ^WADFile
		{
			System::String^ get()
			{
				return this->txtWADFile->Text;
			}
			void set(System::String^ sWADFile)
			{
				if (System::IO::File::Exists(sWADFile))
				{
					this->txtWADFile->Text = sWADFile;
				}
			}
		}

		public: property System::String ^OutputFolder
		{
			System::String^ get()
			{
				return this->txtOutputFolder->Text;
			}
			void set(System::String^ sOutputFolder)
			{
				if (System::IO::Directory::Exists(sOutputFolder))
				{
					this->txtOutputFolder->Text = sOutputFolder;
				}
			}
		}

		public: property bool CreateVMTFiles
		{
			bool get()
			{
				return this->chkCreateVMTFiles->Checked == true;
			}
			void set(bool bCreateVMTFiles)
			{
				this->chkCreateVMTFiles->Checked = bCreateVMTFiles;
			}
		}

		private: System::Void btnWADFileBrowse_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->dlgOpenWADFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->txtWADFile->Text = this->dlgOpenWADFile->FileName;
			}
		}

		private: System::Void btnOutputFolderBrowse_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->dlgOpenFolder->SelectedPath = this->txtOutputFolder->Text;
			if(this->dlgOpenFolder->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->txtOutputFolder->Text = this->dlgOpenFolder->SelectedPath;
			}
		}

		private: System::Void btnConvert_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;

			this->barProgress->Value = 0;
			this->barProgress->Maximum = 1;
			this->txtLog->Clear();

			HLLib::CWADFile WADFile = HLLib::CWADFile();
			VTFLib::CVTFFile VTFFile = VTFLib::CVTFFile();

			SVTFCreateOptions VTFCreateOptions = CVTFFileUtility::GetCreateOptions(this->Options);

			char *cWADFile = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->txtWADFile->Text)).ToPointer();

			if(!WADFile.Open(cWADFile, HL_MODE_READ))
			{
				System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cWADFile);

				this->Cursor = System::Windows::Forms::Cursors::Default;

				MessageBox::Show(String::Concat("Error loading WAD file:\n\n", gcnew String(hlGetString(HL_ERROR_LONG_FORMATED))), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cWADFile);

			HLLib::CDirectoryFolder *Root = WADFile.GetRoot();

			this->barProgress->Maximum = Root->GetCount() - 1;

			for(DWORD i = 0; i < Root->GetCount(); i++)
			{
				HLLib::CDirectoryFile *File = static_cast<HLLib::CDirectoryFile *>(Root->GetItem(i));

				String ^sVTFName = gcnew String(File->GetName());
				sVTFName = sVTFName->Substring(0, sVTFName->LastIndexOf('.'));
				String ^sVTFFile = String::Concat(this->txtOutputFolder->Text, "\\", sVTFName, ".vtf");
				String ^sVMTFile = String::Concat(this->txtOutputFolder->Text, "\\", sVTFName, ".vmt");

				this->Log(String::Concat("Processing ", sVTFName, "..."), System::Drawing::Color::Gray);

				hlUInt dwPaletteSize, dwPixelSize, dwWidth, dwHeight;
				if(WADFile.GetImageSize(File, dwPaletteSize, dwPixelSize))
				{
					hlByte *lpPaletteData = new hlByte[dwPaletteSize];
					hlByte *lpPixelData = new hlByte[dwPixelSize];

					if(WADFile.GetImageData(File, dwWidth, dwHeight, lpPaletteData, lpPixelData))
					{
						bool bHasAlpha = false;

						vlByte *lpImageData = new vlByte[VTFFile.ComputeImageSize(dwWidth, dwHeight, 1, IMAGE_FORMAT_RGBA8888)];

						// Populate image data.
						for(DWORD i = 0; i < dwWidth; i++)
						{
							for(DWORD j = 0; j < dwHeight; j++)
							{
								DWORD dwPixelIndex = i + j ^ dwWidth;
								DWORD dwPaletteIndex = lpPixelData[dwPixelIndex];

								dwPixelIndex ^= 4;
								dwPaletteIndex ^= 3;

								// Populate RGB values.
								for(DWORD k = 0; k < 3; k++)
								{
									lpImageData[dwPixelIndex + k] = lpPaletteData[dwPaletteIndex + k];
								}

								// If we have a transparent texture, compute A value.
								if(sVTFName[0] != '{')
								{
									lpImageData[dwPixelIndex + 3] = 255;
								}
								else
								{
									bHasAlpha = true;
									lpImageData[dwPixelIndex + 3] = dwPaletteIndex / 3 == 255 ? 0 : 255;
								}
							}
						}

						// Create alpha channel for transparent textures.  Assume 0 0 255 is transparent color.
						/*if(sVTFName->get_Chars(0) == '{')
						{
							bHasAlpha = true;

							for(vlByte ^lpStart = lpImageData, ^lpEnd = lpImageData + VTFFile.ComputeImageSize(dwWidth, dwHeight, IMAGE_FORMAT_RGBA8888); lpStart < lpEnd; lpStart += 4)
							{
								if(lpStart[0] == 0 && lpStart[1] == 0 && lpStart[2] == 255)
								{
									lpStart[3] = 0;
								}
							}
						}*/

						VTFCreateOptions.ImageFormat = bHasAlpha ? Options->AlphaFormat : Options->NormalFormat;

						if(VTFFile.Create(dwWidth, dwHeight, lpImageData, VTFCreateOptions) != vlFalse)
						{
							if (VTFFile.GetMinorVersion() >= 3)
							{
								if (Options->chkCreateLODControlResource->Checked || Options->chkCreateInformationResource->Checked)
								{
									if (CVTFFileUtility::CreateResources(Options, &VTFFile) == vlFalse)
									{
										this->Log(String::Concat("Error creating resources for ", sVTFName, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
									}
								}
							}

							// Set flags for each VTF file created.
							for (vlUInt i = 0, j = 0x00000001; i < (vlUInt)this->Options->lstFlags->Items->Count; i++, j <<= 1)
							{
								if (this->Options->lstFlags->GetItemChecked(i))
								{
									// The flags list only includes flags that can be changed by the user.
									switch (i)
									{
									case 0: VTFFile.SetFlag(TEXTUREFLAGS_POINTSAMPLE, true); break;
									case 1: VTFFile.SetFlag(TEXTUREFLAGS_TRILINEAR, true); break;
									case 2: VTFFile.SetFlag(TEXTUREFLAGS_CLAMPS, true); break;
									case 3: VTFFile.SetFlag(TEXTUREFLAGS_CLAMPT, true); break;
									case 4: VTFFile.SetFlag(TEXTUREFLAGS_ANISOTROPIC, true); break;
									case 5: VTFFile.SetFlag(TEXTUREFLAGS_HINT_DXT5, true); break;
									case 6: VTFFile.SetFlag(TEXTUREFLAGS_SRGB, true); break;
									case 7: VTFFile.SetFlag(TEXTUREFLAGS_NORMAL, true); break;
									case 8: VTFFile.SetFlag(TEXTUREFLAGS_NOMIP, true); break;
									case 9: VTFFile.SetFlag(TEXTUREFLAGS_NOLOD, true); break;
									case 10: VTFFile.SetFlag(TEXTUREFLAGS_MINMIP, true); break;
									case 11: VTFFile.SetFlag(TEXTUREFLAGS_PROCEDURAL, true); break;
									case 12: VTFFile.SetFlag(TEXTUREFLAGS_ENVMAP, true); break;
									case 13: VTFFile.SetFlag(TEXTUREFLAGS_RENDERTARGET, true); break;
									case 14: VTFFile.SetFlag(TEXTUREFLAGS_DEPTHRENDERTARGET, true); break;
									case 15: VTFFile.SetFlag(TEXTUREFLAGS_NODEBUGOVERRIDE, true); break;
									case 16: VTFFile.SetFlag(TEXTUREFLAGS_NODEPTHBUFFER, true); break;
									case 17: VTFFile.SetFlag(TEXTUREFLAGS_CLAMPU, true); break;
									case 18: VTFFile.SetFlag(TEXTUREFLAGS_VERTEXTEXTURE, true); break;
									case 19: VTFFile.SetFlag(TEXTUREFLAGS_SSBUMP, true); break;
									case 20: VTFFile.SetFlag(TEXTUREFLAGS_BORDER, true); break;
									default:
										break;
									}
								}
							}

							char *cVTFFile = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sVTFFile)).ToPointer();
							if(VTFFile.Save(cVTFFile))
							{
								this->Log(String::Concat("Wrote ", sVTFFile, "."), System::Drawing::Color::Green);
								if (this->chkCreateVMTFiles->Checked)
								{
									char* cTemp;
									VTFLib::CVMTFile VMTFile;

									cTemp = (char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->VMTOptions->cboShader->Text).ToPointer();
									VMTFile.Create(cTemp);
									System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp);

									// Check if the target location contains \materials\ in the path. Assuming they are going to a game folder.
									if (sVTFFile->Contains("\\materials\\"))
									{
										// Convert to standard string for iteration.
										std::string vtfDest = msclr::interop::marshal_as<std::string>(sVTFFile);
										System::String^ findMaterials = "";
										System::String^ baseTexPrefix = "";
										bool found = false;
										for (wchar_t i : vtfDest)
										{
											if (!found)
											{
												if (findMaterials->Contains("\\materials\\"))
												{
													found = true;
													baseTexPrefix = baseTexPrefix + i;
												}
												else {
													findMaterials = findMaterials + i;
												}
											}
											else {
												baseTexPrefix = baseTexPrefix + i;
											}
										}
										std::string vtfSuffix = msclr::interop::marshal_as<std::string>(baseTexPrefix);
										int period = vtfSuffix.find_last_of('.');
										baseTexPrefix = baseTexPrefix->Remove(period); // Remove '.vtf' extension from basetexture as it's not needed.
										this->VMTOptions->AddVMTStringNode(VMTFile, "$basetexture", baseTexPrefix);
									}
									else
										this->VMTOptions->AddVMTStringNode(VMTFile, "$basetexture", sVTFName);

									this->VMTOptions->AddVMTStringNode(VMTFile, "$bumpmap", this->VMTOptions->txtBumpTexture1->Text);
									this->VMTOptions->AddVMTStringNode(VMTFile, "$basetexture2", this->VMTOptions->txtBaseTexture2->Text);
									this->VMTOptions->AddVMTStringNode(VMTFile, "$bumpmap2", this->VMTOptions->txtBumpTexture2->Text);
									this->VMTOptions->AddVMTStringNode(VMTFile, "$envmap", this->VMTOptions->txtEnviromentTexture->Text);
									this->VMTOptions->AddVMTStringNode(VMTFile, "$envmapmask", this->VMTOptions->txtEnviromentMaskTexture->Text);
									this->VMTOptions->AddVMTStringNode(VMTFile, "$detail", this->VMTOptions->txtDetailTexture->Text);
									this->VMTOptions->AddVMTStringNode(VMTFile, "%tooltexture", this->VMTOptions->txtToolTexture->Text);
									this->VMTOptions->AddVMTStringNode(VMTFile, "$normalmap", this->VMTOptions->txtNormalTexture->Text);
									this->VMTOptions->AddVMTStringNode(VMTFile, "$dudvmap", this->VMTOptions->txtDuDvTexture->Text);

									this->VMTOptions->AddVMTStringNode(VMTFile, "$surfaceprop", this->VMTOptions->cboSurface1->Text);
									this->VMTOptions->AddVMTStringNode(VMTFile, "$surfaceprop2", this->VMTOptions->cboSurface2->Text);

									this->VMTOptions->AddVMTStringNode(VMTFile, "%keywords", this->VMTOptions->txtKeywords->Text);

									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$additive", this->VMTOptions->chkAdditive->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$alphatest", this->VMTOptions->chkAlphaTest->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$nocull", this->VMTOptions->chkNoCull->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$nodecal", this->VMTOptions->chkNoDecal->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$nolod", this->VMTOptions->chkNoLOD->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$translucent", this->VMTOptions->chkTranslucent->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$vertexalpha", this->VMTOptions->chkVertexAlpha->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$vertexcolor", this->VMTOptions->chkVertexColor->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$model", this->VMTOptions->chkModel->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$decal", this->VMTOptions->chkDecal->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$nofog", this->VMTOptions->chkNoFog->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$ignorez", this->VMTOptions->chkIgnoreZ->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$halflambert", this->VMTOptions->chkHalfLambert->Checked, false);
									this->VMTOptions->AddVMTBooleanNode(VMTFile, "$allowalphatocoverage", this->VMTOptions->chkAlphaCoverage->Checked, false);

									cTemp = (char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sVMTFile).ToPointer();

									if (VMTFile.Save(cTemp))
										this->Log(String::Concat("Wrote ", sVMTFile, "."), System::Drawing::Color::Green);
									System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp);

								}
							}
							else
							{
								this->Log(String::Concat("Error writing ", sVTFName, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
							}
							System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cVTFFile);
						}
						else
						{
							this->Log(String::Concat("Error creating ", sVTFName, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
						}

						delete []lpImageData;
					}
					else
					{
						this->Log(String::Concat("Error processing ", sVTFName, ":\n\n", (gcnew String(hlGetString(HL_ERROR_LONG_FORMATED)))->Replace("\n", " ")), System::Drawing::Color::Red);
					}

					delete []lpPaletteData;
					delete []lpPixelData;
				}
				else
				{
					this->Log(String::Concat("Error processing ", sVTFName, ":\n\n", (gcnew String(hlGetString(HL_ERROR_LONG_FORMATED)))->Replace("\n", " ")), System::Drawing::Color::Red);
				}

				this->Log(String::Concat(sVTFName, " processed."), System::Drawing::Color::Gray);

				this->barProgress->Value = i;
				this->lblProgress->Text = String::Concat("% ", ((this->barProgress->Value / this->barProgress->Maximum) * 100).ToString("000.00"));
				this->barProgress->Refresh();
			}

			WADFile.Close();

			this->Cursor = System::Windows::Forms::Cursors::Default;
		}

		private: System::Void btnClose_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		}

		private: System::Void btnOptions_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			// Find the center of the main window to make this dialog box be centered on it.
			this->Options->Location = Point(
				(this->Location.X + (this->Width / 2)) - (this->Options->Width / 2),
				(this->Location.Y + (this->Height / 2)) - (this->Options->Height / 2)
			);
			// Basic check if the Options box's location will be outside of the monitor's bounds.
			if (this->Options->Location.X < 0 || this->Options->Location.Y < 0)
			{
				this->Options->Location = Point(0, 0);
			}
			this->Options->ShowDialog();
		}

		private: void Log(String ^sString, System::Drawing::Color cColor)
		{
			this->txtLog->Focus();
			this->txtLog->SelectionStart = this->txtLog->TextLength;
			this->txtLog->SelectionColor = cColor;
			this->txtLog->AppendText(String::Concat(sString, "\n"));
			this->txtLog->Refresh();
		}

		private: System::Void btnVMTOptions_Click(System::Object^ sender, System::EventArgs^ e) {
			System::String^ revertShaderText = this->VMTOptions->cboShader->Text;
			System::String^ revertBaseText = this->VMTOptions->txtBaseTexture1->Text;
			// Converting some things temporarily so I don't have to make a whole new dialog for this.
			this->VMTOptions->btnCreate->Text = "OK";
			this->VMTOptions->btnCreate->Click -= gcnew System::EventHandler(this->VMTOptions, &CVMTCreate::btnCreate_Click);
			this->VMTOptions->btnCreate->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->VMTOptions->txtBaseTexture1->Enabled = false;
			this->VMTOptions->btnBaseTexture1->Enabled = false;

			this->VMTOptions->ShowDialog();

			this->VMTOptions->btnCreate->Text = "Create";
			this->VMTOptions->btnCreate->Click += gcnew System::EventHandler(this->VMTOptions, &CVMTCreate::btnCreate_Click);
			this->VMTOptions->btnCreate->DialogResult = System::Windows::Forms::DialogResult::None;

			this->VMTOptions->cboShader->Text = revertShaderText;
			this->VMTOptions->txtBaseTexture1->Text = revertBaseText;
			this->VMTOptions->txtBaseTexture1->Enabled = true;
			this->VMTOptions->btnBaseTexture1->Enabled = true;
		}
};
}