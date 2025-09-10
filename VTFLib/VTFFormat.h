/*
 * VTFLib
 * Copyright (C) 2005-2011 Neil Jedrzejewski & Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

// ============================================================
// NOTE: This file is commented for compatibility with Doxygen.
// ============================================================
/*!
	\file VTFFormat.h
    \brief Structures and enumerations relating to the VTF file format.
    
	Contains's structures and enumerations relating to the VTF file format.
	
	Disk file format for VTF files is as follows:
	- VTF Header (80 bytes)
	- Low Res Image (size varies)
	- Image Data (size varies)
	
	Image Data is stored as follows:
	- For each MIP images (starting with the smallest and getting larger)
		- For each frame
			- For each face (for cubemaps)
				- For each Z slice
					- Image data (in relevant format)
*/

#ifndef VTFFORMAT_H
#define VTFFORMAT_H

#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif

// VTF version numbers (current version is 7.5)
//---------------------------------------------
#define VTF_MAJOR_VERSION					7		//!< VTF major version number
#define VTF_MINOR_VERSION					5		//!< VTF minor version number
#define VTF_MINOR_VERSION_DEFAULT			3

#define VTF_MINOR_VERSION_MIN_SPHERE_MAP	1
#define VTF_MINOR_VERSION_MIN_VOLUME		2
#define VTF_MINOR_VERSION_MIN_RESOURCE		3
#define VTF_MINOR_VERSION_MIN_NO_SPHERE_MAP	5

