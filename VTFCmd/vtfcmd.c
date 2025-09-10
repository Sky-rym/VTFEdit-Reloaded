/*
 * VTFCmd
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

#include "stdafx.h"
#include "enumerations.h"

#define MAX_ITEMS	1024

vlUInt uiFileCount = 0;
vlChar *lpFiles[MAX_ITEMS];							// Files to convert.
vlUInt uiFolderCount = 0;
vlChar *lpFolders[MAX_ITEMS];						// Folders to convert.
vlBool bRecursive = vlFalse;						// Recursively search folders.

vlUInt uiProcessed = 0;								// Files processed.
vlUInt uiCompleted = 0;								// Files processed without error.

vlChar *lpPrefix = "";								// String to add to start of output file name.
vlChar *lpPostfix = "";								// String to add to end of output file name.
vlChar *lpOutput = 0;								// Output folder.

vlBool bSilent = vlFalse;							// Don't display output.
vlBool bPause = vlFalse;							// Don't pause the console.
vlBool bHelp = vlFalse;								// Display help.

vlUInt uiVTFImage;									// VTF image handle.
vlUInt uiVMTMaterial;								// VMT material handle.
ILuint uiDevILImage;								// DevIL image handle.

VTFImageFormat AlphaFormat = IMAGE_FORMAT_DXT5;		// VTF image format for alpha textures.
VTFImageFormat NormalFormat = IMAGE_FORMAT_DXT1;	// VTF image format for non-alpha textures.
SVTFCreateOptions CreateOptions;					// VTF creation options.
vlChar *lpShader = 0;								// VMT shader to use.
vlUInt uiParameterCount = 0;
vlChar *lpParameters[MAX_ITEMS][2];					// VMT parameters.
vlChar *lpExportFormat = "tga";						// Format extension for exporting VTF images.

vlBool bHdr = vlFalse;

void Pause();
void Print(const vlChar *lpFormat, ...);
void PrintUsage(const vlChar *lpError, ...);

void ProcessFile(vlChar *lpInputFile);
void ProcessFolder(vlChar *lpInputFolder, vlChar *lpWildcard);

//
// stristr()
// Case insensitive version of strstr().
//
char *stristr(const char *string, const char *strSearch)
{
	const char *ptr = string;
	const char *ptr2;

    while(1)
	{
		ptr = strchr(string, toupper(*strSearch));
		ptr2 = strchr(string, tolower(*strSearch));

		if(ptr == 0)
		{
			ptr = ptr2;
		}
		if(ptr == 0)
		{
			break;
		}
		if(ptr2 && (ptr2 < ptr))
		{
			ptr = ptr2;
		}
		if(!strnicmp(ptr, strSearch, strlen(strSearch)))
		{
			return (char *)ptr;
		}

		string = ptr + 1;
    }

    return 0;
}

//
// strrpl()
// Replace a char in a string with another.
//
void strrpl(char *string, char chr, char rplChr)
{
	while(*string != 0)
	{
		if(*string == chr)
			*string = rplChr;
		string++;
	}
}

int main(int argc, char* argv[])
{
	int i;
	vlChar *lpWildcard;					// Holds wildcard string for folder searches.

	VTFImageFormat ImageFormat;			// Temp variable for string to VTFImageFormat test.
	VTFImageFlag ImageFlag;				// Temp variable for string to VTFImageFlag test.

	vlUInt uiTemp0, uiTemp1;			// Temp variables for string to integer test.
	vlSingle sTemp;						// Temp variable for string to single test.

	VTFResizeMethod ResizeMethod;		// Temp variable for string to VTFResizeMethod test.

	VTFMipmapFilter MipmapFilter;		// Temp variable for string to VTFMipmapFilter test.

	WIN32_FIND_DATA FindData;
	HANDLE Handle;

	// Check we have the right DLL version.
	if(vlGetVersion() != VL_VERSION)
	{
		Print("Wrong VTFLib version.\n");
		return 1;
	}

	// Fill in our CreateOptions struct with VTFLib defaults.
	vlImageCreateDefaultCreateStructure(&CreateOptions);

	// Grab command arguments.
	switch(argc)
	{
	case 1:
		// If no arguments assume double click.
		bPause = vlTrue;
		break;
	case 2:
		// If only one argument assume drag and drop.
		Handle = FindFirstFile(argv[1], &FindData);

		if(Handle != INVALID_HANDLE_VALUE)
		{
			if(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				lpFolders[uiFolderCount++] = argv[1];
				CreateOptions.bResize = vlTrue;
				bPause = vlTrue;
			}
			else
			{
				lpFiles[uiFileCount++] = argv[1];
				CreateOptions.bResize = vlTrue;
				bPause = vlTrue;
			}

			FindClose(Handle);
			break;
		}
		// Fall through.
	default:
		for(i = 1; i < argc; i++)
		{
			if(stricmp(argv[i], "-file") == 0)
			{
				if(i + 1 < argc && uiFileCount < MAX_ITEMS)
				{
					lpFiles[uiFileCount++] = argv[++i];
				}
				else
				{
					PrintUsage("-file expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-folder") == 0)
			{
				if(i + 1 < argc && uiFolderCount < MAX_ITEMS)
				{
					lpFolders[uiFolderCount++] = argv[++i];
				}
				else
				{
					PrintUsage("-folder expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-output") == 0)
			{
				if(i + 1 < argc)
				{
					lpOutput = argv[++i];
				}
				else
				{
					PrintUsage("-output expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-prefix") == 0)
			{
				if(i + 1 < argc)
				{
					lpPrefix = argv[++i];
				}
				else
				{
					PrintUsage("-prefix expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-postfix") == 0)
			{
				if(i + 1 < argc)
				{
					lpPostfix = argv[++i];
				}
				else
				{
					PrintUsage("-postfix expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-version") == 0)
			{
				if(i + 1 < argc && sscanf(argv[++i], "%u.%u", &uiTemp0, &uiTemp1) == 2)
				{
					CreateOptions.uiVersion[0] = uiTemp0;
					CreateOptions.uiVersion[1] = uiTemp1;
				}
				else
				{
					PrintUsage("-version expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-format") == 0)
			{
				if(i + 1 < argc)
				{
					ImageFormat = StringToImageFormat(argv[++i]);
					if(ImageFormat != IMAGE_FORMAT_COUNT)
					{
						NormalFormat = ImageFormat;
					}
					else
					{
						PrintUsage("Unknown format: %s.", argv[i]);
						return 2;
					}
				}
				else
				{
					PrintUsage("-format expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-srgb") == 0)
			{
				CreateOptions.bSRGB = vlTrue;
				//CreateOptions.uiFlags |= TEXTUREFLAGS_SRGB; // Re-enable after properly implementing this.
			}
			else if(stricmp(argv[i], "-alphaformat") == 0)
			{
				if(i + 1 < argc)
				{
					ImageFormat = StringToImageFormat(argv[++i]);
					if(ImageFormat != IMAGE_FORMAT_COUNT)
					{
						AlphaFormat = ImageFormat;
					}
					else
					{
						PrintUsage("Unknown format: %s.", argv[i]);
						return 2;
					}
				}
				else
				{
					PrintUsage("-format expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-exportformat") == 0)
			{
				if(i + 1 < argc)
				{
					lpExportFormat = argv[++i];
				}
				else
				{
					PrintUsage("-exportformat expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-flag") == 0)
			{
				if(i + 1 < argc)
				{
					ImageFlag = StringToImageFlag(argv[++i]);
					if(ImageFlag != TEXTUREFLAGS_COUNT)
					{
						CreateOptions.uiFlags |= ImageFlag;
					}
					else
					{
						PrintUsage("Unknown flag: %s.", argv[i]);
						return 2;
					}
				}
				else
				{
					PrintUsage("-flag expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-resize") == 0)
			{
				CreateOptions.bResize = vlTrue;
			}
			else if(stricmp(argv[i], "-rmethod") == 0)
			{
				if(i + 1 < argc)
				{
					ResizeMethod = StringToResizeMethod(argv[++i]);
					if(ResizeMethod != RESIZE_COUNT)
					{
						CreateOptions.ResizeMethod = ResizeMethod;
					}
					else
					{
						PrintUsage("Unknown rmethod: %s.", argv[i]);
						return 2;
					}
				}
				else
				{
					PrintUsage("-rmethod expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-rfilter") == 0)
			{
				if(i + 1 < argc)
				{
					MipmapFilter = StringToMipmapFilter(argv[++i]);
					if(MipmapFilter != MIPMAP_FILTER_COUNT)
					{
						CreateOptions.ResizeFilter = MipmapFilter;
					}
					else
					{
						PrintUsage("Unknown rfilter: %s.", argv[i]);
						return 2;
					}
				}
				else
				{
					PrintUsage("-rfilter expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-rwidth") == 0)
			{
				if(i + 1 < argc && sscanf(argv[++i], "%u", &uiTemp0) == 1)
				{
					CreateOptions.uiResizeWidth = uiTemp0;
					if(CreateOptions.uiResizeWidth != 0 && CreateOptions.uiResizeHeight != 0)
					{
						CreateOptions.ResizeMethod = RESIZE_SET;
					}
				}
				else
				{
					PrintUsage("-rwidth expects unsigned integer argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-rheight") == 0)
			{
				if(i + 1 < argc && sscanf(argv[++i], "%u", &uiTemp0) == 1)
				{
					CreateOptions.uiResizeHeight = uiTemp0;
					if(CreateOptions.uiResizeWidth != 0 && CreateOptions.uiResizeHeight != 0)
					{
						CreateOptions.ResizeMethod = RESIZE_SET;
					}
				}
				else
				{
					PrintUsage("-rheight expects unsigned integer argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-rclampwidth") == 0)
			{
				if(i + 1 < argc && sscanf(argv[++i], "%u", &uiTemp0) == 1)
				{
					CreateOptions.uiResizeClampWidth = uiTemp0;
				}
				else
				{
					PrintUsage("-rclampwidth expects unsigned integer argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-rclampheight") == 0)
			{
				if(i + 1 < argc && sscanf(argv[++i], "%u", &uiTemp0) == 1)
				{
					CreateOptions.uiResizeClampHeight = uiTemp0;
				}
				else
				{
					PrintUsage("-rclampheight expects unsigned integer argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-gamma") == 0)
			{
				CreateOptions.bGammaCorrection = vlTrue;
			}
			else if(stricmp(argv[i], "-gcorrection") == 0)
			{
				if(i + 1 < argc && sscanf(argv[++i], "%f", &sTemp) == 1)
				{
					CreateOptions.sGammaCorrection = sTemp;
				}
				else
				{
					PrintUsage("-gcorrection expects single argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-nomipmaps") == 0)
			{
				CreateOptions.bMipmaps = vlFalse;
			}
			else if(stricmp(argv[i], "-mfilter") == 0)
			{
				if(i + 1 < argc)
				{
					MipmapFilter = StringToMipmapFilter(argv[++i]);
					if(MipmapFilter != MIPMAP_FILTER_COUNT)
					{
						CreateOptions.MipmapFilter = MipmapFilter;
					}
					else
					{
						PrintUsage("Unknown mfilter: %s.", argv[i]);
						return 2;
					}
				}
				else
				{
					PrintUsage("-mfilter expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-bumpscale") == 0)
			{
				if(i + 1 < argc && sscanf(argv[++i], "%f", &sTemp) == 1)
				{
					CreateOptions.sBumpScale = sTemp;
				}
				else
				{
					PrintUsage("-bumpscale expects single argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-nothumbnail") == 0)
			{
				CreateOptions.bThumbnail = vlFalse;
			}
			else if(stricmp(argv[i], "-noreflectivity") == 0)
			{
				CreateOptions.bReflectivity = vlFalse;
			}
			else if(stricmp(argv[i], "-shader") == 0)
			{
				if(i + 1 < argc)
				{
					lpShader = argv[++i];
				}
				else
				{
					PrintUsage("-shader expects string argument.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-param") == 0)
			{
				if(i + 2 < argc)
				{
					lpParameters[uiParameterCount][0] = argv[++i];
					lpParameters[uiParameterCount][1] = argv[++i];

					uiParameterCount++;
				}
				else
				{
					PrintUsage("-shader expects two string arguments.");
					return 2;
				}
			}
			else if(stricmp(argv[i], "-recurse") == 0)
			{
				bRecursive = vlTrue;
			}
			else if(stricmp(argv[i], "-silent") == 0)
			{
				bSilent = vlTrue;
			}
			else if(stricmp(argv[i], "-pause") == 0)
			{
				bPause = vlTrue;
			}
			else if(stricmp(argv[i], "-help") == 0)
			{
				bHelp = vlTrue;
			}
			else if (stricmp(argv[i], "-hdr") == 0)
			{
				bHdr = vlTrue;
			}
			else if ( stricmp( argv[ i ], "-alphathreshold" ) )
			{
				if(i + 1 < argc && sscanf(argv[++i], "%u", &uiTemp0) == 1)
				{
					CreateOptions.nAlphaThreshold = uiTemp0;
				}
				else
				{
					PrintUsage("-alphathreshold expects a whole number between the range of 0-255.");
					return 2;
				}
			}
			else
			{
				PrintUsage("Unknown argument: %s.", argv[i]);
				return 2;
			}
		}
		break;
	}

	// If the user just wants help, give it to them.
	if(bHelp)
	{
		PrintUsage(0);
		return 0;
	}

	// Make sure we have something to do.
	if(uiFileCount == 0 && uiFolderCount == 0)
	{
		PrintUsage("-file or -folder not specified.");
		return 2;
	}

	// Initialize VTFLib.
	vlInitialize();

	vlCreateImage(&uiVTFImage);
	vlBindImage(uiVTFImage);

	vlCreateMaterial(&uiVMTMaterial);
	vlBindMaterial(uiVMTMaterial);

	// Initialize DevIL.
	ilInit();

	ilEnable(IL_ORIGIN_SET);  // Filps images that are upside down (by format).
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

	ilGenImages(1, &uiDevILImage);
	ilBindImage(uiDevILImage);

	// Process files.
	for(i = 0; i < (int)uiFileCount; i++)
	{
		ProcessFile(lpFiles[i]);
	}

	// Process folders.
	for(i = 0; i < (int)uiFolderCount; i++)
	{
		// Grab the wildcard string from the folder path.
		if((lpWildcard = strrchr(lpFolders[i], '\\')) == 0)
		{
			lpWildcard = "*.*";
		}
		else
		{
			// Wildcard starts after last \ in path.  e.g. C:\input\*.bmp
			*lpWildcard = '\0';
			lpWildcard++;

			// If there is no wildcard after the last \, use *.* as defult.
			if(*lpWildcard == '\0')
			{
				lpWildcard = "*.*";
			}
		}

		ProcessFolder(lpFolders[i], lpWildcard);
	}

	// Shutdown DevIL.
	ilDeleteImages(1, &uiDevILImage);

	ilShutDown();

	// Shutdown VTFLib.
	vlDeleteMaterial(uiVMTMaterial);

	vlDeleteImage(uiVTFImage);

	vlShutdown();

	Print("%d/%d files completed.\n", uiCompleted, uiProcessed);

	// Pause the console.
	Pause();

	return 0;
}

//
// Pause()
// Puase the console.
//
void Pause()
{
	if(bPause)
	{
		Print("Press any key to continue...");
		getchar();
	}
}

//
// Print()
// Wrap printf() so we don't have to keep checking for silent mode.
//
void Print(const vlChar *lpFormat, ...)
{
	va_list ArgumentList;

	if(!bSilent)
	{
		va_start(ArgumentList, lpFormat);
		vprintf(lpFormat, ArgumentList);
		va_end(ArgumentList);
	}
}

//
// PrintUsage()
// Print VTFCmd command line usage help string.
//
void PrintUsage(const vlChar *lpError, ...)
{
	va_list ArgumentList;

	Print("Correct vtfcmd usage:\n");
	Print(" -file <path>              (Input file path.)\n");
	Print(" -folder <path>            (Input directory search string.)\n");
	Print(" -output <path>            (Output directory.)\n");
	Print(" -prefix <string>          (Output file prefix.)\n");
	Print(" -postfix <string>         (Output file postfix.)\n");
	Print(" -version <string>         (Output version.)\n");
	Print(" -format <string>          (Output format to use on non-alpha (colour) textures.)\n");
	Print(" -alphaformat <string>     (Output format to use on alpha textures.)\n");
	Print(" -srgb                     (Whether to treat image as sRGB colour space or not)\n");
	Print(" -flag <string>            (Output flags to set.)\n");
	Print(" -resize                   (Resize the input to a power of 2.)\n");
	Print(" -rmethod <string>         (Resize method to use.)\n");
	Print(" -rfilter <string>         (Resize filter to use.)\n");
	Print(" -rwidth <integer>         (Resize to specific width.)\n");
	Print(" -rheight <integer>        (Resize to specific height.)\n");
	Print(" -rclampwidth <integer>    (Maximum width to resize to.)\n");
	Print(" -rclampheight <integer>   (Maximum height to resize to.)\n");
	Print(" -alphathreshold <integer> (Alpha threshold for One Bit Alpha. Pixel alpha below this value is set to 0)\n");
	Print(" -gamma                    (Gamma correct image.)\n");
	Print(" -gcorrection <single>     (Gamma correction to use.)\n");
	Print(" -nomipmaps                (Don't generate mipmaps.)\n");
	Print(" -mfilter <string>         (Mipmap filter to use.)\n");
	Print(" -bumpscale <single>       (Engine bump mapping scale to use.)\n");
	Print(" -nothumbnail              (Don't generate thumbnail image.)\n");
	Print(" -noreflectivity           (Don't calculate reflectivity.)\n");
	Print(" -shader <string>          (Create a material for the texture.)\n");
	Print(" -param <string> <string>  (Add a parameter to the material.)\n");
	Print(" -recurse                  (Process directories recursively.)\n");
	Print(" -exportformat <string>    (Convert VTF files to the format of this extension.)\n");
	Print(" -silent                   (Silent mode.)\n");
	Print(" -pause                    (Pause when done.)\n");
	Print(" -hdr                      (Indicate input is hdr.)\n");
	Print(" -help                     (Display vtfcmd help.)\n");
	Print("\n");
	Print("Example vtfcmd usage:\n");
	Print("vtfcmd.exe -file \"C:\\texture1.bmp\" -file \"C:\\texture2.bmp\" -format \"dxt1\"\n");
	Print("vtfcmd.exe -folder \"C:\\input\\*.tga\" -output \"C:\\output\" -recurse -pause\n");
	Print("vtfcmd.exe -folder \"C:\\output\\*.vtf\" -output \"C:\\input\" -exportformat \"jpg\"\n");

	if(lpError != 0 && !bSilent)
	{
		Print("\n");
		Print("Error:\n");

		va_start(ArgumentList, lpError);
		vprintf(lpError, ArgumentList);
		va_end(ArgumentList);

		Print("\n");
	}

	if(bHelp)
	{
		Print("\n");
		Print("Formats: RGBA8888, ABGR8888, RGB888, BGR888, RGB565, I8, IA88, A8,\n");
		Print("         RGB888_BLUESCREEN, BGR888_BLUESCREEN, ARGB8888, BGRA8888, DXT1,\n");
		Print("         DXT3, DXT5, BGRX8888, BGR565, BGRX5551, BGRA4444,DXT1_ONEBITALPHA,\n");
		Print("         BGRA5551, UV88, UVWQ8888, RGBA16161616F, RGBA16161616, UVLX8888\n");

		Print("\n");
		Print("Flags:   POINTSAMPLE, TRILINEAR, CLAMPS, CLAMPT, ANISOTROPIC, HINT_DXT5,\n");
		Print("         NORMAL, NOMIP, NOLOD, MINMIP, PROCEDURAL, RENDERTARGET,\n");
		Print("         DEPTHRENDERTARGET, NODEBUGOVERRIDE, SINGLECOPY, NODEPTHBUFFER\n");
		Print("         CLAMPU, VERTEXTEXTURE, SSBUMP, BORDER");

		Print("\n");
		Print("Resize Method:  NEAREST, BIGGEST, SMALLEST\n");

		Print("\n");
		Print("Resize Filter:  POINT, BOX, TRIANGLE, QUADRATIC, CUBIC, CATROM, MITCHELL\n");
		Print("                GAUSSIAN, SINC, BESSEL, HANNING, HAMMING, BLACKMAN, KAISER\n");

		Print("\n");
		Print("Normal Kernal:  4X, 3X3, 5X5, 7X7, 9X9, DUDV\n");

		Print("\n");
		Print("Normal Height:  ALPHA, AVERAGERGB, BIASEDRGB, RED, GREEN, BLUE, MAXRGB,\n");
		Print("                COLORSPACE\n");

		Print("\n");
		Print("Normal Alpha:   NOCHANGE, HEIGHT, BLACK, WHITE\n");
	}

	Pause();
}

//
// CreateOutputPath()
// Create an output file path from the input file path.
//
void CreateOutputPath(vlChar *lpOutputFile, vlChar *lpInputFile, vlChar *lpExtension)
{
	vlChar *lpTemp;

	// Create output file string.
	if(lpOutput != 0 && *lpOutput != '\0')
	{
		// Put the file in the lpOutput directory.
		sprintf(lpOutputFile, "%s\\", lpOutput);
	}
	else
	{
		// Put the file in the same directory as the input file.
		strcpy(lpOutputFile, lpInputFile);
		if((lpTemp = strrchr(lpOutputFile, '\\')) != 0)
		{
			*(lpTemp + 1) = '\0';
		}
		else
		{
			*lpOutputFile = '\0';
		}
	}

	// Add the prefix to the file name.
	strcat(lpOutputFile, lpPrefix);

	// Add the file name of the input file to the file name.
	if((lpTemp = strrchr(lpInputFile, '\\')) != 0)
	{
		strcat(lpOutputFile, lpTemp + 1);
	}
	else
	{
		strcat(lpOutputFile, lpInputFile);
	}

	if((lpTemp = strrchr(lpOutputFile, '.')) != 0 && lpTemp > strrchr(lpOutputFile, '\\'))
	{
		*lpTemp = '\0';
	}

	// Add the postfix to the file name.
	strcat(lpOutputFile, lpPostfix);

	// Add the extension to the file name.
	strcat(lpOutputFile, ".");
	strcat(lpOutputFile, lpExtension);
}

//
// FlipImage()
// Flip lpImageData over the horizontal axis.
//
void FlipImage(vlByte *lpImageData, vlUInt uiWidth, vlUInt uiHeight, vlUInt uiChannels)
{
	vlUInt i, j, k;
	vlByte bTemp;

	for(i = 0; i < uiWidth; i++)
	{
		for(j = 0; j < uiHeight / 2; j++)
		{
			vlByte *pOne = lpImageData + (i + j * uiWidth) * uiChannels;
			vlByte *pTwo = lpImageData + (i + (uiHeight - j - 1) * uiWidth) * uiChannels;

			for(k = 0; k < uiChannels; k++)
			{
				bTemp = pOne[k];
				pOne[k] = pTwo[k];
				pTwo[k] = bTemp;
			}
		}
	}
}

//
// ProcessFile()
// Convert input file to a vtf file and place it in the output folder.
//
void ProcessFile(vlChar *lpInputFile)
{
	vlUInt i;

	vlChar *lpTemp;					// Temp variable for string manipulation.
	vlChar lpVTFFile[512];			// Holds output .vtf file name.
	vlChar lpVMTFile[512];			// Holds output .vmt file name.
	vlChar lpVMTBaseTexture[512];	// Holds $basetexture .vmt param.
	vlChar lpExportFile[512];		// Holds output export file name.

	vlInt iTest;					// Holds .vmt integer test result.
	vlSingle sTest;					// Holds .vmt float test result.
	vlChar cTest[4096];				// Holds .vmt string test result.

	vlSingle sR, sG, sB;			// Reflectivity.
	vlByte *lpImageData;			// Export data.
	VTFImageFormat DestFormat;		// Export format.

	uiProcessed++;

	Print("Processing %s...\n", lpInputFile);

	lpTemp = strrchr(lpInputFile, '.');
	
	if(lpTemp == 0 || stricmp(lpTemp, ".vtf") != 0)
	{
		// Load input file.
		if(!ilLoadImage(lpInputFile))
		{
			Print(" Error loading input file.\n\n");
			return;
		}

		Print(" Information:\n");

		// Display input file info.
		Print("  Width: %d\n", ilGetInteger(IL_IMAGE_WIDTH));
		Print("  Height: %d\n", ilGetInteger(IL_IMAGE_HEIGHT));
		Print("  BPP: %d\n\n", ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL));

		CreateOptions.ImageFormat = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL) == 4 ? AlphaFormat : NormalFormat;

		Print(" Creating texture:\n");

		// Convert input file to RGBA.
		if(!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
		{
			Print("  Error converting input file.\n\n");
			return;
		}

		// Create vtf file.
		if(!vlImageCreateSingle((vlUInt)ilGetInteger(IL_IMAGE_WIDTH), (vlUInt)ilGetInteger(IL_IMAGE_HEIGHT), ilGetData(), &CreateOptions))
		{
			Print("  Error creating vtf file:\n%s\n\n", vlGetLastError());
			return;
		}

		CreateOutputPath(lpVTFFile, lpInputFile, "vtf");

		// Write vtf file.
		Print("  Writing %s...\n", lpVTFFile);
		if(!vlImageSave(lpVTFFile))
		{
			Print(" Error creating vtf file:\n%s\n\n", vlGetLastError());
			return;
		}
		Print("  %s written.\n\n", lpVTFFile);

		// Do we build a material?
		if(lpShader != 0)
		{
			Print(" Creating material:\n");

			// We need to constuct a $basetexture string, to do this we need the path
			// of the vtf file relative to the materials folder.  If we arn't in a
			// materials folder we can't do this.
			if((lpTemp = stristr(lpVTFFile, "materials\\")) == 0)
			{
				Print("  Error creating vmt: texture is not in a ...\\materials\\ folder.\n\n");
			}
			else
			{
				strcpy(lpVMTFile, lpVTFFile);
				strcpy(strrchr(lpVMTFile, '.'), ".vmt");

				strcpy(lpVMTBaseTexture, lpTemp + strlen("materials\\"));
				*strrchr(lpVMTBaseTexture, '.') = '\0';
				strrpl(lpVMTBaseTexture, '\\', '/');

				vlMaterialCreate(lpShader); // Create the root node.
				vlMaterialGetFirstNode(); // Go to the root node.
				vlMaterialAddNodeString("$basetexture", lpVMTBaseTexture); // Add a string node to the root node.

				// Add the custom parameters.
				for(i = 0; i < uiParameterCount; i++)
				{
					// Figure out if the parameter is a string, single or integer.

					if(sscanf(lpParameters[i][1], "%d%s", &iTest, cTest) == 1)
					{
						// We can interpet the string as an integer, assume it is one.
						vlMaterialAddNodeInteger(lpParameters[i][0], iTest);
					}
					else if(sscanf(lpParameters[i][1], "%f%s", &sTest, cTest) == 1)
					{
						// We can interpet the string as an single, assume it is one.
						vlMaterialAddNodeSingle(lpParameters[i][0], sTest);
					}
					else
					{
						// The string must be a string...
						vlMaterialAddNodeString(lpParameters[i][0], lpParameters[i][1]);
					}
				}

				// Write vmt file.
				Print("  Writing %s...\n", lpVMTFile);
				if(!vlMaterialSave(lpVMTFile))
				{
					Print("Error creating vtf file:\n%s\n\n", vlGetLastError());
					return;
				}
				Print("  %s written.\n\n", lpVMTFile);
			}
		}
	}
	else
	{
		if(!vlImageLoad(lpInputFile, vlFalse))
		{
			Print(" Error loading input file:\n%s\n\n", vlGetLastError());
			return;
		}

		VTFImageFormat SourceFormat = vlImageGetFormat();
		//Override source format if hdr is true and header format matches expected format.
		if (bHdr && SourceFormat == IMAGE_FORMAT_BGRA8888)
		{
			SourceFormat = IMAGE_FORMAT_HDR_BGRA8888;
		}

		Print(" Information:\n");

		// Display input file info.
		Print("  Version: v%u.%u\n", vlImageGetMajorVersion(), vlImageGetMinorVersion());
		Print("  Size On Disk: %.2f KB\n", (vlSingle)vlImageGetSize() / 1024.0f);
		Print("  Width: %u\n", vlImageGetWidth());
		Print("  Height: %u\n", vlImageGetHeight());
		Print("  Depth: %u\n", vlImageGetDepth());
		Print("  Frames: %u\n", vlImageGetFrameCount());
		Print("  Start Frame: %u\n", vlImageGetStartFrame());
		Print("  Faces: %u\n", vlImageGetFaceCount());
		Print("  Mipmaps: %u\n", vlImageGetMipmapCount());
		Print("  Flags: %#.8x\n", vlImageGetFlags());
		Print("  Bumpmap Scale: %.2f\n", vlImageGetBumpmapScale());
		vlImageGetReflectivity(&sR, &sG, &sB);
		Print("  Reflectivity: %.2f, %.2f, %.2f\n", sR, sG, sB);
		Print("  Format: %s\n\n", vlImageGetImageFormatInfo(SourceFormat)->lpName);
		Print("  Resources: %u\n", vlImageGetResourceCount());

		Print(" Creating texture:\n");

		// Figure out which destination format to use.
		DestFormat = (vlImageGetFlags() & (TEXTUREFLAGS_ONEBITALPHA | TEXTUREFLAGS_EIGHTBITALPHA)) ? IMAGE_FORMAT_RGBA8888 : IMAGE_FORMAT_RGB888;

		// Alocate the required memory to convert the vtf to.
		lpImageData = malloc(vlImageComputeImageSize(vlImageGetWidth(), vlImageGetHeight(), 1, 1, DestFormat));

		if(lpImageData == 0)
		{
			Print(" malloc() failed.\n\n");
			return;
		}

		// Convert the .vtf.
		if(!vlImageConvert(vlImageGetData(0, 0, 0, 0), lpImageData, vlImageGetWidth(), vlImageGetHeight(), SourceFormat, DestFormat))
		{
			free(lpImageData);

			Print(" Error converting input file:\n%s\n\n", vlGetLastError());
			return;
		}

		// DevIL likes the image data upside down.
		FlipImage(lpImageData, vlImageGetWidth(), vlImageGetHeight(), DestFormat == IMAGE_FORMAT_RGBA8888 ? 4 : 3);

		// Create a new image with the converted image data in DevIL.
		if(!ilTexImage(vlImageGetWidth(), vlImageGetHeight(), 1, DestFormat == IMAGE_FORMAT_RGBA8888 ? 4 : 3, DestFormat == IMAGE_FORMAT_RGBA8888 ? IL_RGBA : IL_RGB, IL_UNSIGNED_BYTE, lpImageData))
		{
			free(lpImageData);

			Print("  Error creating %s file.\n\n", lpExportFormat);
			return;
		}

		free(lpImageData);

		CreateOutputPath(lpExportFile, lpInputFile, lpExportFormat);

		// Write tga file.
		Print("  Writing %s...\n", lpExportFile);
		if(!ilSaveImage(lpExportFile))
		{
			Print(" Error creating %s file.\n\n", lpExportFormat);
			return;
		}
		Print("  %s written.\n\n", lpExportFile);
	}

	Print("%s processed.\n\n", lpInputFile);

	uiCompleted++;
}

//
// ProcessFile()
// Process all files in the input folder.
//
void ProcessFolder(vlChar *lpInputFolder, vlChar *lpWildcard)
{
	vlChar lpSearchString[512];
	vlChar lpPath[512];

	WIN32_FIND_DATA FindData;
	HANDLE Handle;

	Print("Processing %s\\...\n\n", lpInputFolder);

	if(bRecursive)
	{
		sprintf(lpSearchString, "%s\\*", lpInputFolder);

		Handle = FindFirstFile(lpSearchString, &FindData);

		if(Handle != INVALID_HANDLE_VALUE)
		{
			do
			{
				if(stricmp(FindData.cFileName, ".") != 0 && stricmp(FindData.cFileName, "..") != 0)
				{
					sprintf(lpPath, "%s\\%s", lpInputFolder, FindData.cFileName);

					if(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						ProcessFolder(lpPath, lpWildcard);
					}
				}
			} while(FindNextFile(Handle, &FindData));

			FindClose(Handle);
		}
	}

	sprintf(lpSearchString, "%s\\%s", lpInputFolder, lpWildcard);

	Handle = FindFirstFile(lpSearchString, &FindData);

	if(Handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if(stricmp(FindData.cFileName, ".") != 0 && stricmp(FindData.cFileName, "..") != 0)
			{
				sprintf(lpPath, "%s\\%s", lpInputFolder, FindData.cFileName);

				if((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
				{
					ProcessFile(lpPath);
				}
			}
		} while(FindNextFile(Handle, &FindData));

		FindClose(Handle);
	}

	Print("%s\\ processed.\n\n", lpInputFolder);
}