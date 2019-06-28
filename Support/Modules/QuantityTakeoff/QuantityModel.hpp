// Contact person : KiP
// Description : Class to manage model generation and cache for quantity calculations.

#ifndef QUANTITYMODEL_HPP
#define QUANTITYMODEL_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "PropertyEvaluationEnvironmentData.hpp"

// from GSModeler
#include "ModelPolygonFilter.hpp"

// from QuantityTakeoff
#include "QuantityTakeoffTypes.hpp"
#include "QuantityTakeoffExport.hpp"
#include "QuantityCalculator.hpp"
#include "QuantityTakeoffCallbacks.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT QuantityModel : public GS::SharedObject
{
public:
	// ... Type definitions ............................................................................................

	enum ModelPolygonFilterType
	{
		MPF_Unknown			= 0,
		MPF_ExposedSurface	= 1
	};

	// ... Accessors ...................................................................................................

	Modeler::ConstElemPtr							GetElemPtr (const GS::Guid& elemGuid, const CONV2LISTREC& listParams) const;
	Modeler::ConstElemPtr							GetElemPtr (const VBElem::ModelElementConstRef& vbElem, const CONV2LISTREC& listParams) const;

	ModelCalculations::ModelPolygonFilterConstPtr	GetModelPolygonFilter (ModelPolygonFilterType modelPolygonFilterType) const;

	GS::ProcessControl&								GetProcessControl		(void) const;
	const LM::LibrarySet*							GetLibrarySet			(void) const;
	const CalculationRules*							GetCalculationRules		(void) const;
	const EDB::FloorStructureConstRef&				GetFloorStructure		(void) const;
	EDB::ProjectConstRef							GetConstProject			(void) const;
	Modeler::AttributesPtr							GetAttributesPtr		(void) const;
	const VBTo3D::Environment*						GetConv3DEnvir			(void) const;
	const VBTo3D::PhasingEnv&						GetPhasing				(void) const;
	const JCTN::JunctionParamsPtr&					GetJunctionParams		(void) const;
	const VBCalculations::CurrentStoryCutLevels&	GetStoryCutLevels		(void) const;
	const VBCalculations::GDLGlobalCalcEnvir&		GetGDLGlobalCalcEnvir	(void) const;

	const GS::HashSet<GS::Guid>&					GetCoverElemGuids		(void) const;

	const GS::Ref<QT::QTCallBackInterface>&			GetCallBacks			(void) const;

	template<class ListingElemType>
	void											PushListingElems (const GS::PagedArray<ListingElemType>&	listingElems);
	void											PopListingElems ();

	GS::Ref<QT::BeamQuantityCalculator>					GetBeamQuantityCalculator				(const VBElem::BeamConstRef& beam) const;
	GS::Ref<QT::CeilQuantityCalculator>					GetCeilQuantityCalculator				(const VBElem::CeilConstRef& ceil) const;
	GS::Ref<QT::ColumnQuantityCalculator>				GetColumnQuantityCalculator				(const VBElem::ColumnConstRef& column) const;
	GS::Ref<QT::CurtainWallQuantityCalculator>			GetCurtainWallQuantityCalculator		(const VBElem::CurtainWallConstRef& curtainWall) const;
	GS::Ref<QT::CWAccessoryQuantityCalculator>			GetCWAccessoryQuantityCalculator		(const VBElem::CWAccessoryConstRef& cwAccessory) const;
	GS::Ref<QT::CWFrameQuantityCalculator>				GetCWFrameQuantityCalculator			(const VBElem::CWFrameConstRef& cwFrame) const;
	GS::Ref<QT::CWJunctionQuantityCalculator>			GetCWJunctionQuantityCalculator			(const VBElem::CWJunctionConstRef& cwJunction) const;
	GS::Ref<QT::CWPanelQuantityCalculator>				GetCWPanelQuantityCalculator			(const VBElem::CWPanelConstRef& cwPanel) const;
	GS::Ref<QT::CWSegmentQuantityCalculator>			GetCWSegmentQuantityCalculator			(const VBElem::CWSegmentConstRef& cwSegment) const;
	GS::Ref<QT::FreeShapeQuantityCalculator>			GetFreeShapeQuantityCalculator			(const VBElem::FreeShapeConstRef& freeShape) const;
	GS::Ref<QT::GDLObjectQuantityCalculator>			GetGDLObjectQuantityCalculator			(const VBElem::GDLObjectConstRef& gdlObject) const;
	GS::Ref<QT::MeshQuantityCalculator>					GetMeshQuantityCalculator				(const VBElem::MeshConstRef& mesh) const;
	GS::Ref<QT::PlaneRoofQuantityCalculator>			GetPlaneRoofQuantityCalculator			(const VBElem::PlaneRoofConstRef& planeRoof) const;
	GS::Ref<QT::PolyRoofQuantityCalculator>				GetPolyRoofQuantityCalculator			(const VBElem::PolyRoofConstRef& polyRoof) const;
	GS::Ref<QT::PolyRoofElemPartQuantityCalculator>		GetPolyRoofElemPartQuantityCalculator	(const VBElem::PolyRoofConstRef& polyRoof, const Property::PolyRoofElemPartId& elemPartId) const;
	GS::Ref<QT::RailBaseQuantityCalculator>				GetRailBaseQuantityCalculator			(const VBElem::RailBaseConstRef& railBase) const;
	GS::Ref<QT::RailBaseEndQuantityCalculator>			GetRailBaseEndQuantityCalculator		(const VBElem::RailBaseEndConstRef& railBaseEnd) const;
	GS::Ref<QT::RailBaseConnectionQuantityCalculator>	GetRailBaseConnectionQuantityCalculator	(const VBElem::RailBaseConnectionConstRef& railBaseConnection) const;
	GS::Ref<QT::RailingQuantityCalculator>				GetRailingQuantityCalculator			(const VBElem::RailingConstRef& railing) const;
	GS::Ref<QT::RailingPanelQuantityCalculator>			GetRailingPanelQuantityCalculator		(const VBElem::RailingPanelConstRef& railingPanel) const;
	GS::Ref<QT::RailingPostBaseQuantityCalculator>		GetRailingPostBaseQuantityCalculator	(const VBElem::RailingPostBaseConstRef& railingPostBase) const;
	GS::Ref<QT::RailingSegmentQuantityCalculator>		GetRailingSegmentQuantityCalculator		(const VBElem::RailingSegmentConstRef& railingSegment) const;
	GS::Ref<QT::RiserQuantityCalculator>				GetRiserQuantityCalculator				(const VBElem::RiserConstRef& riser) const;
	GS::Ref<QT::RoofQuantityCalculator>					GetRoofQuantityCalculator				(const VBElem::RoofConstRef& roof) const;
	GS::Ref<QT::RoomQuantityCalculator>					GetRoomQuantityCalculator				(const VBElem::RoomConstRef& room) const;
	GS::Ref<QT::ShellQuantityCalculator>				GetShellQuantityCalculator				(const VBElem::ShellConstRef& shell) const;
	GS::Ref<QT::SkylightQuantityCalculator>				GetSkylightQuantityCalculator			(const VBElem::SkylightConstRef& skylight) const;
	GS::Ref<QT::StairQuantityCalculator>				GetStairQuantityCalculator				(const VBElem::StairConstRef& stair) const;
	GS::Ref<QT::StairStructureQuantityCalculator>		GetStairStructureQuantityCalculator		(const VBElem::StairStructureConstRef& stairStructure) const;
	GS::Ref<QT::TreadQuantityCalculator>				GetTreadQuantityCalculator				(const VBElem::TreadConstRef& tread) const;
	GS::Ref<QT::WallQuantityCalculator>					GetWallQuantityCalculator				(const VBElem::WallConstRef& wall, const RoomPart* roomParts = nullptr, const ZoneLimitData* limitData = nullptr, double minSurf = 0.0) const;
	GS::Ref<QT::WallOpeningQuantityCalculator>			GetWallOpeningQuantityCalculator		(const VBElem::WallOpeningConstRef& wallOpening) const;

	void GetWPoly (VBElem::WallConstRef								pWall,
				   Geometry::IrregularPolygon2D*					outWPoly,
				   Int32											floor,
				   VBCalculations::WallComputingEnvir* const		wce = nullptr,
				   VBCalculations::WallBeamConnectionEnvir* const	wbce = nullptr) const;

	Modeler::ConstElemPtr GetHoleElem (const Modeler::ConstElemPtr& withoutHoleElem, const Modeler::ConstElemPtr& withHoleElem) const;

protected:
	// ... Constructor and destructor ..................................................................................

	QuantityModel (GS::ProcessControl&							processControl,
				   const LM::LibrarySet*						librarySet,
				   const CalculationRules*						calculationRules,
				   EDB::FloorStructureConstRef					floorStructure,
				   const GS::Ref<QT::QTCallBackInterface>&		callBacks);

	template<class CoverElemType>
	QuantityModel (GS::ProcessControl&							processControl,
				   const LM::LibrarySet*						librarySet,
				   const CalculationRules*						calculationRules,
				   EDB::FloorStructureConstRef					floorStructure,
				   const GS::Ref<QT::QTCallBackInterface>&		callBacks,
				   VBElem::ModelElementConstRef					listingElem,
				   const GS::PagedArray<CoverElemType>&			coverElems);

	template<class ListingElemType, class CoverElemType>
	QuantityModel (GS::ProcessControl&							processControl,
				   const LM::LibrarySet*						librarySet,
				   const CalculationRules*						calculationRules,
				   EDB::FloorStructureConstRef					floorStructure,
				   const GS::Ref<QT::QTCallBackInterface>&		callBacks,
				   const GS::PagedArray<ListingElemType>&		listingElems,
				   const GS::PagedArray<CoverElemType>&			coverElems);

	virtual ~QuantityModel ();

private:
	// ... Type definitions ............................................................................................

	class ModelElemCacheKey {
	public:
		ModelElemCacheKey () : m_elemGuid (GS::NULLGuid), m_listParams (FILL_FOR_LISTING) {}
		ModelElemCacheKey (const ModelElemCacheKey& source) : m_elemGuid (source.m_elemGuid), m_listParams (source.m_listParams) {}
		ModelElemCacheKey (const GS::Guid& elemGuid, const CONV2LISTREC& listParams) : m_elemGuid (elemGuid), m_listParams (listParams) {}

		~ModelElemCacheKey () {}

		bool operator== (const ModelElemCacheKey& other) const
		{
			return m_elemGuid == other.m_elemGuid && m_listParams == other.m_listParams;
		}
		bool operator!= (const ModelElemCacheKey& other) const
		{
			return !(operator== (other));
		}

		operator GS::HashValue () const
		{
			static UInt32 HashPrime = 65587;	// prime for the hash value computation
			ULong hashValue = 0;
			hashValue = hashValue * HashPrime + m_elemGuid.GetHashValue ();
			hashValue = hashValue * HashPrime + m_listParams.operator GS::HashValue ().hashValue;
			return hashValue;
		}

	private:
		GS::Guid		m_elemGuid;
		CONV2LISTREC	m_listParams;
	};

	class ModelPolygonFilterCacheKey {
	public:
		ModelPolygonFilterCacheKey () : m_type (MPF_Unknown) {}
		ModelPolygonFilterCacheKey (const ModelPolygonFilterCacheKey& source) : m_type (source.m_type) {}
		ModelPolygonFilterCacheKey (ModelPolygonFilterType type) : m_type (type) {}

		~ModelPolygonFilterCacheKey () {}

		bool operator== (const ModelPolygonFilterCacheKey& other)
		{
			return m_type == other.m_type;
		}
		bool operator!= (const ModelPolygonFilterCacheKey& other)
		{
			return !(operator== (other));
		}

		ModelPolygonFilterType	GetType () const { return m_type; }

		operator GS::HashValue () const
		{
			return m_type;
		}

	private:
		ModelPolygonFilterType	m_type;
	};

	typedef	GS::HashTable<GS::Guid, VBElem::ModelElementConstRef>										VBElemSet;
	typedef	GS::HashTable<ModelElemCacheKey, Modeler::ConstElemPtr>										ModelElemCache;
	typedef GS::HashTable<ModelPolygonFilterCacheKey, ModelCalculations::ModelPolygonFilterConstPtr>	ModelPolygonFilterCache;

	// ... Initialization ..............................................................................................

			void	AddElemToListingElemSet	(const VBElem::ModelElementConstRef& elem);
			void	AddElemToCoverElemSet	(const VBElem::ModelElementConstRef& elem);

	virtual	bool	InitConv3DEnvir (const VBES::ElemSetConstRef& elemSet) const = 0;

	// ... Conversion control ..........................................................................................

	enum ConversionGroup {
		Group_Invalid		= -1,
		Group_First			= 0,
		Group_Wall			= 0,
		Group_Beam			= 1,
		Group_Column		= 2,
		Group_Slab			= 3,
		Group_Shell			= 4,
		Group_PlaneRoof		= 5,
		Group_PolyRoof		= 6,
		Group_Mesh			= 7,
		Group_Morph			= 8,
		Group_CurtainWall	= 9,
		Group_Opening		= 10,
		Group_GDLObject		= 11,
		Group_Railing		= 12,
		Group_Room			= 13,
		Group_Stair			= 14,
		Group_CoverElem		= 15,
		Group_Last			= 15
	};

	ConversionGroup			GetConversionGroup (const VBElem::ModelElementConstRef& vbElem) const;
	void					ConvertElemList (GS::PagedArray<EDB::GeneralElemConstRef>& elemList, const CONV2LISTREC& listParams) const;
	void					ConvertGroup (ConversionGroup conversionGroup, const CONV2LISTREC& listParams) const;
	Modeler::ConstElemPtr	GetPlaneSeparetedPolyRoof (VBElem::PolyRoofConstRef polyRoof) const;

	// ... ModelPolygonFilter creation .................................................................................

	void	CreateModelPolygonFilter (ModelPolygonFilterCacheKey modelPolygonFilterCacheKey) const;
	void	CreateExposedSurfaceModelPolygonFilter () const;

	VBElemSet&			GetListingElemSet ();
	const VBElemSet&	GetListingElemSet () const;

	// ... Data members.................................................................................................
protected:	
	mutable VBTo3D::Environment*							m_conv3DEnvir;

private:
	mutable	Modeler::AttributesPtr								m_attributesPtr;
	GS::ProcessControl&											m_processControl;
	const LM::LibrarySet*										m_librarySet;
	const CalculationRules*										m_calculationRules;
	EDB::FloorStructureConstRef									m_floorStructure;
	const GS::Ref<QT::QTCallBackInterface>						m_callBacks;

	mutable	bool												m_isConv3DEnvirInitialized;

	GS::PagedArray<VBElemSet>									m_listingElemSetStack;
	VBElemSet													m_coverElemSet;
	GS::HashSet<GS::Guid>										m_coverElemGuids;

	mutable ModelElemCache										m_modelElemCache;				// converted model elems
	mutable ModelPolygonFilterCache								m_modelPolygonFilterCache;		// contains KD trees to fast polygon search
	mutable	GS::HashTable<GS::Guid, Modeler::ConstElemPtr>		m_planeSeparatedPolyRoofCache;	// elems to cut PolyRoof models to plane separated models

	class WPolyCacheKey {
		VBElem::WallConstRef	wall;
		Int32					floor;

	public:
		WPolyCacheKey () : floor (0) {}

		WPolyCacheKey (const VBElem::WallConstRef& wall, Int32 floor) : wall (wall), floor (floor) 
		{
		}

		operator GS::HashValue () const 
		{
			const UInt32 HashPrime = 65587;
			return wall.GenerateHashValue () + HashPrime * GS::GenerateHashValue (floor);
		}

		bool operator == (const WPolyCacheKey& other) const
		{
			return wall == other.wall && floor == other.floor;
		}
	};

	mutable GS::HashTable <WPolyCacheKey, Geometry::IrregularPolygon2D>	m_wPolyCache;

	class HoleElemCacheKey {
		Modeler::ConstElemPtr withoutHoleElem;
		Modeler::ConstElemPtr withHoleElem;
	public:
		HoleElemCacheKey () {}
		HoleElemCacheKey (const Modeler::ConstElemPtr& withoutHoleElem, const Modeler::ConstElemPtr& withHoleElem) : withoutHoleElem (withoutHoleElem), withHoleElem (withHoleElem)
		{
		}

		operator GS::HashValue () const
		{
			const UInt32 HashPrime = 65587;
			return GS::GenerateHashValue (withoutHoleElem.GetPtr ()) + HashPrime * GS::GenerateHashValue (withHoleElem.GetPtr ());
		}

		bool operator == (const HoleElemCacheKey& other) const
		{
			return withoutHoleElem == other.withoutHoleElem && withHoleElem == other.withHoleElem;
		}
	};

	mutable GS::HashTable <HoleElemCacheKey, Modeler::ConstElemPtr> m_holeElemCache;
};


