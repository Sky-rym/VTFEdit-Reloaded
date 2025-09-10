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

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "stdafx.h"

namespace VTFEdit
{
	public ref class CVTFEditResources : public System::Windows::Forms::Form
	{
	public:
		CVTFEditResources(void)
		{
			this->InitializeComponent();

			this->btnReset_Click(this, System::EventArgs::Empty);
		}

	private: System::Windows::Forms::Button^ btnOK;
	private: System::Windows::Forms::Button^ btnCancel;
	private: System::Windows::Forms::ContextMenu^ mnuReset;
	private: System::Windows::Forms::MenuItem^ btnReset;
	private: System::Windows::Forms::ToolTip^ tipMain;

	private: System::Windows::Forms::GroupBox^ grpResourceOptions;
	private: System::Windows::Forms::GroupBox^ grpLODControlResource;
	private: System::Windows::Forms::NumericUpDown^ numLODControlClampV;
	private: System::Windows::Forms::Label^ lblLODControlClampV;
	private: System::Windows::Forms::NumericUpDown^ numLODControlClampU;
	private: System::Windows::Forms::Label^ lblLODControlClampU;
	private: System::Windows::Forms::GroupBox^ grpInformationResource;
	private: System::Windows::Forms::Label^ lblInformationContact;
	private: System::Windows::Forms::Label^ lblInformationAuthor;
	private: System::Windows::Forms::TextBox^ txtInformationContact;
	private: System::Windows::Forms::TextBox^ txtInformationAuthor;
	private: System::Windows::Forms::TextBox^ txtInformationComments;
	private: System::Windows::Forms::TextBox^ txtInformationDescription;
	private: System::Windows::Forms::Label^ lblInformationComments;
	private: System::Windows::Forms::Label^ lblInformationDescription;
	private: System::Windows::Forms::TextBox^ txtInformationModification;
	private: System::Windows::Forms::TextBox^ txtInformationVersion;
	private: System::Windows::Forms::Label^ lblInformationModification;
	private: System::Windows::Forms::Label^ lblInformationVersion;

	public: System::Windows::Forms::CheckBox^ chkCreateLODControlResource;
	public: System::Windows::Forms::CheckBox^ chkCreateInformationResource;

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
			this->mnuReset = (gcnew System::Windows::Forms::ContextMenu());
			this->btnReset = (gcnew System::Windows::Forms::MenuItem());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->tipMain = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->chkCreateLODControlResource = (gcnew System::Windows::Forms::CheckBox());
			this->chkCreateInformationResource = (gcnew System::Windows::Forms::CheckBox());
			this->grpResourceOptions = (gcnew System::Windows::Forms::GroupBox());
			this->grpLODControlResource = (gcnew System::Windows::Forms::GroupBox());
			this->numLODControlClampV = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblLODControlClampV = (gcnew System::Windows::Forms::Label());
			this->numLODControlClampU = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblLODControlClampU = (gcnew System::Windows::Forms::Label());
			this->grpInformationResource = (gcnew System::Windows::Forms::GroupBox());
			this->txtInformationComments = (gcnew System::Windows::Forms::TextBox());
			this->txtInformationDescription = (gcnew System::Windows::Forms::TextBox());
			this->lblInformationComments = (gcnew System::Windows::Forms::Label());
			this->lblInformationDescription = (gcnew System::Windows::Forms::Label());
			this->txtInformationModification = (gcnew System::Windows::Forms::TextBox());
			this->txtInformationVersion = (gcnew System::Windows::Forms::TextBox());
			this->lblInformationModification = (gcnew System::Windows::Forms::Label());
			this->lblInformationVersion = (gcnew System::Windows::Forms::Label());
			this->txtInformationContact = (gcnew System::Windows::Forms::TextBox());
			this->txtInformationAuthor = (gcnew System::Windows::Forms::TextBox());
			this->lblInformationContact = (gcnew System::Windows::Forms::Label());
			this->lblInformationAuthor = (gcnew System::Windows::Forms::Label());
			this->grpResourceOptions->SuspendLayout();
			this->grpLODControlResource->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numLODControlClampV))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numLODControlClampU))->BeginInit();
			this->grpInformationResource->SuspendLayout();
			this->SuspendLayout();
			// 
			// mnuReset
			// 
			this->mnuReset->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) { this->btnReset });
			// 
			// btnReset
			// 
			this->btnReset->Index = 0;
			this->btnReset->Text = L"&Reset";
			this->btnReset->Click += gcnew System::EventHandler(this, &CVTFEditResources::btnReset_Click);
			// 
			// btnOK
			// 
			this->btnOK->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnOK->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->btnOK->Location = System::Drawing::Point(176, 290);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(60, 22);
			this->btnOK->TabIndex = 0;
			this->btnOK->Text = L"&OK";
			this->btnOK->Click += gcnew System::EventHandler(this, &CVTFEditResources::btnOK_Click);
			// 
			// btnCancel
			// 
			this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->btnCancel->Location = System::Drawing::Point(112, 290);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(60, 22);
			this->btnCancel->TabIndex = 1;
			this->btnCancel->Text = L"&Cancel";
			this->btnCancel->Click += gcnew System::EventHandler(this, &CVTFEditResources::btnCancel_Click);
			// 
			// tipMain
			// 
			this->tipMain->ShowAlways = true;
			this->tipMain->AutoPopDelay = 20000;
			this->tipMain->InitialDelay = 500;
			this->tipMain->ReshowDelay = 100;
			// 
			// chkCreateLODControlResource
			// 
			this->chkCreateLODControlResource->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkCreateLODControlResource->Location = System::Drawing::Point(6, 16);
			this->chkCreateLODControlResource->Name = L"chkCreateLODControlResource";
			this->chkCreateLODControlResource->Size = System::Drawing::Size(192, 19);
			this->chkCreateLODControlResource->TabIndex = 0;
			this->chkCreateLODControlResource->Text = L"Create LOD Control Resource";
			this->tipMain->SetToolTip(this->chkCreateLODControlResource, L"Clamp texture LODs on the U and V axes.");
			this->chkCreateLODControlResource->CheckedChanged += gcnew System::EventHandler(this, &CVTFEditResources::chkCreateLODControlResource_CheckedChanged);
			// 
			// chkCreateInformationResource
			// 
			this->chkCreateInformationResource->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkCreateInformationResource->Location = System::Drawing::Point(6, 16);
			this->chkCreateInformationResource->Name = L"chkCreateInformationResource";
			this->chkCreateInformationResource->Size = System::Drawing::Size(192, 19);
			this->chkCreateInformationResource->TabIndex = 0;
			this->chkCreateInformationResource->Text = L"Create Information Resource";
			this->tipMain->SetToolTip(this->chkCreateInformationResource, L"Embed texture metadata.\r\nNote: Creates an unofficial KVF resource.");
			this->chkCreateInformationResource->CheckedChanged += gcnew System::EventHandler(this, &CVTFEditResources::chkCreateInformationResource_CheckedChanged);
			// 
			// grpResourceOptions
			// 
			this->grpResourceOptions->Controls->Add(this->grpLODControlResource);
			this->grpResourceOptions->Controls->Add(this->grpInformationResource);
			this->grpResourceOptions->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpResourceOptions->Location = System::Drawing::Point(9, 12);
			this->grpResourceOptions->Name = L"grpResourceOptions";
			this->grpResourceOptions->Size = System::Drawing::Size(228, 272);
			this->grpResourceOptions->TabIndex = 0;
			this->grpResourceOptions->TabStop = false;
			this->grpResourceOptions->Text = L"Resource Options:";
			// 
			// grpLODControlResource
			// 
			this->grpLODControlResource->ContextMenu = this->mnuReset;
			this->grpLODControlResource->Controls->Add(this->numLODControlClampV);
			this->grpLODControlResource->Controls->Add(this->lblLODControlClampV);
			this->grpLODControlResource->Controls->Add(this->numLODControlClampU);
			this->grpLODControlResource->Controls->Add(this->lblLODControlClampU);
			this->grpLODControlResource->Controls->Add(this->chkCreateLODControlResource);
			this->grpLODControlResource->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpLODControlResource->Location = System::Drawing::Point(6, 13);
			this->grpLODControlResource->Name = L"grpLODControlResource";
			this->grpLODControlResource->Size = System::Drawing::Size(216, 82);
			this->grpLODControlResource->TabIndex = 0;
			this->grpLODControlResource->TabStop = false;
			this->grpLODControlResource->Text = L"LOD Control Resource:";
			// 
			// numLODControlClampV
			// 
			this->numLODControlClampV->Location = System::Drawing::Point(78, 57);
			this->numLODControlClampV->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->numLODControlClampV->Name = L"numLODControlClampV";
			this->numLODControlClampV->Size = System::Drawing::Size(132, 20);
			this->numLODControlClampV->TabIndex = 4;
			// 
			// lblLODControlClampV
			// 
			this->lblLODControlClampV->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblLODControlClampV->Location = System::Drawing::Point(6, 60);
			this->lblLODControlClampV->Name = L"lblLODControlClampV";
			this->lblLODControlClampV->Size = System::Drawing::Size(66, 13);
			this->lblLODControlClampV->TabIndex = 3;
			this->lblLODControlClampV->Text = L"Clamp V:";
			// 
			// numLODControlClampU
			// 
			this->numLODControlClampU->Location = System::Drawing::Point(78, 38);
			this->numLODControlClampU->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->numLODControlClampU->Name = L"numLODControlClampU";
			this->numLODControlClampU->Size = System::Drawing::Size(132, 20);
			this->numLODControlClampU->TabIndex = 2;
			// 
			// lblLODControlClampU
			// 
			this->lblLODControlClampU->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblLODControlClampU->Location = System::Drawing::Point(6, 41);
			this->lblLODControlClampU->Name = L"lblLODControlClampU";
			this->lblLODControlClampU->Size = System::Drawing::Size(66, 13);
			this->lblLODControlClampU->TabIndex = 1;
			this->lblLODControlClampU->Text = L"Clamp U:";
			// 
			// grpInformationResource
			// 
			this->grpInformationResource->ContextMenu = this->mnuReset;
			this->grpInformationResource->Controls->Add(this->txtInformationComments);
			this->grpInformationResource->Controls->Add(this->txtInformationDescription);
			this->grpInformationResource->Controls->Add(this->lblInformationComments);
			this->grpInformationResource->Controls->Add(this->lblInformationDescription);
			this->grpInformationResource->Controls->Add(this->txtInformationModification);
			this->grpInformationResource->Controls->Add(this->txtInformationVersion);
			this->grpInformationResource->Controls->Add(this->lblInformationModification);
			this->grpInformationResource->Controls->Add(this->lblInformationVersion);
			this->grpInformationResource->Controls->Add(this->txtInformationContact);
			this->grpInformationResource->Controls->Add(this->txtInformationAuthor);
			this->grpInformationResource->Controls->Add(this->lblInformationContact);
			this->grpInformationResource->Controls->Add(this->lblInformationAuthor);
			this->grpInformationResource->Controls->Add(this->chkCreateInformationResource);
			this->grpInformationResource->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpInformationResource->Location = System::Drawing::Point(6, 105);
			this->grpInformationResource->Name = L"grpInformationResource";
			this->grpInformationResource->Size = System::Drawing::Size(216, 158);
			this->grpInformationResource->TabIndex = 1;
			this->grpInformationResource->TabStop = false;
			this->grpInformationResource->Text = L"Information Resource:";
			// 
			// txtInformationComments
			// 
			this->txtInformationComments->Location = System::Drawing::Point(78, 132);
			this->txtInformationComments->MaxLength = 8192;
			this->txtInformationComments->Name = L"txtInformationComments";
			this->txtInformationComments->Size = System::Drawing::Size(132, 20);
			this->txtInformationComments->TabIndex = 12;
			// 
			// txtInformationDescription
			// 
			this->txtInformationDescription->Location = System::Drawing::Point(78, 113);
			this->txtInformationDescription->MaxLength = 8192;
			this->txtInformationDescription->Name = L"txtInformationDescription";
			this->txtInformationDescription->Size = System::Drawing::Size(132, 20);
			this->txtInformationDescription->TabIndex = 10;
			// 
			// lblInformationComments
			// 
			this->lblInformationComments->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblInformationComments->Location = System::Drawing::Point(6, 135);
			this->lblInformationComments->Name = L"lblInformationComments";
			this->lblInformationComments->Size = System::Drawing::Size(66, 12);
			this->lblInformationComments->TabIndex = 11;
			this->lblInformationComments->Text = L"Comments:";
			// 
			// lblInformationDescription
			// 
			this->lblInformationDescription->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblInformationDescription->Location = System::Drawing::Point(6, 116);
			this->lblInformationDescription->Name = L"lblInformationDescription";
			this->lblInformationDescription->Size = System::Drawing::Size(66, 13);
			this->lblInformationDescription->TabIndex = 9;
			this->lblInformationDescription->Text = L"Description:";
			// 
			// txtInformationModification
			// 
			this->txtInformationModification->Location = System::Drawing::Point(78, 94);
			this->txtInformationModification->MaxLength = 8192;
			this->txtInformationModification->Name = L"txtInformationModification";
			this->txtInformationModification->Size = System::Drawing::Size(132, 20);
			this->txtInformationModification->TabIndex = 8;
			// 
			// txtInformationVersion
			// 
			this->txtInformationVersion->Location = System::Drawing::Point(78, 76);
			this->txtInformationVersion->MaxLength = 8192;
			this->txtInformationVersion->Name = L"txtInformationVersion";
			this->txtInformationVersion->Size = System::Drawing::Size(132, 20);
			this->txtInformationVersion->TabIndex = 6;
			// 
			// lblInformationModification
			// 
			this->lblInformationModification->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblInformationModification->Location = System::Drawing::Point(6, 97);
			this->lblInformationModification->Name = L"lblInformationModification";
			this->lblInformationModification->Size = System::Drawing::Size(66, 13);
			this->lblInformationModification->TabIndex = 7;
			this->lblInformationModification->Text = L"Modification:";
			// 
			// lblInformationVersion
			// 
			this->lblInformationVersion->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblInformationVersion->Location = System::Drawing::Point(6, 78);
			this->lblInformationVersion->Name = L"lblInformationVersion";
			this->lblInformationVersion->Size = System::Drawing::Size(66, 12);
			this->lblInformationVersion->TabIndex = 5;
			this->lblInformationVersion->Text = L"Version:";
			// 
			// txtInformationContact
			// 
			this->txtInformationContact->Location = System::Drawing::Point(78, 57);
			this->txtInformationContact->MaxLength = 8192;
			this->txtInformationContact->Name = L"txtInformationContact";
			this->txtInformationContact->Size = System::Drawing::Size(132, 20);
			this->txtInformationContact->TabIndex = 4;
			// 
			// txtInformationAuthor
			// 
			this->txtInformationAuthor->Location = System::Drawing::Point(78, 38);
			this->txtInformationAuthor->MaxLength = 8192;
			this->txtInformationAuthor->Name = L"txtInformationAuthor";
			this->txtInformationAuthor->Size = System::Drawing::Size(132, 20);
			this->txtInformationAuthor->TabIndex = 2;
			// 
			// lblInformationContact
			// 
			this->lblInformationContact->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblInformationContact->Location = System::Drawing::Point(6, 59);
			this->lblInformationContact->Name = L"lblInformationContact";
			this->lblInformationContact->Size = System::Drawing::Size(66, 13);
			this->lblInformationContact->TabIndex = 3;
			this->lblInformationContact->Text = L"Contact:";
			// 
			// lblInformationAuthor
			// 
			this->lblInformationAuthor->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblInformationAuthor->Location = System::Drawing::Point(6, 40);
			this->lblInformationAuthor->Name = L"lblInformationAuthor";
			this->lblInformationAuthor->Size = System::Drawing::Size(66, 13);
			this->lblInformationAuthor->TabIndex = 1;
			this->lblInformationAuthor->Text = L"Author:";
			// 
			// CVTFEditResources
			// 
			this->AcceptButton = this->btnOK;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->CancelButton = this->btnCancel;
			this->ClientSize = System::Drawing::Size(249, 320);
			this->Controls->Add(this->grpResourceOptions);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnOK);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"CVTFEditResources";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"VTF Resources";
			this->Load += gcnew System::EventHandler(this, &CVTFEditResources::CVTFResources_Load);
			this->grpResourceOptions->ResumeLayout(false);
			this->grpLODControlResource->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numLODControlClampV))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numLODControlClampU))->EndInit();
			this->grpInformationResource->ResumeLayout(false);
			this->grpInformationResource->PerformLayout();
			this->ResumeLayout(false);

		}


		// LOD Control Resource

	public: property vlBool CreateLODControlResource
	{
		vlBool get()
		{
			return this->chkCreateLODControlResource->Checked == true;
		}
		void set(vlBool bCreateLODControlResource)
		{
			this->chkCreateLODControlResource->Checked = bCreateLODControlResource > 0;
		}
	}

	public: property vlUInt LODControlClampU
	{
		vlUInt get()
		{
			return Convert::ToUInt32(this->numLODControlClampU->Value);
		}
		void set(vlUInt uiLODControlClampU)
		{
			this->SetNumericUpDownValue(this->numLODControlClampU, Convert::ToDecimal(uiLODControlClampU));
		}
	}

	public: property vlUInt LODControlClampV
	{
		vlUInt get()
		{
			return Convert::ToUInt32(this->numLODControlClampV->Value);
		}
		void set(vlUInt uiLODControlClampV)
		{
			this->SetNumericUpDownValue(this->numLODControlClampV, Convert::ToDecimal(uiLODControlClampV));
		}
	}

	private: System::Void SetNumericUpDownValue(NumericUpDown^ Control, System::Decimal dValue)
	{
		if (dValue < Control->Minimum)
		{
			Control->Value = Control->Minimum;
		}
		else if (dValue > Control->Maximum)
		{
			Control->Value = Control->Maximum;
		}
		else
		{
			Control->Value = dValue;
		}
	}

		   // LOD Control Resource

	public: property vlBool CreateInformationResource
	{
		vlBool get()
		{
			return this->chkCreateInformationResource->Checked == true;
		}
		void set(vlBool bCreateInformationResource)
		{
			this->chkCreateInformationResource->Checked = bCreateInformationResource > 0;
		}
	}

	public: property String^ InformationAuthor
	{
		String^ get()
		{
			return this->txtInformationAuthor->Text;
		}
		void set(String^ sInformationAuthor)
		{
			this->txtInformationAuthor->Text = sInformationAuthor;
		}
	}

	public: property String^ InformationContact
	{
		String^ get()
		{
			return this->txtInformationContact->Text;
		}
		void set(String^ sInformationContact)
		{
			this->txtInformationContact->Text = sInformationContact;
		}
	}

	public: property String^ InformationVersion
	{
		String^ get()
		{
			return this->txtInformationVersion->Text;
		}
		void set(String^ sInformationVersion)
		{
			this->txtInformationVersion->Text = sInformationVersion;
		}
	}

	public: property String^ InformationModification
	{
		String^ get()
		{
			return this->txtInformationModification->Text;
		}
		void set(String^ sInformationModification)
		{
			this->txtInformationModification->Text = sInformationModification;
		}
	}

	public: property String^ InformationDescription
	{
		String^ get()
		{
			return this->txtInformationDescription->Text;
		}
		void set(String^ sInformationDescription)
		{
			this->txtInformationDescription->Text = sInformationDescription;
		}
	}

	public: property String^ InformationComments
	{
		String^ get()
		{
			return this->txtInformationComments->Text;
		}
		void set(String^ sInformationComments)
		{
			this->txtInformationComments->Text = sInformationComments;
		}
	}

	private: System::Void CVTFResources_Load(System::Object^ sender, System::EventArgs^ e)
	{
	}

	private: System::Void chkCreateLODControlResource_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		this->numLODControlClampU->Enabled = this->chkCreateLODControlResource->Checked;
		this->numLODControlClampV->Enabled = this->chkCreateLODControlResource->Checked;
	}

	private: System::Void chkCreateInformationResource_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		this->txtInformationAuthor->Enabled = this->chkCreateInformationResource->Checked;
		this->txtInformationContact->Enabled = this->chkCreateInformationResource->Checked;
		this->txtInformationVersion->Enabled = this->chkCreateInformationResource->Checked;
		this->txtInformationModification->Enabled = this->chkCreateInformationResource->Checked;
		this->txtInformationDescription->Enabled = this->chkCreateInformationResource->Checked;
		this->txtInformationComments->Enabled = this->chkCreateInformationResource->Checked;
	}

	private: System::Void btnReset_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->chkCreateLODControlResource->Checked = false;
		this->numLODControlClampU->Value = this->numLODControlClampU->Maximum;
		this->numLODControlClampV->Value = this->numLODControlClampV->Maximum;

		this->chkCreateInformationResource->Checked = false;
		this->txtInformationAuthor->Clear();
		this->txtInformationContact->Clear();
		this->txtInformationVersion->Clear();
		this->txtInformationModification->Clear();
		this->txtInformationDescription->Clear();
		this->txtInformationComments->Clear();
		this->chkCreateLODControlResource_CheckedChanged(this, System::EventArgs::Empty);
		this->chkCreateInformationResource_CheckedChanged(this, System::EventArgs::Empty);
	}

	private: System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
	}

	private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
	}
	private: System::Void grpMipmaps_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}