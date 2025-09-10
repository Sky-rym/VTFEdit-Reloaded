/*
 * VTFLib
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg

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
	\file VTFFile.h
	\brief Header file for the VTFFile class.
*/

#ifndef VTFFILE_H
#define VTFFILE_H

#include "stdafx.h"
#include "Readers.h"
#include "Writers.h"
#include "VTFFormat.h"

#ifdef __cplusplus
extern "C" {
#endif

//! VTFImageFormat info struct.
/*!  
	The SVTFImageFormatInfo struct provides information on VTF image formats.

	\see VTFImageFormat
*/
#pragma pack(1)
typedef struct tagSVTFImageFormatInfo
{
	const vlChar *lpName;			//!< Enumeration text equivalent.
	vlUInt	uiBitsPerPixel;			//!< Format bits per pixel.
	vlUInt	uiBytesPerPixel;		//!< Format bytes per pixel.
	vlUInt	uiRedBitsPerPixel;		//!< Format red bits per pixel.  0 for N/A.
	vlUInt	uiGreenBitsPerPixel;	//!< Format green bits per pixel.  0 for N/A.
	vlUInt	uiBlueBitsPerPixel;		//!< Format blue bits per pixel.  0 for N/A.
	vlUInt	uiAlphaBitsPerPixel;	//!< Format alpha bits per pixel.  0 for N/A.
	vlBool	bIsCompressed;			//!< Format is compressed (DXT).
	vlBool	bIsSupported;			//!< Format is supported by VTFLib.
} SVTFImageFormatInfo;
#pragma pack()

//! VTF Creation options struct.
/*!  
	The SVTFCreateOptions struct defines options and settings to be used when
	creating VTF images	with methods such as CVTFFile::Create().

	\see CVTFFile::Create()
*/
#pragma pack(1)
typedef struct tagSVTFCreateOptions
{
	vlUInt uiVersion[2];								//!< Output image version.
	VTFImageFormat ImageFormat;							//!< Output image output storage format.

	vlUInt uiFlags;										//!< Output image header flags.
	vlUInt uiStartFrame;								//!< Output image start frame.
	vlSingle sBumpScale;								//!< Output image bump scale.
	vlSingle sReflectivity[3];							//!< Output image reflectivity. (Only used if bReflectivity is false.)

	vlBool bMipmaps;									//!< Generate MIPmaps. (Space is always allocated.)
	VTFMipmapFilter MipmapFilter;						//!< MIP map re-size filter.

	vlBool bThumbnail;									//!< Generate thumbnail image.
	vlBool bReflectivity;								//!< Compute image reflectivity.

	vlBool bResize;										//!< Resize the input image.
	VTFResizeMethod ResizeMethod;						//!< New size compution method.
	VTFMipmapFilter ResizeFilter;						//!< Re-size filter.
	vlUInt uiResizeWidth;								//!< New width after re-size if method is RESIZE_SET.
	vlUInt uiResizeHeight;								//!< New height after re-size if method is RESIZE_SET.

	vlBool bResizeClamp;								//!< Clamp re-size size.
	vlUInt uiResizeClampWidth;							//!< Maximum width to re-size to.
	vlUInt uiResizeClampHeight;							//!< Maximum height to re-size to.

	vlBool bGammaCorrection;							//!< Gamma correct input image.
	vlSingle sGammaCorrection;							//!< Gamma correction to apply.

	vlBool bSphereMap;									//!< Generate a sphere map for six faced environment maps.
	vlBool bSRGB;										//!< Texture is in the SRGB color space.

	vlUInt nAlphaThreshold;								//!< Alpha threshold for One Bit Alpha. Pixel alpha below this value is set to 0.
} SVTFCreateOptions;
#pragma pack()

#ifdef __cplusplus
}
#endif

namespace VTFLib
{
	//! VTF File access/creation class.
	/*!
		The CVTFFile class is the component designed for working with VTF
		format image files. Its public functions allow you to load, save
		and create new VTF files plus perform various processes on the
		image data such as the generation of MIP maps or Normal maps.

		VTFFile generally use RGBA8888 format for passing data to and from
		functions. This is 4 bytes per pixel, 8-bits per channel colour or
		in short, uncompressed 32-bit image data. There are functions for
		converting the data to other formats internally, however for image
		creation you are probably sticking best with RGBA8888 for simplicity.
	 
		The majority of functions return a vlBool value. This is simply a
		test as to whether a function has succeeded or failed to execute properly.
		In the case of functions for checking flags, the vlBool indicates
		if the flag is set or unset. Other data types reflect the purpose
		of the function used.
	*/
	class VTFLIB_API CVTFFile
	{
	private:

