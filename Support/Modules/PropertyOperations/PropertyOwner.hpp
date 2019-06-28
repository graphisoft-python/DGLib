// Contact person :	KiP

#ifndef PROPERTY_OWNER_HPP
#define PROPERTY_OWNER_HPP

#pragma once

// === Includes ========================================================================================================

// from VBAttributes
#include "ADBGeneralDefinitions.hpp"

// from VBElements
#include "PolyRoofTypes.hpp"
#include "FreeShapeTypes.hpp"
#include "OpeningTypes.hpp"

// from PropertyOperations
#include "PropertyOperationsTypes.hpp"
#include "PropertyOperationsExport.hpp"
#include "ComponentBuildingMaterialGetter.hpp"

// === Predeclarations =================================================================================================

namespace ModelCalculations {
	class SurfaceId;
}

namespace VBEO {
	class ModelElemComponentId;
}

namespace Property {
	class PolyRoofElemPartId;
	class FreeShapeElemPartId;
	class PropertyOwnerHashKey;
}

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT PropertyOwner : public GS::SharedObject
{
	DECLARE_ROOT_CLASS_INFO
public:
	virtual ~PropertyOwner ();

	static PropertyOwnerConstPtr			Create							(const EDB::GeneralElemConstRef& generalElem);
	static PropertyOwnerConstPtr			Create							(const EDB::GeneralElemRef& generalElem);
	static PropertyOwnerConstPtr			Create							(const EDB::DefaultElem& defaultElem);
	static PropertyOwnerConstPtr			Create							(EDB::DefaultElem& defaultElem);
	static PropertyOwnerConstPtr			Create							(const VBElem::PolyRoofConstRef& polyRoof, const PolyRoofElemPartId& polyRoofElemPartId);
	static PropertyOwnerConstPtr			Create							(const VBElem::PolyRoofRef& polyRoof, const PolyRoofElemPartId& polyRoofElemPartId);
	static PropertyOwnerConstPtr			Create							(const VBElem::FreeShapeConstRef& freeShape, const FreeShapeElemPartId& freeShapeElemPartId);
	static PropertyOwnerConstPtr			Create							(const VBElem::FreeShapeRef& freeShape, const FreeShapeElemPartId& freeShapeElemPartId);
	static PropertyOwnerConstPtr			CreateFromHoleReplacement		(const VBElem::OpeningConstRef& opening);
	static PropertyOwnerConstPtr			CreateFromHoleReplacement		(const VBElem::OpeningRef& opening);
	static PropertyOwnerConstPtr			CreateFromElemClassId			(const ClassId& classId);
	static PropertyOwnerConstPtr			CreateFromAttribute				(const ADB::GeneralAttributeConstRef& generalAttribute);
	static PropertyOwnerConstPtr			CreateFromAttribute				(const ADB::GeneralAttributeRef& generalAttribute);

	virtual	PropertyOwnerConstPtr			CopyAsConst						() const = 0;
	virtual PropertyOwnerConstPtr			TruncateToElementLevel			() const = 0;
	virtual PropertyOwnerConstPtr			TruncateToComponentLevel		() const = 0;
	virtual PropertyOwnerConstPtr			TruncateToOneLevelHigher		() const = 0;
	virtual	PropertyOwnerConstPtr			ExtendWithComponentId			(const VBEO::ModelElemComponentId& componentId, const ComponentBuildingMaterialGetterConstPtr& componentBuildingMaterialGetter = nullptr) const = 0;
	virtual	PropertyOwnerConstPtr			ExtendWithSurfaceId				(const ModelCalculations::SurfaceId& surfaceId) const = 0;

			bool							operator==						(const PropertyOwner& other) const;
			bool							operator!=						(const PropertyOwner& other) const;

	virtual bool							IsGeneralElem					() const = 0;
	virtual bool							IsDefaultElem					() const = 0;
	virtual	bool							IsAttribute						() const = 0;
	virtual	bool							IsComponent						() const = 0;
	virtual	bool							IsSurface						() const = 0;
	virtual bool							IsPolyRoofElemPart				() const = 0;
	virtual bool							IsFreeShapeElemPart				() const = 0;
	virtual bool							IsHoleReplacement				() const = 0;

	virtual bool							HasClassId						() const = 0;
	virtual	ClassId							GetClassId						() const = 0;

	virtual bool							IsEditable						() const = 0;
	virtual EDB::GeneralElemConstRef		GetGeneralElem					() const = 0;
	virtual EDB::GeneralElemRef				GetEditableGeneralElem			() const = 0;
	virtual const EDB::DefaultElem*			GetDefaultElem					() const = 0;
	virtual EDB::DefaultElem*				GetEditableDefaultElem			() const = 0;
	virtual ADB::GeneralAttributeConstRef	GetGeneralAttribute				() const = 0;
	virtual ADB::GeneralAttributeRef		GetEditableGeneralAttribute		() const = 0;
	virtual	VBEO::ModelElemComponentId		GetComponentId					() const = 0;
	virtual ModelCalculations::SurfaceId	GetSurfaceId					() const = 0;
	virtual	PolyRoofElemPartId				GetPolyRoofElemPartId			() const = 0;
	virtual FreeShapeElemPartId				GetFreeShapeElemPartId			() const = 0;

	virtual	PropertyOwnerConstPtr			GetOneToOneRelatedPropertyOwner () const = 0;

	virtual PropertyOwnerHashKey			GetHashKey						() const = 0;

protected:
	PropertyOwner ();
	virtual PropertyOwner*	Clone () const = 0;
	virtual bool			IsEqual (const PropertyOwner& other) const = 0;
};

}

#endif
