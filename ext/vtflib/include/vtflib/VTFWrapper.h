/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef VTFWRAPPER_H
#define VTFWRAPPER_H

#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// Memory managment routines.
//

VTFLIB_API vlBool vlImageIsBound();
VTFLIB_API vlBool vlBindImage(vlUInt uiImage);

VTFLIB_API vlBool vlCreateImage(vlUInt *uiImage);
VTFLIB_API vlVoid vlDeleteImage(vlUInt uiImage);

//
// Library routines.  (Basically class wrappers.)
//

VTFLIB_API vlVoid vlImageCreateDefaultCreateStructure(SVTFCreateOptions *VTFCreateOptions);

VTFLIB_API vlBool vlImageCreate(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt uiSlices, VTFImageFormat ImageFormat, vlBool bThumbnail, vlBool bMipmaps, vlBool bNullImageData);
VTFLIB_API vlBool vlImageCreateSingle(vlUInt uiWidth, vlUInt uiHeight, vlByte *lpImageDataRGBA8888, SVTFCreateOptions *VTFCreateOptions);
VTFLIB_API vlBool vlImageCreateMultiple(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt uiSlices, vlByte **lpImageDataRGBA8888, SVTFCreateOptions *VTFCreateOptions);
VTFLIB_API vlVoid vlImageDestroy();

VTFLIB_API vlBool vlImageIsLoaded();

VTFLIB_API vlBool vlImageLoad(const vlChar *cFileName, vlBool bHeaderOnly);
VTFLIB_API vlBool vlImageLoadLump(const vlVoid *lpData, vlUInt uiBufferSize, vlBool bHeaderOnly);
VTFLIB_API vlBool vlImageLoadProc(vlVoid *pUserData, vlBool bHeaderOnly);

VTFLIB_API vlBool vlImageSave(const vlChar *cFileName);
VTFLIB_API vlBool vlImageSaveLump(vlVoid *lpData, vlUInt uiBufferSize, vlUInt *uiSize);
VTFLIB_API vlBool vlImageSaveProc(vlVoid *pUserData);

//
// Image routines.
//

VTFLIB_API vlUInt vlImageGetHasImage();

VTFLIB_API vlUInt vlImageGetMajorVersion();
VTFLIB_API vlUInt vlImageGetMinorVersion();
VTFLIB_API vlUInt vlImageGetSize();

VTFLIB_API vlUInt vlImageGetWidth();
VTFLIB_API vlUInt vlImageGetHeight();
VTFLIB_API vlUInt vlImageGetDepth();

VTFLIB_API vlUInt vlImageGetFrameCount();
VTFLIB_API vlUInt vlImageGetFaceCount();
VTFLIB_API vlUInt vlImageGetMipmapCount();

VTFLIB_API vlUInt vlImageGetStartFrame();
VTFLIB_API vlVoid vlImageSetStartFrame(vlUInt uiStartFrame);

VTFLIB_API vlUInt vlImageGetFlags();
VTFLIB_API vlVoid vlImageSetFlags(vlUInt uiFlags);

VTFLIB_API vlBool vlImageGetFlag(VTFImageFlag ImageFlag);
VTFLIB_API vlVoid vlImageSetFlag(VTFImageFlag ImageFlag, vlBool bState);

VTFLIB_API vlSingle vlImageGetBumpmapScale();
VTFLIB_API vlVoid vlImageSetBumpmapScale(vlSingle sBumpmapScale);

VTFLIB_API vlVoid vlImageGetReflectivity(vlSingle *sX, vlSingle *sY, vlSingle *sZ);
VTFLIB_API vlVoid vlImageSetReflectivity(vlSingle sX, vlSingle sY, vlSingle sZ);

VTFLIB_API VTFImageFormat vlImageGetFormat();

VTFLIB_API vlByte *vlImageGetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel);
VTFLIB_API vlVoid vlImageSetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel, vlByte *lpData);

//
// Thumbnail routines.
//