		SVTFHeader *Header;						// VTF header
	
		vlUInt uiImageBufferSize;				// Size of VTF image data buffer
		vlByte *lpImageData;					// VTF image buffer

		vlUInt uiThumbnailBufferSize;			// Size of VTF thumbnail image data buffer
		vlByte *lpThumbnailImageData;			// VTF thumbnail image buffer

	public:

		CVTFFile();		//!< Default constructor

		//! Create a new VTFFile class as a copy of another.
		/*!
			Creates a new VTFFile class as a copy of an existing one. The copy is not linked
			so any changes to it will not effect the class instance it was derived from.

			\param VTFFile is the CVTFFile class you want to copy.
		*/
		CVTFFile(const CVTFFile &VTFFile);

		//! Create a new VTFFile class as a duplicate of another.
		/*!
			Create a new VTFFile class as a duplicate of an existing one, but convert
			the image data to the specified format.

			\param VTFFile is the CVTFFile class you want to copy.
			\param ImageFormat the format you want to convert the copied image data to.
		*/
		CVTFFile(const CVTFFile &VTFFile, VTFImageFormat ImageFormat);

		~CVTFFile();	//!< Deconstructor

	public:
		
		//! Creates a new empty VTF image..
		/*!
			Creates a new empty VTF format image within a the current CVTFFile class.

			\param uiWidth is the width in pixels of the main VTF image.
			\param uiHeight is the height in pixels of the main VTF image.
			\param uiFrames is the number of frames in the VTF image (default 1).
			\param uiFaces is the number of faces in the VTF image (default 1).
			\param uiSlices is the number of z slices in the VTF image (default 1).
			\param ImageFormat is the storage format of the main VTF image (default RGBA8888).
			\param bThumbnail sets if the VTF image will contain an additional thumbnail (default true).
			\param bNullImageData sets if the image data should be zero'd out on creation (default false).
			\return true on successful creation, otherwise false.
			\note Animated and static textures have 1 face. Cubemaps have 6, one for each side of the cube.
			\see tagSVTFCreateOptions
		*/
		vlBool Create(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames = 1, vlUInt uiFaces = 1, vlUInt uiSlices = 1, VTFImageFormat ImageFormat = IMAGE_FORMAT_RGBA8888, vlBool bThumbnail = vlTrue, vlBool bMipmaps = vlTrue, vlBool bNullImageData = vlFalse);
		
		//! Create a new VTF image from existing data.
		/*!
			Creates a new VTF image using image data already stored in memory. The existing
			image data should be stored in RGBA8888 format.
			
			\param uiWidth is the width in pixels of the main VTF image.
			\param uiHeight is the height in pixels of the main VTF image.
			\param lpImageDataRGBA8888 is a pointer to the source RGBA8888 data.
			\param VTFCreateOptions contains the options for image creation.
			\return true on successful creation, otherwise false.
			\see tagSVTFCreateOptions
		*/
		vlBool Create(vlUInt uiWidth, vlUInt uiHeight, vlByte *lpImageDataRGBA8888, const SVTFCreateOptions &VTFCreateOptions);

		//! Create a new VTF multi-frame or cubemap image from existing data.
		/*!
			Creates a new multi-frame or cubemap VTF image using image data already stored
			in memory. The existing image data should be stored in RGBA8888 format.
			
			\param uiWidth is the width in pixels of the main VTF image.
			\param uiHeight is the height in pixels of the main VTF image.
			\param uiFrames is the number of frames in the VTF image.
			\param uiFaces is the number of faces in the VTF image.
			\param vlSlices is the number of z slices in the VTF image.
			\param lpImageDataRGBA8888 is an array of pointers to the image data for each frame/face.
			\param VTFCreateOptions contains the options for image creation.
			\return true on successful creation, otherwise false.
			\note Animated and static textures have 1 face. Cubemaps have 6, one for each side of the cube.
			\see tagSVTFCreateOptions
		*/
		vlBool Create(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiFrames, vlUInt uiFaces, vlUInt vlSlices, vlByte **lpImageDataRGBA8888, const SVTFCreateOptions &VTFCreateOptions);
		
