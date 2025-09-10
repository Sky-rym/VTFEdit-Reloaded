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
#include "About.h"
#include "VTFOptions.h"
#include "VTFResources.h"
#include "VMTCreate.h"
#include "BatchConvert.h"
//#include "WADConvert.h"
#include "Utility.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace VTFEdit
{
	public ref class CVTFEdit : public System::Windows::Forms::Form
	{
	public:
		bool bWarnings;
		bool bNotificationSounds;
	private:
		System::String ^sFileName;

		VTFLib::CVMTFile *VMTFile;
		VTFLib::CVTFFile *VTFFile;

		bool bHDRReseting;
		float fImageScale;
		unsigned char *ucImageData;

		bool bCustomAlphaBackground;
		System::Drawing::Color fAlphaBackgroundColor;

		//CVMTFileUtility::CSyntaxHilighter ^SyntaxHilighter; // Disabled for performance reasons.

		unsigned int uiMaximumRecentFiles;
		System::Collections::ArrayList ^RecentFiles;

		bool bFormRestoring;
		System::Drawing::Point FormSaveLocation;
		System::Drawing::Size FormSaveSize;
		System::String^ FormVMTShader;
		FormWindowState FormSaveWindowState;
		int iFormSaveSidebarSplitPosition;
		int iFormSaveSidebar2SplitPosition;
		float iFormSaveVMTTextZoom;

		CVTFOptions ^Options;
		CVTFEditResources ^EditResources;
		CVMTCreate ^VMTCreate;
		CBatchConvert ^BatchConvert;
		//CWADConvert ^WADConvert; // conversion is broken for some reason, need to fix...
		CAbout ^About;
	private: System::Windows::Forms::MenuItem ^btnCustomAlphaToggle;
	private: System::Windows::Forms::MenuItem ^btnCustomAlphaSetter;
	private: System::Windows::Forms::MenuItem ^menuItem1;



		HWND hWndNewViewer;

	public: 
		CVTFEdit()
		{
			this->sFileName = nullptr;

			this->VMTFile = nullptr;
			this->VTFFile = nullptr;

			this->bHDRReseting = false;
			this->ucImageData = nullptr;

			this->uiMaximumRecentFiles = 8;
			this->RecentFiles = gcnew System::Collections::ArrayList();

			this->bFormRestoring = false;

			this->Options = gcnew CVTFOptions();
			this->EditResources = gcnew CVTFEditResources();
			this->VMTCreate = gcnew CVMTCreate();
			this->BatchConvert = gcnew CBatchConvert(this->Options, this->VMTCreate);
			//this->WADConvert = gcnew CWADConvert(this->Options, this->VMTCreate);
			this->About = gcnew CAbout();

			this->hWndNewViewer = 0;

			this->InitializeComponent();

			//this->SyntaxHilighter = gcnew CVMTFileUtility::CSyntaxHilighter(this->txtVMTFile); // Disabled for performance reasons.
		}

	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator4;
	private: System::Windows::Forms::ToolStripButton^ toolStripZoomIn;
	private: System::Windows::Forms::ToolStripButton^ toolStripZoomOut;
	private: System::Windows::Forms::ToolTip^ tipMain;
	private: System::Windows::Forms::TrackBar^ trkFrame;
	private: System::Windows::Forms::NumericUpDown^ numFrameRate;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::MenuItem^ btnNewVTF;
	private: System::Windows::Forms::MenuItem^ btnNewVMT;
	private: System::Windows::Forms::RichTextBox^ txtVMTFile;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileValidateStrict;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileValidateLoose;
	private: System::Windows::Forms::ContextMenu ^  mnuHDR;
	private: System::Windows::Forms::MenuItem ^  btnHDRReset;
	private: System::Windows::Forms::StatusBarPanel ^  pnlInfo1;
	private: System::Windows::Forms::StatusBarPanel ^  pnlInfo2;
	private: System::Windows::Forms::MenuItem ^  btnExportAll;
	private: System::Windows::Forms::Label ^  lblSlice;
	private: System::Windows::Forms::NumericUpDown ^  numSlice;
	private: System::Windows::Forms::StatusBarPanel ^  pnlFileName;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileSpace3;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileValidate;
	private: System::Windows::Forms::MenuItem^ btnNewMenu;
	private: System::Windows::Forms::ContextMenu ^  mnuVMTFile;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileUndo;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileSpace1;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileCut;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileCopy;
	private: System::Windows::Forms::MenuItem ^  btnVMTFilePaste;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileDelete;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileSpace2;
	private: System::Windows::Forms::MenuItem ^  btnVMTFileSelectAll;
	private: System::Windows::Forms::MenuItem ^  btnConvertFolder;
	private: System::Windows::Forms::MenuItem ^  btnOptionsSpace1;
	private: System::Windows::Forms::MenuItem ^  btnAutoCreateVMTFile;
	//private: System::Windows::Forms::MenuItem ^  btnConvertWADFile;
	private: System::Windows::Forms::MenuItem ^  btnFileSpace4;
	private: System::Windows::Forms::MenuItem ^  btnCreateVMTFile;
	private: System::Windows::Forms::MenuItem ^  btnToolsMenu;
	private: System::Windows::Forms::MenuItem ^  btnFileSpace3;
	private: System::Windows::Forms::MenuItem ^  btnVTFFileZoomIn;
	private: System::Windows::Forms::MenuItem ^  btnVTFFileZoomOut;
	private: System::Windows::Forms::MenuItem ^  btnVTFFileSpace1;
	private: System::Windows::Forms::MenuItem ^  btnVTFFileZoomReset;
	private: System::Windows::Forms::MenuItem ^  btnVTFFileSpace2;
	private: System::Windows::Forms::MenuItem ^  btnVTFFileCopy;
	private: System::Windows::Forms::ContextMenu ^  mnuVTFFile;
	private: System::Windows::Forms::PictureBox ^  picVTFFileTL;
	private: System::Windows::Forms::PictureBox ^  picVTFFileTR;
	private: System::Windows::Forms::PictureBox ^  picVTFFileBL;
	private: System::Windows::Forms::PictureBox ^  picVTFFileBR;
	private: System::Windows::Forms::MenuItem ^  btnTile;
	private: System::Windows::Forms::FolderBrowserDialog ^  dlgExtractDirectoryItem;
	private: System::Windows::Forms::MenuItem ^  btnMask;
	private: System::Windows::Forms::Splitter ^  splSidebar;
	private: System::Windows::Forms::StatusBar ^  barStatus;
	private: System::Windows::Forms::ImageList ^  imgTool;
	private: System::Windows::Forms::MenuItem ^  btnPaste;
	private: System::Windows::Forms::MenuItem ^  btnRecentFiles;
	private: System::Windows::Forms::OpenFileDialog ^  dlgImportFile;
	private: System::Windows::Forms::MenuItem ^  btnFileSpace1;
	private: System::Windows::Forms::MenuItem ^  btnExport;
	private: System::Windows::Forms::SaveFileDialog ^  dlgExportFile;
	private: System::Windows::Forms::MenuItem ^  btnViewMenu;
	private: System::Windows::Forms::MenuItem ^  btnChannelMenu;
	private: System::Windows::Forms::MenuItem ^  btnChannelRGB;
	private: System::Windows::Forms::MenuItem ^  btnChannelR;
	private: System::Windows::Forms::MenuItem ^  btnChannelG;
	private: System::Windows::Forms::MenuItem ^  btnChannelB;
	private: System::Windows::Forms::MenuItem ^  btnChannelA;
	private: System::Windows::Forms::MenuItem ^  btnEditMenu;
	private: System::Windows::Forms::MenuItem ^  btnCopy;
	private: System::Windows::Forms::Panel ^  pnlMain;
	private: System::Windows::Forms::SaveFileDialog ^  dlgSaveVTFFile;
	private: System::Windows::Forms::SaveFileDialog ^  dlgSaveVMTFile;
	private: System::Windows::Forms::MenuItem ^  btnFileSpace2;
	private: System::Windows::Forms::MenuItem ^  btnSave;
	private: System::Windows::Forms::MenuItem ^  btnSaveAs;
	private: System::Windows::Forms::MenuItem ^  btnFileMenu;
	private: System::Windows::Forms::MenuItem ^  btnHelpMenu;
	private: System::Windows::Forms::MenuItem ^  btnAbout;
	private: System::Windows::Forms::Panel^ pnlSidebar2;
	private: System::Windows::Forms::GroupBox^ grpResources;
	private: System::Windows::Forms::Button^ btnEditResources;
	private: System::Windows::Forms::TreeView^ treResources;
	private: System::Windows::Forms::GroupBox^ grpImageInfo;
	private: System::Windows::Forms::Panel^ clrReflectivity;
	private: System::Windows::Forms::Label^ lblImageReflectivity;
	private: System::Windows::Forms::Label^ lblHDRKey;
	private: System::Windows::Forms::TrackBar^ trkHDRExposure;
	private: System::Windows::Forms::NumericUpDown^ numImageBumpmapScale;
	private: System::Windows::Forms::NumericUpDown^ numImageStartFrame;
	private: System::Windows::Forms::Label^ lblImageReflectivityLabel;
	private: System::Windows::Forms::Label^ lblImageBumpmapScaleLabel;
	private: System::Windows::Forms::Label^ lblImageStartFrameLabel;
	private: System::Windows::Forms::Label^ lblImageFormat;
	private: System::Windows::Forms::Label^ lblImageFormatLabel;
	private: System::Windows::Forms::Label^ lblImageHeight;
	private: System::Windows::Forms::Label^ lblImageHeightLabel;
	private: System::Windows::Forms::Label^ lblImageWidth;
	private: System::Windows::Forms::Label^ lblImageWidthLabel;
	private: System::Windows::Forms::GroupBox^ grpFileInfo;
	private: System::Windows::Forms::ComboBox^ cboFileVersion;
	private: System::Windows::Forms::Label^ lblFileSize;
	private: System::Windows::Forms::Label^ lblFileSizeLabel;
	private: System::Windows::Forms::Label^ lblFileVersionLabel;
	private: System::Windows::Forms::Splitter^ splSidebar2;
	private: System::Windows::Forms::ColorDialog^ colorDialog;
	private: System::Windows::Forms::Button ^  btnAnimate;
	private: System::Windows::Forms::Timer ^  tmrAnimate;
	private: System::Windows::Forms::GroupBox ^  grpImage;
	private: System::Windows::Forms::GroupBox ^  grpFlags;
	private: System::Windows::Forms::CheckedListBox ^  lstFlags;
	private: System::Windows::Forms::MainMenu ^  mnuMain;
	private: System::Windows::Forms::MenuItem ^  btnOpen;
	private: System::Windows::Forms::MenuItem ^  btnExit;
	private: System::Windows::Forms::OpenFileDialog ^  dlgOpenFile;
	private: System::Windows::Forms::Panel ^  pnlSidebar;
	private: System::Windows::Forms::Label ^  lblFrame;
	private: System::Windows::Forms::NumericUpDown ^  numFrame;
	private: System::Windows::Forms::Label ^  lblFace;
	private: System::Windows::Forms::NumericUpDown ^  numFace;
	private: System::Windows::Forms::Label ^  lblMipmap;
	private: System::Windows::Forms::NumericUpDown ^  numMipmap;
	private: System::ComponentModel::IContainer ^  components;
	private: System::Windows::Forms::ToolStrip^ toolStripView;
	private: System::Windows::Forms::ToolStripButton^ toolStripRGB;
	private: System::Windows::Forms::ToolStripButton^ toolStripG;
	private: System::Windows::Forms::ToolStripButton^ toolStripB;
	private: System::Windows::Forms::ToolStripButton^ toolStripA;
	private: System::Windows::Forms::ToolStripButton^ toolStripMask;
	private: System::Windows::Forms::ToolStripButton^ toolStripR;
	private: System::Windows::Forms::ToolStripButton^ toolStripTile;
	private: System::Windows::Forms::ToolStripButton^ toolStripOpen;
	private: System::Windows::Forms::ToolStripButton^ toolStripImport;
	private: System::Windows::Forms::ToolStripButton^ toolStripSave;
	private: System::Windows::Forms::ToolStripButton^ toolStripCopy;
	private: System::Windows::Forms::ToolStripButton^ toolStripPaste;
	private: System::Windows::Forms::ToolStripButton^ toolStripClose;
	private: System::Windows::Forms::ToolStripButton^ toolStripExport;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator2;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator3;
	private: System::Windows::Forms::MenuItem^ btnClose;
private: System::Windows::Forms::MenuItem ^btnOptions;

	private: System::Windows::Forms::MenuItem^ btnWarnings;
	private: System::Windows::Forms::MenuItem^ btnNotifSounds;

	private:

		void InitializeComponent(void)
		{
			this->components = ( gcnew System::ComponentModel::Container() );
			System::ComponentModel::ComponentResourceManager ^resources = ( gcnew System::ComponentModel::ComponentResourceManager(CVTFEdit::typeid) );
			this->mnuMain = ( gcnew System::Windows::Forms::MainMenu(this->components) );
			this->btnFileMenu = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnNewMenu = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnNewVTF = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnNewVMT = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnOpen = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnClose = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnFileSpace1 = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnSave = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnSaveAs = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnFileSpace2 = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnExport = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnExportAll = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnFileSpace3 = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnRecentFiles = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnFileSpace4 = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnExit = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnEditMenu = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnCopy = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnPaste = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnViewMenu = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnChannelMenu = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnChannelRGB = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnChannelR = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnChannelG = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnChannelB = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnChannelA = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnMask = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnTile = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnToolsMenu = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnCreateVMTFile = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnConvertFolder = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnOptions = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnWarnings = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnNotifSounds = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnCustomAlphaToggle = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnCustomAlphaSetter = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnHelpMenu = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnAbout = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnAutoCreateVMTFile = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnOptionsSpace1 = ( gcnew System::Windows::Forms::MenuItem() );
			this->dlgOpenFile = ( gcnew System::Windows::Forms::OpenFileDialog() );
			this->barStatus = ( gcnew System::Windows::Forms::StatusBar() );
			this->pnlFileName = ( gcnew System::Windows::Forms::StatusBarPanel() );
			this->pnlInfo1 = ( gcnew System::Windows::Forms::StatusBarPanel() );
			this->pnlInfo2 = ( gcnew System::Windows::Forms::StatusBarPanel() );
			this->pnlSidebar = ( gcnew System::Windows::Forms::Panel() );
			this->grpFlags = ( gcnew System::Windows::Forms::GroupBox() );
			this->lstFlags = ( gcnew System::Windows::Forms::CheckedListBox() );
			this->grpImage = ( gcnew System::Windows::Forms::GroupBox() );
			this->numFrameRate = ( gcnew System::Windows::Forms::NumericUpDown() );
			this->label1 = ( gcnew System::Windows::Forms::Label() );
			this->trkFrame = ( gcnew System::Windows::Forms::TrackBar() );
			this->btnAnimate = ( gcnew System::Windows::Forms::Button() );
			this->lblSlice = ( gcnew System::Windows::Forms::Label() );
			this->numSlice = ( gcnew System::Windows::Forms::NumericUpDown() );
			this->lblMipmap = ( gcnew System::Windows::Forms::Label() );
			this->numMipmap = ( gcnew System::Windows::Forms::NumericUpDown() );
			this->numFace = ( gcnew System::Windows::Forms::NumericUpDown() );
			this->lblFace = ( gcnew System::Windows::Forms::Label() );
			this->numFrame = ( gcnew System::Windows::Forms::NumericUpDown() );
			this->lblFrame = ( gcnew System::Windows::Forms::Label() );
			this->mnuHDR = ( gcnew System::Windows::Forms::ContextMenu() );
			this->btnHDRReset = ( gcnew System::Windows::Forms::MenuItem() );
			this->tmrAnimate = ( gcnew System::Windows::Forms::Timer(this->components) );
			this->dlgSaveVTFFile = ( gcnew System::Windows::Forms::SaveFileDialog() );
			this->dlgSaveVMTFile = ( gcnew System::Windows::Forms::SaveFileDialog() );
			this->pnlMain = ( gcnew System::Windows::Forms::Panel() );
			this->picVTFFileBR = ( gcnew System::Windows::Forms::PictureBox() );
			this->mnuVTFFile = ( gcnew System::Windows::Forms::ContextMenu() );
			this->btnVTFFileZoomIn = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVTFFileZoomOut = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVTFFileSpace1 = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVTFFileZoomReset = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVTFFileSpace2 = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVTFFileCopy = ( gcnew System::Windows::Forms::MenuItem() );
			this->picVTFFileBL = ( gcnew System::Windows::Forms::PictureBox() );
			this->picVTFFileTR = ( gcnew System::Windows::Forms::PictureBox() );
			this->picVTFFileTL = ( gcnew System::Windows::Forms::PictureBox() );
			this->txtVMTFile = ( gcnew System::Windows::Forms::RichTextBox() );
			this->mnuVMTFile = ( gcnew System::Windows::Forms::ContextMenu() );
			this->btnVMTFileUndo = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileSpace1 = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileCut = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileCopy = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFilePaste = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileDelete = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileSpace2 = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileSelectAll = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileSpace3 = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileValidate = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileValidateLoose = ( gcnew System::Windows::Forms::MenuItem() );
			this->btnVMTFileValidateStrict = ( gcnew System::Windows::Forms::MenuItem() );
			this->toolStripView = ( gcnew System::Windows::Forms::ToolStrip() );
			this->toolStripOpen = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripClose = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripImport = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripExport = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripSave = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripCopy = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripPaste = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripSeparator2 = ( gcnew System::Windows::Forms::ToolStripSeparator() );
			this->toolStripRGB = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripR = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripG = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripB = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripA = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripSeparator3 = ( gcnew System::Windows::Forms::ToolStripSeparator() );
			this->toolStripMask = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripTile = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripSeparator4 = ( gcnew System::Windows::Forms::ToolStripSeparator() );
			this->toolStripZoomIn = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->toolStripZoomOut = ( gcnew System::Windows::Forms::ToolStripButton() );
			this->dlgImportFile = ( gcnew System::Windows::Forms::OpenFileDialog() );
			this->dlgExportFile = ( gcnew System::Windows::Forms::SaveFileDialog() );
			this->imgTool = ( gcnew System::Windows::Forms::ImageList(this->components) );
			this->splSidebar = ( gcnew System::Windows::Forms::Splitter() );
			this->dlgExtractDirectoryItem = ( gcnew System::Windows::Forms::FolderBrowserDialog() );
			this->tipMain = ( gcnew System::Windows::Forms::ToolTip(this->components) );
			this->btnEditResources = ( gcnew System::Windows::Forms::Button() );
			this->clrReflectivity = ( gcnew System::Windows::Forms::Panel() );
			this->numImageStartFrame = ( gcnew System::Windows::Forms::NumericUpDown() );
			this->trkHDRExposure = ( gcnew System::Windows::Forms::TrackBar() );
			this->colorDialog = ( gcnew System::Windows::Forms::ColorDialog() );
			this->pnlSidebar2 = ( gcnew System::Windows::Forms::Panel() );
			this->grpResources = ( gcnew System::Windows::Forms::GroupBox() );
			this->treResources = ( gcnew System::Windows::Forms::TreeView() );
			this->grpImageInfo = ( gcnew System::Windows::Forms::GroupBox() );
			this->lblImageReflectivity = ( gcnew System::Windows::Forms::Label() );
			this->lblHDRKey = ( gcnew System::Windows::Forms::Label() );
			this->numImageBumpmapScale = ( gcnew System::Windows::Forms::NumericUpDown() );
			this->lblImageReflectivityLabel = ( gcnew System::Windows::Forms::Label() );
			this->lblImageBumpmapScaleLabel = ( gcnew System::Windows::Forms::Label() );
			this->lblImageStartFrameLabel = ( gcnew System::Windows::Forms::Label() );
			this->lblImageFormat = ( gcnew System::Windows::Forms::Label() );
			this->lblImageFormatLabel = ( gcnew System::Windows::Forms::Label() );
			this->lblImageHeight = ( gcnew System::Windows::Forms::Label() );
			this->lblImageHeightLabel = ( gcnew System::Windows::Forms::Label() );
			this->lblImageWidth = ( gcnew System::Windows::Forms::Label() );
			this->lblImageWidthLabel = ( gcnew System::Windows::Forms::Label() );
			this->grpFileInfo = ( gcnew System::Windows::Forms::GroupBox() );
			this->cboFileVersion = ( gcnew System::Windows::Forms::ComboBox() );
			this->lblFileSize = ( gcnew System::Windows::Forms::Label() );
			this->lblFileSizeLabel = ( gcnew System::Windows::Forms::Label() );
			this->lblFileVersionLabel = ( gcnew System::Windows::Forms::Label() );
			this->splSidebar2 = ( gcnew System::Windows::Forms::Splitter() );
			this->menuItem1 = ( gcnew System::Windows::Forms::MenuItem() );
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->pnlFileName ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->pnlInfo1 ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->pnlInfo2 ) )->BeginInit();
			this->pnlSidebar->SuspendLayout();
			this->grpFlags->SuspendLayout();
			this->grpImage->SuspendLayout();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numFrameRate ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->trkFrame ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numSlice ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numMipmap ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numFace ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numFrame ) )->BeginInit();
			this->pnlMain->SuspendLayout();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->picVTFFileBR ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->picVTFFileBL ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->picVTFFileTR ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->picVTFFileTL ) )->BeginInit();
			this->toolStripView->SuspendLayout();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numImageStartFrame ) )->BeginInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->trkHDRExposure ) )->BeginInit();
			this->pnlSidebar2->SuspendLayout();
			this->grpResources->SuspendLayout();
			this->grpImageInfo->SuspendLayout();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numImageBumpmapScale ) )->BeginInit();
			this->grpFileInfo->SuspendLayout();
			this->SuspendLayout();
			// 
			// mnuMain
			// 
			this->mnuMain->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(6) {
				this->btnFileMenu, this->btnEditMenu,
					this->btnViewMenu, this->btnToolsMenu, this->btnOptions, this->btnHelpMenu
			});
