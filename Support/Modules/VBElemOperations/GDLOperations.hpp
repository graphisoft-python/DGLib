// *********************************************************************************************************************
// Description:		GDL operations
//
// Module:			VBElemOperations
// Namespace:		
// Contact person:	KV
//
// SG compatible
// *********************************************************************************************************************

#ifndef	GDLBASEDELEMOPERATIONS_HPP
#define	GDLBASEDELEMOPERATIONS_HPP

#pragma once

// from GSRoot
#include "Definitions.hpp"

// from InputOutput
#include "Location.hpp"

// from GSUtils
#include "GSUserData.hpp"

// from GDL
#include "GDL.h"

// from VBAttributes
#include "ADBGeneralDefinitions.hpp"

// from GSModeler
#include "AttributeReader.hpp"

// from VBElements
#include "EDBGeneralDefinitions.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

namespace GDL { class IFileServices; }

namespace FTM { class GeneralID; }

namespace LM {
	class LibPart;
	class LibrarySet;
}

namespace ModelerAPI {
	class PixelMapCodec;
}


namespace LibCtrl {
	enum MigrationDirection {
		NotMigration,
		ForwardMigration,
		BackwardMigration
	};
	enum ParamListMode { 
		ParamListFixMode,
		ParamListEditingMode
	};
}

namespace GDLOperations {
	enum RunVLScriptMode {
		RVLMRunUntilNoChange,
		RVLMRunOnlyOnce		
	};

	enum ForceVLScriptMode {
		FVLMForceRunUntilNoChange,
		FVLMForceRunOnlyOnce,
		FVLMDontForce
	};
}

struct VB_ELEM_OPERATIONS_DLL_EXPORT VLData {
	bool					wasSetPars;
	bool					disposeAddPars;
	GSHandle				gdlGlobHdl;		// not owned by SymbUI!
	GSHandle				addParHdl;
	LibCtrl::ParamListMode	paramListMode;
	bool					*addParsCh;
	IO::Location			fileLoc;
	const LM::LibPart*		libPart;
	GSHandle				textHdl;
	GDLParamVLComponent		vlComponent;
	GDL::IFileServices*		fileServices;
};

namespace GDLOperations
{

enum DocumentViewDirection {
	DVDUnset,
	DVDVertical_Only,
	DVDHorizontal_Only,
	DVDFree,
	DVDNone
};

// for IESUtil.hpp (through ACAPLIB.c)
class DocumentViewDirectionWrapper {
	const DocumentViewDirection*	m_documentViewDirection;
public:
	DocumentViewDirectionWrapper (const DocumentViewDirection* documentViewDirection) : m_documentViewDirection (documentViewDirection) {}
	operator const DocumentViewDirection* () const { return m_documentViewDirection; }
};

struct VB_ELEM_OPERATIONS_DLL_EXPORT ScriptRunningEnvironment
{
	ScriptRunningEnvironment (ADB::AttributeSetConstRef attrSet, GSPtr masterValListArr);
	virtual ~ScriptRunningEnvironment ();

	// Reference to AC globals
	GSPtr				masterValListArr;

	GSUserData			gsUserData;

	// Other environment settings
	AttributeReader		attributeReader;
	GdlGenProcs			gdgenenv;
};

GSErr VB_ELEM_OPERATIONS_DLL_EXPORT VLBuild (
	VLData **vl,
	GDL::IFileServices* fileServices,
	GDL::IFileRef* fileRef,
	bool *parmsModified,
	bool runVLScript,
	EDB::GeneralElemConstRef* pElem,
	ScriptRunningEnvironment& environment,
	ForceVLScriptMode forceVLScriptMode
);

GSErr VB_ELEM_OPERATIONS_DLL_EXPORT DoValueScript (
	VLData **vl,
	GDL::IFileRef* fileRef,
	bool *parChanged,
	EDB::GeneralElemConstRef* pElem,
	ScriptRunningEnvironment& environment,
	ForceVLScriptMode forceVLScriptMode
);

GSErr VB_ELEM_OPERATIONS_DLL_EXPORT DoMigrationScript (
	VLData **vl,
	GDL::IFileRef* fileRef,
	EDB::GeneralElemConstRef* pElem,
	LibCtrl::MigrationDirection migrationDirection,
	ScriptRunningEnvironment& environment,
	GS::Guid* aGuidToMigrate = nullptr,
	GSHandle aVariablesFromOldAddPar = nullptr,
	GS::Array<GS::UniString>* migrationWarnings = nullptr
);

GSErr VB_ELEM_OPERATIONS_DLL_EXPORT DoParameterScript ( 
	VLData **vl,
	GDL::IFileRef* fileRef,
	EDB::GeneralElemConstRef* pElem,
	ScriptRunningEnvironment& environment
);

RunVLScriptMode	VB_ELEM_OPERATIONS_DLL_EXPORT		GetRunVLScriptMode	(	const LM::LibPart&			libPart);

bool	VB_ELEM_OPERATIONS_DLL_EXPORT		IsBackgroundImage	(	const LM::LibrarySet*		libSet, 
																	const LM::LibPart*			libPart,	
																	const FTM::GeneralID&		allImgFilesID, 
																	ModelerAPI::PixelMapCodec*	externalCodec = nullptr);
bool	VB_ELEM_OPERATIONS_DLL_EXPORT		IsTextureImage		(	const LM::LibrarySet*		libSet, 
																	const LM::LibPart*			libPart, 
																	const FTM::GeneralID&		allImgFilesID, 
																	ModelerAPI::PixelMapCodec*	externalCodec = nullptr);
bool	VB_ELEM_OPERATIONS_DLL_EXPORT		IsUtilityImage		(	const LM::LibrarySet*		libSet, 
																	const LM::LibPart*			libPart, 
																	const FTM::GeneralID&		allImgFilesID, 
																	ModelerAPI::PixelMapCodec*	externalCodec = nullptr);
bool	VB_ELEM_OPERATIONS_DLL_EXPORT		IsHDRIImage			(	const LM::LibrarySet*		libSet, 
																	const LM::LibPart*			libPart, 
																	const FTM::GeneralID&		allImgFilesID, 
																	ModelerAPI::PixelMapCodec*	externalCodec = nullptr);
bool	VB_ELEM_OPERATIONS_DLL_EXPORT		IsImage				(	const LM::LibPart*			libPart,
																	const FTM::GeneralID&		allImgFilesID);
bool	VB_ELEM_OPERATIONS_DLL_EXPORT		IsExternalImage		(	const LM::LibPart*			libPart, 
																	ModelerAPI::PixelMapCodec*	externalCodec = nullptr);
bool	VB_ELEM_OPERATIONS_DLL_EXPORT		IsOtherImage		(	const LM::LibrarySet*		libSet, 
																	const LM::LibPart*			libPart, 
																	const FTM::GeneralID&		allImgFilesID, 
																	ModelerAPI::PixelMapCodec*	externalCodec = nullptr);

} // namespace GDLOperations

#endif	//GDLBASEDELEMOPERATIONS_HPP