//! Image data formats VTFLib supports.
/*!
	Image data formats supported by VTFLib. Details show colour channel order, plus number
	of bits per-pixel.
	\note "Bluescreen" alpha uses any pixel with an pixel of R0, G0, B255 as transparent.
*/
typedef enum tagVTFImageFormat
{
	IMAGE_FORMAT_RGBA8888 = 0,				//!<  = Red, Green, Blue, Alpha - 32 bpp
	IMAGE_FORMAT_ABGR8888,					//!<  = Alpha, Blue, Green, Red - 32 bpp
	IMAGE_FORMAT_RGB888,					//!<  = Red, Green, Blue - 24 bpp
	IMAGE_FORMAT_BGR888,					//!<  = Blue, Green, Red - 24 bpp
	IMAGE_FORMAT_RGB565,					//!<  = Red, Green, Blue - 16 bpp
	IMAGE_FORMAT_I8,						//!<  = Luminance - 8 bpp
	IMAGE_FORMAT_IA88,						//!<  = Luminance, Alpha - 16 bpp
	IMAGE_FORMAT_P8,						//!<  = Paletted - 8 bpp
	IMAGE_FORMAT_A8,						//!<  = Alpha- 8 bpp
	IMAGE_FORMAT_RGB888_BLUESCREEN,			//!<  = Red, Green, Blue, "BlueScreen" Alpha - 24 bpp
	IMAGE_FORMAT_BGR888_BLUESCREEN,			//!<  = Red, Green, Blue, "BlueScreen" Alpha - 24 bpp
	IMAGE_FORMAT_ARGB8888,					//!<  = Alpha, Red, Green, Blue - 32 bpp
	IMAGE_FORMAT_BGRA8888,					//!<  = Blue, Green, Red, Alpha - 32 bpp
	IMAGE_FORMAT_DXT1,						//!<  = DXT1 compressed format - 4 bpp
	IMAGE_FORMAT_DXT3,						//!<  = DXT3 compressed format - 8 bpp
	IMAGE_FORMAT_DXT5,						//!<  = DXT5 compressed format - 8 bpp
	IMAGE_FORMAT_BGRX8888,					//!<  = Blue, Green, Red, Unused - 32 bpp
	IMAGE_FORMAT_BGR565,					//!<  = Blue, Green, Red - 16 bpp
	IMAGE_FORMAT_BGRX5551,					//!<  = Blue, Green, Red, Unused - 16 bpp
	IMAGE_FORMAT_BGRA4444,					//!<  = Red, Green, Blue, Alpha - 16 bpp
	IMAGE_FORMAT_DXT1_ONEBITALPHA,			//!<  = DXT1 compressed format with 1-bit alpha - 4 bpp
	IMAGE_FORMAT_BGRA5551,					//!<  = Blue, Green, Red, Alpha - 16 bpp
	IMAGE_FORMAT_UV88,						//!<  = 2 channel format for DuDv/Normal maps - 16 bpp
	IMAGE_FORMAT_UVWQ8888,					//!<  = 4 channel format for DuDv/Normal maps - 32 bpp
	IMAGE_FORMAT_RGBA16161616F,				//!<  = Red, Green, Blue, Alpha - 64 bpp
	IMAGE_FORMAT_RGBA16161616,				//!<  = Red, Green, Blue, Alpha signed with mantissa - 64 bpp
	IMAGE_FORMAT_UVLX8888,					//!<  = 4 channel format for DuDv/Normal maps - 32 bpp
	IMAGE_FORMAT_R32F,						//!<  = Luminance - 32 bpp
	IMAGE_FORMAT_RGB323232F,				//!<  = Red, Green, Blue - 96 bpp
	IMAGE_FORMAT_RGBA32323232F,				//!<  = Red, Green, Blue, Alpha - 128 bpp
	IMAGE_FORMAT_NV_DST16,
	IMAGE_FORMAT_NV_DST24,					
	IMAGE_FORMAT_NV_INTZ,
	IMAGE_FORMAT_NV_RAWZ,
	IMAGE_FORMAT_ATI_DST16,
	IMAGE_FORMAT_ATI_DST24,
	IMAGE_FORMAT_NV_NULL,
	IMAGE_FORMAT_ATI1N,						
	IMAGE_FORMAT_ATI2N,
	IMAGE_FORMAT_HDR_BGRA8888,				//!<  = Blue, Green, Red, Alpha - 32 bpp (HDR encoding)
	/*
	XBox:
	IMAGE_FORMAT_X360_DST16,
	IMAGE_FORMAT_X360_DST24,
	IMAGE_FORMAT_X360_DST24F,
	IMAGE_FORMAT_LINEAR_BGRX8888,			//!<  = Blue, Green, Red, Unused - 32 bpp		
	IMAGE_FORMAT_LINEAR_RGBA8888,			//!<  = Red, Green, Blue, Alpha - 32 bpp
	IMAGE_FORMAT_LINEAR_ABGR8888,			//!<  = Alpha, Blue, Green, Red - 32 bpp
	IMAGE_FORMAT_LINEAR_ARGB8888,			//!<  = Alpha, Red, Green, Blue - 32 bpp
	IMAGE_FORMAT_LINEAR_BGRA8888,			//!<  = Blue, Green, Red, Alpha - 32 bpp
	IMAGE_FORMAT_LINEAR_RGB888,				//!<  = Red, Green, Blue - 24 bpp
	IMAGE_FORMAT_LINEAR_BGR888,				//!<  = Blue, Green, Red - 24 bpp
	IMAGE_FORMAT_LINEAR_BGRX5551,			//!<  = Blue, Green, Red, Unused - 16 bpp
	IMAGE_FORMAT_LINEAR_I8,					//!<  = Luminance - 8 bpp
	IMAGE_FORMAT_LINEAR_RGBA16161616,		//!<  = Red, Green, Blue, Alpha signed with mantissa - 64 bpp
	IMAGE_FORMAT_LE_BGRX8888,				//!<  = Blue, Green, Red, Unused - 32 bpp
	IMAGE_FORMAT_LE_BGRA8888,				//!<  = Blue, Green, Red, Alpha - 32 bpp
	*/
	IMAGE_FORMAT_COUNT,
	IMAGE_FORMAT_NONE = -1
} VTFImageFormat;