		//! Destroys the current VTF image by setting the header, thumbnail and image data to zero.
		vlVoid Destroy();

		//! Check if a VTFFile image is loaded or valid.
		/*!
			Checks if a file was loaded or a new image was created correctly by
			checking for the existance of a valid header struct in the VTFFile class.

			\return true if header is valid, otherwise false.
			\see Create()
		*/
		vlBool IsLoaded() const;

		//! Loads a VTF image from disk.
		/*!
			Loads a VTF image file from disk into the current VTFFile class. You may choose to
			load just the header only if you want to get info about the file and save memory.

			\param cFileName is the path and filename of the file to load.
			\param bHeaderOnly sets whether to load just the VTF header or not (default false).
			\return true on sucessful load, otherwise false.
		*/
		vlBool Load(const vlChar *cFileName, vlBool bHeaderOnly = vlFalse);

		//! Loads a VTF image from memory. 
		/*!
			Loads a VTF image file stored in memory into the current VTFFile class.
			You may choose to load just the header only if you want to get info about the file
			and save memory.

			\param lpData is a pointer to the VTF file in memory.
			\param uiBufferSize is the size of the VTF file in bytes.
			\param bHeaderOnly sets whether to load just the VTF header or not (default false).
			\return true on sucessful load, otherwise false.
		*/
		vlBool Load(const vlVoid *lpData, vlUInt uiBufferSize, vlBool bHeaderOnly = vlFalse);

		//! Loads a VTF image using callback functions. 
		/*!
			Loads a VTF image file into the current VTFFile class.
			You may choose to load just the header only if you want to get info about the file
			and save memory.

			\param pUserData is a pointer to custom user data.
			\param bHeaderOnly sets whether to load just the VTF header or not (default false).
			\return true on sucessful load, otherwise false.
		*/
		vlBool Load(vlVoid *pUserData, vlBool bHeaderOnly = vlFalse);

		//! Save a VTF image from disk.
		/*!
			Saves a VTF format image file to disk from the current VTFFile class.

			\param cFileName is the path and filename of the file to load.
			\return true on sucessful save, otherwise false.
		*/
		vlBool Save(const vlChar *cFileName) const;

		//! Save a VTF image to memory.
		/*!
			Saves a VTF format image file to memory from the current VTFFile class.

			\param lpData is a pointer to save the image to.
			\param uiBufferSize is the size of the VTF file in bytes.
			\return true on sucessful save, otherwise false.
		*/
		vlBool Save(vlVoid *lpData, vlUInt uiBufferSize, vlUInt &uiSize) const;

		//! Save a VTF image using callback functions.
		/*!
			Saves a VTF format image file from the current VTFFile class.

			\param pUserData is a pointer to custom user data.
			\return true on sucessful save, otherwise false.
		*/
		vlBool Save(vlVoid *pUserData) const;

	private:
		vlBool IsPowerOfTwo(vlUInt uiSize);
		vlUInt NextPowerOfTwo(vlUInt uiSize);
		vlBool IsMultipleOfFour(vlUInt uiSize);
		vlUInt NearestMultipleOfFour(vlUInt uiSize);

		vlVoid ComputeResources();	 //!< Computes header VTF directory resources.

		// Interface with out reader/writer classes
		vlBool Load(IO::Readers::IReader *Reader, vlBool bHeaderOnly);
		vlBool Save(IO::Writers::IWriter *Writer) const;

	public:

		//! Check if image data has been loaded.
		/*!
			Check to see if the image buffer has data in it. If a VTF file was loaded
			into the class with the bHeaderOnly option, this will return false.
			
			\return true if image data is present, otherwise false.
		*/
		vlBool GetHasImage() const;

		vlUInt GetMajorVersion() const;	 //!< Returns the VTF file major version number.
		vlUInt GetMinorVersion() const;	 //!< Returns the VTF file minor version number.
		vlVoid SetMinorVersion(vlUInt version);	 //!< Sets the VTF file minor version number.
		vlUInt GetSize() const;			 //!< Returns the VTF file size in bytes.

		vlUInt GetWidth() const;	//!< Returns the width of the image in pixels from the VTF header.
		vlUInt GetHeight() const;	//!< Returns the height of the image in pixels from the VTF header.
		vlUInt GetDepth() const;	//!< Returns the depth of the image in pixels from the VTF header.

