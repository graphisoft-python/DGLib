#if !defined (GXIMAGEBASE_H)
#define GXIMAGEBASE_H

#pragma once

#include	"Location.hpp"
#include	"File.hpp"
#include	"FileTypeManager.hpp"

#include	"Pair.hpp"

#include	"GSPix.h"

#include	"GXImageBaseExport.hpp"

// =============================================================================
//
// Image I/O
//
// =============================================================================

namespace GX {

class ImageSaveOptions;

class GXIMAGEBASE_DLL_EXPORT ImageBase
{
public:

	static GSErrCode GSCALL	Init ();
	static GSErrCode GSCALL	Exit ();

	static GSErrCode GSCALL	GetGroupID (FTM::GroupID* groupId);

	static GSErrCode GSCALL	GetFileInfo (	const IO::Location&		fileLoc,
											Int32*					hSize,
											Int32*					vSize,
											Int32*					hRes,	// dpi
											Int32*					vRes,	// dpi
											Int32*					pixelBitNum);

	static GSErrCode GSCALL	ReadFile (	const IO::Location&		fileLoc,
										GSPixMapHandle*			pixHdl,
										GSPixelType				outputFormat = GSPT_Unknown);

	static GSErrCode GSCALL	WriteFile (	const IO::Location&		fileLoc,
										const FTM::TypeID&		fileType,
										GSPixMapHandle			pixHdl,
										const ImageSaveOptions*	saveOptions = nullptr);

	static GSErrCode GSCALL	GetInfo (	GSHandle				imageHandle,
										Int32*					hSize,
										Int32*					vSize,
										Int32*					hRes,	// dpi
										Int32*					vRes,	// dpi
										Int32*					pixelBitNum,
										const FTM::TypeID&		inputFormat = FTM::UnknownType);

	static GSErrCode GSCALL	GetType (	GSHandle				imageHandle,
										FTM::TypeID*			imageType);

	static GSErrCode GSCALL	Convert (	GSHandle	sourceImage,
										const char* sourceTypeMime,
										GSHandle*	targetImage,
										const char* targetTypeMime,
										short		quality);

	static GSErrCode GSCALL	ConvertToPixMap (	GSHandle				imageHandle,
												GSPixMapHandle*			pixHdl,
												const FTM::TypeID&		inputFormat = FTM::UnknownType,
												GSPixelType				outputFormat = GSPT_Unknown);

	static GSErrCode GSCALL	ConvertToPixMapArray (	GSHandle										imageHandle,
													GS::Array<GS::Pair<GSPixMapHandle, double>>*	pixHdlArray,
													const FTM::TypeID&								inputFormat = FTM::UnknownType,
													GSPixelType										outputFormat = GSPT_Unknown);

	static GSErrCode GSCALL	ConvertFromPixMap (	GSPixMapHandle			pixmapHandle,
												const FTM::TypeID&		targetFormat,
												GSHandle*				target,
												const ImageSaveOptions*	saveOptions = nullptr);

	static bool GSCALL		SupportsSettings (const FTM::TypeID& targetFormat);


	static bool GSCALL		IsPreferredStorageType (const FTM::TypeID&		fileTypeID,
													FTM::TypeID*			preferredFType = nullptr);

	static GSErrCode GSCALL	ModifyFileTypeParameters (	const FTM::TypeID&		imageType,
														const char*				description,
														const char*				fileExt,
														UInt32					macType);

	static	void* GSCALL	CountComponents (	void*			componentinst,
												bool			importers,
												char*			description,
												char*			fileExt,
												UInt32*			creator,
												UInt32*			macType,
												GSHandle*		mimeTypeList);

};

}

#endif