template<class ListingElemType>
void	QuantityModel::PushListingElems (const GS::PagedArray<ListingElemType>& listingElems)
{
	m_listingElemSetStack.PushNew ();
	for (UIndex i = 0; i < listingElems.GetSize (); ++i) {
		if (ODB::IsType<VBElem::ModelElement> (listingElems[i])) {
			VBElem::ModelElementConstRef elem = ODB::StaticCast<VBElem::ModelElement> (listingElems[i]);
			AddElemToListingElemSet (elem);
		}
	}
}


template<class CoverElemType>
QuantityModel::QuantityModel (GS::ProcessControl&						processControl,
							  const LM::LibrarySet*						librarySet,
							  const CalculationRules*					calculationRules,
							  EDB::FloorStructureConstRef				floorStructure,
							  const GS::Ref<QT::QTCallBackInterface>&	callBacks,
							  VBElem::ModelElementConstRef				listingElem,
							  const GS::PagedArray<CoverElemType>&		coverElems) :
	m_attributesPtr (nullptr),
	m_conv3DEnvir (nullptr),
	m_processControl (processControl),
	m_librarySet (librarySet),
	m_calculationRules (calculationRules),
	m_floorStructure (floorStructure),
	m_callBacks (callBacks),
	m_isConv3DEnvirInitialized (false)
{
	GS::PagedArray<VBElem::ModelElementConstRef> listingElems;
	listingElems.Push (listingElem);
	PushListingElems (listingElems);

	for (UIndex i = 0; i < coverElems.GetSize (); ++i) {
		if (ODB::IsType<VBElem::ModelElement> (coverElems[i])) {
			VBElem::ModelElementConstRef elem = ODB::StaticCast<VBElem::ModelElement> (coverElems[i]);
			AddElemToCoverElemSet (elem);
		}
	}

	DBASSERT (!GetListingElemSet ().IsEmpty ());
}