		vlUInt GetFrameCount() const;	//!< Returns the frame count from the VTF header.
		vlUInt GetFaceCount() const;	//!< Returns the face count from the VTF header.
		vlUInt GetMipmapCount() const;	//!< Returns the number of MIP levels in the image from the VTF header.

		vlUInt GetStartFrame() const;				//!< Returns the start frame from the VTF header.
		vlVoid SetStartFrame(vlUInt uiStartFrame);  //!< Sets the start frame in the VTF header.

		vlUInt GetFlags() const;	//!< Returns the image flags from the VTF header.
		vlVoid SetFlags(vlUInt uiFlags); 	//!< Sets the image flags in the VTF header.

		//! Check if a specific flag is set in the VTF header.
		/*!
			Checks to see if the given flag is set in the VTF header struct.

			\param ImageFlag is the flag you wish to check for.
			\return true if the flag is set, otherwise false.
		*/
		vlBool GetFlag(VTFImageFlag ImageFlag) const;

		//! Set the state of a specific flag in the VTF header.
		/*!
			Set the boolean state of the given flag in the VTF header struct.

			\param ImageFlag is the flag you wish to set.
			\param bState is the state you wish to set for the flag.
		*/
		vlVoid SetFlag(VTFImageFlag ImageFlag, vlBool bState);

		vlSingle GetBumpmapScale() const;	//!< Get the bump scale value.
		
		//! Set the bump scale value.
		/*!
			Sets the bump scale in the VTF header to the given floating point value.
			\param sBumpmapScale is the scale value to set.
		*/
		vlVoid SetBumpmapScale(vlSingle sBumpmapScale);

		//! Get the reflectivity values.
		/*!
			Get the reflectivity value for each vector axis from the VTF header.

			\param sX, sY, sZ are the variables to hold the values reflectivity vector.
		*/
		vlVoid GetReflectivity(vlSingle &sX, vlSingle &sY, vlSingle &sZ) const;

		//! Set the reflectivity values.
		/*!
			Set the reflectivity value for each vector axis in the VTF header.

			\param sX, sY, sZ are the values for each reflectivity vector axis.
		*/
		vlVoid SetReflectivity(vlSingle sX, vlSingle sY, vlSingle sZ);

		VTFImageFormat GetFormat() const;	//!< Returns the storage format of the main image data set in the VTF header.
		
		//! Get a pointer to the image data for a specific image.
		/*!
			Returns a pointer to the image data for a given frame, face and MIP level.

			\param uiFrame is the desired frame.
			\param uiFace is the desired face.
			\param uiSlice is the desired z slice.
			\param uiMipmapLevel is the desired MIP level.
			\note Frames start at index 0 for the first frame. Faces start at index 0
			for the first face. Cubemaps have 6 faces, others only 1. MIP levels start
			at index 0 for the largest image moving down in size.
			\see GetFormat()
		*/
		vlByte *GetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel) const;
		
		//! Set the image data for a specific image.
		/*!
			Sets the image data for a given frame, face and MIP level. The source image
			data pointed to by lpData must be in the format specified in the VTF header.
			
			\param uiFrame is the desired frame.
			\param uiFace is the desired face.
			\param uiSlice is the desired z slice.
			\param uiMipmapLevel is the desired MIP level.
			\param lpData is a pointer to the image data.
			\return vlByte pointer to the image data.
			\note Frames start at index 0 for the first frame. Faces start at index 0
			for the first face. Cubemaps have 6 faces, others only 1. MIP levels start
			at index 0 for the largest image moving down in size.
			\see GetFormat()
		*/
		vlVoid SetData(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel, vlByte *lpData);

	public:
		
		vlBool GetHasThumbnail() const;		//!< Returns if a the current VTF image image contains a thumbnail version.

		vlUInt GetThumbnailWidth() const;	//!< Returns the width in pixels of the current images thumbnail.
		vlUInt GetThumbnailHeight() const;	//!< Returns the height in pixels of the current images thumbnail.

		VTFImageFormat GetThumbnailFormat() const;	//!< Returns the image format of the current images thumbnail.

		//! Get a pointer to the thumbnail image data for the current image.
		/*!
			Returns a pointer to the thumbnail image data for the current image.
			\return vlByte pointer to the image data.
			\see GetThumbnailFormat()
		*/
		vlByte *GetThumbnailData() const;

		//! Set the thumbnail image data for the current image.
		/*!
			Sets the thumbnail image data for the current image. The source image
			data pointed to by lpData must be in the format specified for the thumbnail
			in the VTF header.
			
			\param lpData is a pointer to the image data.
			\see GetThumbnailFormat()
		*/
		vlVoid SetThumbnailData(vlByte *lpData);