//! VTF image header flags.
typedef enum tagVTFImageFlag
{
	TEXTUREFLAGS_POINTSAMPLE								= 0x00000001,
	TEXTUREFLAGS_TRILINEAR									= 0x00000002,
	TEXTUREFLAGS_CLAMPS										= 0x00000004,
	TEXTUREFLAGS_CLAMPT										= 0x00000008,
	TEXTUREFLAGS_ANISOTROPIC								= 0x00000010,
	TEXTUREFLAGS_HINT_DXT5									= 0x00000020,
	TEXTUREFLAGS_SRGB										= 0x00000040, // Originally internal to VTex as TEXTUREFLAGS_NOCOMPRESS.
	TEXTUREFLAGS_DEPRECATED_NOCOMPRESS						= 0x00000040,
	TEXTUREFLAGS_NORMAL										= 0x00000080,
	TEXTUREFLAGS_NOMIP										= 0x00000100,
	TEXTUREFLAGS_NOLOD										= 0x00000200,
	TEXTUREFLAGS_MINMIP										= 0x00000400,
	TEXTUREFLAGS_PROCEDURAL									= 0x00000800,
	TEXTUREFLAGS_ONEBITALPHA								= 0x00001000, //!< Automatically generated by VTex.
	TEXTUREFLAGS_EIGHTBITALPHA								= 0x00002000, //!< Automatically generated by VTex.
	TEXTUREFLAGS_ENVMAP										= 0x00004000,
	TEXTUREFLAGS_RENDERTARGET								= 0x00008000,
	TEXTUREFLAGS_DEPTHRENDERTARGET							= 0x00010000,
	TEXTUREFLAGS_NODEBUGOVERRIDE							= 0x00020000,
	TEXTUREFLAGS_SINGLECOPY									= 0x00040000,
	TEXTUREFLAGS_UNUSED0									= 0x00080000, //!< Originally internal to VTex as TEXTUREFLAGS_ONEOVERMIPLEVELINALPHA.
	TEXTUREFLAGS_DEPRECATED_ONEOVERMIPLEVELINALPHA			= 0x00080000,
	TEXTUREFLAGS_UNUSED1									= 0x00100000, //!< Originally internal to VTex as TEXTUREFLAGS_PREMULTCOLORBYONEOVERMIPLEVEL.
	TEXTUREFLAGS_DEPRECATED_PREMULTCOLORBYONEOVERMIPLEVEL	= 0x00100000,
	TEXTUREFLAGS_UNUSED2									= 0x00200000, //!< Originally internal to VTex as TEXTUREFLAGS_NORMALTODUDV.
	TEXTUREFLAGS_DEPRECATED_NORMALTODUDV					= 0x00200000,
	TEXTUREFLAGS_UNUSED3									= 0x00400000, //!< Originally internal to VTex as TEXTUREFLAGS_ALPHATESTMIPGENERATION.
	TEXTUREFLAGS_DEPRECATED_ALPHATESTMIPGENERATION			= 0x00400000,
	TEXTUREFLAGS_NODEPTHBUFFER								= 0x00800000,
	TEXTUREFLAGS_UNUSED4									= 0x01000000, //!< Originally internal to VTex as TEXTUREFLAGS_NICEFILTERED.
	TEXTUREFLAGS_DEPRECATED_NICEFILTERED					= 0x01000000,
	TEXTUREFLAGS_CLAMPU										= 0x02000000,
	TEXTUREFLAGS_VERTEXTEXTURE								= 0x04000000,
	TEXTUREFLAGS_SSBUMP										= 0x08000000,
	TEXTUREFLAGS_UNUSED5									= 0x10000000, //!< Originally TEXTUREFLAGS_UNFILTERABLE_OK.
	TEXTUREFLAGS_DEPRECATED_UNFILTERABLE_OK					= 0x10000000,
	TEXTUREFLAGS_BORDER										= 0x20000000,
	TEXTUREFLAGS_DEPRECATED_SPECVAR_RED						= 0x40000000,
	TEXTUREFLAGS_DEPRECATED_SPECVAR_ALPHA					= 0x80000000,
	TEXTUREFLAGS_LAST										= 0x20000000,
	TEXTUREFLAGS_COUNT										= 30
} VTFImageFlag;

//! VTF image cubemap face indices.
typedef enum tagVTFCubeMapFace
{
	CUBEMAP_FACE_RIGHT = 0,		// +x
	CUBEMAP_FACE_LEFT,			// -x
	CUBEMAP_FACE_BACK,			// +y
	CUBEMAP_FACE_FRONT,			// -y
	CUBEMAP_FACE_UP,			// +z
	CUBEMAP_FACE_DOWN,			// -z
	CUBEMAP_FACE_SphereMap,		// fall back
	CUBEMAP_FACE_COUNT
} VTFCubeMapFace;

//! MIP map reduction filter indices.
typedef enum tagVTFMipmapFilter
{
    MIPMAP_FILTER_POINT = 0,
    MIPMAP_FILTER_BOX,
    MIPMAP_FILTER_TRIANGLE, 
    MIPMAP_FILTER_QUADRATIC,
    MIPMAP_FILTER_CUBIC,
    MIPMAP_FILTER_CATROM, 
    MIPMAP_FILTER_MITCHELL,
    MIPMAP_FILTER_GAUSSIAN,
    MIPMAP_FILTER_SINC,
    MIPMAP_FILTER_BESSEL,
    MIPMAP_FILTER_HANNING,
    MIPMAP_FILTER_HAMMING,
    MIPMAP_FILTER_BLACKMAN,
    MIPMAP_FILTER_KAISER,
    MIPMAP_FILTER_COUNT
} VTFMipmapFilter;

#define KERNEL_FILTER_BASE 1040

//! Normal map creation kernel size indices.
typedef enum tagVTFKernelFilter
{
	KERNEL_FILTER_4X = 0,
	KERNEL_FILTER_3X3,
	KERNEL_FILTER_5X5,
	KERNEL_FILTER_7X7,
	KERNEL_FILTER_9X9,
	KERNEL_FILTER_DUDV,
	KERNEL_FILTER_COUNT
} VTFKernelFilter;

