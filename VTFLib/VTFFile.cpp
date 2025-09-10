/*
 * VTFLib
 * Copyright (C) 2005-2011 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#include <algorithm>
#include "VTFLib.h"
#include "VTFFile.h"
#include "VTFFormat.h"
#include "VTFDXTn.h"
#include "VTFMathlib.h"

#include "Compressonator.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

using namespace VTFLib;
using namespace std;

// Class construction
// ------------------
CVTFFile::CVTFFile()
{
	this->Header = 0;

	this->uiImageBufferSize = 0;
	this->lpImageData = 0;

	this->uiThumbnailBufferSize = 0;
	this->lpThumbnailImageData = 0;
}

//
// CVTFFile()
// Copy constructor.
//
CVTFFile::CVTFFile(const CVTFFile &VTFFile)
{
	this->Header = 0;

	this->uiImageBufferSize = 0;
	this->lpImageData = 0;

	this->uiThumbnailBufferSize = 0;
	this->lpThumbnailImageData = 0;

	if(VTFFile.IsLoaded())
	{
		this->Header = new SVTFHeader;
		memcpy(this->Header, VTFFile.Header, sizeof(SVTFHeader));

		if(VTFFile.GetHasImage())
		{
			this->uiImageBufferSize = VTFFile.uiImageBufferSize;
			this->lpImageData = new vlByte[this->uiImageBufferSize];
			memcpy(this->lpImageData, VTFFile.lpImageData, this->uiImageBufferSize);
		}

		if(VTFFile.GetHasThumbnail())
		{
			this->uiThumbnailBufferSize = VTFFile.uiThumbnailBufferSize;
			this->lpThumbnailImageData = new vlByte[this->uiThumbnailBufferSize];
			memcpy(this->lpThumbnailImageData, VTFFile.lpThumbnailImageData, this->uiThumbnailBufferSize);
		}
	}
}

//
// CVTFFile()
// Copy constructor.  Converts VTFFile to ImageFormat.
//
CVTFFile::CVTFFile(const CVTFFile &VTFFile, VTFImageFormat ImageFormat)
{
	this->Header = 0;

	this->uiImageBufferSize = 0;
	this->lpImageData = 0;

	this->uiThumbnailBufferSize = 0;
	this->lpThumbnailImageData = 0;

	if(VTFFile.IsLoaded())
	{
		this->Header = new SVTFHeader;
		memcpy(this->Header, VTFFile.Header, sizeof(SVTFHeader));

		// Set new format.
		this->Header->ImageFormat = ImageFormat;

		// Check flags.
		//if(this->Header->Version[0] < VTF_MAJOR_VERSION || (this->Header->Version[0] == VTF_MAJOR_VERSION && this->Header->Version[1] <= VTF_MINOR_VERSION_MIN_RESOURCE))
		//{
		//	if(!this->GetImageFormatInfo(ImageFormat).bIsCompressed)
		//	{
		//		this->Header->Flags |= TEXTUREFLAGS_DEPRECATED_NOCOMPRESS;
		//	}
		//	else
		//	{
		//		this->Header->Flags &= ~TEXTUREFLAGS_DEPRECATED_NOCOMPRESS;
		//	}
		//}

		if(this->GetImageFormatInfo(ImageFormat).uiAlphaBitsPerPixel == 1)
		{
			this->Header->Flags |= TEXTUREFLAGS_ONEBITALPHA;
		}
		else
		{
			this->Header->Flags &= ~TEXTUREFLAGS_ONEBITALPHA;
		}

		if(this->GetImageFormatInfo(ImageFormat).uiAlphaBitsPerPixel > 1)
		{
			this->Header->Flags |= TEXTUREFLAGS_EIGHTBITALPHA;
		}
		else
		{
			this->Header->Flags &= ~TEXTUREFLAGS_EIGHTBITALPHA;
		}

		// Convert image data.
		if(VTFFile.GetHasImage())
		{
			vlUInt uiFrames = VTFFile.GetFrameCount();
			vlUInt uiFaces = VTFFile.GetFaceCount();
			vlUInt uiMipmaps = VTFFile.GetMipmapCount();
			vlUInt uiSlices = VTFFile.GetDepth();

			this->uiImageBufferSize = this->ComputeImageSize(this->Header->Width, this->Header->Height, uiMipmaps, this->Header->ImageFormat) * uiFrames * uiFaces;
			this->lpImageData = new vlByte[this->uiImageBufferSize];

			//vlByte *lpImageData = new vlByte[this->ComputeImageSize(this->Header->Width, this->Header->Height, 1, IMAGE_FORMAT_RGBA8888)];

			for(vlUInt i = 0; i < uiFrames; i++)
			{
				for(vlUInt j = 0; j < uiFaces; j++)
				{
					for(vlUInt k = 0; k < uiSlices; k++)
					{
						for(vlUInt l = 0; l < uiMipmaps; l++)
						{
							vlUInt uiMipmapWidth, uiMipmapHeight, uiMipmapDepth;
							this->ComputeMipmapDimensions(this->Header->Width, this->Header->Height, 1, l, uiMipmapWidth, uiMipmapHeight, uiMipmapDepth);

							//this->ConvertToRGBA8888(VTFFile.GetData(i, j, k, l), lpImageData, uiMipmapWidth, uiMipmapHeight, VTFFile.GetFormat());
							//this->ConvertFromRGBA8888(lpImageData, this->GetData(i, j, k, l), uiMipmapWidth, uiMipmapHeight, this->GetFormat());
							this->Convert(VTFFile.GetData(i, j, k, l), this->GetData(i, j, k, l), uiMipmapWidth, uiMipmapHeight, VTFFile.GetFormat(), this->GetFormat());
						}
					}
				}
			}

			//delete []lpImageData;
		}

		// Convert thumbnail data.
		if(VTFFile.GetHasThumbnail())
		{
			this->uiThumbnailBufferSize = VTFFile.uiThumbnailBufferSize;
			this->lpThumbnailImageData = new vlByte[this->uiThumbnailBufferSize];
			memcpy(this->lpThumbnailImageData, VTFFile.lpThumbnailImageData, this->uiThumbnailBufferSize);
		}
	}
}

// Class deconstruction
// ------------------
CVTFFile::~CVTFFile()
{
	this->Destroy();
}

//
// Create()
// Creates a VTF file of the specified format and size.  Image data and other
// options must be set after creation.  Essential format flags are automatically
// generated.
//
vlBool CVTFFile::Create(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt uiSlices, VTFImageFormat ImageFormat, vlBool bThumbnail, vlBool bMipmaps, vlBool bNullImageData)
{
	this->Destroy();

	//
	// Check options.
	//

	// Check if width is valid (power of 2 and fits in a short).
	if(!this->IsMultipleOfFour(uiWidth) || uiWidth > 0xffff)
	{
		// 2 is valid since it's a power of 2, but I don't want to do more than this.
		if (uiWidth == 0 || uiWidth != 2)
		{
			LastError.SetFormatted("Invalid image width %u. Width must be a power of two or multiple of four.", uiWidth);
		}
		return vlFalse;
	}

	// Check if height is valid (power of 2 and fits in a short).
	if(!this->IsMultipleOfFour(uiHeight) || uiHeight > 0xffff)
	{
		if (uiHeight == 0 || uiHeight == 2)
		{
			LastError.SetFormatted("Invalid image height %u. Height must be a power of two or multiple of four.", uiHeight);
		}
		return vlFalse;
	}

	// Check if depth is valid (power of 2 and fits in a short).
	if(!this->IsPowerOfTwo(uiSlices) || uiSlices > 0xffff)
	{
		vlUInt uiNextPowerOfTwo = this->NextPowerOfTwo(uiSlices);
		LastError.SetFormatted("Invalid image depth %u. Depth must be a power of two (nearest powers are %u and %u).", uiSlices, uiNextPowerOfTwo >> 1, uiNextPowerOfTwo);

		return vlFalse;
	}

	if(ImageFormat <= IMAGE_FORMAT_NONE || ImageFormat >= IMAGE_FORMAT_COUNT)
	{
		LastError.Set("Invalid image format.");
		return vlFalse;
	}

	if(!this->GetImageFormatInfo(ImageFormat).bIsSupported)
	{
		LastError.Set("Image format not supported.");
		return vlFalse;
	}

	if(uiFrames < 1 || uiFrames > 0xffff)
	{
		LastError.SetFormatted("Invalid image frame count %u.", uiFrames);
		return vlFalse;
	}

	if(uiFaces != 1 && uiFaces != 6 && uiFaces != 7)
	{
		LastError.SetFormatted("Invalid image face count %u.", uiFaces);
		return vlFalse;
	}

	if(uiFaces != 1 && uiFaces != 6 && VTF_MINOR_VERSION_DEFAULT >= VTF_MINOR_VERSION_MIN_NO_SPHERE_MAP)
	{
		LastError.SetFormatted("Invalid image face count %u for version %d.%d.", uiFaces, VTF_MAJOR_VERSION, VTF_MINOR_VERSION_DEFAULT);
		return vlFalse;
	}

	// Note: Valve informs us that animated enviroment maps ARE possible.

	// A image cannot have multiple frames and faces.
	// Logic: StartFrame is used as a flag when the texture is a TEXTUREFLAGS_ENVMAP.
	//if(uiFrames != 1 && uiFaces != 1)
	//{
	//	LastError.Set("Invalid image frame and face count.  An image cannot have multiple frames and faces.");
	//	return vlFalse;
	//}

	//
	// Generate header.
	//

	this->Header = new SVTFHeader;
	memset(this->Header, 0, sizeof(SVTFHeader));

	strcpy_s(this->Header->TypeString, "VTF");
	this->Header->Version[0] = VTF_MAJOR_VERSION;
	this->Header->Version[1] = VTF_MINOR_VERSION_DEFAULT;
	this->Header->HeaderSize = 0;
	this->Header->Width = (vlShort)uiWidth;
	this->Header->Height = (vlShort)uiHeight;
	this->Header->Flags = (this->GetImageFormatInfo(ImageFormat).uiAlphaBitsPerPixel == 1 ? TEXTUREFLAGS_ONEBITALPHA : 0)
							| (this->GetImageFormatInfo(ImageFormat).uiAlphaBitsPerPixel > 1 ? TEXTUREFLAGS_EIGHTBITALPHA : 0)
							| (uiFaces == 1 ? 0 : TEXTUREFLAGS_ENVMAP)
							| (bMipmaps ? 0 : TEXTUREFLAGS_NOMIP | TEXTUREFLAGS_NOLOD);
	this->Header->Frames = (vlShort)uiFrames;
	this->Header->StartFrame = uiFaces != 6 || VTF_MINOR_VERSION_DEFAULT >= VTF_MINOR_VERSION_MIN_NO_SPHERE_MAP ? 0 : 0xffff;
	this->Header->Reflectivity[0] = 1.0f;
	this->Header->Reflectivity[1] = 1.0f;
	this->Header->Reflectivity[2] = 1.0f;
	this->Header->BumpScale = 1.0f;
	this->Header->ImageFormat = ImageFormat;
	this->Header->MipCount = bMipmaps ? (vlByte)this->ComputeMipmapCount(uiWidth, uiHeight, uiSlices) : 1;
	this->Header->Depth = (vlShort)uiSlices;
	this->Header->ResourceCount = 0;

	//
	// Generate thumbnail.
	//

	if(bThumbnail)
	{
		// Note: Valve informs us that DXT1 is the correct format.

		//  The format DXT1 was observed in almost every official .vtf file.
		this->Header->LowResImageFormat = IMAGE_FORMAT_DXT1;

		// Note: Valve informs us that the below is the right dimensions.

		// Find a thumbnail width and height (the first width and height <= 16 pixels).
		// The value 16 was observed in almost every official .vtf file.

		vlUInt uiThumbnailWidth = this->Header->Width, uiThumbnailHeight = this->Header->Height;

		while(vlTrue)
		{
			if(uiThumbnailWidth <= 16 && uiThumbnailHeight <= 16)
			{
				break;
			}

			uiThumbnailWidth >>= 1;
			uiThumbnailHeight >>= 1;
			
			if(uiThumbnailWidth < 1)
				uiThumbnailWidth = 1;

			if(uiThumbnailHeight < 1)
				uiThumbnailHeight = 1;
		}

		this->Header->LowResImageWidth = (vlByte)uiThumbnailWidth;
		this->Header->LowResImageHeight = (vlByte)uiThumbnailHeight;

		this->uiThumbnailBufferSize = this->ComputeImageSize(this->Header->LowResImageWidth, this->Header->LowResImageHeight, 1, this->Header->LowResImageFormat);
		this->lpThumbnailImageData = new vlByte[this->uiThumbnailBufferSize];

		this->Header->Resources[this->Header->ResourceCount++].Type = VTF_LEGACY_RSRC_LOW_RES_IMAGE;
	}
	else
	{
		this->Header->LowResImageFormat = IMAGE_FORMAT_NONE;
		this->Header->LowResImageWidth = 0;
		this->Header->LowResImageHeight = 0;

		this->uiThumbnailBufferSize = 0;
		this->lpThumbnailImageData = 0;
	}

	//
	// Generate image.
	//

	// DXT1 One Bit is apparently broken... Use DXT1 with One Bit Alpha flag enabled instead.
	if ( this->Header->ImageFormat == IMAGE_FORMAT_DXT1_ONEBITALPHA )
		this->Header->ImageFormat = IMAGE_FORMAT_DXT1;
	
	this->uiImageBufferSize = this->ComputeImageSize(this->Header->Width, this->Header->Height, this->Header->Depth, this->Header->MipCount, this->Header->ImageFormat) * uiFrames * uiFaces;
	this->lpImageData = new vlByte[this->uiImageBufferSize];

	this->Header->Resources[this->Header->ResourceCount++].Type = VTF_LEGACY_RSRC_IMAGE;

	//
	// Null image data.
	//

	if(bNullImageData)
	{
		memset(this->lpThumbnailImageData, 0, this->uiThumbnailBufferSize);
		memset(this->lpImageData, 0, this->uiImageBufferSize);
	}

	this->ComputeResources();

	return vlTrue;
}

//
// Create()
// Creates a VTF file of the specified format and size using the provided image RGBA data.
// Can also generate mipmaps and a thumbnail.  Recommended function for high level single
// face/frame VTF file creation.
//
vlBool CVTFFile::Create(vlUInt uiWidth, vlUInt uiHeight, vlByte *lpImageDataRGBA8888, const SVTFCreateOptions &VTFCreateOptions)
{
	return this->Create(uiWidth, uiHeight, 1, 1, 1, &lpImageDataRGBA8888, VTFCreateOptions);
}

static CMP_FORMAT GetCMPFormat( VTFImageFormat imageFormat, bool bDXT5GA )
{
	if ( bDXT5GA )
		return CMP_FORMAT_ATI2N_DXT5;

	switch ( imageFormat )
	{
	case IMAGE_FORMAT_BGR888:			return CMP_FORMAT_BGR_888;
	case IMAGE_FORMAT_RGB888:			return CMP_FORMAT_RGB_888;
	case IMAGE_FORMAT_RGBA8888:			return CMP_FORMAT_RGBA_8888;
	case IMAGE_FORMAT_BGRA8888:			return CMP_FORMAT_BGRA_8888;

	case IMAGE_FORMAT_DXT1_ONEBITALPHA:	return CMP_FORMAT_DXT1;
	case IMAGE_FORMAT_DXT1:				return CMP_FORMAT_DXT1;
	case IMAGE_FORMAT_DXT3:				return CMP_FORMAT_DXT3;
	case IMAGE_FORMAT_DXT5:				return CMP_FORMAT_DXT5;
	case IMAGE_FORMAT_ATI1N:			return CMP_FORMAT_ATI1N;
	// Swizzle is technically wrong for below but we reverse it in the shader!
	case IMAGE_FORMAT_ATI2N:			return CMP_FORMAT_ATI2N;

	default:							return CMP_FORMAT_Unknown;
	}
}

static const char *GetCMPErrorString( CMP_ERROR error )
{
	switch ( error )
	{
		case CMP_OK:		                        return "Ok.";
		case CMP_ABORTED:                           return "The conversion was aborted.";
		case CMP_ERR_INVALID_SOURCE_TEXTURE:        return "The source texture is invalid.";
		case CMP_ERR_INVALID_DEST_TEXTURE:          return "The destination texture is invalid.";
		case CMP_ERR_UNSUPPORTED_SOURCE_FORMAT:     return "The source format is not a supported format.";
		case CMP_ERR_UNSUPPORTED_DEST_FORMAT:       return "The destination format is not a supported format.";
		case CMP_ERR_UNSUPPORTED_GPU_ASTC_DECODE:   return "The gpu hardware is not supported.";
		case CMP_ERR_UNSUPPORTED_GPU_BASIS_DECODE:  return "The gpu hardware is not supported.";
		case CMP_ERR_SIZE_MISMATCH:                 return "The source and destination texture sizes do not match.";
		case CMP_ERR_UNABLE_TO_INIT_CODEC:          return "Compressonator was unable to initialize the codec needed for conversion.";
		case CMP_ERR_UNABLE_TO_INIT_DECOMPRESSLIB:  return "GPU_Decode Lib was unable to initialize the codec needed for decompression .";
		case CMP_ERR_UNABLE_TO_INIT_COMPUTELIB:     return "Compute Lib was unable to initialize the codec needed for compression.";
		case CMP_ERR_CMP_DESTINATION:               return "Error in compressing destination texture";
		case CMP_ERR_MEM_ALLOC_FOR_MIPSET:          return "Memory Error: allocating MIPSet compression level data buffer";
		case CMP_ERR_UNKNOWN_DESTINATION_FORMAT:    return "The destination Codec Type is unknown! In SDK refer to GetCodecType()";
		case CMP_ERR_FAILED_HOST_SETUP:             return "Failed to setup Host for processing";
		case CMP_ERR_PLUGIN_FILE_NOT_FOUND:         return "The required plugin library was not found";
		case CMP_ERR_UNABLE_TO_LOAD_FILE:           return "The requested file was not loaded";
		case CMP_ERR_UNABLE_TO_CREATE_ENCODER:      return "Request to create an encoder failed";
		case CMP_ERR_UNABLE_TO_LOAD_ENCODER:        return "Unable to load an encode library";
		case CMP_ERR_NOSHADER_CODE_DEFINED:         return "No shader code is available for the requested framework";
		case CMP_ERR_GPU_DOESNOT_SUPPORT_COMPUTE:   return "The GPU device selected does not support compute";
		case CMP_ERR_NOPERFSTATS:                   return "No Performance Stats are available";
		case CMP_ERR_GPU_DOESNOT_SUPPORT_CMP_EXT:   return "The GPU does not support the requested compression extension!";
		case CMP_ERR_GAMMA_OUTOFRANGE:              return "Gamma value set for processing is out of range";
		case CMP_ERR_PLUGIN_SHAREDIO_NOT_SET:       return "The plugin C_PluginSetSharedIO call was not set and is required for this plugin to operate";
		case CMP_ERR_UNABLE_TO_INIT_D3DX:           return "Unable to initialize DirectX SDK or get a specific DX API";
		default:
		case CMP_ERR_GENERIC:                       return "An unknown error occurred.";
	}
}

//
// Create()
// Creates a VTF file of the specified format and size using the provided image RGBA data.
// Can also generate mipmaps and a thumbnail.  Recommended function for high level multiple
// face/frame VTF file creation.
//
vlBool CVTFFile::Create(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt uiSlices, vlByte **lpImageDataRGBA8888, const SVTFCreateOptions &VTFCreateOptions)
{
	vlUInt uiCount = 0;
	if(uiFrames > uiCount)
		uiCount = uiFrames;
	if(uiFaces > uiCount)
		uiCount = uiFaces;
	if(uiSlices > uiCount)
		uiCount = uiSlices;
	vlByte **lpNewImageDataRGBA8888 = 0;

	if((uiFrames == 1 && uiFaces > 1 && uiSlices > 1) || (uiFrames > 1 && uiFaces == 1 && uiSlices > 1) || (uiFrames > 1 && uiFaces > 1 && uiSlices == 1))
	{
		LastError.Set("Invalid image frame, face and slice count combination.  Function does not support images with any combination of multiple frames or faces or slices.");
		return vlFalse;
	}

	if(VTFCreateOptions.uiVersion[0] != VTF_MAJOR_VERSION || (VTFCreateOptions.uiVersion[1] < 0 || VTFCreateOptions.uiVersion[1] > VTF_MINOR_VERSION))
	{
		LastError.SetFormatted("File version %u.%u does not match %d.%d to %d.%d.", VTFCreateOptions.uiVersion[0], VTFCreateOptions.uiVersion[1], VTF_MAJOR_VERSION, 0, VTF_MAJOR_VERSION, VTF_MINOR_VERSION);
		return vlFalse;
	}

	if(VTFCreateOptions.uiVersion[0] == VTF_MAJOR_VERSION && VTFCreateOptions.uiVersion[1] < VTF_MINOR_VERSION_MIN_VOLUME && uiSlices > 1)
	{
		LastError.SetFormatted("Volume textures are only supported in version %d.%d and up.", VTF_MAJOR_VERSION, VTF_MINOR_VERSION_MIN_VOLUME);
		return vlFalse;
	}

	if(VTFCreateOptions.uiVersion[0] == VTF_MAJOR_VERSION && VTFCreateOptions.uiVersion[1] < VTF_MINOR_VERSION_MIN_SPHERE_MAP && uiFaces == 7)
	{
		LastError.SetFormatted("Sphere maps are only supported in version %d.%d and up.", VTF_MAJOR_VERSION, VTF_MINOR_VERSION_MIN_SPHERE_MAP);
		return vlFalse;
	}

	if(VTFCreateOptions.bMipmaps && uiSlices > 1)
	{
		LastError.Set("Mipmap generation for depth textures is not supported.");
		return vlFalse;
	}

	try
	{
		if(VTFCreateOptions.bResize)
		{
			vlUInt uiNewWidth = uiWidth;
			vlUInt uiNewHeight = uiHeight;

			switch(VTFCreateOptions.ResizeMethod)
			{
			case RESIZE_NEAREST_POWER2:
			case RESIZE_BIGGEST_POWER2:
			case RESIZE_SMALLEST_POWER2:
				// Find the best width.
				if(!this->IsPowerOfTwo(uiWidth))
				{
					// Find largest power of 2.
					uiNewWidth = this->NextPowerOfTwo(uiWidth);

					if(VTFCreateOptions.ResizeMethod == RESIZE_NEAREST_POWER2)
					{
						if(uiWidth - (uiNewWidth >> 1) < uiNewWidth - uiWidth)
						{
							uiNewWidth >>= 1;
						}
					}
					else if(VTFCreateOptions.ResizeMethod == RESIZE_SMALLEST_POWER2)
					{
						uiNewWidth >>= 1;
					}

					if(uiNewWidth == 0)
					{
						uiNewWidth = 1;
					}
				}
				if(VTFCreateOptions.bResizeClamp && uiNewWidth > VTFCreateOptions.uiResizeClampWidth)
				{
					uiNewWidth = VTFCreateOptions.uiResizeClampWidth;
				}

				// Find the best height.
				if(!this->IsPowerOfTwo(uiHeight))
				{
					// Find largest power of 2.
					uiNewHeight = this->NextPowerOfTwo(uiHeight);

					if(VTFCreateOptions.ResizeMethod == RESIZE_NEAREST_POWER2)
					{
						if(uiHeight - (uiNewHeight >> 1) < uiNewHeight - uiHeight)
						{
							uiNewHeight >>= 1;
						}
					}
					else if(VTFCreateOptions.ResizeMethod == RESIZE_SMALLEST_POWER2)
					{
						uiNewHeight >>= 1;
					}

					if(uiNewHeight == 0)
					{
						uiNewHeight = 1;
					}
				}
				if(VTFCreateOptions.bResizeClamp && uiNewHeight > VTFCreateOptions.uiResizeClampHeight)
				{
					uiNewHeight = VTFCreateOptions.uiResizeClampHeight;
				}
				break;
			case RESIZE_NEAREST_MULTIPLE4:
				// Is not a multiple of 4.
				if (!this->IsMultipleOfFour(uiWidth))
				{
					uiNewWidth = this->NearestMultipleOfFour(uiWidth);
				}
				if (!this->IsMultipleOfFour(uiHeight))
				{
					uiNewHeight = this->NearestMultipleOfFour(uiHeight);
				}
				break;
			case RESIZE_SET:
				uiNewWidth = VTFCreateOptions.uiResizeWidth;
				uiNewHeight = VTFCreateOptions.uiResizeHeight;
				break;
			}

			// Resize the input.
			if(uiWidth != uiNewWidth || uiHeight != uiNewHeight)
			{
				lpNewImageDataRGBA8888 = new vlByte *[uiCount];
				memset(lpNewImageDataRGBA8888, 0, uiCount * sizeof(vlByte *));

				for(vlUInt i = 0; i < uiCount; i++)
				{
					lpNewImageDataRGBA8888[i] = new vlByte[this->ComputeImageSize(uiNewWidth, uiNewHeight, 1, IMAGE_FORMAT_RGBA8888)];

					if(!this->Resize(lpImageDataRGBA8888[i], lpNewImageDataRGBA8888[i], uiWidth, uiHeight, uiNewWidth, uiNewHeight, VTFCreateOptions.ResizeFilter, VTFCreateOptions.bSRGB))
					{
						throw 0;
					}
				}

				uiWidth = uiNewWidth;
				uiHeight = uiNewHeight;

				lpImageDataRGBA8888 = lpNewImageDataRGBA8888;
			}
		}

		// Create image (allocate and setup structures).
		if(!this->Create(uiWidth, uiHeight, uiFrames, uiFaces + (VTFCreateOptions.bSphereMap && uiFaces == 6 ? 1 : 0), uiSlices, VTFCreateOptions.ImageFormat, VTFCreateOptions.bThumbnail, VTFCreateOptions.bMipmaps, vlFalse))
		{
			throw 0;
		}

		// Update version, for the current versions with the current checking this should be sufficient.
		this->Header->Version[0] = VTFCreateOptions.uiVersion[0];
		this->Header->Version[1] = VTFCreateOptions.uiVersion[1];

		this->ComputeResources();

		// Do gamma correction.
		if(VTFCreateOptions.bGammaCorrection)
		{
			for(vlUInt i = 0; i < uiFrames; i++)
			{
				for(vlUInt j = 0; j < uiFaces; j++)
				{
					for(vlUInt k = 0; k < uiSlices; k++)
					{
						this->CorrectImageGamma(lpImageDataRGBA8888[i + j + k], this->Header->Width, this->Header->Height, VTFCreateOptions.sGammaCorrection);
					}
				}
			}
		}

		// Generate mipmaps off source image.
		if(VTFCreateOptions.bMipmaps && this->Header->MipCount != 1)
		{
			auto temp = std::vector<vlByte>(this->Header->Width * this->Header->Height * 4);

			for(vlUInt i = 0; i < uiFrames; i++)
			{
				for(vlUInt j = 0; j < uiFaces; j++)
				{
					for(vlUInt k = 0; k < uiSlices; k++)
					{
						vlByte* pSource = lpImageDataRGBA8888[i + j + k];

						if(!this->ConvertFromRGBA8888(pSource, this->GetData(i, j, k, 0), this->Header->Width, this->Header->Height, this->Header->ImageFormat, VTFCreateOptions.nAlphaThreshold))
						{
							throw 0;
						}

						for (vlUInt m = 1; m < this->Header->MipCount; m++)
						{
							vlUShort usWidth  = max(1u, this->Header->Width  >> m);
							vlUShort usHeight = max(1u, this->Header->Height >> m);

							if (!stbir_resize_uint8_generic(
								pSource, this->Header->Width, this->Header->Height, 0,
								temp.data(), usWidth, usHeight, 0,
								4, 3, 0, STBIR_EDGE_CLAMP, stbir_filter(VTFCreateOptions.MipmapFilter), VTFCreateOptions.bSRGB ? STBIR_COLORSPACE_SRGB : STBIR_COLORSPACE_LINEAR, NULL))
							{
								throw 0;
							}

							if (!this->ConvertFromRGBA8888(temp.data(), this->GetData(i, j, k, m), usWidth, usHeight, this->Header->ImageFormat, VTFCreateOptions.nAlphaThreshold))
							{
								throw 0;
							}
						}
					}
				}
			}
		}
		else
		{
			for(vlUInt i = 0; i < uiFrames; i++)
			{
				for(vlUInt j = 0; j < uiFaces; j++)
				{
					for(vlUInt k = 0; k < uiSlices; k++)
					{
						if(!this->ConvertFromRGBA8888(lpImageDataRGBA8888[i + j + k], this->GetData(i, j, k, 0), this->Header->Width, this->Header->Height, this->Header->ImageFormat, VTFCreateOptions.nAlphaThreshold))
						{
							throw 0;
						}
					}
				}
			}
		}

		// Generate thumbnail off mipmaps.
		if(VTFCreateOptions.bThumbnail)
		{
			if(!this->GenerateThumbnail(VTFCreateOptions.bSRGB))
			{
				throw 0;
			}
		}

		if(VTFCreateOptions.bSphereMap && uiFaces == 6)
		{
			if(!this->GenerateSphereMap())
			{
				throw 0;
			}
		}

		if(VTFCreateOptions.bReflectivity)
		{
			this->Header->Reflectivity[0] = 0.0f;
			this->Header->Reflectivity[1] = 0.0f;
			this->Header->Reflectivity[2] = 0.0f;

			for(vlUInt i = 0; i < uiFrames; i++)
			{
				for(vlUInt j = 0; j < uiFaces; j++)
				{
					for(vlUInt k = 0; k < uiSlices; k++)
					{
						vlSingle sX, sY, sZ;
						this->ComputeImageReflectivity(lpImageDataRGBA8888[i + j + k], uiWidth, uiHeight, sX, sY, sZ);

						this->Header->Reflectivity[0] += sX;
						this->Header->Reflectivity[1] += sY;
						this->Header->Reflectivity[2] += sZ;
					}
				}
			}

			vlSingle sInverse = 1.0f / (vlSingle)(uiFrames * uiFaces * uiSlices);

			this->Header->Reflectivity[0] *= sInverse;
			this->Header->Reflectivity[1] *= sInverse;
			this->Header->Reflectivity[2] *= sInverse;
		}
		else
		{
			this->SetReflectivity(VTFCreateOptions.sReflectivity[0], VTFCreateOptions.sReflectivity[1], VTFCreateOptions.sReflectivity[2]);
		}

		// Set the flags, call SetFlag() to make sure we don't set anything we shouldn't.
		for(vlUInt i = 0, uiFlag = 0x00000001; i < TEXTUREFLAGS_COUNT; i++, uiFlag <<= 1)
		{
			if(VTFCreateOptions.uiFlags & uiFlag)
			{
				this->SetFlag((VTFImageFlag)uiFlag, vlTrue);
			}
		}
		this->SetStartFrame(VTFCreateOptions.uiStartFrame);
		this->SetBumpmapScale(VTFCreateOptions.sBumpScale);

		return vlTrue;
	}
	catch(...)
	{
		if(lpNewImageDataRGBA8888 != 0)
		{
			for(vlUInt i = 0; i < uiCount; i++)
			{
				delete []lpNewImageDataRGBA8888[i];
			}
			delete []lpNewImageDataRGBA8888;
		}

		this->Destroy();

		return vlFalse;
	}
}

//
// Destroy()
// Frees all resources associated with the curret image.
//
vlVoid CVTFFile::Destroy()
{
	if(this->Header != 0)
	{
		for(vlUInt i = 0; i < this->Header->ResourceCount; i++)
		{
			delete []this->Header->Data[i].Data;
		}
	}

	delete this->Header;
	this->Header = 0;

	this->uiImageBufferSize = 0;
	delete []this->lpImageData;
	this->lpImageData= 0;

	this->uiThumbnailBufferSize = 0;
	delete []this->lpThumbnailImageData;
	this->lpThumbnailImageData = 0;
}

vlBool CVTFFile::IsPowerOfTwo(vlUInt uiSize)
{
	return uiSize > 0 && (uiSize & (uiSize - 1)) == 0;
}

vlBool CVTFFile::IsMultipleOfFour(vlUInt uiSize)
{
	return uiSize >= 4 && ( uiSize % 4 == 0 );
}

vlUInt CVTFFile::NearestMultipleOfFour(vlUInt uiSize)
{
	if (uiSize < 4)
	{
		return 4;
	}

	if (this->IsMultipleOfFour(uiSize))
	{
		return uiSize;
	}
	else
	{
		vlUInt uiSizeMod = uiSize % 4;
		return uiSizeMod < 3 ? uiSize - uiSizeMod : uiSize + 1;
	}
}

vlUInt CVTFFile::NextPowerOfTwo(vlUInt uiSize)
{
	if(uiSize == 0)
	{
		return 1;
	}

	if(this->IsPowerOfTwo(uiSize))
	{
		return uiSize;
	}

	uiSize--;
	for(vlUInt i = 1; i <= sizeof(vlUInt) * 4; i <<= 1)
	{
		uiSize = uiSize | (uiSize >> i);
	}
	uiSize++;

	return uiSize;
}

//
// IsLoaded()
// Returns true if a image has been created or loaded.  Use GetHasImage()
// and GetHasThumbnail() to determine if any image data is associated with
// the image or if it was a header only load operation.
//
vlBool CVTFFile::IsLoaded() const
{
	return this->Header != 0;
}

vlBool CVTFFile::Load(const vlChar *cFileName, vlBool bHeaderOnly)
{
	auto cfr = IO::Readers::CFileReader(cFileName);
	return this->Load(&cfr, bHeaderOnly);
}

vlBool CVTFFile::Load(const vlVoid *lpData, vlUInt uiBufferSize, vlBool bHeaderOnly)
{
	auto cmr = IO::Readers::CMemoryReader(lpData, uiBufferSize);
	return this->Load(&cmr, bHeaderOnly);
}

vlBool CVTFFile::Load(vlVoid *pUserData, vlBool bHeaderOnly)
{
	auto cpr = IO::Readers::CProcReader(pUserData);
	return this->Load(&cpr, bHeaderOnly);
}

vlBool CVTFFile::Save(const vlChar *cFileName) const
{
	auto cfw = IO::Writers::CFileWriter(cFileName);
	return this->Save(&cfw);
}

vlBool CVTFFile::Save(vlVoid *lpData, vlUInt uiBufferSize, vlUInt &uiSize) const
{
	uiSize = 0;

	IO::Writers::CMemoryWriter MemoryWriter = IO::Writers::CMemoryWriter(lpData, uiBufferSize);

	vlBool bResult = this->Save(&MemoryWriter);

	uiSize = MemoryWriter.GetStreamSize();

	return bResult;
}

vlBool CVTFFile::Save(vlVoid *pUserData) const
{
	auto cpw = IO::Writers::CProcWriter(pUserData);
	return this->Save(&cpw);
}

// -----------------------------------------------------------------------------------
// vlBool Load(IO::Readers::IReader *Reader, vlBool bHeaderOnly)
//
// Loads a VTF file from a stream into memory.
// Reader - The stream to read from.
// bHeaderOnly - only read in the header if true (dont allocate and read image data in)
// ------------------------------------------------------------------------------------
vlBool CVTFFile::Load(IO::Readers::IReader *Reader, vlBool bHeaderOnly)
{
	this->Destroy();

	try
	{
		if(!Reader->Open())
			throw 0;

		// Get the size of the .vtf file.
		vlUInt uiFileSize = Reader->GetStreamSize();

		// Check we at least have enough bytes for a header.
		if(uiFileSize < sizeof(SVTFFileHeader))
		{
			LastError.Set("File is corrupt; file to small for it's header.");
			throw 0;
		}

		SVTFFileHeader FileHeader;

		// read the file header
		memset(&FileHeader, 0, sizeof(SVTFFileHeader));
		if(Reader->Read(&FileHeader, sizeof(SVTFFileHeader)) != sizeof(SVTFFileHeader))
		{
			throw 0;
		}

		if(memcmp(FileHeader.TypeString, "VTF\0", 4) != 0)
		{
			LastError.Set("File signature does not match 'VTF'.");
			throw 0;
		}

		if(FileHeader.Version[0] != VTF_MAJOR_VERSION || (FileHeader.Version[1] < 0 || FileHeader.Version[1] > VTF_MINOR_VERSION))
		{
			LastError.SetFormatted("File version %u.%u does not match %d.%d to %d.%d.", FileHeader.Version[0], FileHeader.Version[1], VTF_MAJOR_VERSION, 0, VTF_MAJOR_VERSION, VTF_MINOR_VERSION);
			throw 0;
		}

		if(FileHeader.HeaderSize > sizeof(SVTFHeader))
		{
			LastError.SetFormatted("File header size %d B is larger than the %d B maximum expected.", FileHeader.HeaderSize, sizeof(SVTFHeader));
			throw 0;
		}

		Reader->Seek(0, FILE_BEGIN);

		this->Header = new SVTFHeader;
		memset(this->Header, 0, sizeof(SVTFHeader));

		// read the header
		if(Reader->Read(this->Header, FileHeader.HeaderSize) != FileHeader.HeaderSize)
		{
			throw 0;
		}

		if(this->Header->Version[0] < VTF_MAJOR_VERSION || (this->Header->Version[0] == VTF_MAJOR_VERSION && this->Header->Version[1] < VTF_MINOR_VERSION_MIN_VOLUME))
		{
			// set depth if version is lower than 7.2
			this->Header->Depth = 1;
		}

		if(!this->GetSupportsResources())
		{
			// set resource count if version is lower than 7.3
			this->Header->ResourceCount = 0;
		}

		// if we just want the header loaded, bail here
		if(bHeaderOnly)
		{
			Reader->Close();
			return vlTrue;
		}

		// work out how big out buffers need to be
		this->uiImageBufferSize = this->ComputeImageSize(this->Header->Width, this->Header->Height, this->Header->Depth, this->Header->MipCount, this->Header->ImageFormat) * this->GetFaceCount() * this->GetFrameCount();

		if(this->Header->LowResImageFormat != IMAGE_FORMAT_NONE)
		{
			this->uiThumbnailBufferSize = this->ComputeImageSize(this->Header->LowResImageWidth, this->Header->LowResImageHeight, 1, this->Header->LowResImageFormat);
		}
		else
		{
			this->uiThumbnailBufferSize = 0;
		}

		// read the resource directory if version > 7.3
		vlUInt uiThumbnailBufferOffset = 0, uiImageDataOffset = 0;
		if(this->Header->ResourceCount)
		{
			if(this->Header->ResourceCount > VTF_RSRC_MAX_DICTIONARY_ENTRIES)
			{
				LastError.SetFormatted("File may be corrupt; directory length %u exceeds maximum dictionary length of %u.", this->Header->ResourceCount, VTF_RSRC_MAX_DICTIONARY_ENTRIES);
				throw 0;
			}

			for(vlUInt i = 0; i < this->Header->ResourceCount; i++)
			{
				switch(this->Header->Resources[i].Type)
				{
				case VTF_LEGACY_RSRC_LOW_RES_IMAGE:
					if(this->Header->LowResImageFormat == IMAGE_FORMAT_NONE)
					{
						LastError.Set("File may be corrupt; unexpected low resolution image directory entry.");
						throw 0;
					}
					if(uiThumbnailBufferOffset != 0)
					{
						LastError.Set("File may be corrupt; multiple low resolution image directory entries.");
						throw 0;
					}
					uiThumbnailBufferOffset = this->Header->Resources[i].Data;
					break;
				case VTF_LEGACY_RSRC_IMAGE:
					if(uiImageDataOffset != 0)
					{
						LastError.Set("File may be corrupt; multiple image directory entries.");
						throw 0;
					}
					uiImageDataOffset = this->Header->Resources[i].Data;
					break;
				default:
					if((this->Header->Resources[i].Flags & RSRCF_HAS_NO_DATA_CHUNK) == 0)
					{
						if(this->Header->Resources[i].Data + sizeof(vlUInt) > uiFileSize)
						{
							LastError.Set("File may be corrupt; file to small for it's resource data.");
							throw 0;
						}

						vlUInt uiSize = 0;
						Reader->Seek(this->Header->Resources[i].Data, FILE_BEGIN);
						if(Reader->Read(&uiSize, sizeof(vlUInt)) != sizeof(vlUInt))
						{
							throw 0;
						}

						if(this->Header->Resources[i].Data + sizeof(vlUInt) + uiSize > uiFileSize)
						{
							LastError.Set("File may be corrupt; file to small for it's resource data.");
							throw 0;
						}

						this->Header->Data[i].Size = uiSize;
						this->Header->Data[i].Data = new vlByte[uiSize];
						if(Reader->Read(this->Header->Data[i].Data, uiSize) != uiSize)
						{
							throw 0;
						}
					}
					break;
				}
			}
		}
		else
		{
			uiThumbnailBufferOffset = this->Header->HeaderSize;
			uiImageDataOffset = uiThumbnailBufferOffset + this->uiThumbnailBufferSize;
		}
		
		// sanity check
		// headersize + lowbuffersize + buffersize *should* equal the filesize
		if(this->Header->HeaderSize > uiFileSize || uiThumbnailBufferOffset + this->uiThumbnailBufferSize > uiFileSize || uiImageDataOffset + this->uiImageBufferSize > uiFileSize)
		{
			LastError.Set("File may be corrupt; file to small for it's image data.");
			throw 0;
		}

		if(uiThumbnailBufferOffset == 0)
		{
			this->Header->LowResImageFormat = IMAGE_FORMAT_NONE;
		}

		// assuming all is well, size our data buffers
		if(this->Header->LowResImageFormat != IMAGE_FORMAT_NONE)
		{
			this->lpThumbnailImageData = new vlByte[this->uiThumbnailBufferSize];

			// load the low res data
			Reader->Seek(uiThumbnailBufferOffset, FILE_BEGIN);
			if(Reader->Read(this->lpThumbnailImageData, this->uiThumbnailBufferSize) != this->uiThumbnailBufferSize)
			{
				throw 0;
			}
		}

		if(uiImageDataOffset == 0)
		{
			this->Header->ImageFormat = IMAGE_FORMAT_NONE;
		}

		if(this->Header->ImageFormat != IMAGE_FORMAT_NONE)
		{
			this->lpImageData = new vlByte[this->uiImageBufferSize];

			// load the high-res data
			Reader->Seek(uiImageDataOffset, FILE_BEGIN);
			if(Reader->Read(this->lpImageData, this->uiImageBufferSize) != this->uiImageBufferSize)
			{
				throw 0;
			}
		}

		// Fixup resource offsets for writing.
		this->ComputeResources();
	}
	catch(...)
	{
		Reader->Close();

		this->Destroy();

		return vlFalse;
	}

	Reader->Close();

	return vlTrue;
}

//
// Save()
// Saves the current image.  Basic format checking is done.
//
vlBool CVTFFile::Save(IO::Writers::IWriter *Writer) const
{
	if(!this->IsLoaded() || !this->GetHasImage())
	{
		LastError.Set("No image to save.");
		return vlFalse;
	}

	// ToDo: Check if the image buffer is ok.
	//       Check flags and other header values.

	try
	{
		if(!Writer->Open())
			throw 0;

		// Write the header.
		if(Writer->Write(this->Header, this->Header->HeaderSize) != this->Header->HeaderSize)
		{
			throw 0;
		}

		if(this->GetSupportsResources())
		{
			for(vlUInt i = 0; i < this->Header->ResourceCount; i++)
			{
				switch(this->Header->Resources[i].Type)
				{
				case VTF_LEGACY_RSRC_LOW_RES_IMAGE:
					if(Writer->Write(this->lpThumbnailImageData, this->uiThumbnailBufferSize) != this->uiThumbnailBufferSize)
					{
						throw 0;
					}
					break;
				case VTF_LEGACY_RSRC_IMAGE:
					if(Writer->Write(this->lpImageData, this->uiImageBufferSize) != this->uiImageBufferSize)
					{
						throw 0;
					}
					break;
				default:
					if((this->Header->Resources[i].Flags & RSRCF_HAS_NO_DATA_CHUNK) == 0)
					{
						if(Writer->Write(&this->Header->Data[i].Size, sizeof(vlUInt)) != sizeof(vlUInt))
						{
							throw 0;
						}

						if(Writer->Write(this->Header->Data[i].Data, this->Header->Data[i].Size) != this->Header->Data[i].Size)
						{
							throw 0;
						}
					}
				}
			}
		}
		else
		{
			if(this->Header->LowResImageFormat != IMAGE_FORMAT_NONE)
			{
				// write the thumbnail image data
				if(Writer->Write(this->lpThumbnailImageData, this->uiThumbnailBufferSize) != this->uiThumbnailBufferSize)
				{
					throw 0;
				}
			}

			if(this->Header->ImageFormat != IMAGE_FORMAT_NONE)
			{
				// write the image data
				if(Writer->Write(this->lpImageData, this->uiImageBufferSize) != this->uiImageBufferSize)
				{
					throw 0;
				}
			}
		}
	}
	catch(...)
	{
		Writer->Close();

		return vlFalse;
	}

	Writer->Close();

	return vlTrue;
}

//
// GetHasImage()
// A image can be loaded as header only, this function indicates weather
// image data was loaded or not.
//
vlBool CVTFFile::GetHasImage() const
{
	if(!this->IsLoaded())
		return vlFalse;

	return this->lpImageData != 0;
}

//
// GetMajorVersion()
// Returns the size of the VTF file major version number.
//
vlUInt CVTFFile::GetMajorVersion() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->Version[0];
}

//
// GetMinorVersion()
// Returns the size of the VTF file minor version number.
//
vlUInt CVTFFile::GetMinorVersion() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->Version[1];
}

vlVoid CVTFFile::SetMinorVersion(vlUInt version)
{
	if(!this->IsLoaded())
		return;

	if (this->Header->Version[1] == version)
		return;

	vlUInt oldMinVersion = this->GetMinorVersion();
	this->Header->Version[1] = version;

	if(version >= 3 && oldMinVersion < 3)
	{
		// This is for VTFs that are below 7.3 as they don't have resources, so they need to be set and computed.
		// Set resource count to 2 and set their type. First is thumbnail data, second is the image.
		this->Header->ResourceCount = 2;
		this->Header->Resources[0].Type = 1;
		this->Header->Resources[1].Type = 48;
		this->ComputeResources();
	}
	else {
		// Correct the image when going from 7.3+ to 7.2 or lower.
		this->ComputeResources();
	}
}

//
// ComputeResources()
// Computes header VTF directory resources.
//
vlVoid CVTFFile::ComputeResources()
{
	if(!this->IsLoaded())
		return;

	// Correct resource count.
	if(!this->GetSupportsResources())
	{
		this->Header->ResourceCount = 0;
	}

	// Correct header size.
	STATIC_ASSERT(VTF_MAJOR_VERSION == 7, "HeaderSize needs calculation for new major version.");
	STATIC_ASSERT(VTF_MINOR_VERSION == 5, "HeaderSize needs calculation for new minor version.");
	if(this->Header->Version[0] == 7)
	{
		switch(this->Header->Version[1])
		{
		case 0:
			this->Header->HeaderSize = sizeof(SVTFHeader_70_A);
			break;
		case 1:
			this->Header->HeaderSize = sizeof(SVTFHeader_71_A);
			break;
		case 2:
			this->Header->HeaderSize = sizeof(SVTFHeader_72_A);
			break;
		case 3:
			this->Header->HeaderSize = sizeof(SVTFHeader_73_A) + this->Header->ResourceCount * sizeof(SVTFResource);
			break;
		case 4:
			this->Header->HeaderSize = sizeof(SVTFHeader_74_A) + this->Header->ResourceCount * sizeof(SVTFResource);
			break;
		case 5:
			this->Header->HeaderSize = sizeof(SVTFHeader_75_A) + this->Header->ResourceCount * sizeof(SVTFResource);
			break;
		}
	}

	// Correct resource offsets.
	vlUInt uiOffset = this->Header->HeaderSize;
	for(vlUInt i = 0; i < this->Header->ResourceCount; i++)
	{
		switch(this->Header->Resources[i].Type)
		{
		case VTF_LEGACY_RSRC_LOW_RES_IMAGE:
			this->Header->Resources[i].Data = uiOffset;
			uiOffset += this->uiThumbnailBufferSize;
			break;
		case VTF_LEGACY_RSRC_IMAGE:
			this->Header->Resources[i].Data = uiOffset;
			uiOffset += this->uiImageBufferSize;
			break;
		default:
			if((this->Header->Resources[i].Flags & RSRCF_HAS_NO_DATA_CHUNK) == 0)
			{
				this->Header->Resources[i].Data = uiOffset;
				uiOffset += sizeof(vlUInt) + this->Header->Data[i].Size;
			}
			break;
		}
	}
}

//
// GetSize()
// Returns the size of the VTF file in bytes.
//
vlUInt CVTFFile::GetSize() const
{
	if(!this->IsLoaded())
		return 0;

	vlUInt uiResourceSize = 0;
	if(this->GetSupportsResources())
	{
		for(vlUInt i = 0; i < this->Header->ResourceCount; i++)
		{
			switch(this->Header->Resources[i].Type)
			{
			case VTF_LEGACY_RSRC_LOW_RES_IMAGE:
			case VTF_LEGACY_RSRC_IMAGE:
				break;
			default:
				if((this->Header->Resources[i].Flags & RSRCF_HAS_NO_DATA_CHUNK) == 0)
				{
					uiResourceSize += sizeof(vlUInt) + this->Header->Data[i].Size;
				}
				break;
			}
		}
	}

	return this->Header->HeaderSize + this->uiThumbnailBufferSize + this->uiImageBufferSize + uiResourceSize;
}

//
// GetWidth()
// Gets the width of the largest level mipmap.
//
vlUInt CVTFFile::GetWidth() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->Width;
}

//
// GetHeight()
// Gets the height of the largest level mipmap.
//
vlUInt CVTFFile::GetHeight() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->Height;
}

//
// GetDepth()
// Gets the depth of the largest level mipmap.
//
vlUInt CVTFFile::GetDepth() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->Depth;
}

//
// GetFrameCount()
// Gets the number of frames the image has.  All images have at least 1 frame.
//
vlUInt CVTFFile::GetFrameCount() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->Frames;
}

//---------------------------------------------------------------------------------
// GetFaceCount()
//
// Returns the number of faces in the texture based on the status of the header
// flags. Cubemaps have 6 or 7 faces, others just 1.
//---------------------------------------------------------------------------------
vlUInt CVTFFile::GetFaceCount() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->Flags & TEXTUREFLAGS_ENVMAP ? (this->Header->StartFrame != 0xffff && this->Header->Version[1] < VTF_MINOR_VERSION_MIN_NO_SPHERE_MAP ? CUBEMAP_FACE_COUNT : CUBEMAP_FACE_COUNT - 1) : 1;
}

//
// GetMipmapCount()
// Gets the number of mipmaps the image has.
//
vlUInt CVTFFile::GetMipmapCount() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->MipCount;
}

//
// GetStartFrame()
// Gets the first frame in the animation sequence.  If the image is
// an enviroment map and 0xffff is returned, the enviroment map has
// no sphere map.
//
vlUInt CVTFFile::GetStartFrame() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->StartFrame;
}

//
// SetStartFrame()
// Sets the first frame in the animation sequence.
//
vlVoid CVTFFile::SetStartFrame(vlUInt uiStartFrame)
{
	if(!this->IsLoaded())
		return;

	// Note: Valve informs us that animated enviroment maps ARE possible.
	// The StartFrame MAY be valid but there is the issue of the enviroment
	// maps without sphere maps.  This is trivial...

	// Don't let the user set the start frame of an enviroment map.
	if(this->Header->Flags & TEXTUREFLAGS_ENVMAP)
	{
		return;
	}

	if(uiStartFrame >= (vlUInt)this->Header->Frames)
	{
		uiStartFrame = (vlUInt)this->Header->Frames - 1;
	}

	this->Header->StartFrame = (vlUShort)uiStartFrame;
}

//
// GetFlags()
// Gets the flags associated with the image.  These flags
// are stored in the VTFImageFlag enumeration.
//
vlUInt CVTFFile::GetFlags() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->Flags;
}

// SetFlags()
// Sets the flags associated with the image.  These flags
// are stored in the VTFImageFlag enumeration.
//
vlVoid CVTFFile::SetFlags(vlUInt uiFlags)
{
	if(!this->IsLoaded())
		return;

	// Don't let the user set flags critical to the image's format.
	//if(this->Header->Version[0] < VTF_MAJOR_VERSION || (this->Header->Version[0] == VTF_MAJOR_VERSION && this->Header->Version[1] <= VTF_MINOR_VERSION_MIN_RESOURCE))
	//{
	//	if(this->Header->Flags & TEXTUREFLAGS_DEPRECATED_NOCOMPRESS)
	//		uiFlags |= TEXTUREFLAGS_DEPRECATED_NOCOMPRESS;
	//	else
	//		uiFlags &= ~TEXTUREFLAGS_DEPRECATED_NOCOMPRESS;
	//}

	if(this->Header->Flags & TEXTUREFLAGS_EIGHTBITALPHA)
		uiFlags |= TEXTUREFLAGS_EIGHTBITALPHA;
	else
		uiFlags &= ~TEXTUREFLAGS_EIGHTBITALPHA;

	if(this->Header->Flags & TEXTUREFLAGS_ONEBITALPHA)
		uiFlags |= TEXTUREFLAGS_ONEBITALPHA;
	else
		uiFlags &= ~TEXTUREFLAGS_ONEBITALPHA;

	if(this->Header->Flags & TEXTUREFLAGS_ENVMAP)
		uiFlags |= TEXTUREFLAGS_ENVMAP;
	else
		uiFlags &= ~TEXTUREFLAGS_ENVMAP;

	this->Header->Flags = uiFlags;
}

//
// GetFlag()
// Gets the status of the specified flag in the image.
//
vlBool CVTFFile::GetFlag(VTFImageFlag ImageFlag) const
{
	if(!this->IsLoaded())
		return vlFalse;

	return (this->Header->Flags & ImageFlag) != 0;
}

//
// SetFlag()
// Sets the flag ImageFlag to bState (set or not set).  Flags critical
// to the image's format cannot be set.
//
vlVoid CVTFFile::SetFlag(VTFImageFlag ImageFlag, vlBool bState)
{
	if(!this->IsLoaded())
		return;

	//if(this->Header->Version[0] < VTF_MAJOR_VERSION || (this->Header->Version[0] == VTF_MAJOR_VERSION && this->Header->Version[1] <= VTF_MINOR_VERSION_MIN_RESOURCE))
	//{
	//	if(ImageFlag == TEXTUREFLAGS_DEPRECATED_NOCOMPRESS)
	//	{
	//		return;
	//	}
	//}

	// Don't let the user set flags critical to the image's format.
	if(ImageFlag == TEXTUREFLAGS_ONEBITALPHA || ImageFlag == TEXTUREFLAGS_EIGHTBITALPHA || ImageFlag == TEXTUREFLAGS_ENVMAP)
	{
		return;
	}

	if(bState)
	{
		this->Header->Flags |= ImageFlag;
	}
	else
	{
		this->Header->Flags &= ~ImageFlag;
	}
}

//
// GetBumpmapScale()
// Gets the bumpmap scale of the image.
//
vlSingle CVTFFile::GetBumpmapScale() const
{
	if(!this->IsLoaded())
		return 0.0f;

	return this->Header->BumpScale;
}

//
// SetBumpmapScale()
// Sets the bumpmap scale of the image.
//
vlVoid CVTFFile::SetBumpmapScale(vlSingle sBumpmapScale)
{
	if(!this->IsLoaded())
		return;

	this->Header->BumpScale = sBumpmapScale;
}

//
// GetReflectivity()
// Gets the reflectivity of the image.
//
vlVoid CVTFFile::GetReflectivity(vlSingle &sX, vlSingle &sY, vlSingle &sZ) const
{
	if(!this->IsLoaded())
		return;

	sX = this->Header->Reflectivity[0];
	sY = this->Header->Reflectivity[1];
	sZ = this->Header->Reflectivity[2];
}

//
// SetReflectivity()
// Sets the reflectivity of the image.
//
vlVoid CVTFFile::SetReflectivity(vlSingle sX, vlSingle sY, vlSingle sZ)
{
	if(!this->IsLoaded())
		return;

	this->Header->Reflectivity[0] = sX;
	this->Header->Reflectivity[1] = sY;
	this->Header->Reflectivity[2] = sZ;
}

//
// GetFormat()
// Gets the format of the image.
//
VTFImageFormat CVTFFile::GetFormat() const
{
	if(!this->IsLoaded())
		return IMAGE_FORMAT_NONE;

	return this->Header->ImageFormat;
}

//
// GetData()
// Gets the image data of the specified frame, face and mipmap in the format
// of the image.
//
vlByte *CVTFFile::GetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel) const
{
	if(!this->IsLoaded())
		return 0;

	return this->lpImageData + this->ComputeDataOffset(uiFrame, uiFace, uiSlice, uiMipmapLevel, this->Header->ImageFormat);
}

//
// SetData()
// Sets the image data of the specified frame, face and mipmap.  Image data
// must be in the format of the image.
//
vlVoid CVTFFile::SetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel, vlByte *lpData)
{
	if(!this->IsLoaded() || this->lpImageData == 0)
		return;

	memcpy(this->lpImageData + this->ComputeDataOffset(uiFrame, uiFace, uiSlice, uiMipmapLevel, this->Header->ImageFormat), lpData, CVTFFile::ComputeMipmapSize(this->Header->Width, this->Header->Height, 1, uiMipmapLevel, this->Header->ImageFormat));
}

//
// GetHasThumbnail()
// A image does not need a thumbnail, this function returns wheather
// the image has a thumbnail or not.
//
vlBool CVTFFile::GetHasThumbnail() const
{
	if(!this->IsLoaded())
		return vlFalse;

	return this->Header->LowResImageFormat != IMAGE_FORMAT_NONE;
}

//
// GetThumbnailWidth()
// Gets the width of the thumbnail image.
//
vlUInt CVTFFile::GetThumbnailWidth() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->LowResImageWidth;
}

//
// GetThumbnailHeight()
// Sets the height of the thumbnail image.
//
vlUInt CVTFFile::GetThumbnailHeight() const
{
	if(!this->IsLoaded())
		return 0;

	return this->Header->LowResImageHeight;
}

//
// GetThumbnailFormat()
// Gets the format of the thumbnail image.
//
VTFImageFormat CVTFFile::GetThumbnailFormat() const
{
	if(!this->IsLoaded())
		return IMAGE_FORMAT_NONE;

	return this->Header->LowResImageFormat;
}

//
// GetThumbnailData()
// Gets the thumbnail image data in the format of the image.  This "thumbnail"
// image is a small same of the original image used by the engine for color sampling
// when you hit the wall with a crowbar etc.
//
vlByte *CVTFFile::GetThumbnailData() const
{
	if(!this->IsLoaded())
		return 0;

	return this->lpThumbnailImageData;
}

//
// SetThumbnailData()
// Sets the thumbnail image data.  Image data must be in the format of the image.
//
vlVoid CVTFFile::SetThumbnailData(vlByte *lpData)
{
	if(!this->IsLoaded() || this->lpThumbnailImageData == 0)
		return;

	memcpy(this->lpThumbnailImageData, lpData, this->uiThumbnailBufferSize/*CVTFFile::ComputeImageSize(this->Header->LowResImageWidth, this->Header->LowResImageHeight, this->Header->LowResImageFormat)*/);
}