	public:
		vlBool GetSupportsResources() const;			//!< Returns true if the current VTF file version supports resources.

		vlUInt GetResourceCount() const;				//!< Returns the number of resources contained within the VTF file.
		vlUInt GetResourceType(vlUInt uiIndex) const;	//!< Returns the resource type;
		vlBool GetHasResource(vlUInt uiType) const;		//!< Returns true if the resource exists.

		//! Get a VTF resource type's data.
		/*!
			Checks to see if the resource type exists and returns it's data.

			\param uiType is the resource type to retrieve.
			\param uiSize is the size of the resource data.
			\return a pointer to the resource data buffer if the resource exists.
		*/
		vlVoid *GetResourceData(vlUInt uiType, vlUInt &uiSize) const;

		//! Set a VTF resource type's data.
		/*!
			Set a resource type's data.  If the type deson't exist, the resource is
			created.  If uiSize is 0, the resource is deleted.

			\param uiType is the resource type to set.
			\param uiSize is the size of the resource data; if 0 the resource is deleted, otherwise if the resource does not have a data chunk this must be 4.
			\param lpData is the resource data; if null the resource data is zeroed.
			\return a pointer to the resource data buffer if the resource exists or was created.
		*/
		vlVoid *SetResourceData(vlUInt uiType, vlUInt uiSize, vlVoid *lpData);

	public:

		//! Generate MIP maps from the main image data.
		/*!
			Generates MIP maps for the image down to 1 x 1 pixel using the data in
			MIP level 0 as the source.

			\param MipmapFilter is the reduction filter to use (default Box).
			\param bSRGB is whether we are generating mips for color data or not.
			\return true on sucessful creation, otherwise false.
		*/
		vlBool GenerateMipmaps(VTFMipmapFilter MipmapFilter, vlBool bSRGB);

		//! Generate MIP maps from a specific face and frame.
		/*!
			Generates MIP maps for the image down to 1 x 1 pixel using the data in
			the given face and frame as the source.

			\param uiFace is the face index to use.
			\param uiFrame is the frame index to use.
			\param MipmapFilter is the reduction filter to use (default Box).
			\param bSRGB is whether we are generating mips for color data or not.
			\note Frames start at index 0 for the first frame. Faces start at index 0
			for the first face. Cubemaps have 6 faces, others only 1.
			\return true on sucessful creation, otherwise false.
		*/
		vlBool GenerateMipmaps(vlUInt uiFace, vlUInt uiFrame, VTFMipmapFilter MipmapFilter, vlBool bSRGB);

		//! Generate a thumbnail image.
		/*!
			Generates the thumbnail image for the VTF image by copying an existing MIP map
			of the right size and converting it to the required format.

			\return true on sucessful creation, otherwise false.
			\see SetThumbnailData()
		*/
		vlBool GenerateThumbnail(vlBool bSRGB);

		//! Convert image to a normal map.
		/*!
			Converts the image to a normal map using the image data in
			MIP level 0 as the source.

			\param KernelFilter is the kernel filter to use (default 3x3).
			\param HeightConversionMethod is the method of determining the height data from the source (default average RGB).
			\param NormalAlphaResult is how the alpha channel should be handled post processing (defaul make 100% opaque).
			\return true on sucessful creation, otherwise false.
			\note  The options for conversion are the same used in the nVidea NormalMap Photoshop plug-in.
		*/
		vlBool GenerateNormalMap(VTFKernelFilter KernelFilter = KERNEL_FILTER_3X3, VTFHeightConversionMethod HeightConversionMethod = HEIGHT_CONVERSION_METHOD_AVERAGE_RGB, VTFNormalAlphaResult NormalAlphaResult = NORMAL_ALPHA_RESULT_WHITE);
		
		//! Convert image to a normal map from a specific frame.
		/*!
			Converts the image to a normal map using the image data in
			the given frame as the source.
			
			\param uiFrame is the frame index to use.
			\param KernelFilter is the kernel filter to use (default 3x3).
			\param HeightConversionMethod is the method of determining the height data from the source (default average RGB).
			\param NormalAlphaResult is how the alpha channel should be handled post processing (defaul make 100% opaque).
			\return true on sucessful creation, otherwise false.
			\note  The options for conversion are the same used in the nVidea NormalMap Photoshop plug-in.
		*/
		vlBool GenerateNormalMap(vlUInt uiFrame, VTFKernelFilter KernelFilter = KERNEL_FILTER_3X3, VTFHeightConversionMethod HeightConversionMethod = HEIGHT_CONVERSION_METHOD_AVERAGE_RGB, VTFNormalAlphaResult NormalAlphaResult = NORMAL_ALPHA_RESULT_WHITE);

