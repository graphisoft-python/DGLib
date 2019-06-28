// *********************************************************************************************************************
// Description:		ToolBox interface
//
// Module:			VBElemOperations
// Namespace:		ToolOperations
// Contact person:	NN
//
// SG compatible
// *********************************************************************************************************************

#ifndef	ITOOLBOX_HPP
#define	ITOOLBOX_HPP

#pragma once

// from GSRoot
#include "Definitions.hpp"
#include "AutoPtr.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

namespace GS
{
	class UnID;
}

namespace EDB {
	class Tool;
}

namespace ToolOperations
{

class VB_ELEM_OPERATIONS_DLL_EXPORT EnableHiddenToolsGuard
{
public:
	virtual ~EnableHiddenToolsGuard ();
};

class VB_ELEM_OPERATIONS_DLL_EXPORT IToolRegistry
{
public:
	enum SearchByLibPartMode {
		SearchByUnID,
		SearchByMainGuid
	};

	virtual ~IToolRegistry ();

	virtual GSType									GetSignature					(const EDB::Tool& tool) const = 0;
	virtual GS::UnID								GetSubtypeUnID					(const EDB::Tool& tool) const = 0;
	virtual short									GetIsSyType						(const EDB::Tool& tool) const = 0;
	virtual bool									IsLibpartBased					(const EDB::Tool& tool) const = 0;

	virtual const EDB::Tool&						GetToolBySignature				(GSType	owner) const = 0;
	virtual const EDB::Tool&						GetToolByLibPartUnID			(const GS::UnID& unID, SearchByLibPartMode searchMode = SearchByUnID) const = 0;

	virtual const EDB::Tool&						GetMainTool						(const EDB::Tool& tool) const = 0;
	virtual GS::AutoPtr<EnableHiddenToolsGuard>		CreateEnableHiddenToolsGuard	() const = 0;
};
	
} // namespace ToolOperations

#endif	//ITOOLBOX_HPP