vlBool CVTFFile::GetSupportsResources() const
{
	if(!this->IsLoaded())
		return vlFalse;

	return this->Header->Version[0] > VTF_MAJOR_VERSION || (this->Header->Version[0] == VTF_MAJOR_VERSION && this->Header->Version[1] >= VTF_MINOR_VERSION_MIN_RESOURCE);
}

vlUInt CVTFFile::GetResourceCount() const
{
	if(!this->GetSupportsResources())
		return 0;

	return this->Header->ResourceCount;
}

vlUInt CVTFFile::GetResourceType(vlUInt uiIndex) const
{
	if(!this->GetSupportsResources())
		return 0;

	if(uiIndex >= this->Header->ResourceCount)
		return 0;

	return this->Header->Resources[uiIndex].Type;
}

vlBool CVTFFile::GetHasResource(vlUInt uiType) const
{
	if(!this->GetSupportsResources())
		return vlFalse;

	for(vlUInt i = 0; i < this->Header->ResourceCount; i++)
	{
		if(this->Header->Resources[i].Type == uiType)
		{
			return vlTrue;
		}
	}

	return vlFalse;
}

vlVoid *CVTFFile::GetResourceData(vlUInt uiType, vlUInt &uiSize) const
{
	if(this->IsLoaded())
	{
		if(this->GetSupportsResources())
		{
			switch(uiType)
			{
			case VTF_LEGACY_RSRC_LOW_RES_IMAGE:
				uiSize = this->uiThumbnailBufferSize;
				return this->lpThumbnailImageData;
				break;
			case VTF_LEGACY_RSRC_IMAGE:
				uiSize = this->uiImageBufferSize;
				return this->lpImageData;
				break;
			default:
				for(vlUInt i = 0; i < this->Header->ResourceCount; i++)
				{
					if(this->Header->Resources[i].Type == uiType)
					{
						if(this->Header->Resources[i].Flags & RSRCF_HAS_NO_DATA_CHUNK)
						{
							uiSize = sizeof(vlUInt);
							return &this->Header->Resources[i].Data;
						}
						else
						{
							uiSize = this->Header->Data[i].Size;
							return this->Header->Data[i].Data;
						}
					}
				}
				break;
			}
		}
		else
		{
			LastError.Set("Resources require VTF file version v7.3 and up.");
		}
	}

	uiSize = 0;
	return 0;
}