template<class ListingElemType, class CoverElemType>
QuantityModel::QuantityModel (GS::ProcessControl&						processControl,
							  const LM::LibrarySet*						librarySet,
							  const CalculationRules*					calculationRules,
							  EDB::FloorStructureConstRef				floorStructure,
							  const GS::Ref<QT::QTCallBackInterface>&	callBacks,
							  const GS::PagedArray<ListingElemType>&	listingElems,
							  const GS::PagedArray<CoverElemType>&		coverElems) :
	m_attributesPtr (nullptr),
	m_conv3DEnvir (nullptr),
	m_processControl (processControl),
	m_librarySet (librarySet),
	m_calculationRules (calculationRules),
	m_floorStructure (floorStructure),
	m_callBacks (callBacks),
	m_isConv3DEnvirInitialized (false)
{
	PushListingElems (listingElems);

	for (UIndex i = 0; i < coverElems.GetSize (); ++i) {
		if (ODB::IsType<VBElem::ModelElement> (coverElems[i])) {
			VBElem::ModelElementConstRef elem = ODB::StaticCast<VBElem::ModelElement> (coverElems[i]);
			AddElemToCoverElemSet (elem);
		}
	}
}



class QUANTITYTAKEOFF_DLL_EXPORT QuantityCalculatorProviderAdapter : public Property::QuantityCalculatorProvider
{
public:
	QuantityCalculatorProviderAdapter (const GS::SharedPtr<QuantityModel>& quantityModel);
	virtual ~QuantityCalculatorProviderAdapter ();

