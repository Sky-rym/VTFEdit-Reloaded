/*
 * VTFEdit
 * Copyright (C) 2005-2011 Neil Jedrzejewski & Ryan Gregg
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

namespace VTFEdit
{
	public ref class CAbout : public System::Windows::Forms::Form
	{
	public: 
		CAbout(void)
		{
			this->InitializeComponent();

			this->lblVTFLibVersion->Text = String::Concat("VTFLib Version: ", gcnew String(vlGetVersionString()));
		}

	private: System::Windows::Forms::Button ^ btnOK;
	private: System::Windows::Forms::GroupBox ^ grpAbout;

	private: System::Windows::Forms::Label ^ lblLanguage;

	private: System::Windows::Forms::Label ^ lblAuthor;
	private: System::Windows::Forms::LinkLabel ^ lnkNemsTools;
	private: System::Windows::Forms::PictureBox ^ picIcon;
	private: System::Windows::Forms::LinkLabel ^ lnkWunderboy;

	private: System::Windows::Forms::Label ^ lblVTFEditVersion;
	private: System::Windows::Forms::Label^ lblVTFLibVersion;
	private: System::Windows::Forms::LinkLabel^ linkLabel1;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^ components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CAbout::typeid));
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->grpAbout = (gcnew System::Windows::Forms::GroupBox());
			this->lblVTFLibVersion = (gcnew System::Windows::Forms::Label());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->lnkWunderboy = (gcnew System::Windows::Forms::LinkLabel());
			this->lblLanguage = (gcnew System::Windows::Forms::Label());
			this->lblAuthor = (gcnew System::Windows::Forms::Label());
			this->lblVTFEditVersion = (gcnew System::Windows::Forms::Label());
			this->lnkNemsTools = (gcnew System::Windows::Forms::LinkLabel());
			this->picIcon = (gcnew System::Windows::Forms::PictureBox());
			this->grpAbout->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picIcon))->BeginInit();
			this->SuspendLayout();
			// 
			// btnOK
			// 
			this->btnOK->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnOK->Location = System::Drawing::Point(232, 207);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(263, 26);
			this->btnOK->TabIndex = 0;
			this->btnOK->Text = L"&OK";
			this->btnOK->Click += gcnew System::EventHandler(this, &CAbout::btnOK_Click);
			// 
			// grpAbout
			// 
			this->grpAbout->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->grpAbout->Controls->Add(this->lblVTFLibVersion);
			this->grpAbout->Controls->Add(this->btnOK);
			this->grpAbout->Controls->Add(this->linkLabel1);
			this->grpAbout->Controls->Add(this->lnkWunderboy);
			this->grpAbout->Controls->Add(this->lblLanguage);
			this->grpAbout->Controls->Add(this->lblAuthor);
			this->grpAbout->Controls->Add(this->lblVTFEditVersion);
			this->grpAbout->Controls->Add(this->lnkNemsTools);
			this->grpAbout->Controls->Add(this->picIcon);
			this->grpAbout->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpAbout->Location = System::Drawing::Point(6, 6);
			this->grpAbout->Name = L"grpAbout";
			this->grpAbout->Size = System::Drawing::Size(499, 239);
			this->grpAbout->TabIndex = 1;
			this->grpAbout->TabStop = false;
			// 
			// lblVTFLibVersion
			// 
			this->lblVTFLibVersion->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->lblVTFLibVersion->Location = System::Drawing::Point(233, 115);
			this->lblVTFLibVersion->Name = L"lblVTFLibVersion";
			this->lblVTFLibVersion->Size = System::Drawing::Size(163, 19);
			this->lblVTFLibVersion->TabIndex = 2;
			this->lblVTFLibVersion->Text = L"VTFLib Version: X.X.X";
			// 
			// linkLabel1
			// 
			this->linkLabel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->linkLabel1->LinkColor = System::Drawing::Color::Black;
			this->linkLabel1->Location = System::Drawing::Point(327, 151);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(65, 20);
			this->linkLabel1->TabIndex = 8;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"froggi.es";
			this->linkLabel1->VisitedLinkColor = System::Drawing::Color::Black;
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &CAbout::linkLabel1_LinkClicked);
			// 
			// lnkWunderboy
			// 
			this->lnkWunderboy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->lnkWunderboy->LinkColor = System::Drawing::Color::Black;
			this->lnkWunderboy->Location = System::Drawing::Point(390, 180);
			this->lnkWunderboy->Name = L"lnkWunderboy";
			this->lnkWunderboy->Size = System::Drawing::Size(102, 22);
			this->lnkWunderboy->TabIndex = 6;
			this->lnkWunderboy->TabStop = true;
			this->lnkWunderboy->Text = L"wunderboy.org";
			this->lnkWunderboy->VisitedLinkColor = System::Drawing::Color::Black;
			this->lnkWunderboy->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &CAbout::lnkWunderboy_LinkClicked);
			// 
			// lblLanguage
			// 
			this->lblLanguage->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->lblLanguage->Location = System::Drawing::Point(232, 94);
			this->lblLanguage->Name = L"lblLanguage";
			this->lblLanguage->Size = System::Drawing::Size(101, 21);
			this->lblLanguage->TabIndex = 4;
			this->lblLanguage->Text = L"Written In: C++";
			// 
			// lblAuthor
			// 
			this->lblAuthor->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->lblAuthor->Location = System::Drawing::Point(232, 45);
			this->lblAuthor->Name = L"lblAuthor";
			this->lblAuthor->Size = System::Drawing::Size(264, 39);
			this->lblAuthor->TabIndex = 2;
			this->lblAuthor->Text = L"Authors: IAmKnotMax, Skyrym, misyltoad, Neil Jedrzejewski && Ryan Gregg";
			// 
			// lblVTFEditVersion
			// 
			this->lblVTFEditVersion->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->lblVTFEditVersion->Location = System::Drawing::Point(317, 16);
			this->lblVTFEditVersion->Name = L"lblVTFEditVersion";
			this->lblVTFEditVersion->Size = System::Drawing::Size(99, 20);
			this->lblVTFEditVersion->TabIndex = 1;
			this->lblVTFEditVersion->Text = L"Version: 2.1.3";
			// 
			// lnkNemsTools
			// 
			this->lnkNemsTools->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->lnkNemsTools->LinkColor = System::Drawing::Color::Black;
			this->lnkNemsTools->Location = System::Drawing::Point(231, 182);
			this->lnkNemsTools->Name = L"lnkNemsTools";
			this->lnkNemsTools->Size = System::Drawing::Size(104, 22);
			this->lnkNemsTools->TabIndex = 7;
			this->lnkNemsTools->TabStop = true;
			this->lnkNemsTools->Text = L"nemesis.twl.net";
			this->lnkNemsTools->VisitedLinkColor = System::Drawing::Color::Black;
			this->lnkNemsTools->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &CAbout::lnkNemsTools_LinkClicked);
			// 
			// picIcon
			// 
			this->picIcon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picIcon.Image")));
			this->picIcon->Location = System::Drawing::Point(6, 12);
			this->picIcon->Name = L"picIcon";
			this->picIcon->Size = System::Drawing::Size(220, 220);
			this->picIcon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->picIcon->TabIndex = 0;
			this->picIcon->TabStop = false;
			// 
			// CAbout
			// 
			this->AcceptButton = this->btnOK;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(510, 251);
			this->Controls->Add(this->grpAbout);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"CAbout";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"About VTFEdit Reloaded";
			this->grpAbout->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picIcon))->EndInit();
			this->ResumeLayout(false);

		}

		private: System::Void lnkWunderboy_LinkClicked(System::Object ^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs ^ e)
		{
			try
			{
				System::Diagnostics::Process::Start("http://www.wunderboy.org/");
			}
			catch(Exception ^)
			{

			}
		}

		private: System::Void lnkNemsTools_LinkClicked(System::Object ^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs ^ e)
		{
			try
			{
				System::Diagnostics::Process::Start("https://nemstools.github.io/");
			}
			catch(Exception ^)
			{

			}
		}

		private: System::Void btnOK_Click(System::Object ^ sender, System::EventArgs ^ e)
		{
			this->Close();
		}

		private: System::Void linkLabel1_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
		{
			try
			{
				System::Diagnostics::Process::Start("https://froggi.es");
			}
			catch(Exception ^)
			{

			}
		}
};

}