vlVoid *CVTFFile::SetResourceData(vlUInt uiType, vlUInt uiSize, vlVoid *lpData)
{
	if(this->IsLoaded())
	{
		if(this->GetSupportsResources())
		{
			switch(uiType)
			{
			case VTF_LEGACY_RSRC_LOW_RES_IMAGE:
				LastError.Set("Low resolution image resource cannot be modified through resource interface.");
				break;
			case VTF_LEGACY_RSRC_IMAGE:
				LastError.Set("Image resource cannot be modified through resource interface.");
				break;
			default:
				for(vlUInt i = 0; i < this->Header->ResourceCount; i++)
				{
					if(this->Header->Resources[i].Type == uiType)
					{
						if(uiSize == 0)
						{
							delete []this->Header->Data[i].Data;
							for(vlUInt j = i + 1; j < this->Header->ResourceCount; j++)
							{
								this->Header->Resources[j - 1] = this->Header->Resources[j];
								this->Header->Data[j - 1] = this->Header->Data[j];
							}
							this->Header->ResourceCount--;
							this->ComputeResources();
							return 0;
						}
						else
						{
							if(this->Header->Resources[i].Flags & RSRCF_HAS_NO_DATA_CHUNK)
							{
								if(uiSize != sizeof(vlUInt))
								{
									LastError.Set("Resources with no data chunk must have size 4.");
									return 0;
								}
								if(lpData == 0)
								{
									this->Header->Resources[i].Data= 0;
								}
								else if(&this->Header->Resources[i].Data != lpData)
								{
									this->Header->Resources[i].Data = *(vlUInt *)lpData;
								}
								return &this->Header->Resources[i].Data;
							}
							else
							{
								if(this->Header->Data[i].Size != uiSize)
								{
									delete []this->Header->Data[i].Data;
									this->Header->Data[i].Size = uiSize;
									this->Header->Data[i].Data = new vlByte[uiSize];
									this->ComputeResources();
								}
								if(lpData == 0)
								{
									memset(this->Header->Data[i].Data, 0, this->Header->Data[i].Size);
								}
								else if(this->Header->Data[i].Data != lpData)
								{
									memcpy(this->Header->Data[i].Data, lpData, this->Header->Data[i].Size);
								}
								return this->Header->Data[i].Data;
							}
						}
					}
				}

				// Resource not found.
				if(uiSize != 0)
				{
					if(this->Header->ResourceCount == VTF_RSRC_MAX_DICTIONARY_ENTRIES)
					{
						LastError.SetFormatted("Maximum directory entry count %u reached.", VTF_RSRC_MAX_DICTIONARY_ENTRIES);
						return 0;
					}

					vlUInt uiIndex = this->Header->ResourceCount;

					this->Header->Resources[uiIndex].Type = uiType;
					this->Header->Resources[uiIndex].Data = 0;

					this->Header->Data[uiIndex].Size = 0;
					this->Header->Data[uiIndex].Data = 0;

					if(this->Header->Resources[uiIndex].Flags & RSRCF_HAS_NO_DATA_CHUNK)
					{
						if(uiSize != sizeof(vlUInt))
						{
							LastError.Set("Resources with no data chunk must have size 4.");
							return 0;
						}
						if(lpData != 0)
						{
							this->Header->Resources[uiIndex].Data = *(vlUInt *)lpData;
						}
						else
						{
							this->Header->Resources[uiIndex].Data = 0;
						}
						this->Header->ResourceCount++;
						this->ComputeResources();
						return &this->Header->Resources[uiIndex].Data;
					}
					else
					{
						this->Header->Data[uiIndex].Size = uiSize;
						this->Header->Data[uiIndex].Data = new vlByte[uiSize];
						if(lpData != 0)
						{
							memcpy(this->Header->Data[uiIndex].Data, lpData, this->Header->Data[uiIndex].Size);
						}
						else
						{
							memset(this->Header->Data[uiIndex].Data, 0, this->Header->Data[uiIndex].Size);
						}
						this->Header->ResourceCount++;
						this->ComputeResources();
						return this->Header->Data[uiIndex].Data;
					}
				}
				break;
			}
		}
		else
		{
			LastError.Set("Resources require VTF file version v7.3 and up.");
		}
	}

	return 0;
}