// 
// btnFileMenu
// 
			this->btnFileMenu->Index = 0;
			this->btnFileMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(13) {
				this->btnNewMenu, this->btnOpen,
					this->btnClose, this->btnFileSpace1, this->btnSave, this->btnSaveAs, this->btnFileSpace2, this->btnExport, this->btnExportAll,
					this->btnFileSpace3, this->btnRecentFiles, this->btnFileSpace4, this->btnExit
			});
			this->btnFileMenu->Text = L"&File";
			// 
			// btnNewMenu
			// 
			this->btnNewMenu->Index = 0;
			this->btnNewMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(2) { this->btnNewVTF, this->btnNewVMT });
			this->btnNewMenu->Text = L"&Create New...";
			this->btnNewMenu->Click += gcnew System::EventHandler(this, &CVTFEdit::btnNew_Click);
			// 
			// btnNewVTF
			// 
			this->btnNewVTF->Index = 0;
			this->btnNewVTF->Shortcut = System::Windows::Forms::Shortcut::CtrlN;
			this->btnNewVTF->Text = L"VTF";
			this->btnNewVTF->Click += gcnew System::EventHandler(this, &CVTFEdit::btnNewVTF_Click);
			// 
			// btnNewVMT
			// 
			this->btnNewVMT->Index = 1;
			this->btnNewVMT->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftN;
			this->btnNewVMT->Text = L"VMT";
			this->btnNewVMT->Click += gcnew System::EventHandler(this, &CVTFEdit::btnNewVMT_Click);
			// 
			// btnOpen
			// 
			this->btnOpen->Index = 1;
			this->btnOpen->Shortcut = System::Windows::Forms::Shortcut::CtrlO;
			this->btnOpen->Text = L"&Open";
			this->btnOpen->Click += gcnew System::EventHandler(this, &CVTFEdit::btnOpen_Click);
			// 
			// btnClose
			// 
			this->btnClose->Enabled = false;
			this->btnClose->Index = 2;
			this->btnClose->Shortcut = System::Windows::Forms::Shortcut::CtrlQ;
			this->btnClose->Text = L"&Close";
			this->btnClose->Click += gcnew System::EventHandler(this, &CVTFEdit::btnClose_Click);
			// 
			// btnFileSpace1
			// 
			this->btnFileSpace1->Index = 3;
			this->btnFileSpace1->Text = L"-";
			// 
			// btnSave
			// 
			this->btnSave->Enabled = false;
			this->btnSave->Index = 4;
			this->btnSave->Shortcut = System::Windows::Forms::Shortcut::CtrlS;
			this->btnSave->Text = L"&Save";
			this->btnSave->Click += gcnew System::EventHandler(this, &CVTFEdit::btnSave_Click);
			// 
			// btnSaveAs
			// 
			this->btnSaveAs->Enabled = false;
			this->btnSaveAs->Index = 5;
			this->btnSaveAs->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftS;
			this->btnSaveAs->Text = L"Save &As...";
			this->btnSaveAs->Click += gcnew System::EventHandler(this, &CVTFEdit::btnSaveAs_Click);
			// 
			// btnFileSpace2
			// 
			this->btnFileSpace2->Index = 6;
			this->btnFileSpace2->Text = L"-";
			// 
			// btnExport
			// 
			this->btnExport->Enabled = false;
			this->btnExport->Index = 7;
			this->btnExport->Shortcut = System::Windows::Forms::Shortcut::CtrlE;
			this->btnExport->Text = L"&Export";
			this->btnExport->Click += gcnew System::EventHandler(this, &CVTFEdit::btnExport_Click);
			// 
			// btnExportAll
			// 
			this->btnExportAll->Enabled = false;
			this->btnExportAll->Index = 8;
			this->btnExportAll->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftE;
			this->btnExportAll->Text = L"&Export All";
			this->btnExportAll->Click += gcnew System::EventHandler(this, &CVTFEdit::btnExportAll_Click);
			// 
			// btnFileSpace3
			// 
			this->btnFileSpace3->Index = 9;
			this->btnFileSpace3->Text = L"-";
			// 
			// btnRecentFiles
			// 
			this->btnRecentFiles->Index = 10;
			this->btnRecentFiles->Text = L"&Recent Files";
			this->btnRecentFiles->Visible = false;
			// 
			// btnFileSpace4
			// 
			this->btnFileSpace4->Index = 11;
			this->btnFileSpace4->Text = L"-";
			this->btnFileSpace4->Visible = false;
			// 
			// btnExit
			// 
			this->btnExit->Index = 12;
			this->btnExit->Shortcut = System::Windows::Forms::Shortcut::AltF4;
			this->btnExit->Text = L"E&xit";
			this->btnExit->Click += gcnew System::EventHandler(this, &CVTFEdit::btnExit_Click);
			// 
			// btnEditMenu
			// 
			this->btnEditMenu->Index = 1;
			this->btnEditMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(2) { this->btnCopy, this->btnPaste });
			this->btnEditMenu->Text = L"&Edit";
			// 
			// btnCopy
			// 
			this->btnCopy->Enabled = false;
			this->btnCopy->Index = 0;
			this->btnCopy->Shortcut = System::Windows::Forms::Shortcut::CtrlC;
			this->btnCopy->Text = L"&Copy";
			this->btnCopy->Click += gcnew System::EventHandler(this, &CVTFEdit::btnCopy_Click);
			// 
			// btnPaste
			// 
			this->btnPaste->Enabled = false;
			this->btnPaste->Index = 1;
			this->btnPaste->Shortcut = System::Windows::Forms::Shortcut::CtrlV;
			this->btnPaste->Text = L"&Paste";
			this->btnPaste->Click += gcnew System::EventHandler(this, &CVTFEdit::btnPaste_Click);
			// 
			// btnViewMenu
			// 
			this->btnViewMenu->Index = 2;
			this->btnViewMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(3) {
				this->btnChannelMenu, this->btnMask,
					this->btnTile
			});
			this->btnViewMenu->Text = L"&View";
			// 
			// btnChannelMenu
			// 
			this->btnChannelMenu->Index = 0;
			this->btnChannelMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(5) {
				this->btnChannelRGB,
					this->btnChannelR, this->btnChannelG, this->btnChannelB, this->btnChannelA
			});
			this->btnChannelMenu->Text = L"&Channel";
			// 
			// btnChannelRGB
			// 
			this->btnChannelRGB->Checked = true;
			this->btnChannelRGB->Index = 0;
			this->btnChannelRGB->RadioCheck = true;
			this->btnChannelRGB->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftC;
			this->btnChannelRGB->Text = L"RGB";
			this->btnChannelRGB->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannel_Click);
			// 
			// btnChannelR
			// 
			this->btnChannelR->Index = 1;
			this->btnChannelR->RadioCheck = true;
			this->btnChannelR->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftR;
			this->btnChannelR->Text = L"R";
			this->btnChannelR->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannelR_Click);
			// 
			// btnChannelG
			// 
			this->btnChannelG->Index = 2;
			this->btnChannelG->RadioCheck = true;
			this->btnChannelG->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftG;
			this->btnChannelG->Text = L"G";
			this->btnChannelG->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannelG_Click);
			// 
			// btnChannelB
			// 
			this->btnChannelB->Index = 3;
			this->btnChannelB->RadioCheck = true;
			this->btnChannelB->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftB;
			this->btnChannelB->Text = L"B";
			this->btnChannelB->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannelB_Click);
			// 
			// btnChannelA
			// 
			this->btnChannelA->Index = 4;
			this->btnChannelA->RadioCheck = true;
			this->btnChannelA->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftA;
			this->btnChannelA->Text = L"A";
			this->btnChannelA->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannelA_Click);
			// 
			// btnMask
			// 
			this->btnMask->Index = 1;
			this->btnMask->Shortcut = System::Windows::Forms::Shortcut::CtrlW;
			this->btnMask->Text = L"&Mask";
			this->btnMask->Click += gcnew System::EventHandler(this, &CVTFEdit::btnMask_Click);
			// 
			// btnTile
			// 
			this->btnTile->Index = 2;
			this->btnTile->Shortcut = System::Windows::Forms::Shortcut::CtrlT;
			this->btnTile->Text = L"&Tile";
			this->btnTile->Click += gcnew System::EventHandler(this, &CVTFEdit::btnTile_Click);
			// 
			// btnToolsMenu
			// 
			this->btnToolsMenu->Index = 3;
			this->btnToolsMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(2) {
				this->btnCreateVMTFile,
					this->btnConvertFolder
			});
			this->btnToolsMenu->Text = L"&Tools";
			// 
			// btnCreateVMTFile
			// 
			this->btnCreateVMTFile->Index = 0;
			this->btnCreateVMTFile->Text = L"Create &VMT File";
			this->btnCreateVMTFile->Click += gcnew System::EventHandler(this, &CVTFEdit::btnCreateVMTFile_Click);
			// 
			// btnConvertFolder
			// 
			this->btnConvertFolder->Index = 1;
			this->btnConvertFolder->Text = L"Convert &Folder";
			this->btnConvertFolder->Click += gcnew System::EventHandler(this, &CVTFEdit::btnConvertFolder_Click);
			// 
			// btnOptions
			// 
			this->btnOptions->Index = 4;
			this->btnOptions->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(5) {
				this->btnWarnings, this->btnNotifSounds,
					this->menuItem1, this->btnCustomAlphaToggle, this->btnCustomAlphaSetter
			});
			this->btnOptions->Text = L"&Options";
			// 
			// btnWarnings
			// 
			this->btnWarnings->Index = 0;
			this->btnWarnings->Text = L"&Warning Popups";
			this->btnWarnings->Click += gcnew System::EventHandler(this, &CVTFEdit::btnWarnings_Click);
			// 
			// btnNotifSounds
			// 
			this->btnNotifSounds->Index = 1;
			this->btnNotifSounds->Text = L"Notification &Sounds";
			this->btnNotifSounds->Click += gcnew System::EventHandler(this, &CVTFEdit::btnNotifSounds_Click);
			// 
			// btnCustomAlphaToggle
			// 
			this->btnCustomAlphaToggle->Index = 3;
			this->btnCustomAlphaToggle->Text = L"Custom &Alpha Background";
			this->btnCustomAlphaToggle->Click += gcnew System::EventHandler(this, &CVTFEdit::btnCustomAlphaToggle_Click);
			// 
			// btnCustomAlphaSetter
			// 
			this->btnCustomAlphaSetter->Index = 4;
			this->btnCustomAlphaSetter->Text = L"Alpha Background &Color";
			this->btnCustomAlphaSetter->Click += gcnew System::EventHandler(this, &CVTFEdit::btnCustomAlphaSetter_Click);
			// 
			// btnHelpMenu
			// 
			this->btnHelpMenu->Index = 5;
			this->btnHelpMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(1) { this->btnAbout });
			this->btnHelpMenu->Text = L"&Help";
			// 
			// btnAbout
			// 
			this->btnAbout->Index = 0;
			this->btnAbout->Text = L"&About";
			this->btnAbout->Click += gcnew System::EventHandler(this, &CVTFEdit::btnAbout_Click);
			// 
			// btnAutoCreateVMTFile
			// 
			this->btnAutoCreateVMTFile->Index = -1;
			this->btnAutoCreateVMTFile->Text = L"&Auto Create VMT File";
			this->btnAutoCreateVMTFile->Click += gcnew System::EventHandler(this, &CVTFEdit::btnAutoCreateVMTFile_Click);
			// 
			// btnOptionsSpace1
			// 
			this->btnOptionsSpace1->Index = -1;
			this->btnOptionsSpace1->Text = L"-";
			// 
			// dlgOpenFile
			// 
			this->dlgOpenFile->Filter = L"Supported Files (*.vmt;*.vtf)|*.vmt;*.vtf|VMT Files (*.vmt)|*.vmt|VTF File (*.vtf"
				L")|*.vtf";
			this->dlgOpenFile->Title = L"Open File";
			// 
			// barStatus
			// 
			this->barStatus->Location = System::Drawing::Point(0, 544);
			this->barStatus->Name = L"barStatus";
			this->barStatus->Panels->AddRange(gcnew cli::array< System::Windows::Forms::StatusBarPanel ^  >(3) {
				this->pnlFileName, this->pnlInfo1,
					this->pnlInfo2
			});
			this->barStatus->ShowPanels = true;
			this->barStatus->Size = System::Drawing::Size(784, 17);
			this->barStatus->TabIndex = 3;
			// 
			// pnlFileName
			// 
			this->pnlFileName->AutoSize = System::Windows::Forms::StatusBarPanelAutoSize::Spring;
			this->pnlFileName->MinWidth = 100;
			this->pnlFileName->Name = L"pnlFileName";
			this->pnlFileName->Width = 617;
			// 
			// pnlInfo1
			// 
			this->pnlInfo1->AutoSize = System::Windows::Forms::StatusBarPanelAutoSize::Contents;
			this->pnlInfo1->MinWidth = 75;
			this->pnlInfo1->Name = L"pnlInfo1";
			this->pnlInfo1->Width = 75;
			// 
			// pnlInfo2
			// 
			this->pnlInfo2->AutoSize = System::Windows::Forms::StatusBarPanelAutoSize::Contents;
			this->pnlInfo2->MinWidth = 75;
			this->pnlInfo2->Name = L"pnlInfo2";
			this->pnlInfo2->Width = 75;
			// 
			// pnlSidebar
			// 
			this->pnlSidebar->BackColor = System::Drawing::SystemColors::Control;
			this->pnlSidebar->Controls->Add(this->grpFlags);
			this->pnlSidebar->Controls->Add(this->grpImage);
			this->pnlSidebar->Dock = System::Windows::Forms::DockStyle::Left;
			this->pnlSidebar->Location = System::Drawing::Point(0, 43);
			this->pnlSidebar->MinimumSize = System::Drawing::Size(230, 0);
			this->pnlSidebar->Name = L"pnlSidebar";
			this->pnlSidebar->Size = System::Drawing::Size(230, 501);
			this->pnlSidebar->TabIndex = 0;
			// 
			// grpFlags
			// 
			this->grpFlags->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom )
																						   | System::Windows::Forms::AnchorStyles::Left )
																						 | System::Windows::Forms::AnchorStyles::Right ) );
			this->grpFlags->Controls->Add(this->lstFlags);
			this->grpFlags->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpFlags->Location = System::Drawing::Point(7, 195);
			this->grpFlags->Name = L"grpFlags";
			this->grpFlags->Size = System::Drawing::Size(217, 300);
			this->grpFlags->TabIndex = 1;
			this->grpFlags->TabStop = false;
			this->grpFlags->Text = L"Flags:";
			// 
			// lstFlags
			// 
			this->lstFlags->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom )
																						   | System::Windows::Forms::AnchorStyles::Left )
																						 | System::Windows::Forms::AnchorStyles::Right ) );
			this->lstFlags->CheckOnClick = true;
			this->lstFlags->ForeColor = System::Drawing::SystemColors::WindowText;
			this->lstFlags->HorizontalScrollbar = true;
			this->lstFlags->Location = System::Drawing::Point(5, 17);
			this->lstFlags->Name = L"lstFlags";
			this->lstFlags->Size = System::Drawing::Size(208, 274);
			this->lstFlags->TabIndex = 3;
			this->lstFlags->TabStop = false;
			this->lstFlags->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &CVTFEdit::lstFlags_ItemCheck);
			// 
			// grpImage
			// 
			this->grpImage->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																						 | System::Windows::Forms::AnchorStyles::Right ) );
			this->grpImage->Controls->Add(this->numFrameRate);
			this->grpImage->Controls->Add(this->label1);
			this->grpImage->Controls->Add(this->trkFrame);
			this->grpImage->Controls->Add(this->btnAnimate);
			this->grpImage->Controls->Add(this->lblSlice);
			this->grpImage->Controls->Add(this->numSlice);
			this->grpImage->Controls->Add(this->lblMipmap);
			this->grpImage->Controls->Add(this->numMipmap);
			this->grpImage->Controls->Add(this->numFace);
			this->grpImage->Controls->Add(this->lblFace);
			this->grpImage->Controls->Add(this->numFrame);
			this->grpImage->Controls->Add(this->lblFrame);
			this->grpImage->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpImage->Location = System::Drawing::Point(7, 7);
			this->grpImage->Name = L"grpImage";
			this->grpImage->Size = System::Drawing::Size(217, 178);
			this->grpImage->TabIndex = 0;
			this->grpImage->TabStop = false;
			this->grpImage->Text = L"Image:";
			// 
			// numFrameRate
			// 
			this->numFrameRate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																							 | System::Windows::Forms::AnchorStyles::Right ) );
			this->numFrameRate->Location = System::Drawing::Point(68, 104);
			this->numFrameRate->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->numFrameRate->Name = L"numFrameRate";
			this->numFrameRate->Size = System::Drawing::Size(144, 20);
			this->numFrameRate->TabIndex = 19;
			this->tipMain->SetToolTip(this->numFrameRate, L"The amount of time between each frame in milliseconds.\r\n(A smaller number is fast"
									  L"er.)");
			this->numFrameRate->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 42, 0, 0, 0 });
			this->numFrameRate->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::numFrateRate_ValueChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(7, 108);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(60, 13);
			this->label1->TabIndex = 18;
			this->label1->Text = L"Framerate: ";
			// 
			// trkFrame
			// 
			this->trkFrame->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																						 | System::Windows::Forms::AnchorStyles::Right ) );
			this->trkFrame->AutoSize = false;
			this->trkFrame->Location = System::Drawing::Point(6, 152);
			this->trkFrame->Name = L"trkFrame";
			this->trkFrame->Size = System::Drawing::Size(204, 19);
			this->trkFrame->TabIndex = 17;
			this->trkFrame->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::trkFrame_ValueChanged);
			// 
			// btnAnimate
			// 
			this->btnAnimate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																						   | System::Windows::Forms::AnchorStyles::Right ) );
			this->btnAnimate->Enabled = false;
			this->btnAnimate->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnAnimate->Location = System::Drawing::Point(6, 128);
			this->btnAnimate->Name = L"btnAnimate";
			this->btnAnimate->Size = System::Drawing::Size(206, 21);
			this->btnAnimate->TabIndex = 14;
			this->btnAnimate->Text = L"Play";
			this->btnAnimate->Click += gcnew System::EventHandler(this, &CVTFEdit::btnAnimate_Click);
			// 
			// lblSlice
			// 
			this->lblSlice->BackColor = System::Drawing::Color::Transparent;
			this->lblSlice->Location = System::Drawing::Point(7, 57);
			this->lblSlice->Name = L"lblSlice";
			this->lblSlice->Size = System::Drawing::Size(46, 19);
			this->lblSlice->TabIndex = 4;
			this->lblSlice->Text = L"Slice:";
			// 
			// numSlice
			// 
			this->numSlice->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																						 | System::Windows::Forms::AnchorStyles::Right ) );
			this->numSlice->Location = System::Drawing::Point(68, 56);
			this->numSlice->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
			this->numSlice->Name = L"numSlice";
			this->numSlice->Size = System::Drawing::Size(144, 20);
			this->numSlice->TabIndex = 5;
			this->numSlice->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::numVTFFile_ValueChanged);
			// 
			// lblMipmap
			// 
			this->lblMipmap->BackColor = System::Drawing::Color::Transparent;
			this->lblMipmap->Location = System::Drawing::Point(7, 76);
			this->lblMipmap->Name = L"lblMipmap";
			this->lblMipmap->Size = System::Drawing::Size(60, 17);
			this->lblMipmap->TabIndex = 6;
			this->lblMipmap->Text = L"Mipmap:";
			// 
			// numMipmap
			// 
			this->numMipmap->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																						  | System::Windows::Forms::AnchorStyles::Right ) );
			this->numMipmap->Location = System::Drawing::Point(68, 75);
			this->numMipmap->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
			this->numMipmap->Name = L"numMipmap";
			this->numMipmap->Size = System::Drawing::Size(144, 20);
			this->numMipmap->TabIndex = 7;
			this->numMipmap->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::numVTFFile_ValueChanged);
			// 
			// numFace
			// 
			this->numFace->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																						| System::Windows::Forms::AnchorStyles::Right ) );
			this->numFace->Location = System::Drawing::Point(68, 37);
			this->numFace->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
			this->numFace->Name = L"numFace";
			this->numFace->Size = System::Drawing::Size(144, 20);
			this->numFace->TabIndex = 3;
			this->numFace->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::numVTFFile_ValueChanged);
			// 
			// lblFace
			// 
			this->lblFace->BackColor = System::Drawing::Color::Transparent;
			this->lblFace->Location = System::Drawing::Point(7, 38);
			this->lblFace->Name = L"lblFace";
			this->lblFace->Size = System::Drawing::Size(60, 19);
			this->lblFace->TabIndex = 2;
			this->lblFace->Text = L"Face:";
			// 
			// numFrame
			// 
			this->numFrame->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																						 | System::Windows::Forms::AnchorStyles::Right ) );
			this->numFrame->Location = System::Drawing::Point(68, 18);
			this->numFrame->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
			this->numFrame->Name = L"numFrame";
			this->numFrame->Size = System::Drawing::Size(144, 20);
			this->numFrame->TabIndex = 1;
			this->numFrame->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::numVTFFile_ValueChanged);
			// 
			// lblFrame
			// 
			this->lblFrame->BackColor = System::Drawing::Color::Transparent;
			this->lblFrame->Location = System::Drawing::Point(7, 20);
			this->lblFrame->Name = L"lblFrame";
			this->lblFrame->Size = System::Drawing::Size(46, 17);
			this->lblFrame->TabIndex = 0;
			this->lblFrame->Text = L"Frame:";
			// 
			// mnuHDR
			// 
			this->mnuHDR->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(1) { this->btnHDRReset });
			// 
			// btnHDRReset
			// 
			this->btnHDRReset->Index = 0;
			this->btnHDRReset->Text = L"&Reset";
			this->btnHDRReset->Click += gcnew System::EventHandler(this, &CVTFEdit::btnHDRReset_Click);
			// 
			// tmrAnimate
			// 
			this->tmrAnimate->Interval = 42;
			this->tmrAnimate->Tick += gcnew System::EventHandler(this, &CVTFEdit::tmrAnimate_Tick);
			// 
			// dlgSaveVTFFile
			// 
			this->dlgSaveVTFFile->Filter = L"VTF Files (*.vtf)|*.vtf";
			this->dlgSaveVTFFile->Title = L"Save VTF File";
			// 
			// dlgSaveVMTFile
			// 
			this->dlgSaveVMTFile->Filter = L"VMT Files (*.vmt)|*.vmt";
			this->dlgSaveVMTFile->Title = L"Save VMT File";
			// 
			// pnlMain
			// 
			this->pnlMain->AllowDrop = true;
			this->pnlMain->AutoScroll = true;
			this->pnlMain->AutoSize = true;
			this->pnlMain->BackColor = System::Drawing::SystemColors::ControlDark;
			this->pnlMain->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnlMain->Controls->Add(this->picVTFFileBR);
			this->pnlMain->Controls->Add(this->picVTFFileBL);
			this->pnlMain->Controls->Add(this->picVTFFileTR);
			this->pnlMain->Controls->Add(this->picVTFFileTL);
			this->pnlMain->Controls->Add(this->txtVMTFile);
			this->pnlMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlMain->Location = System::Drawing::Point(233, 43);
			this->pnlMain->Name = L"pnlMain";
			this->pnlMain->Size = System::Drawing::Size(318, 501);
			this->pnlMain->TabIndex = 2;
			this->pnlMain->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			this->pnlMain->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			// 
			// picVTFFileBR
			// 
			this->picVTFFileBR->AllowDrop = true;
			this->picVTFFileBR->ContextMenu = this->mnuVTFFile;
			this->picVTFFileBR->Location = System::Drawing::Point(26, 27);
			this->picVTFFileBR->Name = L"picVTFFileBR";
			this->picVTFFileBR->Size = System::Drawing::Size(21, 21);
			this->picVTFFileBR->TabIndex = 4;
			this->picVTFFileBR->TabStop = false;
			this->picVTFFileBR->Visible = false;
			this->picVTFFileBR->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			this->picVTFFileBR->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->picVTFFileBR->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CVTFEdit::picVTFFile_MouseMove);
			// 
			// mnuVTFFile
			// 
			this->mnuVTFFile->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(6) {
				this->btnVTFFileZoomIn,
					this->btnVTFFileZoomOut, this->btnVTFFileSpace1, this->btnVTFFileZoomReset, this->btnVTFFileSpace2, this->btnVTFFileCopy
			});
// 
// btnVTFFileZoomIn
// 
			this->btnVTFFileZoomIn->Index = 0;
			this->btnVTFFileZoomIn->Text = L"Zoom &In";
			this->btnVTFFileZoomIn->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVTFFileZoomIn_Click);
			// 
			// btnVTFFileZoomOut
			// 
			this->btnVTFFileZoomOut->Index = 1;
			this->btnVTFFileZoomOut->Text = L"Zoom &Out";
			this->btnVTFFileZoomOut->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVTFFileZoomOut_Click);
			// 
			// btnVTFFileSpace1
			// 
			this->btnVTFFileSpace1->Index = 2;
			this->btnVTFFileSpace1->Text = L"-";
			// 
			// btnVTFFileZoomReset
			// 
			this->btnVTFFileZoomReset->Index = 3;
			this->btnVTFFileZoomReset->Text = L"&Reset Zoom";
			this->btnVTFFileZoomReset->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVTFFileZoomReset_Click);
			// 
			// btnVTFFileSpace2
			// 
			this->btnVTFFileSpace2->Index = 4;
			this->btnVTFFileSpace2->Text = L"-";
			// 
			// btnVTFFileCopy
			// 
			this->btnVTFFileCopy->Index = 5;
			this->btnVTFFileCopy->Text = L"&Copy Image To Clipboard";
			this->btnVTFFileCopy->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVTFFileCopy_Click);
			// 
			// picVTFFileBL
			// 
			this->picVTFFileBL->AllowDrop = true;
			this->picVTFFileBL->ContextMenu = this->mnuVTFFile;
			this->picVTFFileBL->Location = System::Drawing::Point(7, 27);
			this->picVTFFileBL->Name = L"picVTFFileBL";
			this->picVTFFileBL->Size = System::Drawing::Size(20, 21);
			this->picVTFFileBL->TabIndex = 3;
			this->picVTFFileBL->TabStop = false;
			this->picVTFFileBL->Visible = false;
			this->picVTFFileBL->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			this->picVTFFileBL->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->picVTFFileBL->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CVTFEdit::picVTFFile_MouseMove);
			// 
			// picVTFFileTR
			// 
			this->picVTFFileTR->AllowDrop = true;
			this->picVTFFileTR->ContextMenu = this->mnuVTFFile;
			this->picVTFFileTR->Location = System::Drawing::Point(26, 8);
			this->picVTFFileTR->Name = L"picVTFFileTR";
			this->picVTFFileTR->Size = System::Drawing::Size(21, 21);
			this->picVTFFileTR->TabIndex = 2;
			this->picVTFFileTR->TabStop = false;
			this->picVTFFileTR->Visible = false;
			this->picVTFFileTR->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			this->picVTFFileTR->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->picVTFFileTR->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CVTFEdit::picVTFFile_MouseMove);
			// 
			// picVTFFileTL
			// 
			this->picVTFFileTL->AllowDrop = true;
			this->picVTFFileTL->ContextMenu = this->mnuVTFFile;
			this->picVTFFileTL->Location = System::Drawing::Point(7, 8);
			this->picVTFFileTL->Name = L"picVTFFileTL";
			this->picVTFFileTL->Size = System::Drawing::Size(20, 21);
			this->picVTFFileTL->TabIndex = 0;
			this->picVTFFileTL->TabStop = false;
			this->picVTFFileTL->Visible = false;
			this->picVTFFileTL->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			this->picVTFFileTL->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->picVTFFileTL->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CVTFEdit::picVTFFile_MouseMove);
			// 
			// txtVMTFile
			// 
			this->txtVMTFile->AcceptsTab = true;
			this->txtVMTFile->AllowDrop = true;
			this->txtVMTFile->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>( static_cast<System::Byte>( 31 ) ), static_cast<System::Int32>( static_cast<System::Byte>( 31 ) ),
																		   static_cast<System::Int32>( static_cast<System::Byte>( 31 ) ));
			this->txtVMTFile->ContextMenu = this->mnuVMTFile;
			this->txtVMTFile->DetectUrls = false;
			this->txtVMTFile->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtVMTFile->Font = ( gcnew System::Drawing::Font(L"Consolas", 10) );
			this->txtVMTFile->ForeColor = System::Drawing::Color::White;
			this->txtVMTFile->Location = System::Drawing::Point(0, 0);
			this->txtVMTFile->Name = L"txtVMTFile";
			this->txtVMTFile->Size = System::Drawing::Size(316, 499);
			this->txtVMTFile->TabIndex = 5;
			this->txtVMTFile->Text = L"";
			this->txtVMTFile->Visible = false;
			this->txtVMTFile->WordWrap = false;
			this->txtVMTFile->SelectionChanged += gcnew System::EventHandler(this, &CVTFEdit::txtVMTFile_SelectionChanged);
			this->txtVMTFile->TextChanged += gcnew System::EventHandler(this, &CVTFEdit::txtVMTFile_TextChanged);
			this->txtVMTFile->MouseLeave += gcnew System::EventHandler(this, &CVTFEdit::txtVMTFile_MouseLeave);
			// 
			// mnuVMTFile
			// 
			this->mnuVMTFile->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(10) {
				this->btnVMTFileUndo, this->btnVMTFileSpace1,
					this->btnVMTFileCut, this->btnVMTFileCopy, this->btnVMTFilePaste, this->btnVMTFileDelete, this->btnVMTFileSpace2, this->btnVMTFileSelectAll,
					this->btnVMTFileSpace3, this->btnVMTFileValidate
			});
