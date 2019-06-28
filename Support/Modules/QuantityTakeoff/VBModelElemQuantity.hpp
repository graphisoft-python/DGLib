// Contact person : KiP

#ifndef VBMODELELEM_QUANTITY_HPP
#define VBMODELELEM_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElemOperations
#include "ModelElemComponentSurfaceId.hpp"

// from QuantityTakeoff
#include "QuantityTakeoffTypes.hpp"
#include "QuantityTakeoffExport.hpp"
#include "QuantityModel.hpp"

// =====================================================================================================================

namespace QT {

class VBModelElemQuantityCalculator
{
protected:
	VBModelElemQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~VBModelElemQuantityCalculator ();

	Modeler::ConstElemPtr			GetElemPtr			(const CONV2LISTREC& listParams) const;
	Modeler::ConstAttributesPtr		GetAttributesPtr	() const;

	// ... volume and surface area .....................................................................................

	double		GetVolume			(const CONV2LISTREC& listParams, const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;
	double		GetSurfaceArea		(const CONV2LISTREC& listParams, const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;
	double		GetSurfaceAreaOf	(Int32 surfaceType, const CONV2LISTREC& listParams, const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;
	double		GetSurfaceAreaOf	(const GS::Array<Int32>& surfaceTypes, const CONV2LISTREC& listParams, const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;

	// ... components ..................................................................................................

	virtual VBEO::ModelElemComponentId			GetComponentId											(const Modeler::MeshBody& body) const = 0;
	short										GetComponentIndexFromBodyUserData						(const Modeler::MeshBody& body) const;
	GS::HashSet<VBEO::ModelElemComponentId>		GetComponentsOfBasicElem								(const GS::Optional<VBEO::ModelElemComponentId::SubElementId>& subElemId = GS::NoValue) const;
	GS::HashSet<VBEO::ModelElemComponentId>		GetComponentsFromElemStructure							() const;
	GS::HashSet<VBEO::ModelElemComponentId>		GetComponentsFrom3DModel								(const CONV2LISTREC& listParams = CreateListParams (DetailedFinalModel), const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;
	short										GetComponentBuildingMaterialIndexFromElemStructure		(const VBEO::ModelElemComponentId& componentId) const;
	short										GetComponentBuildingMaterialIndexFrom3DModel			(const VBEO::ModelElemComponentId& componentId, const CONV2LISTREC& listParams = CreateListParams (DetailedFinalModel), const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;
	double										GetComponentVolume										(const VBEO::ModelElemComponentId& componentId, const CONV2LISTREC& listParams = CreateListParams (DetailedFinalModel), const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;
	double										GetComponentVolumeOfGDLBasedElem						(const VBEO::ModelElemComponentId& componentId, const CONV2LISTREC& listParams = CreateListParams (DetailedFinalModel), const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;
	bool										HasComponentProjectedArea								(const VBEO::ModelElemComponentId& componentId) const;
	double										GetComponentProjectedArea								(const VBEO::ModelElemComponentId& componentId, const CONV2LISTREC& listParams = CreateListParams (DetailedFinalModel), const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;

	// ... surfaces ....................................................................................................

	GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfacesFrom3DModel		(const CONV2LISTREC& listParams = CreateListParams (NormalFinalModel)) const;
	GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfacesFrom3DModel		(const CONV2LISTREC& listParams = CreateListParams (DetailedFinalModel), const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr, const ModelCalculations::IPolygonFilter* polygonFilter = nullptr) const;
	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId, const CONV2LISTREC& listParams = CreateListParams (DetailedFinalModel), const ModelCalculations::IMeshBodyFilter* bodyFilter = nullptr) const;

	// ... subelems ....................................................................................................

	virtual void									EnumerateModelElemSubElements					(const std::function<void (const VBElem::ModelElementConstRef&)>& processor) const;
	VBElem::ModelElementConstRef					GetModelElemSubElement							(const GS::Guid& subElementGuid) const;
	GS::HashSet<VBEO::ModelElemComponentId>			GetComponentsOfCompoundElem						() const;
	UIndex											GetComponentBuildingMaterialIdxInCompoundElem	(const VBEO::ModelElemComponentId& componentId) const;
	double											GetComponentVolumeInCompoundElem				(const VBEO::ModelElemComponentId& componentId) const;
	double											GetComponentProjectedAreaInCompoundElem			(const VBEO::ModelElemComponentId& componentId) const;
	GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfacesOfCompoundElem				() const;
	GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfacesOfCompoundElem				() const;
	double											GetExposedSurfaceAreaInCompondElem				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const;

	// ... other .......................................................................................................

	Modeler::ConstElemPtr							GetHoleElem () const;

	void											CalcHoleCondParams (double*							volume_cond,
																		double*							surface1_cond,
																		double*							surface2_cond,
																		double*							lengthRed1_cond,
																		double*							lengthRed2_cond,
																		double							minHoleVolume,
																		bool							volReductionFlag,
																		double							minHoleSurface,
																		bool							surfReductionFlag,
																		double							minHoleLength,
																		bool							lenReductionFlag,
																		GS::HashTable<QT_ElemPartId, QT_ElementQuantity>* quantitiesTable /*= nullptr*/,
																		const GS::Array< GS::Pair<WallPart,VBElem::RoomConstRef> >* wallPartZoneList /*= nullptr*/) const;

	virtual CONV2LISTREC							GetWithHoleListParams ()								const { DBBREAK (); throw GS::Exception ("Not implemented!"); }
	virtual CONV2LISTREC							GetWithoutHoleListParams ()								const { DBBREAK (); throw GS::Exception ("Not implemented!"); }

	double											GetHeightAlong3DDirection (
																		const Vector3D& direction,
																		const CalculationModelType cmt)		const;

	bool IsPBCConversion () const;

	QuantityModelConstPtr quantityModel;
	VBElem::ModelElementConstRef vbElem;

	void EnumerateBodies (const CONV2LISTREC& listParams, const ModelCalculations::IMeshBodyFilter* bodyFilter, const std::function<void (const ModelCalculations::BodyIterator&)>& processor) const;

private:	
	GS::Ref<Property::IModelElementQuantityCalculator>	GetModelElemQuantityCalculator	(const VBElem::ModelElementConstRef& modelElem) const;	
	virtual	ModelCalculations::ProjectionSurfaceRef		GetProjectionSurface			(const VBEO::ModelElemComponentId& componentId) const;
	virtual	IPolygonSurfaceType*						GetPolygonSurfaceType			() const;

	short GetBodyBuildingMaterialIdxFromUserData (const Modeler::MeshBody& body) const;

	VBModelElemQuantityCalculator ();	// prevent to get nullptr in quantityModel
};

}

#endif