//
// GenerateMipmaps()
// Generate mipmaps from the first mipmap level.
//
vlBool CVTFFile::GenerateMipmaps(VTFMipmapFilter MipmapFilter, vlBool bSRGB)
{
	if(!this->IsLoaded())
		return vlFalse;

	if(this->Header->MipCount == 0)
		return vlTrue;

	vlUInt uiFrameCount = this->GetFrameCount();
	vlUInt uiFaceCount = this->GetFaceCount();

	for(vlUInt i = 0; i < uiFrameCount; i++)
	{
		for(vlUInt j = 0; j < uiFaceCount; j++)
		{
			if(!this->GenerateMipmaps(i, j, MipmapFilter, bSRGB))
			{
				return vlFalse;
			}
		}
	}

	return vlTrue;
}

//
// GenerateMipmaps()
// Generate mipmaps from the first mipmap level of the specified frame and face.
//
vlBool CVTFFile::GenerateMipmaps(vlUInt uiFace, vlUInt uiFrame, VTFMipmapFilter MipmapFilter, vlBool bSRGB)
{
	if(!this->IsLoaded())
		return vlFalse;

#ifdef USE_NVDXT
	if(this->lpImageData == 0)
	{
		LastError.Set("No image data to generate mipmaps from.");
		return vlFalse;
	}

	if(this->Header->Depth > 1)
	{
		LastError.Set("Mipmap generation for depth textures is not supported.");
		return vlFalse;
	}

	assert(MipmapFilter >= 0 && MipmapFilter < MIPMAP_FILTER_COUNT);

	if(this->Header->MipCount == 1)
	{
		return vlTrue;
	}

	// The mipmap callback NVMipmapCallback() will call ConvertFromRGBA8888() which will use the
	// NVDXT lib to compress the image data if it is in a DXT format.  This is bad!!!  The
	// nvDXTcompressRGBA() function only seems to be able to handle one call at a time and since
	// we made a call for the mipmap generation the thing will crash.  Hence all this DXT nonsense.
	// This took me a LONG time to figure out!  Go NVidia docs...
	// Sidenote: this could very well cause problems in multithreaded applications!

	// Get the format to generate mipmaps to.
	VTFImageFormat MipmapImageFormat;
	switch(this->Header->ImageFormat)
	{
	case IMAGE_FORMAT_DXT1:
	case IMAGE_FORMAT_DXT1_ONEBITALPHA:
	case IMAGE_FORMAT_DXT3:
	case IMAGE_FORMAT_DXT5:
		MipmapImageFormat = this->Header->ImageFormat;
		break;
	default:
		MipmapImageFormat = IMAGE_FORMAT_RGBA8888;
		break;
	}

	nvCompressionOptions Options = nvCompressionOptions();

	SNVCompressionUserData UserData = SNVCompressionUserData(this, uiFace, uiFrame, 0, MipmapImageFormat);

	// Don't generate mipmaps.
	Options.mipMapGeneration = kGenerateMipMaps;

	Options.mipFilterType = (nvMipFilterTypes)MipmapFilter;

	// Set the format.
	switch(uiDXTQuality)
	{
	case DXT_QUALITY_LOW:
		Options.quality = kQualityFastest;
		break;
	case DXT_QUALITY_MEDIUM:
		Options.quality = kQualityNormal;
		break;
	case DXT_QUALITY_HIGH:
		Options.quality = kQualityProduction;
		break;
	case DXT_QUALITY_HIGHEST:
		Options.quality = kQualityHighest;
		break;
	}
	switch(MipmapImageFormat)
	{
	case IMAGE_FORMAT_DXT1:
		Options.textureFormat = kDXT1;
		Options.bForceDXT1FourColors = true;
		break;
	case IMAGE_FORMAT_DXT1_ONEBITALPHA:
		Options.bBinaryAlpha = true;
		Options.bForceDXT1FourColors = true;
		Options.textureFormat = kDXT1a;
		break;
	case IMAGE_FORMAT_DXT3:
		Options.textureFormat = kDXT3;
		break;
	case IMAGE_FORMAT_DXT5:
		Options.textureFormat = kDXT5;
		break;
	case IMAGE_FORMAT_RGBA8888:
		Options.textureFormat = k8888;
		Options.bSwapRB = true;
		break;
	}

	if(MipmapImageFormat != IMAGE_FORMAT_RGBA8888)
	{
		// nvDXTcompressRGBA() fails on widths or heights of 1 or 2 so rescale those images.
		if(this->Header->Width < 4)
		{
			Options.rescaleImageType = kRescalePreScale;
			Options.rescaleImageFilter = kMipFilterPoint;
			Options.scaleX = 4.0f;
		}

		if(this->Header->Height < 4)
		{
			Options.rescaleImageType = kRescalePreScale;
			Options.rescaleImageFilter = kMipFilterPoint;
			Options.scaleY = 4.0f;
		}
	}

	// The UserData struct gets passed to our callback.
	Options.user_data = &UserData;

	vlByte *lpImageData = new vlByte[this->ComputeImageSize(this->Header->Width, this->Header->Height, 1, IMAGE_FORMAT_RGBA8888)];
	
	if(!this->ConvertToRGBA8888(this->GetData(uiFace, uiFrame, 0, 0), lpImageData, this->Header->Width, this->Header->Height, this->Header->ImageFormat))
	{
		delete []lpImageData;

		return vlFalse;
	}

	if(!nvDXTCompressWrapper(lpImageData, this->Header->Width, this->Header->Height, &Options, NVWriteCallback))
	{
		delete []lpImageData;

		return vlFalse;
	}

	delete []lpImageData;

	return vlTrue;
#else
	LastError.Set("NVDXT support required for CVTFFile::GenerateMipmaps().");
	return vlFalse;
#endif
}