#define HEIGHT_CONVERSION_METHOD_BASE 1009

//! Normal map height conversion method indices.
typedef enum tagVTFHeightConversionMethod
{
    HEIGHT_CONVERSION_METHOD_ALPHA = 0,
    HEIGHT_CONVERSION_METHOD_AVERAGE_RGB,
    HEIGHT_CONVERSION_METHOD_BIASED_RGB,
    HEIGHT_CONVERSION_METHOD_RED,
    HEIGHT_CONVERSION_METHOD_GREEN,
    HEIGHT_CONVERSION_METHOD_BLUE,
    HEIGHT_CONVERSION_METHOD_MAX_RGB,
    HEIGHT_CONVERSION_METHOD_COLORSPACE,
    //HEIGHT_CONVERSION_METHOD_NORMALIZE,
	HEIGHT_CONVERSION_METHOD_COUNT
} VTFHeightConversionMethod;

#define NORMAL_ALPHA_RESULT_BASE 1033

//! Normal map alpha channel handling indices.
typedef enum tagVTFNormalAlphaResult
{
	NORMAL_ALPHA_RESULT_NOCHANGE = 0,
    NORMAL_ALPHA_RESULT_HEIGHT,
    NORMAL_ALPHA_RESULT_BLACK,
    NORMAL_ALPHA_RESULT_WHITE,
	NORMAL_ALPHA_RESULT_COUNT
} VTFNormalAlphaResult;

//! Image re-size handling method indices.
typedef enum tagVTFResizeMethod
{
    RESIZE_NEAREST_POWER2 = 0,
    RESIZE_BIGGEST_POWER2,
    RESIZE_SMALLEST_POWER2,
    RESIZE_NEAREST_MULTIPLE4,
    RESIZE_SET,
    RESIZE_COUNT
} VTFResizeMethod;

//! Spheremap creation look direction indices.
//--------------------------------------------
typedef enum tagVTFLookDir
{
	LOOK_DOWN_X = 0,
	LOOK_DOWN_NEGX,
	LOOK_DOWN_Y,
	LOOK_DOWN_NEGY,
	LOOK_DOWN_Z,
	LOOK_DOWN_NEGZ
} VTFLookDir;

#define MAKE_VTF_RSRC_ID(a, b, c) ((vlUInt)(((vlByte)a) | ((vlByte)b << 8) | ((vlByte)c << 16)))
#define MAKE_VTF_RSRC_IDF(a, b, c, d) ((vlUInt)(((vlByte)a) | ((vlByte)b << 8) | ((vlByte)c << 16) | ((vlByte)d << 24)))

//! Resource entry type flags.
//--------------------------------------------
typedef enum tagVTFResourceEntryTypeFlag
{
	RSRCF_HAS_NO_DATA_CHUNK = 0x02
} VTFResourceEntryTypeFlag;

//! Resource entry type idendifiers.
//--------------------------------------------
typedef enum tagVTFResourceEntryType
{
	VTF_LEGACY_RSRC_LOW_RES_IMAGE = MAKE_VTF_RSRC_ID(0x01, 0, 0),
	VTF_LEGACY_RSRC_IMAGE = MAKE_VTF_RSRC_ID(0x30, 0, 0),
	VTF_RSRC_SHEET = MAKE_VTF_RSRC_ID(0x10, 0, 0),
	VTF_RSRC_CRC = MAKE_VTF_RSRC_IDF('C', 'R', 'C', RSRCF_HAS_NO_DATA_CHUNK),
	VTF_RSRC_TEXTURE_LOD_SETTINGS = MAKE_VTF_RSRC_IDF('L', 'O', 'D', RSRCF_HAS_NO_DATA_CHUNK),
	VTF_RSRC_TEXTURE_SETTINGS_EX = MAKE_VTF_RSRC_IDF('T', 'S', 'O', RSRCF_HAS_NO_DATA_CHUNK),
	VTF_RSRC_KEY_VALUE_DATA = MAKE_VTF_RSRC_ID('K', 'V', 'D'),
	VTF_RSRC_MAX_DICTIONARY_ENTRIES = 32
} VTFResourceEntryType;

#pragma pack(1)

//! VTFFileHeader struct.
/*!

	The VTF file header sits at the start of a VTF file and is used to
	determine which version of the file is being loaded.
*/
struct SVTFFileHeader
{
	vlChar			TypeString[4];					//!< "Magic number" identifier- "VTF\0".
	vlUInt			Version[2];						//!< Version[0].version[1] (currently 7.2)
	vlUInt			HeaderSize;						//!< Size of the header struct (currently 80 bytes)				
};

