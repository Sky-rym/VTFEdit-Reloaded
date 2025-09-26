/*
 * HLLib
 * Copyright (C) 2006-2013 Ryan Gregg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later
 * version.
 */

#ifndef HLLIB_H
#define HLLIB_H

#ifdef _MSC_VER
#	ifdef HLLIB_EXPORTS
#		define HLLIB_API __declspec(dllexport)
#	else
#		define HLLIB_API __declspec(dllimport)
#	endif
#else
#	if defined(HAVE_GCCVISIBILITYPATCH) || __GNUC__ >= 4
#		define HLLIB_API __attribute__ ((visibility("default")))
#	else
#		define HLLIB_API
#	endif
#endif

typedef unsigned char		hlBool;
typedef char				hlChar;
#ifdef __cplusplus
typedef wchar_t				hlWChar;
#else
typedef unsigned short		hlWChar;
#endif
typedef unsigned char		hlByte;
typedef signed short		hlShort;
typedef unsigned short		hlUShort;
typedef signed int			hlInt;
typedef unsigned int		hlUInt;
typedef signed long			hlLong;
typedef unsigned long		hlULong;
typedef signed long long	hlLongLong;
typedef unsigned long long	hlULongLong;
typedef float				hlSingle;
typedef double				hlDouble;
typedef void				hlVoid;

#ifdef _MSC_VER
	typedef unsigned __int8		hlUInt8;
	typedef unsigned __int16	hlUInt16;
	typedef unsigned __int32	hlUInt32;
	typedef unsigned __int64	hlUInt64;
#else
#	include <stdint.h>

	typedef uint8_t		hlUInt8;
	typedef uint16_t	hlUInt16;
	typedef uint32_t	hlUInt32;
	typedef uint64_t	hlUInt64;
#endif

typedef hlSingle		hlFloat;

#define hlFalse			0
#define hlTrue			1

#define HL_VERSION_NUMBER	((2 << 24) | (4 << 16) | (6 << 8) | 0)
#define HL_VERSION_STRING	"2.4.6"

#define HL_ID_INVALID 0xffffffff

#define HL_DEFAULT_PACKAGE_TEST_BUFFER_SIZE 8
#define HL_DEFAULT_VIEW_SIZE 131072
#define HL_DEFAULT_COPY_BUFFER_SIZE 131072

//
// C data types.
//

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	HL_VERSION = 0,
	HL_ERROR,
	HL_ERROR_SYSTEM,
	HL_ERROR_SHORT_FORMATED,
	HL_ERROR_LONG_FORMATED,
	HL_PROC_OPEN,
	HL_PROC_CLOSE,
	HL_PROC_READ,
	HL_PROC_WRITE,
	HL_PROC_SEEK,
	HL_PROC_TELL,
	HL_PROC_SIZE,
	HL_PROC_EXTRACT_ITEM_START,
	HL_PROC_EXTRACT_ITEM_END,
	HL_PROC_EXTRACT_FILE_PROGRESS,
	HL_PROC_VALIDATE_FILE_PROGRESS,
	HL_OVERWRITE_FILES,
	HL_PACKAGE_BOUND,
	HL_PACKAGE_ID,
	HL_PACKAGE_SIZE,
	HL_PACKAGE_TOTAL_ALLOCATIONS,
	HL_PACKAGE_TOTAL_MEMORY_ALLOCATED,
	HL_PACKAGE_TOTAL_MEMORY_USED,
	HL_READ_ENCRYPTED,
	HL_FORCE_DEFRAGMENT,
	HL_PROC_DEFRAGMENT_PROGRESS,
	HL_PROC_DEFRAGMENT_PROGRESS_EX,
	HL_PROC_SEEK_EX,
	HL_PROC_TELL_EX,
	HL_PROC_SIZE_EX
} HLOption;

typedef enum
{
	HL_MODE_INVALID = 0x00,
	HL_MODE_READ = 0x01,
	HL_MODE_WRITE = 0x02,
	HL_MODE_CREATE = 0x04,
	HL_MODE_VOLATILE = 0x08,
	HL_MODE_NO_FILEMAPPING = 0x10,
	HL_MODE_QUICK_FILEMAPPING = 0x20
} HLFileMode;

typedef enum
{
	HL_SEEK_BEGINNING = 0,
	HL_SEEK_CURRENT,
	HL_SEEK_END
} HLSeekMode;

typedef enum
{
	HL_ITEM_NONE = 0,
	HL_ITEM_FOLDER,
	HL_ITEM_FILE
} HLDirectoryItemType;

typedef enum
{
	HL_ORDER_ASCENDING = 0,
	HL_ORDER_DESCENDING
} HLSortOrder;

typedef enum
{
	HL_FIELD_NAME = 0,
	HL_FIELD_SIZE
} HLSortField;

typedef enum
{
	HL_FIND_FILES = 0x01,
	HL_FIND_FOLDERS = 0x02,
	HL_FIND_NO_RECURSE = 0x04,
	HL_FIND_CASE_SENSITIVE = 0x08,
	HL_FIND_MODE_STRING = 0x10,
	HL_FIND_MODE_SUBSTRING = 0x20,
	HL_FIND_MODE_WILDCARD = 0x00,
	HL_FIND_ALL = HL_FIND_FILES | HL_FIND_FOLDERS
} HLFindType;

typedef enum
{
	HL_STREAM_NONE = 0,
	HL_STREAM_FILE,
	HL_STREAM_GCF,
	HL_STREAM_MAPPING,
	HL_STREAM_MEMORY,
	HL_STREAM_PROC,
	HL_STREAM_NULL
} HLStreamType;

typedef enum
{
	HL_MAPPING_NONE = 0,
	HL_MAPPING_FILE,
	HL_MAPPING_MEMORY,
	HL_MAPPING_STREAM
} HLMappingType;

typedef enum
{
	HL_PACKAGE_NONE = 0,
	HL_PACKAGE_BSP,
	HL_PACKAGE_GCF,
	HL_PACKAGE_PAK,
	HL_PACKAGE_VBSP,
	HL_PACKAGE_WAD,
	HL_PACKAGE_XZP,
	HL_PACKAGE_ZIP,
	HL_PACKAGE_NCF,
	HL_PACKAGE_VPK,
	HL_PACKAGE_SGA
} HLPackageType;

typedef enum
{
	HL_ATTRIBUTE_INVALID = 0,
	HL_ATTRIBUTE_BOOLEAN,
	HL_ATTRIBUTE_INTEGER,
	HL_ATTRIBUTE_UNSIGNED_INTEGER,
	HL_ATTRIBUTE_FLOAT,
	HL_ATTRIBUTE_STRING
} HLAttributeType;

typedef enum
{
	HL_BSP_PACKAGE_VERSION = 0,
	HL_BSP_PACKAGE_COUNT,
	HL_BSP_ITEM_WIDTH = 0,
	HL_BSP_ITEM_HEIGHT,
	HL_BSP_ITEM_PALETTE_ENTRIES,
	HL_BSP_ITEM_COUNT,

	HL_GCF_PACKAGE_VERSION = 0,
	HL_GCF_PACKAGE_ID,
	HL_GCF_PACKAGE_ALLOCATED_BLOCKS,
	HL_GCF_PACKAGE_USED_BLOCKS,
	HL_GCF_PACKAGE_BLOCK_LENGTH,
	HL_GCF_PACKAGE_LAST_VERSION_PLAYED,
	HL_GCF_PACKAGE_COUNT,
	HL_GCF_ITEM_ENCRYPTED = 0,
	HL_GCF_ITEM_COPY_LOCAL,
	HL_GCF_ITEM_OVERWRITE_LOCAL,
	HL_GCF_ITEM_BACKUP_LOCAL,
	HL_GCF_ITEM_FLAGS,
	HL_GCF_ITEM_FRAGMENTATION,
	HL_GCF_ITEM_COUNT,

	HL_NCF_PACKAGE_VERSION = 0,
	HL_NCF_PACKAGE_ID,
	HL_NCF_PACKAGE_LAST_VERSION_PLAYED,
	HL_NCF_PACKAGE_COUNT,
	HL_NCF_ITEM_ENCRYPTED = 0,
	HL_NCF_ITEM_COPY_LOCAL,
	HL_NCF_ITEM_OVERWRITE_LOCAL,
	HL_NCF_ITEM_BACKUP_LOCAL,
	HL_NCF_ITEM_FLAGS,
	HL_NCF_ITEM_COUNT,

	HL_PAK_PACKAGE_COUNT = 0,
	HL_PAK_ITEM_COUNT = 0,

	HL_SGA_PACKAGE_VERSION_MAJOR = 0,
	HL_SGA_PACKAGE_VERSION_MINOR,
	HL_SGA_PACKAGE_MD5_FILE,
	HL_SGA_PACKAGE_NAME,
	HL_SGA_PACKAGE_MD5_HEADER,
	HL_SGA_PACKAGE_COUNT,
	HL_SGA_ITEM_SECTION_ALIAS = 0,
	HL_SGA_ITEM_SECTION_NAME,
	HL_SGA_ITEM_MODIFIED,
	HL_SGA_ITEM_TYPE,
	HL_SGA_ITEM_CRC,
	HL_SGA_ITEM_VERIFICATION,
	HL_SGA_ITEM_COUNT,

	HL_VBSP_PACKAGE_VERSION = 0,
	HL_VBSP_PACKAGE_MAP_REVISION,
	HL_VBSP_PACKAGE_COUNT,
	HL_VBSP_ITEM_VERSION = 0,
	HL_VBSP_ITEM_FOUR_CC,
	HL_VBSP_ZIP_PACKAGE_DISK,
	HL_VBSP_ZIP_PACKAGE_COMMENT,
	HL_VBSP_ZIP_ITEM_CREATE_VERSION,
	HL_VBSP_ZIP_ITEM_EXTRACT_VERSION,
	HL_VBSP_ZIP_ITEM_FLAGS,
	HL_VBSP_ZIP_ITEM_COMPRESSION_METHOD,
	HL_VBSP_ZIP_ITEM_CRC,
	HL_VBSP_ZIP_ITEM_DISK,
	HL_VBSP_ZIP_ITEM_COMMENT,
	HL_VBSP_ITEM_COUNT,

	HL_VPK_PACKAGE_Archives = 0,
	HL_VPK_PACKAGE_Version,
	HL_VPK_PACKAGE_COUNT,
	HL_VPK_ITEM_PRELOAD_BYTES = 0,
	HL_VPK_ITEM_ARCHIVE,
	HL_VPK_ITEM_CRC,
	HL_VPK_ITEM_COUNT,

	HL_WAD_PACKAGE_VERSION = 0,
	HL_WAD_PACKAGE_COUNT,
	HL_WAD_ITEM_WIDTH = 0,
	HL_WAD_ITEM_HEIGHT,
	HL_WAD_ITEM_PALETTE_ENTRIES,
	HL_WAD_ITEM_MIPMAPS,
	HL_WAD_ITEM_COMPRESSED,
	HL_WAD_ITEM_TYPE,
	HL_WAD_ITEM_COUNT,

	HL_XZP_PACKAGE_VERSION = 0,
	HL_XZP_PACKAGE_PRELOAD_BYTES,
	HL_XZP_PACKAGE_COUNT,
	HL_XZP_ITEM_CREATED = 0,
	HL_XZP_ITEM_PRELOAD_BYTES,
	HL_XZP_ITEM_COUNT,

	HL_ZIP_PACKAGE_DISK = 0,
	HL_ZIP_PACKAGE_COMMENT,
	HL_ZIP_PACKAGE_COUNT,
	HL_ZIP_ITEM_CREATE_VERSION = 0,
	HL_ZIP_ITEM_EXTRACT_VERSION,
	HL_ZIP_ITEM_FLAGS,
	HL_ZIP_ITEM_COMPRESSION_METHOD,
	HL_ZIP_ITEM_CRC,
	HL_ZIP_ITEM_DISK,
	HL_ZIP_ITEM_COMMENT,
	HL_ZIP_ITEM_COUNT
} HLPackageAttribute;

