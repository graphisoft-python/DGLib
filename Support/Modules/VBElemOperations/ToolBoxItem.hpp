// *********************************************************************************************************************
// Description:		ToolBox Item for Background Processes
//
// Module:			VBElemOperations
// Namespace:		ToolOperations
// Contact person:	NN
//
// SG compatible
// *********************************************************************************************************************

#ifndef	TOOLBOX_ITEM_HPP
#define	TOOLBOX_ITEM_HPP

#pragma once

// from GSRoot
#include "GSUnID.hpp"

// from VBElements
#include "ElementManagerTypes.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

namespace ToolOperations {

enum ToolTypeIds {		// Type identifiers for non database object tools
	TypeId_ArrowSel = 1,
	TypeId_Marquee  = 2
};

class VB_ELEM_OPERATIONS_DLL_EXPORT ToolBoxItem
{
private:
	//general
	GSType			signature;		// static type identifier from element registry (Tool: regID, ESYM: esym signature)
	EDB::Tool		tool;

	// symbol specific
	GS::UnID		lpfUnID;		// subtype tree node identifier; used to filter the dialog content
	short			isSyType;		// IsSymb, IsLight, IsWind, IsDoor, IsLabel

	EDB::Tool		mainTool;
public:
	ToolBoxItem ();

	ToolBoxItem (const EDB::Tool& 	itemTool,
				 short			  	syType,
				 const GS::UnID&	unID,
				 const EDB::Tool&	mainTool,
				 bool				isArrowSelTool,
				 bool				isMarqueeTool);

	virtual ~ToolBoxItem ();

	GSType 				GetSignature 	() const;
	const EDB::Tool&	GetTool			() const;
	GS::UnID			GetSubtypeUnID	() const;
	void				SetSubtypeUnID	(const GS::UnID& newUnId);

	short				GetIsSyType		() const;
	bool				IsLibpartBased	() const;

	const EDB::Tool&	GetMainTool		() const;

	GSErrCode			Write			(GS::OChannel& oc) const;
	GSErrCode			Read			(GS::IChannel& ic);
};

} // namespace ToolOperations

#endif	//TOOLBOX_ITEM_HPP
