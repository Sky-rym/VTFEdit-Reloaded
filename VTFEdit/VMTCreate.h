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

#include "VMTFileUtility.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace VTFEdit
{
	public ref class CVMTCreate : public System::Windows::Forms::Form
	{
	public: 
		CVMTCreate(void)
		{
			this->InitializeComponent();
		}

	private: System::Windows::Forms::OpenFileDialog ^  dlgOpenVTFFile;
	private: System::Windows::Forms::GroupBox ^  grpTextures;
	public: System::Windows::Forms::Button ^  btnBaseTexture1;
	public: System::Windows::Forms::TextBox ^  txtBaseTexture1;
	private: System::Windows::Forms::Label ^  lblBaseTexture1;
	private: System::Windows::Forms::TabControl ^  tabMain;
	private: System::Windows::Forms::TabPage ^  tabTextures;
	private: System::Windows::Forms::Button ^  btnBumpTexture1;
	public: System::Windows::Forms::TextBox ^  txtBumpTexture1;
	private: System::Windows::Forms::Label ^  lblBumpTexture1;
	private: System::Windows::Forms::Button ^  btnEnviromentTexture;
	public: System::Windows::Forms::TextBox ^  txtEnviromentTexture;
	private: System::Windows::Forms::Label ^  lblEnviromentTexture;
	private: System::Windows::Forms::Button ^  btnEnviromentMaskTexture;
	public: System::Windows::Forms::TextBox ^  txtEnviromentMaskTexture;
	private: System::Windows::Forms::Label ^  lblEnviromentMaskTexture;
	private: System::Windows::Forms::Button ^  btnDetailTexture;
	public: System::Windows::Forms::TextBox ^  txtDetailTexture;
	private: System::Windows::Forms::Label ^  lblDetailTexture;
	private: System::Windows::Forms::ToolTip ^  tipMain;
	private: System::Windows::Forms::Button ^  btnClose;
	public: System::Windows::Forms::Button ^  btnCreate;
	private: System::Windows::Forms::Button ^  btnToolTexture;
	public: System::Windows::Forms::TextBox ^  txtToolTexture;
	private: System::Windows::Forms::Label ^  lblToolTexture;
	private: System::Windows::Forms::Button ^  btnBumpTexture2;
	public: System::Windows::Forms::TextBox ^  txtBumpTexture2;
	private: System::Windows::Forms::Label ^  lblBumpTexture2;
	private: System::Windows::Forms::Label ^  lblBaseTexture2;
	private: System::Windows::Forms::Button ^  btnNormalTexture;
	public: System::Windows::Forms::TextBox ^  txtNormalTexture;
	private: System::Windows::Forms::Label ^  lblNormalTexture;
	private: System::Windows::Forms::Button ^  btnDuDvTexture;
	public: System::Windows::Forms::TextBox ^  txtDuDvTexture;
	private: System::Windows::Forms::Label ^  lblDuDvTexture;
	private: System::Windows::Forms::Button ^  btnBaseTexture2;
	public: System::Windows::Forms::TextBox ^  txtBaseTexture2;
	private: System::Windows::Forms::TabPage ^  tabOptions;
	private: System::Windows::Forms::GroupBox ^  grpOptions;
	private: System::Windows::Forms::Button ^  btnClear;
	public: System::Windows::Forms::SaveFileDialog ^  dlgSaveVMTFile;
	private: System::Windows::Forms::Label ^  lblShader;
	public: System::Windows::Forms::ComboBox ^  cboShader;
	public: System::Windows::Forms::ComboBox ^  cboSurface1;
	private: System::Windows::Forms::Label ^  lblSurface1;
	public: System::Windows::Forms::ComboBox ^  cboSurface2;
	private: System::Windows::Forms::Label ^  lblSurface2;
	private: System::Windows::Forms::Label ^  lblKeywords;
	public: System::Windows::Forms::TextBox ^  txtKeywords;
	public: System::Windows::Forms::CheckBox ^  chkTranslucent;
	public: System::Windows::Forms::CheckBox ^  chkAdditive;
	public: System::Windows::Forms::CheckBox ^  chkNoCull;
	public: System::Windows::Forms::CheckBox ^  chkAlphaTest;
	public: System::Windows::Forms::CheckBox ^  chkNoLOD;
	public: System::Windows::Forms::CheckBox ^  chkNoDecal;
	public: System::Windows::Forms::CheckBox ^  chkVertexColor;
	public: System::Windows::Forms::CheckBox ^  chkVertexAlpha;
	public: System::Windows::Forms::CheckBox^ chkModel;
	public: System::Windows::Forms::CheckBox^ chkDecal;
	public: System::Windows::Forms::CheckBox^ chkHalfLambert;
	public: System::Windows::Forms::CheckBox^ chkIgnoreZ;
	public: System::Windows::Forms::CheckBox^ chkNoFog;
	public: System::Windows::Forms::CheckBox^ chkAlphaCoverage;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(CVMTCreate::typeid));
			this->grpTextures = (gcnew System::Windows::Forms::GroupBox());
			this->btnNormalTexture = (gcnew System::Windows::Forms::Button());
			this->txtNormalTexture = (gcnew System::Windows::Forms::TextBox());
			this->lblNormalTexture = (gcnew System::Windows::Forms::Label());
			this->btnDuDvTexture = (gcnew System::Windows::Forms::Button());
			this->txtDuDvTexture = (gcnew System::Windows::Forms::TextBox());
			this->lblDuDvTexture = (gcnew System::Windows::Forms::Label());
			this->btnBumpTexture2 = (gcnew System::Windows::Forms::Button());
			this->txtBumpTexture2 = (gcnew System::Windows::Forms::TextBox());
			this->lblBumpTexture2 = (gcnew System::Windows::Forms::Label());
			this->btnBaseTexture2 = (gcnew System::Windows::Forms::Button());
			this->txtBaseTexture2 = (gcnew System::Windows::Forms::TextBox());
			this->lblBaseTexture2 = (gcnew System::Windows::Forms::Label());
			this->btnToolTexture = (gcnew System::Windows::Forms::Button());
			this->txtToolTexture = (gcnew System::Windows::Forms::TextBox());
			this->lblToolTexture = (gcnew System::Windows::Forms::Label());
			this->btnDetailTexture = (gcnew System::Windows::Forms::Button());
			this->txtDetailTexture = (gcnew System::Windows::Forms::TextBox());
			this->lblDetailTexture = (gcnew System::Windows::Forms::Label());
			this->btnEnviromentMaskTexture = (gcnew System::Windows::Forms::Button());
			this->txtEnviromentMaskTexture = (gcnew System::Windows::Forms::TextBox());
			this->lblEnviromentMaskTexture = (gcnew System::Windows::Forms::Label());
			this->btnEnviromentTexture = (gcnew System::Windows::Forms::Button());
			this->txtEnviromentTexture = (gcnew System::Windows::Forms::TextBox());
			this->lblEnviromentTexture = (gcnew System::Windows::Forms::Label());
			this->btnBumpTexture1 = (gcnew System::Windows::Forms::Button());
			this->txtBumpTexture1 = (gcnew System::Windows::Forms::TextBox());
			this->lblBumpTexture1 = (gcnew System::Windows::Forms::Label());
			this->btnBaseTexture1 = (gcnew System::Windows::Forms::Button());
			this->txtBaseTexture1 = (gcnew System::Windows::Forms::TextBox());
			this->lblBaseTexture1 = (gcnew System::Windows::Forms::Label());
			this->dlgOpenVTFFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tabMain = (gcnew System::Windows::Forms::TabControl());
			this->tabTextures = (gcnew System::Windows::Forms::TabPage());
			this->tabOptions = (gcnew System::Windows::Forms::TabPage());
			this->grpOptions = (gcnew System::Windows::Forms::GroupBox());
			this->chkHalfLambert = (gcnew System::Windows::Forms::CheckBox());
			this->chkIgnoreZ = (gcnew System::Windows::Forms::CheckBox());
			this->chkNoFog = (gcnew System::Windows::Forms::CheckBox());
			this->chkDecal = (gcnew System::Windows::Forms::CheckBox());
			this->chkModel = (gcnew System::Windows::Forms::CheckBox());
			this->txtKeywords = (gcnew System::Windows::Forms::TextBox());
			this->chkVertexAlpha = (gcnew System::Windows::Forms::CheckBox());
			this->chkVertexColor = (gcnew System::Windows::Forms::CheckBox());
			this->chkNoDecal = (gcnew System::Windows::Forms::CheckBox());
			this->chkNoLOD = (gcnew System::Windows::Forms::CheckBox());
			this->chkAlphaTest = (gcnew System::Windows::Forms::CheckBox());
			this->chkNoCull = (gcnew System::Windows::Forms::CheckBox());
			this->chkAdditive = (gcnew System::Windows::Forms::CheckBox());
			this->chkTranslucent = (gcnew System::Windows::Forms::CheckBox());
			this->lblKeywords = (gcnew System::Windows::Forms::Label());
			this->cboSurface2 = (gcnew System::Windows::Forms::ComboBox());
			this->lblSurface2 = (gcnew System::Windows::Forms::Label());
			this->cboSurface1 = (gcnew System::Windows::Forms::ComboBox());
			this->lblSurface1 = (gcnew System::Windows::Forms::Label());
			this->cboShader = (gcnew System::Windows::Forms::ComboBox());
			this->lblShader = (gcnew System::Windows::Forms::Label());
			this->tipMain = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->btnCreate = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->dlgSaveVMTFile = (gcnew System::Windows::Forms::SaveFileDialog());
			this->chkAlphaCoverage = (gcnew System::Windows::Forms::CheckBox());
			this->grpTextures->SuspendLayout();
			this->tabMain->SuspendLayout();
			this->tabTextures->SuspendLayout();
			this->tabOptions->SuspendLayout();
			this->grpOptions->SuspendLayout();
			this->SuspendLayout();
			// 
			// grpTextures
			// 
			this->grpTextures->Controls->Add(this->btnNormalTexture);
			this->grpTextures->Controls->Add(this->txtNormalTexture);
			this->grpTextures->Controls->Add(this->lblNormalTexture);
			this->grpTextures->Controls->Add(this->btnDuDvTexture);
			this->grpTextures->Controls->Add(this->txtDuDvTexture);
			this->grpTextures->Controls->Add(this->lblDuDvTexture);
			this->grpTextures->Controls->Add(this->btnBumpTexture2);
			this->grpTextures->Controls->Add(this->txtBumpTexture2);
			this->grpTextures->Controls->Add(this->lblBumpTexture2);
			this->grpTextures->Controls->Add(this->btnBaseTexture2);
			this->grpTextures->Controls->Add(this->txtBaseTexture2);
			this->grpTextures->Controls->Add(this->lblBaseTexture2);
			this->grpTextures->Controls->Add(this->btnToolTexture);
			this->grpTextures->Controls->Add(this->txtToolTexture);
			this->grpTextures->Controls->Add(this->lblToolTexture);
			this->grpTextures->Controls->Add(this->btnDetailTexture);
			this->grpTextures->Controls->Add(this->txtDetailTexture);
			this->grpTextures->Controls->Add(this->lblDetailTexture);
			this->grpTextures->Controls->Add(this->btnEnviromentMaskTexture);
			this->grpTextures->Controls->Add(this->txtEnviromentMaskTexture);
			this->grpTextures->Controls->Add(this->lblEnviromentMaskTexture);
			this->grpTextures->Controls->Add(this->btnEnviromentTexture);
			this->grpTextures->Controls->Add(this->txtEnviromentTexture);
			this->grpTextures->Controls->Add(this->lblEnviromentTexture);
			this->grpTextures->Controls->Add(this->btnBumpTexture1);
			this->grpTextures->Controls->Add(this->txtBumpTexture1);
			this->grpTextures->Controls->Add(this->lblBumpTexture1);
			this->grpTextures->Controls->Add(this->btnBaseTexture1);
			this->grpTextures->Controls->Add(this->txtBaseTexture1);
			this->grpTextures->Controls->Add(this->lblBaseTexture1);
			this->grpTextures->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpTextures->Location = System::Drawing::Point(6, 6);
			this->grpTextures->Name = L"grpTextures";
			this->grpTextures->Size = System::Drawing::Size(311, 209);
			this->grpTextures->TabIndex = 0;
			this->grpTextures->TabStop = false;
			this->grpTextures->Text = L"Textures:";
			// 
			// btnNormalTexture
			// 
			this->btnNormalTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnNormalTexture->Location = System::Drawing::Point(292, 164);
			this->btnNormalTexture->Name = L"btnNormalTexture";
			this->btnNormalTexture->Size = System::Drawing::Size(15, 16);
			this->btnNormalTexture->TabIndex = 26;
			this->btnNormalTexture->Text = L"...";
			this->btnNormalTexture->Click += gcnew System::EventHandler(this, &CVMTCreate::btnNormalTexture_Click);
			// 
			// txtNormalTexture
			// 
			this->txtNormalTexture->Location = System::Drawing::Point(93, 160);
			this->txtNormalTexture->Name = L"txtNormalTexture";
			this->txtNormalTexture->Size = System::Drawing::Size(195, 20);
			this->txtNormalTexture->TabIndex = 25;
			this->tipMain->SetToolTip(this->txtNormalTexture, L"$normalmap");
			this->txtNormalTexture->TextChanged += gcnew System::EventHandler(this, &CVMTCreate::txtNormalTexture_TextChanged);
			this->txtNormalTexture->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblNormalTexture
			// 
			this->lblNormalTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblNormalTexture->Location = System::Drawing::Point(6, 162);
			this->lblNormalTexture->Name = L"lblNormalTexture";
			this->lblNormalTexture->Size = System::Drawing::Size(83, 19);
			this->lblNormalTexture->TabIndex = 24;
			this->lblNormalTexture->Text = L"Normal Map:";
			// 
			// btnDuDvTexture
			// 
			this->btnDuDvTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnDuDvTexture->Location = System::Drawing::Point(292, 183);
			this->btnDuDvTexture->Name = L"btnDuDvTexture";
			this->btnDuDvTexture->Size = System::Drawing::Size(15, 16);
			this->btnDuDvTexture->TabIndex = 29;
			this->btnDuDvTexture->Text = L"...";
			this->btnDuDvTexture->Click += gcnew System::EventHandler(this, &CVMTCreate::btnDuDvTexture_Click);
			// 
			// txtDuDvTexture
			// 
			this->txtDuDvTexture->Location = System::Drawing::Point(93, 179);
			this->txtDuDvTexture->Name = L"txtDuDvTexture";
			this->txtDuDvTexture->Size = System::Drawing::Size(195, 20);
			this->txtDuDvTexture->TabIndex = 28;
			this->tipMain->SetToolTip(this->txtDuDvTexture, L"$dudvmap");
			this->txtDuDvTexture->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblDuDvTexture
			// 
			this->lblDuDvTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblDuDvTexture->Location = System::Drawing::Point(6, 182);
			this->lblDuDvTexture->Name = L"lblDuDvTexture";
			this->lblDuDvTexture->Size = System::Drawing::Size(83, 18);
			this->lblDuDvTexture->TabIndex = 27;
			this->lblDuDvTexture->Text = L"DuDv Map:";
			// 
			// btnBumpTexture2
			// 
			this->btnBumpTexture2->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnBumpTexture2->Location = System::Drawing::Point(292, 70);
			this->btnBumpTexture2->Name = L"btnBumpTexture2";
			this->btnBumpTexture2->Size = System::Drawing::Size(15, 16);
			this->btnBumpTexture2->TabIndex = 11;
			this->btnBumpTexture2->Text = L"...";
			this->btnBumpTexture2->Click += gcnew System::EventHandler(this, &CVMTCreate::btnBumpTexture2_Click);
			// 
			// txtBumpTexture2
			// 
			this->txtBumpTexture2->Location = System::Drawing::Point(93, 67);
			this->txtBumpTexture2->Name = L"txtBumpTexture2";
			this->txtBumpTexture2->Size = System::Drawing::Size(195, 20);
			this->txtBumpTexture2->TabIndex = 10;
			this->tipMain->SetToolTip(this->txtBumpTexture2, L"$bumpmap2");
			this->txtBumpTexture2->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblBumpTexture2
			// 
			this->lblBumpTexture2->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblBumpTexture2->Location = System::Drawing::Point(6, 70);
			this->lblBumpTexture2->Name = L"lblBumpTexture2";
			this->lblBumpTexture2->Size = System::Drawing::Size(83, 18);
			this->lblBumpTexture2->TabIndex = 9;
			this->lblBumpTexture2->Text = L"Bump Map 2:";
			// 
			// btnBaseTexture2
			// 
			this->btnBaseTexture2->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnBaseTexture2->Location = System::Drawing::Point(292, 51);
			this->btnBaseTexture2->Name = L"btnBaseTexture2";
			this->btnBaseTexture2->Size = System::Drawing::Size(15, 15);
			this->btnBaseTexture2->TabIndex = 8;
			this->btnBaseTexture2->Text = L"...";
			this->btnBaseTexture2->Click += gcnew System::EventHandler(this, &CVMTCreate::btnBaseTexture2_Click);
			// 
			// txtBaseTexture2
			// 
			this->txtBaseTexture2->Location = System::Drawing::Point(93, 49);
			this->txtBaseTexture2->Name = L"txtBaseTexture2";
			this->txtBaseTexture2->Size = System::Drawing::Size(195, 20);
			this->txtBaseTexture2->TabIndex = 7;
			this->tipMain->SetToolTip(this->txtBaseTexture2, L"$basetexture2");
			this->txtBaseTexture2->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblBaseTexture2
			// 
			this->lblBaseTexture2->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblBaseTexture2->Location = System::Drawing::Point(6, 51);
			this->lblBaseTexture2->Name = L"lblBaseTexture2";
			this->lblBaseTexture2->Size = System::Drawing::Size(83, 17);
			this->lblBaseTexture2->TabIndex = 6;
			this->lblBaseTexture2->Text = L"Base Texture 2:";
			// 
			// btnToolTexture
			// 
			this->btnToolTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnToolTexture->Location = System::Drawing::Point(292, 145);
			this->btnToolTexture->Name = L"btnToolTexture";
			this->btnToolTexture->Size = System::Drawing::Size(15, 16);
			this->btnToolTexture->TabIndex = 23;
			this->btnToolTexture->Text = L"...";
			this->btnToolTexture->Click += gcnew System::EventHandler(this, &CVMTCreate::btnToolTexture_Click);
			// 
			// txtToolTexture
			// 
			this->txtToolTexture->Location = System::Drawing::Point(93, 141);
			this->txtToolTexture->Name = L"txtToolTexture";
			this->txtToolTexture->Size = System::Drawing::Size(195, 20);
			this->txtToolTexture->TabIndex = 22;
			this->tipMain->SetToolTip(this->txtToolTexture, L"%tooltexture");
			this->txtToolTexture->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblToolTexture
			// 
			this->lblToolTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblToolTexture->Location = System::Drawing::Point(6, 143);
			this->lblToolTexture->Name = L"lblToolTexture";
			this->lblToolTexture->Size = System::Drawing::Size(83, 19);
			this->lblToolTexture->TabIndex = 21;
			this->lblToolTexture->Text = L"Tool Texture:";
			// 
			// btnDetailTexture
			// 
			this->btnDetailTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnDetailTexture->Location = System::Drawing::Point(292, 127);
			this->btnDetailTexture->Name = L"btnDetailTexture";
			this->btnDetailTexture->Size = System::Drawing::Size(15, 15);
			this->btnDetailTexture->TabIndex = 20;
			this->btnDetailTexture->Text = L"...";
			this->btnDetailTexture->Click += gcnew System::EventHandler(this, &CVMTCreate::btnDetailTexture_Click);
			// 
			// txtDetailTexture
			// 
			this->txtDetailTexture->Location = System::Drawing::Point(93, 122);
			this->txtDetailTexture->Name = L"txtDetailTexture";
			this->txtDetailTexture->Size = System::Drawing::Size(195, 20);
			this->txtDetailTexture->TabIndex = 19;
			this->tipMain->SetToolTip(this->txtDetailTexture, L"$detail");
			this->txtDetailTexture->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblDetailTexture
			// 
			this->lblDetailTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblDetailTexture->Location = System::Drawing::Point(6, 125);
			this->lblDetailTexture->Name = L"lblDetailTexture";
			this->lblDetailTexture->Size = System::Drawing::Size(83, 17);
			this->lblDetailTexture->TabIndex = 18;
			this->lblDetailTexture->Text = L"Detail Texture:";
			// 
			// btnEnviromentMaskTexture
			// 
			this->btnEnviromentMaskTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnEnviromentMaskTexture->Location = System::Drawing::Point(292, 107);
			this->btnEnviromentMaskTexture->Name = L"btnEnviromentMaskTexture";
			this->btnEnviromentMaskTexture->Size = System::Drawing::Size(15, 16);
			this->btnEnviromentMaskTexture->TabIndex = 17;
			this->btnEnviromentMaskTexture->Text = L"...";
			this->btnEnviromentMaskTexture->Click += gcnew System::EventHandler(this, &CVMTCreate::btnEnviromentMaskTexture_Click);
			// 
			// txtEnviromentMaskTexture
			// 
			this->txtEnviromentMaskTexture->Location = System::Drawing::Point(93, 104);
			this->txtEnviromentMaskTexture->Name = L"txtEnviromentMaskTexture";
			this->txtEnviromentMaskTexture->Size = System::Drawing::Size(195, 20);
			this->txtEnviromentMaskTexture->TabIndex = 16;
			this->tipMain->SetToolTip(this->txtEnviromentMaskTexture, L"$envmapmask");
			this->txtEnviromentMaskTexture->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblEnviromentMaskTexture
			// 
			this->lblEnviromentMaskTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblEnviromentMaskTexture->Location = System::Drawing::Point(6, 107);
			this->lblEnviromentMaskTexture->Name = L"lblEnviromentMaskTexture";
			this->lblEnviromentMaskTexture->Size = System::Drawing::Size(92, 18);
			this->lblEnviromentMaskTexture->TabIndex = 15;
			this->lblEnviromentMaskTexture->Text = L"Enviroment Mask:";
			// 
			// btnEnviromentTexture
			// 
			this->btnEnviromentTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnEnviromentTexture->Location = System::Drawing::Point(292, 88);
			this->btnEnviromentTexture->Name = L"btnEnviromentTexture";
			this->btnEnviromentTexture->Size = System::Drawing::Size(15, 16);
			this->btnEnviromentTexture->TabIndex = 14;
			this->btnEnviromentTexture->Text = L"...";
			this->btnEnviromentTexture->Click += gcnew System::EventHandler(this, &CVMTCreate::btnEnviromentTexture_Click);
			// 
			// txtEnviromentTexture
			// 
			this->txtEnviromentTexture->Location = System::Drawing::Point(93, 85);
			this->txtEnviromentTexture->Name = L"txtEnviromentTexture";
			this->txtEnviromentTexture->Size = System::Drawing::Size(195, 20);
			this->txtEnviromentTexture->TabIndex = 13;
			this->tipMain->SetToolTip(this->txtEnviromentTexture, L"$envmap");
			this->txtEnviromentTexture->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblEnviromentTexture
			// 
			this->lblEnviromentTexture->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblEnviromentTexture->Location = System::Drawing::Point(6, 88);
			this->lblEnviromentTexture->Name = L"lblEnviromentTexture";
			this->lblEnviromentTexture->Size = System::Drawing::Size(83, 19);
			this->lblEnviromentTexture->TabIndex = 12;
			this->lblEnviromentTexture->Text = L"Enviroment:";
			// 
			// btnBumpTexture1
			// 
			this->btnBumpTexture1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnBumpTexture1->Location = System::Drawing::Point(292, 31);
			this->btnBumpTexture1->Name = L"btnBumpTexture1";
			this->btnBumpTexture1->Size = System::Drawing::Size(15, 16);
			this->btnBumpTexture1->TabIndex = 5;
			this->btnBumpTexture1->Text = L"...";
			this->btnBumpTexture1->Click += gcnew System::EventHandler(this, &CVMTCreate::btnBumpTexture1_Click);
			// 
			// txtBumpTexture1
			// 
			this->txtBumpTexture1->Location = System::Drawing::Point(93, 31);
			this->txtBumpTexture1->Name = L"txtBumpTexture1";
			this->txtBumpTexture1->Size = System::Drawing::Size(195, 20);
			this->txtBumpTexture1->TabIndex = 4;
			this->tipMain->SetToolTip(this->txtBumpTexture1, L"$bumpmap");
			this->txtBumpTexture1->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblBumpTexture1
			// 
			this->lblBumpTexture1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblBumpTexture1->Location = System::Drawing::Point(6, 33);
			this->lblBumpTexture1->Name = L"lblBumpTexture1";
			this->lblBumpTexture1->Size = System::Drawing::Size(83, 19);
			this->lblBumpTexture1->TabIndex = 3;
			this->lblBumpTexture1->Text = L"Bump Map 1:";
			// 
			// btnBaseTexture1
			// 
			this->btnBaseTexture1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnBaseTexture1->Location = System::Drawing::Point(292, 12);
			this->btnBaseTexture1->Name = L"btnBaseTexture1";
			this->btnBaseTexture1->Size = System::Drawing::Size(15, 17);
			this->btnBaseTexture1->TabIndex = 2;
			this->btnBaseTexture1->Text = L"...";
			this->btnBaseTexture1->Click += gcnew System::EventHandler(this, &CVMTCreate::btnBaseTexture1_Click);
			// 
			// txtBaseTexture1
			// 
			this->txtBaseTexture1->Location = System::Drawing::Point(93, 12);
			this->txtBaseTexture1->Name = L"txtBaseTexture1";
			this->txtBaseTexture1->Size = System::Drawing::Size(195, 20);
			this->txtBaseTexture1->TabIndex = 1;
			this->tipMain->SetToolTip(this->txtBaseTexture1, L"$basetexture");
			this->txtBaseTexture1->TextChanged += gcnew System::EventHandler(this, &CVMTCreate::txtBaseTexture1_TextChanged);
			this->txtBaseTexture1->Leave += gcnew System::EventHandler(this, &CVMTCreate::txtTexture_Leave);
			// 
			// lblBaseTexture1
			// 
			this->lblBaseTexture1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblBaseTexture1->Location = System::Drawing::Point(6, 14);
			this->lblBaseTexture1->Name = L"lblBaseTexture1";
			this->lblBaseTexture1->Size = System::Drawing::Size(83, 19);
			this->lblBaseTexture1->TabIndex = 0;
			this->lblBaseTexture1->Text = L"Base Texture 1:";
			// 
			// dlgOpenVTFFile
			// 
			this->dlgOpenVTFFile->Filter = L"VTF Files (*.vtf)|*.vtf";
			this->dlgOpenVTFFile->Title = L"Open VTF File";
			// 
			// tabMain
			// 
			this->tabMain->Controls->Add(this->tabTextures);
			this->tabMain->Controls->Add(this->tabOptions);
			this->tabMain->Location = System::Drawing::Point(6, 6);
			this->tabMain->Name = L"tabMain";
			this->tabMain->SelectedIndex = 0;
			this->tabMain->Size = System::Drawing::Size(324, 236);
			this->tabMain->TabIndex = 0;
			// 
			// tabTextures
			// 
			this->tabTextures->Controls->Add(this->grpTextures);
			this->tabTextures->Location = System::Drawing::Point(4, 22);
			this->tabTextures->Name = L"tabTextures";
			this->tabTextures->Size = System::Drawing::Size(316, 210);
			this->tabTextures->TabIndex = 0;
			this->tabTextures->Text = L"Textures";
			// 
			// tabOptions
			// 
			this->tabOptions->Controls->Add(this->grpOptions);
			this->tabOptions->Location = System::Drawing::Point(4, 22);
			this->tabOptions->Name = L"tabOptions";
			this->tabOptions->Size = System::Drawing::Size(316, 210);
			this->tabOptions->TabIndex = 1;
			this->tabOptions->Text = L"Options";
			// 
			// grpOptions
			// 
			this->grpOptions->Controls->Add(this->chkAlphaCoverage);
			this->grpOptions->Controls->Add(this->chkHalfLambert);
			this->grpOptions->Controls->Add(this->chkIgnoreZ);
			this->grpOptions->Controls->Add(this->chkNoFog);
			this->grpOptions->Controls->Add(this->chkDecal);
			this->grpOptions->Controls->Add(this->chkModel);
			this->grpOptions->Controls->Add(this->txtKeywords);
			this->grpOptions->Controls->Add(this->chkVertexAlpha);
			this->grpOptions->Controls->Add(this->chkVertexColor);
			this->grpOptions->Controls->Add(this->chkNoDecal);
			this->grpOptions->Controls->Add(this->chkNoLOD);
			this->grpOptions->Controls->Add(this->chkAlphaTest);
			this->grpOptions->Controls->Add(this->chkNoCull);
			this->grpOptions->Controls->Add(this->chkAdditive);
			this->grpOptions->Controls->Add(this->chkTranslucent);
			this->grpOptions->Controls->Add(this->lblKeywords);
			this->grpOptions->Controls->Add(this->cboSurface2);
			this->grpOptions->Controls->Add(this->lblSurface2);
			this->grpOptions->Controls->Add(this->cboSurface1);
			this->grpOptions->Controls->Add(this->lblSurface1);
			this->grpOptions->Controls->Add(this->cboShader);
			this->grpOptions->Controls->Add(this->lblShader);
			this->grpOptions->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpOptions->Location = System::Drawing::Point(6, 6);
			this->grpOptions->Name = L"grpOptions";
			this->grpOptions->Size = System::Drawing::Size(301, 220);
			this->grpOptions->TabIndex = 0;
			this->grpOptions->TabStop = false;
			this->grpOptions->Text = L"Options:";
			this->grpOptions->Enter += gcnew System::EventHandler(this, &CVMTCreate::grpOptions_Enter);
			// 
			// chkHalfLambert
			// 
			this->chkHalfLambert->Location = System::Drawing::Point(192, 135);
			this->chkHalfLambert->Name = L"chkHalfLambert";
			this->chkHalfLambert->Size = System::Drawing::Size(87, 24);
			this->chkHalfLambert->TabIndex = 23;
			this->chkHalfLambert->Text = L"Half Lambert";
			this->tipMain->SetToolTip(this->chkHalfLambert, L"$halflambert\r\nOnly works on models.");
			this->chkHalfLambert->UseVisualStyleBackColor = true;
			// 
			// chkIgnoreZ
			// 
			this->chkIgnoreZ->Location = System::Drawing::Point(192, 117);
			this->chkIgnoreZ->Name = L"chkIgnoreZ";
			this->chkIgnoreZ->Size = System::Drawing::Size(87, 24);
			this->chkIgnoreZ->TabIndex = 22;
			this->chkIgnoreZ->Text = L"Ignore Z";
			this->tipMain->SetToolTip(this->chkIgnoreZ, L"$ignorez");
			this->chkIgnoreZ->UseVisualStyleBackColor = true;
			// 
			// chkNoFog
			// 
			this->chkNoFog->Location = System::Drawing::Point(192, 98);
			this->chkNoFog->Name = L"chkNoFog";
			this->chkNoFog->Size = System::Drawing::Size(87, 24);
			this->chkNoFog->TabIndex = 21;
			this->chkNoFog->Text = L"No Fog";
			this->tipMain->SetToolTip(this->chkNoFog, L"$nofog");
			this->chkNoFog->UseVisualStyleBackColor = true;
			// 
			// chkDecal
			// 
			this->chkDecal->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkDecal->Location = System::Drawing::Point(111, 174);
			this->chkDecal->Name = L"chkDecal";
			this->chkDecal->Size = System::Drawing::Size(51, 19);
			this->chkDecal->TabIndex = 19;
			this->chkDecal->Text = L"Decal";
			this->tipMain->SetToolTip(this->chkDecal, L"$decal");
			this->chkDecal->UseVisualStyleBackColor = true;
			// 
			// chkModel
			// 
			this->chkModel->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkModel->Location = System::Drawing::Point(111, 156);
			this->chkModel->Name = L"chkModel";
			this->chkModel->Size = System::Drawing::Size(51, 18);
			this->chkModel->TabIndex = 18;
			this->chkModel->Text = L"Model";
			this->tipMain->SetToolTip(this->chkModel, L"$model");
			this->chkModel->UseVisualStyleBackColor = true;
			// 
			// txtKeywords
			// 
			this->txtKeywords->Location = System::Drawing::Point(72, 70);
			this->txtKeywords->Name = L"txtKeywords";
			this->txtKeywords->Size = System::Drawing::Size(217, 20);
			this->txtKeywords->TabIndex = 7;
			this->tipMain->SetToolTip(this->txtKeywords, L"%keywords");
			// 
			// chkVertexAlpha
			// 
			this->chkVertexAlpha->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkVertexAlpha->Location = System::Drawing::Point(6, 157);
			this->chkVertexAlpha->Name = L"chkVertexAlpha";
			this->chkVertexAlpha->Size = System::Drawing::Size(81, 18);
			this->chkVertexAlpha->TabIndex = 16;
			this->chkVertexAlpha->Text = L"Vertex Alpha";
			this->tipMain->SetToolTip(this->chkVertexAlpha, L"$vertexalpha");
			// 
			// chkVertexColor
			// 
			this->chkVertexColor->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkVertexColor->Location = System::Drawing::Point(6, 175);
			this->chkVertexColor->Name = L"chkVertexColor";
			this->chkVertexColor->Size = System::Drawing::Size(81, 19);
			this->chkVertexColor->TabIndex = 17;
			this->chkVertexColor->Text = L"Vertex Color";
			this->tipMain->SetToolTip(this->chkVertexColor, L"$vertexcolor");
			// 
			// chkNoDecal
			// 
			this->chkNoDecal->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkNoDecal->Location = System::Drawing::Point(111, 119);
			this->chkNoDecal->Name = L"chkNoDecal";
			this->chkNoDecal->Size = System::Drawing::Size(66, 19);
			this->chkNoDecal->TabIndex = 13;
			this->chkNoDecal->Text = L"No Decal";
			this->tipMain->SetToolTip(this->chkNoDecal, L"$nodecal");
			// 
			// chkNoLOD
			// 
			this->chkNoLOD->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkNoLOD->Location = System::Drawing::Point(111, 137);
			this->chkNoLOD->Name = L"chkNoLOD";
			this->chkNoLOD->Size = System::Drawing::Size(62, 19);
			this->chkNoLOD->TabIndex = 14;
			this->chkNoLOD->Text = L"No LOD";
			this->tipMain->SetToolTip(this->chkNoLOD, L"$nolod");
			// 
			// chkAlphaTest
			// 
			this->chkAlphaTest->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkAlphaTest->Location = System::Drawing::Point(6, 119);
			this->chkAlphaTest->Name = L"chkAlphaTest";
			this->chkAlphaTest->Size = System::Drawing::Size(75, 20);
			this->chkAlphaTest->TabIndex = 9;
			this->chkAlphaTest->Text = L"Alpha Test";
			this->tipMain->SetToolTip(this->chkAlphaTest, L"$alphatest");
			// 
			// chkNoCull
			// 
			this->chkNoCull->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkNoCull->Location = System::Drawing::Point(111, 100);
			this->chkNoCull->Name = L"chkNoCull";
			this->chkNoCull->Size = System::Drawing::Size(57, 19);
			this->chkNoCull->TabIndex = 12;
			this->chkNoCull->Text = L"No Cull";
			this->tipMain->SetToolTip(this->chkNoCull, L"$nocull");
			// 
			// chkAdditive
			// 
			this->chkAdditive->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkAdditive->Location = System::Drawing::Point(6, 138);
			this->chkAdditive->Name = L"chkAdditive";
			this->chkAdditive->Size = System::Drawing::Size(66, 19);
			this->chkAdditive->TabIndex = 8;
			this->chkAdditive->Text = L"Additive";
			this->tipMain->SetToolTip(this->chkAdditive, L"$additive");
			// 
			// chkTranslucent
			// 
			this->chkTranslucent->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkTranslucent->Location = System::Drawing::Point(6, 100);
			this->chkTranslucent->Name = L"chkTranslucent";
			this->chkTranslucent->Size = System::Drawing::Size(81, 20);
			this->chkTranslucent->TabIndex = 15;
			this->chkTranslucent->Text = L"Translucent";
			this->tipMain->SetToolTip(this->chkTranslucent, L"$translucent");
			// 
			// lblKeywords
			// 
			this->lblKeywords->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblKeywords->Location = System::Drawing::Point(6, 74);
			this->lblKeywords->Name = L"lblKeywords";
			this->lblKeywords->Size = System::Drawing::Size(66, 18);
			this->lblKeywords->TabIndex = 6;
			this->lblKeywords->Text = L"Keywords:";
			// 
			// cboSurface2
			// 
			this->cboSurface2->Items->AddRange(gcnew cli::array< System::Object^  >(126) {
				L"Advisor_shield", L"Alienflesh", L"Antlion",
					L"Antlion_eggshell", L"Antlionsand", L"Armorflesh", L"Bat", L"Blade", L"Blockbullets", L"Bloodyflesh", L"Boulder", L"Brakingrubbertire",
					L"Brick", L"Canister", L"Cardboard", L"Carpet", L"Cavern_rock", L"Ceiling_tile", L"Chain", L"Chainlink", L"Chainsaw", L"Clay",
					L"Combine_glass", L"Combine_metal", L"Computer", L"Concrete", L"Concrete_block", L"Cricketbat", L"Crowbar", L"Crowbar", L"Default",
					L"Default_silent", L"Dirt", L"Fireaxe", L"Flesh", L"Floating_metal_barrel", L"Floatingstandable", L"Foliage", L"Foliage_leaf",
					L"Fryingpan", L"Glass", L"Glassbottle", L"Glassfloor", L"Golfclub", L"Grass", L"Gravel", L"Gravel", L"Grenade", L"Guitar", L"Gunship",
					L"Hunter", L"Ice", L"Item", L"Jalopy", L"Jalopytire", L"Jeeptire", L"Ladder", L"Metal", L"Metal_Box", L"Metal_barrel", L"Metal_bouncy",
					L"Metal_sand_barrel", L"Metal_seafloorcar", L"Metal_shield", L"Metalgrate", L"Metalpanel", L"Metalvehicle", L"Metalvent", L"Mud",
					L"No_decal", L"Paintcan", L"Paper", L"Papercup", L"Pitchfork", L"Plaster", L"Plastic", L"Plastic_Box", L"Plastic_barrel", L"Plastic_barrel_buoyant",
					L"Player", L"Player_control_clip", L"Popcan", L"Porcelain", L"Pottery", L"Puddle", L"Quicksand", L"Rock", L"Roller", L"Rubber",
					L"Rubbertire", L"Sand", L"Sheetrock", L"Shovel", L"Slidingrubbertire", L"Slidingrubbertire_front", L"Slidingrubbertire_jalopyfront",
					L"Slidingrubbertire_jalopyrear", L"Slidingrubbertire_rear", L"Slime", L"Slipperymetal", L"Slipperyslide", L"Slipperyslime", L"Snow",
					L"Solidmetal", L"Strider", L"Strongman_bell", L"Sugarcane", L"Sword", L"Tile", L"Upholstery", L"Wade", L"Water", L"Watermelon",
					L"Weapon", L"Wet", L"Wood", L"Wood_Box", L"Wood_Crate", L"Wood_Dense", L"Wood_Furniture", L"Wood_LowDensity", L"Wood_Panel",
					L"Wood_Plank", L"Wood_Solid", L"Woodladder", L"Zombieflesh"
			});
			this->cboSurface2->Location = System::Drawing::Point(72, 51);
			this->cboSurface2->Name = L"cboSurface2";
			this->cboSurface2->Size = System::Drawing::Size(217, 21);
			this->cboSurface2->TabIndex = 5;
			this->tipMain->SetToolTip(this->cboSurface2, L"$surfaceprop2");
			// 
			// lblSurface2
			// 
			this->lblSurface2->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblSurface2->Location = System::Drawing::Point(6, 55);
			this->lblSurface2->Name = L"lblSurface2";
			this->lblSurface2->Size = System::Drawing::Size(66, 17);
			this->lblSurface2->TabIndex = 4;
			this->lblSurface2->Text = L"Surface 2:";
			// 
			// cboSurface1
			// 
			this->cboSurface1->Items->AddRange(gcnew cli::array< System::Object^  >(126) {
				L"Advisor_shield", L"Alienflesh", L"Antlion",
					L"Antlion_eggshell", L"Antlionsand", L"Armorflesh", L"Bat", L"Blade", L"Blockbullets", L"Bloodyflesh", L"Boulder", L"Brakingrubbertire",
					L"Brick", L"Canister", L"Cardboard", L"Carpet", L"Cavern_rock", L"Ceiling_tile", L"Chain", L"Chainlink", L"Chainsaw", L"Clay",
					L"Combine_glass", L"Combine_metal", L"Computer", L"Concrete", L"Concrete_block", L"Cricketbat", L"Crowbar", L"Crowbar", L"Default",
					L"Default_silent", L"Dirt", L"Fireaxe", L"Flesh", L"Floating_metal_barrel", L"Floatingstandable", L"Foliage", L"Foliage_leaf",
					L"Fryingpan", L"Glass", L"Glassbottle", L"Glassfloor", L"Golfclub", L"Grass", L"Gravel", L"Gravel", L"Grenade", L"Guitar", L"Gunship",
					L"Hunter", L"Ice", L"Item", L"Jalopy", L"Jalopytire", L"Jeeptire", L"Ladder", L"Metal", L"Metal_Box", L"Metal_barrel", L"Metal_bouncy",
					L"Metal_sand_barrel", L"Metal_seafloorcar", L"Metal_shield", L"Metalgrate", L"Metalpanel", L"Metalvehicle", L"Metalvent", L"Mud",
					L"No_decal", L"Paintcan", L"Paper", L"Papercup", L"Pitchfork", L"Plaster", L"Plastic", L"Plastic_Box", L"Plastic_barrel", L"Plastic_barrel_buoyant",
					L"Player", L"Player_control_clip", L"Popcan", L"Porcelain", L"Pottery", L"Puddle", L"Quicksand", L"Rock", L"Roller", L"Rubber",
					L"Rubbertire", L"Sand", L"Sheetrock", L"Shovel", L"Slidingrubbertire", L"Slidingrubbertire_front", L"Slidingrubbertire_jalopyfront",
					L"Slidingrubbertire_jalopyrear", L"Slidingrubbertire_rear", L"Slime", L"Slipperymetal", L"Slipperyslide", L"Slipperyslime", L"Snow",
					L"Solidmetal", L"Strider", L"Strongman_bell", L"Sugarcane", L"Sword", L"Tile", L"Upholstery", L"Wade", L"Water", L"Watermelon",
					L"Weapon", L"Wet", L"Wood", L"Wood_Box", L"Wood_Crate", L"Wood_Dense", L"Wood_Furniture", L"Wood_LowDensity", L"Wood_Panel",
					L"Wood_Plank", L"Wood_Solid", L"Woodladder", L"Zombieflesh"
			});
			this->cboSurface1->Location = System::Drawing::Point(72, 31);
			this->cboSurface1->Name = L"cboSurface1";
			this->cboSurface1->Size = System::Drawing::Size(217, 21);
			this->cboSurface1->TabIndex = 3;
			this->tipMain->SetToolTip(this->cboSurface1, L"$surfaceprop");
			// 
			// lblSurface1
			// 
			this->lblSurface1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblSurface1->Location = System::Drawing::Point(6, 35);
			this->lblSurface1->Name = L"lblSurface1";
			this->lblSurface1->Size = System::Drawing::Size(66, 19);
			this->lblSurface1->TabIndex = 2;
			this->lblSurface1->Text = L"Surface 1:";
			// 
			// cboShader
			// 
			this->cboShader->Items->AddRange(gcnew cli::array< System::Object^  >(44) {
				L"Aftershock", L"Cable", L"Character", L"Core",
					L"DecalModulate", L"DepthOfField", L"Engine_Post", L"EyeRefract", L"Eyes", L"LensFX", L"LightmappedGeneric", L"LightmappedReflective",
					L"LightmappedTwoTexture", L"Lightmapped_4WayBlend", L"Modulate", L"MonitorScreen", L"MotionBlur", L"Multiblend", L"PaintBlob",
					L"ParallaxTest", L"Pyro_vision", L"RGBFilmGrain", L"Refract", L"Screenspace_general", L"Shadow", L"Sky", L"SolidEnergy", L"SplineRope",
					L"Sprite", L"SpriteCard", L"Subrect", L"Suppression", L"SurfaceGGX", L"Teeth", L"UnlitGeneric", L"UnlitTwoTexture", L"VertexLitGeneric",
					L"VolumeCloud", L"VortWarp", L"Water", L"WindowImposter", L"WorldGGX", L"WorldTwoTextureBlend", L"WorldVertexTransition"
			});
			this->cboShader->Location = System::Drawing::Point(72, 12);
			this->cboShader->Name = L"cboShader";
			this->cboShader->Size = System::Drawing::Size(217, 21);
			this->cboShader->TabIndex = 1;
			this->cboShader->Text = L"LightmappedGeneric";
			this->cboShader->TextChanged += gcnew System::EventHandler(this, &CVMTCreate::cboShader_TextChanged);
			// 
			// lblShader
			// 
			this->lblShader->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblShader->Location = System::Drawing::Point(6, 16);
			this->lblShader->Name = L"lblShader";
			this->lblShader->Size = System::Drawing::Size(66, 19);
			this->lblShader->TabIndex = 0;
			this->lblShader->Text = L"Shader:";
			// 
			// btnClose
			// 
			this->btnClose->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnClose->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnClose->Location = System::Drawing::Point(270, 244);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(60, 22);
			this->btnClose->TabIndex = 2;
			this->btnClose->Text = L"&Close";
			this->btnClose->Click += gcnew System::EventHandler(this, &CVMTCreate::btnClose_Click);
			// 
			// btnCreate
			// 
			this->btnCreate->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnCreate->Location = System::Drawing::Point(206, 244);
			this->btnCreate->Name = L"btnCreate";
			this->btnCreate->Size = System::Drawing::Size(60, 22);
			this->btnCreate->TabIndex = 1;
			this->btnCreate->Text = L"C&reate";
			this->btnCreate->Click += gcnew System::EventHandler(this, &CVMTCreate::btnCreate_Click);
			// 
			// btnClear
			// 
			this->btnClear->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnClear->Location = System::Drawing::Point(4, 244);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(60, 22);
			this->btnClear->TabIndex = 3;
			this->btnClear->Text = L"C&lear";
			this->btnClear->Click += gcnew System::EventHandler(this, &CVMTCreate::btnClear_Click);
			// 
			// dlgSaveVMTFile
			// 
			this->dlgSaveVMTFile->Filter = L"VMT Files (*.vmt)|*.vmt";
			this->dlgSaveVMTFile->Title = L"Save VMT File";
			// 
			// chkAlphaCoverage
			// 
			this->chkAlphaCoverage->Location = System::Drawing::Point(192, 153);
			this->chkAlphaCoverage->Name = L"chkAlphaCoverage";
			this->chkAlphaCoverage->Size = System::Drawing::Size(102, 24);
			this->chkAlphaCoverage->TabIndex = 24;
			this->chkAlphaCoverage->Text = L"Alpha Coverage";
			this->tipMain->SetToolTip(this->chkAlphaCoverage, L"$allowalphatocoverage\r\nOnly works with $alphatest and anti-aliasing enabled in your game config.");
			this->chkAlphaCoverage->UseVisualStyleBackColor = true;
			//
			// tipMain
			// 
			this->tipMain->ShowAlways = true;
			this->tipMain->AutoPopDelay = 20000;
			this->tipMain->InitialDelay = 500;
			this->tipMain->ReshowDelay = 100;
			// 
			// CVMTCreate
			// 
			this->AcceptButton = this->btnCreate;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->CancelButton = this->btnClose;
			this->ClientSize = System::Drawing::Size(334, 270);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->btnCreate);
			this->Controls->Add(this->tabMain);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"CVMTCreate";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Create VMT File";
			this->grpTextures->ResumeLayout(false);
			this->grpTextures->PerformLayout();
			this->tabMain->ResumeLayout(false);
			this->tabTextures->ResumeLayout(false);
			this->tabOptions->ResumeLayout(false);
			this->grpOptions->ResumeLayout(false);
			this->grpOptions->PerformLayout();
			this->ResumeLayout(false);

		}
		private: System::Void GetTexture(System::Windows::Forms::TextBox ^oTextBox)
		{
			if(this->dlgOpenVTFFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				oTextBox->Text = CVMTFileUtility::GetTexturePathFromSystemPath(this->dlgOpenVTFFile->FileName);
			}
		}

		public: System::Void Create(System::String ^sFileName, VTFLib::CVTFFile &VTFFile)
		{
			this->txtBaseTexture1->Text = CVMTFileUtility::GetTexturePathFromSystemPath(sFileName);
			this->chkAlphaTest->Checked = VTFFile.GetFlag(TEXTUREFLAGS_ONEBITALPHA) != 0;
			this->chkTranslucent->Checked = VTFFile.GetFlag(TEXTUREFLAGS_EIGHTBITALPHA) != 0;
		}

		private: System::Void Clear()
		{
			this->txtBaseTexture1->Clear();
			this->txtBumpTexture1->Clear();
			this->txtBaseTexture2->Clear();
			this->txtBumpTexture2->Clear();
			this->txtEnviromentTexture->Clear();
			this->txtEnviromentMaskTexture->Clear();
			this->txtDetailTexture->Clear();
			this->txtToolTexture->Clear();
			this->txtNormalTexture->Clear();
			this->txtDuDvTexture->Clear();

			this->cboShader->Text = "LightmappedGeneric";
			this->cboSurface1->Text = "";
			this->cboSurface2->Text = "";

			this->txtKeywords->Clear();

			this->chkAdditive->Checked = false;
			this->chkAlphaTest->Checked = false;
			this->chkNoCull->Checked = false;
			this->chkNoDecal->Checked = false;
			this->chkNoLOD->Checked = false;
			this->chkTranslucent->Checked = false;
			this->chkVertexAlpha->Checked = false;
			this->chkVertexColor->Checked = false;
			this->chkModel->Checked = false;
			this->chkDecal->Checked = false;
		}

		private: System::Void txtTexture_Leave(System::Object ^  sender, System::EventArgs ^  e)
		{
			static_cast<System::Windows::Forms::TextBox ^>(sender)->Text = CVMTFileUtility::GetTexturePathFromSystemPath(static_cast<System::Windows::Forms::TextBox ^>(sender)->Text);
		}

		private: System::Void txtBaseTexture1_TextChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			//this->btnCreate->Enabled = this->GetTexturePath(txtBaseTexture1->Text)->Length != 0 && this->cboShader->Text->Length != 0;
		}

		private: System::Void cboShader_TextChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnCreate->Enabled =/* this->GetTexturePath(txtBaseTexture1->Text)->Length != 0 && */this->cboShader->Text->Length != 0;
		}

		private: System::Void btnBaseTexture1_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtBaseTexture1);
		}

		private: System::Void btnBumpTexture1_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtBumpTexture1);
		}

		private: System::Void btnBaseTexture2_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtBaseTexture2);
		}
		private: System::Void btnBumpTexture2_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtBumpTexture2);
		}

		private: System::Void btnEnviromentTexture_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtEnviromentTexture);
		}

		private: System::Void btnEnviromentMaskTexture_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtEnviromentMaskTexture);
		}

		private: System::Void btnDetailTexture_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtDetailTexture);
		}

		private: System::Void btnToolTexture_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtToolTexture);
		}

		private: System::Void btnNormalTexture_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtNormalTexture);
		}

		private: System::Void btnDuDvTexture_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->GetTexture(this->txtDuDvTexture);
		}

		private: System::Void btnClear_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->Clear();
		}

		public: System::Void AddVMTStringNode(VTFLib::CVMTFile &VMTFile, System::String ^sName, System::String ^sValue)
		{
			if(sValue->Length == 0)
				return;

			char *cName = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sName).ToPointer();
			char *cValue = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sValue).ToPointer();
			VMTFile.GetRoot()->AddStringNode(cName, cValue);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cValue);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cName);
		}

		private: System::Void AddVMTIntegerNode(VTFLib::CVMTFile &VMTFile, System::String ^sName, int iValue)
		{
			char *cName = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sName).ToPointer();
			VMTFile.GetRoot()->AddIntegerNode(cName, iValue);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cName);
		}

		private: System::Void AddVMTSingleNode(VTFLib::CVMTFile &VMTFile, System::String ^sName, float fValue)
		{
			char *cName = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sName).ToPointer();
			VMTFile.GetRoot()->AddSingleNode(cName, fValue);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cName);
		}

		public: System::Void AddVMTBooleanNode(VTFLib::CVMTFile &VMTFile, System::String ^sName, bool bValue, bool bDefault)
		{
			if(bValue == bDefault)
				return;

			char *cName = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sName).ToPointer();
			VMTFile.GetRoot()->AddIntegerNode(cName, bValue ? 1 : 0);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cName);
		}

		public: System::Void btnCreate_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			System::String ^sVMTFile = this->txtBaseTexture1->Text;

			int iIndex = sVMTFile->LastIndexOf("/");
			if(iIndex != -1)
			{
				sVMTFile = sVMTFile->Substring(iIndex + 1);
			}

			this->dlgSaveVMTFile->FileName = sVMTFile;
			if(this->dlgSaveVMTFile->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				return;

			char *cTemp;
			VTFLib::CVMTFile VMTFile;

			cTemp = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->cboShader->Text).ToPointer();
			VMTFile.Create(cTemp);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp);

			this->AddVMTStringNode(VMTFile, "$basetexture", this->txtBaseTexture1->Text);
			this->AddVMTStringNode(VMTFile, "$bumpmap", this->txtBumpTexture1->Text);
			this->AddVMTStringNode(VMTFile, "$basetexture2", this->txtBaseTexture2->Text);
			this->AddVMTStringNode(VMTFile, "$bumpmap2", this->txtBumpTexture2->Text);
			this->AddVMTStringNode(VMTFile, "$envmap", this->txtEnviromentTexture->Text);
			this->AddVMTStringNode(VMTFile, "$envmapmask", this->txtEnviromentMaskTexture->Text);
			this->AddVMTStringNode(VMTFile, "$detail", this->txtDetailTexture->Text);
			this->AddVMTStringNode(VMTFile, "%tooltexture", this->txtToolTexture->Text);
			this->AddVMTStringNode(VMTFile, "$normalmap", this->txtNormalTexture->Text);
			this->AddVMTStringNode(VMTFile, "$dudvmap", this->txtDuDvTexture->Text);

			this->AddVMTStringNode(VMTFile, "$surfaceprop", this->cboSurface1->Text);
			this->AddVMTStringNode(VMTFile, "$surfaceprop2", this->cboSurface2->Text);

			this->AddVMTStringNode(VMTFile, "%keywords", this->txtKeywords->Text);

			this->AddVMTBooleanNode(VMTFile, "$additive", this->chkAdditive->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$alphatest", this->chkAlphaTest->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$nocull", this->chkNoCull->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$nodecal", this->chkNoDecal->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$nolod", this->chkNoLOD->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$translucent", this->chkTranslucent->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$vertexalpha", this->chkVertexAlpha->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$vertexcolor", this->chkVertexColor->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$model", this->chkModel->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$decal", this->chkDecal->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$nofog", this->chkNoFog->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$ignorez", this->chkIgnoreZ->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$halflambert", this->chkHalfLambert->Checked, false);
			this->AddVMTBooleanNode(VMTFile, "$allowalphatocoverage", this->chkAlphaCoverage->Checked, false);

			cTemp = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->dlgSaveVMTFile->FileName).ToPointer();
			VMTFile.Save(cTemp);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp);
		}

		private: System::Void btnClose_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
		}
	private: System::Void grpOptions_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void txtNormalTexture_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}