typedef enum
{
	HL_VALIDATES_OK = 0,
	HL_VALIDATES_ASSUMED_OK,
	HL_VALIDATES_INCOMPLETE,
	HL_VALIDATES_CORRUPT,
	HL_VALIDATES_CANCELED,
	HL_VALIDATES_ERROR
} HLValidation;

typedef struct
{
	HLAttributeType eAttributeType;
	hlChar lpName[252];
	union
	{
		struct
		{
			hlBool bValue;
		} Boolean;
		struct
		{
			hlInt iValue;
		} Integer;
		struct
		{
			hlUInt uiValue;
			hlBool bHexadecimal;
		} UnsignedInteger;
		struct
		{
			hlFloat fValue;
		} Float;
		struct
		{
			hlChar lpValue[256];
		} String;
	} Value;
} HLAttribute;

typedef hlVoid HLDirectoryItem;
typedef hlVoid HLStream;

typedef hlBool (*POpenProc) (hlUInt, hlVoid *);
typedef hlVoid (*PCloseProc)(hlVoid *);
typedef hlUInt (*PReadProc)  (hlVoid *, hlUInt, hlVoid *);
typedef hlUInt (*PWriteProc)  (const hlVoid *, hlUInt, hlVoid *);
typedef hlULongLong (*PSeekExProc) (hlLongLong, HLSeekMode, hlVoid *);
typedef hlUInt (*PTellProc) (hlVoid *);
typedef hlULongLong (*PTellExProc) (hlVoid *);
typedef hlUInt (*PSizeProc) (hlVoid *);
typedef hlULongLong (*PSizeExProc) (hlVoid *);

typedef hlVoid (*PExtractItemStartProc) (const HLDirectoryItem *pItem);
typedef hlVoid (*PExtractItemEndProc) (const HLDirectoryItem *pItem, hlBool bSuccess);
typedef hlVoid (*PExtractFileProgressProc) (const HLDirectoryItem *pFile, hlUInt uiBytesExtracted, hlUInt uiBytesTotal, hlBool *pCancel);
typedef hlVoid (*PValidateFileProgressProc) (const HLDirectoryItem *pFile, hlUInt uiBytesValidated, hlUInt uiBytesTotal, hlBool *pCancel);
typedef hlVoid (*PDefragmentProgressProc) (const HLDirectoryItem *pFile, hlUInt uiFilesDefragmented, hlUInt uiFilesTotal, hlUInt uiBytesDefragmented, hlUInt uiBytesTotal, hlBool *pCancel);
typedef hlVoid (*PDefragmentProgressExProc) (const HLDirectoryItem *pFile, hlUInt uiFilesDefragmented, hlUInt uiFilesTotal, hlULongLong uiBytesDefragmented, hlULongLong uiBytesTotal, hlBool *pCancel);

#ifdef __cplusplus
}
#endif

//
// C library routines.
//

