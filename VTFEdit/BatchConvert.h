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
	public ref class CBatchConvert : public System::Windows::Forms::Form
	{
	private:
		CVTFOptions ^ Options;
		CVMTCreate ^ VMTOptions;

		System::String^ revertShaderText;

		   System::String^ revertBaseText;

	public: 
		CBatchConvert(CVTFOptions ^Options, CVMTCreate ^VMTOptions)
		{
			this->Options = Options;
			this->VMTOptions = VMTOptions;

			this->InitializeComponent();
		}

	private: System::Windows::Forms::Button ^  btnOptions;
	private: System::Windows::Forms::GroupBox ^  grpProgress;
	private: System::Windows::Forms::ProgressBar ^  barProgress;
	private: System::Windows::Forms::Label^ lblProgress;
	private: System::Windows::Forms::Button ^  btnClose;
	private: System::Windows::Forms::Button ^  btnConvert;
	private: System::Windows::Forms::GroupBox ^  grpOptions;
	private: System::Windows::Forms::CheckBox ^  chkCreateVMTFiles;
	private: System::Windows::Forms::Button ^  btnOutputFolderBrowse;
	private: System::Windows::Forms::TextBox ^  txtOutputFolder;
	private: System::Windows::Forms::Label ^  lblOutputFolder;
	private: System::Windows::Forms::Label ^  lblWADFile;
	private: System::Windows::Forms::GroupBox ^  grpLog;
	private: System::Windows::Forms::RichTextBox ^  txtLog;
	private: System::Windows::Forms::Button ^  btnInputFolderBrowse;
	private: System::Windows::Forms::TextBox ^  txtInputFolder;
	private: System::Windows::Forms::FolderBrowserDialog ^  dlgOpenFolder;
	private: System::Windows::Forms::CheckBox ^  chkRecursive;
	private: System::Windows::Forms::ToolTip ^  tipMain;
	private: System::Windows::Forms::TextBox ^  txtToVTFFilter;
	private: System::Windows::Forms::RadioButton ^  radToVTF;
	private: System::Windows::Forms::ComboBox ^  cboFromVTFFormat;
	private: System::Windows::Forms::RadioButton ^  radFromVTF;
	private: System::Windows::Forms::TextBox ^  txtFromVTFFilter;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CBatchConvert::typeid));
			this->btnOptions = (gcnew System::Windows::Forms::Button());
			this->grpProgress = (gcnew System::Windows::Forms::GroupBox());
			this->lblProgress = (gcnew System::Windows::Forms::Label());
			this->barProgress = (gcnew System::Windows::Forms::ProgressBar());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->btnConvert = (gcnew System::Windows::Forms::Button());
			this->grpOptions = (gcnew System::Windows::Forms::GroupBox());
			this->cboFromVTFFormat = (gcnew System::Windows::Forms::ComboBox());
			this->radFromVTF = (gcnew System::Windows::Forms::RadioButton());
			this->txtFromVTFFilter = (gcnew System::Windows::Forms::TextBox());
			this->radToVTF = (gcnew System::Windows::Forms::RadioButton());
			this->txtToVTFFilter = (gcnew System::Windows::Forms::TextBox());
			this->chkRecursive = (gcnew System::Windows::Forms::CheckBox());
			this->chkCreateVMTFiles = (gcnew System::Windows::Forms::CheckBox());
			this->btnOutputFolderBrowse = (gcnew System::Windows::Forms::Button());
			this->txtOutputFolder = (gcnew System::Windows::Forms::TextBox());
			this->lblOutputFolder = (gcnew System::Windows::Forms::Label());
			this->btnInputFolderBrowse = (gcnew System::Windows::Forms::Button());
			this->txtInputFolder = (gcnew System::Windows::Forms::TextBox());
			this->lblWADFile = (gcnew System::Windows::Forms::Label());
			this->grpLog = (gcnew System::Windows::Forms::GroupBox());
			this->txtLog = (gcnew System::Windows::Forms::RichTextBox());
			this->dlgOpenFolder = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->tipMain = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->btnVMTOptions = (gcnew System::Windows::Forms::Button());
			this->grpProgress->SuspendLayout();
			this->grpOptions->SuspendLayout();
			this->grpLog->SuspendLayout();
			this->SuspendLayout();
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
			this->btnOptions->Click += gcnew System::EventHandler(this, &CBatchConvert::btnOptions_Click);
			// 
			// grpProgress
			// 
			this->grpProgress->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpProgress->Controls->Add(this->lblProgress);
			this->grpProgress->Controls->Add(this->barProgress);
			this->grpProgress->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpProgress->Location = System::Drawing::Point(6, 127);
			this->grpProgress->Name = L"grpProgress";
			this->grpProgress->Size = System::Drawing::Size(372, 41);
			this->grpProgress->TabIndex = 3;
			this->grpProgress->TabStop = false;
			this->grpProgress->Text = L"Progress:";
			// 
			// lblProgress
			// 
			this->lblProgress->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->lblProgress->BackColor = System::Drawing::Color::Transparent;
			this->lblProgress->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblProgress->Location = System::Drawing::Point(312, 15);
			this->lblProgress->Name = L"lblProgress";
			this->lblProgress->Size = System::Drawing::Size(55, 21);
			this->lblProgress->TabIndex = 1;
			this->lblProgress->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
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
			this->btnClose->Click += gcnew System::EventHandler(this, &CBatchConvert::btnClose_Click);
			// 
			// btnConvert
			// 
			this->btnConvert->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnConvert->Enabled = false;
			this->btnConvert->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnConvert->Location = System::Drawing::Point(252, 334);
			this->btnConvert->Name = L"btnConvert";
			this->btnConvert->Size = System::Drawing::Size(60, 22);
			this->btnConvert->TabIndex = 0;
			this->btnConvert->Text = L"Con&vert";
			this->btnConvert->Click += gcnew System::EventHandler(this, &CBatchConvert::btnConvert_Click);
			// 
			// grpOptions
			// 
			this->grpOptions->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpOptions->Controls->Add(this->cboFromVTFFormat);
			this->grpOptions->Controls->Add(this->radFromVTF);
			this->grpOptions->Controls->Add(this->txtFromVTFFilter);
			this->grpOptions->Controls->Add(this->radToVTF);
			this->grpOptions->Controls->Add(this->txtToVTFFilter);
			this->grpOptions->Controls->Add(this->chkRecursive);
			this->grpOptions->Controls->Add(this->chkCreateVMTFiles);
			this->grpOptions->Controls->Add(this->btnOutputFolderBrowse);
			this->grpOptions->Controls->Add(this->txtOutputFolder);
			this->grpOptions->Controls->Add(this->lblOutputFolder);
			this->grpOptions->Controls->Add(this->btnInputFolderBrowse);
			this->grpOptions->Controls->Add(this->txtInputFolder);
			this->grpOptions->Controls->Add(this->lblWADFile);
			this->grpOptions->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpOptions->Location = System::Drawing::Point(6, 6);
			this->grpOptions->Name = L"grpOptions";
			this->grpOptions->Size = System::Drawing::Size(372, 114);
			this->grpOptions->TabIndex = 2;
			this->grpOptions->TabStop = false;
			this->grpOptions->Text = L"Options:";
			// 
			// cboFromVTFFormat
			// 
			this->cboFromVTFFormat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboFromVTFFormat->Enabled = false;
			this->cboFromVTFFormat->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"bmp", L"jpg", L"png", L"tga" });
			this->cboFromVTFFormat->Location = System::Drawing::Point(41, 67);
			this->cboFromVTFFormat->Name = L"cboFromVTFFormat";
			this->cboFromVTFFormat->Size = System::Drawing::Size(59, 21);
			this->cboFromVTFFormat->TabIndex = 9;
			// 
			// radFromVTF
			// 
			this->radFromVTF->Location = System::Drawing::Point(6, 70);
			this->radFromVTF->Name = L"radFromVTF";
			this->radFromVTF->Size = System::Drawing::Size(48, 18);
			this->radFromVTF->TabIndex = 8;
			this->radFromVTF->Text = L"To";
			this->radFromVTF->CheckedChanged += gcnew System::EventHandler(this, &CBatchConvert::radToFormat_CheckedChanged);
			// 
			// txtFromVTFFilter
			// 
			this->txtFromVTFFilter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtFromVTFFilter->Location = System::Drawing::Point(106, 68);
			this->txtFromVTFFilter->Name = L"txtFromVTFFilter";
			this->txtFromVTFFilter->ReadOnly = true;
			this->txtFromVTFFilter->Size = System::Drawing::Size(236, 20);
			this->txtFromVTFFilter->TabIndex = 10;
			this->txtFromVTFFilter->Text = L"*.vtf";
			this->tipMain->SetToolTip(this->txtFromVTFFilter, L"Wildcard filter.  Examples include *.* or *.vtf.");
			// 
			// radToVTF
			// 
			this->radToVTF->Checked = true;
			this->radToVTF->Location = System::Drawing::Point(6, 51);
			this->radToVTF->Name = L"radToVTF";
			this->radToVTF->Size = System::Drawing::Size(60, 19);
			this->radToVTF->TabIndex = 6;
			this->radToVTF->TabStop = true;
			this->radToVTF->Text = L"To VTF";
			this->radToVTF->CheckedChanged += gcnew System::EventHandler(this, &CBatchConvert::radToFormat_CheckedChanged);
			// 
			// txtToVTFFilter
			// 
			this->txtToVTFFilter->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtToVTFFilter->Location = System::Drawing::Point(106, 50);
			this->txtToVTFFilter->Name = L"txtToVTFFilter";
			this->txtToVTFFilter->Size = System::Drawing::Size(236, 20);
			this->txtToVTFFilter->TabIndex = 7;
			this->txtToVTFFilter->Text = L"*.tga";
			this->tipMain->SetToolTip(this->txtToVTFFilter, L"Wildcard filter.  Examples include *.* or *.tga or *.bmp;*.tga.");
			// 
			// chkRecursive
			// 
			this->chkRecursive->Checked = true;
			this->chkRecursive->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkRecursive->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkRecursive->Location = System::Drawing::Point(106, 90);
			this->chkRecursive->Name = L"chkRecursive";
			this->chkRecursive->Size = System::Drawing::Size(66, 19);
			this->chkRecursive->TabIndex = 11;
			this->chkRecursive->Text = L"&Recursive";
			this->tipMain->SetToolTip(this->chkRecursive, L"Include subdirectories.");
			// 
			// chkCreateVMTFiles
			// 
			this->chkCreateVMTFiles->Checked = true;
			this->chkCreateVMTFiles->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkCreateVMTFiles->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkCreateVMTFiles->Location = System::Drawing::Point(178, 90);
			this->chkCreateVMTFiles->Name = L"chkCreateVMTFiles";
			this->chkCreateVMTFiles->Size = System::Drawing::Size(100, 19);
			this->chkCreateVMTFiles->TabIndex = 12;
			this->chkCreateVMTFiles->Text = L"Create &VMT Files";
			this->tipMain->SetToolTip(this->chkCreateVMTFiles, L"Generate .vmt files for .vtf files. Ouput folder should be a material folder.");
			// 
			// btnOutputFolderBrowse
			// 
			this->btnOutputFolderBrowse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnOutputFolderBrowse->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnOutputFolderBrowse->Location = System::Drawing::Point(348, 31);
			this->btnOutputFolderBrowse->Name = L"btnOutputFolderBrowse";
			this->btnOutputFolderBrowse->Size = System::Drawing::Size(15, 16);
			this->btnOutputFolderBrowse->TabIndex = 5;
			this->btnOutputFolderBrowse->Text = L"...";
			this->btnOutputFolderBrowse->Click += gcnew System::EventHandler(this, &CBatchConvert::btnOutputFolderBrowse_Click);
			// 
			// txtOutputFolder
			// 
			this->txtOutputFolder->AllowDrop = true;
			this->txtOutputFolder->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtOutputFolder->Location = System::Drawing::Point(106, 31);
			this->txtOutputFolder->Name = L"txtOutputFolder";
			this->txtOutputFolder->Size = System::Drawing::Size(236, 20);
			this->txtOutputFolder->TabIndex = 4;
			this->tipMain->SetToolTip(this->txtOutputFolder, L"Destination image folder.");
			// 
			// lblOutputFolder
			// 
			this->lblOutputFolder->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblOutputFolder->Location = System::Drawing::Point(6, 34);
			this->lblOutputFolder->Name = L"lblOutputFolder";
			this->lblOutputFolder->Size = System::Drawing::Size(105, 19);
			this->lblOutputFolder->TabIndex = 3;
			this->lblOutputFolder->Text = L"Output Folder:";
			// 
			// btnInputFolderBrowse
			// 
			this->btnInputFolderBrowse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnInputFolderBrowse->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnInputFolderBrowse->Location = System::Drawing::Point(348, 12);
			this->btnInputFolderBrowse->Name = L"btnInputFolderBrowse";
			this->btnInputFolderBrowse->Size = System::Drawing::Size(15, 17);
			this->btnInputFolderBrowse->TabIndex = 2;
			this->btnInputFolderBrowse->Text = L"...";
			this->btnInputFolderBrowse->Click += gcnew System::EventHandler(this, &CBatchConvert::btnInputFolderBrowse_Click);
			// 
			// txtInputFolder
			// 
			this->txtInputFolder->AllowDrop = true;
			this->txtInputFolder->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->txtInputFolder->Location = System::Drawing::Point(106, 12);
			this->txtInputFolder->Name = L"txtInputFolder";
			this->txtInputFolder->Size = System::Drawing::Size(236, 20);
			this->txtInputFolder->TabIndex = 1;
			this->tipMain->SetToolTip(this->txtInputFolder, L"Source image folder.");
			this->txtInputFolder->TextChanged += gcnew System::EventHandler(this, &CBatchConvert::txtInputFolder_TextChanged);
			// 
			// lblWADFile
			// 
			this->lblWADFile->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblWADFile->Location = System::Drawing::Point(6, 15);
			this->lblWADFile->Name = L"lblWADFile";
			this->lblWADFile->Size = System::Drawing::Size(60, 19);
			this->lblWADFile->TabIndex = 0;
			this->lblWADFile->Text = L"Input Folder:";
			// 
			// grpLog
			// 
			this->grpLog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpLog->Controls->Add(this->txtLog);
			this->grpLog->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpLog->Location = System::Drawing::Point(6, 170);
			this->grpLog->Name = L"grpLog";
			this->grpLog->Size = System::Drawing::Size(372, 160);
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
			this->txtLog->Size = System::Drawing::Size(360, 139);
			this->txtLog->TabIndex = 0;
			this->txtLog->Text = L"";
			// 
			// dlgOpenFolder
			// 
			this->dlgOpenFolder->Description = L"Select a folder:";
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
			this->btnVMTOptions->Location = System::Drawing::Point(84, 334);
			this->btnVMTOptions->Name = L"btnVMTOptions";
			this->btnVMTOptions->Size = System::Drawing::Size(80, 22);
			this->btnVMTOptions->TabIndex = 6;
			this->btnVMTOptions->Text = L"VM&T Options";
			this->btnVMTOptions->UseVisualStyleBackColor = true;
			this->btnVMTOptions->Click += gcnew System::EventHandler(this, &CBatchConvert::btnVMTOptions_Click);
			// 
			// CBatchConvert
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
			this->Name = L"CBatchConvert";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Batch Convert";
			this->Load += gcnew System::EventHandler(this, &CBatchConvert::CBatchConvert_Load);
			this->grpProgress->ResumeLayout(false);
			this->grpOptions->ResumeLayout(false);
			this->grpOptions->PerformLayout();
			this->grpLog->ResumeLayout(false);
			this->ResumeLayout(false);

		}
		public: property System::String ^InputFolder
		{
			System::String^ get()
			{
				return this->txtInputFolder->Text;
			}
			void set(System::String^ sInputFolder)
			{
				if(System::IO::Directory::Exists(sInputFolder))
				{
					this->txtInputFolder->Text = sInputFolder;
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
				if(System::IO::Directory::Exists(sOutputFolder))
				{
					this->txtOutputFolder->Text = sOutputFolder;
				}
			}
		}

		public: property bool ToVTF
		{
			bool get()
			{
				return this->radToVTF->Checked;
			}
			void set(bool bToVTF)
			{
				if (bToVTF)
				{
					this->radToVTF->Checked = true;
				}
				else
				{
					this->radFromVTF->Checked = true;
				}
			}
		}

		public: property System::String ^ToVTFFilter
		{
			System::String^ get()
			{
				return this->txtToVTFFilter->Text;
			}
			void set(System::String^ sFilter)
			{
				this->txtToVTFFilter->Text = sFilter;
			}
		}

		public: property System::String ^FromVTFFormat
		{
			System::String^ get()
			{
				return this->cboFromVTFFormat->Text;
			}
			void set(System::String^ sFormat)
			{
				this->cboFromVTFFormat->Text = sFormat;
				if (this->cboFromVTFFormat->SelectedIndex == -1)
				{
					this->cboFromVTFFormat->SelectedIndex = 3;
				}
			}
		}
		public: property System::String ^FromVTFFilter
		{
			System::String^ get()
			{
				return this->txtFromVTFFilter->Text;
			}
			void set(System::String^ sFilter)
			{
				this->txtFromVTFFilter->Text = sFilter;
			}
		}

		public: property bool Recurse
		{
			bool get()
			{
				return this->chkRecursive->Checked == true;
			}
			void set(bool bRecurse)
			{
				this->chkRecursive->Checked = bRecurse;
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

		private: System::Void CBatchConvert_Load(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->cboFromVTFFormat->SelectedIndex == -1)
			{
				this->cboFromVTFFormat->SelectedIndex = 3;
			}
		}

		private: System::Void btnInputFolderBrowse_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->dlgOpenFolder->SelectedPath = this->txtInputFolder->Text;
			if(this->dlgOpenFolder->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->txtInputFolder->Text = this->dlgOpenFolder->SelectedPath;
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

		private: System::Void txtInputFolder_TextChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnConvert->Enabled = System::IO::Directory::Exists(this->txtInputFolder->Text);
		}

		private: System::Void radToFormat_CheckedChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtToVTFFilter->ReadOnly = !this->radToVTF->Checked;
			this->cboFromVTFFormat->Enabled = this->radFromVTF->Checked;
			this->txtFromVTFFilter->ReadOnly = !this->radFromVTF->Checked;
		}

		private: int CountFiles(System::String ^sInputFolder, System::String ^sFilter, bool bRecursive)
		{
			int count = 0;

			System::IO::DirectoryInfo ^Folder = gcnew System::IO::DirectoryInfo(sInputFolder);

			if (bRecursive)
			{
				array<System::IO::DirectoryInfo ^>^ Folders = Folder->GetDirectories();

				for(int i = 0; i < Folders->Length; i++)
				{
					count += this->CountFiles(Folders[i]->FullName, sFilter, bRecursive);
				}
			}

			System::String^ filterSplit = ";";
			array<System::String^>^ Filters = sFilter->Split(filterSplit->ToCharArray());

			for(int i = 0; i < Filters->Length; i++)
			{
				array<System::IO::FileInfo ^>^ Files = Folder->GetFiles(Filters[i]);
				count += Files->Length;
			}

			return count;
		}

		private: System::Void ConvertFolder(System::String ^sInputFolder, System::String ^sOutputFolder, System::String ^sFilter, bool bRecursive, SVTFCreateOptions &VTFCreateOptions)
		{
			VTFLib::CVTFFile VTFFile = VTFLib::CVTFFile();

			System::IO::DirectoryInfo ^Folder = gcnew System::IO::DirectoryInfo(sInputFolder);

			this->Log(String::Concat("Entering ", sInputFolder, "..."), System::Drawing::Color::Green);

			if (bRecursive)
			{
				array<System::IO::DirectoryInfo ^>^ Folders = Folder->GetDirectories();

				for(int i = 0; i < Folders->Length; i++)
				{
					this->ConvertFolder(String::Concat(sInputFolder, "\\", Folders[i]->Name), String::Concat(sOutputFolder, "\\", Folders[i]->Name), sFilter, bRecursive, VTFCreateOptions);
				}
			}

			System::String^ filterString = ";";
			array<System::String ^>^ Filters = sFilter->Split(filterString->ToCharArray());

			for(int i = 0; i < Filters->Length; i++)
			{
				array<System::IO::FileInfo ^>^ Files = Folder->GetFiles(Filters[i]);

				for(int j = 0; j < Files->Length; j++)
				{
					bool bIsVTF = String::Compare(Files[j]->Extension, ".vtf", true) == 0;
					bool bHasAlpha = false;

					this->Log(String::Concat("Processing ", Files[j]->Name, "..."), System::Drawing::Color::Gray);

					if(this->radToVTF->Checked && !bIsVTF) // Convert to .vtf.
					{
						String ^sVTFName = Files[j]->Name->Substring(0, Files[j]->Name->Length - Files[j]->Extension->Length);
						String ^sVTFFile = String::Concat(sOutputFolder, "\\", sVTFName, ".vtf");
						String ^sVMTFile = String::Concat(sOutputFolder, "\\", sVTFName, ".vmt");

						char *cFile = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Files[j]->FullName)).ToPointer();

						// Load the image and convert it to RGBA.
						if(ilLoadImage(cFile))
						{
							if(ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
							{
								vlUInt uiWidth = (vlUInt)ilGetInteger(IL_IMAGE_WIDTH);
								vlUInt uiHeight = (vlUInt)ilGetInteger(IL_IMAGE_HEIGHT);
								vlUInt val = uiWidth * uiHeight * 4;
								// Copy the image data.
								vlByte *lpImageData = new vlByte[val];
								memcpy(lpImageData, ilGetData(), val);

								// Only check for alpha when bHasAlpha is false. This is to allow for checking through multiple images for transparency
								// and to not unnecessarily check for alpha when it was already detected, which would be pointless.
								if ( !bHasAlpha ) {
									DWORD uiStride = (uiWidth + 3) / 4 * 4;
									System::Drawing::Bitmap^ vtfImage = gcnew System::Drawing::Bitmap(uiWidth, uiHeight, uiStride * 3,	System::Drawing::Imaging::PixelFormat::Format32bppArgb, (System::IntPtr)lpImageData);

									// Iterate all pixels in the image and check if any of them are lower than 255 ( is not fully opaque )
									for ( vlUInt j = 0; j < uiWidth; j++ ) {
										for ( vlUInt k = 0; k < uiHeight; k++ ) {
											if ( vtfImage->GetPixel( j, k ).A < 255 ) {
												bHasAlpha = true;
												break;
											}
										}
									}
								}
								
								VTFCreateOptions.ImageFormat = bHasAlpha ? Options->AlphaFormat : Options->NormalFormat;

								if(VTFFile.Create(uiWidth, uiHeight, lpImageData, VTFCreateOptions) != vlFalse)
								{
									if (VTFFile.GetMinorVersion() >= 3)
									{
										if (Options->chkCreateLODControlResource->Checked || Options->chkCreateInformationResource->Checked)
										{
											if (CVTFFileUtility::CreateResources(Options, &VTFFile) == vlFalse)
											{
												this->Log(String::Concat("Error creating resources for ", Files[j]->Name, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
											}
										}
									}

									if(!System::IO::Directory::Exists(sOutputFolder))
									{
										try
										{
											System::IO::Directory::CreateDirectory(sOutputFolder);
										}
										catch(Exception ^)
										{

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
										//this->Log(String::Concat("Wrote ", sVTFFile, "."), System::Drawing::Color::Green);
										if(this->chkCreateVMTFiles->Checked)
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

											if(VMTFile.Save(cTemp))
												this->Log(String::Concat("Wrote ", sVMTFile, "."), System::Drawing::Color::Green);
											System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp);

										}
									}
									else
									{
										this->Log(String::Concat("Error writing ", Files[j]->Name, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
									}
									System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cVTFFile);
								}
								else
								{
									this->Log(String::Concat("Error creating ", Files[j]->Name, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
								}
								
							}
							else
							{
								this->Log(String::Concat("Error converting ", Files[j]->Name, "."), System::Drawing::Color::Red);
							}
						}
						else
						{
							this->Log(String::Concat("Error loading ", Files[j]->Name, "."), System::Drawing::Color::Red);
						}

						System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cFile);

						this->Log(String::Concat(Files[j]->Name, " processed."), System::Drawing::Color::Gray);
					}
					else if(bIsVTF)  // Convert from .vtf.
					{
						String ^sOtherName = Files[j]->Name->Substring(0, Files[j]->Name->Length - Files[j]->Extension->Length);
						String ^sOtherFile = String::Concat(sOutputFolder, "\\", sOtherName, ".", this->cboFromVTFFormat->Text);

						char *cFile = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Files[j]->FullName)).ToPointer();

						if(VTFFile.Load(cFile))
						{
							vlUInt uiWidth = VTFFile.GetWidth(), uiHeight = VTFFile.GetHeight();
				
							vlByte *lpImageData = new vlByte[VTFFile.ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)];

							if(VTFFile.ConvertToRGBA8888(VTFFile.GetData(0, 0, 0, 0), lpImageData, uiWidth, uiHeight, VTFFile.GetFormat()))
							{
								// DevIL likes image data upside down...
								VTFFile.FlipImage(lpImageData, uiWidth, uiHeight);

								if(ilTexImage(uiWidth, uiHeight, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, lpImageData))
								{
									if(!System::IO::Directory::Exists(sOutputFolder))
									{
										try
										{
											System::IO::Directory::CreateDirectory(sOutputFolder);
										}
										catch(Exception ^)
										{

										}
									}

									char *cOtherFile = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sOtherFile)).ToPointer();
									if(ilSaveImage(cOtherFile))
									{
										this->Log(String::Concat("Wrote ", sOtherFile, "."), System::Drawing::Color::Green);
									}
									else
									{
										this->Log(String::Concat("Error writing ", Files[j]->Name, "."), System::Drawing::Color::Red);
									}
									System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cOtherFile);
								}
								else
								{
									this->Log(String::Concat("Error creating ", Files[j]->Name, "."), System::Drawing::Color::Red);
								}
							}
							else
							{
								this->Log(String::Concat("Error converting ", Files[j]->Name, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
							}

							delete []lpImageData;
						}
						else
						{
							this->Log(String::Concat("Error loading ", Files[j]->Name, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
						}

						System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cFile);

						this->Log(String::Concat(Files[j]->Name, " processed."), System::Drawing::Color::Gray);
					}
					else
					{
						this->Log(String::Concat(Files[j]->Name, " skipped."), System::Drawing::Color::Gray);
					}

					this->barProgress->Value++;
					this->lblProgress->Text = String::Concat("% ", ((this->barProgress->Value / this->barProgress->Maximum) * 100).ToString("000.00"));
					this->barProgress->Refresh();
				}
			}

			// Revert the text for shader and basetexture to what they previously were.
			this->VMTOptions->cboShader->Text = revertShaderText;
			this->VMTOptions->txtBaseTexture1->Text = revertBaseText;

			this->Log(String::Concat("Exiting ", sInputFolder, "."), System::Drawing::Color::Green);
		}

		private: System::Void btnConvert_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;

			String ^sFilter = this->radToVTF->Checked ? this->txtToVTFFilter->Text : this->txtFromVTFFilter->Text;
			if(sFilter->Length == 0)
			{
				sFilter = "^";
			}

			this->barProgress->Value = 0;
			this->barProgress->Maximum = this->CountFiles(this->txtInputFolder->Text, sFilter, this->chkRecursive->Checked);
			this->txtLog->Clear();

			SVTFCreateOptions VTFCreateOptions = CVTFFileUtility::GetCreateOptions(this->Options);

			
			this->ConvertFolder(this->txtInputFolder->Text, this->txtOutputFolder->Text->Length == 0 ? this->txtInputFolder->Text : this->txtOutputFolder->Text, sFilter, this->chkRecursive->Checked, VTFCreateOptions);

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
			revertShaderText = this->VMTOptions->cboShader->Text;
			revertBaseText = this->VMTOptions->txtBaseTexture1->Text;
			// Converting some things temporarily so I don't have to make a whole new dialog for this.
			this->VMTOptions->btnCreate->Text = "OK";
			this->VMTOptions->btnCreate->Click -= gcnew System::EventHandler(this->VMTOptions, &CVMTCreate::btnCreate_Click);
			this->VMTOptions->btnCreate->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->VMTOptions->txtBaseTexture1->Text = "";
			this->VMTOptions->txtBaseTexture1->Enabled = false;
			this->VMTOptions->btnBaseTexture1->Enabled = false;

			this->VMTOptions->ShowDialog();

			this->VMTOptions->btnCreate->Text = "Create";
			this->VMTOptions->btnCreate->Click += gcnew System::EventHandler(this->VMTOptions, &CVMTCreate::btnCreate_Click);
			this->VMTOptions->btnCreate->DialogResult = System::Windows::Forms::DialogResult::None;

			this->VMTOptions->txtBaseTexture1->Enabled = true;
			this->VMTOptions->btnBaseTexture1->Enabled = true;
		}
};
}