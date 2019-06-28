// *********************************************************************************************************************
// Description:		Attribute accessing interface
//
// Module:			GSModeler2D
// Namespace:		Modeler
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (IATTRIBUTEREADER_HPP)
#define IATTRIBUTEREADER_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------


// from GSRoot
#include	"Definitions.hpp"
#include	"AutoPtr.hpp"
#include	"GSDebug.hpp"

// from GSModeler2D
#include	"GSModeler2DExport.h"
#include	"PenData.hpp"
#include	"BuildingMaterialData.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {
	class UniString;
}

namespace GX {
	namespace Pattern {
		class FillData; 
		class LineData; 
	}
}

namespace Modeler {
	class TextureData;
	class MaterialData;


	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------


	class	GSMODELER2D_DLL_EXPORT	IAttributeReader 
	{
	public:
		virtual GS::UniString									GetFillName (short fillInd) const = 0;
		virtual short											GetFillIndexByName (const GS::UniString& attrName) const = 0; 
		virtual	short											GetFillMaxInd	() const = 0;			//-1 is error!
		virtual short											GetFirstEmptyFill () const = 0;
		virtual GS::AutoPtr <GX::Pattern::FillData>				GetFillData (short fillInd) const = 0;
		
		virtual GS::UniString									GetLineName (short lineInd) const = 0;
		virtual short											GetLineIndexByName (const GS::UniString& attrName) const = 0; 
		virtual	short											GetLineMaxInd	() const = 0;			//-1 is error!
		virtual GS::AutoPtr <GX::Pattern::LineData>				GetLineData (short lineInd) const = 0; 

		virtual	USize											GetNumPen	() const = 0;
		virtual	GS::AutoPtr <Modeler::PenData> 					GetPenData	(short penInd) const = 0;

		virtual	GS::AutoPtr <Modeler::BuildingMaterialData>		GetBuildingMaterialData (short bmatInd) const = 0; 

		virtual bool											ExistsMaterial (short matInd) const = 0;
		virtual GS::UniString									GetMaterialName (short matInd) const = 0;
		virtual short											GetMaterialIndexByName (const GS::UniString& attrName) const = 0; 
		virtual	short											GetMaterialMaxInd	() const = 0;			//-1 is error!
		virtual	GS::AutoPtr <Modeler::MaterialData> 			GetMaterialData	(short matInd, short texPictIndex = -1) const = 0;
		virtual GS::AutoPtr <Modeler::TextureData>				GetTextureData (short matInd, short texPictIndex) const = 0;

		// The AttributeReader should handle sharing the data between the cloned instances (i.e. the data members should be Refs)
		virtual GS::AutoPtr<IAttributeReader>					Clone () const = 0;

		virtual ~IAttributeReader (void);
	};


	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Modeler

#endif	// IATTRIBUTEREADER_HPP