	virtual void													PushHint (const GS::PagedArray<EDB::GeneralElemConstRef>& elems) override final;
	virtual void													PopHint () override final;

	virtual GS::Ref<Property::IModelElementQuantityCalculator>		GetQuantityCalculator (const Property::PropertyOwnerConstPtr& propertyOwner) const override final;
	virtual GS::Ref<Property::IBeamQuantityCalculator>				GetQuantityCalculator (const VBElem::BeamConstRef& beam) const override final;
	virtual GS::Ref<Property::ICeilQuantityCalculator>				GetQuantityCalculator (const VBElem::CeilConstRef& ceil) const override final;
	virtual GS::Ref<Property::IColumnQuantityCalculator>			GetQuantityCalculator (const VBElem::ColumnConstRef& column) const override final;
	virtual GS::Ref<Property::ICurtainWallQuantityCalculator>		GetQuantityCalculator (const VBElem::CurtainWallConstRef& cwFrame) const override final;
	virtual GS::Ref<Property::ICWFrameQuantityCalculator>			GetQuantityCalculator (const VBElem::CWFrameConstRef& cwFrame) const override final;
	virtual GS::Ref<Property::ICWPanelQuantityCalculator>			GetQuantityCalculator (const VBElem::CWPanelConstRef& cwPanel) const override final;
	virtual GS::Ref<Property::ICWSegmentQuantityCalculator>			GetQuantityCalculator (const VBElem::CWSegmentConstRef& cwSegment) const override final;
	virtual GS::Ref<Property::ICWAccessoryQuantityCalculator>		GetQuantityCalculator (const VBElem::CWAccessoryConstRef& cwAccessory) const override final;
	virtual GS::Ref<Property::ICWJunctionQuantityCalculator>		GetQuantityCalculator (const VBElem::CWJunctionConstRef& cwJunction) const override final;
	virtual GS::Ref<Property::IFreeShapeQuantityCalculator>			GetQuantityCalculator (const VBElem::FreeShapeConstRef& freeShape) const override final;
	virtual GS::Ref<Property::IGDLObjectQuantityCalculator>			GetQuantityCalculator (const VBElem::GDLObjectConstRef& object) const override final;
	virtual GS::Ref<Property::IMeshQuantityCalculator>				GetQuantityCalculator (const VBElem::MeshConstRef& mesh) const override final;
	virtual GS::Ref<Property::IPlaneRoofQuantityCalculator>			GetQuantityCalculator (const VBElem::PlaneRoofConstRef& planeRoof) const override final;
	virtual GS::Ref<Property::IPolyRoofQuantityCalculator>			GetQuantityCalculator (const VBElem::PolyRoofConstRef& polyRoof) const override final;
	virtual GS::Ref<Property::IPolyRoofQuantityCalculator>			GetQuantityCalculator (const VBElem::PolyRoofConstRef& polyRoof, const Property::PolyRoofElemPartId& elemPartId) const override final;
	virtual GS::Ref<Property::IRoomQuantityCalculator>				GetQuantityCalculator (const VBElem::RoomConstRef& room) const override final;
	virtual GS::Ref<Property::IRailBaseQuantityCalculator>			GetQuantityCalculator (const VBElem::RailBaseConstRef& railBase) const override final;
	virtual GS::Ref<Property::IRailBaseEndQuantityCalculator>		GetQuantityCalculator (const VBElem::RailBaseEndConstRef& railBase) const override final;
	virtual GS::Ref<Property::IRailBaseConnectionQuantityCalculator>GetQuantityCalculator (const VBElem::RailBaseConnectionConstRef& railBase) const override final;
	virtual GS::Ref<Property::IRailingQuantityCalculator>			GetQuantityCalculator (const VBElem::RailingConstRef& railing) const override final;	
	virtual GS::Ref<Property::IRailingPanelQuantityCalculator>		GetQuantityCalculator (const VBElem::RailingPanelConstRef& railingPanel) const override final;
	virtual GS::Ref<Property::IRailingPostBaseQuantityCalculator>	GetQuantityCalculator (const VBElem::RailingPostBaseConstRef& railingPostBase) const override final;
	virtual GS::Ref<Property::IRailingSegmentQuantityCalculator>	GetQuantityCalculator (const VBElem::RailingSegmentConstRef& railingSegment) const override final;
	virtual GS::Ref<Property::IRiserQuantityCalculator>				GetQuantityCalculator (const VBElem::RiserConstRef& riser) const override final;
	virtual GS::Ref<Property::IShellQuantityCalculator>				GetQuantityCalculator (const VBElem::ShellConstRef& shell) const override final;
	virtual GS::Ref<Property::ISkylightQuantityCalculator>			GetQuantityCalculator (const VBElem::SkylightConstRef& skylight) const override final;
	virtual GS::Ref<Property::IStairQuantityCalculator>				GetQuantityCalculator (const VBElem::StairConstRef& stair) const override final;
	virtual GS::Ref<Property::IStairStructureQuantityCalculator>	GetQuantityCalculator (const VBElem::StairStructureConstRef& stairStructure) const override final;
	virtual GS::Ref<Property::IStairSubElementQuantityCalculator>	GetQuantityCalculator (const VBElem::StairSubElementConstRef& stairSubElement) const override final;
	virtual GS::Ref<Property::ITreadQuantityCalculator>				GetQuantityCalculator (const VBElem::TreadConstRef& tread) const override final;
	virtual GS::Ref<Property::IWallOpeningQuantityCalculator>		GetQuantityCalculator (const VBElem::WallOpeningConstRef& wallOpening) const override final;
	virtual GS::Ref<Property::IWallQuantityCalculator>				GetQuantityCalculator (const VBElem::WallConstRef& wall) const override final;

protected:
	void SetQuantityModel (const GS::SharedPtr<QuantityModel>& newQuantityModel) { quantityModel = newQuantityModel; }	//#KiP_Refactor #KiP_QT #KiP_Urgency_Low #KiP_Severity_Medium

private:
	GS::SharedPtr<QuantityModel> quantityModel;
};

}


#endif
