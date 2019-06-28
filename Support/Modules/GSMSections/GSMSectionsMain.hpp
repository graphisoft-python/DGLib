// *********************************************************************************************************************
// Description:		LibraryManage common data
//
// Module:			LibraryManager
// Namespace:		LM
// Contact person:	AGY
//
// SG compatible
// *********************************************************************************************************************

#if !defined (GSMSECTIONSMAIN_HPP)
#define GSMSECTIONSMAIN_HPP

#pragma once


#include "GSRoot.hpp"
#include "GSMSectionsExport.h"
#include "ODBReference.hpp"
#include "SymbolFile.hpp"

namespace GDL {
	class ParamList;
}

namespace LM {
	class LibPartId;
	typedef ODB::ConstRef<LibPartId>	LibPartIdConstRef;
	class AncestryHierarchy;
	class LibrarySet;
}

GSMSECTIONS_DLL_EXPORT
GSErr	GSMSECTIONS_CALL	SwapLP_SectByType (GS::PlatformSign	inplatform,
											   UInt32			sectType,
											   GSHandle			syWorkHdl,
											   short			syVersion,
											   short			sectVersion,
											   GS::PlatformSign	toplatform);	// cel platform

GSMSECTIONS_DLL_EXPORT
GSErr	GSMSECTIONS_CALL	GDLUpdateAndSplitSyParHandle (GSHandle	syParHandle,
														  short		syFileVersion,
														  GSHandle*	addParHdl	 = nullptr,
														  GSHandle*	parNameHdl	 = nullptr,
														  GSHandle*	wdFrameHdl	 = nullptr,
														  GSHandle*	wdOrientHdl	 = nullptr);

GSMSECTIONS_DLL_EXPORT
bool	GSMSECTIONS_CALL	CreateCurrentLibPartParamList (const LPF::SymbolFile*	symbolFile,
							   /*should be GDL::ParamList*/const GSHandle&			coreParamList,
							   /*should be GDL::ParamList*/GSHandle*				currentLibPartParamList);


struct GlobalsFilter {
	enum E {
		All,
		ViewDependent,
		ViewIndependent
	};
};

GSMSECTIONS_DLL_EXPORT
GSErrCode	GSMSECTIONS_CALL	WriteGlobalsChecksum (
	GS::OChannel& oc,
	const Int32* globalsBits,
	const GDL::ParamList& globalsValues,
	GlobalsFilter::E filter = GlobalsFilter::All);

#endif
