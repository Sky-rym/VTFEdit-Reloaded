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
#include "Utility.h"

using namespace System;

namespace VTFEdit
{
	public ref class CVTFFileUtility
	{
	public:
		static SVTFCreateOptions GetCreateOptions(CVTFOptions ^ Options)
		{
			SVTFCreateOptions VTFCreateOptions;

			vlImageCreateDefaultCreateStructure(&VTFCreateOptions);

			if(Options->Version->IndexOf('.') != -1)
			{
				try
				{
					VTFCreateOptions.uiVersion[0] = Convert::ToUInt32(Options->Version->Substring(0, Options->Version->IndexOf('.')));
					VTFCreateOptions.uiVersion[1] = Convert::ToUInt32(Options->Version->Substring(Options->Version->IndexOf('.') + 1));
				}
				catch(Exception ^)
				{
					VTFCreateOptions.uiVersion[0] = VTF_MAJOR_VERSION;
					VTFCreateOptions.uiVersion[1] = 4; // Defaulting to 4 instead of 5 because of how common people use this for older branch games.
				}
			}
			VTFCreateOptions.ImageFormat = Options->NormalFormat;
			VTFCreateOptions.bResize = Options->ResizeImage;
			VTFCreateOptions.ResizeMethod = Options->ResizeMethod;
			VTFCreateOptions.ResizeFilter = Options->ResizeFilter;
			VTFCreateOptions.bResizeClamp = Options->ResizeClamp;
			VTFCreateOptions.uiResizeClampWidth = Options->ResizeClampWidth;
			VTFCreateOptions.uiResizeClampHeight = Options->ResizeClampHeight;
			VTFCreateOptions.bGammaCorrection = Options->CorrectGamma;
			VTFCreateOptions.sGammaCorrection = Options->GammaCorrection;
			VTFCreateOptions.bMipmaps = Options->GenerateMipmaps;
			VTFCreateOptions.MipmapFilter = Options->MipmapFilter;
			VTFCreateOptions.bThumbnail = Options->GenerateThumbnail;
			VTFCreateOptions.bReflectivity = Options->ComputeReflectivity;
			VTFCreateOptions.bSphereMap = Options->GenerateSphereMap;
			VTFCreateOptions.bSRGB = Options->sRGB;
			VTFCreateOptions.nAlphaThreshold = Options->AlphaThreshold;

			vlSetFloat(VTFLIB_LUMINANCE_WEIGHT_R, Options->LuminanceWeightR);
			vlSetFloat(VTFLIB_LUMINANCE_WEIGHT_G, Options->LuminanceWeightG);
			vlSetFloat(VTFLIB_LUMINANCE_WEIGHT_B, Options->LuminanceWeightB);

			/*
			*	The bit of code below is commented out because it is invalid and the wrong thing to do on multiple fronts,
			*	Some of why this is wrong/invalid stem from issues with VTFEdit/VTFLib's internal design and or problematic decisions from Valve with later branches/versions of Source depending on how you look at it,
			*	Either way this should never be turned back on unless VTFEdit/VTFLib's handling of different VTF versions gets a major overhaul but even then I doubt this marker flag is that useful or even valid for what it's being used for here.
			*/

			/*if (Options->sRGB)
				VTFCreateOptions.uiFlags |= TEXTUREFLAGS_SRGB;*/

			return VTFCreateOptions;
		}

		static bool CreateResources(CVTFOptions ^ Options, VTFLib::CVTFFile *pVTFFile)
		{
			bool bResult = true;

			if(Options->CreateLODControlResource)
			{
				SVTFTextureLODControlResource LODControlResource;
				memset(&LODControlResource, 0, sizeof(SVTFTextureLODControlResource));
				LODControlResource.ResolutionClampU = Options->LODControlClampU;
				LODControlResource.ResolutionClampV = Options->LODControlClampV;

				bResult &= pVTFFile->SetResourceData(VTF_RSRC_TEXTURE_LOD_SETTINGS, sizeof(SVTFTextureLODControlResource), &LODControlResource) != vlFalse;
			}
			else {
				// If it doesn't have this resource checked, make sure it's wiped from the already existing resources or not created at all.
				pVTFFile->SetResourceData(VTF_RSRC_TEXTURE_LOD_SETTINGS, 0, 0);
			}

			if(Options->CreateInformationResource)
			{
				char cTemp[8192];				
				VTFLib::CVMTFile *pVMTFile = new VTFLib::CVMTFile();

				pVMTFile->Create("Information");
				if(Options->InformationAuthor->Length > 0)
				{
					CUtility::StringToCharPointer(Options->InformationAuthor, cTemp, sizeof(cTemp));
					pVMTFile->GetRoot()->AddStringNode("Author", cTemp);
				}
				if(Options->InformationContact->Length > 0)
				{
					CUtility::StringToCharPointer(Options->InformationContact, cTemp, sizeof(cTemp));
					pVMTFile->GetRoot()->AddStringNode("Contact", cTemp);
				}
				if(Options->InformationVersion->Length > 0)
				{
					CUtility::StringToCharPointer(Options->InformationVersion, cTemp, sizeof(cTemp));
					pVMTFile->GetRoot()->AddStringNode("Version", cTemp);
				}
				if(Options->InformationModification->Length > 0)
				{
					CUtility::StringToCharPointer(Options->InformationModification, cTemp, sizeof(cTemp));
					pVMTFile->GetRoot()->AddStringNode("Modification", cTemp);
				}
				if(Options->InformationDescription->Length > 0)
				{
					CUtility::StringToCharPointer(Options->InformationDescription, cTemp, sizeof(cTemp));
					pVMTFile->GetRoot()->AddStringNode("Description", cTemp);
				}
				if(Options->InformationComments->Length > 0)
				{
					CUtility::StringToCharPointer(Options->InformationComments, cTemp, sizeof(cTemp));
					pVMTFile->GetRoot()->AddStringNode("Comments", cTemp);
				}

				vlUInt uiSize = 0;
				vlByte lpBuffer[65536]{};
				if(pVMTFile->Save(lpBuffer, sizeof(lpBuffer), uiSize))
				{
					bResult &= pVTFFile->SetResourceData(VTF_RSRC_KEY_VALUE_DATA, uiSize, lpBuffer) != vlFalse;
				}

				delete pVMTFile;
			}
			else {
				// If it doesn't have this resource checked, make sure it's wiped from the already existing resources or not created at all.
				pVTFFile->SetResourceData(VTF_RSRC_KEY_VALUE_DATA, 0, 0);
			}

			return bResult;
		}
	};
}