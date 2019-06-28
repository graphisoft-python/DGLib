#if ! defined NOT_IMPLEMENTED_ATTRIBUTE_READER_HPP
#define NOT_IMPLEMENTED_ATTRIBUTE_READER_HPP


#include	"IAttributeReader.hpp"

// from Graphics
#include	"FillData.hpp"
#include	"LineData.hpp"

// from GSModeler2D
#include	"PenData.hpp"
#include	"BuildingMaterialData.hpp"
#include	"TextureData.hpp"

// from Model3D
#include	"Model3D/MaterialData.hpp"


namespace Modeler {


class MODEL3D_DLL_EXPORT NotImplementedAttributeReader : public IAttributeReader 
{
public:
	virtual GS::UniString									GetFillName (short /*fillInd*/) const override { DBBREAK_STR ("Not implemented!"); return ""; }
	virtual short											GetFillIndexByName (const GS::UniString& /*attrName*/) const override { DBBREAK_STR ("Not implemented!"); return -1; } 
	virtual	short											GetFillMaxInd	() const override { DBBREAK_STR ("Not implemented!"); return -1; }
	virtual short											GetFirstEmptyFill () const override { DBBREAK_STR ("Not implemented!"); return -1; }
	virtual GS::AutoPtr <GX::Pattern::FillData>				GetFillData (short /*fillInd*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }

	virtual GS::UniString									GetLineName (short /*lineInd*/) const override { DBBREAK_STR ("Not implemented!"); return ""; }
	virtual short											GetLineIndexByName (const GS::UniString& /*attrName*/) const override { DBBREAK_STR ("Not implemented!"); return -1; } 
	virtual	short											GetLineMaxInd	() const override { DBBREAK_STR ("Not implemented!"); return -1; }
	virtual GS::AutoPtr <GX::Pattern::LineData>				GetLineData (short /*lineInd*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; } 

	virtual	USize											GetNumPen	() const override { DBBREAK_STR ("Not implemented!"); return 0; }
	virtual	GS::AutoPtr <Modeler::PenData> 					GetPenData	(short /*penInd*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }

	virtual	GS::AutoPtr <Modeler::BuildingMaterialData>		GetBuildingMaterialData (short /*bmatInd*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; } 

	virtual bool											ExistsMaterial (short /*matInd*/) const override { DBBREAK_STR ("Not implemented!"); return false; }
	virtual GS::UniString									GetMaterialName (short /*matInd*/) const override { DBBREAK_STR ("Not implemented!"); return ""; }
	virtual short											GetMaterialIndexByName (const GS::UniString& /*attrName*/) const override { DBBREAK_STR ("Not implemented!"); return -1; } 
	virtual	short											GetMaterialMaxInd	() const override { DBBREAK_STR ("Not implemented!"); return -1; }
	virtual	GS::AutoPtr <Modeler::MaterialData> 			GetMaterialData	(short /*matInd*/, short /*texPictIndex = -1*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }
	virtual GS::AutoPtr <Modeler::TextureData>				GetTextureData (short /*matInd*/, short /*texPictIndex*/) const override { DBBREAK_STR ("Not implemented!"); return nullptr; }

	virtual GS::AutoPtr<IAttributeReader>					Clone () const override { return GS::AutoPtr<IAttributeReader> {new NotImplementedAttributeReader}; }

	virtual ~NotImplementedAttributeReader (void);
};


}	// namespace Modeler


#endif // NOT_IMPLEMENTED_ATTRIBUTE_READER_HPP

