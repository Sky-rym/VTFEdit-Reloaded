/*
 * VTFLib
 * Copyright (C) 2005-2011 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include "VTFLib.h"
#include "VTFWrapper.h"
#include "VTFFile.h"

using namespace VTFLib;

//
// vlImageBound()
// Returns true if an image is bound, false otherwise.
//
VTFLIB_API vlBool vlImageIsBound()
{
	if(!bInitialized)
	{
		LastError.Set("VTFLib not initialized.");
		return vlFalse;
	}

	return Image != 0;
}

//
// vlBindImage()
// Bind an image to operate on.
// All library routines will use this image.
//
VTFLIB_API vlBool vlBindImage(vlUInt uiImage)
{
	if(!bInitialized)
	{
		LastError.Set("VTFLib not initialized.");
		return vlFalse;
	}

	if(uiImage >= ImageVector->size() || (*ImageVector)[uiImage] == 0)
	{
		LastError.Set("Invalid image.");
		return vlFalse;
	}

	if(Image == (*ImageVector)[uiImage])	// If it is already bound do nothing.
		return vlTrue;

	Image = (*ImageVector)[uiImage];

	return vlTrue;
}

//
// vlCreateImage()
// Create an image to work on.
//
VTFLIB_API vlBool vlCreateImage(vlUInt *uiImage)
{
	if(!bInitialized)
	{
		LastError.Set("VTFLib not initialized.");
		return vlFalse;
	}

	ImageVector->push_back(new CVTFFile());
	*uiImage = (vlUInt)ImageVector->size() - 1;

	return vlTrue;
}

//
// vlDeleteImage()
// Delete an image and all resources associated with it.
//
VTFLIB_API vlVoid vlDeleteImage(vlUInt uiImage)
{
	if(!bInitialized)
		return;

	if(uiImage >= ImageVector->size())
		return;

	if((*ImageVector)[uiImage] == 0)
		return;

	if((*ImageVector)[uiImage] == Image)
	{
		Image = 0;
	}

	delete (*ImageVector)[uiImage];
	(*ImageVector)[uiImage] = 0;
}

VTFLIB_API vlVoid vlImageCreateDefaultCreateStructure(SVTFCreateOptions *VTFCreateOptions)
{
	VTFCreateOptions->uiVersion[0] = VTF_MAJOR_VERSION;
	VTFCreateOptions->uiVersion[1] = VTF_MINOR_VERSION_DEFAULT;

	VTFCreateOptions->ImageFormat = IMAGE_FORMAT_RGBA8888;

	VTFCreateOptions->uiFlags = 0;
	VTFCreateOptions->uiStartFrame = 0;
	VTFCreateOptions->sBumpScale = 1.0f;
	VTFCreateOptions->sReflectivity[0] = 1.0f;
	VTFCreateOptions->sReflectivity[1] = 1.0f;
	VTFCreateOptions->sReflectivity[2] = 1.0f;

	VTFCreateOptions->bMipmaps = vlTrue;
	VTFCreateOptions->MipmapFilter = MIPMAP_FILTER_BOX;

	VTFCreateOptions->bResize = vlFalse;
	VTFCreateOptions->ResizeMethod = RESIZE_NEAREST_POWER2;
	VTFCreateOptions->ResizeFilter = MIPMAP_FILTER_TRIANGLE;
	VTFCreateOptions->uiResizeWidth = 0;
	VTFCreateOptions->uiResizeHeight = 0;

	VTFCreateOptions->bResizeClamp = vlTrue;
	VTFCreateOptions->uiResizeClampWidth = 4096;
	VTFCreateOptions->uiResizeClampHeight = 4096;

	VTFCreateOptions->bThumbnail = vlTrue;
	VTFCreateOptions->bReflectivity = vlTrue;

	VTFCreateOptions->bGammaCorrection = vlFalse;
	VTFCreateOptions->sGammaCorrection = 2.0f;

	VTFCreateOptions->bSphereMap = vlFalse;
	VTFCreateOptions->bSRGB = vlFalse;
	VTFCreateOptions->nAlphaThreshold = 0;
}

VTFLIB_API vlBool vlImageCreate(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt uiSlices, VTFImageFormat ImageFormat, vlBool bThumbnail, vlBool bMipmaps, vlBool bNullImageData)
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->Create(uiWidth, uiHeight, uiFrames, uiFaces, uiSlices, ImageFormat, bThumbnail, bMipmaps, bNullImageData);
}

VTFLIB_API vlBool vlImageCreateSingle(vlUInt uiWidth, vlUInt uiHeight, vlByte *lpImageDataRGBA8888, SVTFCreateOptions *VTFCreateOptions)
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->Create(uiWidth, uiHeight, lpImageDataRGBA8888, *VTFCreateOptions);
}

VTFLIB_API vlBool vlImageCreateMultiple(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt uiSlices, vlByte **lpImageDataRGBA8888, SVTFCreateOptions *VTFCreateOptions)
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->Create(uiWidth, uiHeight, uiFrames, uiFaces, uiSlices, lpImageDataRGBA8888, *VTFCreateOptions);
}

VTFLIB_API vlVoid vlImageDestroy()
{
	if(Image == 0)
		return;

	Image->Destroy();
}

VTFLIB_API vlBool vlImageIsLoaded()
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->IsLoaded();
}

VTFLIB_API vlBool vlImageLoad(const vlChar *cFileName, vlBool bHeaderOnly)
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->Load(cFileName, bHeaderOnly);
}

VTFLIB_API vlBool vlImageLoadLump(const vlVoid *lpData, vlUInt uiBufferSize, vlBool bHeaderOnly)
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->Load(lpData, uiBufferSize, bHeaderOnly);
}

VTFLIB_API vlBool vlImageLoadProc(vlVoid *pUserData, vlBool bHeaderOnly)
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->Load(pUserData, bHeaderOnly);
}

VTFLIB_API vlBool vlImageSave(const vlChar *cFileName)
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->Save(cFileName);
}

VTFLIB_API vlBool vlImageSaveLump(vlVoid *lpData, vlUInt uiBufferSize, vlUInt *uiSize)
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->Save(lpData, uiBufferSize, *uiSize);
}

VTFLIB_API vlBool vlImageSaveProc(vlVoid *pUserData)
{
	if(Image == 0)
	{
		LastError.Set("No image bound.");
		return vlFalse;
	}

	return Image->Save(pUserData);
}

VTFLIB_API vlUInt vlImageGetMajorVersion()
{
	if(Image == 0)
		return 0;

	return Image->GetMajorVersion();
}

VTFLIB_API vlUInt vlImageGetMinorVersion()
{
	if(Image == 0)
		return 0;

	return Image->GetMinorVersion();
}

VTFLIB_API vlUInt vlImageGetSize()
{
	if(Image == 0)
		return 0;

	return Image->GetSize();
}

VTFLIB_API vlUInt vlImageGetHasImage()
{
	if(Image == 0)
		return vlFalse;

	return Image->GetHasImage();
}

VTFLIB_API vlUInt vlImageGetWidth()
{
	if(Image == 0)
		return 0;

	return Image->GetWidth();
}

VTFLIB_API vlUInt vlImageGetHeight()
{
	if(Image == 0)
		return 0;

	return Image->GetHeight();
}

VTFLIB_API vlUInt vlImageGetDepth()
{
	if(Image == 0)
		return 0;

	return Image->GetDepth();
}

VTFLIB_API vlUInt vlImageGetFrameCount()
{
	if(Image == 0)
		return 0;

	return Image->GetFrameCount();
}

VTFLIB_API vlUInt vlImageGetFaceCount()
{
	if(Image == 0)
		return 0;

	return Image->GetFaceCount();
}

VTFLIB_API vlUInt vlImageGetMipmapCount()
{
	if(Image == 0)
		return 0;

	return Image->GetMipmapCount();
}

VTFLIB_API vlUInt vlImageGetStartFrame()
{
	if(Image == 0)
		return 0;

	return Image->GetStartFrame();
}

VTFLIB_API vlVoid vlImageSetStartFrame(vlUInt uiStartFrame)
{
	if(Image == 0)
		return;

	Image->SetStartFrame(uiStartFrame);
}

VTFLIB_API vlUInt vlImageGetFlags()
{
	if(Image == 0)
		return 0;

	return Image->GetFlags();
}

VTFLIB_API vlVoid vlImageSetFlags(vlUInt uiFlags)
{
	if(Image == 0)
		return;

	Image->SetFlags(uiFlags);
}

VTFLIB_API vlBool vlImageGetFlag(VTFImageFlag ImageFlag)
{
	if(Image == 0)
		return vlFalse;

	return Image->GetFlag(ImageFlag);
}

VTFLIB_API vlVoid vlImageSetFlag(VTFImageFlag ImageFlag, vlBool bState)
{
	if(Image == 0)
		return;

	Image->SetFlag(ImageFlag, bState);
}

VTFLIB_API vlSingle vlImageGetBumpmapScale()
{
	if(Image == 0)
		return 0.0f;

	return Image->GetBumpmapScale();
}

VTFLIB_API vlVoid vlImageSetBumpmapScale(vlSingle sBumpmapScale)
{
	if(Image == 0)
		return;

	Image->SetBumpmapScale(sBumpmapScale);
}

VTFLIB_API vlVoid vlImageGetReflectivity(vlSingle *sX, vlSingle *sY, vlSingle *sZ)
{
	if(Image == 0)
		return;

	Image->GetReflectivity(*sX, *sY, *sZ);
}

VTFLIB_API vlVoid vlImageSetReflectivity(vlSingle sX, vlSingle sY, vlSingle sZ)
{
	if(Image == 0)
		return;

	Image->SetReflectivity(sX, sY, sZ);
}

VTFLIB_API VTFImageFormat vlImageGetFormat()
{
	if(Image == 0)
		return IMAGE_FORMAT_NONE;

	return Image->GetFormat();
}

VTFLIB_API vlByte *vlImageGetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel)
{
	if(Image == 0)
		return 0;

	return Image->GetData(uiFrame, uiFace, uiSlice, uiMipmapLevel);
}

VTFLIB_API vlVoid vlImageSetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel, vlByte *lpData)
{
	if(Image == 0)
		return;

	Image->SetData(uiFrame, uiFace, uiSlice, uiMipmapLevel, lpData);
}

VTFLIB_API vlBool vlImageGetHasThumbnail()
{
	if(Image == 0)
		return vlFalse;

	return Image->GetHasThumbnail();
}

VTFLIB_API vlUInt vlImageGetThumbnailWidth()
{
	if(Image == 0)
		return 0;

	return Image->GetThumbnailWidth();
}

VTFLIB_API vlUInt vlImageGetThumbnailHeight()
{
	if(Image == 0)
		return 0;

	return Image->GetThumbnailHeight();
}

VTFLIB_API VTFImageFormat vlImageGetThumbnailFormat()
{
	if(Image == 0)
		return IMAGE_FORMAT_NONE;

	return Image->GetThumbnailFormat();
}

VTFLIB_API vlByte *vlImageGetThumbnailData()
{
	if(Image == 0)
		return 0;

	return Image->GetThumbnailData();
}

VTFLIB_API vlVoid vlImageSetThumbnailData(vlByte *lpData)
{
	if(Image == 0)
		return;

	Image->SetThumbnailData(lpData);
}

VTFLIB_API vlBool vlImageGetSupportsResources()
{
	if(Image == 0)
		return vlFalse;

	return Image->GetSupportsResources();
}

VTFLIB_API vlUInt vlImageGetResourceCount()
{
	if(Image == 0)
		return 0;

	return Image->GetResourceCount();
}

VTFLIB_API vlUInt vlImageGetResourceType(vlUInt uiIndex)
{
	if(Image == 0)
		return 0;

	return Image->GetResourceType(uiIndex);
}

VTFLIB_API vlBool vlImageGetHasResource(vlUInt uiType)
{
	if(Image == 0)
		return vlFalse;

	return Image->GetHasResource(uiType);
}

VTFLIB_API vlVoid *vlImageGetResourceData(vlUInt uiType, vlUInt *uiSize)
{
	if(Image == 0)
		return 0;

	return Image->GetResourceData(uiType, *uiSize);
}

VTFLIB_API vlVoid *vlImageSetResourceData(vlUInt uiType, vlUInt uiSize, vlVoid *lpData)
{
	if(Image == 0)
		return 0;

	return Image->SetResourceData(uiType, uiSize, lpData);
}

VTFLIB_API vlBool vlImageGenerateMipmaps(vlUInt uiFace, vlUInt uiFrame, VTFMipmapFilter MipmapFilter, vlBool bSRGB)
{
	if(Image == 0)
		return vlFalse;

	return Image->GenerateMipmaps(uiFace, uiFrame, MipmapFilter, bSRGB);
}

VTFLIB_API vlBool vlImageGenerateAllMipmaps(VTFMipmapFilter MipmapFilter, vlBool bSRGB)
{
	if(Image == 0)
		return vlFalse;

	return Image->GenerateMipmaps(MipmapFilter, bSRGB);
}

VTFLIB_API vlBool vlImageGenerateThumbnail(vlBool bSRGB)
{
	if(Image == 0)
		return vlFalse;

	return Image->GenerateThumbnail(bSRGB);
}

VTFLIB_API vlBool vlImageGenerateNormalMap(vlUInt uiFrame, VTFKernelFilter KernelFilter, VTFHeightConversionMethod HeightConversionMethod, VTFNormalAlphaResult NormalAlphaResult)
{
	if(Image == 0)
		return vlFalse;

	return Image->GenerateNormalMap(uiFrame, KernelFilter, HeightConversionMethod, NormalAlphaResult);
}

VTFLIB_API vlBool vlImageGenerateAllNormalMaps(VTFKernelFilter KernelFilter, VTFHeightConversionMethod HeightConversionMethod, VTFNormalAlphaResult NormalAlphaResult)
{
	if(Image == 0)
		return vlFalse;

	return Image->GenerateNormalMap(KernelFilter, HeightConversionMethod, NormalAlphaResult);
}

VTFLIB_API vlBool vlImageGenerateSphereMap()
{
	if(Image == 0)
		return vlFalse;

	return Image->GenerateSphereMap();
}

VTFLIB_API vlBool vlImageComputeReflectivity()
{
	if(Image == 0)
		return vlFalse;

	return Image->ComputeReflectivity();
}

VTFLIB_API SVTFImageFormatInfo const *vlImageGetImageFormatInfo(VTFImageFormat ImageFormat)
{
	return &CVTFFile::GetImageFormatInfo(ImageFormat);
}

VTFLIB_API vlBool vlImageGetImageFormatInfoEx(VTFImageFormat ImageFormat, SVTFImageFormatInfo *VTFImageFormatInfo)
{
	if(ImageFormat >= 0 && ImageFormat < IMAGE_FORMAT_COUNT)
	{
		memcpy(VTFImageFormatInfo, &CVTFFile::GetImageFormatInfo(ImageFormat), sizeof(SVTFImageFormatInfo));
		return vlTrue;
	}

	return vlFalse;
}

VTFLIB_API vlUInt vlImageComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmaps, VTFImageFormat ImageFormat)
{
	return CVTFFile::ComputeImageSize(uiWidth, uiHeight, uiDepth, uiMipmaps, ImageFormat);
}

VTFLIB_API vlUInt vlImageComputeMipmapCount(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth)
{
	return CVTFFile::ComputeMipmapCount(uiWidth, uiHeight, uiDepth);
}

VTFLIB_API vlVoid vlImageComputeMipmapDimensions(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, vlUInt *uiMipmapWidth, vlUInt *uiMipmapHeight, vlUInt *uiMipmapDepth)
{
	CVTFFile::ComputeMipmapDimensions(uiWidth, uiHeight, uiDepth, uiMipmapLevel, *uiMipmapWidth, *uiMipmapHeight, *uiMipmapDepth);
}

VTFLIB_API vlUInt vlImageComputeMipmapSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, VTFImageFormat ImageFormat)
{
	return CVTFFile::ComputeMipmapSize(uiWidth, uiHeight, uiDepth, uiMipmapLevel, ImageFormat);
}

VTFLIB_API vlBool vlImageConvertToRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat)
{
	return CVTFFile::ConvertToRGBA8888(lpSource, lpDest, uiWidth, uiHeight, SourceFormat);
}

VTFLIB_API vlBool vlImageConvertFromRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat DestFormat)
{
	return CVTFFile::ConvertFromRGBA8888(lpSource, lpDest, uiWidth, uiHeight, DestFormat);
}

VTFLIB_API vlBool vlImageConvert(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat, VTFImageFormat DestFormat)
{
	return CVTFFile::Convert(lpSource, lpDest, uiWidth, uiHeight, SourceFormat, DestFormat);
}

VTFLIB_API vlBool vlImageResize(vlByte *lpSourceRGBA8888, vlByte *lpDestRGBA8888, vlUInt uiSourceWidth, vlUInt uiSourceHeight, vlUInt uiDestWidth, vlUInt uiDestHeight, VTFMipmapFilter ResizeFilter, vlBool bSRGB)
{
	return CVTFFile::Resize(lpSourceRGBA8888, lpDestRGBA8888, uiSourceWidth, uiSourceHeight, uiDestWidth, uiDestHeight, ResizeFilter, bSRGB);
}

VTFLIB_API vlVoid vlImageCorrectImageGamma(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle sGammaCorrection)
{
	CVTFFile::CorrectImageGamma(lpImageDataRGBA8888, uiWidth, uiHeight, sGammaCorrection);
}

VTFLIB_API vlVoid vlImageComputeImageReflectivity(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle *sX, vlSingle *sY, vlSingle *sZ)
{
	CVTFFile::ComputeImageReflectivity(lpImageDataRGBA8888, uiWidth, uiHeight, *sX, *sY, *sZ);
}

VTFLIB_API vlVoid vlImageFlipImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight)
{
	CVTFFile::FlipImage(lpImageDataRGBA8888, uiWidth, uiHeight);
}

VTFLIB_API vlVoid vlImageMirrorImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight)
{
	CVTFFile::FlipImage(lpImageDataRGBA8888, uiWidth, uiHeight);
}