// 
// btnVMTFileUndo
// 
			this->btnVMTFileUndo->Enabled = false;
			this->btnVMTFileUndo->Index = 0;
			this->btnVMTFileUndo->Text = L"&Undo";
			this->btnVMTFileUndo->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileUndo_Click);
			// 
			// btnVMTFileSpace1
			// 
			this->btnVMTFileSpace1->Index = 1;
			this->btnVMTFileSpace1->Text = L"-";
			// 
			// btnVMTFileCut
			// 
			this->btnVMTFileCut->Enabled = false;
			this->btnVMTFileCut->Index = 2;
			this->btnVMTFileCut->Text = L"&Cut";
			this->btnVMTFileCut->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileCut_Click);
			// 
			// btnVMTFileCopy
			// 
			this->btnVMTFileCopy->Enabled = false;
			this->btnVMTFileCopy->Index = 3;
			this->btnVMTFileCopy->Text = L"&Copy";
			this->btnVMTFileCopy->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileCopy_Click);
			// 
			// btnVMTFilePaste
			// 
			this->btnVMTFilePaste->Enabled = false;
			this->btnVMTFilePaste->Index = 4;
			this->btnVMTFilePaste->Text = L"&Paste";
			this->btnVMTFilePaste->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFilePaste_Click);
			// 
			// btnVMTFileDelete
			// 
			this->btnVMTFileDelete->Enabled = false;
			this->btnVMTFileDelete->Index = 5;
			this->btnVMTFileDelete->Text = L"&Delete";
			this->btnVMTFileDelete->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileDelete_Click);
			// 
			// btnVMTFileSpace2
			// 
			this->btnVMTFileSpace2->Index = 6;
			this->btnVMTFileSpace2->Text = L"-";
			// 
			// btnVMTFileSelectAll
			// 
			this->btnVMTFileSelectAll->Enabled = false;
			this->btnVMTFileSelectAll->Index = 7;
			this->btnVMTFileSelectAll->Text = L"Select &All";
			this->btnVMTFileSelectAll->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileSelectAll_Click);
			// 
			// btnVMTFileSpace3
			// 
			this->btnVMTFileSpace3->Index = 8;
			this->btnVMTFileSpace3->Text = L"-";
			// 
			// btnVMTFileValidate
			// 
			this->btnVMTFileValidate->Index = 9;
			this->btnVMTFileValidate->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem ^  >(2) {
				this->btnVMTFileValidateLoose,
					this->btnVMTFileValidateStrict
			});
			this->btnVMTFileValidate->Text = L"&Validate";
			// 
			// btnVMTFileValidateLoose
			// 
			this->btnVMTFileValidateLoose->Index = 0;
			this->btnVMTFileValidateLoose->Text = L"&Loose";
			this->btnVMTFileValidateLoose->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileValidateLoose_Click);
			// 
			// btnVMTFileValidateStrict
			// 
			this->btnVMTFileValidateStrict->Index = 1;
			this->btnVMTFileValidateStrict->Text = L"&Strict";
			this->btnVMTFileValidateStrict->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileValidateStrict_Click);
			// 
			// toolStripView
			// 
			this->toolStripView->AutoSize = false;
			this->toolStripView->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
			this->toolStripView->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem ^  >(19) {
				this->toolStripOpen,
					this->toolStripClose, this->toolStripImport, this->toolStripExport, this->toolStripSave, this->toolStripCopy, this->toolStripPaste,
					this->toolStripSeparator2, this->toolStripRGB, this->toolStripR, this->toolStripG, this->toolStripB, this->toolStripA, this->toolStripSeparator3,
					this->toolStripMask, this->toolStripTile, this->toolStripSeparator4, this->toolStripZoomIn, this->toolStripZoomOut
			});
			this->toolStripView->Location = System::Drawing::Point(0, 0);
			this->toolStripView->MaximumSize = System::Drawing::Size(0, 43);
			this->toolStripView->Name = L"toolStripView";
			this->toolStripView->Padding = System::Windows::Forms::Padding(0);
			this->toolStripView->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->toolStripView->Size = System::Drawing::Size(784, 43);
			this->toolStripView->TabIndex = 6;
			this->toolStripView->Text = L"toolStpView";
			// 
			// toolStripOpen
			// 
			this->toolStripOpen->AutoSize = false;
			this->toolStripOpen->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripOpen->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripOpen.Image") ) );
			this->toolStripOpen->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripOpen->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripOpen->Name = L"toolStripOpen";
			this->toolStripOpen->Size = System::Drawing::Size(40, 40);
			this->toolStripOpen->Text = L"Open";
			this->toolStripOpen->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripOpen_Click);
			// 
			// toolStripClose
			// 
			this->toolStripClose->AutoSize = false;
			this->toolStripClose->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripClose->Enabled = false;
			this->toolStripClose->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripClose.Image") ) );
			this->toolStripClose->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripClose->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripClose->Name = L"toolStripClose";
			this->toolStripClose->Size = System::Drawing::Size(40, 40);
			this->toolStripClose->Text = L"Close";
			this->toolStripClose->ToolTipText = L"Close";
			this->toolStripClose->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripClose_Click);
			// 
			// toolStripImport
			// 
			this->toolStripImport->AutoSize = false;
			this->toolStripImport->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripImport->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripImport.Image") ) );
			this->toolStripImport->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripImport->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripImport->Name = L"toolStripImport";
			this->toolStripImport->Size = System::Drawing::Size(40, 40);
			this->toolStripImport->Text = L"Create New VTF";
			this->toolStripImport->ToolTipText = L"Create New VTF";
			this->toolStripImport->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripImport_Click);
			// 
			// toolStripExport
			// 
			this->toolStripExport->AutoSize = false;
			this->toolStripExport->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripExport->Enabled = false;
			this->toolStripExport->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripExport.Image") ) );
			this->toolStripExport->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripExport->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripExport->Name = L"toolStripExport";
			this->toolStripExport->Size = System::Drawing::Size(40, 40);
			this->toolStripExport->Text = L"Export";
			this->toolStripExport->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripExport_Click);
			// 
			// toolStripSave
			// 
			this->toolStripSave->AutoSize = false;
			this->toolStripSave->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripSave->Enabled = false;
			this->toolStripSave->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripSave.Image") ) );
			this->toolStripSave->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripSave->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripSave->Name = L"toolStripSave";
			this->toolStripSave->Size = System::Drawing::Size(40, 40);
			this->toolStripSave->Text = L"Save";
			this->toolStripSave->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripSave_Click);
			// 
			// toolStripCopy
			// 
			this->toolStripCopy->AutoSize = false;
			this->toolStripCopy->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripCopy->Enabled = false;
			this->toolStripCopy->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripCopy.Image") ) );
			this->toolStripCopy->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripCopy->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripCopy->Name = L"toolStripCopy";
			this->toolStripCopy->Size = System::Drawing::Size(40, 40);
			this->toolStripCopy->Text = L"Copy";
			this->toolStripCopy->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripCopy_Click);
			// 
			// toolStripPaste
			// 
			this->toolStripPaste->AutoSize = false;
			this->toolStripPaste->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripPaste->Enabled = false;
			this->toolStripPaste->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripPaste.Image") ) );
			this->toolStripPaste->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripPaste->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripPaste->Name = L"toolStripPaste";
			this->toolStripPaste->Size = System::Drawing::Size(40, 40);
			this->toolStripPaste->Text = L"Paste";
			this->toolStripPaste->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripPaste_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(6, 43);
			// 
			// toolStripRGB
			// 
			this->toolStripRGB->AutoSize = false;
			this->toolStripRGB->Checked = this->btnChannelRGB->Checked;
			this->toolStripRGB->CheckOnClick = true;
			this->toolStripRGB->CheckState = System::Windows::Forms::CheckState::Checked;
			this->toolStripRGB->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripRGB->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripRGB.Image") ) );
			this->toolStripRGB->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripRGB->ImageTransparentColor = System::Drawing::Color::SpringGreen;
			this->toolStripRGB->Name = L"toolStripRGB";
			this->toolStripRGB->Size = System::Drawing::Size(40, 40);
			this->toolStripRGB->Text = L"Red Green and Blue Channels";
			this->toolStripRGB->ToolTipText = L"Red Green and Blue Channels";
			this->toolStripRGB->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripRGB_Click);
			// 
			// toolStripR
			// 
			this->toolStripR->AutoSize = false;
			this->toolStripR->Checked = this->btnChannelR->Checked;
			this->toolStripR->CheckOnClick = true;
			this->toolStripR->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripR->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripR.Image") ) );
			this->toolStripR->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripR->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripR->Name = L"toolStripR";
			this->toolStripR->Size = System::Drawing::Size(40, 40);
			this->toolStripR->Text = L"Red Channel";
			this->toolStripR->ToolTipText = L"Red Channel";
			this->toolStripR->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripR_Click);
			// 
			// toolStripG
			// 
			this->toolStripG->AutoSize = false;
			this->toolStripG->Checked = this->btnChannelG->Checked;
			this->toolStripG->CheckOnClick = true;
			this->toolStripG->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripG->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripG.Image") ) );
			this->toolStripG->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripG->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripG->Name = L"toolStripG";
			this->toolStripG->Size = System::Drawing::Size(40, 40);
			this->toolStripG->Text = L"Green Channel";
			this->toolStripG->ToolTipText = L"Green Channel";
			this->toolStripG->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripG_Click);
			// 
			// toolStripB
			// 
			this->toolStripB->AutoSize = false;
			this->toolStripB->Checked = this->btnChannelB->Checked;
			this->toolStripB->CheckOnClick = true;
			this->toolStripB->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripB->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripB.Image") ) );
			this->toolStripB->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripB->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripB->Name = L"toolStripB";
			this->toolStripB->Size = System::Drawing::Size(40, 40);
			this->toolStripB->Text = L"Blue Channel";
			this->toolStripB->ToolTipText = L"Blue Channel";
			this->toolStripB->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripB_Click);
			// 
			// toolStripA
			// 
			this->toolStripA->AutoSize = false;
			this->toolStripA->Checked = this->btnChannelA->Checked;
			this->toolStripA->CheckOnClick = true;
			this->toolStripA->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripA->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripA.Image") ) );
			this->toolStripA->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripA->ImageTransparentColor = System::Drawing::Color::Maroon;
			this->toolStripA->Name = L"toolStripA";
			this->toolStripA->Size = System::Drawing::Size(40, 40);
			this->toolStripA->Text = L"Alpha Channel";
			this->toolStripA->ToolTipText = L"Alpha Channel";
			this->toolStripA->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripA_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(6, 43);
			// 
			// toolStripMask
			// 
			this->toolStripMask->AutoSize = false;
			this->toolStripMask->Checked = this->btnMask->Checked;
			this->toolStripMask->CheckOnClick = true;
			this->toolStripMask->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripMask->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripMask.Image") ) );
			this->toolStripMask->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripMask->ImageTransparentColor = System::Drawing::Color::Maroon;
			this->toolStripMask->Name = L"toolStripMask";
			this->toolStripMask->Size = System::Drawing::Size(40, 40);
			this->toolStripMask->Text = L"Toggle Alpha Mask";
			this->toolStripMask->ToolTipText = L"Toggle Alpha Mask";
			this->toolStripMask->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripMask_Click);
			// 
			// toolStripTile
			// 
			this->toolStripTile->AutoSize = false;
			this->toolStripTile->Checked = this->btnTile->Checked;
			this->toolStripTile->CheckOnClick = true;
			this->toolStripTile->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripTile->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripTile.Image") ) );
			this->toolStripTile->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripTile->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripTile->Name = L"toolStripTile";
			this->toolStripTile->Size = System::Drawing::Size(40, 40);
			this->toolStripTile->Text = L"Toggle Image Tiling";
			this->toolStripTile->ToolTipText = L"Toggle Image Tiling";
			this->toolStripTile->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripTile_Click);
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(6, 43);
			// 
			// toolStripZoomIn
			// 
			this->toolStripZoomIn->AutoSize = false;
			this->toolStripZoomIn->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripZoomIn->Enabled = false;
			this->toolStripZoomIn->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripZoomIn.Image") ) );
			this->toolStripZoomIn->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripZoomIn->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripZoomIn->Name = L"toolStripZoomIn";
			this->toolStripZoomIn->Size = System::Drawing::Size(40, 40);
			this->toolStripZoomIn->Text = L"Zoom In";
			this->toolStripZoomIn->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripZoomIn_Click);
			// 
			// toolStripZoomOut
			// 
			this->toolStripZoomOut->AutoSize = false;
			this->toolStripZoomOut->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripZoomOut->Enabled = false;
			this->toolStripZoomOut->Image = ( cli::safe_cast<System::Drawing::Image ^>( resources->GetObject(L"toolStripZoomOut.Image") ) );
			this->toolStripZoomOut->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripZoomOut->ImageTransparentColor = System::Drawing::Color::Transparent;
			this->toolStripZoomOut->Name = L"toolStripZoomOut";
			this->toolStripZoomOut->Size = System::Drawing::Size(40, 40);
			this->toolStripZoomOut->Text = L"Zoom Out";
			this->toolStripZoomOut->ToolTipText = L"Zoom Out";
			this->toolStripZoomOut->Click += gcnew System::EventHandler(this, &CVTFEdit::toolStripZoomOut_Click);
			// 
			// dlgImportFile
			// 
			this->dlgImportFile->Filter = resources->GetString(L"dlgImportFile.Filter");
			this->dlgImportFile->Multiselect = true;
			this->dlgImportFile->Title = L"Import File";
			// 
			// dlgExportFile
			// 
			this->dlgExportFile->Filter = L"BMP Files (*.bmp)|*.bmp|JPEG Files (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG Files (*.png)|"
				L"*.png|TGA Files (*.tga)|*.tga";
			this->dlgExportFile->FilterIndex = 4;
			this->dlgExportFile->Title = L"Export File";
			// 
			// imgTool
			// 
			this->imgTool->ImageStream = ( cli::safe_cast<System::Windows::Forms::ImageListStreamer ^>( resources->GetObject(L"imgTool.ImageStream") ) );
			this->imgTool->TransparentColor = System::Drawing::Color::Fuchsia;
			this->imgTool->Images->SetKeyName(0, L"");
			this->imgTool->Images->SetKeyName(1, L"");
			this->imgTool->Images->SetKeyName(2, L"");
			this->imgTool->Images->SetKeyName(3, L"");
			this->imgTool->Images->SetKeyName(4, L"");
			// 
			// splSidebar
			// 
			this->splSidebar->BackColor = System::Drawing::SystemColors::Control;
			this->splSidebar->Location = System::Drawing::Point(230, 43);
			this->splSidebar->MinExtra = 96;
			this->splSidebar->MinSize = 96;
			this->splSidebar->Name = L"splSidebar";
			this->splSidebar->Size = System::Drawing::Size(3, 501);
			this->splSidebar->TabIndex = 5;
			this->splSidebar->TabStop = false;
			this->splSidebar->SplitterMoved += gcnew System::Windows::Forms::SplitterEventHandler(this, &CVTFEdit::splSidebar_SplitterMoved);
			// 
			// dlgExtractDirectoryItem
			// 
			this->dlgExtractDirectoryItem->Description = L"Extract directory item to:";
			// 
			// tipMain
			// 
			this->tipMain->AutoPopDelay = 20000;
			this->tipMain->InitialDelay = 500;
			this->tipMain->ReshowDelay = 100;
			this->tipMain->ShowAlways = true;
			// 
			// btnEditResources
			// 
			this->btnEditResources->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																								 | System::Windows::Forms::AnchorStyles::Right ) );
			this->btnEditResources->Enabled = false;
			this->btnEditResources->Location = System::Drawing::Point(6, 15);
			this->btnEditResources->Name = L"btnEditResources";
			this->btnEditResources->Size = System::Drawing::Size(201, 23);
			this->btnEditResources->TabIndex = 3;
			this->btnEditResources->Text = L"Edit Resources";
			this->tipMain->SetToolTip(this->btnEditResources, L"Edits the resources of the VTF.\r\nOnly supported on VTF versions 7.3 and up.");
			this->btnEditResources->UseVisualStyleBackColor = true;
			this->btnEditResources->Click += gcnew System::EventHandler(this, &CVTFEdit::btnEditResources_Click);
			// 
			// clrReflectivity
			// 
			this->clrReflectivity->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																								| System::Windows::Forms::AnchorStyles::Right ) );
			this->clrReflectivity->BackColor = System::Drawing::SystemColors::ControlLight;
			this->clrReflectivity->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->clrReflectivity->Cursor = System::Windows::Forms::Cursors::Hand;
			this->clrReflectivity->Location = System::Drawing::Point(73, 135);
			this->clrReflectivity->Name = L"clrReflectivity";
			this->clrReflectivity->Size = System::Drawing::Size(134, 20);
			this->clrReflectivity->TabIndex = 3;
			this->tipMain->SetToolTip(this->clrReflectivity, L"The color reflected by the image in VRAD. Can be overriden with \"$reflectivity\" i"
									  L"n its vmt.");
			this->clrReflectivity->Click += gcnew System::EventHandler(this, &CVTFEdit::clrReflectivity_Click);
			// 
			// numImageStartFrame
			// 
			this->numImageStartFrame->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																								   | System::Windows::Forms::AnchorStyles::Right ) );
			this->numImageStartFrame->Enabled = false;
			this->numImageStartFrame->Location = System::Drawing::Point(73, 74);
			this->numImageStartFrame->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 0, 0, 0, 0 });
			this->numImageStartFrame->Name = L"numImageStartFrame";
			this->numImageStartFrame->Size = System::Drawing::Size(134, 20);
			this->numImageStartFrame->TabIndex = 9;
			this->tipMain->SetToolTip(this->numImageStartFrame, L"The frame this image will start on, if multiple frames are present.");
			// 
			// trkHDRExposure
			// 
			this->trkHDRExposure->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																							   | System::Windows::Forms::AnchorStyles::Right ) );
			this->trkHDRExposure->AutoSize = false;
			this->trkHDRExposure->ContextMenu = this->mnuHDR;
			this->trkHDRExposure->Location = System::Drawing::Point(68, 160);
			this->trkHDRExposure->Name = L"trkHDRExposure";
			this->trkHDRExposure->Size = System::Drawing::Size(139, 16);
			this->trkHDRExposure->TabIndex = 21;
			this->tipMain->SetToolTip(this->trkHDRExposure, L"The amount of exposure for this image in HDR.\n(Only available with RGBA16161616F."
									  L")");
									  // 
									  // pnlSidebar2
									  // 
			this->pnlSidebar2->BackColor = System::Drawing::SystemColors::Control;
			this->pnlSidebar2->Controls->Add(this->grpResources);
			this->pnlSidebar2->Controls->Add(this->grpImageInfo);
			this->pnlSidebar2->Controls->Add(this->grpFileInfo);
			this->pnlSidebar2->Dock = System::Windows::Forms::DockStyle::Right;
			this->pnlSidebar2->Location = System::Drawing::Point(554, 43);
			this->pnlSidebar2->MinimumSize = System::Drawing::Size(230, 0);
			this->pnlSidebar2->Name = L"pnlSidebar2";
			this->pnlSidebar2->Size = System::Drawing::Size(230, 501);
			this->pnlSidebar2->TabIndex = 7;
			// 
			// grpResources
			// 
			this->grpResources->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom )
																							   | System::Windows::Forms::AnchorStyles::Left )
																							 | System::Windows::Forms::AnchorStyles::Right ) );
			this->grpResources->Controls->Add(this->btnEditResources);
			this->grpResources->Controls->Add(this->treResources);
			this->grpResources->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpResources->Location = System::Drawing::Point(9, 268);
			this->grpResources->Name = L"grpResources";
			this->grpResources->Size = System::Drawing::Size(213, 227);
			this->grpResources->TabIndex = 3;
			this->grpResources->TabStop = false;
			this->grpResources->Text = L"Resources:";
			// 
			// treResources
			// 
			this->treResources->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom )
																							   | System::Windows::Forms::AnchorStyles::Left )
																							 | System::Windows::Forms::AnchorStyles::Right ) );
			this->treResources->Location = System::Drawing::Point(7, 41);
			this->treResources->Name = L"treResources";
			this->treResources->Size = System::Drawing::Size(200, 177);
			this->treResources->TabIndex = 0;
			// 
			// grpImageInfo
			// 
			this->grpImageInfo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																							 | System::Windows::Forms::AnchorStyles::Right ) );
			this->grpImageInfo->Controls->Add(this->clrReflectivity);
			this->grpImageInfo->Controls->Add(this->lblImageReflectivity);
			this->grpImageInfo->Controls->Add(this->lblHDRKey);
			this->grpImageInfo->Controls->Add(this->trkHDRExposure);
			this->grpImageInfo->Controls->Add(this->numImageBumpmapScale);
			this->grpImageInfo->Controls->Add(this->numImageStartFrame);
			this->grpImageInfo->Controls->Add(this->lblImageReflectivityLabel);
			this->grpImageInfo->Controls->Add(this->lblImageBumpmapScaleLabel);
			this->grpImageInfo->Controls->Add(this->lblImageStartFrameLabel);
			this->grpImageInfo->Controls->Add(this->lblImageFormat);
			this->grpImageInfo->Controls->Add(this->lblImageFormatLabel);
			this->grpImageInfo->Controls->Add(this->lblImageHeight);
			this->grpImageInfo->Controls->Add(this->lblImageHeightLabel);
			this->grpImageInfo->Controls->Add(this->lblImageWidth);
			this->grpImageInfo->Controls->Add(this->lblImageWidthLabel);
			this->grpImageInfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpImageInfo->Location = System::Drawing::Point(9, 77);
			this->grpImageInfo->Name = L"grpImageInfo";
			this->grpImageInfo->Size = System::Drawing::Size(213, 185);
			this->grpImageInfo->TabIndex = 1;
			this->grpImageInfo->TabStop = false;
			this->grpImageInfo->Text = L"Image Info:";
			// 
			// lblImageReflectivity
			// 
			this->lblImageReflectivity->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																									 | System::Windows::Forms::AnchorStyles::Right ) );
			this->lblImageReflectivity->BackColor = System::Drawing::Color::Transparent;
			this->lblImageReflectivity->Location = System::Drawing::Point(73, 118);
			this->lblImageReflectivity->Name = L"lblImageReflectivity";
			this->lblImageReflectivity->Size = System::Drawing::Size(134, 20);
			this->lblImageReflectivity->TabIndex = 22;
			// 
			// lblHDRKey
			// 
			this->lblHDRKey->BackColor = System::Drawing::Color::Transparent;
			this->lblHDRKey->Location = System::Drawing::Point(7, 160);
			this->lblHDRKey->Name = L"lblHDRKey";
			this->lblHDRKey->Size = System::Drawing::Size(60, 19);
			this->lblHDRKey->TabIndex = 20;
			this->lblHDRKey->Text = L"Exposure:";
			// 
			// numImageBumpmapScale
			// 
			this->numImageBumpmapScale->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																									 | System::Windows::Forms::AnchorStyles::Right ) );
			this->numImageBumpmapScale->Enabled = false;
			this->numImageBumpmapScale->Location = System::Drawing::Point(73, 93);
			this->numImageBumpmapScale->Name = L"numImageBumpmapScale";
			this->numImageBumpmapScale->Size = System::Drawing::Size(134, 20);
			this->numImageBumpmapScale->TabIndex = 17;
			// 
			// lblImageReflectivityLabel
			// 
			this->lblImageReflectivityLabel->BackColor = System::Drawing::Color::Transparent;
			this->lblImageReflectivityLabel->Location = System::Drawing::Point(7, 116);
			this->lblImageReflectivityLabel->Name = L"lblImageReflectivityLabel";
			this->lblImageReflectivityLabel->Size = System::Drawing::Size(65, 18);
			this->lblImageReflectivityLabel->TabIndex = 18;
			this->lblImageReflectivityLabel->Text = L"Reflectivity:";
			// 
			// lblImageBumpmapScaleLabel
			// 
			this->lblImageBumpmapScaleLabel->BackColor = System::Drawing::Color::Transparent;
			this->lblImageBumpmapScaleLabel->Location = System::Drawing::Point(7, 95);
			this->lblImageBumpmapScaleLabel->Name = L"lblImageBumpmapScaleLabel";
			this->lblImageBumpmapScaleLabel->Size = System::Drawing::Size(67, 17);
			this->lblImageBumpmapScaleLabel->TabIndex = 16;
			this->lblImageBumpmapScaleLabel->Text = L"Bump Scale:";
			// 
			// lblImageStartFrameLabel
			// 
			this->lblImageStartFrameLabel->BackColor = System::Drawing::Color::Transparent;
			this->lblImageStartFrameLabel->Location = System::Drawing::Point(7, 76);
			this->lblImageStartFrameLabel->Name = L"lblImageStartFrameLabel";
			this->lblImageStartFrameLabel->Size = System::Drawing::Size(65, 19);
			this->lblImageStartFrameLabel->TabIndex = 8;
			this->lblImageStartFrameLabel->Text = L"Start Frame:";
			// 
			// lblImageFormat
			// 
			this->lblImageFormat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																							   | System::Windows::Forms::AnchorStyles::Right ) );
			this->lblImageFormat->BackColor = System::Drawing::Color::Transparent;
			this->lblImageFormat->Location = System::Drawing::Point(73, 57);
			this->lblImageFormat->Name = L"lblImageFormat";
			this->lblImageFormat->Size = System::Drawing::Size(134, 19);
			this->lblImageFormat->TabIndex = 5;
			// 
			// lblImageFormatLabel
			// 
			this->lblImageFormatLabel->BackColor = System::Drawing::Color::Transparent;
			this->lblImageFormatLabel->Location = System::Drawing::Point(7, 57);
			this->lblImageFormatLabel->Name = L"lblImageFormatLabel";
			this->lblImageFormatLabel->Size = System::Drawing::Size(46, 19);
			this->lblImageFormatLabel->TabIndex = 4;
			this->lblImageFormatLabel->Text = L"Format:";
			// 
			// lblImageHeight
			// 
			this->lblImageHeight->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																							   | System::Windows::Forms::AnchorStyles::Right ) );
			this->lblImageHeight->BackColor = System::Drawing::Color::Transparent;
			this->lblImageHeight->Location = System::Drawing::Point(73, 38);
			this->lblImageHeight->Name = L"lblImageHeight";
			this->lblImageHeight->Size = System::Drawing::Size(134, 19);
			this->lblImageHeight->TabIndex = 3;
			// 
			// lblImageHeightLabel
			// 
			this->lblImageHeightLabel->BackColor = System::Drawing::Color::Transparent;
			this->lblImageHeightLabel->Location = System::Drawing::Point(7, 38);
			this->lblImageHeightLabel->Name = L"lblImageHeightLabel";
			this->lblImageHeightLabel->Size = System::Drawing::Size(46, 19);
			this->lblImageHeightLabel->TabIndex = 2;
			this->lblImageHeightLabel->Text = L"Height:";
			// 
			// lblImageWidth
			// 
			this->lblImageWidth->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																							  | System::Windows::Forms::AnchorStyles::Right ) );
			this->lblImageWidth->BackColor = System::Drawing::Color::Transparent;
			this->lblImageWidth->Location = System::Drawing::Point(73, 20);
			this->lblImageWidth->Name = L"lblImageWidth";
			this->lblImageWidth->Size = System::Drawing::Size(134, 17);
			this->lblImageWidth->TabIndex = 1;
			// 
			// lblImageWidthLabel
			// 
			this->lblImageWidthLabel->BackColor = System::Drawing::Color::Transparent;
			this->lblImageWidthLabel->Location = System::Drawing::Point(7, 20);
			this->lblImageWidthLabel->Name = L"lblImageWidthLabel";
			this->lblImageWidthLabel->Size = System::Drawing::Size(46, 17);
			this->lblImageWidthLabel->TabIndex = 0;
			this->lblImageWidthLabel->Text = L"Width:";
			// 
			// grpFileInfo
			// 
			this->grpFileInfo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																							| System::Windows::Forms::AnchorStyles::Right ) );
			this->grpFileInfo->Controls->Add(this->cboFileVersion);
			this->grpFileInfo->Controls->Add(this->lblFileSize);
			this->grpFileInfo->Controls->Add(this->lblFileSizeLabel);
			this->grpFileInfo->Controls->Add(this->lblFileVersionLabel);
			this->grpFileInfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpFileInfo->Location = System::Drawing::Point(9, 7);
			this->grpFileInfo->Name = L"grpFileInfo";
			this->grpFileInfo->Size = System::Drawing::Size(213, 64);
			this->grpFileInfo->TabIndex = 0;
			this->grpFileInfo->TabStop = false;
			this->grpFileInfo->Text = L"File Info:";
			// 
			// cboFileVersion
			// 
			this->cboFileVersion->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																							   | System::Windows::Forms::AnchorStyles::Right ) );
			this->cboFileVersion->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboFileVersion->FormattingEnabled = true;
			this->cboFileVersion->Items->AddRange(gcnew cli::array< System::Object ^  >(6) { L"7.5", L"7.4", L"7.3", L"7.2", L"7.1", L"7.0" });
			this->cboFileVersion->Location = System::Drawing::Point(73, 17);
			this->cboFileVersion->Name = L"cboFileVersion";
			this->cboFileVersion->Size = System::Drawing::Size(134, 21);
			this->cboFileVersion->TabIndex = 3;
			// 
			// lblFileSize
			// 
			this->lblFileSize->Anchor = static_cast<System::Windows::Forms::AnchorStyles>( ( ( System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left )
																							| System::Windows::Forms::AnchorStyles::Right ) );
			this->lblFileSize->BackColor = System::Drawing::Color::Transparent;
			this->lblFileSize->Location = System::Drawing::Point(73, 39);
			this->lblFileSize->Name = L"lblFileSize";
			this->lblFileSize->Size = System::Drawing::Size(134, 19);
			this->lblFileSize->TabIndex = 3;
			// 
			// lblFileSizeLabel
			// 
			this->lblFileSizeLabel->BackColor = System::Drawing::Color::Transparent;
			this->lblFileSizeLabel->Location = System::Drawing::Point(7, 40);
			this->lblFileSizeLabel->Name = L"lblFileSizeLabel";
			this->lblFileSizeLabel->Size = System::Drawing::Size(46, 19);
			this->lblFileSizeLabel->TabIndex = 2;
			this->lblFileSizeLabel->Text = L"Size:";
			// 
			// lblFileVersionLabel
			// 
			this->lblFileVersionLabel->BackColor = System::Drawing::Color::Transparent;
			this->lblFileVersionLabel->Location = System::Drawing::Point(7, 20);
			this->lblFileVersionLabel->Name = L"lblFileVersionLabel";
			this->lblFileVersionLabel->Size = System::Drawing::Size(46, 17);
			this->lblFileVersionLabel->TabIndex = 0;
			this->lblFileVersionLabel->Text = L"Version:";
			// 
			// splSidebar2
			// 
			this->splSidebar2->BackColor = System::Drawing::SystemColors::Control;
			this->splSidebar2->Dock = System::Windows::Forms::DockStyle::Right;
			this->splSidebar2->Location = System::Drawing::Point(551, 43);
			this->splSidebar2->Name = L"splSidebar2";
			this->splSidebar2->Size = System::Drawing::Size(3, 501);
			this->splSidebar2->TabIndex = 8;
			this->splSidebar2->TabStop = false;
			this->splSidebar2->SplitterMoved += gcnew System::Windows::Forms::SplitterEventHandler(this, &CVTFEdit::splSidebar2_SplitterMoved);
			// 
			// menuItem1
			// 
			this->menuItem1->Index = 2;
			this->menuItem1->Text = L"-";
			// 
			// CVTFEdit
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->pnlMain);
			this->Controls->Add(this->splSidebar2);
			this->Controls->Add(this->pnlSidebar2);
			this->Controls->Add(this->splSidebar);
			this->Controls->Add(this->pnlSidebar);
			this->Controls->Add(this->barStatus);
			this->Controls->Add(this->toolStripView);
			this->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8) );
			this->Icon = ( cli::safe_cast<System::Drawing::Icon ^>( resources->GetObject(L"$this.Icon") ) );
			this->Menu = this->mnuMain;
			this->MinimumSize = System::Drawing::Size(690, 600);
			this->Name = L"CVTFEdit";
			this->Text = L"VTFEdit Reloaded";
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &CVTFEdit::CVTFEdit_Closing);
			this->Load += gcnew System::EventHandler(this, &CVTFEdit::CVTFEdit_Load);
			this->Move += gcnew System::EventHandler(this, &CVTFEdit::CVTFEdit_Move);
			this->Resize += gcnew System::EventHandler(this, &CVTFEdit::CVTFEdit_Resize);
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->pnlFileName ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->pnlInfo1 ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->pnlInfo2 ) )->EndInit();
			this->pnlSidebar->ResumeLayout(false);
			this->grpFlags->ResumeLayout(false);
			this->grpImage->ResumeLayout(false);
			this->grpImage->PerformLayout();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numFrameRate ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->trkFrame ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numSlice ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numMipmap ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numFace ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numFrame ) )->EndInit();
			this->pnlMain->ResumeLayout(false);
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->picVTFFileBR ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->picVTFFileBL ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->picVTFFileTR ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->picVTFFileTL ) )->EndInit();
			this->toolStripView->ResumeLayout(false);
			this->toolStripView->PerformLayout();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numImageStartFrame ) )->EndInit();
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->trkHDRExposure ) )->EndInit();
			this->pnlSidebar2->ResumeLayout(false);
			this->grpResources->ResumeLayout(false);
			this->grpImageInfo->ResumeLayout(false);
			( cli::safe_cast<System::ComponentModel::ISupportInitialize ^>( this->numImageBumpmapScale ) )->EndInit();
			this->grpFileInfo->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		//
		// Form events.
		//

		public: property System::String ^FileName
		{
			System::String^ get()
			{
				return this->sFileName;
			}
			void set(System::String^ sFileName)
			{
				this->sFileName = sFileName;
				this->pnlFileName->Text = this->sFileName;

				if (sFileName)
				{
					if (sFileName->LastIndexOf('\\') != -1)
					{
						this->Text = System::String::Concat(sFileName->Substring(sFileName->LastIndexOf('\\') + 1), " - ", Application::ProductName);
					}
					else
					{
						this->Text = System::String::Concat(sFileName, " - ", Application::ProductName);
					}
				}
				else
				{
					if (this->VTFFile)
					{
						this->Text = "untitled.vtf - ", Application::ProductName;
					}
					else if (this->VMTFile)
					{
						this->Text = "untitled.vmt - ", Application::ProductName;
					}
					else
					{
						this->Text = Application::ProductName;
					}
				}
			}
		}

		private: System::Void CVTFEdit_Load(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->ClearAll();

			this->txtVMTFile->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->txtVMTFile->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);

			this->numImageBumpmapScale->DecimalPlaces = 2;
			this->numImageBumpmapScale->Increment = System::Decimal(0.01);
			this->numImageBumpmapScale->Minimum = System::Decimal(-100);
			this->numImageBumpmapScale->Maximum = System::Decimal(100);
			this->numImageBumpmapScale->Value = System::Decimal(0);
			this->btnHDRReset_Click(this, System::EventArgs::Empty);

			// Restore options.
			this->BackupForm();
			bool bHasConfig = false;
			// Uncomment this code if the program returns to using an installer
			//System::String ^pNewConfigFile = IO::Path::Combine(GetAppDataFolder(), System::String::Concat(Application::ProductName, ".ini"));
			System::String ^pNewConfigFile = IO::Path::Combine(Application::StartupPath, System::String::Concat(Application::ProductName, ".ini"));
			System::String ^pOldConfigFile = IO::Path::Combine(Application::StartupPath, System::String::Concat(Application::ProductName, ".old.ini"));
			if(IO::File::Exists(pNewConfigFile))
			{
				bHasConfig = this->ReadConfigFile(pNewConfigFile);
			}
			else if(IO::File::Exists(pOldConfigFile))
			{
				bHasConfig = this->ReadConfigFile(pOldConfigFile);
			}
			this->RestoreForm();

			// If we were pased a file, load it.
			array<System::String^>^ CommandLineArgs = System::Environment::GetCommandLineArgs();

			if(CommandLineArgs->Length >= 2)
			{
				System::String ^sFilePath = CommandLineArgs[1];

				if(System::IO::File::Exists(sFilePath))
				{
					if(sFilePath->ToLower()->EndsWith(".vtf") || sFilePath->ToLower()->EndsWith(".vmt"))
					{
						this->Open(sFilePath, false);
					}
					else
					{
						array<System::String^>^ sFileNames = gcnew array<System::String^>(1);
						sFileNames[0] = sFilePath;
						this->Import(sFileNames);
					}
				}
			}

			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				// Set intitial clipboard state.
				this->toolStripPaste->Enabled = System::Windows::Forms::Clipboard::GetDataObject()->GetDataPresent(System::Windows::Forms::DataFormats::Bitmap);
				this->btnPaste->Enabled = this->toolStripPaste->Enabled;

				// Add ourselves to clipboard notification chain.
				if(this->hWndNewViewer == 0)
				{
					this->hWndNewViewer = SetClipboardViewer((HWND)this->Handle.ToPointer());
				}
			}
			else
			{	// Set intitial clipboard state.
				this->toolStripPaste->Enabled = true;
				this->btnPaste->Enabled = this->toolStripPaste->Enabled;
			}
		}

		private: System::Void CVTFEdit_Closing(System::Object ^  sender, System::ComponentModel::CancelEventArgs ^  e)
		{
			//Causes crash when more than once instance of VTFEdit is open.  WM_DESTROY is all that is needed?
			//ChangeClipboardChain((HWND)this->Handle.ToPointer(), this->hWndNewViewer);
			
			// Uncomment this code if the program returns to using an installer
			//System::String ^pNewConfigFile = IO::Path::Combine(GetAppDataFolder(), System::String::Concat(Application::ProductName, ".ini"));
			System::String ^pNewConfigFile = IO::Path::Combine(Application::StartupPath, System::String::Concat(Application::ProductName, ".ini"));
			System::String ^pOldConfigFile = IO::Path::Combine(Application::StartupPath, System::String::Concat(Application::ProductName, ".old.ini"));
			if(this->WriteConfigFile(pNewConfigFile))
			{
				if(IO::File::Exists(pOldConfigFile))
				{
					try
					{
						IO::File::Delete(pOldConfigFile);
					}
					catch(Exception ^)
					{
					}
				}
			}
		}

		private: System::Void CVTFEdit_Move(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->BackupForm();
		}

		private: System::Void CVTFEdit_Resize(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->BackupForm();
			this->UpdateVTFFile();
		}

		private: System::Void splSidebar_SplitterMoved(System::Object ^  sender, System::Windows::Forms::SplitterEventArgs ^  e)
		{
			this->BackupForm();
			this->UpdateVTFFile();
		}

		private: void BackupForm()
		{
			if(!this->bFormRestoring && this->WindowState != FormWindowState::Minimized)
			{
				if(this->WindowState != FormWindowState::Maximized)
				{
					this->FormSaveLocation = Location;
					this->FormSaveSize = Size;
				}
				this->iFormSaveSidebarSplitPosition = this->splSidebar->SplitPosition;
				this->iFormSaveSidebar2SplitPosition = this->splSidebar2->SplitPosition;
				this->iFormSaveVMTTextZoom = this->txtVMTFile->ZoomFactor;

				this->FormSaveWindowState = this->WindowState;
			}
		}

		private: void RestoreForm()
		{
			this->bFormRestoring = true;
			try
			{
				this->Location = this->FormSaveLocation;
				this->Size = this->FormSaveSize;
				this->WindowState = this->FormSaveWindowState;
				this->splSidebar->SplitPosition = this->iFormSaveSidebarSplitPosition;
				this->txtVMTFile->ZoomFactor = this->iFormSaveVMTTextZoom;
			}
			catch(Exception ^)
			{

			}
			this->bFormRestoring = false;
		}

		//
		// WndProc()
		// Override default WndProc to process clipboard messages.
		//
		protected: System::Void WndProc(Message %e) override
		{
			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				switch(e.Msg)
				{
				case WM_CHANGECBCHAIN:
					// Store the changed handle of the next item in the clipboard chain.
					this->hWndNewViewer = (HWND)e.LParam.ToPointer();

					if(this->hWndNewViewer != 0)
					{
						::SendMessage(this->hWndNewViewer, e.Msg, (WPARAM)e.WParam.ToPointer(), (LPARAM)e.LParam.ToPointer());
					}

					// We have processed this message.
					e.Result = System::IntPtr::Zero;
					break;
				case WM_DRAWCLIPBOARD:
				{
					try
					{
						this->btnPaste->Enabled = System::Windows::Forms::Clipboard::GetDataObject()->GetDataPresent(System::Windows::Forms::DataFormats::Bitmap);
					}
					catch(Exception ^)
					{
						this->btnPaste->Enabled = false;
					}
					this->toolStripPaste->Enabled = this->btnPaste->Enabled;

					this->btnVMTFilePaste->Enabled = false;
					try
					{
						array<System::String^>^ Formats = System::Windows::Forms::Clipboard::GetDataObject()->GetFormats();
						for(int i = 0; i < Formats->Length; i++)
						{
							if(System::Windows::Forms::DataFormats::GetFormat(Formats[i])->Name->Equals("Text"))
							{
								this->btnVMTFilePaste->Enabled = true;
								break;
							}
						}
					}
					catch(Exception ^)
					{
						this->btnVMTFilePaste->Enabled = false;
					}

					// Pass the message on.
					if(this->hWndNewViewer != 0)
					{
						::SendMessage(this->hWndNewViewer, e.Msg, (WPARAM)e.WParam.ToPointer(), (LPARAM)e.LParam.ToPointer());
					}

					// We have processed this message.
					e.Result = System::IntPtr::Zero;
					break;
				}
				case WM_DESTROY:
					ChangeClipboardChain((HWND)this->Handle.ToPointer(), this->hWndNewViewer);

					__super::WndProc(e);
					break;
				default:
					__super::WndProc(e);
					break;
				}
			}
			else
			{
				__super::WndProc(e);
			}
		}

		//
		// VTF and VMT routines.
		//

		private: void UpdateVTFFile()
		{
			if(this->VTFFile == 0)
				return;

			static bool bUpdating = false;
			if(bUpdating)
				return;

			bUpdating = true;

			this->picVTFFileTL->Visible = true;

			this->picVTFFileTL->Image = nullptr;
			this->picVTFFileTR->Image = nullptr;
			this->picVTFFileBL->Image = nullptr;
			this->picVTFFileBR->Image = nullptr;

			delete []this->ucImageData;
			this->ucImageData = 0;

			vlUInt uiFrame = Convert::ToUInt32(this->numFrame->Value);
			vlUInt uiFace = Convert::ToUInt32(this->numFace->Value);
			vlUInt uiSlice = Convert::ToUInt32(this->numSlice->Value);
			vlUInt uiMipmap = Convert::ToUInt32(this->numMipmap->Value);
			vlSingle sHDRExposure = Convert::ToSingle(this->trkHDRExposure->Value) / 100.0f;

			vlUInt uiWidth = 0;
			vlUInt uiHeight = 0;
			vlUInt uiDepth = 0;

			vlUInt uiScaledWidth = 0;
			vlUInt uiScaledHeight = 0;

			vlByte *lpBuffer = nullptr;
			vlUInt uiBufferSize = 0;
			
			this->VTFFile->ComputeMipmapDimensions(this->VTFFile->GetWidth(), this->VTFFile->GetHeight(), this->VTFFile->GetDepth(), uiMipmap, uiWidth, uiHeight, uiDepth);

			if(uiSlice >= uiDepth)
				uiSlice = uiDepth - 1;

			this->numSlice->Value = uiSlice;
			this->numSlice->Maximum = uiDepth;

			uiScaledWidth = (vlUInt)((float)uiWidth * this->fImageScale);
			uiScaledHeight = (vlUInt)((float)uiHeight * this->fImageScale);

			// Allocate buffer to decode image data to.
			uiBufferSize = this->VTFFile->ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888);
			
			lpBuffer = new vlByte[uiBufferSize];

			// Decode image data.
			vlSetFloat(VTFLIB_FP16_HDR_EXPOSURE, sHDRExposure);
			this->VTFFile->ConvertToRGBA8888(this->VTFFile->GetData(uiFrame, uiFace, uiSlice, uiMipmap), lpBuffer, uiWidth, uiHeight, this->VTFFile->GetFormat());

			float fInverseImageScale = 1.0f / this->fImageScale;

			vlUInt uiScaledStride = (uiScaledWidth + 3) / 4 * 4;

			// Allocate buffer for bitmap image data.
			this->ucImageData = new unsigned char[uiScaledStride * uiScaledHeight * 3];

			vlUInt uiR{}, uiG{}, uiB{};

			// Pick R, G, B and A indicies.
			if(this->btnChannelRGB->Checked)
			{
				uiR = 0;
				uiG = 1;
				uiB = 2;
			}
			else if(this->btnChannelR->Checked)
			{
				uiR = 0;
				uiG = 0;
				uiB = 0;
			}
			else if(this->btnChannelG->Checked)
			{
				uiR = 1;
				uiG = 1;
				uiB = 1;
			}
			else if(this->btnChannelB->Checked)
			{
				uiR = 2;
				uiG = 2;
				uiB = 2;
			}
			else if(this->btnChannelA->Checked)
			{
				uiR = 3;
				uiG = 3;
				uiB = 3;
			}

			if(this->btnMask->Checked)// && (this->VTFFile->GetFlag(TEXTUREFLAGS_ONEBITALPHA) || this->VTFFile->GetFlag(TEXTUREFLAGS_EIGHTBITALPHA)))
			{
				// Generate checkered mask and alpha blend texture with it.
				for(vlUInt i = 0; i < uiScaledWidth; i++)
				{
					for(vlUInt j = 0; j < uiScaledHeight; j++)
					{
						vlUInt uiSrcIndex = ((vlUInt)((float)i * fInverseImageScale) + (vlUInt)((float)j * fInverseImageScale) * uiWidth) * 4;
						vlUInt uiDstIndex = (i + j * uiScaledStride) * 3;

						#pragma warning(disable:6385)
						float fAlpha = (float)lpBuffer[uiSrcIndex + 3] / (float)255.0f;
						float fOneMinusAlpha = 1.0f - fAlpha;
						
						float fBlendR = 255.0f;
						float fBlendG = 255.0f;
						float fBlendB = 255.0f;
						if ( !bCustomAlphaBackground ) {
							fBlendR = (i / 8 % 2 == j / 8 % 2) ? 255.0f : 191.25f;
							fBlendG = (i / 8 % 2 == j / 8 % 2) ? 255.0f : 191.25f;
							fBlendB = (i / 8 % 2 == j / 8 % 2) ? 255.0f : 191.25f;
						}
						else {
							fBlendR = fAlphaBackgroundColor.R;
							fBlendG = fAlphaBackgroundColor.G;
							fBlendB = fAlphaBackgroundColor.B;
						}

						this->ucImageData[uiDstIndex + 2] = (unsigned char)(fAlpha * (float)lpBuffer[uiSrcIndex + uiR] + fOneMinusAlpha * fBlendR);
						this->ucImageData[uiDstIndex + 1] = (unsigned char)(fAlpha * (float)lpBuffer[uiSrcIndex + uiG] + fOneMinusAlpha * fBlendG);
						this->ucImageData[uiDstIndex + 0] = (unsigned char)(fAlpha * (float)lpBuffer[uiSrcIndex + uiB] + fOneMinusAlpha * fBlendB);
					}
				}
			}
			else
			{
				// Don't generate checkered mask.
				for(vlUInt i = 0; i < uiScaledWidth; i++)
				{
					for(vlUInt j = 0; j < uiScaledHeight; j++)
					{
						vlUInt uiSrcIndex = ((vlUInt)((float)i * fInverseImageScale) + (vlUInt)((float)j * fInverseImageScale) * uiWidth) * 4;
						vlUInt uiDstIndex = (i + j * uiScaledStride) * 3;

						this->ucImageData[uiDstIndex + 2] = lpBuffer[uiSrcIndex + uiR];
						this->ucImageData[uiDstIndex + 1] = lpBuffer[uiSrcIndex + uiG];
						this->ucImageData[uiDstIndex + 0] = lpBuffer[uiSrcIndex + uiB];
					}
				}
			}

			delete []lpBuffer;

			#pragma warning(disable:6001) // disable uninitialized memory warning
			System::Drawing::Bitmap^ vtfImage = gcnew System::Drawing::Bitmap(uiScaledWidth, uiScaledHeight, uiScaledStride * 3, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr)this->ucImageData);

			this->picVTFFileTL->Size = System::Drawing::Size(uiScaledWidth, uiScaledHeight);
			this->picVTFFileTL->Image = vtfImage;

			this->picVTFFileTL->Visible = true;

			if (this->btnTile->Checked)
			{
				this->picVTFFileTR->Size = this->picVTFFileTL->Size;
				this->picVTFFileTR->Image = vtfImage;

				this->picVTFFileBL->Size = this->picVTFFileTL->Size;
				this->picVTFFileBL->Image = vtfImage;

				this->picVTFFileBR->Size = this->picVTFFileTL->Size;
				this->picVTFFileBR->Image = vtfImage;

				this->picVTFFileTR->Visible = true;
				this->picVTFFileBL->Visible = true;
				this->picVTFFileBR->Visible = true;
			}
			else {
				this->picVTFFileTR->Visible = false;
				this->picVTFFileBL->Visible = false;
				this->picVTFFileBR->Visible = false;
			}
			
			bUpdating = false;
		}

		private: void UpdateVTFView()
		{
			if (this->btnTile->Checked)
			{
				if (!this->pnlMain->HorizontalScroll->Visible || !this->pnlMain->VerticalScroll->Visible)
				{
					this->picVTFFileTL->Location = System::Drawing::Point(
						((this->pnlMain->Size.Width / 2) - (this->picVTFFileTL->Size.Width)),
						((this->pnlMain->Size.Height / 2) - (this->picVTFFileTL->Size.Height)));
				}

				this->picVTFFileTR->Location = System::Drawing::Point(
					this->picVTFFileTL->Location.X + this->picVTFFileTL->Size.Width, 
					this->picVTFFileTL->Location.Y );

				this->picVTFFileBL->Location = System::Drawing::Point(
					this->picVTFFileTL->Location.X, 
					this->picVTFFileTL->Location.Y + this->picVTFFileTL->Size.Height );

				this->picVTFFileBR->Location = System::Drawing::Point(
					this->picVTFFileTL->Location.X + this->picVTFFileTL->Size.Width, 
					this->picVTFFileTL->Location.Y + this->picVTFFileTL->Size.Height );

				// Fix one case of weirdness of Panel's autoscroll. If image is smaller than panel and scroll is still visible, fix the location.
				if (((this->picVTFFileTL->Size.Width * 2 <= this->pnlMain->Size.Width) && this->pnlMain->HorizontalScroll->Visible) ||
					((this->picVTFFileTL->Size.Height * 2 <= this->pnlMain->Size.Height) && this->pnlMain->VerticalScroll->Visible))
				{
					this->picVTFFileTL->Location = System::Drawing::Point(0, 0);
					this->UpdateVTFView();
				}
			}
			else
			{
				if (!this->pnlMain->HorizontalScroll->Visible || !this->pnlMain->VerticalScroll->Visible)
				{
					this->picVTFFileTL->Location = System::Drawing::Point(
						((this->pnlMain->Size.Width / 2) - (this->picVTFFileTL->Size.Width / 2)),
						((this->pnlMain->Size.Height / 2) - (this->picVTFFileTL->Size.Height / 2)));
				}

				// Fix one case of weirdness of Panel's autoscroll. If image is smaller than panel and scroll is still visible, fix the location.
				if (((this->picVTFFileTL->Size.Width <= this->pnlMain->Size.Width) && this->pnlMain->HorizontalScroll->Visible) || 
					((this->picVTFFileTL->Size.Height <= this->pnlMain->Size.Height) && this->pnlMain->VerticalScroll->Visible))
				{
					this->picVTFFileTL->Location = System::Drawing::Point(0,0);
					this->UpdateVTFView();
				}
			}

			this->pnlInfo1->Text = System::String::Concat((this->fImageScale * 100.0f).ToString(), "%");
		}

		private: void SetVTFFile(VTFLib::CVTFFile *VTFFile)
		{
			this->numFrame->Value = 0;
			this->numFace->Value = 0;
			this->numSlice->Value = 0;
			this->numMipmap->Value = 0;

			this->numFrame->Maximum = VTFFile->GetFrameCount() - 1;
			this->trkFrame->Maximum = VTFFile->GetFrameCount() - 1;
			this->numFace->Maximum = VTFFile->GetFaceCount() - 1;
			this->numSlice->Maximum = VTFFile->GetDepth() - 1;
			this->numMipmap->Maximum = VTFFile->GetMipmapCount() - 1;

			this->toolStripZoomIn->Enabled = true;
			this->toolStripZoomOut->Enabled = true;
			this->clrReflectivity->Enabled = true;

			if(VTFFile->GetStartFrame() < VTFFile->GetFrameCount())
			{
				this->numFrame->Value = VTFFile->GetStartFrame();
			}

			if(VTFFile->GetFrameCount() > 1)
			{
				this->btnAnimate->Enabled = true;
				this->numFrame->Enabled = true;
				this->trkFrame->Enabled = true;
				this->numImageStartFrame->Enabled = true;
			}
			else 
			{
				this->numFrame->Enabled = false;
				this->trkFrame->Enabled = false;
				this->numImageStartFrame->Enabled = false;
			}

			// It was meant to be this way
			if((VTFFile->GetFaceCount() - 1) < 1) {
				this->numFace->Enabled = false;
			}
			else {
				this->numFace->Enabled = true;
			}

			if((VTFFile->GetDepth() - 1) < 1) {
				this->numSlice->Enabled = false;
			}
			else {
				this->numSlice->Enabled = true;
			}

			if((VTFFile->GetMipmapCount() - 1) < 1) {
				this->numMipmap->Enabled = false;
			}
			else {
				this->numMipmap->Enabled = true;
			}

			if(VTFFile->GetFormat() == IMAGE_FORMAT_RGBA16161616F)
			{
				this->trkHDRExposure->Enabled = true;
			}
			else {
				this->trkHDRExposure->Enabled = false;
			}

			if (VTFFile->GetSupportsResources())
			{
				this->btnEditResources->Enabled = true;
			}
			else {
				this->btnEditResources->Enabled = false;
			}

			vlUInt uiFlags = VTFFile->GetFlags();

			this->lstFlags->BeginUpdate();
			this->lstFlags->Items->Clear();

			#pragma warning(disable: 4800)
			this->lstFlags->Items->Add("Point Sample", uiFlags & TEXTUREFLAGS_POINTSAMPLE);
			this->lstFlags->Items->Add("Trilinear", uiFlags & TEXTUREFLAGS_TRILINEAR);
			this->lstFlags->Items->Add("Clamp S", uiFlags & TEXTUREFLAGS_CLAMPS);
			this->lstFlags->Items->Add("Clamp T", uiFlags & TEXTUREFLAGS_CLAMPT);
			this->lstFlags->Items->Add("Anisotropic", uiFlags & TEXTUREFLAGS_ANISOTROPIC);
			this->lstFlags->Items->Add("Hint DXT5", uiFlags & TEXTUREFLAGS_HINT_DXT5);
			this->lstFlags->Items->Add("SRGB", uiFlags & TEXTUREFLAGS_SRGB);
			this->lstFlags->Items->Add("Normal Map", uiFlags & TEXTUREFLAGS_NORMAL);
			this->lstFlags->Items->Add("No Mipmap", uiFlags & TEXTUREFLAGS_NOMIP);
			this->lstFlags->Items->Add("No Level Of Detail", uiFlags & TEXTUREFLAGS_NOLOD);
			this->lstFlags->Items->Add("No Minimum Mipmap", uiFlags & TEXTUREFLAGS_MINMIP);
			this->lstFlags->Items->Add("Procedural", uiFlags & TEXTUREFLAGS_PROCEDURAL);
			this->lstFlags->Items->Add("(VTEX) One Bit Alpha", uiFlags & TEXTUREFLAGS_ONEBITALPHA);
			this->lstFlags->Items->Add("(VTEX) Eight Bit Alpha", uiFlags & TEXTUREFLAGS_EIGHTBITALPHA);
			this->lstFlags->Items->Add("Enviroment Map", uiFlags & TEXTUREFLAGS_ENVMAP);
			this->lstFlags->Items->Add("Render Target", uiFlags & TEXTUREFLAGS_RENDERTARGET);
			this->lstFlags->Items->Add("Depth Render Target", uiFlags & TEXTUREFLAGS_DEPTHRENDERTARGET);
			this->lstFlags->Items->Add("No Debug Override", uiFlags & TEXTUREFLAGS_NODEBUGOVERRIDE);
			this->lstFlags->Items->Add("Single Copy", uiFlags & TEXTUREFLAGS_SINGLECOPY);
			this->lstFlags->Items->Add("(VTEX) One Over Mipmap Level In Alpha", uiFlags & TEXTUREFLAGS_UNUSED0);
			this->lstFlags->Items->Add("(VTEX) Premultiply Color By One Over Mipmap Level     ", uiFlags & TEXTUREFLAGS_UNUSED1); // Spaces for scroll bar
			this->lstFlags->Items->Add("(VTEX) Normal To DuDv", uiFlags & TEXTUREFLAGS_UNUSED2);
			this->lstFlags->Items->Add("(VTEX) Alpha Test Mipmap Generation", uiFlags & TEXTUREFLAGS_UNUSED3);
			this->lstFlags->Items->Add("No Depth Buffer", uiFlags & TEXTUREFLAGS_NODEPTHBUFFER);
			this->lstFlags->Items->Add("(VTEX) NICE Filtered", uiFlags & TEXTUREFLAGS_UNUSED4);
			this->lstFlags->Items->Add("Clamp U", uiFlags & TEXTUREFLAGS_CLAMPU);
			this->lstFlags->Items->Add("Vertex Texture", uiFlags & TEXTUREFLAGS_VERTEXTEXTURE);
			this->lstFlags->Items->Add("SSBump", uiFlags & TEXTUREFLAGS_SSBUMP);
			this->lstFlags->Items->Add("(VTEX) Unfilterable", uiFlags & TEXTUREFLAGS_UNUSED5);
			this->lstFlags->Items->Add("Clamp Border", uiFlags & TEXTUREFLAGS_BORDER);
			#pragma warning(default: 4800)

			this->lstFlags->EndUpdate();

			vlUInt minVersion = VTFFile->GetMinorVersion();
			switch (minVersion)
			{
			case 5: this->cboFileVersion->SelectedIndex = 0; break;
			case 4: this->cboFileVersion->SelectedIndex = 1; break;
			case 3: this->cboFileVersion->SelectedIndex = 2; break;
			case 2: this->cboFileVersion->SelectedIndex = 3; break;
			case 1: this->cboFileVersion->SelectedIndex = 4; break;
			case 0: this->cboFileVersion->SelectedIndex = 5; break;
			default: this->cboFileVersion->SelectedIndex = 2; break;
			}
			//this->lblFileVersion->Text = System::String::Concat(VTFFile->GetMajorVersion().ToString(), ".", VTFFile->GetMinorVersion().ToString());
			this->lblFileSize->Text = System::String::Concat(((float)VTFFile->GetSize() / 1024.0f).ToString("#,##0.000"), " KB");

			this->lblImageWidth->Text = VTFFile->GetWidth().ToString();
			this->lblImageHeight->Text = VTFFile->GetHeight().ToString();
			this->lblImageFormat->Text = this->GetImageFormatString(VTFFile->GetFormat());
			//this->lblImageStartFrame->Text = VTFFile->GetStartFrame().ToString();
			this->numImageStartFrame->Maximum = VTFFile->GetFrameCount() - 1;
			this->numImageStartFrame->Value = VTFFile->GetStartFrame() == 0xffff ? 0 : VTFFile->GetStartFrame();
			//this->lblImageBumpmapScale->Text = VTFFile->GetBumpmapScale().ToString("0.00");
			this->numImageBumpmapScale->Value = System::Decimal(VTFFile->GetBumpmapScale());

			vlSingle sX, sY, sZ;
			VTFFile->GetReflectivity(sX, sY, sZ);

			this->lblImageReflectivity->Text = System::String::Concat(
				  "R ", sX.ToString("0.000"), 
				", G ", sY.ToString("0.000"), 
				", B ", sZ.ToString("0.000"));
			this->clrReflectivity->BackColor = System::Drawing::Color::FromArgb(int(sX*255), int(sY*255), int(sZ*255));

			this->treResources->BeginUpdate();
			this->treResources->Nodes->Clear();

			for(vlUInt i = 0; i < VTFFile->GetResourceCount(); i++)
			{
				vlUInt uiResource = VTFFile->GetResourceType(i);

				System::String ^sName = "Unknown";
				switch(uiResource)
				{
				case VTF_LEGACY_RSRC_LOW_RES_IMAGE:
					sName = "Thumbnail Image";
					break;
				case VTF_LEGACY_RSRC_IMAGE:
					sName = "Image";
					break;
				case VTF_RSRC_SHEET:
					sName = "Sheet";
					break;
				case VTF_RSRC_CRC:
					sName = "Cyclic Redundancy Check";
					break;
				case VTF_RSRC_TEXTURE_LOD_SETTINGS:
					sName = "LOD Settings";
					break;
				case VTF_RSRC_TEXTURE_SETTINGS_EX:
					sName = "Extended Texture Settings";
					break;
				case VTF_RSRC_KEY_VALUE_DATA:
					sName = "Key/Value Data";
					break;
				default:
					sName = "Unknown";
					break;
				}

				System::Windows::Forms::TreeNode ^pNode = gcnew System::Windows::Forms::TreeNode(sName);

				vlUInt uiSize = 0;
				vlVoid *lpData = VTFFile->GetResourceData(uiResource, uiSize);

				switch(uiResource)
				{
				case VTF_RSRC_CRC:
					pNode->Nodes->Add(System::String::Concat("Checksum: 0x", (*(vlUInt *)lpData).ToString("X8")));
					break;
				case VTF_RSRC_TEXTURE_LOD_SETTINGS:
					if(lpData && uiSize == sizeof(SVTFTextureLODControlResource))
					{
						SVTFTextureLODControlResource *pLODControl = (SVTFTextureLODControlResource *)lpData;
						pNode->Nodes->Add(System::String::Concat("Clamp U: ", pLODControl->ResolutionClampU.ToString()));
						pNode->Nodes->Add(System::String::Concat("Clamp V: ", pLODControl->ResolutionClampV.ToString()));
						break;
					}
				case VTF_RSRC_KEY_VALUE_DATA:
					if(lpData && uiSize)
					{
						VTFLib::CVMTFile *pVMTFile = new VTFLib::CVMTFile();

						if(pVMTFile->Load(lpData, uiSize))
						{
							pNode->Text = gcnew System::String(pVMTFile->GetRoot()->GetName());
							this->SetInformation(pNode, pVMTFile->GetRoot());
						}
					}
				default:
					if(lpData && uiSize == sizeof(vlUInt))
					{
						pNode->Nodes->Add(System::String::Concat("Data: 0x", (*(vlUInt *)lpData).ToString("X8")));
					}
					else
					{
						pNode->Nodes->Add(System::String::Concat("Size: ", uiSize.ToString("#,##0"), " B"));
					}
					break;
				}

				this->treResources->Nodes->Add(pNode);
				pNode->Expand();
			}

			this->treResources->EndUpdate();

			this->VTFFile = VTFFile;

			this->SetInitialImageScale();
			this->UpdateVTFFile();
			this->UpdateVTFView();
		}

		private: void SetInitialImageScale()
		{
			// set initial size of the image to a generally appropriate size to hopefully not need to immediately zoom in or out
			if (this->btnTile->Checked) {
				if (this->VTFFile->GetWidth() >= 4096 || this->VTFFile->GetHeight() >= 4096) { this->fImageScale = 0.0625f; }
				else if (this->VTFFile->GetWidth() >= 2048 || this->VTFFile->GetHeight() >= 2048) { this->fImageScale = 0.125f; }
				else if (this->VTFFile->GetWidth() >= 1024 || this->VTFFile->GetHeight() >= 1024) { this->fImageScale = 0.25f; }
				else if (this->VTFFile->GetWidth() >= 512 || this->VTFFile->GetHeight() >= 512) { this->fImageScale = 0.5f; }
				else if (this->VTFFile->GetWidth() >= 256 || this->VTFFile->GetHeight() >= 256) { this->fImageScale = 1.0f; }
				else if (this->VTFFile->GetWidth() >= 128 || this->VTFFile->GetHeight() >= 128) { this->fImageScale = 2.0f; }
				else if (this->VTFFile->GetWidth() >= 64 || this->VTFFile->GetHeight() >= 64) { this->fImageScale = 4.0f; }
				else if (this->VTFFile->GetWidth() >= 32 || this->VTFFile->GetHeight() >= 32) { this->fImageScale = 8.0f; }
				else if (this->VTFFile->GetWidth() >= 16 || this->VTFFile->GetHeight() >= 16) { this->fImageScale = 16.0f; }
				else if (this->VTFFile->GetWidth() >= 8 || this->VTFFile->GetHeight() >= 8) { this->fImageScale = 32.0f; }
				else if (this->VTFFile->GetWidth() >= 4 || this->VTFFile->GetHeight() >= 4) { this->fImageScale = 64.0f; }
				else if (this->VTFFile->GetWidth() >= 2 || this->VTFFile->GetHeight() >= 2) { this->fImageScale = 128.0f; }
			}
			else {
				if (this->VTFFile->GetWidth() >= 4096 || this->VTFFile->GetHeight() >= 4096) { this->fImageScale = 0.125f; }
				else if (this->VTFFile->GetWidth() >= 2048 || this->VTFFile->GetHeight() >= 2048) { this->fImageScale = 0.25f; }
				else if (this->VTFFile->GetWidth() >= 1024 || this->VTFFile->GetHeight() >= 1024) { this->fImageScale = 0.5f; }
				else if (this->VTFFile->GetWidth() >= 512 || this->VTFFile->GetHeight() >= 512) { this->fImageScale = 1.0f; }
				else if (this->VTFFile->GetWidth() >= 256 || this->VTFFile->GetHeight() >= 256) { this->fImageScale = 2.0f; }
				else if (this->VTFFile->GetWidth() >= 128 || this->VTFFile->GetHeight() >= 128) { this->fImageScale = 4.0f; }
				else if (this->VTFFile->GetWidth() >= 64 || this->VTFFile->GetHeight() >= 64) { this->fImageScale = 8.0f; }
				else if (this->VTFFile->GetWidth() >= 32 || this->VTFFile->GetHeight() >= 32) { this->fImageScale = 16.0f; }
				else if (this->VTFFile->GetWidth() >= 16 || this->VTFFile->GetHeight() >= 16) { this->fImageScale = 32.0f; }
				else if (this->VTFFile->GetWidth() >= 8 || this->VTFFile->GetHeight() >= 8) { this->fImageScale = 64.0f; }
				else if (this->VTFFile->GetWidth() >= 4 || this->VTFFile->GetHeight() >= 4) { this->fImageScale = 128.0f; }
				else if (this->VTFFile->GetWidth() >= 2 || this->VTFFile->GetHeight() >= 2) { this->fImageScale = 256.0f; }
			}
		}

		private: void SetInformation(System::Windows::Forms::TreeNode ^pNode, VTFLib::Nodes::CVMTGroupNode *pVMTNode)
		{
			for(vlUInt i = 0; i < pVMTNode->GetNodeCount(); i++)
			{
				VTFLib::Nodes::CVMTNode *pVMTChild = pVMTNode->GetNode(i);
				switch(pVMTChild->GetType())
				{
					case NODE_TYPE_GROUP:
					{
						System::Windows::Forms::TreeNode ^pChild = gcnew System::Windows::Forms::TreeNode(gcnew System::String(pVMTChild->GetName()));
						this->SetInformation(pChild, static_cast<VTFLib::Nodes::CVMTGroupNode *>(pVMTChild));
						pNode->Nodes->Add(pChild);
						break;
					}
					case NODE_TYPE_STRING:
					{
						System::Windows::Forms::TreeNode ^pChild = gcnew System::Windows::Forms::TreeNode(gcnew System::String(pVMTChild->GetName()));
						pChild->Nodes->Add(gcnew System::Windows::Forms::TreeNode(gcnew System::String(static_cast<VTFLib::Nodes::CVMTStringNode *>(pVMTChild)->GetValue())));
						pNode->Nodes->Add(pChild);
						break;
					}
					case NODE_TYPE_INTEGER:
					{
						System::Windows::Forms::TreeNode ^pChild = gcnew System::Windows::Forms::TreeNode(gcnew System::String(pVMTChild->GetName()));
						pChild->Nodes->Add(gcnew System::Windows::Forms::TreeNode(static_cast<VTFLib::Nodes::CVMTIntegerNode *>(pVMTChild)->GetValue().ToString()));
						pNode->Nodes->Add(pChild);
						break;
					}
					case NODE_TYPE_SINGLE:
					{
						System::Windows::Forms::TreeNode ^pChild = gcnew System::Windows::Forms::TreeNode(gcnew System::String(pVMTChild->GetName()));
						pChild->Nodes->Add(gcnew System::Windows::Forms::TreeNode(static_cast<VTFLib::Nodes::CVMTSingleNode *>(pVMTChild)->GetValue().ToString()));
						pNode->Nodes->Add(pChild);
						break;
					}
				}
			}
		}

		private: bool GetVTFFile()
		{
			this->VTFFile->SetFlags(0);
			for(vlUInt i = 0, j = 0x00000001; i < (vlUInt)this->lstFlags->Items->Count; i++, j <<= 1)
			{
				this->VTFFile->SetFlag((VTFImageFlag)j, this->lstFlags->GetItemChecked(i));
			}

			this->VTFFile->SetStartFrame(Convert::ToUInt32(this->numImageStartFrame->Value));

			VTFFile->SetBumpmapScale(Convert::ToSingle(this->numImageBumpmapScale->Value));

			return true;
		}

		private: void SetVMTFile(VTFLib::CVMTFile *VMTFile)
		{
			this->VMTFile = VMTFile;

			this->EnableVMTContextMenuItems();
			//this->SyntaxHilighter->Enabled = true; // Disabled for performance reasons.
			//this->SyntaxHilighter->Process(); // Disabled for performance reasons.

			this->txtVMTFile->Visible = true;
		}

		private: bool GetVMTFile()
		{
			char *cText = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->txtVMTFile->Text).ToPointer();
			vlBool bResult = VMTFile->Load( cText, this->txtVMTFile->Text->Length);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cText);

			if (!bResult)
			{
				if (bWarnings)
				{
					if (bNotificationSounds)
					{
						System::Media::SystemSounds::Asterisk->Play();
					}
					MessageBox::Show(System::String::Concat("Error parsing VMT file:\n\n", gcnew System::String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}

			return bResult != 0;
		}

		private: bool CloseFile() {
			if (this->VTFFile != 0 || this->VMTFile != 0)
			{
				if (bWarnings)
				{
					if (bNotificationSounds)
					{
						System::Media::SystemSounds::Asterisk->Play();
					}
					return MessageBox::Show("Are you sure you want to close the current file?", "Confirm Close", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes;
				}
				else {
					return true;
				}
			}
			else {
				return true;
			}
		}

		private: void New()
		{
			this->ClearAll();

			VTFLib::CVMTFile *VMTFile = new VTFLib::CVMTFile();

			this->txtVMTFile->Text = "\"LightmappedGeneric\"\n{\n\t\"$basetexture\"\t\"\"\n}";
			this->txtVMTFile->SelectionStart = 1;
			this->txtVMTFile->SelectionLength = 18;

			this->SetVMTFile(VMTFile);

			this->FileName = nullptr;

			this->btnSave->Enabled = true;
			this->toolStripSave->Enabled = true;
			this->toolStripClose->Enabled = true;
			this->btnClose->Enabled = true;
			this->btnSaveAs->Enabled = true;

			this->pnlSidebar->Visible = false;
			this->pnlSidebar2->Visible = false;

			this->txtVMTFile->Focus();
		}

		private: void ClearAll()
		{
			this->pnlSidebar->Visible = true;
			this->pnlSidebar2->Visible = true;

			this->btnSave->Enabled = false;
			this->toolStripSave->Enabled = false;
			this->toolStripClose->Enabled = false;
			this->btnClose->Enabled = false;
			this->btnSaveAs->Enabled = false;

			this->btnExport->Enabled = false;
			this->btnExportAll->Enabled = false;
			this->toolStripExport->Enabled = false;

			this->toolStripCopy->Enabled = false;
			this->toolStripZoomIn->Enabled = false;
			this->toolStripZoomOut->Enabled = false;
			this->btnCopy->Enabled = false;

			this->trkHDRExposure->Enabled = false;

			this->btnAnimate->Text = "&Play";
			this->btnAnimate->Enabled = false;
			this->tmrAnimate->Enabled = false;

			this->numFrame->Enabled = false;
			this->numFrame->Value = 0;
			this->numFace->Enabled = false;
			this->numFace->Value = 0;
			this->numSlice->Enabled = false;
			this->numSlice->Value = 0;
			this->numMipmap->Enabled = false;
			this->numMipmap->Value = 0;

			this->numImageStartFrame->Enabled = false;
			this->numImageStartFrame->Value = 0;
			this->numImageBumpmapScale->Enabled = false;
			this->numImageBumpmapScale->Value = 1;
			this->trkHDRExposure->Enabled = false;
			this->trkFrame->Enabled = false;
			this->clrReflectivity->BackColor = System::Drawing::SystemColors::ControlLight;
			this->clrReflectivity->Enabled = false;
			this->lblImageReflectivity->Text = "";
			this->lblImageWidth->Text = "";
			this->lblImageHeight->Text = "";
			this->lblImageFormat->Text = "";
			this->lblFileSize->Text = "";
			this->cboFileVersion->SelectedIndex = -1;
			this->cboFileVersion->Enabled = false;

			this->btnEditResources->Enabled = false;
			this->treResources->Nodes->Clear();

			this->picVTFFileTL->Visible = false;
			this->picVTFFileTR->Visible = false;
			this->picVTFFileBL->Visible = false;
			this->picVTFFileBR->Visible = false;

			this->picVTFFileTL->Image = nullptr;
			this->picVTFFileTR->Image = nullptr;
			this->picVTFFileBL->Image = nullptr;
			this->picVTFFileBR->Image = nullptr;

			this->pnlMain->ContextMenu = nullptr;

			//this->treVMTFile->Visible = false;
			//this->treVMTFile->Nodes->Clear();
			//this->SyntaxHilighter->Enabled = false; // Disabled for performance reasons.
			//this->SyntaxHilighter->Purge(); // Disabled for performance reasons.

			this->txtVMTFile->Visible = false;
			this->txtVMTFile->Clear();
			this->txtVMTFile->ClearUndo();

			this->lstFlags->Items->Clear();

			delete this->VMTFile;
			this->VMTFile = 0;

			delete this->VTFFile;
			this->VTFFile = 0;

			delete[]this->ucImageData;
			this->ucImageData = 0;

			this->FileName = nullptr;
			this->pnlInfo1->Text = nullptr;
			this->pnlInfo2->Text = nullptr;
		}

		private: void Open(System::String ^sFileName, bool bTemp)
		{
			this->ClearAll();

			char cPath[512];
			CUtility::StringToCharPointer(sFileName, cPath, 512);

			if(sFileName->ToLower()->EndsWith(".vtf"))
			{
				VTFLib::CVTFFile *VTFFile = new VTFLib::CVTFFile();

				if(VTFFile->Load(cPath))
				{
					this->SetVTFFile(VTFFile);

					if(!bTemp)
					{
						this->FileName = sFileName;

						this->AddRecentFile(this->FileName);
					}
					else
					{
						this->FileName = nullptr;
					}

					this->btnSave->Enabled = true;
					this->toolStripSave->Enabled = true;
					this->toolStripClose->Enabled = true;
					this->btnClose->Enabled = true;
					this->btnSaveAs->Enabled = true;

					this->btnExport->Enabled = true;
					this->btnExportAll->Enabled = true;
					this->toolStripExport->Enabled = true;

					this->toolStripCopy->Enabled = true;
					this->btnCopy->Enabled = true;

					this->numImageBumpmapScale->Enabled = true;
					this->clrReflectivity->Enabled = true;

					this->cboFileVersion->Enabled = true;

					this->pnlSidebar->Visible = true;
					this->pnlSidebar2->Visible = true;

					this->pnlMain->ContextMenu = this->mnuVTFFile;

				}
				else
				{
					delete VTFFile;

					if (bWarnings)
					{
						if (bNotificationSounds)
						{
							System::Media::SystemSounds::Asterisk->Play();
						}
						MessageBox::Show(System::String::Concat("Error loading VTF texture:\n\n", gcnew System::String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}
			else if(sFileName->ToLower()->EndsWith(".vmt"))
			{
				VTFLib::CVMTFile *VMTFile = new VTFLib::CVMTFile();

				if(VMTFile->Load(cPath))
				{
					try
					{
						this->txtVMTFile->LoadFile(sFileName, System::Windows::Forms::RichTextBoxStreamType::PlainText);
					}
					catch(Exception ^e)
					{
						delete VMTFile;

						if (bWarnings)
						{
							if (bNotificationSounds)
							{
								System::Media::SystemSounds::Asterisk->Play();
							}
							MessageBox::Show(System::String::Concat("Error loading VMT file:\n\n", e->Message), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
						}
						return;
					}

					this->SetVMTFile(VMTFile);

					if(!bTemp)
					{
						this->FileName = sFileName;

						this->AddRecentFile(this->FileName);
					}
					else
					{
						this->FileName = nullptr;
					}

					this->btnSave->Enabled = true;
					this->toolStripSave->Enabled = true;
					this->toolStripClose->Enabled = true;
					this->btnClose->Enabled = true;
					this->btnSaveAs->Enabled = true;

					this->pnlSidebar->Visible = false;
					this->pnlSidebar2->Visible = false;

					this->txtVMTFile->Focus();
				}
				else
				{
					delete VMTFile;

					if (bWarnings)
					{
						if (bNotificationSounds)
						{
							System::Media::SystemSounds::Asterisk->Play();
						}
						MessageBox::Show(System::String::Concat("Error loading VMT file:\n\n", gcnew System::String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}
		}

		private: void Save(System::String ^sFileName)
		{
			if(sFileName == nullptr)
				return;

			if(this->VTFFile != 0)
			{
				char cPath[512];
				CUtility::StringToCharPointer(sFileName, cPath, 512);

				if (!this->GetVTFFile())
				{
					return;
				}

				vlUInt currentMinVersion = VTFFile->GetMinorVersion();
				vlUInt minVersion = this->cboFileVersion->SelectedIndex;
				switch (minVersion)
				{
				case 0: minVersion = 5; break;
				case 1: minVersion = 4; break;
				case 2: minVersion = 3; break;
				case 3: minVersion = 2; break;
				case 4: minVersion = 1; break;
				case 5: minVersion = 0; break;
				default: minVersion = 1; break;
				}

				this->VTFFile->SetMinorVersion(minVersion);
				// normally $reflectivity is in the range of 0.0 - 1.0
				this->VTFFile->SetReflectivity(float(this->colorDialog->Color.R)/255, float(this->colorDialog->Color.G)/255, float(this->colorDialog->Color.B)/255);

				if(this->VTFFile->Save(cPath))
				{
					this->FileName = sFileName;

					this->AddRecentFile(this->FileName);

					if(this->btnAutoCreateVMTFile->Checked)
					{
						CVMTFileUtility::CreateDefaultMaterial(this->FileName, this->FormVMTShader);
					}

					if(currentMinVersion != minVersion) {
						// Resources may need to be reloaded so the file won't need to be opened again to see the changes.
						this->SetVTFFile(VTFFile);

						// If the minor version has been changed, the size of the file will be different.
						this->lblFileSize->Text = System::String::Concat(((float)VTFFile->GetSize() / 1024.0f).ToString("#,##0.000"), " KB");
					}
				}
				else
				{
					if (bWarnings)
					{
						if (bNotificationSounds)
						{
							System::Media::SystemSounds::Asterisk->Play();
						}
						MessageBox::Show(System::String::Concat("Error saving VTF texture:\n\n", gcnew System::String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}
			else if(this->VMTFile != 0)
			{
				char cPath[512];
				CUtility::StringToCharPointer(sFileName, cPath, 512);

				if(!this->GetVMTFile())
				{
					return;
				}

				try
				{
					this->txtVMTFile->SaveFile(sFileName, System::Windows::Forms::RichTextBoxStreamType::PlainText);

					this->FileName = sFileName;
				}
				catch(Exception ^e)
				{
					if (bWarnings)
					{
						if (bNotificationSounds)
						{
							System::Media::SystemSounds::Asterisk->Play();
						}
						MessageBox::Show(System::String::Concat("Error saving VMT file:\n\n", e->Message), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}
		}

		private: void SaveAs()
		{
			if(this->VTFFile != 0)
			{
				if(this->dlgSaveVTFFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->Save(this->dlgSaveVTFFile->FileName);
				}
			}
			else if(this->VMTFile != 0)
			{
				if(this->dlgSaveVMTFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->Save(this->dlgSaveVMTFile->FileName);
				}
			}
		}

		private: void Import(array<System::String ^>^ sFileNames)
		{
			// Find the center of the main window to make this dialog box be centered on it.
			this->Options->Location = Point(
				(this->FormSaveLocation.X + (this->FormSaveSize.Width / 2)) - (this->Options->Width / 2),
				(this->FormSaveLocation.Y + (this->FormSaveSize.Height / 2)) - (this->Options->Height / 2)
				);
			// Basic check if the Options box's location will be outside of the monitor's bounds.
			if (this->Options->Location.X < 0 || this->Options->Location.Y < 0) 
			{
				this->Options->Location = Point(0,0);
			}
			if(this->Options->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			{
				return;
			}

			this->ClearAll();

			char cPath[512];

			VTFLib::CVTFFile *VTFFile = new VTFLib::CVTFFile();

			// Initialize image data.
			vlUInt uiWidth = 0, uiHeight = 0;
			bool bHasAlpha = false;

			vlByte **lpImageData = new vlByte *[sFileNames->Length];
			memset(lpImageData, 0, sizeof(vlByte *) * sFileNames->Length);

			// Load each frame/face.
			for(int i = 0; i < sFileNames->Length; i++)
			{
				CUtility::StringToCharPointer(static_cast<System::String ^>(sFileNames[i]), cPath, 512);

				// Load the image and convert it to RGBA.
				if(ilLoadImage(cPath))
				{
					if(ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
					{
						// Get the size of the image and make sure it matches the other images.
						if(i == 0)
						{
							uiWidth = (vlUInt)ilGetInteger(IL_IMAGE_WIDTH);
							uiHeight = (vlUInt)ilGetInteger(IL_IMAGE_HEIGHT);
						}
						else
						{
							if(uiWidth != (vlUInt)ilGetInteger(IL_IMAGE_WIDTH) || uiHeight != (vlUInt)ilGetInteger(IL_IMAGE_HEIGHT))
							{
								delete VTFFile;
								VTFFile = 0;

								if (bWarnings)
								{
									if (bNotificationSounds)
									{
										System::Media::SystemSounds::Asterisk->Play();
									}
									MessageBox::Show("Error loading image:\n\nAll frames and faces must be the same size.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
								}

								break;
							}
						}
						vlUInt val = uiWidth * uiHeight * 4;
						// Copy the image data.
						lpImageData[i] = new vlByte[val];
						memcpy(lpImageData[i], ilGetData(), val);
						
						// Only check for alpha when bHasAlpha is false. This is to allow for checking through multiple images for transparency
						// and to not unnecessarily check for alpha when it was already detected, which would be pointless.
						if ( !bHasAlpha ) {
							DWORD uiStride = (uiWidth + 3) / 4 * 4;
							System::Drawing::Bitmap^ vtfImage = gcnew System::Drawing::Bitmap(uiWidth, uiHeight, uiStride * 3,	System::Drawing::Imaging::PixelFormat::Format32bppArgb, (System::IntPtr)lpImageData[i]);

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
					}
					else
					{
						delete VTFFile;
						VTFFile = 0;

						if (bWarnings)
						{
							if (bNotificationSounds)
							{
								System::Media::SystemSounds::Asterisk->Play();
							}
							MessageBox::Show("Error converting image.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
						}
						break;
					}
				}
				else
				{
					delete VTFFile;
					VTFFile = 0;

					if (bWarnings)
					{
						if (bNotificationSounds)
						{
							System::Media::SystemSounds::Asterisk->Play();
						}
						MessageBox::Show("Error loading image.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}

					break;
				}
			}

			// Check that we loaded all images.
			if(VTFFile != 0)
			{
				vlUInt uiFrames = this->Options->TextureType == 0 ? sFileNames->Length : 1;
				vlUInt uiFaces = this->Options->TextureType == 1 ? sFileNames->Length : 1;
				vlUInt uiSlices = this->Options->TextureType == 2 ? sFileNames->Length : 1;

				SVTFCreateOptions VTFCreateOptions = CVTFFileUtility::GetCreateOptions(this->Options);

				VTFCreateOptions.ImageFormat = bHasAlpha ? Options->AlphaFormat : Options->NormalFormat;

				// Create the .vtf file.
				if(VTFFile->Create(uiWidth, uiHeight, uiFrames, uiFaces, uiSlices, lpImageData, VTFCreateOptions) != vlFalse && CVTFFileUtility::CreateResources(Options, VTFFile))
				{
					for (vlUInt i = 0; i < (vlUInt)this->Options->lstFlags->Items->Count; i++)
					{
						if (this->Options->lstFlags->GetItemChecked(i))
						{
							// The flags list only includes flags that can be changed by the user.
							switch (i)
							{
							case 0: VTFFile->SetFlag(TEXTUREFLAGS_POINTSAMPLE, true); break;
							case 1: VTFFile->SetFlag(TEXTUREFLAGS_TRILINEAR, true); break;
							case 2: VTFFile->SetFlag(TEXTUREFLAGS_CLAMPS, true); break;
							case 3: VTFFile->SetFlag(TEXTUREFLAGS_CLAMPT, true); break;
							case 4: VTFFile->SetFlag(TEXTUREFLAGS_ANISOTROPIC, true); break;
							case 5: VTFFile->SetFlag(TEXTUREFLAGS_HINT_DXT5, true); break;
							case 6: VTFFile->SetFlag(TEXTUREFLAGS_SRGB, true); break;
							case 7: VTFFile->SetFlag(TEXTUREFLAGS_NORMAL, true); break;
							case 8: VTFFile->SetFlag(TEXTUREFLAGS_NOMIP, true); break;
							case 9: VTFFile->SetFlag(TEXTUREFLAGS_NOLOD, true); break;
							case 10: VTFFile->SetFlag(TEXTUREFLAGS_MINMIP, true); break;
							case 11: VTFFile->SetFlag(TEXTUREFLAGS_PROCEDURAL, true); break;
							case 12: VTFFile->SetFlag(TEXTUREFLAGS_ENVMAP, true); break;
							case 13: VTFFile->SetFlag(TEXTUREFLAGS_RENDERTARGET, true); break;
							case 14: VTFFile->SetFlag(TEXTUREFLAGS_DEPTHRENDERTARGET, true); break;
							case 15: VTFFile->SetFlag(TEXTUREFLAGS_NODEBUGOVERRIDE, true); break;
							case 16: VTFFile->SetFlag(TEXTUREFLAGS_NODEPTHBUFFER, true); break;
							case 17: VTFFile->SetFlag(TEXTUREFLAGS_CLAMPU, true); break;
							case 18: VTFFile->SetFlag(TEXTUREFLAGS_VERTEXTEXTURE, true); break;
							case 19: VTFFile->SetFlag(TEXTUREFLAGS_SSBUMP, true); break;
							case 20: VTFFile->SetFlag(TEXTUREFLAGS_BORDER, true); break;
							default:
								break;
							}
						}
					}

					this->SetVTFFile(VTFFile);

					this->FileName = nullptr;

					this->btnSave->Enabled = true;
					this->toolStripSave->Enabled = true;
					this->toolStripClose->Enabled = true;
					this->btnClose->Enabled = true;
					this->btnSaveAs->Enabled = true;

					this->btnExport->Enabled = true;
					this->btnExportAll->Enabled = true;
					this->toolStripExport->Enabled = true;

					this->toolStripCopy->Enabled = true;
					this->btnCopy->Enabled = true;

					this->cboFileVersion->Enabled = true;
					this->numImageBumpmapScale->Enabled = true;

					this->pnlSidebar->Visible = true;
					this->pnlSidebar2->Visible = true;

					this->pnlMain->ContextMenu = this->mnuVTFFile;

				}
				else
				{
					delete VTFFile;

					if (bWarnings)
					{
						if (bNotificationSounds)
						{
							System::Media::SystemSounds::Asterisk->Play();
						}
						MessageBox::Show(System::String::Concat("Error creating VTF texture:\n\n", gcnew System::String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}

			// Delete all image data.
			for(int i = 0; i < sFileNames->Length; i++)
			{
				delete []lpImageData[i];
			}
			delete []lpImageData;
		}

		private: void Export(System::String ^sFileName)
		{
			if(this->VTFFile == 0)
				return;

			char cPath[512];
			CUtility::StringToCharPointer(sFileName, cPath, 512);

			//ILuint uiImage;

			//ilInit();

			//ilEnable(IL_ORIGIN_SET);
			//ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

			//ilGenImages(1, &uiImage);
			//ilBindImage(uiImage);

			vlUInt uiWidth, uiHeight, uiDepth;
			this->VTFFile->ComputeMipmapDimensions(this->VTFFile->GetWidth(), this->VTFFile->GetHeight(), this->VTFFile->GetDepth(), (vlUInt)this->numMipmap->Value, uiWidth,  uiHeight, uiDepth);

			vlByte *lpImageData = new vlByte[this->VTFFile->ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)];

			VTFFile->ConvertToRGBA8888(this->VTFFile->GetData((vlUInt)this->numFrame->Value, (vlUInt)this->numFace->Value, (vlUInt)this->numSlice->Value, (vlUInt)this->numMipmap->Value), lpImageData, uiWidth, uiHeight, this->VTFFile->GetFormat());

			// DevIL likes image data upside down...
			VTFFile->FlipImage(lpImageData, uiWidth, uiHeight);

			if(!(ilTexImage(uiWidth, uiHeight, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, lpImageData) && ilSaveImage(cPath)))
			{
				if (bWarnings)
				{
					if (bNotificationSounds)
					{
						System::Media::SystemSounds::Asterisk->Play();
					}
					MessageBox::Show("Error saving image.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}

			delete []lpImageData;

			//ilDeleteImages(1, &uiImage);
			//ilShutDown();
		}

		private: void ExportAll(System::String ^sFileName)
		{
			#pragma warning(disable : 4996)
			if(this->VTFFile == 0)
				return;

			char cPath[512];
			char cExt[512] = "";
			char *cInsert;

			CUtility::StringToCharPointer(sFileName, cPath, 512);
			cInsert = strrchr(cPath, '.');
			if(cInsert)
			{
				strcpy(cExt, cInsert);
			}
			else
			{
				cInsert = cPath + strlen(cPath);
			}

			//ILuint uiImage;

			//ilInit();

			//ilEnable(IL_ORIGIN_SET);
			//ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

			//ilGenImages(1, &uiImage);
			//ilBindImage(uiImage);

			vlUInt uiWidth, uiHeight, uiDepth;
			this->VTFFile->ComputeMipmapDimensions(this->VTFFile->GetWidth(), this->VTFFile->GetHeight(), this->VTFFile->GetDepth(), (vlUInt)this->numMipmap->Value, uiWidth,  uiHeight, uiDepth);

			vlByte *lpImageData = new vlByte[this->VTFFile->ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)];

			for(vlUInt i = 0; i < this->VTFFile->GetFrameCount(); i++)
			{
				for(vlUInt j = 0; j < this->VTFFile->GetFaceCount(); j++)
				{
					for(vlUInt k = 0; k < this->VTFFile->GetDepth(); k++)
					{
						VTFFile->ConvertToRGBA8888(this->VTFFile->GetData(i, j, k, (vlUInt)this->numMipmap->Value), lpImageData, uiWidth, uiHeight, this->VTFFile->GetFormat());

						// DevIL likes image data upside down...
						VTFFile->FlipImage(lpImageData, uiWidth, uiHeight);

						sprintf(cInsert, "_%.2u_%.2u_%.2u%s", i, j, k, cExt);
						if(!(ilTexImage(uiWidth, uiHeight, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, lpImageData) && ilSaveImage(cPath)))
						{
							if (bWarnings)
							{
								if (bNotificationSounds)
								{
									System::Media::SystemSounds::Asterisk->Play();
								}
								MessageBox::Show("Error saving image.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
							}
						}
					}
				}
			}

			delete []lpImageData;

			//ilDeleteImages(1, &uiImage);
			//ilShutDown();
		}

		//
		// Main menu.
		//

		private: System::Void btnNew_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if (this->CloseFile())
			{
				this->New();
			}
		}

		private: System::Void btnOpen_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if (this->CloseFile())
			{
				if (this->dlgOpenFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->Open(this->dlgOpenFile->FileName, false);
				}
			}
		}

		private: System::Void btnSave_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->FileName != nullptr)
				this->Save(this->FileName);
			else
				this->SaveAs();
		}

		private: System::Void btnSaveAs_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->SaveAs();
		}

		private: System::Void btnImport_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if (this->CloseFile())
			{
				if (this->dlgImportFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->Import(this->dlgImportFile->FileNames);
				}
			}
		}

		private: System::String ^RemoveExtension(System::String ^sFileName)
		{
			if(sFileName == nullptr)
			{
				return "";
			}

			System::String ^sTempFileName = sFileName;
			if(sTempFileName->LastIndexOf("\\") != -1)
			{
				sTempFileName = sTempFileName->Substring(sTempFileName->LastIndexOf("\\") + 1);
			}
			if(sTempFileName->LastIndexOf(".") != -1)
			{
				sTempFileName = sTempFileName->Substring(0, sTempFileName->LastIndexOf("."));
			}
			return sTempFileName;
		}

		private: System::Void btnExport_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->dlgExportFile->FileName = this->RemoveExtension(this->FileName);

			if(this->dlgExportFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->Export(this->dlgExportFile->FileName);
			}
		}

		private: System::Void btnExportAll_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->dlgExportFile->FileName = this->RemoveExtension(this->FileName);

			if(this->dlgExportFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->ExportAll(this->dlgExportFile->FileName);
			}
		}

		private: System::Void btnCreateVMTFile_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->VTFFile != 0 && this->FileName != nullptr && (this->FileName->Length >= 4 && System::String::Compare(this->FileName, this->FileName->Length - 4, ".vtf", 0, 4, true) == 0))
			{
				this->VMTCreate->Create(this->FileName, *this->VTFFile);
			}
			this->VMTCreate->ShowDialog();
		}

		private: System::Void btnConvertFolder_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->BatchConvert->ShowDialog();
		}

		//private: System::Void btnConvertWADFile_Click(System::Object ^  sender, System::EventArgs ^  e)
		//{
		//	//this->WADConvert->ShowDialog();
		//}

		private: System::Void btnRecentFile_Click(System::Object ^sender, System::EventArgs ^e)
		{
			if (this->CloseFile())
			{
				this->Open(static_cast<System::String^>(this->RecentFiles[static_cast<MenuItem^>(sender)->Index]), false);
			}
		}

		private: System::Void btnExit_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			__super::Close();
		}

		private: System::Void btnCopy_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				if(this->picVTFFileTL->Image != nullptr)
				{
					System::Windows::Forms::Clipboard::SetDataObject(this->picVTFFileTL->Image, true);
				}
			}
			else
			{
				if (bWarnings)
				{
					if (bNotificationSounds)
					{
						System::Media::SystemSounds::Asterisk->Play();
					}
					MessageBox::Show("Operation not supported.\n\nVTFEdit has determined that the current thread apartment state does not\nsupport this operation. This is a .NET design flaw.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		private: System::Void btnPaste_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				System::Windows::Forms::IDataObject ^Data = System::Windows::Forms::Clipboard::GetDataObject();

				if(!Data->GetDataPresent(System::Windows::Forms::DataFormats::Bitmap))
				{
					return;
				}

				System::Drawing::Bitmap ^Bitmap = static_cast<System::Drawing::Bitmap ^>(Data->GetData(System::Windows::Forms::DataFormats::Bitmap));

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
				if(this->Options->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				{
					return;
				}

				this->ClearAll();

				VTFLib::CVTFFile *VTFFile = new VTFLib::CVTFFile();

				// Initialize image data.
				vlUInt uiWidth = (vlUInt)Bitmap->Width, uiHeight = (vlUInt)Bitmap->Height;

				vlByte *lpImageData = new vlByte[uiWidth * uiHeight * 4];
				vlByte *lpPointer = lpImageData;

				for(int j = 0; j < Bitmap->Height; j++)
				{
					for(int i = 0; i < Bitmap->Width; i++)
					{
						System::Drawing::Color Pixel = Bitmap->GetPixel(i, j);

						*(lpPointer++) = (vlByte)Pixel.R;
						*(lpPointer++) = (vlByte)Pixel.G;
						*(lpPointer++) = (vlByte)Pixel.B;
						*(lpPointer++) = (vlByte)Pixel.A;
					}
				}

				SVTFCreateOptions VTFCreateOptions = CVTFFileUtility::GetCreateOptions(this->Options);

				// Create the .vtf file.
				if(VTFFile->Create(uiWidth, uiHeight, lpImageData, VTFCreateOptions) != vlFalse && CVTFFileUtility::CreateResources(Options, VTFFile))
				{
					this->SetVTFFile(VTFFile);

					this->btnSave->Enabled = true;
					this->toolStripSave->Enabled = true;
					this->toolStripClose->Enabled = true;
					this->btnClose->Enabled = true;
					this->btnSaveAs->Enabled = true;

					this->btnExport->Enabled = true;
					this->btnExportAll->Enabled = true;
					this->toolStripExport->Enabled = true;

					this->toolStripCopy->Enabled = true;
					this->btnCopy->Enabled = true;
				}
				else
				{
					delete VTFFile;

					if (bWarnings)
					{
						if (bNotificationSounds)
						{
							System::Media::SystemSounds::Asterisk->Play();
						}
						MessageBox::Show(System::String::Concat("Error creating VTF texture:\n\n", gcnew System::String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}

				delete []lpImageData;
			}
			else
			{
				if (bWarnings)
				{
					if (bNotificationSounds)
					{
						System::Media::SystemSounds::Asterisk->Play();
					}
					MessageBox::Show("Operation not supported.\n\nVTFEdit has determined that the current thread apartment state does not\nsupport this operation. This is a .NET design flaw.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		private: System::Void btnChannel_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnChannelRGB->Checked = true;
			this->toolStripRGB->Checked = true;

			this->btnChannelR->Checked = false;
			this->btnChannelG->Checked = false;
			this->btnChannelB->Checked = false;
			this->btnChannelA->Checked = false;
			this->toolStripR->Checked = false;
			this->toolStripG->Checked = false;
			this->toolStripB->Checked = false;
			this->toolStripA->Checked = false;

			this->UpdateVTFFile();
		}

		private: System::Void btnMask_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnMask->Checked = !this->btnMask->Checked;
			this->toolStripMask->Checked = !this->toolStripMask->Checked;

			this->UpdateVTFFile();
		}

		private: System::Void btnTile_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnTile->Checked = !this->btnTile->Checked;
			this->toolStripTile->Checked = !this->toolStripTile->Checked;

			this->UpdateVTFFile();
			this->UpdateVTFView();
		}

		private: System::Void btnAutoCreateVMTFile_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnAutoCreateVMTFile->Checked = !this->btnAutoCreateVMTFile->Checked;
		}

		private: System::Void btnAbout_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->About->ShowDialog();
		}

		private: System::Void numVTFFile_ValueChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->trkFrame->Value = Convert::ToInt32(this->numFrame->Value);
			if(!this->bHDRReseting)
			{
				this->UpdateVTFFile();
				this->UpdateVTFView();
			}
		}

		//
		// Animation.
		//

		private: System::Void btnAnimate_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->tmrAnimate->Enabled)
			{
				this->tmrAnimate->Enabled = false;
				this->btnAnimate->Text = "&Play";
			}
			else
			{
				this->tmrAnimate->Enabled = true;
				this->btnAnimate->Text = "&Stop";
			}
		}

		private: System::Void tmrAnimate_Tick(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(System::Windows::Forms::Form::ActiveForm != this)
				return;

			int iValue = (int)this->numFrame->Value + 1;

			if(iValue > this->numFrame->Maximum)
				iValue = (int)this->numFrame->Minimum;

			this->numFrame->Value = iValue;
			this->trkFrame->Value = iValue;
		}

		private: System::Void lstFlags_ItemCheck(System::Object ^  sender, System::Windows::Forms::ItemCheckEventArgs ^  e)
		{
			if(this->VTFFile == 0)
				return;

			// Flags you shouldn't be allowed to change as they're set when created.
			if( e->Index == 12 || 
				e->Index == 13 || 
				e->Index == 19 || 
				e->Index == 20 || 
				e->Index == 21 || 
				e->Index == 22 || 
				e->Index == 24 || 
				e->Index == 28)
			{
				e->NewValue = e->CurrentValue;
			}
		}

		//
		// HDR context.
		//

		private: System::Void btnHDRReset_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->bHDRReseting = true;

			this->trkHDRExposure->LargeChange = 1;
			this->trkHDRExposure->Minimum = 0;
			this->trkHDRExposure->Maximum = 8000;
			this->trkHDRExposure->Value = 2000;
			this->trkHDRExposure->TickFrequency = 160;

			this->bHDRReseting = false;

			this->UpdateVTFFile();
		}

		//
		// VTF context.
		//

		private: System::Void picVTFFile_MouseMove(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e)
		{
			int iX = (int)((float)e->X / this->fImageScale) + 1;
			int iY = (int)((float)e->Y / this->fImageScale) + 1;

			this->pnlInfo2->Text = System::String::Concat(iX.ToString(), ", ", iY.ToString());
		}

		private: System::Void btnVTFFileZoomIn_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if (this->VTFFile == 0 || this->picVTFFileTL->Width >= 4096 || this->picVTFFileTL->Height >= 4096)
				return;

			this->fImageScale *= 2.0f;
			this->UpdateVTFFile();
			this->UpdateVTFView();
		}

		private: System::Void btnVTFFileZoomOut_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->VTFFile == 0 || this->picVTFFileTL->Width <= 4 || this->picVTFFileTL->Height <= 4)
				return;

			this->fImageScale *= 0.5f;
			this->UpdateVTFFile();
			this->UpdateVTFView();
		}

		private: System::Void btnVTFFileZoomReset_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->VTFFile == 0)
				return;

			this->fImageScale = 1.0f;
			this->UpdateVTFFile();
			this->UpdateVTFView();
		}

		private: System::Void btnVTFFileCopy_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->VTFFile == 0)
				return;

			this->toolStripCopy_Click(this->toolStripCopy, System::EventArgs::Empty);
		}

		//
		// VMT context.
		//

		private: System::Void EnableVMTContextMenuItems()
		{
			this->btnVMTFileUndo->Enabled = this->txtVMTFile->CanUndo;
			this->btnVMTFileCut->Enabled = this->txtVMTFile->SelectedText->Length > 0;
			this->btnVMTFileCopy->Enabled = this->txtVMTFile->SelectedText->Length > 0;
			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				this->btnVMTFilePaste->Enabled = false;
				array<System::String ^>^Formats = System::Windows::Forms::Clipboard::GetDataObject()->GetFormats();
				for(int i = 0; i < Formats->Length; i++)
				{
					if(System::Windows::Forms::DataFormats::GetFormat(Formats[i])->Name->Equals("Text"))
					{
						this->btnVMTFilePaste->Enabled = true;
						break;
					}
				}
			}
			else
			{
				this->btnVMTFilePaste->Enabled = true;
			}
			this->btnVMTFileDelete->Enabled = this->txtVMTFile->SelectedText->Length > 0;
			this->btnVMTFileSelectAll->Enabled = this->txtVMTFile->Text->Length > 0;

			int line, column;

			line = this->txtVMTFile->GetLineFromCharIndex(this->txtVMTFile->SelectionStart);
			column = (int)::SendMessage((HWND)this->txtVMTFile->Handle.ToPointer(), EM_LINEINDEX, line, 0);
			column = this->txtVMTFile->SelectionStart - column;

			this->pnlInfo2->Text = System::String::Concat("Ln ", (line + 1).ToString(), ", Col ", (column + 1).ToString());
		}

		private: System::Void btnVMTFileUndo_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->Undo();
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFileCut_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->Cut();
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFileCopy_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->Copy();
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFilePaste_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->Paste(System::Windows::Forms::DataFormats::GetFormat(System::Windows::Forms::DataFormats::Text));
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFileDelete_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->SelectedText = "";
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFileSelectAll_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->SelectAll();
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFileValidateLoose_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			char *cText = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->txtVMTFile->Text).ToPointer();
			if(VMTFile->Load( cText, this->txtVMTFile->Text->Length))
			{
				MessageBox::Show("VMT validation successful.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else
			{
				if (bWarnings)
				{
					if (bNotificationSounds)
					{
						System::Media::SystemSounds::Asterisk->Play();
					}
					MessageBox::Show(System::String::Concat("Error validating VMT:\n\n", gcnew System::String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cText);
		}

		private: System::Void btnVMTFileValidateStrict_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			vlSetInteger(VTFLIB_VMT_PARSE_MODE, PARSE_MODE_STRICT);
			this->btnVMTFileValidateLoose_Click(sender, e);
			vlSetInteger(VTFLIB_VMT_PARSE_MODE, PARSE_MODE_LOOSE);
		}

		private: System::Void txtVMTFile_SelectionChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->EnableVMTContextMenuItems();
		}

		private: System::Void txtVMTFile_TextChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->EnableVMTContextMenuItems();

			//this->txtVMTFile->SelectionChanged -= gcnew System::EventHandler(this, &CVTFEdit::txtVMTFile_SelectionChanged); // Disabled for performance reasons.
			//this->SyntaxHilighter->Process(); // Disabled for performance reasons.
			//this->txtVMTFile->SelectionChanged += gcnew System::EventHandler(this, &CVTFEdit::txtVMTFile_SelectionChanged); // Disabled for performance reasons.
		}

		//
		// Helper functions.
		//

		private: System::String ^GetImageFormatString(VTFImageFormat ImageFormat)
		{
			SVTFImageFormatInfo ImageFormatInfo;
			if(vlImageGetImageFormatInfoEx(ImageFormat, &ImageFormatInfo))
			{
				return gcnew System::String(ImageFormatInfo.lpName);
			}
			return "";
		}

		//
		// Recent menu.
		//

		private: void AddRecentFile(System::String ^sFileName)
		{
			for(int i = 0; i < this->RecentFiles->Count; i++)
			{
				if(System::String::Compare(static_cast<System::String ^>(this->RecentFiles[i]), sFileName, true) == 0)
				{
					if(i == 0)
					{
						return;
					}
					else
					{
						this->RecentFiles->RemoveAt(i);
						this->RecentFiles->Insert(0, sFileName);

						this->UpdateRecentFiles();

						return;
					}
				}
			}

			this->RecentFiles->Insert(0, sFileName);

			while(this->RecentFiles->Count > (int)this->uiMaximumRecentFiles)
			{
				this->RecentFiles->RemoveAt(this->RecentFiles->Count - 1);
			}

			this->UpdateRecentFiles();
		}

		private: void UpdateRecentFiles()
		{
			this->btnRecentFiles->MenuItems->Clear();

			for(int i = 0; i < this->RecentFiles->Count; i++)
			{
				MenuItem ^RecentFile = gcnew MenuItem(static_cast<System::String ^>(this->RecentFiles[i]));
				RecentFile->Click += gcnew EventHandler(this, &CVTFEdit::btnRecentFile_Click);
				this->btnRecentFiles->MenuItems->Add(RecentFile);
			}

			this->btnRecentFiles->Visible = RecentFiles->Count != 0;
			this->btnFileSpace4->Visible = RecentFiles->Count != 0;
		}

		//
		// Configuration
		//

		private: bool WriteConfigFile(System::String ^sConfigFile)
		{
			System::IO::StreamWriter ^ConfigFile;

			try
			{
				ConfigFile = gcnew System::IO::StreamWriter(sConfigFile, false, System::Text::Encoding::ASCII);
			}
			catch(Exception ^)
			{
				return false;
			}

			//try
			//{
				ConfigFile->WriteLine("[VTFEdit]");
				ConfigFile->WriteLine("");

				ConfigFile->WriteLine(System::String::Concat("VTFEdit.AnimationFrameInterval = ", this->tmrAnimate->Interval.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFEdit.Mask = ", this->btnMask->Checked.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFEdit.Tile = ", this->btnTile->Checked.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFEdit.AutoCreateVMTFile = ", this->btnAutoCreateVMTFile->Checked.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFEdit.ExtractDirectory = ", this->dlgExtractDirectoryItem->SelectedPath));

				ConfigFile->WriteLine("");
				ConfigFile->WriteLine("[Forms]");
				ConfigFile->WriteLine("");

				ConfigFile->WriteLine(System::String::Concat("Forms.VTFEdit.Location.X = ", this->FormSaveLocation.X.ToString()));
				ConfigFile->WriteLine(System::String::Concat("Forms.VTFEdit.Location.Y = ", this->FormSaveLocation.Y.ToString()));
				ConfigFile->WriteLine(System::String::Concat("Forms.VTFEdit.Size.Width = ", this->FormSaveSize.Width.ToString()));
				ConfigFile->WriteLine(System::String::Concat("Forms.VTFEdit.Size.Height = ", this->FormSaveSize.Height.ToString()));
				if(this->FormSaveWindowState == FormWindowState::Maximized)
				{
					ConfigFile->WriteLine("Forms.VTFEdit.WindowState = Maximized");
				}
				else
				{
					ConfigFile->WriteLine("Forms.VTFEdit.WindowState = Normal");
				}
				ConfigFile->WriteLine(System::String::Concat("Forms.VTFEdit.Sidebar.SplitPosition = ", this->iFormSaveSidebarSplitPosition.ToString()));
				ConfigFile->WriteLine(System::String::Concat("Forms.VTFEdit.VMTTextZoom = ", this->iFormSaveVMTTextZoom.ToString()));
				ConfigFile->WriteLine(System::String::Concat("Forms.VTFEdit.CustomAlphaBackground = ", this->bCustomAlphaBackground));
				ConfigFile->WriteLine(System::String::Concat("Forms.VTFEdit.AlphaBackgroundColor = ", this->fAlphaBackgroundColor.ToArgb()));

				ConfigFile->WriteLine(System::String::Concat("Forms.BatchConvert.InputFolder = ", this->BatchConvert->InputFolder));
				ConfigFile->WriteLine(System::String::Concat("Forms.BatchConvert.OutputFolder = ", this->BatchConvert->OutputFolder));
				ConfigFile->WriteLine(System::String::Concat("Forms.BatchConvert.ToVTF = ", this->BatchConvert->ToVTF.ToString()));
				ConfigFile->WriteLine(System::String::Concat("Forms.BatchConvert.ToVTFFilter = ", this->BatchConvert->ToVTFFilter));
				ConfigFile->WriteLine(System::String::Concat("Forms.BatchConvert.FromVTFFormat = ", this->BatchConvert->FromVTFFormat));
				ConfigFile->WriteLine(System::String::Concat("Forms.BatchConvert.FromVTFFilter = ", this->BatchConvert->FromVTFFilter));
				ConfigFile->WriteLine(System::String::Concat("Forms.BatchConvert.Recurse = ", this->BatchConvert->Recurse.ToString()));
				ConfigFile->WriteLine(System::String::Concat("Forms.BatchConvert.CreateVMTFiles = ", this->BatchConvert->CreateVMTFiles.ToString()));

				//ConfigFile->WriteLine(System::String::Concat("Forms.WADConvert.WADFile = ", this->WADConvert->WADFile));
				//ConfigFile->WriteLine(System::String::Concat("Forms.WADConvert.OutputFolder = ", this->WADConvert->OutputFolder));
				//ConfigFile->WriteLine(System::String::Concat("Forms.WADConvert.CreateVMTFiles = ", this->WADConvert->CreateVMTFiles.ToString()));

				ConfigFile->WriteLine("");
				ConfigFile->WriteLine("[VTF Options]");
				ConfigFile->WriteLine("");

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.NormalFormat = ", Convert::ToInt32(this->Options->NormalFormat).ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.AlphaFormat = ", Convert::ToInt32(this->Options->AlphaFormat).ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.TextureType = ", this->Options->TextureType.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.sRGB = ", this->Options->sRGB.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.VMTShader = ", this->VMTCreate->cboShader->Text));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.Resize = ", this->Options->ResizeImage.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.ResizeMethod = ", Convert::ToInt32(this->Options->ResizeMethod).ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.ResizeFilter = ", Convert::ToInt32(this->Options->ResizeFilter).ToString()));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.ResizeClamp = ", this->Options->ResizeClamp.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.ResizeClampWidth = ", this->Options->ResizeClampWidth.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.ResizeClampHeight = ", this->Options->ResizeClampHeight.ToString()));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.GenerateMipmaps = ", this->Options->GenerateMipmaps.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.MipmapFilter = ", Convert::ToInt32(this->Options->MipmapFilter).ToString()));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.Version = ", this->Options->Version));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.Warnings = ", this->bWarnings));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.NotificationSounds = ", this->bNotificationSounds));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.ComputeReflectivity = ", this->Options->ComputeReflectivity.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.GenerateThumbnail = ", this->Options->GenerateThumbnail.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.GenerateSphereMap = ", this->Options->GenerateSphereMap.ToString()));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.CorrectGamma = ", this->Options->CorrectGamma.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.GammaCorrection = ", this->Options->GammaCorrection.ToString()));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.LuminanceWeightR = ", this->Options->LuminanceWeightR.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.LuminanceWeightG = ", this->Options->LuminanceWeightG.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.LuminanceWeightB = ", this->Options->LuminanceWeightB.ToString()));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.AlphaThreshold = ", this->Options->AlphaThreshold.ToString()));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.CreateLODControlResource = ", this->Options->CreateLODControlResource.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.LODControlClampU = ", this->Options->LODControlClampU.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.LODControlClampV = ", this->Options->LODControlClampV.ToString()));

				ConfigFile->WriteLine(System::String::Concat("VTFOptions.CreateInformationResource = ", this->Options->CreateInformationResource.ToString()));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.InformationAuthor = ", this->Options->InformationAuthor));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.InformationContact = ", this->Options->InformationContact));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.InformationVersion = ", this->Options->InformationVersion));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.InformationModification = ", this->Options->InformationModification));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.InformationDescription = ", this->Options->InformationDescription));
				ConfigFile->WriteLine(System::String::Concat("VTFOptions.InformationComments = ", this->Options->InformationComments));

				ConfigFile->WriteLine("");
				ConfigFile->WriteLine("[Recent Files]");
				ConfigFile->WriteLine("");

				ConfigFile->WriteLine(System::String::Concat("RecentFiles.Maximum = ", this->uiMaximumRecentFiles.ToString()));

				for(int i = this->RecentFiles->Count - 1; i >= 0; i--)
				{
					ConfigFile->WriteLine(System::String::Concat("RecentFiles.File = ", static_cast<System::String ^>(this->RecentFiles[i])));
				}
			//}
			//catch(Exception ^)
			//{
				//ConfigFile->Close();
				//return false;
			//}

			ConfigFile->Close();

			return true;
		}

		private: bool ReadConfigFile(System::String ^sConfigFile)
		{
			System::IO::StreamReader ^ConfigFile;

			try
			{
				ConfigFile = gcnew System::IO::StreamReader(sConfigFile, System::Text::Encoding::ASCII);
			}
			catch(Exception ^)
			{
				return false;
			}

			try
			{
				System::String ^sLine, ^sArg, ^sVal;

				while((sLine = ConfigFile->ReadLine()) != nullptr)
				{
					int iIndex = sLine->IndexOf("=");

					if(iIndex == -1)
						continue;

					sArg = sLine->Substring(0, iIndex)->Trim();
					sVal = sLine->Substring(iIndex + 1)->Trim();

					try
					{
						if(System::String::Compare(sArg, "VTFEdit.AnimationFrameInterval", true) == 0)
						{
							this->numFrameRate->Value = Convert::ToInt32(sVal);
							this->tmrAnimate->Interval = Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "VTFEdit.Mask", true) == 0)
						{
							this->btnMask->Checked = Convert::ToBoolean(sVal);
							this->toolStripMask->Checked = Convert::ToBoolean(sVal);
						}
						else if(System::String::Compare(sArg, "VTFEdit.Tile", true) == 0)
						{
							this->btnTile->Checked = Convert::ToBoolean(sVal);
							this->toolStripTile->Checked = Convert::ToBoolean(sVal);
						}
						else if(System::String::Compare(sArg, "VTFEdit.AutoCreateVMTFile", true) == 0)
						{
							this->btnAutoCreateVMTFile->Checked = Convert::ToBoolean(sVal);
						}
						else if(System::String::Compare(sArg, "VTFEdit.ExtractDirectory", true) == 0)
						{
							this->dlgExtractDirectoryItem->SelectedPath = sVal;;
						}

						else if(System::String::Compare(sArg, "Forms.VTFEdit.Location.X", true) == 0)
						{
							this->FormSaveLocation.X = Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "Forms.VTFEdit.Location.Y", true) == 0)
						{
							this->FormSaveLocation.Y = Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "Forms.VTFEdit.Size.Width", true) == 0)
						{
							this->FormSaveSize.Width = Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "Forms.VTFEdit.Size.Height", true) == 0)
						{
							this->FormSaveSize.Height = Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "Forms.VTFEdit.WindowState", true) == 0)
						{
							if(System::String::Compare(sVal, "Normal", true) == 0)
							{
								this->FormSaveWindowState = FormWindowState::Normal;
							}
							else if(System::String::Compare(sVal, "Maximized", true) == 0)
							{
								this->FormSaveWindowState = FormWindowState::Maximized;
							}
						}
						else if(System::String::Compare(sArg, "Forms.VTFEdit.Sidebar.SplitPosition", true) == 0)
						{
							this->iFormSaveSidebarSplitPosition = Convert::ToInt32(sVal);
						}
						else if (System::String::Compare(sArg, "Forms.VTFEdit.Sidebar2.SplitPosition", true) == 0)
						{
							this->iFormSaveSidebar2SplitPosition = Convert::ToInt32(sVal);
						}
						else if (System::String::Compare(sArg, "Forms.VTFEdit.VMTTextZoom", true) == 0)
						{
							this->iFormSaveVMTTextZoom = Convert::ToDouble(sVal);
						}
						else if (System::String::Compare(sArg, "Forms.VTFEdit.CustomAlphaBackground", true) == 0)
						{
							this->bCustomAlphaBackground = Convert::ToBoolean(sVal);
							this->btnCustomAlphaToggle->Checked = this->bCustomAlphaBackground;
						}
						else if (System::String::Compare(sArg, "Forms.VTFEdit.AlphaBackgroundColor", true) == 0)
						{
							this->fAlphaBackgroundColor = System::Drawing::Color::FromArgb(Convert::ToInt32(sVal));
						}

						else if(System::String::Compare(sArg, "Forms.BatchConvert.InputFolder", true) == 0)
						{
							this->BatchConvert->InputFolder = sVal;
						}
						else if(System::String::Compare(sArg, "Forms.BatchConvert.OutputFolder", true) == 0)
						{
							this->BatchConvert->OutputFolder = sVal;
						}
						else if(System::String::Compare(sArg, "Forms.BatchConvert.ToVTF", true) == 0)
						{
							this->BatchConvert->ToVTF = Convert::ToBoolean(sVal);
						}
						else if(System::String::Compare(sArg, "Forms.BatchConvert.ToVTFFilter", true) == 0)
						{
							this->BatchConvert->ToVTFFilter = sVal;
						}
						else if(System::String::Compare(sArg, "Forms.BatchConvert.FromVTFFormat", true) == 0)
						{
							this->BatchConvert->FromVTFFormat = sVal;
						}
						else if(System::String::Compare(sArg, "Forms.BatchConvert.FromVTFFilter", true) == 0)
						{
							this->BatchConvert->FromVTFFilter = sVal;
						}
						else if(System::String::Compare(sArg, "Forms.BatchConvert.Recurse", true) == 0)
						{
							this->BatchConvert->Recurse = Convert::ToBoolean(sVal);
						}
						else if(System::String::Compare(sArg, "Forms.BatchConvert.CreateVMTFiles", true) == 0)
						{
							this->BatchConvert->CreateVMTFiles = Convert::ToBoolean(sVal);
						}

						//else if(System::String::Compare(sArg, "Forms.WADConvert.WADFile", true) == 0)
						//{
						//	this->WADConvert->WADFile = sVal;
						//}
						//else if(System::String::Compare(sArg, "Forms.WADConvert.OutputFolder", true) == 0)
						//{
						//	this->WADConvert->OutputFolder = sVal;
						//}
						//else if(System::String::Compare(sArg, "Forms.WADConvert.CreateVMTFiles", true) == 0)
						//{
						//	this->WADConvert->CreateVMTFiles = Convert::ToBoolean(sVal);
						//}

						else if(System::String::Compare(sArg, "VTFOptions.NormalFormat", true) == 0)
						{
							this->Options->NormalFormat = (VTFImageFormat)Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.AlphaFormat", true) == 0)
						{
							this->Options->AlphaFormat = (VTFImageFormat)Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.TextureType", true) == 0)
						{
							this->Options->TextureType = Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.sRGB", true) == 0)
						{
							this->Options->sRGB = Convert::ToByte(sVal);
						}
						else if (System::String::Compare(sArg, "VTFOptions.VMTShader", true) == 0)
						{
							this->VMTCreate->cboShader->Text = sVal;
							this->FormVMTShader = sVal;
						}

						else if(System::String::Compare(sArg, "VTFOptions.Resize", true) == 0)
						{
							this->Options->ResizeImage = Convert::ToByte(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.ResizeMethod", true) == 0)
						{
							this->Options->ResizeMethod = (VTFResizeMethod)Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.ResizeFilter", true) == 0)
						{
							this->Options->ResizeFilter = (VTFMipmapFilter)Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.ResizeClamp", true) == 0)
						{
							this->Options->ResizeClamp = Convert::ToByte(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.ResizeClampWidth", true) == 0)
						{
							this->Options->ResizeClampWidth = Convert::ToInt32(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.ResizeClampHeight", true) == 0)
						{
							this->Options->ResizeClampHeight = Convert::ToInt32(sVal);
						}

						else if(System::String::Compare(sArg, "VTFOptions.GenerateMipmaps", true) == 0)
						{
							this->Options->GenerateMipmaps = Convert::ToByte(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.MipmapFilter", true) == 0)
						{
							this->Options->MipmapFilter = (VTFMipmapFilter)Convert::ToInt32(sVal);
						}

						else if(System::String::Compare(sArg, "VTFOptions.Version", true) == 0)
						{
							this->Options->Version = sVal;
						}

						else if (System::String::Compare(sArg, "VTFOptions.Warnings", true) == 0)
						{
							this->bWarnings = Convert::ToBoolean(sVal);
							this->btnWarnings->Checked = this->bWarnings;
						}
						else if (System::String::Compare(sArg, "VTFOptions.NotificationSounds", true) == 0)
						{
							this->bNotificationSounds = Convert::ToBoolean(sVal);
							this->btnNotifSounds->Checked = this->bNotificationSounds;
						}

						else if(System::String::Compare(sArg, "VTFOptions.ComputeReflectivity", true) == 0)
						{
							this->Options->ComputeReflectivity = Convert::ToByte(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.GenerateThumbnail", true) == 0)
						{
							this->Options->GenerateThumbnail = Convert::ToByte(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.GenerateSphereMap", true) == 0)
						{
							this->Options->GenerateSphereMap = Convert::ToByte(sVal);
						}

						else if(System::String::Compare(sArg, "VTFOptions.CorrectGamma", true) == 0)
						{
							this->Options->CorrectGamma = Convert::ToByte(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.GammaCorrection", true) == 0)
						{
							this->Options->GammaCorrection = Convert::ToSingle(sVal);
						}

						else if(System::String::Compare(sArg, "VTFOptions.LuminanceWeightR", true) == 0)
						{
							this->Options->LuminanceWeightR = Convert::ToSingle(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.LuminanceWeightG", true) == 0)
						{
							this->Options->LuminanceWeightG = Convert::ToSingle(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.LuminanceWeightB", true) == 0)
						{
							this->Options->LuminanceWeightB = Convert::ToSingle(sVal);
						}

						else if(System::String::Compare(sArg, "VTFOptions.AlphaThreshold", true) == 0)
						{
							this->Options->AlphaThreshold = Convert::ToInt16(sVal);
						}

						else if(System::String::Compare(sArg, "VTFOptions.CreateLODControlResource", true) == 0)
						{
							this->Options->CreateLODControlResource = Convert::ToByte(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.LODControlClampU", true) == 0)
						{
							this->Options->LODControlClampU = Convert::ToByte(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.LODControlClampV", true) == 0)
						{
							this->Options->LODControlClampV = Convert::ToByte(sVal);
						}

						else if(System::String::Compare(sArg, "VTFOptions.CreateInformationResource", true) == 0)
						{
							this->Options->CreateInformationResource = Convert::ToByte(sVal);
						}
						else if(System::String::Compare(sArg, "VTFOptions.InformationAuthor", true) == 0)
						{
							this->Options->InformationAuthor = sVal;
						}
						else if(System::String::Compare(sArg, "VTFOptions.InformationContact", true) == 0)
						{
							this->Options->InformationContact = sVal;
						}
						else if(System::String::Compare(sArg, "VTFOptions.InformationVersion", true) == 0)
						{
							this->Options->InformationVersion = sVal;
						}
						else if(System::String::Compare(sArg, "VTFOptions.InformationModification", true) == 0)
						{
							this->Options->InformationModification = sVal;
						}
						else if(System::String::Compare(sArg, "VTFOptions.InformationDescription", true) == 0)
						{
							this->Options->InformationDescription = sVal;
						}
						else if(System::String::Compare(sArg, "VTFOptions.InformationComments", true) == 0)
						{
							this->Options->InformationComments = sVal;
						}

						else if(System::String::Compare(sArg, "RecentFiles.Maximum", true) == 0)
						{
							this->uiMaximumRecentFiles = Convert::ToUInt32(sVal);

							if(this->uiMaximumRecentFiles > 32)
							{
								this->uiMaximumRecentFiles = 32;
							}
						}
						else if(System::String::Compare(sArg, "RecentFiles.File", true) == 0 && System::IO::File::Exists(sVal))
						{
							this->AddRecentFile(sVal);
						}
					}
					catch(Exception ^)
					{
						continue;
					}
				}
			}
			catch(Exception ^)
			{
				ConfigFile->Close();
				return false;
			}

			ConfigFile->Close();

			return true;
		}

		private: System::Void Control_DragDrop(System::Object ^  sender, System::Windows::Forms::DragEventArgs ^  e)
		{
			if (!this->CloseFile())
				return;
			array< System::String^>^ lpFiles = static_cast<array< System::String^>^>(e->Data->GetData(System::Windows::Forms::DataFormats::FileDrop));
			if(lpFiles->Length > 0)
			{
				if (lpFiles[0]->ToLower()->EndsWith(".bmp") ||
					lpFiles[0]->ToLower()->EndsWith(".dds") ||
					lpFiles[0]->ToLower()->EndsWith(".gif") ||
					lpFiles[0]->ToLower()->EndsWith(".jpg") ||
					lpFiles[0]->ToLower()->EndsWith(".jpeg") ||
					lpFiles[0]->ToLower()->EndsWith(".png") ||
					lpFiles[0]->ToLower()->EndsWith(".tga"))
				{
					this->Import(lpFiles);
				}
				else
				{
					this->Open(lpFiles[0], false);
				}
			}
		}

		private: System::Void Control_DragEnter(System::Object ^  sender, System::Windows::Forms::DragEventArgs ^  e)
		{
			if(e->Data->GetDataPresent(System::Windows::Forms::DataFormats::FileDrop, false))
			{
				array< System::String^>^ lpFiles = static_cast<array< System::String^>^>(e->Data->GetData(System::Windows::Forms::DataFormats::FileDrop));
				if(lpFiles->Length > 0)
				{
					if(!System::IO::Directory::Exists(lpFiles[0]))
					{
						 if(lpFiles[0]->ToLower()->EndsWith(".vmt")   ||
							lpFiles[0]->ToLower()->EndsWith(".vtf")   || 
							lpFiles[0]->ToLower()->EndsWith(".bmp")   ||
							lpFiles[0]->ToLower()->EndsWith(".dds")   ||
							lpFiles[0]->ToLower()->EndsWith(".gif")   ||
							lpFiles[0]->ToLower()->EndsWith(".jpg")   ||
							lpFiles[0]->ToLower()->EndsWith(".jpeg")  ||
							lpFiles[0]->ToLower()->EndsWith(".png")   ||
							lpFiles[0]->ToLower()->EndsWith(".tga")   )
						 {
							e->Effect = System::Windows::Forms::DragDropEffects::All;
						 }
						 else {
							e->Effect = System::Windows::Forms::DragDropEffects::None;
						 }
					}
				}
			}
		}

		private: System::Void toolStripRGB_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			// Yes I know these are long, but there isn't a nice way to do this without a radio button system in the tool strip. No I'm not going to use the drop down button just to have the radio button functionality. I want all buttons visible at once.
			if (this->toolStripRGB->Checked) 
			{
				this->btnChannelRGB->Checked = true;
				this->btnChannelR->Checked = false;
				this->btnChannelG->Checked = false;
				this->btnChannelB->Checked = false;
				this->btnChannelA->Checked = false;

				this->toolStripRGB->Checked = true;
				this->toolStripR->Checked = false;
				this->toolStripG->Checked = false;
				this->toolStripB->Checked = false;
				this->toolStripA->Checked = false;
			}
			else
			{
				this->toolStripRGB->Checked = true;
			}
			this->UpdateVTFFile();
		}

		private: System::Void toolStripR_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (this->toolStripR->Checked) 
			{
				this->btnChannelRGB->Checked = false;
				this->btnChannelR->Checked = true;
				this->btnChannelG->Checked = false;
				this->btnChannelB->Checked = false;
				this->btnChannelA->Checked = false;

				this->toolStripRGB->Checked = false;
				this->toolStripG->Checked = false;
				this->toolStripB->Checked = false;
				this->toolStripA->Checked = false;
			}
			else
			{
				this->toolStripR->Checked = true;
			}
			this->UpdateVTFFile();
		}

		private: System::Void toolStripG_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (this->toolStripG->Checked) 
			{
				this->btnChannelRGB->Checked = false;
				this->btnChannelR->Checked = false;
				this->btnChannelG->Checked = true;
				this->btnChannelB->Checked = false;
				this->btnChannelA->Checked = false;

				this->toolStripRGB->Checked = false;
				this->toolStripR->Checked = false;
				this->toolStripB->Checked = false;
				this->toolStripA->Checked = false;
			}
			else 
			{
				this->toolStripG->Checked = true;
			}
			this->UpdateVTFFile();
		}

		private: System::Void toolStripB_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (this->toolStripB->Checked)
			{
				this->btnChannelRGB->Checked = false;
				this->btnChannelR->Checked = false;
				this->btnChannelG->Checked = false;
				this->btnChannelB->Checked = true;
				this->btnChannelA->Checked = false;

				this->toolStripRGB->Checked = false;
				this->toolStripR->Checked = false;
				this->toolStripG->Checked = false;
				this->toolStripA->Checked = false;
			}
			else
			{
				this->toolStripB->Checked = true;
			}
			this->UpdateVTFFile();
		}

		private: System::Void toolStripA_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (this->toolStripA->Checked)
			{
				this->btnChannelRGB->Checked = false;
				this->btnChannelR->Checked = false;
				this->btnChannelG->Checked = false;
				this->btnChannelB->Checked = false;
				this->btnChannelA->Checked = true;

				this->toolStripRGB->Checked = false;
				this->toolStripR->Checked = false;
				this->toolStripG->Checked = false;
				this->toolStripB->Checked = false;
			}
			else 
			{
				this->toolStripA->Checked = true;
			}
			this->UpdateVTFFile();
		}

		private: System::Void toolStripMask_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			this->btnMask->Checked = this->toolStripMask->Checked ? true : false;
			this->UpdateVTFFile();
		}

		private: System::Void toolStripTile_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			this->btnTile->Checked = this->toolStripTile->Checked ? true : false;
			this->UpdateVTFFile();
			this->UpdateVTFView();
		}

		private: System::Void toolStripImport_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (this->CloseFile())
			{
				if (this->dlgImportFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->Import(this->dlgImportFile->FileNames);
				}
			}
		}

		private: System::Void toolStripClose_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (this->CloseFile())
			{
				this->ClearAll();
			}
		}

		private: System::Void toolStripCopy_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				if (this->picVTFFileTL->Image != nullptr)
				{
					System::Windows::Forms::Clipboard::SetDataObject(this->picVTFFileTL->Image, true);
				}
			}
			else
			{
				if (bWarnings)
				{
					if (bNotificationSounds)
					{
						System::Media::SystemSounds::Asterisk->Play();
					}
					MessageBox::Show("Operation not supported.\n\nVTFEdit has determined that the current thread apartment state does not\nsupport this operation. This is a .NET design flaw.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		private: System::Void toolStripPaste_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				System::Windows::Forms::IDataObject^ Data = System::Windows::Forms::Clipboard::GetDataObject();

				if (!Data->GetDataPresent(System::Windows::Forms::DataFormats::Bitmap))
				{
					return;
				}

				System::Drawing::Bitmap^ Bitmap = static_cast<System::Drawing::Bitmap^>(Data->GetData(System::Windows::Forms::DataFormats::Bitmap));

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
				if (this->Options->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				{
					return;
				}

				this->ClearAll();

				VTFLib::CVTFFile* VTFFile = new VTFLib::CVTFFile();

				// Initialize image data.
				vlUInt uiWidth = (vlUInt)Bitmap->Width, uiHeight = (vlUInt)Bitmap->Height;

				vlByte* lpImageData = new vlByte[uiWidth * uiHeight * 4];
				vlByte* lpPointer = lpImageData;

				for (int j = 0; j < Bitmap->Height; j++)
				{
					for (int i = 0; i < Bitmap->Width; i++)
					{
						System::Drawing::Color Pixel = Bitmap->GetPixel(i, j);

						*(lpPointer++) = (vlByte)Pixel.R;
						*(lpPointer++) = (vlByte)Pixel.G;
						*(lpPointer++) = (vlByte)Pixel.B;
						*(lpPointer++) = (vlByte)Pixel.A;
					}
				}

				SVTFCreateOptions VTFCreateOptions = CVTFFileUtility::GetCreateOptions(this->Options);

				// Create the .vtf file.
				if (VTFFile->Create(uiWidth, uiHeight, lpImageData, VTFCreateOptions) != vlFalse && CVTFFileUtility::CreateResources(Options, VTFFile))
				{
					this->SetVTFFile(VTFFile);

					this->btnSave->Enabled = true;
					this->toolStripSave->Enabled = true;
					this->toolStripClose->Enabled = true;
					this->btnClose->Enabled = true;
					this->btnSaveAs->Enabled = true;

					this->btnExport->Enabled = true;
					this->btnExportAll->Enabled = true;

					this->toolStripCopy->Enabled = true;
				}
				else
				{
					delete VTFFile;

					if (bWarnings)
					{
						if (bNotificationSounds)
						{
							System::Media::SystemSounds::Asterisk->Play();
						}
						MessageBox::Show(System::String::Concat("Error creating VTF texture:\n\n", gcnew System::String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}

				delete[]lpImageData;
			}
			else
			{
				if (bWarnings)
				{
					if (bNotificationSounds)
					{
						System::Media::SystemSounds::Asterisk->Play();
					}
					MessageBox::Show("Operation not supported.\n\nVTFEdit has determined that the current thread apartment state does not\nsupport this operation. This is a .NET design flaw.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		private: System::Void toolStripOpen_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (this->CloseFile())
			{
				if (this->dlgOpenFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->Open(this->dlgOpenFile->FileName, false);
				}
			}
		}

		private: System::Void toolStripExport_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			this->dlgExportFile->FileName = this->RemoveExtension(this->FileName);

			if (this->dlgExportFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->Export(this->dlgExportFile->FileName);
			}
		}

		private: System::Void toolStripSave_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (this->FileName != nullptr) 
			{
				this->Save(this->FileName);
			}
			else {
				this->SaveAs();
			}
		}

		private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (this->CloseFile()) 
			{
				this->ClearAll();
			}
		}

		private: System::Void btnNewVTF_Click(System::Object^ sender, System::EventArgs^ e) {
			if (this->CloseFile())
			{
				if (this->dlgImportFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->Import(this->dlgImportFile->FileNames);
				}
			}
		}

		private: System::Void btnNewVMT_Click(System::Object^ sender, System::EventArgs^ e) {
			if (this->CloseFile())
			{
				this->New();
			}
		}

		private: System::Void btnEditResources_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			// Iterate through the TreeView nodes to find the currently loaded resources if there are any.
			for (auto i = 0; i < treResources->Nodes->Count; i++)
			{
				// Set the check boxes for edit resources dialog if either of these two were found.
				System::Windows::Forms::TreeNode^ mainNode = treResources->Nodes[i];
				if(mainNode->Text->Contains("LOD"))
					EditResources->chkCreateLODControlResource->Checked = true;
				else if(mainNode->Text->Contains("Information"))
					EditResources->chkCreateInformationResource->Checked = true;

				System::Windows::Forms::TreeNode^ currentNode = treResources->Nodes[i]->FirstNode;
				System::Windows::Forms::TreeNode^ lastNode = treResources->Nodes[i]->LastNode;

				if (lastNode->Text->Contains("Clamp"))
					lastNode->Text = "Clamp V: " + EditResources->LODControlClampV.ToString();


				while (currentNode->NextNode != nullptr)
				{
					//currentNode->Text = "next"; // note to self, this is two steps down for Information
					if (currentNode->Text == "Author")
						EditResources->InformationAuthor = currentNode->FirstNode->Text;
					else if(currentNode->Text == "Contact")
						EditResources->InformationContact = currentNode->FirstNode->Text;
					else if (currentNode->Text == "Version")
						EditResources->InformationVersion = currentNode->FirstNode->Text;
					else if (currentNode->Text == "Modification")
						EditResources->InformationModification = currentNode->FirstNode->Text;
					else if (currentNode->Text == "Description")
						EditResources->InformationDescription = currentNode->FirstNode->Text;
					else if (currentNode->Text == "Comments")
						EditResources->InformationComments = currentNode->FirstNode->Text;
					
					currentNode = currentNode->NextNode;
				}
			}

			// Find the center of the main window to make this dialog box be centered on it.
			this->EditResources->Location = Point(
				(this->FormSaveLocation.X + (this->FormSaveSize.Width / 2)) - (this->EditResources->Width / 2),
				(this->FormSaveLocation.Y + (this->FormSaveSize.Height / 2)) - (this->EditResources->Height / 2)
			);
			// Basic check if the Options box's location will be outside of the monitor's bounds.
			if (this->EditResources->Location.X < 0 || this->EditResources->Location.Y < 0)
			{
				this->EditResources->Location = Point(0, 0);
			}
			if (this->EditResources->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			{
				return;
			}
			
			// Doing this the lazy way. I want a different dialog that's only the Resources tab from Options dalog.
			CVTFOptions^ tmpOptions = Options;

			//vlByte lpData[65536]{};
			if (EditResources->CreateLODControlResource)
			{
				tmpOptions->CreateLODControlResource = true;
				tmpOptions->LODControlClampU = EditResources->LODControlClampU;
				tmpOptions->LODControlClampV = EditResources->LODControlClampV;
			}
			else {
				tmpOptions->CreateLODControlResource = false;
			}

			if (EditResources->CreateInformationResource)
			{
				tmpOptions->CreateInformationResource = true;
				tmpOptions->InformationAuthor = EditResources->InformationAuthor;
				tmpOptions->InformationComments = EditResources->InformationComments;
				tmpOptions->InformationContact = EditResources->InformationContact;
				tmpOptions->InformationDescription = EditResources->InformationDescription;
				tmpOptions->InformationModification = EditResources->InformationModification;
				tmpOptions->InformationVersion = EditResources->InformationVersion;
			}
			else {
				tmpOptions->CreateInformationResource = false;
			}

			CVTFFileUtility::CreateResources(tmpOptions, this->VTFFile);

			this->SetVTFFile(this->VTFFile);
		}

		private: System::Void toolStripZoomIn_Click(System::Object^ sender, System::EventArgs^ e) {
			if (this->VTFFile == 0 || this->picVTFFileTL->Width >= 4096 || this->picVTFFileTL->Height >= 4096)
				return;

			this->fImageScale *= 2.0f;
			this->UpdateVTFFile();
			this->UpdateVTFView();
		}

		private: System::Void toolStripZoomOut_Click(System::Object^ sender, System::EventArgs^ e) {
			if (this->VTFFile == 0 || this->picVTFFileTL->Width <= 4 || this->picVTFFileTL->Height <= 4)
				return;

			this->fImageScale *= 0.5f;
			this->UpdateVTFFile();
			this->UpdateVTFView();
		}

		private: System::Void trkFrame_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			this->numFrame->Value = this->trkFrame->Value;
			if (!this->bHDRReseting)
			{
				this->UpdateVTFFile();
			}
		}

		private: System::Void numFrateRate_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			if (this->tmrAnimate->Enabled)
			{
				this->tmrAnimate->Stop();
				this->tmrAnimate->Interval = Convert::ToInt32(this->numFrameRate->Value);
				this->tmrAnimate->Start();
			}
			else {
				this->tmrAnimate->Interval = Convert::ToInt32(this->numFrameRate->Value);
			}
		}

		private: System::Void btnChannelR_Click(System::Object^ sender, System::EventArgs^ e) {
			this->btnChannelR->Checked = true;
			this->toolStripR->Checked = true;

			this->btnChannelRGB->Checked = false;
			this->btnChannelG->Checked = false;
			this->btnChannelB->Checked = false;
			this->btnChannelA->Checked = false;
			this->toolStripRGB->Checked = false;
			this->toolStripG->Checked = false;
			this->toolStripB->Checked = false;
			this->toolStripA->Checked = false;

			this->UpdateVTFFile();
		}

		private: System::Void btnChannelG_Click(System::Object^ sender, System::EventArgs^ e) {
			this->btnChannelG->Checked = true;
			this->toolStripG->Checked = true;

			this->btnChannelRGB->Checked = false;
			this->btnChannelR->Checked = false;
			this->btnChannelB->Checked = false;
			this->btnChannelA->Checked = false;
			this->toolStripRGB->Checked = false;
			this->toolStripR->Checked = false;
			this->toolStripB->Checked = false;
			this->toolStripA->Checked = false;

			this->UpdateVTFFile();
		}

		private: System::Void btnChannelB_Click(System::Object^ sender, System::EventArgs^ e) {
			this->btnChannelB->Checked = true;
			this->toolStripB->Checked = true;

			this->btnChannelRGB->Checked = false;
			this->btnChannelR->Checked = false;
			this->btnChannelG->Checked = false;
			this->btnChannelA->Checked = false;
			this->toolStripRGB->Checked = false;
			this->toolStripR->Checked = false;
			this->toolStripG->Checked = false;
			this->toolStripA->Checked = false;

			this->UpdateVTFFile();
		}

		private: System::Void btnChannelA_Click(System::Object^ sender, System::EventArgs^ e) {
			this->btnChannelA->Checked = true;
			this->toolStripA->Checked = true;

			this->btnChannelRGB->Checked = false;
			this->btnChannelR->Checked = false;
			this->btnChannelG->Checked = false;
			this->btnChannelB->Checked = false;
			this->toolStripRGB->Checked = false;
			this->toolStripR->Checked = false;
			this->toolStripG->Checked = false;
			this->toolStripB->Checked = false;

			this->UpdateVTFFile();
		}

		private: System::Void trkHDRExposure_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			this->UpdateVTFFile();
		}

		private: System::Void clrReflectivity_Click(System::Object^ sender, System::EventArgs^ e) {
			this->colorDialog->Color = this->clrReflectivity->BackColor;
			if (this->colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->lblImageReflectivity->Text = System::String::Concat(
					  "R ", (float(this->colorDialog->Color.R)/255).ToString("0.000"),
					", G ", (float(this->colorDialog->Color.G)/255).ToString("0.000"),
					", B ", (float(this->colorDialog->Color.B)/255).ToString("0.000")
				);
				this->clrReflectivity->BackColor = this->colorDialog->Color;
			}
		}

		private: System::Void txtVMTFile_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
			this->BackupForm();
		}

		private: System::Void splSidebar2_SplitterMoved(System::Object^ sender, System::Windows::Forms::SplitterEventArgs^ e) {
			this->BackupForm();
			this->UpdateVTFView();
		}

		private: System::Void btnWarnings_Click(System::Object^ sender, System::EventArgs^ e) {
			this->btnWarnings->Checked = !this->btnWarnings->Checked;
			this->bWarnings = this->btnWarnings->Checked;
		}

		private: System::Void btnNotifSounds_Click(System::Object^ sender, System::EventArgs^ e) {
			this->btnNotifSounds->Checked = !this->btnNotifSounds->Checked;
			this->bNotificationSounds = this->btnNotifSounds->Checked;
		}

		private: System::Void btnCustomAlphaToggle_Click(System::Object ^sender, System::EventArgs ^e) {
			this->btnCustomAlphaToggle->Checked = !this->btnCustomAlphaToggle->Checked;
			bCustomAlphaBackground = !bCustomAlphaBackground;
			this->UpdateVTFFile();
		}

		private: System::Void btnCustomAlphaSetter_Click(System::Object ^sender, System::EventArgs ^e) {
			this->colorDialog->Color = fAlphaBackgroundColor;
			if ( this->colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK ) {
				fAlphaBackgroundColor = this->colorDialog->Color;
			}
			this->UpdateVTFFile();
		}
};
}