//! VTFHeader_70 struct.
/*!

	The complete header for v7.0 of the VTF file format.
*/
struct SVTFHeader_70 : public SVTFFileHeader
{
	vlUShort		Width;							//!< Width of the largest image
	vlUShort		Height;							//!< Height of the largest image
	vlUInt			Flags;							//!< Flags for the image
	vlUShort		Frames;							//!< Number of frames if animated (1 for no animation)
	vlUShort		StartFrame;						//!< Start frame (always 0)
	vlByte			Padding0[4];					//!< Reflectivity padding (16 byte alignment)
	vlSingle		Reflectivity[3];				//!< Reflectivity vector
	vlByte			Padding1[4];					//!< Reflectivity padding (8 byte packing)
	vlSingle		BumpScale;						//!< Bump map scale
	VTFImageFormat	ImageFormat;					//!< Image format index
	vlByte			MipCount;						//!< Number of MIP levels (including the largest image)
	VTFImageFormat	LowResImageFormat;				//!< Image format of the thumbnail image
	vlByte			LowResImageWidth;				//!< Thumbnail image width
	vlByte			LowResImageHeight;				//!< Thumbnail image height
};

//! VTFHeader_70_A struct.
/*!

	The complete header for v7.0 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_70_A : public SVTFHeader_70 {};

//! VTFHeader_71 struct.
/*!

	The complete header for v7.1 of the VTF file format.
*/
struct SVTFHeader_71 : public SVTFHeader_70
{

};

//! VTFHeader_71_A struct.
/*!

	The complete header for v7.1 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_71_A : public SVTFHeader_71 {};

//! VTFHeader_72 struct.
/*!

	The complete header for v7.2 of the VTF file format.
*/
struct SVTFHeader_72 : public SVTFHeader_71
{
	vlUShort		Depth;							//!< Depth of the largest image
};

//! VTFHeader_72_A struct.
/*!

	The complete header for v7.2 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_72_A : public SVTFHeader_72 {};

//! VTFHeader_73 struct.
/*!

	The complete header for v7.3 of the VTF file format.
*/
struct SVTFHeader_73 : public SVTFHeader_72
{
	vlByte		Padding2[3];
	vlUInt		ResourceCount;							//!< Number of image resources
};

//! VTFHeader_72_A struct.
/*!

	The complete header for v7.3 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_73_A : public SVTFHeader_73 {};

//! VTFHeader_74 struct.
/*!

	The complete header for v7.4 of the VTF file format.
*/
struct SVTFHeader_74 : public SVTFHeader_73
{

};

//! VTFHeader_74_A struct.
/*!

	The complete header for v7.4 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_74_A : public SVTFHeader_74 {};

//! VTFHeader_75 struct.
/*!

	The complete header for v7.5 of the VTF file format.
*/
struct SVTFHeader_75 : public SVTFHeader_74
{

};

//! VTFHeader_75_A struct.
/*!

	The complete header for v7.5 of the VTF file format aligned to 16 bytes.
*/
__declspec(align(16)) struct SVTFHeader_75_A : public SVTFHeader_75 {};

struct SVTFResource
{
	union
	{ 
		vlUInt Type;
		struct
		{
			vlByte ID[3];	//!< Unique resource ID
			vlByte Flags;	//!< Resource flags
		};
	};
	vlUInt Data;	//!< Resource data (e.g. for a  CRC) or offset from start of the file
};

struct SVTFResourceData
{
	vlUInt Size;	//!< Resource data buffer size
	vlByte *Data;	//!< Resource data bufffer
};

typedef struct tagSVTFTextureLODControlResource
{
	vlByte ResolutionClampU;
	vlByte ResolutionClampV;
	vlByte Padding[2];
} SVTFTextureLODControlResource;

typedef struct tagSVTFTextureSettingsExResource
{
	vlByte Flags0;
	vlByte Flags1;
	vlByte Flags2;
	vlByte Flags3;
} SVTFTextureSettingsExResource;

struct SVTFHeader : public SVTFHeader_74_A
{
	vlByte				Padding3[8];
	SVTFResource		Resources[VTF_RSRC_MAX_DICTIONARY_ENTRIES];
	SVTFResourceData	Data[VTF_RSRC_MAX_DICTIONARY_ENTRIES];
};

#pragma pack()

#ifdef __cplusplus
}
#endif

#endif // VTFFORMAT_H