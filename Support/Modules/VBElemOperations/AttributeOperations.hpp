// *********************************************************************************************************************
// Description:		Attribute operations
//
// Module:			VBElemOperations
// Namespace:		
// Contact person:	KV
//
// SG compatible
// *********************************************************************************************************************

#ifndef	ATTRIBUTEOPERATIONS_HPP
#define	ATTRIBUTEOPERATIONS_HPP

#pragma once

#include "VBElemOperationsExport.hpp"

// from VBAttributes
#include "ADBGeneralDefinitions.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

// from VBAttributes
#include "VBAttributes.hpp"
#include "material.hpp"

// from GSModeler
#include "Model3D/ModelerAttributes.hpp"
#include "Model3D/PolygonAttributes.hpp"

// from TWRoot
#include "LockableObjectSet.hpp"

// from LibraryManager
#include "LibPart.hpp"

class HatchObject;

namespace AttributeOperations
{
	void AddMaterialFromBuildingMaterial (ADB::AttributeSetConstRef attributeSet, short buildMatIndex, GS::HashSet<short>& materials);
	void AddMaterialsFromSyHatch (ADB::AttributeSetConstRef attributeSet, const HatchObject& hatchPtr, GS::HashSet<short>& materials);
	VB_ELEM_OPERATIONS_DLL_EXPORT short GetRealFillTypeIndex (ADB::AttributeSetConstRef attributeSet, short originalFillType);

	class VB_ELEM_OPERATIONS_DLL_EXPORT IMaterialAddInterface {
	protected:
		IMaterialAddInterface ();
		virtual ~IMaterialAddInterface () = 0;
	public:
		virtual bool HasCreateRight (ADB::AttributeContainerConstRef) = 0;
		virtual bool HasLibPartCreateRight () = 0;
		virtual bool NeedToAddClientCreatedFlag () = 0;
		virtual const FTM::GroupID& GetAllImgFilesID () = 0;
		virtual const FTM::TypeID& GetObjectFileID () = 0;
		virtual const LM::LibPart* SearchLibPartDocuName (const GS::UniString& docuName) = 0;
		virtual GS::UniString GetConvertedAttributeSuffix () = 0;
		virtual const LM::LibPart*	FindOrCreateTextureFileInLibrary (GS::UniString&		textureName,
																	  GSPixMapHandle		texturePixMap,
																	  bool					isAllowedToCreateTexture,
																	  bool*					failNoTWRightToCreateAttribute) = 0;
	};

	short VB_ELEM_OPERATIONS_DLL_EXPORT AddModelMaterialToProject (const Modeler::Attributes::Viewer&	attrViewer,
																   const Modeler::PolygonAttributes&	polygonAttributes,
																   GS::HashTable <short, short>*		convertedMaterials,
																   bool*								failNoTWRightToCreateAttribute,
																   ADB::AttributeSetRef					pAttributeSet,
																   IMaterialAddInterface*				materialAddInterface);


} // namespace AttributeOperations

#endif	//ATTRIBUTEOPERATIONS_HPP
