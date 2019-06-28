// *********************************************************************************************************************
// Description:		Copied ToolBox for Background Processes
//
// Module:			VBElemOperations
// Namespace:		ToolOperations
// Contact person:	NN
//
// SG compatible
// *********************************************************************************************************************

#ifndef	COPIED_TOOLBOX_HPP
#define	COPIED_TOOLBOX_HPP

#pragma once

// from GSRoot
#include "Array.hpp"
#include "Md5.hpp"

// from VBElemOperations
#include "IToolRegistry.hpp"
#include "ToolBoxItem.hpp"
#include "VBElemOperationsExport.hpp"


namespace ToolOperations {

class VB_ELEM_OPERATIONS_DLL_EXPORT ToolRegistryCopy : public IToolRegistry
{
private:
	GS::Array<ToolBoxItem>	items;
	MD5::FingerPrint		checksum;

public:
	ToolRegistryCopy ();
// 	ToolRegistryCopy (const ToolRegistryCopy& source);
// 	ToolRegistryCopy (const ToolRegistryCopy&& source);
	ToolRegistryCopy (GS::Array<ToolBoxItem>& registryItems);

// 	ToolRegistryCopy& operator= (const ToolRegistryCopy& source);
// 	ToolRegistryCopy& operator= (const ToolRegistryCopy&& source);

	virtual ~ToolRegistryCopy ();

	const MD5::FingerPrint&							GetChecksum						() const;

	virtual GSType									GetSignature					(const EDB::Tool& tool) const override;
	virtual GS::UnID								GetSubtypeUnID					(const EDB::Tool& tool) const override;
	virtual short									GetIsSyType						(const EDB::Tool& tool) const override;
	virtual bool									IsLibpartBased					(const EDB::Tool& tool) const override;

	virtual const EDB::Tool&						GetToolBySignature				(GSType	owner) const override;
	virtual const EDB::Tool&						GetToolByLibPartUnID			(const GS::UnID& unID, SearchByLibPartMode searchMode = SearchByUnID) const override;

	virtual const EDB::Tool&						GetMainTool						(const EDB::Tool& tool) const override;
	virtual GS::AutoPtr<EnableHiddenToolsGuard>		CreateEnableHiddenToolsGuard	() const override;
private:
	MD5::FingerPrint								GenerateChecksum		();
	UInt32											GetIndexByTool			(const EDB::Tool& tool) const;
};

} // namespace ToolOperations

#endif	//COPIED_TOOLBOX_HPP