#ifdef __cplusplus
extern "C" {
#endif

HLLIB_API hlVoid hlInitialize();
HLLIB_API hlVoid hlShutdown();

//
// Get/Set
//

HLLIB_API hlBool hlGetBoolean(HLOption eOption);
HLLIB_API hlBool hlGetBooleanValidate(HLOption eOption, hlBool *pValue);
HLLIB_API hlVoid hlSetBoolean(HLOption eOption, hlBool bValue);

HLLIB_API hlInt hlGetInteger(HLOption eOption);
HLLIB_API hlBool hlGetIntegerValidate(HLOption eOption, hlInt *pValue);
HLLIB_API hlVoid hlSetInteger(HLOption eOption, hlInt iValue);

HLLIB_API hlUInt hlGetUnsignedInteger(HLOption eOption);
HLLIB_API hlBool hlGetUnsignedIntegerValidate(HLOption eOption, hlUInt *pValue);
HLLIB_API hlVoid hlSetUnsignedInteger(HLOption eOption, hlUInt iValue);

HLLIB_API hlLongLong hlGetLongLong(HLOption eOption);
HLLIB_API hlBool hlGetLongLongValidate(HLOption eOption, hlLongLong *pValue);
HLLIB_API hlVoid hlSetLongLong(HLOption eOption, hlLongLong iValue);

HLLIB_API hlULongLong hlGetUnsignedLongLong(HLOption eOption);
HLLIB_API hlBool hlGetUnsignedLongLongValidate(HLOption eOption, hlULongLong *pValue);
HLLIB_API hlVoid hlSetUnsignedLongLong(HLOption eOption, hlULongLong iValue);

HLLIB_API hlFloat hlGetFloat(HLOption eOption);
HLLIB_API hlBool hlGetFloatValidate(HLOption eOption, hlFloat *pValue);
HLLIB_API hlVoid hlSetFloat(HLOption eOption, hlFloat fValue);

HLLIB_API const hlChar *hlGetString(HLOption eOption);
HLLIB_API hlBool hlGetStringValidate(HLOption eOption, const hlChar **pValue);
HLLIB_API hlVoid hlSetString(HLOption eOption, const hlChar *lpValue);

HLLIB_API const hlVoid *hlGetVoid(HLOption eOption);
HLLIB_API hlBool hlGetVoidValidate(HLOption eOption, const hlVoid **pValue);
HLLIB_API hlVoid hlSetVoid(HLOption eOption, const hlVoid *pValue);

//
// Attributes
//

HLLIB_API hlBool hlAttributeGetBoolean(HLAttribute *pAttribute);
HLLIB_API hlVoid hlAttributeSetBoolean(HLAttribute *pAttribute, const hlChar *lpName, hlBool bValue);

HLLIB_API hlInt hlAttributeGetInteger(HLAttribute *pAttribute);
HLLIB_API hlVoid hlAttributeSetInteger(HLAttribute *pAttribute, const hlChar *lpName, hlInt iValue);

HLLIB_API hlUInt hlAttributeGetUnsignedInteger(HLAttribute *pAttribute);
HLLIB_API hlVoid hlAttributeSetUnsignedInteger(HLAttribute *pAttribute, const hlChar *lpName, hlUInt uiValue, hlBool bHexadecimal);

HLLIB_API hlFloat hlAttributeGetFloat(HLAttribute *pAttribute);
HLLIB_API hlVoid hlAttributeSetFloat(HLAttribute *pAttribute, const hlChar *lpName, hlFloat fValue);

HLLIB_API const hlChar *hlAttributeGetString(HLAttribute *pAttribute);
HLLIB_API hlVoid hlAttributeSetString(HLAttribute *pAttribute, const hlChar *lpName, const hlChar *lpValue);

//
// Directory Item
//

HLLIB_API HLDirectoryItemType hlItemGetType(const HLDirectoryItem *pItem);

HLLIB_API const hlChar *hlItemGetName(const HLDirectoryItem *pItem);
HLLIB_API hlUInt hlItemGetID(const HLDirectoryItem *pItem);
HLLIB_API const hlVoid *hlItemGetData(const HLDirectoryItem *pItem);

HLLIB_API hlUInt hlItemGetPackage(const HLDirectoryItem *pItem);
HLLIB_API HLDirectoryItem *hlItemGetParent(HLDirectoryItem *pItem);

HLLIB_API hlBool hlItemGetSize(const HLDirectoryItem *pItem, hlUInt *pSize);
HLLIB_API hlBool hlItemGetSizeEx(const HLDirectoryItem *pItem, hlULongLong *pSize);
HLLIB_API hlBool hlItemGetSizeOnDisk(const HLDirectoryItem *pItem, hlUInt *pSize);
HLLIB_API hlBool hlItemGetSizeOnDiskEx(const HLDirectoryItem *pItem, hlULongLong *pSize);

HLLIB_API hlVoid hlItemGetPath(const HLDirectoryItem *pItem, hlChar *lpPath, hlUInt uiPathSize);
HLLIB_API hlBool hlItemExtract(HLDirectoryItem *pItem, const hlChar *lpPath);

//
// Directory Folder
//

HLLIB_API hlUInt hlFolderGetCount(const HLDirectoryItem *pItem);

HLLIB_API HLDirectoryItem *hlFolderGetItem(HLDirectoryItem *pItem, hlUInt uiIndex);
HLLIB_API HLDirectoryItem *hlFolderGetItemByName(HLDirectoryItem *pItem, const hlChar *lpName, HLFindType eFind);
HLLIB_API HLDirectoryItem *hlFolderGetItemByPath(HLDirectoryItem *pItem, const hlChar *lpPath, HLFindType eFind);

HLLIB_API hlVoid hlFolderSort(HLDirectoryItem *pItem, HLSortField eField, HLSortOrder eOrder, hlBool bRecurse);

HLLIB_API HLDirectoryItem *hlFolderFindFirst(HLDirectoryItem *pFolder, const hlChar *lpSearch, HLFindType eFind);
HLLIB_API HLDirectoryItem *hlFolderFindNext(HLDirectoryItem *pFolder, HLDirectoryItem *pItem, const hlChar *lpSearch, HLFindType eFind);

HLLIB_API hlUInt hlFolderGetSize(const HLDirectoryItem *pItem, hlBool bRecurse);
HLLIB_API hlULongLong hlFolderGetSizeEx(const HLDirectoryItem *pItem, hlBool bRecurse);
HLLIB_API hlUInt hlFolderGetSizeOnDisk(const HLDirectoryItem *pItem, hlBool bRecurse);
HLLIB_API hlULongLong hlFolderGetSizeOnDiskEx(const HLDirectoryItem *pItem, hlBool bRecurse);
HLLIB_API hlUInt hlFolderGetFolderCount(const HLDirectoryItem *pItem, hlBool bRecurse);
HLLIB_API hlUInt hlFolderGetFileCount(const HLDirectoryItem *pItem, hlBool bRecurse);

//
// Directory File
//

HLLIB_API hlUInt hlFileGetExtractable(const HLDirectoryItem *pItem);
HLLIB_API HLValidation hlFileGetValidation(const HLDirectoryItem *pItem);
HLLIB_API hlUInt hlFileGetSize(const HLDirectoryItem *pItem);
HLLIB_API hlUInt hlFileGetSizeOnDisk(const HLDirectoryItem *pItem);

HLLIB_API hlBool hlFileCreateStream(HLDirectoryItem *pItem, HLStream **pStream);
HLLIB_API hlVoid hlFileReleaseStream(HLDirectoryItem *pItem, HLStream *pStream);

//
// Stream
//

HLLIB_API HLStreamType hlStreamGetType(const HLStream *pStream);

HLLIB_API hlBool hlStreamGetOpened(const HLStream *pStream);
HLLIB_API hlUInt hlStreamGetMode(const HLStream *pStream);

HLLIB_API hlBool hlStreamOpen(HLStream *pStream, hlUInt uiMode);
HLLIB_API hlVoid hlStreamClose(HLStream *pStream);

HLLIB_API hlUInt hlStreamGetStreamSize(const HLStream *pStream);
HLLIB_API hlULongLong hlStreamGetStreamSizeEx(const HLStream *pStream);
HLLIB_API hlUInt hlStreamGetStreamPointer(const HLStream *pStream);
HLLIB_API hlULongLong hlStreamGetStreamPointerEx(const HLStream *pStream);

HLLIB_API hlUInt hlStreamSeek(HLStream *pStream, hlLongLong iOffset, HLSeekMode eSeekMode);
HLLIB_API hlULongLong hlStreamSeekEx(HLStream *pStream, hlLongLong iOffset, HLSeekMode eSeekMode);

HLLIB_API hlBool hlStreamReadChar(HLStream *pStream, hlChar *pChar);
HLLIB_API hlUInt hlStreamRead(HLStream *pStream, hlVoid *lpData, hlUInt uiBytes);

HLLIB_API hlBool hlStreamWriteChar(HLStream *pStream, hlChar iChar);
HLLIB_API hlUInt hlStreamWrite(HLStream *pStream, const hlVoid *lpData, hlUInt uiBytes);

//
// Package
//

HLLIB_API hlBool hlBindPackage(hlUInt uiPackage);

HLLIB_API HLPackageType hlGetPackageTypeFromName(const hlChar *lpName);
HLLIB_API HLPackageType hlGetPackageTypeFromMemory(const hlVoid *lpBuffer, hlUInt uiBufferSize);
HLLIB_API HLPackageType hlGetPackageTypeFromStream(HLStream *pStream);
HLLIB_API hlBool hlCreatePackage(HLPackageType ePackageType, hlUInt *uiPackage);
HLLIB_API hlVoid hlDeletePackage(hlUInt uiPackage);

HLLIB_API HLPackageType hlPackageGetType();
HLLIB_API const hlChar *hlPackageGetExtension();
HLLIB_API const hlChar *hlPackageGetDescription();

HLLIB_API hlBool hlPackageGetOpened();

HLLIB_API hlBool hlPackageOpenFile(const hlChar *lpFileName, hlUInt uiMode);
HLLIB_API hlBool hlPackageOpenMemory(hlVoid *lpData, hlUInt uiBufferSize, hlUInt uiMode);
HLLIB_API hlBool hlPackageOpenProc(hlVoid *pUserData, hlUInt uiMode);
HLLIB_API hlBool hlPackageOpenStream(HLStream *pStream, hlUInt uiMode);
HLLIB_API hlVoid hlPackageClose();

HLLIB_API hlBool hlPackageDefragment();

HLLIB_API HLDirectoryItem *hlPackageGetRoot();

HLLIB_API hlUInt hlPackageGetAttributeCount();
HLLIB_API const hlChar *hlPackageGetAttributeName(HLPackageAttribute eAttribute);
HLLIB_API hlBool hlPackageGetAttribute(HLPackageAttribute eAttribute, HLAttribute *pAttribute);

HLLIB_API hlUInt hlPackageGetItemAttributeCount();
HLLIB_API const hlChar *hlPackageGetItemAttributeName(HLPackageAttribute eAttribute);
HLLIB_API hlBool hlPackageGetItemAttribute(const HLDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute *pAttribute);

HLLIB_API hlBool hlPackageGetExtractable(const HLDirectoryItem *pFile, hlBool *pExtractable);
HLLIB_API hlBool hlPackageGetFileSize(const HLDirectoryItem *pFile, hlUInt *pSize);
HLLIB_API hlBool hlPackageGetFileSizeOnDisk(const HLDirectoryItem *pFile, hlUInt *pSize);
HLLIB_API hlBool hlPackageCreateStream(const HLDirectoryItem *pFile, HLStream **pStream);
HLLIB_API hlVoid hlPackageReleaseStream(HLStream *pStream);

HLLIB_API const hlChar *hlNCFFileGetRootPath();
HLLIB_API hlVoid hlNCFFileSetRootPath(const hlChar *lpRootPath);

HLLIB_API hlBool hlWADFileGetImageSizePaletted(const HLDirectoryItem *pFile, hlUInt *uiPaletteDataSize, hlUInt *uiPixelDataSize);
HLLIB_API hlBool hlWADFileGetImageDataPaletted(const HLDirectoryItem *pFile, hlUInt *uiWidth, hlUInt *uiHeight, hlByte **lpPaletteData, hlByte **lpPixelData);
HLLIB_API hlBool hlWADFileGetImageSize(const HLDirectoryItem *pFile, hlUInt *uiPixelDataSize);
HLLIB_API hlBool hlWADFileGetImageData(const HLDirectoryItem *pFile, hlUInt *uiWidth, hlUInt *uiHeight, hlByte **lpPixelData);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#	include <list>

namespace HLLib
{
	class HLLIB_API CDirectoryItem;
	class HLLIB_API CDirectoryFile;
	class HLLIB_API CDirectoryFolder;

	namespace Streams
	{
		class HLLIB_API IStream;
		class HLLIB_API CFileStream;
		class HLLIB_API CGCFStream;
		class HLLIB_API CMappingStream;
		class HLLIB_API CMemoryStream;
		class HLLIB_API CNullStream;
		class HLLIB_API CProcStream;
	}

	namespace Mapping
	{
		class HLLIB_API CView;
		class HLLIB_API CViewList;
		class HLLIB_API CMapping;
		class HLLIB_API CFileMapping;
		class HLLIB_API CMemoryMapping;
		class HLLIB_API CStreamMapping;
	}

	class HLLIB_API CStreamList;
	class HLLIB_API CPackage;
	class HLLIB_API CBSPFile;
	class HLLIB_API CGCFFile;
	class HLLIB_API CNCFFile;
	class HLLIB_API CPAKFile;
	class HLLIB_API CVBSPFile;
	class HLLIB_API CVPKFile;
	class HLLIB_API CWADFile;
	class HLLIB_API CXZPFile;
	class HLLIB_API CZIPFile;
}

namespace HLLib
{
	//
	// CDirectoryItem
	//

	class HLLIB_API CDirectoryItem
	{
	private:
		hlChar *lpName;
		hlUInt uiID;
		hlVoid *pData;
		CPackage *pPackage;
		CDirectoryFolder *pParent;

	public:
		CDirectoryItem(const hlChar *lpName, hlUInt uiID, hlVoid *pData, CPackage *pPackage, CDirectoryFolder *pParent);
		virtual ~CDirectoryItem();

		virtual HLDirectoryItemType GetType() const = 0;

		const hlChar *GetName() const;
		hlUInt GetID() const;
		hlVoid *GetData();
		const hlVoid *GetData() const;

		CPackage *GetPackage();
		const CPackage *GetPackage() const;
		CDirectoryFolder *GetParent();
		const CDirectoryFolder *GetParent() const;

		hlVoid GetPath(hlChar *lpPath, hlUInt uiPathSize) const;

		virtual hlBool Extract(const hlChar *lpPath) = 0;

	protected:
		static hlBool GetFileExists(const hlChar *lpPath);
		static hlBool GetFolderExists(const hlChar *lpPath);
		static hlVoid RemoveIllegalCharacters(hlChar *lpName);
	};

	//
	// CDirectoryFile
	//

	class HLLIB_API CDirectoryFile : public CDirectoryItem
	{
	public:
		CDirectoryFile(const hlChar *lpName, hlUInt uiID, hlVoid *pData, CPackage *pPackage, CDirectoryFolder *pParent);
		virtual ~CDirectoryFile();

		virtual HLDirectoryItemType GetType() const;

		hlBool GetExtractable() const;
		hlBool GetExtractable(hlBool &bExtractable) const;
		HLValidation GetValidation() const;
		hlBool GetValidation(HLValidation &eValidation) const;
		hlUInt GetSize() const;
		hlBool GetSize(hlUInt &uiSize) const;
		hlUInt GetSizeOnDisk() const;
		hlBool GetSizeOnDisk(hlUInt &uiSize) const;

		hlBool CreateStream(Streams::IStream *&pStream) const;
		hlVoid ReleaseStream(Streams::IStream *pStream) const;

		virtual hlBool Extract(const hlChar *lpPath);
	};

	//
	// CDirectoryFolder
	//

	class HLLIB_API CDirectoryFolder : public CDirectoryItem
	{
	private:
		class CDirectoryItemVector;

	private:
		CDirectoryItemVector *pDirectoryItemVector;

	public:
		CDirectoryFolder(CPackage *pPackage);
		CDirectoryFolder(const hlChar *lpName, hlUInt uiID, hlVoid *pData, CPackage *pPackage, CDirectoryFolder *pParent);
		virtual ~CDirectoryFolder();

		virtual HLDirectoryItemType GetType() const;

		CDirectoryFolder *AddFolder(const hlChar *lpName, hlUInt uiID = HL_ID_INVALID, hlVoid *lpData = 0);
		CDirectoryFile *AddFile(const hlChar *lpName, hlUInt uiID = HL_ID_INVALID, hlVoid *lpData = 0);

		hlUInt GetCount() const;
		CDirectoryItem *GetItem(hlUInt uiIndex);
		const CDirectoryItem *GetItem(hlUInt uiIndex) const;
		CDirectoryItem *GetItem(const hlChar *lpName, HLFindType eFind = HL_FIND_ALL);
		const CDirectoryItem *GetItem(const hlChar *lpName, HLFindType eFind = HL_FIND_ALL) const;
		CDirectoryItem *GetRelativeItem(const hlChar *lpPath, HLFindType eFind = HL_FIND_ALL);
		const CDirectoryItem *GetRelativeItem(const hlChar *lpPath, HLFindType eFind = HL_FIND_ALL) const;

		hlVoid Sort(HLSortField eField = HL_FIELD_NAME, HLSortOrder eOrder = HL_ORDER_ASCENDING, hlBool bRecurse = hlTrue);

		CDirectoryItem *FindFirst(const hlChar *lpSearch, HLFindType eFind = HL_FIND_ALL);
		const CDirectoryItem *FindFirst(const hlChar *lpSearch, HLFindType eFind = HL_FIND_ALL) const;
		CDirectoryItem *FindNext(const CDirectoryItem *pItem, const hlChar *lpSearch, HLFindType eFind = HL_FIND_ALL);
		const CDirectoryItem *FindNext(const CDirectoryItem *pItem, const hlChar *lpSearch, HLFindType eFind = HL_FIND_ALL) const;

		hlUInt GetSize(hlBool bRecurse = hlTrue) const;
		hlULongLong GetSizeEx(hlBool bRecurse = hlTrue) const;
		hlUInt GetSizeOnDisk(hlBool bRecurse = hlTrue) const;
		hlULongLong GetSizeOnDiskEx(hlBool bRecurse = hlTrue) const;
		hlUInt GetFolderCount(hlBool bRecurse = hlTrue) const;
		hlUInt GetFileCount(hlBool bRecurse = hlTrue) const;

		virtual hlBool Extract(const hlChar *lpPath);

	private:
		hlBool Match(const hlChar *lpString, const hlChar *lpSearch) const;
		const CDirectoryItem *FindNext(const CDirectoryFolder *pFolder, const CDirectoryItem *pRelative, const hlChar *lpSearch, HLFindType eFind = HL_FIND_ALL) const;
	};

	namespace Streams
	{
		//
		// IStream
		//

		class HLLIB_API IStream
		{
		public:
			virtual ~IStream();

			virtual HLStreamType GetType() const = 0;

			virtual const hlChar *GetFileName() const = 0;

			virtual hlBool GetOpened() const = 0;
			virtual hlUInt GetMode() const = 0;

			virtual hlBool Open(hlUInt uiMode) = 0;
			virtual hlVoid Close() = 0;

			virtual hlULongLong GetStreamSize() const = 0;
			virtual hlULongLong GetStreamPointer() const = 0;

			virtual hlULongLong Seek(hlLongLong iOffset, HLSeekMode eSeekMode) = 0;

			virtual hlBool Read(hlChar &cChar) = 0;
			virtual hlUInt Read(hlVoid *lpData, hlUInt uiBytes) = 0;

			virtual hlBool Write(hlChar iChar) = 0;
			virtual hlUInt Write(const hlVoid *lpData, hlUInt uiBytes) = 0;
		};

		//
		// CFileStream
		//

		class HLLIB_API CFileStream : public IStream
		{
		private:
#ifdef _WIN32
			HANDLE hFile;
#else
			hlInt iFile;
#endif
			hlUInt uiMode;

			hlChar *lpFileName;

		public:
			CFileStream(const hlChar *lpFileName);
			~CFileStream();

			virtual HLStreamType GetType() const;

			virtual const hlChar *GetFileName() const;

			virtual hlBool GetOpened() const;
			virtual hlUInt GetMode() const;

			virtual hlBool Open(hlUInt uiMode);
			virtual hlVoid Close();

			virtual hlULongLong GetStreamSize() const;
			virtual hlULongLong GetStreamPointer() const;

			virtual hlULongLong Seek(hlLongLong iOffset, HLSeekMode eSeekMode);

			virtual hlBool Read(hlChar &cChar);
			virtual hlUInt Read(hlVoid *lpData, hlUInt uiBytes);

			virtual hlBool Write(hlChar iChar);
			virtual hlUInt Write(const hlVoid *lpData, hlUInt uiBytes);
		};

		//
		// CGCFStream
		//

		class HLLIB_API CGCFStream : public IStream
		{
		private:
			hlBool bOpened;
			hlUInt uiMode;

			CGCFFile &GCFFile;
			hlUInt uiFileID;

			Mapping::CView *pView;
			hlUInt uiBlockEntryIndex;
			hlULongLong uiBlockEntryOffset;
			hlUInt uiDataBlockIndex;
			hlULongLong uiDataBlockOffset;

			hlULongLong uiPointer;
			hlULongLong uiLength;

		public:
			CGCFStream(CGCFFile &GCFFile, hlUInt uiFileID);
			~CGCFStream();

			virtual HLStreamType GetType() const;

			const CGCFFile &GetPackage() const;
			virtual const hlChar *GetFileName() const;

			virtual hlBool GetOpened() const;
			virtual hlUInt GetMode() const;

			virtual hlBool Open(hlUInt uiMode);
			virtual hlVoid Close();

			virtual hlULongLong GetStreamSize() const;
			virtual hlULongLong GetStreamPointer() const;

			virtual hlULongLong Seek(hlLongLong iOffset, HLSeekMode eSeekMode);

			virtual hlBool Read(hlChar &cChar);
			virtual hlUInt Read(hlVoid *lpData, hlUInt uiBytes);

			virtual hlBool Write(hlChar iChar);
			virtual hlUInt Write(const hlVoid *lpData, hlUInt uiBytes);

		private:
			hlBool Map(hlUInt uiPointer);
		};

		//
		// CMappingStream
		//

		class HLLIB_API CMappingStream : public IStream
		{
		private:
			hlBool bOpened;
			hlUInt uiMode;

			Mapping::CMapping &Mapping;
			Mapping::CView *pView;

			hlULongLong uiMappingOffset;
			hlULongLong uiMappingSize;
			hlULongLong uiViewSize;

			hlULongLong uiPointer;
			hlULongLong uiLength;

		public:
			CMappingStream(Mapping::CMapping &Mapping, hlULongLong uiMappingOffset, hlULongLong uiMappingSize, hlULongLong uiViewSize = HL_DEFAULT_VIEW_SIZE);
			~CMappingStream();

			virtual HLStreamType GetType() const;

			const Mapping::CMapping &GetMapping() const;
			virtual const hlChar *GetFileName() const;

			virtual hlBool GetOpened() const;
			virtual hlUInt GetMode() const;

			virtual hlBool Open(hlUInt uiMode);
			virtual hlVoid Close();

			virtual hlULongLong GetStreamSize() const;
			virtual hlULongLong GetStreamPointer() const;

			virtual hlULongLong Seek(hlLongLong iOffset, HLSeekMode eSeekMode);

			virtual hlBool Read(hlChar &cChar);
			virtual hlUInt Read(hlVoid *lpData, hlUInt uiBytes);

			virtual hlBool Write(hlChar iChar);
			virtual hlUInt Write(const hlVoid *lpData, hlUInt uiBytes);

		private:
			hlBool Map(hlULongLong uiPointer);
		};

		//
		// CMemoryStream
		//

		class HLLIB_API CMemoryStream : public IStream
		{
		private:
			hlBool bOpened;
			hlUInt uiMode;

			hlVoid *lpData;
			hlUInt uiBufferSize;

			hlULongLong uiPointer;
			hlULongLong uiLength;

		public:
			CMemoryStream(hlVoid *lpData, hlUInt uiBufferSize);
			~CMemoryStream();

			virtual HLStreamType GetType() const;

			const hlVoid *GetBuffer() const;
			hlUInt GetBufferSize() const;
			virtual const hlChar *GetFileName() const;

			virtual hlBool GetOpened() const;
			virtual hlUInt GetMode() const;

			virtual hlBool Open(hlUInt uiMode);
			virtual hlVoid Close();

			virtual hlULongLong GetStreamSize() const;
			virtual hlULongLong GetStreamPointer() const;

			virtual hlULongLong Seek(hlLongLong iOffset, HLSeekMode eSeekMode);

			virtual hlBool Read(hlChar &cChar);
			virtual hlUInt Read(hlVoid *lpData, hlUInt uiBytes);

			virtual hlBool Write(hlChar iChar);
			virtual hlUInt Write(const hlVoid *lpData, hlUInt uiBytes);
		};

		//
		// CNullStream
		//

		class HLLIB_API CNullStream : public IStream
		{
		private:
			hlBool bOpened;
			hlUInt uiMode;

		public:
			CNullStream();
			~CNullStream();

			virtual HLStreamType GetType() const;

			virtual const hlChar *GetFileName() const;

			virtual hlBool GetOpened() const;
			virtual hlUInt GetMode() const;

			virtual hlBool Open(hlUInt uiMode);
			virtual hlVoid Close();

			virtual hlULongLong GetStreamSize() const;
			virtual hlULongLong GetStreamPointer() const;

			virtual hlULongLong Seek(hlLongLong iOffset, HLSeekMode eSeekMode);

			virtual hlBool Read(hlChar &cChar);
			virtual hlUInt Read(hlVoid *lpData, hlUInt uiBytes);

			virtual hlBool Write(hlChar cChar);
			virtual hlUInt Write(const hlVoid *lpData, hlUInt uiBytes);
		};

		//
		// CProcStream
		//

		class HLLIB_API CProcStream : public IStream
		{
		private:
			hlBool bOpened;
			hlUInt uiMode;

			hlVoid *pUserData;

		public:
			CProcStream(hlVoid *pUserData);
			~CProcStream();

			virtual HLStreamType GetType() const;

			virtual const hlChar *GetFileName() const;

			virtual hlBool GetOpened() const;
			virtual hlUInt GetMode() const;

			virtual hlBool Open(hlUInt uiMode);
			virtual hlVoid Close();

			virtual hlULongLong GetStreamSize() const;
			virtual hlULongLong GetStreamPointer() const;

			virtual hlULongLong Seek(hlLongLong iOffset, HLSeekMode eSeekMode);

			virtual hlBool Read(hlChar &cChar);
			virtual hlUInt Read(hlVoid *lpData, hlUInt uiBytes);

			virtual hlBool Write(hlChar iChar);
			virtual hlUInt Write(const hlVoid *lpData, hlUInt uiBytes);
		};
	}

	namespace Mapping
	{
		//
		// CView
		//

		class HLLIB_API CView
		{
			friend class CMapping;

		private:
			CMapping *pMapping;

			hlVoid *lpView;
			hlULongLong uiOffset;
			hlULongLong uiLength;
			hlULongLong uiAllocationOffset;
			hlULongLong uiAllocationLength;

		public:
			CView(CMapping *pMapping, hlVoid *lpView, hlULongLong uiAllocationOffset, hlULongLong uiAllocationLength, hlULongLong uiOffset = 0, hlULongLong uiLength = 0);
			~CView();

			CMapping *GetMapping() const;

			const hlVoid *GetView() const;
			hlULongLong GetOffset() const;
			hlULongLong GetLength() const;
			const hlVoid *GetAllocationView() const;
			hlULongLong GetAllocationOffset() const;
			hlULongLong GetAllocationLength() const;
		};

		//
		// CMapping
		//

		class HLLIB_API CMapping
		{
		private:
			CViewList *pViews;

		public:
			CMapping();
			virtual ~CMapping();

			virtual HLMappingType GetType() const = 0;

			virtual const hlChar *GetFileName() const;

			virtual hlBool GetOpened() const = 0;
			virtual hlUInt GetMode() const = 0;

			hlUInt GetTotalAllocations() const;
			hlULongLong GetTotalMemoryAllocated() const;
			hlULongLong GetTotalMemoryUsed() const;

			hlBool Open(hlUInt uiMode);
			hlVoid Close();

			virtual hlULongLong GetMappingSize() const = 0;

			hlBool Map(CView *&pView, hlULongLong uiOffset, hlULongLong uiLength);
			hlBool Unmap(CView *&pView);

			hlBool Commit(CView &View);
			hlBool Commit(CView &View, hlULongLong uiOffset, hlULongLong uiLength);

		private:
			virtual hlBool OpenInternal(hlUInt uiMode) = 0;
			virtual hlVoid CloseInternal() = 0;

			virtual hlBool MapInternal(CView *&pView, hlULongLong uiOffset, hlULongLong uiLength) = 0;
			virtual hlVoid UnmapInternal(CView &View);

			virtual hlBool CommitInternal(CView &View, hlULongLong uiOffset, hlULongLong uiLength);
		};

		//
		// CFileMapping
		//

		class HLLIB_API CFileMapping : public CMapping
		{
		private:
#ifdef _WIN32
			HANDLE hFile;
			HANDLE hFileMapping;
#else
			hlInt iFile;
#endif
			hlUInt uiAllocationGranularity;
			hlUInt uiMode;

			hlVoid *lpView;
			hlULongLong uiViewSize;

			hlChar *lpFileName;

		public:
			CFileMapping(const hlChar *lpFileName);
			virtual ~CFileMapping();

			virtual HLMappingType GetType() const;

			virtual const hlChar *GetFileName() const;

			virtual hlBool GetOpened() const;
			virtual hlUInt GetMode() const;

			virtual hlULongLong GetMappingSize() const;

		private:
			virtual hlBool OpenInternal(hlUInt uiMode);
			virtual hlVoid CloseInternal();

			virtual hlBool MapInternal(CView *&pView, hlULongLong uiOffset, hlULongLong uiLength);
			virtual hlVoid UnmapInternal(CView &View);
		};

		//
		// CMemoryMapping
		//

		class HLLIB_API CMemoryMapping : public CMapping
		{
		private:
			hlBool bOpened;
			hlUInt uiMode;

			hlVoid *lpData;
			hlULongLong uiBufferSize;

		public:
			CMemoryMapping(hlVoid *lpData, hlULongLong uiBufferSize);
			virtual ~CMemoryMapping();

			virtual HLMappingType GetType() const;

			const hlVoid *GetBuffer() const;
			hlUInt GetBufferSize() const;

			virtual hlBool GetOpened() const;
			virtual hlUInt GetMode() const;

			virtual hlULongLong GetMappingSize() const;

		private:
			virtual hlBool OpenInternal(hlUInt uiMode);
			virtual hlVoid CloseInternal();

			virtual hlBool MapInternal(CView *&pView, hlULongLong uiOffset, hlULongLong uiLength);
		};

		//
		// CStreamMapping
		//

		class HLLIB_API CStreamMapping : public CMapping
		{
		private:
			Streams::IStream &Stream;

		public:
			CStreamMapping(Streams::IStream &Stream);
			virtual ~CStreamMapping();

			virtual HLMappingType GetType() const;

			const Streams::IStream& GetStream() const;
			virtual const hlChar *GetFileName() const;

			virtual hlBool GetOpened() const;
			virtual hlUInt GetMode() const;

			virtual hlULongLong GetMappingSize() const;

		private:
			virtual hlBool OpenInternal(hlUInt uiMode);
			virtual hlVoid CloseInternal();

			virtual hlBool MapInternal(CView *&pView, hlULongLong uiOffset, hlULongLong uiLength);
			virtual hlVoid UnmapInternal(CView &View);

			virtual hlBool CommitInternal(CView &View, hlULongLong uiOffset, hlULongLong uiLength);
		};
	}

	//
	// CPackage
	//

	class HLLIB_API CPackage
	{
	private:
		hlBool bDeleteStream;
		hlBool bDeleteMapping;
		Streams::IStream *pStream;

	protected:
		Mapping::CMapping *pMapping;

		CDirectoryFolder *pRoot;

	private:
		CStreamList *pStreams;

	public:
		CPackage();
		virtual ~CPackage();

		virtual HLPackageType GetType() const = 0;
		virtual const hlChar *GetExtension() const = 0;
		virtual const hlChar *GetDescription() const = 0;

		hlBool GetOpened() const;

		hlBool Open(Streams::IStream &Stream, hlUInt uiMode);
		hlBool Open(Mapping::CMapping &Mapping, hlUInt uiMode);
		hlBool Open(const hlChar *lpFileName, hlUInt uiMode);
		hlBool Open(hlVoid *lpData, hlUInt uiBufferSize, hlUInt uiMode);
		hlBool Open(hlVoid *pUserData, hlUInt uiMode);
		hlVoid Close();

		hlBool Defragment();

		const Mapping::CMapping* GetMapping() const;
		CDirectoryFolder *GetRoot();
		const CDirectoryFolder *GetRoot() const;

		hlUInt GetAttributeCount() const;
		const hlChar *GetAttributeName(HLPackageAttribute eAttribute) const;
		hlBool GetAttribute(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		hlUInt GetItemAttributeCount() const;
		const hlChar *GetItemAttributeName(HLPackageAttribute eAttribute) const;
		hlBool GetItemAttribute(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		hlBool GetFileExtractable(const CDirectoryFile *pFile, hlBool &bExtractable) const;
		hlBool GetFileValidation(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		hlBool GetFileSize(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		hlBool GetFileSizeOnDisk(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		hlBool CreateStream(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;
		hlVoid ReleaseStream(Streams::IStream *pStream) const;

	protected:
		virtual hlBool MapDataStructures() = 0;
		virtual hlVoid UnmapDataStructures() = 0;

		virtual hlBool DefragmentInternal();

		virtual CDirectoryFolder *CreateRoot() = 0;
		virtual hlVoid ReleaseRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const;
		virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const = 0;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const = 0;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const = 0;
		virtual hlVoid ReleaseStreamInternal(Streams::IStream &Stream) const;

	private:
		hlBool Open(Streams::IStream *pStream, hlUInt uiMode, hlBool bDeleteStream);
		hlBool Open(Mapping::CMapping *pMapping, hlUInt uiMode, hlBool bDeleteMapping);
	};

	//
	// BSP File
	//

	#define HL_BSP_LUMP_COUNT 15

	class HLLIB_API CBSPFile : public CPackage
	{
	private:
		#pragma pack(1)

		struct BSPLump
		{
			hlUInt uiOffset;
			hlUInt uiLength;
		};

		struct BSPHeader
		{
			hlUInt uiVersion;
			BSPLump lpLumps[HL_BSP_LUMP_COUNT];
		};

		struct BSPTextureHeader
		{
			hlUInt uiTextureCount;
			hlUInt lpOffsets[1];
		};

		struct BSPTexture
		{
			hlChar lpName[16];
			hlUInt uiWidth;
			hlUInt uiHeight;
			hlUInt lpOffsets[4];
		};

		#pragma pack()

	private:
		static const char *lpAttributeNames[];
		static const char *lpItemAttributeNames[];

		Mapping::CView *pHeaderView;
		Mapping::CView *pTextureView;

		const BSPHeader *pHeader;
		const BSPTextureHeader *pTextureHeader;

	public:
		CBSPFile();
		virtual ~CBSPFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;
		virtual hlVoid ReleaseStreamInternal(Streams::IStream &Stream) const;

	private:
		hlVoid GetFileName(hlChar *lpBuffer, hlUInt uiBufferSize);

		hlBool GetLumpInfo(const CDirectoryFile &File, hlUInt &uiWidth, hlUInt &uiHeight, hlUInt &uiPaletteSize, hlUInt uiMipmap = 0) const;
		hlBool GetLumpInfo(const CDirectoryFile &File, hlUInt &uiWidth, hlUInt &uiHeight, hlUInt &uiPaletteSize, const hlByte *&lpPalette, const hlByte *&lpPixels, hlUInt uiMipmap = 0) const;
	};

	//
	// CGCFFile
	//

	class HLLIB_API CGCFFile : public CPackage
	{
		friend class Streams::CGCFStream;

	private:
		#pragma pack(1)

		struct GCFHeader
		{
			hlUInt uiDummy0;		// Always 0x00000001
			hlUInt uiDummy1;		// Always 0x00000001
			hlUInt uiVersion;		// GCF version number.
			hlUInt uiCacheID;
			hlUInt uiLastVersionPlayed;
			hlUInt uiDummy3;
			hlUInt uiDummy4;
			hlUInt uiFileSize;		// Total size of GCF file in bytes.
			hlUInt uiBlockSize;		// Size of each data block in bytes.
			hlUInt uiBlockCount;	// Number of data blocks.
			hlUInt uiDummy5;
		};

		struct GCFBlockEntryHeader
		{
			hlUInt uiBlockCount;	// Number of data blocks.
			hlUInt uiBlocksUsed;	// Number of data blocks that point to data.
			hlUInt uiDummy0;
			hlUInt uiDummy1;
			hlUInt uiDummy2;
			hlUInt uiDummy3;
			hlUInt uiDummy4;
			hlUInt uiChecksum;		// Header checksum.
		};

		struct GCFBlockEntry
		{
			hlUInt uiEntryFlags;				// Flags for the block entry.  0x200F0000 == Not used.
			hlUInt uiFileDataOffset;			// The offset for the data contained in this block entry in the file.
			hlUInt uiFileDataSize;				// The length of the data in this block entry.
			hlUInt uiFirstDataBlockIndex;		// The index to the first data block of this block entry's data.
			hlUInt uiNextBlockEntryIndex;		// The next block entry in the series.  (N/A if == BlockCount.)
			hlUInt uiPreviousBlockEntryIndex;	// The previous block entry in the series.  (N/A if == BlockCount.)
			hlUInt uiDirectoryIndex;			// The index of the block entry in the directory.
		};

		struct GCFFragmentationMapHeader
		{
			hlUInt uiBlockCount;		// Number of data blocks.
			hlUInt uiFirstUnusedEntry;	// The index of the first unused fragmentation map entry.
			hlUInt uiTerminator;		// The block entry terminator; 0 = 0x0000ffff or 1 = 0xffffffff.
			hlUInt uiChecksum;			// Header checksum.
		};

		struct GCFFragmentationMap
		{
			hlUInt uiNextDataBlockIndex;		// The index of the next data block.
		};

		// The below section is part of version 5 but not version 6.

		struct GCFBlockEntryMapHeader
		{
			hlUInt uiBlockCount;			// Number of data blocks.	
			hlUInt uiFirstBlockEntryIndex;	// Index of the first block entry.
			hlUInt uiLastBlockEntryIndex;	// Index of the last block entry.
			hlUInt uiDummy0;
			hlUInt uiChecksum;				// Header checksum.
		};

		struct GCFBlockEntryMap
		{
			hlUInt uiPreviousBlockEntryIndex;	// The previous block entry.  (N/A if == BlockCount.)
			hlUInt uiNextBlockEntryIndex;		// The next block entry.  (N/A if == BlockCount.)
		};

		// End section.

		struct GCFDirectoryHeader
		{
			hlUInt uiDummy0;				// Always 0x00000004
			hlUInt uiCacheID;				// Cache ID.
			hlUInt uiLastVersionPlayed;		// GCF file version.
			hlUInt uiItemCount;				// Number of items in the directory.	
			hlUInt uiFileCount;				// Number of files in the directory.
			hlUInt uiDummy1;				// Always 0x00008000.  Data per checksum?
			hlUInt uiDirectorySize;			// Size of lpGCFDirectoryEntries & lpGCFDirectoryNames & lpGCFDirectoryInfo1Entries & lpGCFDirectoryInfo2Entries & lpGCFDirectoryCopyEntries & lpGCFDirectoryLocalEntries in bytes.
			hlUInt uiNameSize;				// Size of the directory names in bytes.
			hlUInt uiInfo1Count;			// Number of Info1 entires.
			hlUInt uiCopyCount;				// Number of files to copy.
			hlUInt uiLocalCount;			// Number of files to keep local.
			hlUInt uiDummy2;
			hlUInt uiDummy3;
			hlUInt uiChecksum;				// Header checksum.
		};

		struct GCFDirectoryEntry
		{
			hlUInt uiNameOffset;		// Offset to the directory item name from the end of the directory items.
			hlUInt uiItemSize;			// Size of the item.  (If file, file size.  If folder, num items.)
			hlUInt uiChecksumIndex;		// Checksome index. (0xFFFFFFFF == None).
			hlUInt uiDirectoryFlags;	// Flags for the directory item.  (0x00000000 == Folder).
			hlUInt uiParentIndex;		// Index of the parent directory item.  (0xFFFFFFFF == None).
			hlUInt uiNextIndex;			// Index of the next directory item.  (0x00000000 == None).
			hlUInt uiFirstIndex;		// Index of the first directory item.  (0x00000000 == None).
		};

		struct GCFDirectoryInfo1Entry
		{
			hlUInt uiDummy0;
		};

		struct GCFDirectoryInfo2Entry
		{
			hlUInt uiDummy0;
		};

		struct GCFDirectoryCopyEntry
		{
			hlUInt uiDirectoryIndex;	// Index of the directory item.
		};

		struct GCFDirectoryLocalEntry
		{
			hlUInt uiDirectoryIndex;	// Index of the directory item.
		};

		// The below header was added in version 4 or version 5.

		struct GCFDirectoryMapHeader
		{
			hlUInt uiDummy0;			// Always 0x00000001
			hlUInt uiDummy1;			// Always 0x00000000
		};

		struct GCFDirectoryMapEntry
		{
			hlUInt uiFirstBlockIndex;	// Index of the first data block. (N/A if == BlockCount.)
		};

		struct GCFChecksumHeader
		{
			hlUInt uiDummy0;			// Always 0x00000001
			hlUInt uiChecksumSize;		// Size of LPGCFCHECKSUMHEADER & LPGCFCHECKSUMMAPHEADER & in bytes.
		};

		struct GCFChecksumMapHeader
		{
			hlUInt uiDummy0;			// Always 0x14893721
			hlUInt uiDummy1;			// Always 0x00000001
			hlUInt uiItemCount;			// Number of items.
			hlUInt uiChecksumCount;		// Number of checksums.
		};

		struct GCFChecksumMapEntry
		{
			hlUInt uiChecksumCount;			// Number of checksums.
			hlUInt uiFirstChecksumIndex;	// Index of first checksum.
		};

		struct GCFChecksumEntry
		{
			hlULong uiChecksum;				// Checksum.
		};

		struct GCFDataBlockHeader
		{
			hlUInt uiLastVersionPlayed;		// GCF file version.  This field is not part of all file versions.
			hlUInt uiBlockCount;			// Number of data blocks.
			hlUInt uiBlockSize;				// Size of each data block in bytes.
			hlUInt uiFirstBlockOffset;		// Offset to first data block.
			hlUInt uiBlocksUsed;			// Number of data blocks that contain data.
			hlUInt uiChecksum;				// Header checksum.
		};

		#pragma pack()

	private:
		static const char *lpAttributeNames[];
		static const char *lpItemAttributeNames[];

		Mapping::CView *pHeaderView;

		GCFHeader *pHeader;

		GCFBlockEntryHeader *pBlockEntryHeader;
		GCFBlockEntry *lpBlockEntries;

		GCFFragmentationMapHeader *pFragmentationMapHeader;
		GCFFragmentationMap *lpFragmentationMap;

		// The below section is part of version 5 but not version 6.
		GCFBlockEntryMapHeader *pBlockEntryMapHeader;
		GCFBlockEntryMap *lpBlockEntryMap;

		GCFDirectoryHeader *pDirectoryHeader;
		GCFDirectoryEntry *lpDirectoryEntries;
		hlChar *lpDirectoryNames;
		GCFDirectoryInfo1Entry *lpDirectoryInfo1Entries;
		GCFDirectoryInfo2Entry *lpDirectoryInfo2Entries;
		GCFDirectoryCopyEntry *lpDirectoryCopyEntries;
		GCFDirectoryLocalEntry *lpDirectoryLocalEntries;

		GCFDirectoryMapHeader *pDirectoryMapHeader;
		GCFDirectoryMapEntry *lpDirectoryMapEntries;

		GCFChecksumHeader *pChecksumHeader;
		GCFChecksumMapHeader *pChecksumMapHeader;
		GCFChecksumMapEntry *lpChecksumMapEntries;
		GCFChecksumEntry *lpChecksumEntries;

		GCFDataBlockHeader *pDataBlockHeader;

		CDirectoryItem **lpDirectoryItems;

	public:
		CGCFFile();
		virtual ~CGCFFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual hlBool DefragmentInternal();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const;
		virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;

	private:
		hlVoid CreateRoot(CDirectoryFolder *pFolder);

		hlVoid GetItemFragmentation(hlUInt uiDirectoryItemIndex, hlUInt &uiBlocksFragmented, hlUInt &uiBlocksUsed) const;
	};

	//
	// CNCFFile
	//

	class HLLIB_API CNCFFile : public CPackage
	{
	private:
		#pragma pack(1)

		struct NCFHeader
		{
			hlUInt uiDummy0;			// Always 0x00000001
			hlUInt uiMajorVersion;		// Always 0x00000002
			hlUInt uiMinorVersion;		// NCF version number.
			hlUInt uiCacheID;
			hlUInt uiLastVersionPlayed;
			hlUInt uiDummy3;
			hlUInt uiDummy4;
			hlUInt uiFileSize;		// Total size of NCF file in bytes.
			hlUInt uiBlockSize;		// Size of each data block in bytes.
			hlUInt uiBlockCount;	// Number of data blocks.
			hlUInt uiDummy5;
		};

		struct NCFDirectoryHeader
		{
			hlUInt uiDummy0;				// Always 0x00000004
			hlUInt uiCacheID;				// Cache ID.
			hlUInt uiLastVersionPlayed;		// NCF file version.
			hlUInt uiItemCount;				// Number of items in the directory.	
			hlUInt uiFileCount;				// Number of files in the directory.
			hlUInt uiChecksumDataLength;	// Always 0x00008000.  Data per checksum?
			hlUInt uiDirectorySize;			// Size of lpNCFDirectoryEntries & lpNCFDirectoryNames & lpNCFDirectoryInfo1Entries & lpNCFDirectoryInfo2Entries & lpNCFDirectoryCopyEntries & lpNCFDirectoryLocalEntries in bytes.
			hlUInt uiNameSize;				// Size of the directory names in bytes.
			hlUInt uiInfo1Count;			// Number of Info1 entires.
			hlUInt uiCopyCount;				// Number of files to copy.
			hlUInt uiLocalCount;			// Number of files to keep local.
			hlUInt uiDummy1;
			hlUInt uiDummy2;
			hlUInt uiChecksum;				// Header checksum.
		};

		struct NCFDirectoryEntry
		{
			hlUInt uiNameOffset;		// Offset to the directory item name from the end of the directory items.
			hlUInt uiItemSize;			// Size of the item.  (If file, file size.  If folder, num items.)
			hlUInt uiChecksumIndex;		// Checksome index. (0xFFFFFFFF == None).
			hlUInt uiDirectoryFlags;	// Flags for the directory item.  (0x00000000 == Folder).
			hlUInt uiParentIndex;		// Index of the parent directory item.  (0xFFFFFFFF == None).
			hlUInt uiNextIndex;			// Index of the next directory item.  (0x00000000 == None).
			hlUInt uiFirstIndex;		// Index of the first directory item.  (0x00000000 == None).
		};

		struct NCFDirectoryInfo1Entry
		{
			hlUInt uiDummy0;
		};

		struct NCFDirectoryInfo2Entry
		{
			hlUInt uiDummy0;
		};

		struct NCFDirectoryCopyEntry
		{
			hlUInt uiDirectoryIndex;	// Index of the directory item.
		};

		struct NCFDirectoryLocalEntry
		{
			hlUInt uiDirectoryIndex;	// Index of the directory item.
		};

		struct NCFUnknownHeader
		{
			hlUInt uiDummy0;			// Always 0x00000001
			hlUInt uiDummy1;			// Always 0x00000000
		};

		struct NCFUnknownEntry
		{
			hlUInt uiDummy0;
		};

		struct NCFChecksumHeader
		{
			hlUInt uiDummy0;			// Always 0x00000001
			hlUInt uiChecksumSize;		// Size of LPNCFCHECKSUMHEADER & LPNCFCHECKSUMMAPHEADER & in bytes.
		};

		struct NCFChecksumMapHeader
		{
			hlUInt uiDummy0;			// Always 0x14893721
			hlUInt uiDummy1;			// Always 0x00000001
			hlUInt uiItemCount;			// Number of items.
			hlUInt uiChecksumCount;		// Number of checksums.
		};

		struct NCFChecksumMapEntry
		{
			hlUInt uiChecksumCount;			// Number of checksums.
			hlUInt uiFirstChecksumIndex;	// Index of first checksum.
		};

		struct NCFChecksumEntry
		{
			hlULong uiChecksum;				// Checksum.
		};

		#pragma pack()

	private:
		static const char *lpAttributeNames[];
		static const char *lpItemAttributeNames[];

		hlChar *lpRootPath;

		Mapping::CView *pHeaderView;

		NCFHeader *pHeader;

		NCFDirectoryHeader *pDirectoryHeader;
		NCFDirectoryEntry *lpDirectoryEntries;
		hlChar *lpDirectoryNames;
		NCFDirectoryInfo1Entry *lpDirectoryInfo1Entries;
		NCFDirectoryInfo2Entry *lpDirectoryInfo2Entries;
		NCFDirectoryCopyEntry *lpDirectoryCopyEntries;
		NCFDirectoryLocalEntry *lpDirectoryLocalEntries;

		NCFUnknownHeader *pUnknownHeader;
		NCFUnknownEntry *lpUnknownEntries;

		NCFChecksumHeader *pChecksumHeader;
		NCFChecksumMapHeader *pChecksumMapHeader;
		NCFChecksumMapEntry *lpChecksumMapEntries;
		NCFChecksumEntry *lpChecksumEntries;

	public:
		CNCFFile();
		virtual ~CNCFFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

		const hlChar *GetRootPath() const;
		hlVoid SetRootPath(const hlChar *lpRootPath);

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const;
		virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;

	private:
		hlVoid CreateRoot(CDirectoryFolder *pFolder);

		hlVoid GetPath(const CDirectoryFile *pFile, hlChar *lpPath, hlUInt uiPathSize) const;
	};

	//
	// CPAKFile
	//

	class HLLIB_API CPAKFile : public CPackage
	{
	private:
		#pragma pack(1)

		struct PAKHeader
		{
			hlChar lpSignature[4];
			hlUInt uiDirectoryOffset;
			hlUInt uiDirectoryLength;
		};

		struct PAKDirectoryItem
		{
			hlChar lpItemName[56];
			hlUInt uiItemOffset;
			hlUInt uiItemLength;
		};

		#pragma pack()

	private:
		Mapping::CView *pHeaderView;
		Mapping::CView *pDirectoryItemView;

		const PAKHeader *pHeader;
		const PAKDirectoryItem *lpDirectoryItems;

	public:
		CPAKFile();
		virtual ~CPAKFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;
	};

	//
	// CSGAFile
	//

	class HLLIB_API CSGAFile : public CPackage
	{
	private:
		#pragma pack(1)

		struct SGAHeaderBase
		{
			hlChar lpSignature[8];
			hlUShort uiMajorVersion;
			hlUShort uiMinorVersion;
		};

		struct SGAHeader4 : public SGAHeaderBase
		{
			hlByte lpFileMD5[16];
			hlWChar lpName[64];
			hlByte lpHeaderMD5[16];
			hlUInt uiHeaderLength;
			hlUInt uiFileDataOffset;
			hlUInt uiDummy0;
		};

		struct SGAHeader6 : public SGAHeaderBase
		{
			hlWChar lpName[64];
			hlUInt uiHeaderLength;
			hlUInt uiFileDataOffset;
			hlUInt uiDummy0;
		};

		template<typename T>
		struct SGADirectoryHeader
		{
			hlUInt uiSectionOffset;
			T uiSectionCount;
			hlUInt uiFolderOffset;
			T uiFolderCount;
			hlUInt uiFileOffset;
			T uiFileCount;
			hlUInt uiStringTableOffset;
			T uiStringTableCount;
		};

		typedef SGADirectoryHeader<hlUShort> SGADirectoryHeader4;
		typedef SGADirectoryHeader<hlUInt> SGADirectoryHeader5;

		struct SGADirectoryHeader7 : public SGADirectoryHeader5
		{
			hlUInt uiHashTableOffset;
			hlUInt uiBlockSize;
		};

		template<typename T>
		struct SGASection
		{
			hlChar lpAlias[64];
			hlChar lpName[64];
			T uiFolderStartIndex;
			T uiFolderEndIndex;
			T uiFileStartIndex;
			T uiFileEndIndex;
			T uiFolderRootIndex;
		};

		typedef SGASection<hlUShort> SGASection4;
		typedef SGASection<hlUInt> SGASection5;

		template<typename T>
		struct SGAFolder
		{
			hlUInt uiNameOffset;
			T uiFolderStartIndex;
			T uiFolderEndIndex;
			T uiFileStartIndex;
			T uiFileEndIndex;
		};

		typedef SGAFolder<hlUShort> SGAFolder4;
		typedef SGAFolder<hlUInt> SGAFolder5;

		struct SGAFile4
		{
			hlUInt uiNameOffset;
			hlUInt uiOffset;
			hlUInt uiSizeOnDisk;
			hlUInt uiSize;
			hlUInt uiTimeModified;
			hlByte uiDummy0;
			hlByte uiType;
		};

		struct SGAFile6 : public SGAFile4
		{
			hlUInt uiCRC32;
		};

		struct SGAFile7 : public SGAFile6
		{
			hlUInt uiHashOffset;
		};

		struct SGAFileHeader
		{
			hlChar lpName[256];
			hlUInt uiCRC32;
		};

		enum SGAFileVerification
		{
			VERIFICATION_NONE,
			VERIFICATION_CRC,
			VERIFICATION_CRC_BLOCKS,
			VERIFICATION_MD5_BLOCKS,
			VERIFICATION_SHA1_BLOCKS,
			VERIFICATION_COUNT,
		};

		#pragma pack()

		class ISGADirectory
		{
		public:
			virtual ~ISGADirectory() = 0;

		public:
			virtual hlBool MapDataStructures() = 0;
			virtual hlVoid UnmapDataStructures() = 0;

			virtual CDirectoryFolder *CreateRoot() = 0;

			virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const = 0;

			virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const = 0;
			virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const = 0;
			virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const = 0;
			virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const = 0;

			virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const = 0;
			virtual hlVoid ReleaseStreamInternal(Streams::IStream &Stream) const = 0;
		};

		// Specialization SGAFile7 and up where the CRC moved to the header and the CRC is of the compressed data and there are stronger hashes.
		template<typename TSGAHeader, typename TSGADirectoryHeader, typename TSGASection, typename TSGAFolder, typename TSGAFile>
		class CSGASpecializedDirectory : public ISGADirectory
		{
		public:
			typedef typename TSGAHeader SGAHeader;
			typedef typename TSGADirectoryHeader SGADirectoryHeader;
			typedef typename TSGASection SGASection;
			typedef typename TSGAFolder SGAFolder;
			typedef typename TSGAFile SGAFile;

			CSGASpecializedDirectory(CSGAFile& File);

		protected:
			CSGAFile& File;

			Mapping::CView *pHeaderDirectoryView;
			const SGADirectoryHeader *pDirectoryHeader;
			const SGASection *lpSections;
			const SGAFolder *lpFolders;
			const SGAFile *lpFiles;
			const hlChar *lpStringTable;

		public:
			virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

			virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		};

		// Specialization SGAFile4 where the CRC was stored in a SGAFileHeader located before the file data.
		template<typename TSGAHeader, typename TSGADirectoryHeader, typename TSGASection, typename TSGAFolder>
		class CSGASpecializedDirectory<TSGAHeader, TSGADirectoryHeader, TSGASection, TSGAFolder, SGAFile4> : public ISGADirectory
		{
		public:
			typedef typename TSGAHeader SGAHeader;
			typedef typename TSGADirectoryHeader SGADirectoryHeader;
			typedef typename TSGASection SGASection;
			typedef typename TSGAFolder SGAFolder;
			typedef CSGAFile::SGAFile4 SGAFile;

			CSGASpecializedDirectory(CSGAFile& File);

		protected:
			CSGAFile& File;

			Mapping::CView *pHeaderDirectoryView;
			const SGADirectoryHeader *pDirectoryHeader;
			const SGASection *lpSections;
			const SGAFolder *lpFolders;
			const SGAFile *lpFiles;
			const hlChar *lpStringTable;

		public:
			virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

			virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		};

		// Specialization SGAFile6 where the CRC moved to the header and the CRC is of the compressed data.
		template<typename TSGAHeader, typename TSGADirectoryHeader, typename TSGASection, typename TSGAFolder>
		class CSGASpecializedDirectory<TSGAHeader, TSGADirectoryHeader, TSGASection, TSGAFolder, SGAFile6> : public ISGADirectory
		{
		public:
			typedef typename TSGAHeader SGAHeader;
			typedef typename TSGADirectoryHeader SGADirectoryHeader;
			typedef typename TSGASection SGASection;
			typedef typename TSGAFolder SGAFolder;
			typedef CSGAFile::SGAFile6 SGAFile;

			CSGASpecializedDirectory(CSGAFile& File);

		protected:
			CSGAFile& File;

			Mapping::CView *pHeaderDirectoryView;
			const SGADirectoryHeader *pDirectoryHeader;
			const SGASection *lpSections;
			const SGAFolder *lpFolders;
			const SGAFile *lpFiles;
			const hlChar *lpStringTable;

		public:
			virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

			virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		};

		template<typename TSGAHeader, typename TSGADirectoryHeader, typename TSGASection, typename TSGAFolder, typename TSGAFile>
		class CSGADirectory : public CSGASpecializedDirectory<TSGAHeader, TSGADirectoryHeader, TSGASection, TSGAFolder, TSGAFile>
		{
		public:
			CSGADirectory(CSGAFile& File);
			virtual ~CSGADirectory();

		public:
			virtual hlBool MapDataStructures();
			virtual hlVoid UnmapDataStructures();

			virtual CDirectoryFolder *CreateRoot();

			virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

			virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const;
			virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
			virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

			virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;
			virtual hlVoid ReleaseStreamInternal(Streams::IStream &Stream) const;

		private:
			hlVoid CreateFolder(CDirectoryFolder *pParent, hlUInt uiFolderIndex);
		};

		typedef CSGADirectory<SGAHeader4, SGADirectoryHeader4, SGASection4, SGAFolder4, SGAFile4> CSGADirectory4;
		typedef CSGADirectory<SGAHeader4, SGADirectoryHeader5, SGASection5, SGAFolder5, SGAFile4> CSGADirectory5;
		typedef CSGADirectory<SGAHeader6, SGADirectoryHeader5, SGASection5, SGAFolder5, SGAFile6> CSGADirectory6;
		typedef CSGADirectory<SGAHeader6, SGADirectoryHeader7, SGASection5, SGAFolder5, SGAFile7> CSGADirectory7;

		friend CSGADirectory4;
		friend CSGADirectory5;
		friend CSGADirectory6;
		friend CSGADirectory7;

	private:
		static const char *lpAttributeNames[];
		static const char *lpItemAttributeNames[];
		static const char *lpVerificationNames[];

		Mapping::CView *pHeaderView;
		const SGAHeaderBase *pHeader;

		ISGADirectory* pDirectory;

	public:
		CSGAFile();
		virtual ~CSGAFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const;
		virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;
		virtual hlVoid ReleaseStreamInternal(Streams::IStream &Stream) const;
	};

	//
	// CVBSPFile
	//

	#define HL_VBSP_LUMP_COUNT 64

	class HLLIB_API CVBSPFile : public CPackage
	{
	private:
		#pragma pack(1)

		struct VBSPLump
		{
			hlUInt	uiOffset;
			hlUInt	uiLength;
			hlUInt	uiVersion;							// Default to zero.
			hlChar	lpFourCC[4];						// Default to ( char )0, ( char )0, ( char )0, ( char )0.
		};

		struct VBSPHeader
		{
			hlChar		lpSignature[4];					// BSP file signature.
			hlInt		iVersion;						// BSP file version.
			VBSPLump	lpLumps[HL_VBSP_LUMP_COUNT];	// Lumps.
			hlInt		iMapRevision;					// The map's revision (iteration, version) number.
		};

		struct ZIPEndOfCentralDirectoryRecord
		{
			hlUInt uiSignature; // 4 bytes (0x06054b50)
			hlUInt16 uiNumberOfThisDisk;  // 2 bytes
			hlUInt16 uiNumberOfTheDiskWithStartOfCentralDirectory; // 2 bytes
			hlUInt16 uiCentralDirectoryEntriesThisDisk;	// 2 bytes
			hlUInt16 uiCentralDirectoryEntriesTotal;	// 2 bytes
			hlUInt uiCentralDirectorySize; // 4 bytes
			hlUInt uiStartOfCentralDirOffset; // 4 bytes
			hlUInt16 uiCommentLength; // 2 bytes
			// zip file comment follows
		};

		struct ZIPFileHeader
		{
			hlUInt uiSignature; //  4 bytes (0x02014b50) 
			hlUInt16 uiVersionMadeBy; // version made by 2 bytes 
			hlUInt16 uiVersionNeededToExtract; // version needed to extract 2 bytes 
			hlUInt16 uiFlags; // general purpose bit flag 2 bytes 
			hlUInt16 uiCompressionMethod; // compression method 2 bytes 
			hlUInt16 uiLastModifiedTime; // last mod file time 2 bytes 
			hlUInt16 uiLastModifiedDate; // last mod file date 2 bytes 
			hlUInt uiCRC32; // crc-32 4 bytes 
			hlUInt uiCompressedSize; // compressed size 4 bytes 
			hlUInt uiUncompressedSize; // uncompressed size 4 bytes 
			hlUInt16 uiFileNameLength; // file name length 2 bytes 
			hlUInt16 uiExtraFieldLength; // extra field length 2 bytes 
			hlUInt16 uiFileCommentLength; // file comment length 2 bytes 
			hlUInt16 uiDiskNumberStart; // disk number start 2 bytes 
			hlUInt16 uiInternalFileAttribs; // internal file attributes 2 bytes 
			hlUInt uiExternalFileAttribs; // external file attributes 4 bytes 
			hlUInt uiRelativeOffsetOfLocalHeader; // relative offset of local header 4 bytes 
			// file name (variable size) 
			// extra field (variable size) 
			// file comment (variable size) 
		};

		struct ZIPLocalFileHeader
		{
			hlUInt uiSignature; //local file header signature 4 bytes (0x04034b50) 
			hlUInt16 uiVersionNeededToExtract; // version needed to extract 2 bytes 
			hlUInt16 uiFlags; // general purpose bit flag 2 bytes 
			hlUInt16 uiCompressionMethod; // compression method 2 bytes 
			hlUInt16 uiLastModifiedTime; // last mod file time 2 bytes 
			hlUInt16 uiLastModifiedDate; // last mod file date 2 bytes 
			hlUInt uiCRC32; // crc-32 4 bytes 
			hlUInt uiCompressedSize; // compressed size 4 bytes 
			hlUInt uiUncompressedSize; // uncompressed size 4 bytes 
			hlUInt16 uiFileNameLength; // file name length 2 bytes 
			hlUInt16 uiExtraFieldLength; // extra field length 2 bytes 
			// file name (variable size) 
			// extra field (variable size) 
			// file data (variable size) 
		};

		#pragma pack()

	private:
		static const char *lpAttributeNames[];
		static const char *lpItemAttributeNames[];

		Mapping::CView *pHeaderView;
		Mapping::CView *pFileHeaderView;
		Mapping::CView *pEndOfCentralDirectoryRecordView;

		const VBSPHeader *pHeader;
		const ZIPEndOfCentralDirectoryRecord *pEndOfCentralDirectoryRecord;

	public:
		CVBSPFile();
		virtual ~CVBSPFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const;
		virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;

	private:
		hlVoid GetFileName(hlChar *lpBuffer, hlUInt uiBufferSize);
	};

	//
	// CVPKFile
	//

	class HLLIB_API CVPKFile : public CPackage
	{
	private:
		#pragma pack(1)

		struct VPKHeader
		{
			hlUInt uiSignature;			// Always 0x55aa1234.
			hlUInt uiVersion;
			hlUInt uiDirectoryLength;
		};

		// Added in version 2.
		struct VPKExtendedHeader
		{
			hlUInt uiDummy0;
			hlUInt uiArchiveHashLength;
			hlUInt uiExtraLength;		// Looks like some more MD5 hashes.
			hlUInt uiDummy1;
		};

		struct VPKDirectoryEntry
		{
			hlUInt uiCRC;
			hlUShort uiPreloadBytes;
			hlUShort uiArchiveIndex;
			hlUInt uiEntryOffset;
			hlUInt uiEntryLength;
			hlUShort uiDummy0;			// Always 0xffff.
		};

		// Added in version 2.
		struct VPKArchiveHash
		{
			hlUInt uiArchiveIndex;
			hlUInt uiArchiveOffset;
			hlUInt uiLength;
			hlByte lpHash[16];			// MD5
		};

		#pragma pack()

		struct VPKArchive
		{
			Streams::IStream *pStream;
			Mapping::CMapping *pMapping;
		};

		struct VPKDirectoryItem
		{
			VPKDirectoryItem(const hlChar *lpExtention, const hlChar *lpPath, const hlChar *lpName, const VPKDirectoryEntry *pDirectoryEntry, const hlVoid *lpPreloadData) : lpExtention(lpExtention), lpPath(lpPath), lpName(lpName), pDirectoryEntry(pDirectoryEntry), lpPreloadData(lpPreloadData)
			{
			}

			const hlChar *lpExtention;
			const hlChar *lpPath;
			const hlChar *lpName;
			const VPKDirectoryEntry *pDirectoryEntry;
			const hlVoid *lpPreloadData;
		};

		typedef std::list<VPKDirectoryItem *> CDirectoryItemList;

	private:
		static const char *lpAttributeNames[];
		static const char *lpItemAttributeNames[];

		Mapping::CView *pView;

		hlUInt uiArchiveCount;
		VPKArchive *lpArchives;

		const VPKHeader *pHeader;
		const VPKExtendedHeader *pExtendedHeader;
		const VPKArchiveHash *lpArchiveHashes;
		class CDirectoryItemList *pDirectoryItems;

	public:
		CVPKFile();
		virtual ~CVPKFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const;
		virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;
		virtual hlVoid ReleaseStreamInternal(Streams::IStream &Stream) const;

	private:
		hlBool MapString(const hlChar *&lpViewData, const hlChar *lpViewDirectoryDataEnd, const hlChar *&lpString);
	};

	//
	// CWADFile
	//

	class HLLIB_API CWADFile : public CPackage
	{
	private:
		#pragma pack(1)

		struct WADHeader
		{
			hlChar lpSignature[4];
			hlUInt uiLumpCount;
			hlUInt uiLumpOffset;
		};

		struct WADLump
		{
			hlUInt uiOffset;
			hlUInt uiDiskLength;
			hlUInt uiLength;
			hlChar iType;
			hlChar iCompression;
			hlChar iPadding0;
			hlChar iPadding1;
			hlChar lpName[16];
		};

		struct WADLumpInfo
		{
			hlUInt uiWidth;
			hlUInt uiHeight;
			hlUInt uiPaletteSize;
		};

		#pragma pack()

	private:
		static const char *lpAttributeNames[];
		static const char *lpItemAttributeNames[];

		Mapping::CView *pHeaderView;
		Mapping::CView *pLumpView;

		const WADHeader *pHeader;
		const WADLump *lpLumps;
		WADLumpInfo *lpLumpInfo;

	public:
		CWADFile();
		virtual ~CWADFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

		hlBool GetImageSize(const CDirectoryFile *pFile, hlUInt &uiPaletteDataSize, hlUInt &uiPixelDataSize);
		hlBool GetImageData(const CDirectoryFile *pFile, hlUInt &uiWidth, hlUInt &uiHeight, hlByte *lpPaletteData, hlByte *lpPixelData);

		hlBool GetImageSize(const CDirectoryFile *pFile, hlUInt &uiPixelDataSize);
		hlBool GetImageData(const CDirectoryFile *pFile, hlUInt &uiWidth, hlUInt &uiHeight, hlByte *lpPixelData);

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const;
		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;
		virtual hlVoid ReleaseStreamInternal(Streams::IStream &Stream) const;

	private:
		hlBool GetLumpInfo(const CDirectoryFile &File, hlUInt &uiWidth, hlUInt &uiHeight, hlUInt &uiPaletteSize, hlUInt uiMipmap = 0) const;
		hlBool GetLumpInfo(const CDirectoryFile &File, hlUInt &uiWidth, hlUInt &uiHeight, hlUInt &uiPaletteSize, const hlByte *&lpPalette, const hlByte *&lpPixels, Mapping::CView *&pView, hlUInt uiMipmap = 0) const;
	};

	//
	// CXZPFile
	//

	class HLLIB_API CXZPFile : public CPackage
	{
	private:
		#pragma pack(1)

		struct XZPHeader
		{
			hlChar lpSignature[4];
			hlUInt uiVersion;
			hlUInt uiPreloadDirectoryEntryCount;
			hlUInt uiDirectoryEntryCount;
			hlUInt uiPreloadBytes;
			hlUInt uiHeaderLength;
			hlUInt uiDirectoryItemCount;
			hlUInt uiDirectoryItemOffset;
			hlUInt uiDirectoryItemLength;
		};

		struct XZPDirectoryEntry
		{
			hlUInt uiFileNameCRC;
			hlUInt uiEntryLength;
			hlUInt uiEntryOffset;
		};

		struct XZPDirectoryMapping
		{
			hlUInt16 uiPreloadDirectoryEntryIndex;
		};

		struct XZPDirectoryItem
		{
			hlUInt uiFileNameCRC;
			hlUInt uiNameOffset;
			hlUInt uiTimeCreated;
		};

		struct XZPFooter
		{
			hlUInt uiFileLength;
			hlChar lpSignature[4];
		};

		#pragma pack()

	private:
		static const char *lpAttributeNames[];
		static const char *lpItemAttributeNames[];

		Mapping::CView *pHeaderView;
		Mapping::CView *pDirectoryEntryView;
		Mapping::CView *pDirectoryItemView;
		Mapping::CView *pFooterView;

		const XZPHeader *pHeader;
		const XZPDirectoryEntry *lpDirectoryEntries;
		const XZPDirectoryEntry *lpPreloadDirectoryEntries;
		const XZPDirectoryMapping *lpPreloadDirectoryMappings;
		const XZPDirectoryItem *lpDirectoryItems;
		const XZPFooter *pFooter;

	public:
		CXZPFile();
		virtual ~CXZPFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;
	};

	//
	// CZIPFile
	//

	class HLLIB_API CZIPFile : public CPackage
	{
	private:
		#pragma pack(1)

		struct ZIPEndOfCentralDirectoryRecord
		{
			hlUInt uiSignature; // 4 bytes (0x06054b50)
			hlUInt16 uiNumberOfThisDisk;  // 2 bytes
			hlUInt16 uiNumberOfTheDiskWithStartOfCentralDirectory; // 2 bytes
			hlUInt16 uiCentralDirectoryEntriesThisDisk;	// 2 bytes
			hlUInt16 uiCentralDirectoryEntriesTotal;	// 2 bytes
			hlUInt uiCentralDirectorySize; // 4 bytes
			hlUInt uiStartOfCentralDirOffset; // 4 bytes
			hlUInt16 uiCommentLength; // 2 bytes
			// zip file comment follows
		};

		struct ZIPFileHeader
		{
			hlUInt uiSignature; //  4 bytes (0x02014b50) 
			hlUInt16 uiVersionMadeBy; // version made by 2 bytes 
			hlUInt16 uiVersionNeededToExtract; // version needed to extract 2 bytes 
			hlUInt16 uiFlags; // general purpose bit flag 2 bytes 
			hlUInt16 uiCompressionMethod; // compression method 2 bytes 
			hlUInt16 uiLastModifiedTime; // last mod file time 2 bytes 
			hlUInt16 uiLastModifiedDate; // last mod file date 2 bytes 
			hlUInt uiCRC32; // crc-32 4 bytes 
			hlUInt uiCompressedSize; // compressed size 4 bytes 
			hlUInt uiUncompressedSize; // uncompressed size 4 bytes 
			hlUInt16 uiFileNameLength; // file name length 2 bytes 
			hlUInt16 uiExtraFieldLength; // extra field length 2 bytes 
			hlUInt16 uiFileCommentLength; // file comment length 2 bytes 
			hlUInt16 uiDiskNumberStart; // disk number start 2 bytes 
			hlUInt16 uiInternalFileAttribs; // internal file attributes 2 bytes 
			hlUInt uiExternalFileAttribs; // external file attributes 4 bytes 
			hlUInt uiRelativeOffsetOfLocalHeader; // relative offset of local header 4 bytes 
			// file name (variable size) 
			// extra field (variable size) 
			// file comment (variable size) 
		};

		struct ZIPLocalFileHeader
		{
			hlUInt uiSignature; //local file header signature 4 bytes (0x04034b50) 
			hlUInt16 uiVersionNeededToExtract; // version needed to extract 2 bytes 
			hlUInt16 uiFlags; // general purpose bit flag 2 bytes 
			hlUInt16 uiCompressionMethod; // compression method 2 bytes 
			hlUInt16 uiLastModifiedTime; // last mod file time 2 bytes 
			hlUInt16 uiLastModifiedDate; // last mod file date 2 bytes 
			hlUInt uiCRC32; // crc-32 4 bytes 
			hlUInt uiCompressedSize; // compressed size 4 bytes 
			hlUInt uiUncompressedSize; // uncompressed size 4 bytes 
			hlUInt16 uiFileNameLength; // file name length 2 bytes 
			hlUInt16 uiExtraFieldLength; // extra field length 2 bytes 
			// file name (variable size) 
			// extra field (variable size) 
			// file data (variable size) 
		};

		#pragma pack()

	private:
		static const char *lpAttributeNames[];
		static const char *lpItemAttributeNames[];

		Mapping::CView *pFileHeaderView;
		Mapping::CView *pEndOfCentralDirectoryRecordView;

		const ZIPEndOfCentralDirectoryRecord *pEndOfCentralDirectoryRecord;

	public:
		CZIPFile();
		virtual ~CZIPFile();

		virtual HLPackageType GetType() const;
		virtual const hlChar *GetExtension() const;
		virtual const hlChar *GetDescription() const;

	protected:
		virtual hlBool MapDataStructures();
		virtual hlVoid UnmapDataStructures();

		virtual CDirectoryFolder *CreateRoot();

		virtual hlUInt GetAttributeCountInternal() const;
		virtual const hlChar *GetAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetAttributeInternal(HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlUInt GetItemAttributeCountInternal() const;
		virtual const hlChar *GetItemAttributeNameInternal(HLPackageAttribute eAttribute) const;
		virtual hlBool GetItemAttributeInternal(const CDirectoryItem *pItem, HLPackageAttribute eAttribute, HLAttribute &Attribute) const;

		virtual hlBool GetFileExtractableInternal(const CDirectoryFile *pFile, hlBool &bExtractable) const;
		virtual hlBool GetFileValidationInternal(const CDirectoryFile *pFile, HLValidation &eValidation) const;
		virtual hlBool GetFileSizeInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;
		virtual hlBool GetFileSizeOnDiskInternal(const CDirectoryFile *pFile, hlUInt &uiSize) const;

		virtual hlBool CreateStreamInternal(const CDirectoryFile *pFile, Streams::IStream *&pStream) const;
	};
}
#endif

#endif