		vlBool GenerateSphereMap();		//!< Creates a spheremap from using the 6 faces of the image making up its cubemap.

	public:

		vlBool ComputeReflectivity();	//!< Calculates and sets the reflectivity vector values for the VTF image based on the colour averages of each pixel.
	
	public:

		//! Get VTFImageFormat info.
		/*!
			Returns a SImageFormatInfo info struct for the specified VTFImageFormat.

			\param ImageFormat is the format to get info on.
			\return SImageFormatInfo info struct.
		*/
		static SVTFImageFormatInfo const &GetImageFormatInfo(VTFImageFormat ImageFormat);

		//! Calculate data buffer size for an image
		/*!
			Returns the total memory needed in bytes for an image uiWidth and uiHeight in size,
			in the specified format. The result includes the memory used by all MIP map levels
			from the largest dimension down to 1 x 1 pixel.

			\param uiWidth is the width in pixels of the largest MIP level.
			\param uiHeight is the height in pixels of the largest MIP level.
			\param uiDepth is the depth in pixels of the largest MIP level.
			\param ImageFormat is the storage format of the image data.
			\return size of the image data in bytes.
		*/
		static vlUInt ComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, VTFImageFormat ImageFormat);

		//! Calculate data buffer size for an image with MIP maps
		/*!
			Returns the total memory needed in bytes for an image uiWidth and uiHeight in size,
			in the specified format. The result includes the memory used by the number of MIP
			maps given as uiMipmaps starting with the original width and height.

			\param uiWidth is the width in pixels of the largest MIP level.
			\param uiHeight is the height in pixels of the largest MIP level.
			\param uiDepth is the depth in pixels of the largest MIP level.
			\param uiMipmaps is the number of MIP maps to include in the calculation starting with the largest.
			\param ImageFormat is the storage format of the image data.
			\return size of the image data in bytes.
		*/
		static vlUInt ComputeImageSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmaps, VTFImageFormat ImageFormat);

		//! Compute the number of MIP maps needed by an image
		/*!
			Returns how many MIP map levels an image of the specified size will need down to
			1 x 1 pixels. The count includes the original source image.

			\param uiWidth is the width in pixels of the original image.
			\param uiHeight is the height in pixels of the original image.
			\param uiDepth is the depth in pixels of the original image.
			\return number of MIP maps needed.
		*/
		static vlUInt ComputeMipmapCount(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth);	//!< Returns how many MIP map levels are required for an image uiWidth and uiHeight in size, down to 1x1 pixel.

		//! Compute the dimensions of a specific MIP level.
		/*!
			Returns the dimensions of a given MIP level where the largest MIP level
			(level 0) is the specified width and height.

			\param uiWidth is the width in pixels of the largest MIP level.
			\param uiHeight is the height in pixels of the largest MIP level.
			\param uiDepth is the depth in pixels of the largest MIP level.
			\param uiMipmapLevel is the MIP level you want the dimensions of.
			\param uiMipmapWidth is the variable to hold the calculated width.
			\param uiMipmapHeight is the variable to hold the calculated height.
			\param uiMipmapDepth is the variable to hold the calculated depth.
		*/
		static vlVoid ComputeMipmapDimensions(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, vlUInt &uiMipmapWidth, vlUInt &uiMipmapHeight, vlUInt &uiMipmapDepth);
		
		//! Compute how much memory a specific MIP map level needs.
		/*!
			Computers the total memory needed in bytes for the a specific MIP map level 
			of an image of a given width and height stored in the specified image format.

			\param uiWidth is the width in pixels of the source image.
			\param uiHeight is the height in pixels of the source image.
			\param uiDepth is the depth in pixels of the source image.
			\param uiMipmapLevel is the MIP level you want the size of.
			\param ImageFormat is the image format the MIP map image data is stored in.
			\return size of the MIP map image data in bytes.
		*/
		static vlUInt ComputeMipmapSize(vlUInt uiWidth, vlUInt uiHeight, vlUInt uiDepth, vlUInt uiMipmapLevel, VTFImageFormat ImageFormat);

	private:

		// Calculates where in the VTF image the data begins
		vlUInt ComputeDataOffset(vlUInt uiFrame, vlUInt uiFace, vlUInt uiSlice, vlUInt uiMipmapLevel, VTFImageFormat ImageFormat) const;

	public:

		//! Convert an image to RGBA8888 format.
		/*!
			Converts image data stored in the given format to RGBA8888 format.

			\param lpSource is a pointer to the source image data.
			\param lpDest is a pointer to the buffer for the converted data.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param SourceFormat is the image format of the source data.
			\return true on sucessful conversion, otherwise false.
		*/
		static vlBool ConvertToRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat);

		//! Convert an image from RGBA8888 format.
		/*!
			Converts image data stored in RGBA8888 format to the the specified storage format.

			\param lpSource is a pointer to the source image data in RGBA8888 format.
			\param lpDest is a pointer to the buffer for the converted data.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param DestFormat is the image format you wish to convert to.
			\return true on sucessful conversion, otherwise false.
		*/
		static vlBool ConvertFromRGBA8888(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat DestFormat, vlUInt nAlphaThreshold = 0);

		//! Convert an image from any format to any format.
		/*!
			Converts image data stored in any format to the the specified storage format.

			\param lpSource is a pointer to the source image data.
			\param lpDest is a pointer to the buffer for the converted data.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param SourceFormat is the image format you are converting from.
			\param DestFormat is the image format you wish to convert to.
			\return true on sucessful conversion, otherwise false.
		*/
		static vlBool Convert(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat, VTFImageFormat DestFormat, vlUInt nAlphaThreshold = 0);

		//! Re-sizes an image.
		/*!
			Re-sizes an image in RGBA8888 format to the given dimensions using the specified filters.

			\param lpSourceRGBA8888 is a pointer to the source image data in RGBA8888 format.
			\param lpDestRGBA8888 is a pointer to the buffer for the converted data.
			\param uiSourceWidth is the width of the source image in pixels.
			\param uiSourceHeight is the height of the source image in pixels.
			\param uiDestWidth is the width of the destination image in pixels.
			\param uiDestHeight is the height of the destination image in pixels.
			\param ResizeFilter is the image reduction filter to use (default triangle).
			\param bRGB is whether we are generating mips for color data or not.
			\return true on sucessful re-size, otherwise false.
		*/
		static vlBool Resize(vlByte *lpSourceRGBA8888, vlByte *lpDestRGBA8888, vlUInt uiSourceWidth, vlUInt uiSourceHeight, vlUInt uiDestWidth, vlUInt uiDestHeight, VTFMipmapFilter ResizeFilter, vlBool bSRGB);

	private:
		
		// DXTn format decompression function
		static vlBool DecompressDXTn(vlByte *src, vlByte *dst, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat SourceFormat);

		// DXTn format compression function
		static vlBool CompressDXTn(vlByte *lpSource, vlByte *lpDest, vlUInt uiWidth, vlUInt uiHeight, VTFImageFormat DestFormat, vlUInt nAlphaThreshold);

	public:

		//! Correct and images gamma.
		/*!
			Applies gamma correction to an image.

			\param lpImageDataRGBA8888 is a pointer to the image data in RGBA8888 format.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param sGammaCorrection is the amount of gamma correction to apply.
		*/
		static vlVoid CorrectImageGamma(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle sGammaCorrection);

		//! Computes the reflectivity for an image.
		/*!
			Calculates and sets the reflectivity vector values for the VTF image based on the
			colour averages of each pixel.

			\param lpImageDataRGBA8888 is a pointer to the image data in RGBA8888 format.
			\param uiWidth is the width of the source image in pixels.
			\param uiHeight is the height of the source image in pixels.
			\param sX, sY, sZ are the variables to hold the values reflectivity vector.
			\see ComputeReflectivity()
			\see GetReflectivity()
			\see SetReflectivity()
		*/
		static vlVoid ComputeImageReflectivity(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight, vlSingle &sX, vlSingle &sY, vlSingle &sZ);

		static vlVoid FlipImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight);		//!< Flips an image vertically along its X-axis.
		static vlVoid MirrorImage(vlByte *lpImageDataRGBA8888, vlUInt uiWidth, vlUInt uiHeight);	//!< Flips an image horizontally along its Y-axis.
	};
}

#endif