//
// GenerateThumbnail()
// We should have a mipmap that matches the thumbnail size.  This function finds it and
// copies it over to the mipmap data, converting it if need be.
//
vlBool CVTFFile::GenerateThumbnail(vlBool bSRGB)
{
	if(!this->IsLoaded())
		return vlFalse;

	if(!this->GetHasThumbnail())
	{
		LastError.Set("VTF file does not have a thumbnail.");
		return vlFalse;
	}

	if(this->lpImageData == 0)
	{
		LastError.Set("No image data to generate thumbnail from.");
		return vlFalse;
	}

	// Find a mipmap that matches the size of the thumbnail.
	for(vlUInt i = 0; i < this->Header->MipCount; i++)
	{
		vlUInt uiMipmapWidth, uiMipmapHeight, uiMipmapDepth;
		CVTFFile::ComputeMipmapDimensions(this->Header->Width, this->Header->Height, 1, i, uiMipmapWidth, uiMipmapHeight, uiMipmapDepth);

		if(uiMipmapWidth == (vlUInt)this->Header->LowResImageWidth && uiMipmapHeight == (vlUInt)this->Header->LowResImageHeight)
		{
			// Check if it is the same format (in which case copy it) otherwise convert
			// it to the right format and copy it.
			if(this->Header->ImageFormat == this->Header->LowResImageFormat)
			{
				this->SetThumbnailData(this->GetData(0, 0, 0, i));
			}
			else
			{
				if(!CVTFFile::Convert(this->GetData(0, 0, 0, i), this->GetThumbnailData(), uiMipmapWidth, uiMipmapHeight, this->Header->ImageFormat, this->Header->LowResImageFormat))
				{
					return vlFalse;
				}
			}
			return vlTrue;
		}
	}

	// We don't have a matching mipmap (maybe we have no mipmaps) so generate one.
	vlByte *lpImageData = new vlByte[CVTFFile::ComputeImageSize(this->Header->Width, this->Header->Height, 1, IMAGE_FORMAT_RGBA8888)];
	vlByte *lpThumbnailImageData = new vlByte[CVTFFile::ComputeImageSize(this->Header->LowResImageWidth, this->Header->LowResImageHeight, 1, IMAGE_FORMAT_RGBA8888)];

	if(!CVTFFile::ConvertToRGBA8888(this->GetData(0, 0, 0, 0), lpImageData, this->Header->Width, this->Header->Height, this->Header->ImageFormat))
	{
		delete []lpImageData;
		delete []lpThumbnailImageData;

		return vlFalse;
	}

	if(!CVTFFile::Resize(lpImageData, lpThumbnailImageData, this->Header->Width, this->Header->Height, this->Header->LowResImageWidth, this->Header->LowResImageHeight, MIPMAP_FILTER_CATROM, bSRGB))
	{
		delete []lpImageData;
		delete []lpThumbnailImageData;

		return vlFalse;
	}

	if(!CVTFFile::ConvertFromRGBA8888(lpThumbnailImageData, this->GetThumbnailData(), this->Header->LowResImageWidth, this->Header->LowResImageHeight, this->Header->LowResImageFormat))
	{
		delete []lpImageData;
		delete []lpThumbnailImageData;

		return vlFalse;
	}

	delete []lpImageData;
	delete []lpThumbnailImageData;

	//LastError.Set("VTF file does not have a mipmap that matches the thumbnail size.");
	return vlTrue;
}

//
// GenerateNormalMap()
// Convert the first level mipmap of each frame to a normal map.
//
vlBool CVTFFile::GenerateNormalMap(VTFKernelFilter KernelFilter, VTFHeightConversionMethod HeightConversionMethod, VTFNormalAlphaResult NormalAlphaResult)
{
	if(!this->IsLoaded())
		return vlFalse;

	vlUInt uiFrameCount = this->GetFrameCount();

	for(vlUInt i = 0; i < uiFrameCount; i++)
	{
		if(!this->GenerateNormalMap(i, KernelFilter, HeightConversionMethod, NormalAlphaResult))
		{
			return vlFalse;
		}
	}

	return vlTrue;
}

//
// GenerateNormalMap()
// Convert the first level mipmap of the specified frame to a normal map.
//
vlBool CVTFFile::GenerateNormalMap(vlUInt uiFrame, VTFKernelFilter KernelFilter, VTFHeightConversionMethod HeightConversionMethod, VTFNormalAlphaResult NormalAlphaResult)
{
	if(!this->IsLoaded())
		return vlFalse;

	if(this->Header->Flags & TEXTUREFLAGS_ENVMAP)
	{
		LastError.Set("Image is an enviroment map.");
		return vlFalse;
	}

	if(this->lpImageData == 0)
	{
		LastError.Set("No image data to generate normal map from.");
		return vlFalse;
	}

	vlByte *lpData = this->GetData(0, uiFrame, 0, 0);

	// Will hold frame's converted image data.
	vlByte *lpSource = new vlByte[this->ComputeImageSize(this->Header->Width, this->Header->Height, 1, IMAGE_FORMAT_RGBA8888)];

	// Get the frame's image data.
	if(!this->ConvertToRGBA8888(lpData, lpSource, this->Header->Width, this->Header->Height, this->Header->ImageFormat))
	{
		delete []lpSource;

		return vlFalse;
	}

	// Will hold normal image data.
	//vlByte *lpDest = new vlByte[this->ComputeImageSize(this->Header->Width, this->Header->Height, IMAGE_FORMAT_RGBA8888)];

	//delete []lpSource;

	// Set the frame's image data.
	if(!this->ConvertFromRGBA8888(lpSource/*lpDest*/, lpData, this->Header->Width, this->Header->Height, this->Header->ImageFormat))
	{
		delete []lpSource;	// Moved from above.
		//delete []lpDest;

		return vlFalse;
	}

	delete []lpSource;	// Moved from above.
	//delete []lpDest;

	return vlTrue;
}

// Simple struct for holding face data for SphereMap rendering
// -----------------------------------------------------------
struct SphereMapFace
{
	vlUInt *buf;			// pointer to the address where the image data is.
	Vector u, v, n, o;		// vectors for plane equations
};

// Define our faces and vectors (don't moan about the order!)
// ----------------------------------------------------------
SphereMapFace SFace[6] =
{
	{0, {0, 0, -1}, {0, 1, 0}, {-1, 0, 0}, {-0.5, -0.5, 0.5}},	// left (lf)
	{0, {1, 0, 0}, {0, 1, 0}, {0, 0, -1}, {-0.5, -0.5, -0.5}},	// down (dn) 
	{0, {0, 0, 1}, {0, 1, 0}, {1, 0, 0}, {0.5, -0.5, -0.5}}, 	// right (rt)
	{0, {-1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0.5, -0.5, 0.5}},	// up (up)
	{0, {1, 0, 0}, {0, 0, 1}, {0, 1, 0}, {-0.5, 0.5, -0.5}},	// front (ft)
	{0,	{1, 0, 0}, {0, 0, -1}, {0, -1, 0}, {-0.5, -0.5, 0.5}}	// back (bk)
};

// Normalised pixel colour struct
// ------------------------------
struct NColour
{
	vlSingle r, g, b;
};

//
// GenerateSphereMap()
// Generate a sphere map from the first six faces (the cube map) of an enviroment map.
//
vlBool CVTFFile::GenerateSphereMap()
{
	if(!this->IsLoaded())
		return vlFalse;

	if(!(this->Header->Flags & TEXTUREFLAGS_ENVMAP))
	{
		LastError.Set("Image is not an enviroment map.");
		return vlFalse;
	}

	if(this->Header->StartFrame == 0xffff)
	{
		LastError.Set("Enviroment map does not have a sphere map.");
		return vlFalse;
	}

	if(this->lpImageData == 0)
	{
		LastError.Set("No image data to generate sphere map from.");
		return vlFalse;
	}

	vlUInt uiWidth = (vlUInt)this->Header->Width;
	vlUInt uiHeight = (vlUInt)this->Header->Height;

	// lets go!
	vlByte *lpImageData[6] = { 0, 0, 0, 0, 0, 0 };  					// 6 pointers to memory for our faces.
	vlByte *lpSphereMapData = 0;					// SphereMap buffer 
	vlUInt map[6] = {2, 0, 5, 4, 3, 1};		// used to remap valves face order to my face order.
	vlUInt samples = 4;							// pixel samples for rendering

	vlUInt i, j, x, y, f;
	NColour c{}, texel{}, average{};
	Vector v{}, r{}, p{};
	vlSingle s, t, temp, k;
	 
	// load the faces into the buffers and convert as needed
	for( i = 0; i < 6; i ++)
	{ 
		vlUInt j = map[i];		// Valve face order to my face order map.

		lpImageData[j] = new vlByte[this->ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)]; 
		
		if(!this->ConvertToRGBA8888(this->GetData(0, i, 0, 0), lpImageData[j], uiWidth, uiHeight, this->Header->ImageFormat)) 
		{ 
			for(vlUInt l = 0; l < 6; l++)  
				delete[] lpImageData[l];  
			
			LastError.Set("Could not convert source to RGBA8888 format");
			return vlFalse; 
		} 
		SFace[j].buf = (vlUInt *)lpImageData[j];	// save the address
	}

	// Assuming at this point our faces have loaded fine, create a buffer for the SphereMap
	lpSphereMapData = new vlByte[this->ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)]; 

	// At this point we need to flip 4 of the faces as follows as their "Valve" orientation
	// is different to what the SphereMap rendering code needs.
	// up - flip horizontal
	// rt - flip horizontal
	// ft - flip vertical
	// bk - flip vertical

	this->MirrorImage(lpImageData[0], this->Header->Width, this->Header->Height);
	this->MirrorImage(lpImageData[2], this->Header->Width, this->Header->Height);
	this->MirrorImage(lpImageData[3], this->Header->Width, this->Header->Height);
	this->FlipImage(lpImageData[4], this->Header->Width, this->Header->Height);
	this->FlipImage(lpImageData[5], this->Header->Width, this->Header->Height);
	
	// disable conversion warning
	//#pragma warning(disable: 4244)

	// calculate the average colour for the forward face
	// using just the forward face is quicker and seems fairly
	// consistent with what Valves own SphereMaps look like.
	vlUInt uiAvgR = 0, uiAvgG = 0, uiAvgB = 0;
	vlUInt uiPixelCount = uiWidth * uiHeight;
	
	vlByte *src = lpImageData[3];	// 3 = up or forward face
	vlByte *lpSourceEnd = src + (uiWidth * uiHeight * 4);
	
	for( ; src < lpSourceEnd; src += 4)
	{
		uiAvgR += src[0];
		uiAvgG += src[1];
		uiAvgB += src[2];
	}

	uiAvgR /= uiPixelCount; 
	uiAvgG /= uiPixelCount;
	uiAvgB /= uiPixelCount;

	// the value here is 1/255 - we're normalising the RGBs.
	average.r = 0.003921f * (vlSingle)uiAvgR;
	average.g = 0.003921f * (vlSingle)uiAvgG;
	average.b = 0.003921f * (vlSingle)uiAvgB;

	vlByte *lpSphereMapDataPointer = lpSphereMapData;

	// Calculate sphere-map by rendering a perfectly reflective solid sphere.
	for (y = 0; y < uiHeight; y++)
	{
		for (x = 0; x < uiWidth; x++)
		{
			texel.r = texel.g = texel.b = 0.0f;
		
			for (j = 0; j < samples; j++)
			{
				s = ((vlSingle)x + (vlSingle)drand48()) / (vlSingle)uiWidth - 0.5f;
				t = ((vlSingle)y + (vlSingle)drand48()) / (vlSingle)uiHeight - 0.5f;
				temp = s * s + t * t;

				//point not on sphere so use the average colour
				if (temp >= 0.25f)
				{
					texel.r += average.r;		
					texel.g += average.g;		
					texel.b += average.b;		
					continue;
				}

				//get point on sphere
				p.x = s;
				p.y = t;
				p.z = sqrt(0.25f - temp);
				VecScale(&p, 2.0f);

				//ray from infinity (eyepoint) to surface
				v.x = 0.0f;
				v.y = 0.0f;
				v.z = 1.0f;

				//get reflected ray
				VecReflect(&p, &v, &r);

				//Intersect reflected ray with cube
				f = Intersect(&r);
				k = VecDot(&SFace[f].o, &SFace[f].n) / VecDot(&r, &SFace[f].n);
				VecScale(&r, k);
				VecSub(&r, &SFace[f].o, &v);

				//Get texture map-indices
				s = VecDot(&v, &SFace[f].u);
				t = VecDot(&v, &SFace[f].v);

				//Sample to get color
				SphereMapFace *pf = &SFace[f];
				vlUInt xpos, ypos;
				vlByte *p;
  
				xpos = (vlUInt)(s * (vlSingle)uiWidth);
				ypos = (vlUInt)(t * (vlSingle)uiHeight);

				p = (vlByte *)&pf->buf[ypos * uiWidth + xpos];
				c.r = (vlSingle)p[0] / 255.0f;
				c.g = (vlSingle)p[1] / 255.0f;
				c.b = (vlSingle)p[2] / 255.0f;

				texel.r += c.r;
				texel.g += c.g;
				texel.b += c.b;
			}
	
			// punch the pixel into our SphereMap image buffer
			lpSphereMapDataPointer[0] = (vlByte)(255.0f * texel.r / (vlSingle)samples);
			lpSphereMapDataPointer[1] = (vlByte)(255.0f * texel.g / (vlSingle)samples);
			lpSphereMapDataPointer[2] = (vlByte)(255.0f * texel.b / (vlSingle)samples);
			lpSphereMapDataPointer[3] = 0xff;
			lpSphereMapDataPointer += 4;
		}
	}

	//#pragma warning(default: 4244)

	if (!this->ConvertFromRGBA8888(lpSphereMapData,
									this->GetData(0, CUBEMAP_FACE_SphereMap, 0, 0),
									this->Header->Width,
									this->Header->Height,
									this->Header->ImageFormat) )
	{
		for(i = 0; i < 6; i++)
		{
			delete[] lpImageData[i];
		}
		delete[] lpSphereMapData;

		return vlFalse; 
	};

	// delete the memory buffers
	for(i = 0; i < 6; i++)
	{
		delete[] lpImageData[i];
	}
	delete[] lpSphereMapData;

	return vlTrue;
}

//
// ComputeReflectivity()
// Compute the reflectivity value of the texture using all faces and frames.
//
vlBool CVTFFile::ComputeReflectivity()
{
	if(!this->IsLoaded())
		return vlFalse;

	if(this->lpImageData == 0)
	{
		LastError.Set("No image data to compute reflectivity from.");

		return vlFalse;
	}

	this->Header->Reflectivity[0] = 0.0f;
	this->Header->Reflectivity[1] = 0.0f;
	this->Header->Reflectivity[2] = 0.0f;

    vlByte *lpImageData = new vlByte[this->ComputeImageSize(this->Header->Width, this->Header->Height, 1, IMAGE_FORMAT_RGBA8888)];

	vlUInt uiFrameCount = this->GetFrameCount();
	vlUInt uiFaceCount = this->GetFaceCount();
	vlUInt uiSliceCount = this->GetDepth();

    for(vlUInt uiFrame = 0; uiFrame < uiFrameCount; uiFrame++)
    {
        for(vlUInt uiFace = 0; uiFace < uiFaceCount; uiFace++)
        {
			for(vlUInt uiSlice = 0; uiSlice < uiSliceCount; uiSlice++)
			{
				if(!this->ConvertToRGBA8888(this->GetData(uiFrame, uiFace, uiSlice, 0), lpImageData, this->Header->Width, this->Header->Height, this->Header->ImageFormat))
				{
					delete []lpImageData;

					return vlFalse;
				}

				vlSingle sX, sY, sZ;
				this->ComputeImageReflectivity(lpImageData, this->Header->Width, this->Header->Height, sX, sY, sZ);

				this->Header->Reflectivity[0] += sX;
				this->Header->Reflectivity[1] += sY;
				this->Header->Reflectivity[2] += sZ;
			}
        }
    }

	vlSingle sInverse = 1.0f / (vlSingle)(uiFrameCount * uiFaceCount * uiSliceCount);

	this->Header->Reflectivity[0] *= sInverse;
	this->Header->Reflectivity[1] *= sInverse;
	this->Header->Reflectivity[2] *= sInverse;

	delete []lpImageData;

	return vlTrue;
}

