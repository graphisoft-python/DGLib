// *****************************************************************************
// TypeIDs for the included attribute types
// AttributeManager, platform-independent
//
// Namespaces:        Contact person:
//							JG
//
// [SG compatible]
// *****************************************************************************

#if !defined (ATTRIBUTETYPEIDS_HPP)
#define ATTRIBUTETYPEIDS_HPP

#pragma once

//============================ TypeIds ====================================

// current type ids
enum TypeIds {
	UnknownID				= 0,
	TypeId_City				= 'CIT2',
	TypeId_CompWall			= 'CWA2',
	TypeId_DimStand			= 'STN2',
	TypeId_Fill				= 'FIL3',
	TypeId_Layer			= 'LAY2',
	TypeId_LayerComb		= 'LCO2',
	TypeId_LineType			= 'LIN2',
	TypeId_MarkupStyle		= 'MSTY',
	TypeId_Material			= 'MAT2',
	TypeId_Pen				= 'PEN2',
	TypeId_RoomCat			= 'RMC2',
	TypeId_Profile			= 'PROF',
	TypeId_PenTable			= 'PTBL',
	TypeId_MEPSystem		= 'MEPS',
	TypeId_OperationProfile	= 'EDOP',
	TypeId_GraphicOverride	= 'GOVR',
	TypeId_BuildingMaterial	= 'BMAT'
};

#endif