VTFLIB_API vlBool vlImageGetHasThumbnail();

VTFLIB_API vlUInt vlImageGetThumbnailWidth();
VTFLIB_API vlUInt vlImageGetThumbnailHeight();

VTFLIB_API VTFImageFormat vlImageGetThumbnailFormat();

VTFLIB_API vlByte *vlImageGetThumbnailData();
VTFLIB_API vlVoid vlImageSetThumbnailData(vlByte *lpData);

//
// Resource routines.
//

VTFLIB_API vlBool vlImageGetSupportsResources();

VTFLIB_API vlUInt vlImageGetResourceCount();
VTFLIB_API vlUInt vlImageGetResourceType(vlUInt uiIndex);
VTFLIB_API vlBool vlImageGetHasResource(vlUInt uiType);

VTFLIB_API vlVoid *vlImageGetResourceData(vlUInt uiType, vlUInt *uiSize);
VTFLIB_API vlVoid *vlImageSetResourceData(vlUInt uiType, vlUInt uiSize, vlVoid *lpData);

//
// Helper routines.
//

VTFLIB_API vlBool vlImageGenerateMipmaps(vlUInt uiFace, vlUInt uiFrame, VTFMipmapFilter MipmapFilter, vlBool bSRGB);
VTFLIB_API vlBool vlImageGenerateAllMipmaps(VTFMipmapFilter MipmapFilter, vlBool bSRGB);

VTFLIB_API vlBool vlImageGenerateThumbnail(vlBool bSRGB);

VTFLIB_API vlBool vlImageGenerateNormalMap(vlUInt uiFrame, VTFKernelFilter KernelFilter, VTFHeightConversionMethod HeightConversionMethod, VTFNormalAlphaResult NormalAlphaResult);
VTFLIB_API vlBool vlImageGenerateAllNormalMaps(VTFKernelFilter KernelFilter, VTFHeightConversionMethod HeightConversionMethod, VTFNormalAlphaResult NormalAlphaResult);

VTFLIB_API vlBool vlImageGenerateSphereMap();

VTFLIB_API vlBool vlImageComputeReflectivity();

//
// Conversion routines.
//

VTFLIB_API SVTFImageFormatInfo const *vlImageGetImageFormatInfo(VTFImageFormat ImageFormat);
VTFLIB_API vlBool vlImageGetImageFormatInfoEx(VTFImageFormat ImageFormat, SVTFImageFormatInfo *VTFImageFormatInfo);

VTFLIB_API vlUInt vlImageComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmaps, VTFImageFormat ImageFormat);

VTFLIB_API vlUInt vlImageComputeMipmapCount(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth);
VTFLIB_API vlVoid vlImageComputeMipmapDimensions(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, vlUInt *uiMipmapWidth, vlUInt *uiMipmapHeight, vlUInt *uiMipmapDepth);
VTFLIB_API vlUInt vlImageComputeMipmapSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, VTFImageFormat ImageFormat);

VTFLIB_API vlBool vlImageConvertToRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat);
VTFLIB_API vlBool vlImageConvertFromRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat DestFormat);

VTFLIB_API vlBool vlImageConvert(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat, VTFImageFormat DestFormat);

VTFLIB_API vlBool vlImageResize(vlByte *lpSourceRGBA8888, vlByte *lpDestRGBA8888, vlUInt uiSourceWidth, vlUInt uiSourceHeight, vlUInt uiDestWidth, vlUInt uiDestHeight, VTFMipmapFilter ResizeFilter, vlBool bSRGB);

VTFLIB_API vlVoid vlImageCorrectImageGamma(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle sGammaCorrection);
VTFLIB_API vlVoid vlImageComputeImageReflectivity(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle *sX, vlSingle *sY, vlSingle *sZ);

VTFLIB_API vlVoid vlImageFlipImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight);
VTFLIB_API vlVoid vlImageMirrorImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight);

#ifdef __cplusplus
}
#endif

#endif