// Array which holds information about our image format
// (taken from imageloader.cpp, Valve Source SDK)
//------------------------------------------------------
static SVTFImageFormatInfo VTFImageFormatInfo[] =
{
	{ "RGBA8888",			 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_RGBA8888,
	{ "ABGR8888",			 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_ABGR8888, 
	{ "RGB888",				 24,  3,  8,  8,  8,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_RGB888,
	{ "BGR888",				 24,  3,  8,  8,  8,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_BGR888,
	{ "RGB565",				 16,  2,  5,  6,  5,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_RGB565, 
	{ "I8",					  8,  1,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_I8,
	{ "IA88",				 16,  2,  0,  0,  0,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_IA88
	{ "P8",					  8,  1,  0,  0,  0,  0, vlFalse, vlFalse },		// IMAGE_FORMAT_P8
	{ "A8",					  8,  1,  0,  0,  0,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_A8
	{ "RGB888 Bluescreen",	 24,  3,  8,  8,  8,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_RGB888_BLUESCREEN
	{ "BGR888 Bluescreen",	 24,  3,  8,  8,  8,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_BGR888_BLUESCREEN
	{ "ARGB8888",			 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_ARGB8888
	{ "BGRA8888",			 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_BGRA8888
	{ "DXT1",				  4,  0,  0,  0,  0,  0,  vlTrue,  vlTrue },		// IMAGE_FORMAT_DXT1
	{ "DXT3",				  8,  0,  0,  0,  0,  8,  vlTrue,  vlTrue },		// IMAGE_FORMAT_DXT3
	{ "DXT5",				  8,  0,  0,  0,  0,  8,  vlTrue,  vlTrue },		// IMAGE_FORMAT_DXT5
	{ "BGRX8888",			 32,  4,  8,  8,  8,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_BGRX8888
	{ "BGR565",				 16,  2,  5,  6,  5,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_BGR565
	{ "BGRX5551",			 16,  2,  5,  5,  5,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_BGRX5551
	{ "BGRA4444",			 16,  2,  4,  4,  4,  4, vlFalse,  vlTrue },		// IMAGE_FORMAT_BGRA4444
	{ "DXT1 One Bit Alpha",	  4,  0,  0,  0,  0,  1,  vlTrue,  vlTrue },		// IMAGE_FORMAT_DXT1_ONEBITALPHA
	{ "BGRA5551",			 16,  2,  5,  5,  5,  1, vlFalse,  vlTrue },		// IMAGE_FORMAT_BGRA5551
	{ "UV88",				 16,  2,  8,  8,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_UV88
	{ "UVWQ8888",			 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_UVWQ8899
	{ "RGBA16161616F",	     64,  8, 16, 16, 16, 16, vlFalse,  vlTrue },		// IMAGE_FORMAT_RGBA16161616F
	{ "RGBA16161616",	     64,  8, 16, 16, 16, 16, vlFalse,  vlTrue },		// IMAGE_FORMAT_RGBA16161616
	{ "UVLX8888",			 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_UVLX8888
	{ "R32F",				 32,  4, 32,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_R32F
	{ "RGB323232F",			 96, 12, 32, 32, 32,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_RGB323232F
	{ "RGBA32323232F",		128, 16, 32, 32, 32, 32, vlFalse,  vlTrue },		// IMAGE_FORMAT_RGBA32323232F
	{ "nVidia DST16",		 16,  2,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_NV_DST16
	{ "nVidia DST24",		 24,  3,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_NV_DST24
	{ "nVidia INTZ",		 32,  4,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_NV_INTZ
	{ "nVidia RAWZ",		 32,  4,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_NV_RAWZ
	{ "ATI DST16",			 16,  2,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_ATI_DST16
	{ "ATI DST24",			 24,  3,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_ATI_DST24
	{ "nVidia NULL",		 32,  4,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_NV_NULL
	{ "ATI1N",				  4,  0,  0,  0,  0,  0,  vlTrue,  vlTrue },		// IMAGE_FORMAT_ATI1N
	{ "ATI2N",				  8,  0,  0,  0,  0,  0,  vlTrue,  vlTrue },		// IMAGE_FORMAT_ATI2N
	{ "HDR_BGRA8888",		 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue }			// IMAGE_FORMAT_BGRA8888
	/*
	{ "Xbox360 DST16",		 16,  0,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_X360_DST16
	{ "Xbox360 DST24",		 24,  0,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_X360_DST24
	{ "Xbox360 DST24F",		 24,  0,  0,  0,  0,  0, vlFalse , vlTrue },		// IMAGE_FORMAT_X360_DST24F
	{ "Linear BGRX8888",	 32,  4,  8,  8,  8,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_BGRX8888
	{ "Linear RGBA8888",     32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_RGBA8888
	{ "Linear ABGR8888",	 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_ABGR8888
	{ "Linear ARGB8888",	 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_ARGB8888
	{ "Linear BGRA8888",	 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_BGRA8888
	{ "Linear RGB888",		 24,  3,  8,  8,  8,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_RGB888
	{ "Linear BGR888",		 24,  3,  8,  8,  8,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_BGR888
	{ "Linear BGRX5551",	 16,  2,  5,  5,  5,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_BGRX5551
	{ "Linear I8",			  8,  1,  0,  0,  0,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_I8
	{ "Linear RGBA16161616", 64,  8, 16, 16, 16, 16, vlFalse,  vlTrue },		// IMAGE_FORMAT_LINEAR_RGBA16161616
	{ "LE BGRX8888",         32,  4,  8,  8,  8,  0, vlFalse,  vlTrue },		// IMAGE_FORMAT_LE_BGRX8888
	{ "LE BGRA8888",		 32,  4,  8,  8,  8,  8, vlFalse,  vlTrue }			// IMAGE_FORMAT_LE_BGRA8888
	*/
};

SVTFImageFormatInfo const &CVTFFile::GetImageFormatInfo(VTFImageFormat ImageFormat)
{
	assert(ImageFormat >= 0 && ImageFormat < IMAGE_FORMAT_COUNT);

	return VTFImageFormatInfo[ImageFormat];
}

//------------------------------------------------------------------------------------
// ComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat ImageFormat)
// 
// Returns how many bytes are needed to store an image of width * height in the chosen
// image format. If bMipMaps is true, the total will reflect the space needed to store
// the original image plus all the mipmaps down to a size of 1 x 1
//------------------------------------------------------------------------------------
vlUInt CVTFFile::ComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, VTFImageFormat ImageFormat)
{
	switch(ImageFormat)
	{
	case IMAGE_FORMAT_DXT1:
	case IMAGE_FORMAT_DXT1_ONEBITALPHA:
		if(uiWidth < 4 && uiWidth > 0)
			uiWidth = 4;

		if(uiHeight < 4 && uiHeight > 0)
			uiHeight = 4;

		return ((uiWidth + 3) / 4) * ((uiHeight + 3) / 4) * 8 * uiDepth;
	case IMAGE_FORMAT_DXT3:
	case IMAGE_FORMAT_DXT5:
		if(uiWidth < 4 && uiWidth > 0)
			uiWidth = 4;

		if(uiHeight < 4 && uiHeight > 0)
			uiHeight = 4;

		return ((uiWidth + 3) / 4) * ((uiHeight + 3) / 4) * 16 * uiDepth;
	default:
		return uiWidth * uiHeight * uiDepth * CVTFFile::GetImageFormatInfo(ImageFormat).uiBytesPerPixel;
	}
}

//
// ComputeImageSize();
// Gets the size in bytes of the data needed to store an image of size uiWidth x uiHeight
// with uiMipmaps mipmap levels and ImageFormat format.
//
vlUInt CVTFFile::ComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmaps, VTFImageFormat ImageFormat)
{
	vlUInt uiImageSize = 0;

	assert(uiWidth != 0 && uiHeight != 0 && uiDepth != 0);

	for(vlUInt i = 0; i < uiMipmaps; i++)
	{
		uiImageSize += CVTFFile::ComputeImageSize(uiWidth, uiHeight, uiDepth, ImageFormat);
		
		uiWidth >>= 1;
		uiHeight >>= 1;
		uiDepth >>= 1;

		if(uiWidth < 1)
			uiWidth = 1;

		if(uiHeight < 1)
			uiHeight = 1;

		if(uiDepth < 1)
			uiDepth = 1;
	}

	return uiImageSize;
}

//
// ComputeMipmapCount();
// Gets the number of mipmaps an image of size uiWidth x uiHeight will have including
// the mipmap of size uiWidth x uiHeight.
//
vlUInt CVTFFile::ComputeMipmapCount(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth)
{
	vlUInt uiCount = 0;

	assert(uiWidth != 0 && uiHeight != 0 && uiDepth != 0);

	while(vlTrue)
	{
		uiCount++;
		
		uiWidth >>= 1;
		uiHeight >>= 1;
		uiDepth >>= 1;

		if(uiWidth == 0 && uiHeight == 0 && uiDepth == 0)
			break;

		/*if(uiWidth < 1)
			uiWidth = 1;

		if(uiHeight < 1)
			uiHeight = 1;

		if(uiDepth < 1)
			uiDepth = 1;*/
	}

	return uiCount;
}

//-----------------------------------------------------------------------------
// ComputeMIPMapDimensions( vlInt iMipLevel, vlInt *pMipWidth, vlInt *pMipHeight )
//
// Computes the dimensions of a particular mip level
//-----------------------------------------------------------------------------
vlVoid CVTFFile::ComputeMipmapDimensions(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, vlUInt &uiMipmapWidth, vlUInt &uiMipmapHeight, vlUInt &uiMipmapDepth)
{
	// work out the width/height by taking the orignal dimension
	// and bit shifting them down uiMipmapLevel times
	uiMipmapWidth = uiWidth >> uiMipmapLevel;
	uiMipmapHeight = uiHeight >> uiMipmapLevel;
	uiMipmapDepth = uiDepth >> uiMipmapLevel;
	
	// stop the dimension being less than 1 x 1
	if(uiMipmapWidth < 1)
		uiMipmapWidth = 1;

	if(uiMipmapHeight < 1)
		uiMipmapHeight = 1;

	if(uiMipmapDepth < 1)
		uiMipmapDepth = 1;
}

//-----------------------------------------------------------------------------
// ComputeMIPSize( vlInt iMipLevel, VTFImageFormat fmt )
//
// Computes the size (in bytes) of a single mipmap of a single face of a single frame 
//-----------------------------------------------------------------------------
vlUInt CVTFFile::ComputeMipmapSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, VTFImageFormat ImageFormat)
{
	// figure out the width/height of this MIP level
	vlUInt uiMipmapWidth, uiMipmapHeight, uiMipmapDepth;
	CVTFFile::ComputeMipmapDimensions(uiWidth, uiHeight, uiDepth, uiMipmapLevel, uiMipmapWidth, uiMipmapHeight, uiMipmapDepth);
	
	// return the memory requirements
	return CVTFFile::ComputeImageSize(uiMipmapWidth, uiMipmapHeight, uiMipmapDepth, ImageFormat);
}

//---------------------------------------------------------------------------------
// ComputeDataOffset(vlUInt uiFrame, vlUInt uiFace, vlUInt uiMipLevel, VTFImageFormat ImageFormat)
//
// Returns the offset in our HiResDataBuffer of the data for an image at the 
// chose frame, face, and mip level. Frame number starts at 0, Face starts at 0
// MIP level 0 is the largest moving up to MIP count-1 for the smallest
// To get the first, and largest image, you would use 0, 0, 0
//---------------------------------------------------------------------------------
vlUInt CVTFFile::ComputeDataOffset(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipLevel, VTFImageFormat ImageFormat) const
{
	vlUInt uiOffset = 0;

	vlUInt uiFrameCount = this->GetFrameCount();
	vlUInt uiFaceCount = this->GetFaceCount();
	vlUInt uiSliceCount = this->GetDepth();
	vlUInt uiMipCount = this->GetMipmapCount();

	if(uiFrame >= uiFrameCount)
	{
		uiFrame = uiFrameCount - 1;
	}
	
	if(uiFace >= uiFaceCount)
	{
		uiFace = uiFaceCount - 1;
	}

	if(uiSlice >= uiSliceCount)
	{
		uiSlice = uiSliceCount - 1;
	}

	if(uiMipLevel >= uiMipCount)
	{
		uiMipLevel = uiMipCount - 1;
	}

	// Transverse past all frames and faces of each mipmap (up to the requested one).
	for(vlInt i = (vlInt)uiMipCount - 1; i > (vlInt)uiMipLevel; i--)
	{
		uiOffset += this->ComputeMipmapSize(this->Header->Width, this->Header->Height, this->Header->Depth, i, ImageFormat) * uiFrameCount * uiFaceCount;
	}

	vlUInt uiTemp1 = this->ComputeMipmapSize(this->Header->Width, this->Header->Height, this->Header->Depth, uiMipLevel, ImageFormat);
	vlUInt uiTemp2 = this->ComputeMipmapSize(this->Header->Width, this->Header->Height, 1, uiMipLevel, ImageFormat);

	// Transverse past requested frames and faces of requested mipmap.
	uiOffset += uiTemp1 * uiFrame * uiFaceCount * uiSliceCount;
	uiOffset += uiTemp1 * uiFace * uiSliceCount;
	uiOffset += uiTemp2 * uiSlice;

	assert(uiOffset < this->uiImageBufferSize);
	
	return uiOffset;
}

//-----------------------------------------------------------------------------------------------------
// ConvertToRGBA8888( vlByte *src, vlByte *dst, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat )
//
// Converts data from the source format to RGBA8888 format. Data is read from *src
// and written to *dst. Width and height are needed to it knows how much data to process
//-----------------------------------------------------------------------------------------------------
vlBool CVTFFile::ConvertToRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat)
{
	return CVTFFile::Convert(lpSource, lpDest, uiWidth, uiHeight, SourceFormat, IMAGE_FORMAT_RGBA8888);
}

//-----------------------------------------------------------------------------------------------------
// DecompressDXTn(vlByte *src, vlByte *dst, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat)
//
// Converts data from the DXT1 to RGBA8888 format. Data is read from *src
// and written to *dst. Width and height are needed to it knows how much data to process
//-----------------------------------------------------------------------------------------------------
vlBool CVTFFile::DecompressDXTn(vlByte *src, vlByte *dst, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat)
{
	CMP_Texture srcTexture = {0};
	srcTexture.dwSize     = sizeof( srcTexture );
	srcTexture.dwWidth    = uiWidth;
	srcTexture.dwHeight   = uiHeight;
	srcTexture.dwPitch    = 0;
	srcTexture.format     = GetCMPFormat( SourceFormat, false );
	srcTexture.dwDataSize = CMP_CalculateBufferSize( &srcTexture );
	srcTexture.pData      = (CMP_BYTE*) src;

	CMP_CompressOptions options = {0};
	options.dwSize        = sizeof(options);
	options.fquality      = 1.0f;
	options.dwnumThreads  = 0;
	options.bDXT1UseAlpha = SourceFormat == ( IMAGE_FORMAT_DXT1_ONEBITALPHA | IMAGE_FORMAT_DXT1 );

	CMP_Texture destTexture = {0};
	destTexture.dwSize     = sizeof( destTexture );
	destTexture.dwWidth    = uiWidth;
	destTexture.dwHeight   = uiHeight;
	destTexture.dwPitch    = 4 * uiWidth;
	destTexture.format     = CMP_FORMAT_RGBA_8888;
	destTexture.dwDataSize = destTexture.dwPitch * uiHeight;
	destTexture.pData      = (CMP_BYTE*) dst;

	CMP_ERROR cmp_status = CMP_ConvertTexture( &srcTexture, &destTexture, &options, NULL );
	if (cmp_status != CMP_OK)
	{
		LastError.Set( GetCMPErrorString( cmp_status ) );
		return vlFalse;
	}

	return vlTrue;
}

//
// ConvertFromRGBA8888()
// Convert input image data (lpSource) to output image data (lpDest) of format DestFormat.
//
vlBool CVTFFile::ConvertFromRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat DestFormat, vlUInt nAlphaThreshold)
{
	return CVTFFile::Convert(lpSource, lpDest, uiWidth, uiHeight, IMAGE_FORMAT_RGBA8888, DestFormat, nAlphaThreshold);
}

//
// CompressDXTn()
// Compress input image data (lpSource) to output image data (lpDest) of format DestFormat
// where DestFormat is of format DXTn.  Uses NVidia DXT library.
//
vlBool CVTFFile::CompressDXTn(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat DestFormat, vlUInt nAlphaThreshold = 0)
{
	CMP_Texture srcTexture = {0};
	srcTexture.dwSize     = sizeof( srcTexture );
	srcTexture.dwWidth    = uiWidth;
	srcTexture.dwHeight   = uiHeight;
	srcTexture.dwPitch    = 4 * uiWidth;
	srcTexture.format     = CMP_FORMAT_RGBA_8888;
	srcTexture.dwDataSize = uiHeight * srcTexture.dwPitch;
	srcTexture.pData      = (CMP_BYTE*) lpSource;

	CMP_CompressOptions options = {0};
	options.dwSize        = sizeof(options);
	options.fquality      = 1.0f;
	options.dwnumThreads  = 0;
	if ( DestFormat == IMAGE_FORMAT_DXT1 || DestFormat == IMAGE_FORMAT_DXT1_ONEBITALPHA ) {
		options.bDXT1UseAlpha = true;
	}
	else {
		options.bDXT1UseAlpha = false;
	}
	options.nAlphaThreshold = nAlphaThreshold;

	CMP_Texture destTexture = {0};
	destTexture.dwSize     = sizeof( destTexture );
	destTexture.dwWidth    = uiWidth;
	destTexture.dwHeight   = uiHeight;
	destTexture.dwPitch    = 0;
	destTexture.format     = GetCMPFormat( DestFormat, false );
	destTexture.dwDataSize = CMP_CalculateBufferSize( &destTexture );
	destTexture.pData      = (CMP_BYTE*) lpDest;

	CMP_ERROR cmp_status = CMP_ConvertTexture( &srcTexture, &destTexture, &options, NULL );
	if (cmp_status != CMP_OK)
	{
		LastError.Set( GetCMPErrorString( cmp_status ) );
		return vlFalse;
	}

	return vlTrue;
}

typedef vlVoid (*TransformProc)(vlUInt16& R, vlUInt16& G, vlUInt16& B, vlUInt16& A);

vlVoid ToLuminance(vlUInt16& R, vlUInt16& G, vlUInt16& B, vlUInt16& A)
{
	R = G = B = (vlUInt16)(sLuminanceWeightR * (vlSingle)R + sLuminanceWeightG * (vlSingle)G + sLuminanceWeightB * (vlSingle)B);
}

vlVoid FromLuminance(vlUInt16& R, vlUInt16& G, vlUInt16& B, vlUInt16& A)
{
	B = G = R;
}

vlVoid ToBlueScreen(vlUInt16& R, vlUInt16& G, vlUInt16& B, vlUInt16& A)
{
	if(A == 0x0000)
	{
		R = uiBlueScreenMaskR;
		G = uiBlueScreenMaskG;
		B = uiBlueScreenMaskB;
	}
	A = 0xffff;
}

vlVoid FromBlueScreen(vlUInt16& R, vlUInt16& G, vlUInt16& B, vlUInt16& A)
{
	if(R == uiBlueScreenMaskR && G == uiBlueScreenMaskG && B == uiBlueScreenMaskB)
	{
		R = uiBlueScreenClearR;
		G = uiBlueScreenClearG;
		B = uiBlueScreenClearB;
		A = 0x0000;
	}
	else
	{
		A = 0xffff;
	}
}

static inline vlSingle FP16ToFP32(vlUInt16 input)
{
	const vlUInt32 uiF32Bias = 127;
	const vlUInt32 uiF16Bias = 15;
	const vlSingle sMaxFloat16Bits = 65504.0f;

	struct
	{
		vlUInt16 uiMantissa : 10;
		vlUInt16 uiExponent : 5;
		vlUInt16 uiSign : 1;
	} fp16;
	std::memcpy(&fp16, &input, sizeof(vlUInt16));

	if (fp16.uiExponent == 31)
	{
		if (fp16.uiMantissa == 0) // Check for Infinity
			return sMaxFloat16Bits * ((fp16.uiSign == 1) ? -1.0f : 1.0f);
		else if (fp16.uiMantissa != 0) // Check for NaN
			return 0.0f;
	}

	if (fp16.uiExponent == 0 && fp16.uiMantissa != 0)
	{
		// Denorm...
		const vlSingle sHalfDenorm = 1.0f / vlSingle(1 << 14);
		const vlSingle sMantissa   = vlSingle(fp16.uiMantissa) / vlSingle(1 << 10);
		const vlSingle sSign       = fp16.uiSign ? -1.0f : 1.0f;

		return sSign * sMantissa * sHalfDenorm;
	}
	else
	{
		const vlUInt32 uiMantissa = fp16.uiMantissa;
		const vlUInt32 uiExponent = fp16.uiExponent != 0
			? fp16.uiExponent - uiF16Bias + uiF32Bias
			: 0;
		const vlUInt32 uiSign     = fp16.uiSign;

		vlUInt32 uiBits = (uiMantissa << 13) | (uiExponent << 23) | (uiSign << 31);
		vlSingle sValue;
		std::memcpy(&sValue, &uiBits, sizeof(sValue));
		return sValue;
	}
}

// A very very basic Reinhard implementation for
// previewing cubemaps...
// (Feel free to use something better with proper luminance
// and a white point!)
vlSingle Reinhard(vlSingle sValue)
{
    return sValue / (1.0f + sValue);
}

vlVoid ToFP16(vlUInt16& R, vlUInt16& G, vlUInt16& B, vlUInt16& A)
{
}

vlUInt16 FP16ToUnorm(vlUInt16 uiValue)
{
	vlSingle sValue = FP16ToFP32(uiValue);

	sValue *= sFP16HDRExposure;
	sValue = Reinhard(sValue);
	sValue *= 65535.0f;
	sValue = min(max(sValue, 0.0f), 65535.0f);
	return (vlUInt16) sValue;
}

vlVoid FromFP16(vlUInt16& R, vlUInt16& G, vlUInt16& B, vlUInt16& A)
{
	R = FP16ToUnorm(R);
	G = FP16ToUnorm(G);
	B = FP16ToUnorm(B);
	A = FP16ToUnorm(A);
}

typedef struct tagSVTFImageConvertInfo
{
	vlUInt	uiBitsPerPixel;			// Format bytes per pixel.
	vlUInt	uiBytesPerPixel;		// Format bytes per pixel.
	vlUInt	uiRBitsPerPixel;		// Format conversion red bits per pixel.  0 for N/A.
	vlUInt	uiGBitsPerPixel;		// Format conversion green bits per pixel.  0 for N/A.
	vlUInt	uiBBitsPerPixel;		// Format conversion blue bits per pixel.  0 for N/A.
	vlUInt	uiABitsPerPixel;		// Format conversion alpha bits per pixel.  0 for N/A.
	vlInt	iR;						// "Red" index.
	vlInt	iG;						// "Green" index.
	vlInt	iB;						// "Blue" index.
	vlInt	iA;						// "Alpha" index.
	vlBool	bIsCompressed;			// Format is compressed (DXT).
	vlBool	bIsSupported;			// Format is supported by VTFLib.
	TransformProc pToTransform;		// Custom transform to function.
	TransformProc pFromTransform;	// Custom transform from function.
	VTFImageFormat Format;
} SVTFImageConvertInfo;

static SVTFImageConvertInfo VTFImageConvertInfo[] =
{
	{	 32,  4,  8,  8,  8,  8,	 0,	 1,	 2,	 3,	vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_RGBA8888},
	{	 32,  4,  8,  8,  8,  8,	 3,	 2,	 1,	 0, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_ABGR8888},
	{	 24,  3,  8,  8,  8,  0,	 0,	 1,	 2,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_RGB888},
	{	 24,  3,  8,  8,  8,  0,	 2,	 1,	 0,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_BGR888},
	{	 16,  2,  5,  6,  5,  0,	 0,	 1,	 2,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_RGB565},
	{	  8,  1,  8,  8,  8,  0,	 0,	-1,	-1,	-1, vlFalse,  vlTrue,	ToLuminance,	FromLuminance,	IMAGE_FORMAT_I8},
	{	 16,  2,  8,  8,  8,  8,	 0,	-1,	-1,	 1, vlFalse,  vlTrue,	ToLuminance,	FromLuminance,	IMAGE_FORMAT_IA88},
	{	  8,  1,  0,  0,  0,  0,	-1,	-1,	-1,	-1, vlFalse, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_P8},
	{ 	  8,  1,  0,  0,  0,  8,	-1,	-1,	-1,	 0, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_A8},
	{ 	 24,  3,  8,  8,  8,  8,	 0,	 1,	 2,	-1, vlFalse,  vlTrue,	ToBlueScreen,	FromBlueScreen,	IMAGE_FORMAT_RGB888_BLUESCREEN},
	{ 	 24,  3,  8,  8,  8,  8,	 2,	 1,	 0,	-1, vlFalse,  vlTrue,	ToBlueScreen,	FromBlueScreen,	IMAGE_FORMAT_BGR888_BLUESCREEN},
	{ 	 32,  4,  8,  8,  8,  8,	 3,	 0,	 1,	 2, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_ARGB8888},
	{ 	 32,  4,  8,  8,  8,  8,	 2,	 1,	 0,	 3, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_BGRA8888},
	{ 	  4,  0,  0,  0,  0,  0,	-1,	-1,	-1,	-1,  vlTrue,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_DXT1},
	{ 	  8,  0,  0,  0,  0,  8,	-1,	-1,	-1,	-1,  vlTrue,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_DXT3},
	{ 	  8,  0,  0,  0,  0,  8,	-1,	-1,	-1,	-1,  vlTrue,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_DXT5},
	{ 	 32,  4,  8,  8,  8,  0,	 2,	 1,	 0,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_BGRX8888},
	{ 	 16,  2,  5,  6,  5,  0,	 2,	 1,	 0,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_BGR565},
	{ 	 16,  2,  5,  5,  5,  0,	 2,	 1,	 0,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_BGRX5551},
	{ 	 16,  2,  4,  4,  4,  4,	 2,	 1,	 0,	 3, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_BGRA4444},
	{ 	  4,  0,  0,  0,  0,  1,	-1,	-1,	-1,	-1,  vlTrue,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_DXT1_ONEBITALPHA},
	{ 	 16,  2,  5,  5,  5,  1,	 2,	 1,	 0,	 3, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_BGRA5551},
	{ 	 16,  2,  8,  8,  0,  0,	 0,	 1,	-1,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_UV88},
	{ 	 32,  4,  8,  8,  8,  8,	 0,	 1,	 2,	 3, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_UVWQ8888},
	{    64,  8, 16, 16, 16, 16,	 0,	 1,	 2,	 3, vlFalse,  vlTrue,	ToFP16,	FromFP16,	IMAGE_FORMAT_RGBA16161616F},
	{	 64,  8, 16, 16, 16, 16,	 0,	 1,	 2,	 3, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_RGBA16161616},
	{ 	 32,  4,  8,  8,  8,  8,	 0,	 1,	 2,	 3, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_UVLX8888},
	{ 	 32,  4, 32,  0,  0,  0,	 0,	-1,	-1,	-1, vlFalse, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_R32F},
	{ 	 96, 12, 32, 32, 32,  0,	 0,	 1,	 2,	-1, vlFalse, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_RGB323232F},
	{	128, 16, 32, 32, 32, 32,	 0,	 1,	 2,	 3, vlFalse, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_RGBA32323232F},
	{    16,  2, 16,  0,  0,  0,	 0,	-1,	-1,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_NV_DST16},
	{	 24,  3, 24,  0,  0,  0,	 0,	-1,	-1,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_NV_DST24},
	{	 32,  4,  0,  0,  0,  0,	-1,	-1,	-1,	-1, vlFalse, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_NV_INTZ},
	{	 24,  3,  0,  0,  0,  0,    -1,	-1,	-1,	-1, vlFalse, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_NV_RAWZ},
	{	 16,  2, 16,  0,  0,  0,	 0,	-1,	-1,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_ATI_DST16},
	{	 24,  3, 24,  0,  0,  0,	 0,	-1,	-1,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_ATI_DST24},
	{	 32,  4,  0,  0,  0,  0,	-1,	-1,	-1,	-1, vlFalse, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_NV_NULL},
	{	  4,  0,  0,  0,  0,  0,	-1, -1, -1, -1,  vlTrue, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_ATI1N},
	{     8,  0,  0,  0,  0,  0,	-1, -1, -1, -1,  vlTrue, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_ATI2N},
	{ 	 32,  4,  8,  8,  8,  8,	 2,	 1,	 0,	 3, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_HDR_BGRA8888},/*,
	{	 16,  2, 16,  0,  0,  0,	 0, -1, -1, -1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_X360_DST16},
	{	 24,  3, 24,  0,  0,  0,	 0, -1, -1, -1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_X360_DST24},
	{	 24,  3,  0,  0,  0,  0,	-1, -1, -1, -1, vlFalse, vlFalse,	NULL,	NULL,		IMAGE_FORMAT_X360_DST24F},
	{ 	 32,  4,  8,  8,  8,  0,	 2,	 1,	 0,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_LINEAR_BGRX8888},
	{	 32,  4,  8,  8,  8,  8,	 0,	 1,	 2,	 3,	vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_LINEAR_RGBA8888},
	{	 32,  4,  8,  8,  8,  8,	 3,	 2,	 1,	 0, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_LINEAR_ABGR8888},
	{ 	 32,  4,  8,  8,  8,  8,	 3,	 0,	 1,	 2, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_LINEAR_ARGB8888},
	{ 	 32,  4,  8,  8,  8,  8,	 2,	 1,	 0,	 3, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_LINEAR_BGRA8888},
	{	 32,  4,  8,  8,  8,  8,	 0,	 1,	 2,	-1,	vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_LINEAR_RGB888},
	{	 32,  4,  8,  8,  8,  8,	 2,	 1,	 0,	-1,	vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_LINEAR_BGR888},
	{ 	 16,  2,  5,  5,  5,  0,	 2,	 1,	 0,	-1, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_LINEAR_BGRX5551},
	{	  8,  1,  8,  8,  8,  0,	 0,	-1,	-1,	-1, vlFalse,  vlTrue,	ToLuminance,	FromLuminance,	IMAGE_FORMAT_LINEAR_I8},	
	{	 64,  8, 16, 16, 16, 16,	 0,	 1,	 2,	 3, vlFalse,  vlTrue,	NULL,	NULL,		IMAGE_FORMAT_LINEAR_RGBA16161616}*/
};

// Get each channels shift and mask (for encoding and decoding).
template<typename T>
vlVoid GetShiftAndMask(const SVTFImageConvertInfo& Info, T &uiRShift, T &uiGShift, T &uiBShift, T &uiAShift, T &uiRMask, T &uiGMask, T &uiBMask, T &uiAMask)
{
	if(Info.iR >= 0)
	{
		if(Info.iG >= 0 && Info.iG < Info.iR)
			uiRShift += (T)Info.uiGBitsPerPixel;

		if(Info.iB >= 0 && Info.iB < Info.iR)
			uiRShift += (T)Info.uiBBitsPerPixel;

		if(Info.iA >= 0 && Info.iA < Info.iR)
			uiRShift += (T)Info.uiABitsPerPixel;

		uiRMask = (T)(~0) >> (T)((sizeof(T) * 8) - Info.uiRBitsPerPixel); // Mask is for down shifted values.
	}

	if(Info.iG >= 0)
	{
		if(Info.iR >= 0 && Info.iR < Info.iG)
			uiGShift += (T)Info.uiRBitsPerPixel;

		if(Info.iB >= 0 && Info.iB < Info.iG)
			uiGShift += (T)Info.uiBBitsPerPixel;

		if(Info.iA >= 0 && Info.iA < Info.iG)
			uiGShift += (T)Info.uiABitsPerPixel;

		uiGMask = (T)(~0) >> (T)((sizeof(T) * 8) - Info.uiGBitsPerPixel);
	}

	if(Info.iB >= 0)
	{
		if(Info.iR >= 0 && Info.iR < Info.iB)
			uiBShift += (T)Info.uiRBitsPerPixel;

		if(Info.iG >= 0 && Info.iG < Info.iB)
			uiBShift += (T)Info.uiGBitsPerPixel;

		if(Info.iA >= 0 && Info.iA < Info.iB)
			uiBShift += (T)Info.uiABitsPerPixel;

		uiBMask = (T)(~0) >> (T)((sizeof(T) * 8) - Info.uiBBitsPerPixel);
	}

	if(Info.iA >= 0)
	{
		if(Info.iR >= 0 && Info.iR < Info.iA)
			uiAShift += (T)Info.uiRBitsPerPixel;

		if(Info.iG >= 0 && Info.iG < Info.iA)
			uiAShift += (T)Info.uiGBitsPerPixel;

		if(Info.iB >= 0 && Info.iB < Info.iA)
			uiAShift += (T)Info.uiBBitsPerPixel;

		uiAMask = (T)(~0) >> (T)((sizeof(T) * 8) - Info.uiABitsPerPixel);
	}
}

// Downsample a channel.
template<typename T>
T Shrink(T S, T SourceBits, T DestBits)
{
	if(SourceBits == 0 || DestBits == 0)
		return 0;

	return S >> (SourceBits - DestBits);
}

// Upsample a channel.
template<typename T>
T Expand(T S, T SourceBits, T DestBits)
{
	if(SourceBits == 0 || DestBits == 0)
		return 0;

	T D = 0;

	// Repeat source bit pattern as much as possible.
	while(DestBits >= SourceBits)
	{
		D <<= SourceBits;
		D |= S;
		DestBits -= SourceBits;
	}

	// Add most significant part of source bit pattern to least significant part of dest bit pattern.
	if(DestBits)
	{
		S >>= SourceBits - DestBits;
		D <<= DestBits;
		D |= S;
	}

	return D;
}

// Run custom transformation functions.
template<typename T, typename U>
vlVoid Transform(TransformProc pTransform1, TransformProc pTransform2, T SR, T SG, T SB, T SA, T SRBits, T SGBits, T SBBits, T SABits, U& DR, U& DG, U& DB, U& DA, U DRBits, U DGBits, U DBBits, U DABits)
{
	vlUInt16 TR, TG, TB, TA;

	// Expand from source to 16 bits for transform functions.
	SRBits && SRBits < 16 ? TR = (vlUInt16)Expand<T>(SR, SRBits, 16) : TR = (vlUInt16)SR;
	SGBits && SGBits < 16 ? TG = (vlUInt16)Expand<T>(SG, SGBits, 16) : TG = (vlUInt16)SG;
	SBBits && SBBits < 16 ? TB = (vlUInt16)Expand<T>(SB, SBBits, 16) : TB = (vlUInt16)SB;
	SABits && SABits < 16 ? TA = (vlUInt16)Expand<T>(SA, SABits, 16) : TA = (vlUInt16)SA;

	// Source transform then dest transform.
	if(pTransform1)
		pTransform1(TR, TG, TB, TA);
	if(pTransform2)
		pTransform2(TR, TG, TB, TA);

	// Shrink to dest from 16 bits.
	DRBits && DRBits < 16 ? DR = (U)Shrink<vlUInt16>(TR, 16, (vlUInt16)DRBits) : DR = (U)TR;
	DGBits && DGBits < 16 ? DG = (U)Shrink<vlUInt16>(TG, 16, (vlUInt16)DGBits) : DG = (U)TG;
	DBBits && DBBits < 16 ? DB = (U)Shrink<vlUInt16>(TB, 16, (vlUInt16)DBBits) : DB = (U)TB;
	DABits && DABits < 16 ? DA = (U)Shrink<vlUInt16>(TA, 16, (vlUInt16)DABits) : DA = (U)TA;
}

#define HDR_EXPOSURE 512;

// Convert source to dest using required storage requirments (hence the template).
template<typename T, typename U>
vlBool ConvertTemplated(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, const SVTFImageConvertInfo& SourceInfo, const SVTFImageConvertInfo& DestInfo)
{
	vlUInt16 uiSourceRShift = 0, uiSourceGShift = 0, uiSourceBShift = 0, uiSourceAShift = 0;
	vlUInt16 uiSourceRMask = 0, uiSourceGMask = 0, uiSourceBMask = 0, uiSourceAMask = 0;

	vlUInt16 uiDestRShift = 0, uiDestGShift = 0, uiDestBShift = 0, uiDestAShift = 0;
	vlUInt16 uiDestRMask = 0, uiDestGMask = 0, uiDestBMask = 0, uiDestAMask = 0;

	GetShiftAndMask<vlUInt16>(SourceInfo, uiSourceRShift, uiSourceGShift, uiSourceBShift, uiSourceAShift, uiSourceRMask, uiSourceGMask, uiSourceBMask, uiSourceAMask);
	GetShiftAndMask<vlUInt16>(DestInfo, uiDestRShift, uiDestGShift, uiDestBShift, uiDestAShift, uiDestRMask, uiDestGMask, uiDestBMask, uiDestAMask);

	vlByte *lpSourceEnd = lpSource + (uiWidth * uiHeight * SourceInfo.uiBytesPerPixel);
	for(; lpSource < lpSourceEnd; lpSource += SourceInfo.uiBytesPerPixel, lpDest += DestInfo.uiBytesPerPixel)
	{
		// read source into single variable
		vlUInt i;
		T Source = 0;
		for(i = 0; i < SourceInfo.uiBytesPerPixel; i++)
		{
			Source |= (T)lpSource[i] << ((T)i * 8);
		}

		vlUInt16 SR = 0, SG = 0, SB = 0, SA = ~0;
		vlUInt16 DR = 0, DG = 0, DB = 0, DA = ~0;	// default values

		// read source values
		if(uiSourceRMask)
			SR = (vlUInt16)(Source >> (T)uiSourceRShift) & uiSourceRMask;	// isolate R channel

		if(uiSourceGMask)
			SG = (vlUInt16)(Source >> (T)uiSourceGShift) & uiSourceGMask;	// isolate G channel

		if(uiSourceBMask)
			SB = (vlUInt16)(Source >> (T)uiSourceBShift) & uiSourceBMask;	// isolate B channel

		if(uiSourceAMask)
			SA = (vlUInt16)(Source >> (T)uiSourceAShift) & uiSourceAMask;	// isolate A channel

		if (SourceInfo.Format == IMAGE_FORMAT_HDR_BGRA8888)
		{
			//If hdr, reduce colours to ldr range
			//Clamp rgb values to prevent artifacting
			vlUInt16 modifier = SA * 16;
			SR = (SR * modifier) / HDR_EXPOSURE;
			SR = min(max(0, SR), 255);

			SG = (SG * modifier) / HDR_EXPOSURE;
			SG = min(max(0, SG), 255);

			SB = (SB * modifier) / HDR_EXPOSURE;
			SB = min(max(0, SB), 255);

			SA = ~0;
		}

		if(SourceInfo.pFromTransform || DestInfo.pToTransform)
		{
			// transform values
			Transform<vlUInt16, vlUInt16>(SourceInfo.pFromTransform, DestInfo.pToTransform, SR, SG, SB, SA, SourceInfo.uiRBitsPerPixel, SourceInfo.uiGBitsPerPixel, SourceInfo.uiBBitsPerPixel, SourceInfo.uiABitsPerPixel, DR, DG, DB, DA, DestInfo.uiRBitsPerPixel, DestInfo.uiGBitsPerPixel, DestInfo.uiBBitsPerPixel, DestInfo.uiABitsPerPixel);
		}
		else
		{
			// default value transform
			if(uiSourceRMask && uiDestRMask)
			{
				if(DestInfo.uiRBitsPerPixel < SourceInfo.uiRBitsPerPixel)	// downsample
					DR = Shrink<vlUInt16>(SR, SourceInfo.uiRBitsPerPixel, DestInfo.uiRBitsPerPixel);
				else if(DestInfo.uiRBitsPerPixel > SourceInfo.uiRBitsPerPixel)	// upsample
					DR = Expand<vlUInt16>(SR, SourceInfo.uiRBitsPerPixel, DestInfo.uiRBitsPerPixel);
				else
					DR = SR;
			}

			if(uiSourceGMask && uiDestGMask)
			{
				if(DestInfo.uiGBitsPerPixel < SourceInfo.uiGBitsPerPixel)	// downsample
					DG = Shrink<vlUInt16>(SG, SourceInfo.uiGBitsPerPixel, DestInfo.uiGBitsPerPixel);
				else if(DestInfo.uiGBitsPerPixel > SourceInfo.uiGBitsPerPixel)	// upsample
					DG = Expand<vlUInt16>(SG, SourceInfo.uiGBitsPerPixel, DestInfo.uiGBitsPerPixel);
				else
					DG = SG;
			}

			if(uiSourceBMask && uiDestBMask)
			{
				if(DestInfo.uiBBitsPerPixel < SourceInfo.uiBBitsPerPixel)	// downsample
					DB = Shrink<vlUInt16>(SB, SourceInfo.uiBBitsPerPixel, DestInfo.uiBBitsPerPixel);
				else if(DestInfo.uiBBitsPerPixel > SourceInfo.uiBBitsPerPixel)	// upsample
					DB = Expand<vlUInt16>(SB, SourceInfo.uiBBitsPerPixel, DestInfo.uiBBitsPerPixel);
				else
					DB = SB;
			}

			if(uiSourceAMask && uiDestAMask)
			{
				if(DestInfo.uiABitsPerPixel < SourceInfo.uiABitsPerPixel)	// downsample
					DA = Shrink<vlUInt16>(SA, SourceInfo.uiABitsPerPixel, DestInfo.uiABitsPerPixel);
				else if(DestInfo.uiABitsPerPixel > SourceInfo.uiABitsPerPixel)	// upsample
					DA = Expand<vlUInt16>(SA, SourceInfo.uiABitsPerPixel, DestInfo.uiABitsPerPixel);
				else
					DA = SA;
			}
		}

		// write source to single variable
		U Dest = ((U)(DR & uiDestRMask) << (U)uiDestRShift) | ((U)(DG & uiDestGMask) << (U)uiDestGShift) | ((U)(DB & uiDestBMask) << (U)uiDestBShift) | ((U)(DA & uiDestAMask) << (U)uiDestAShift);
		for(i = 0; i < DestInfo.uiBytesPerPixel; i++)
		{
			lpDest[i] = (vlByte)((Dest >> ((T)i * 8)) & 0xff);
		}
	}

	return vlTrue;
}

vlBool CVTFFile::Convert(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat, VTFImageFormat DestFormat, vlUInt nAlphaThreshold)
{
	assert(lpSource != 0);
	assert(lpDest != 0);

	assert(SourceFormat >= 0 && SourceFormat < IMAGE_FORMAT_COUNT);
	assert(DestFormat >= 0 && DestFormat < IMAGE_FORMAT_COUNT);

	const SVTFImageConvertInfo& SourceInfo = VTFImageConvertInfo[SourceFormat];
	const SVTFImageConvertInfo& DestInfo = VTFImageConvertInfo[DestFormat];

	if(!SourceInfo.bIsSupported || !DestInfo.bIsSupported)
	{
		LastError.Set("Image format conversion not supported.");

		return vlFalse;
	}

	// Optimize common convertions.
	if(SourceFormat == DestFormat)
	{
		memcpy( lpDest, lpSource, CVTFFile::ComputeImageSize(uiWidth, uiHeight, 1, DestFormat));
		return vlTrue;
	}

	if(SourceFormat == IMAGE_FORMAT_RGB888 && DestFormat == IMAGE_FORMAT_RGBA8888)
	{
		vlByte *lpLast = lpSource + CVTFFile::ComputeImageSize(uiWidth, uiHeight, 1, SourceFormat);
		for(; lpSource < lpLast; lpSource += 3, lpDest += 4)
		{
			lpDest[0] = lpSource[0];
			lpDest[1] = lpSource[1];
			lpDest[2] = lpSource[2];
			lpDest[3] = 255;
		}
		return vlTrue;
	}

	if(SourceFormat == IMAGE_FORMAT_RGBA8888 && DestFormat == IMAGE_FORMAT_RGB888)
	{
		vlByte *lpLast = lpSource + CVTFFile::ComputeImageSize(uiWidth, uiHeight, 1, SourceFormat);
		for(; lpSource < lpLast; lpSource += 4, lpDest += 3)
		{
			lpDest[0] = lpSource[0];
			lpDest[1] = lpSource[1];
			lpDest[2] = lpSource[2];
		}
		return vlTrue;
	}

	// Do general convertions.
	if(SourceInfo.bIsCompressed || DestInfo.bIsCompressed)
	{
		vlByte *lpSourceRGBA = lpSource;
		vlBool bResult = vlTrue;

		// allocate temp data for intermittent conversions
		if(SourceFormat != IMAGE_FORMAT_RGBA8888)
		{
			lpSourceRGBA = new vlByte[CVTFFile::ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)];
		}

		// decompress the source or convert it to RGBA for compressing
		switch(SourceFormat)
		{
		case IMAGE_FORMAT_RGBA8888:
			break;
		case IMAGE_FORMAT_DXT1:
		case IMAGE_FORMAT_DXT1_ONEBITALPHA:
		case IMAGE_FORMAT_DXT3:
		case IMAGE_FORMAT_DXT5:
			bResult = CVTFFile::DecompressDXTn(lpSource, lpSourceRGBA, uiWidth, uiHeight, SourceFormat);
			break;
		default:
			bResult = CVTFFile::Convert(lpSource, lpSourceRGBA, uiWidth, uiHeight, SourceFormat, IMAGE_FORMAT_RGBA8888);
			break;
		}

		if(bResult)
		{
			// compress the source or convert it to the dest format if it is not compressed
			switch(DestFormat)
			{
			case IMAGE_FORMAT_DXT1:
			case IMAGE_FORMAT_DXT1_ONEBITALPHA:
			case IMAGE_FORMAT_DXT3:
			case IMAGE_FORMAT_DXT5:
				bResult = CVTFFile::CompressDXTn(lpSourceRGBA, lpDest, uiWidth, uiHeight, DestFormat, nAlphaThreshold);
				break;
			default:
				bResult = CVTFFile::Convert(lpSourceRGBA, lpDest, uiWidth, uiHeight, IMAGE_FORMAT_RGBA8888, DestFormat);
				break;
			}
		}

		// free temp data
		if(lpSourceRGBA != lpSource)
		{
			delete []lpSourceRGBA;
		}

		return bResult;
	}
	else
	{
		// convert from one variable order and bit format to another
		if(SourceInfo.uiBytesPerPixel <= 1)
		{
			if(DestInfo.uiBytesPerPixel <= 1)
				return ConvertTemplated<vlUInt8, vlUInt8>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 2)
				return ConvertTemplated<vlUInt8, vlUInt16>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 4)
				return ConvertTemplated<vlUInt8, vlUInt32>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 8)
				return ConvertTemplated<vlUInt8, vlUInt64>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
		}
		else if(SourceInfo.uiBytesPerPixel <= 2)
		{
			if(DestInfo.uiBytesPerPixel <= 1)
				return ConvertTemplated<vlUInt16, vlUInt8>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 2)
				return ConvertTemplated<vlUInt16, vlUInt16>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 4)
				return ConvertTemplated<vlUInt16, vlUInt32>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 8)
				return ConvertTemplated<vlUInt16, vlUInt64>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
		}
		else if(SourceInfo.uiBytesPerPixel <= 4)
		{
			if(DestInfo.uiBytesPerPixel <= 1)
				return ConvertTemplated<vlUInt32, vlUInt8>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 2)
				return ConvertTemplated<vlUInt32, vlUInt16>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 4)
				return ConvertTemplated<vlUInt32, vlUInt32>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 8)
				return ConvertTemplated<vlUInt32, vlUInt64>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
		}
		else if(SourceInfo.uiBytesPerPixel <= 8)
		{
			if(DestInfo.uiBytesPerPixel <= 1)
				return ConvertTemplated<vlUInt64, vlUInt8>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 2)
				return ConvertTemplated<vlUInt64, vlUInt16>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 4)
				return ConvertTemplated<vlUInt64, vlUInt32>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
			else if(DestInfo.uiBytesPerPixel <= 8)
				return ConvertTemplated<vlUInt64, vlUInt64>(lpSource, lpDest, uiWidth, uiHeight, SourceInfo, DestInfo);
		}
		return vlFalse;
	}

	return vlFalse;
}

vlBool CVTFFile::Resize(vlByte *lpSourceRGBA8888, vlByte *lpDestRGBA8888, vlUInt uiSourceWidth, vlUInt uiSourceHeight, vlUInt uiDestWidth, vlUInt uiDestHeight, VTFMipmapFilter ResizeFilter, vlBool bSRGB)
{
	assert(ResizeFilter >= 0 && ResizeFilter < MIPMAP_FILTER_COUNT);

	if (!stbir_resize_uint8_generic(
		lpSourceRGBA8888, uiSourceWidth, uiSourceHeight, 0,
		lpDestRGBA8888, uiDestWidth, uiDestHeight, 0,
		4, 3, 0, STBIR_EDGE_CLAMP, stbir_filter(ResizeFilter), bSRGB ? STBIR_COLORSPACE_SRGB : STBIR_COLORSPACE_LINEAR, NULL))
	{
		LastError.Set("Error resizing image.");
		return vlFalse;
	}

	return vlTrue;
}

//
// CorrectImageGamma()
// Do gamma correction on the image data.
//
vlVoid CVTFFile::CorrectImageGamma(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle sGammaCorrection)
{
	if(sGammaCorrection == 1.0f)
	{
		return;
	}

	vlByte bTable[256]{};

	sGammaCorrection = 1.0f / sGammaCorrection;

	// Precalculate all possible gamma correction values.
	for(vlUInt i = 0; i < 256; i++)
	{
		bTable[i] = (vlByte)(pow((vlSingle)i / 255.0f, sGammaCorrection) * 255.0f);
	}

	vlByte *lpImageDataRGBA8888End = lpImageDataRGBA8888 + uiWidth * uiHeight * 4;

	// Do gamma correction on RGB channels.
	for(; lpImageDataRGBA8888 < lpImageDataRGBA8888End; lpImageDataRGBA8888 += 4)
	{
		lpImageDataRGBA8888[0] = bTable[lpImageDataRGBA8888[0]];
		lpImageDataRGBA8888[1] = bTable[lpImageDataRGBA8888[1]];
		lpImageDataRGBA8888[2] = bTable[lpImageDataRGBA8888[2]];
	}
}

//
// ComputeImageReflectivity()
// Compute the image data reflectivity value.
//
vlVoid CVTFFile::ComputeImageReflectivity(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle &sX, vlSingle &sY, vlSingle &sZ)
{
	sX = sY = sZ = 0.0f;

	vlSingle sTable[256]{};

	//
	// Precalculate all possible reflectivity values.
	//

	for(vlUInt i = 0; i < 256; i++)
	{
		sTable[i] = pow((vlSingle)i / 255.0f, 2.2f);
	}

	//
	// Compute reflectivity on RGB channels.
	//

	// This is the method Valve uses.

	/*vlByte *lpImageDataRGBA8888End = lpImageDataRGBA8888 + uiWidth * uiHeight * 4;

	for(; lpImageDataRGBA8888 < lpImageDataRGBA8888End; lpImageDataRGBA8888 += 4)
	{
		sX += sTable[lpImageDataRGBA8888[0]];
		sY += sTable[lpImageDataRGBA8888[1]];
		sZ += sTable[lpImageDataRGBA8888[2]];
	}

	vlSingle sInverse = 1.0f / (vlSingle)(uiWidth * uiHeight);

	sX *= sInverse;
	sY *= sInverse;
	sZ *= sInverse;*/

	// This method is better on floating point limitations for large images then the above.

	vlSingle sTempX, sTempY, sTempZ, sInverse;

	for(vlUInt j = 0; j < uiHeight; j++)
	{
		sTempX = sTempY = sTempZ = 0.0f;

		for(vlUInt i = 0; i < uiWidth; i++)
		{
			vlUInt uiIndex = (i + j * uiWidth) * 4;

			sTempX += sTable[lpImageDataRGBA8888[uiIndex + 0]];
			sTempY += sTable[lpImageDataRGBA8888[uiIndex + 1]];
			sTempZ += sTable[lpImageDataRGBA8888[uiIndex + 2]];
		}

		sInverse = 1.0f / (vlSingle)uiWidth;

		sX += sTempX * sInverse;
		sY += sTempY * sInverse;
		sZ += sTempZ * sInverse;
	}

	sInverse = 1.0f / (vlSingle)uiHeight;

	sX *= sInverse;
	sY *= sInverse;
	sZ *= sInverse;
}

//
// FlipImage()
// Flips image data over the X axis.
//
vlVoid CVTFFile::FlipImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight)
{
	vlUInt *lpImageData = (vlUInt *)lpImageDataRGBA8888;

	for(vlUInt i = 0; i < uiWidth; i++)
	{
		for(vlUInt j = 0; j < uiHeight / 2; j++)
		{
			vlUInt *pOne = lpImageData + (i + j * uiWidth);
			vlUInt *pTwo = lpImageData + (i + (uiHeight - j - 1) * uiWidth);

			vlUInt uiTemp = *pOne;
			*pOne = *pTwo;
			*pTwo = uiTemp;
		}
	}
}

//
// MirrorImage()
// Flips image data over the Y axis.
//
vlVoid CVTFFile::MirrorImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight)
{
	vlUInt *lpImageData = (vlUInt *)lpImageDataRGBA8888;

	for(vlUInt i = 0; i < uiWidth / 2; i++)
	{
		for(vlUInt j = 0; j < uiHeight; j++)
		{
			vlUInt *pOne = lpImageData + (i + j * uiWidth);
			vlUInt *pTwo = lpImageData + ((uiWidth - i - 1) + j * uiWidth);

			vlUInt uiTemp = *pOne;
			*pOne = *pTwo;
			*pTwo = uiTemp;
		}
	}
}
