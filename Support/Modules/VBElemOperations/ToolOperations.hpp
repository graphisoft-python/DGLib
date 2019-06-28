// *********************************************************************************************************************
// Description:		Tool operations
//
// Module:			VBElemOperations
// Namespace:		ToolOperations
// Contact person:	NN
//
// SG compatible
// *********************************************************************************************************************

#ifndef	TOOL_OPERATIONS_HPP
#define	TOOL_OPERATIONS_HPP

#pragma once

// from GSRoot
#include "GSUnID.hpp"
#include "SkipMap.hpp"

// from VBElements
#include "EDBGeneralDefinitions.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

namespace GS {
	class UnID;
}

namespace EDB {
	class Tool;
}

namespace LM {
	class LibrarySet;
	class LibPart;
}

class LibPartHandlerRegistry;

namespace CAT {
	class ExtendedElemTypeIdentifier;
}

namespace ToolOperations {
	class IToolRegistry;
}

namespace ToolOperations {

VB_ELEM_OPERATIONS_DLL_EXPORT EDB::Tool GetPrimaryMode				 (const LM::LibrarySet* 			librarySet,
																	  const LibPartHandlerRegistry* 	libPartHandlerRegistry,
																	  const ToolOperations::IToolRegistry&	toolRegistry,
																	  EDB::GeneralElemConstRef 			pElem);

VB_ELEM_OPERATIONS_DLL_EXPORT EDB::Tool	GetAncestorTool				 (const LM::LibrarySet*				librarySet,
																	  const LibPartHandlerRegistry*		libPartHandlerRegistry,
																	  const ToolOperations::IToolRegistry&	toolRegistry,
																	  const LM::LibPart*				libPart,
																	  const GS::UnID&					creator);

VB_ELEM_OPERATIONS_DLL_EXPORT bool		GetPseudoCreator			 (const LM::LibrarySet*				librarySet,
																	  const LibPartHandlerRegistry*		libPartHandlerRegistry,
																	  const ToolOperations::IToolRegistry&	toolRegistry,
																	  const LM::LibPart*				libPart,
																	  const GS::UnID&					origCreatorUnID,
																	  GS::UnID*							pseudo,
																	  bool								assert = true);

VB_ELEM_OPERATIONS_DLL_EXPORT GS::UnID GetImmediateRegisteredCreator (const LM::LibrarySet*				librarySet,
																	  const ToolOperations::IToolRegistry&	toolRegistry,
																	  const LM::LibPart*				libPart);

VB_ELEM_OPERATIONS_DLL_EXPORT GS::UnID GetCurrRootID				 ();

VB_ELEM_OPERATIONS_DLL_EXPORT CAT::ExtendedElemTypeIdentifier GetExtendedElemTypeIdentifier (GS::GSType						 type,
																							 const ToolOperations::IToolRegistry& toolRegistry);


struct VBElemOperationInitParams
{
	// Tools that used common libpart subtype before, but are separated
	// (might still use old, common-type libparts)
	// Example:
	//	Main GUID of WindowDoorSkylightMarkerID,
	//	UnID-s of the derived types (WindowMarkerID, DoorMarkerID, SkylightMarkerID)
	struct SubTypeSubstitute
	{
		GS::UnID			parentSubTypeUnID;
		GS::Array<GS::UnID>	derivedSubTypeUnIDs;
	};
	GS::Array<SubTypeSubstitute> substituteSubTypes;
};
VB_ELEM_OPERATIONS_DLL_EXPORT void Init (const VBElemOperationInitParams&);

} // namespace ToolOperations

#endif	//TOOL_OPERATIONS_HPP
