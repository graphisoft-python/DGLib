// Contact person : KiP

#ifndef PROPERTY_EVALUATION_ENVIRONMENT_SOURCE_HPP
#define PROPERTY_EVALUATION_ENVIRONMENT_SOURCE_HPP

#pragma  once

// === Includes ========================================================================================================

// from GSRoot
#include "SharedObject.hpp"

// from VBElements
#include "BeamTypes.hpp"
#include "CeilTypes.hpp"
#include "ColumnTypes.hpp"
#include "CurtainWallTypes.hpp"
#include "CWFrameTypes.hpp"
#include "CWPanelTypes.hpp"
#include "CWAccessoryTypes.hpp"
#include "CWJunctionTypes.hpp"
#include "CWSegmentTypes.hpp"
#include "DrawingTypes.hpp"
#include "FreeShapeTypes.hpp"
#include "GDLObjectTypes.hpp"
#include "MeshTypes.hpp"
#include "PlaneRoofTypes.hpp"
#include "PolyRoofTypes.hpp"
#include "RailBaseTypes.hpp"
#include "RailBaseEndTypes.hpp"
#include "RailBaseConnectionTypes.hpp"
#include "RailingTypes.hpp"
#include "RailingPanelTypes.hpp"
#include "RailingPostBaseTypes.hpp"
#include "RailingSegmentTypes.hpp"
#include "RiserTypes.hpp"
#include "RoomTypes.hpp"
#include "ShellTypes.hpp"
#include "SkylightTypes.hpp"
#include "StairTypes.hpp"
#include "StairStructureTypes.hpp"
#include "StairSubElementTypes.hpp"
#include "TreadTypes.hpp"
#include "WallOpeningTypes.hpp"
#include "WallTypes.hpp"
#include "SymbTypes.hpp"
#include "ChangeMarkerTypes.hpp"

#include "VBElemSet/ElemSet.hpp"

// from VBElemOperations
#include "GDLGlobalCalculations.hpp"

// from PropertyOperations
#include "PropertyOperationsTypes.hpp"
#include "PropertyOperationsExport.hpp"
#include "PropertyValueCache.hpp"
#include "StaticBuiltInPropertyDefinitionContainer.hpp"

#include "ExpressionEvaluationAuxiliaryData.hpp"

// === Predeclarations =================================================================================================

namespace LM {
	class LibrarySet;
}

namespace Property {
	class IModelElementQuantityCalculator;
	class IBeamQuantityCalculator;
	class ICeilQuantityCalculator;
	class IColumnQuantityCalculator;
	class ICurtainWallQuantityCalculator;
	class ICWFrameQuantityCalculator;
	class ICWPanelQuantityCalculator;
	class ICWAccessoryQuantityCalculator;
	class ICWJunctionQuantityCalculator;
	class ICWSegmentQuantityCalculator;
	class IFreeShapeQuantityCalculator;
	class IGDLObjectQuantityCalculator;
	class IMeshQuantityCalculator;
	class IPlaneRoofQuantityCalculator;
	class IPolyRoofQuantityCalculator;
	class IRailBaseQuantityCalculator;
	class IRailBaseEndQuantityCalculator;
	class IRailBaseConnectionQuantityCalculator;
	class IRailingQuantityCalculator;
	class IRailingPanelQuantityCalculator;
	class IRailingPostBaseQuantityCalculator;
	class IRailingSegmentQuantityCalculator;
	class IRiserQuantityCalculator;
	class IRoomQuantityCalculator;
	class IShellQuantityCalculator;
	class ISkylightQuantityCalculator;
	class IStairQuantityCalculator;
	class IStairStructureQuantityCalculator;
	class IStairSubElementQuantityCalculator;
	class ITreadQuantityCalculator;
	class IWallOpeningQuantityCalculator;
	class IWallQuantityCalculator;
	class IZoneQuantityCalculator;

	template <Int32 permissionFlags>
	class EvaluationEnvironment;

	class PolyRoofElemPartId;
}

namespace VBElem {
	class ModelElement;
	typedef ODB::ConstRef<ModelElement> ModelElementConstRef;
}

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ElevationReferenceLevels
{
public:
	ElevationReferenceLevels (double firstReferenceLevel, double secondReferenceLevel, double seaLevel);

	double	GetFirstReferenceLevel () const;
	double	GetSecondReferenceLevel () const;
	double	GetSeaLevel () const;

private:
	double firstReferenceLevel;
	double secondReferenceLevel;
	double seaLevel;
};


class PROPERTY_OPERATIONS_DLL_EXPORT ExpressionEvaluationEnvironmentSource {
public:
	enum EvaluationSelector {
		EvaluationDisabled
	};
	ExpressionEvaluationEnvironmentSource (EvaluationSelector = EvaluationSelector::EvaluationDisabled);
	ExpressionEvaluationEnvironmentSource (const PropertyOperations::ExpressionEvaluationAuxiliaryData& evalAuxData);

	bool 													IsExpressionEvaluationEnabled () const;
	PropertyOperations::ExpressionEvaluationAuxiliaryData	GetExpressionEvaluationAuxiliaryData () const;
private:
	bool 													isExpressionEvaluationEnabled;
	PropertyOperations::ExpressionEvaluationAuxiliaryData	evalAuxData;
};


class PROPERTY_OPERATIONS_DLL_EXPORT PropertyEvaluationAuxiliaryData : public GS::SharedObject
{
public:
	enum ConversionMode
	{
		PBC_Conversion,
		Legacy_Conversion
	};

	virtual ~PropertyEvaluationAuxiliaryData ();

	virtual EDB::ProjectConstRef									GetProject () const = 0;
	virtual const LM::LibrarySet*									GetLibrarySet () const = 0;
	virtual ElevationReferenceLevels								GetReferenceLevels () const = 0;
	virtual StaticBuiltInPropertyDefinitionContainerConstPtr		GetExpressionBuiltInPropertyContainer () const = 0;
	virtual PropertyOperations::ExpressionEvaluationAuxiliaryData	GetExpressionEvaluationAuxiliaryData () const = 0;
	virtual bool													IsExpressionEvaluationEnabled () const = 0;
	virtual ConversionMode											GetConversionMode () const = 0;
};

class PROPERTY_OPERATIONS_DLL_EXPORT PropertyEvaluationAuxiliaryDataImpl : public PropertyEvaluationAuxiliaryData
{
public:
	PropertyEvaluationAuxiliaryDataImpl (const EDB::ProjectConstRef&									project,
										 const LM::LibrarySet*											librarySet,
										 const ElevationReferenceLevels&								referenceLevels,
										 const StaticBuiltInPropertyDefinitionContainerConstPtr&		expressionBuiltInPC,
										 const ExpressionEvaluationEnvironmentSource&					expressionEvaluationEnvironmentSource,
										 ConversionMode													conversionMode);

	virtual EDB::ProjectConstRef									GetProject () const override;
	virtual const LM::LibrarySet*									GetLibrarySet () const override;
	virtual ElevationReferenceLevels								GetReferenceLevels () const override;
	virtual StaticBuiltInPropertyDefinitionContainerConstPtr		GetExpressionBuiltInPropertyContainer () const override;
	virtual PropertyOperations::ExpressionEvaluationAuxiliaryData	GetExpressionEvaluationAuxiliaryData () const override;
	virtual bool													IsExpressionEvaluationEnabled () const override;
	virtual ConversionMode											GetConversionMode () const override;

private:
	EDB::ProjectConstRef									project;
	const LM::LibrarySet*									librarySet;
	ElevationReferenceLevels								referenceLevels;
	StaticBuiltInPropertyDefinitionContainerConstPtr		expressionBuiltInPC;
	ExpressionEvaluationEnvironmentSource					expressionEvalEnvSource;
	ConversionMode											conversionMode;
};


class PROPERTY_OPERATIONS_DLL_EXPORT QuantityCalculatorProvider : public GS::SharedObject
{
public:
	virtual ~QuantityCalculatorProvider ();

	virtual void											PushHint					(const GS::PagedArray<EDB::GeneralElemConstRef>& elems) = 0;
	virtual void											PopHint						() = 0;

	virtual GS::Ref<IModelElementQuantityCalculator>		GetQuantityCalculator		(const PropertyOwnerConstPtr& propertyOwner)										const = 0;
	virtual GS::Ref<IBeamQuantityCalculator>				GetQuantityCalculator		(const VBElem::BeamConstRef& beam)													const = 0;
	virtual GS::Ref<ICeilQuantityCalculator>				GetQuantityCalculator		(const VBElem::CeilConstRef& ceil)													const = 0;
	virtual GS::Ref<IColumnQuantityCalculator>				GetQuantityCalculator		(const VBElem::ColumnConstRef& column)												const = 0;
	virtual GS::Ref<ICurtainWallQuantityCalculator>			GetQuantityCalculator		(const VBElem::CurtainWallConstRef& cw)												const = 0;
	virtual GS::Ref<ICWFrameQuantityCalculator>				GetQuantityCalculator		(const VBElem::CWFrameConstRef& cwFrame)											const = 0;
	virtual GS::Ref<ICWPanelQuantityCalculator>				GetQuantityCalculator		(const VBElem::CWPanelConstRef& cwPanel)											const = 0;
	virtual GS::Ref<ICWAccessoryQuantityCalculator>			GetQuantityCalculator		(const VBElem::CWAccessoryConstRef& cwAcc)											const = 0;
	virtual GS::Ref<ICWJunctionQuantityCalculator>			GetQuantityCalculator		(const VBElem::CWJunctionConstRef& cwJunc)											const = 0;
	virtual GS::Ref<ICWSegmentQuantityCalculator>			GetQuantityCalculator		(const VBElem::CWSegmentConstRef& cwSegment)										const = 0;
	virtual GS::Ref<IFreeShapeQuantityCalculator>			GetQuantityCalculator		(const VBElem::FreeShapeConstRef& freeShape)										const = 0;
	virtual GS::Ref<IGDLObjectQuantityCalculator>			GetQuantityCalculator		(const VBElem::GDLObjectConstRef& object)											const = 0;
	virtual GS::Ref<IMeshQuantityCalculator>				GetQuantityCalculator		(const VBElem::MeshConstRef& mesh)													const = 0;
	virtual GS::Ref<IPlaneRoofQuantityCalculator>			GetQuantityCalculator		(const VBElem::PlaneRoofConstRef& planeRoof)										const = 0;
	virtual GS::Ref<IPolyRoofQuantityCalculator>			GetQuantityCalculator		(const VBElem::PolyRoofConstRef& polyRoof)											const = 0;
	virtual GS::Ref<IPolyRoofQuantityCalculator>			GetQuantityCalculator		(const VBElem::PolyRoofConstRef& polyRoof, const PolyRoofElemPartId& elemPartId)	const = 0;
	virtual GS::Ref<IRailBaseQuantityCalculator>			GetQuantityCalculator		(const VBElem::RailBaseConstRef& railBase)											const = 0;
	virtual GS::Ref<IRailBaseEndQuantityCalculator>			GetQuantityCalculator		(const VBElem::RailBaseEndConstRef& railBase)										const = 0;
	virtual GS::Ref<IRailBaseConnectionQuantityCalculator>	GetQuantityCalculator		(const VBElem::RailBaseConnectionConstRef& railBase)								const = 0;
	virtual GS::Ref<IRailingQuantityCalculator>				GetQuantityCalculator		(const VBElem::RailingConstRef& railing)											const = 0;
	virtual GS::Ref<IRailingPanelQuantityCalculator>		GetQuantityCalculator		(const VBElem::RailingPanelConstRef& railingPanel)									const = 0;
	virtual GS::Ref<IRailingPostBaseQuantityCalculator>		GetQuantityCalculator		(const VBElem::RailingPostBaseConstRef& railingPostBase)							const = 0;
	virtual GS::Ref<IRailingSegmentQuantityCalculator>		GetQuantityCalculator		(const VBElem::RailingSegmentConstRef& railingSegment)								const = 0;
	virtual GS::Ref<IRiserQuantityCalculator>				GetQuantityCalculator		(const VBElem::RiserConstRef& room)													const = 0;
	virtual GS::Ref<IRoomQuantityCalculator>				GetQuantityCalculator		(const VBElem::RoomConstRef& riser)													const = 0;
	virtual GS::Ref<IShellQuantityCalculator>				GetQuantityCalculator		(const VBElem::ShellConstRef& shell)												const = 0;
	virtual GS::Ref<ISkylightQuantityCalculator>			GetQuantityCalculator		(const VBElem::SkylightConstRef& skylight)											const = 0;
	virtual GS::Ref<IStairQuantityCalculator>				GetQuantityCalculator		(const VBElem::StairConstRef& stair)												const = 0;
	virtual GS::Ref<IStairStructureQuantityCalculator>		GetQuantityCalculator		(const VBElem::StairStructureConstRef& stairStructure)								const = 0;
	virtual GS::Ref<IStairSubElementQuantityCalculator>		GetQuantityCalculator		(const VBElem::StairSubElementConstRef& stairStructure)								const = 0;
	virtual GS::Ref<ITreadQuantityCalculator>				GetQuantityCalculator		(const VBElem::TreadConstRef& tread)												const = 0;
	virtual GS::Ref<IWallOpeningQuantityCalculator>			GetQuantityCalculator		(const VBElem::WallOpeningConstRef& wallOpening)									const = 0;
	virtual GS::Ref<IWallQuantityCalculator>				GetQuantityCalculator		(const VBElem::WallConstRef& wall)													const = 0;
};


class PROPERTY_OPERATIONS_DLL_EXPORT CalcRoomSurfVol_Data
{
public:
	CalcRoomSurfVol_Data ()
	{
		volume = nullptr;
		bound_surf = nullptr;
		top_surf = nullptr;
		bot_surf = nullptr;
		roof_top_surf = nullptr;
		roof_bot_surf = nullptr;
		slab_top_surf = nullptr;
		slab_bot_surf = nullptr;
		beam_top_surf = nullptr;
		beam_bot_surf = nullptr;
		wall_inset_top = nullptr;
		wall_inset_back = nullptr;
		wall_inset_side = nullptr;
	}

	double*					volume;
	double*					bound_surf;
	double*					top_surf;
	double*					bot_surf;
	double*					roof_top_surf;
	double*					roof_bot_surf;
	double*					slab_top_surf;
	double*					slab_bot_surf;
	double*					beam_top_surf;
	double*					beam_bot_surf;
	double*					wall_inset_top;
	double*					wall_inset_back;
	double*					wall_inset_side;
};


class PROPERTY_OPERATIONS_DLL_EXPORT ArchicadAccessor : public GS::SharedObject
{
public:
	virtual ~ArchicadAccessor ();

	virtual bool							IsElemLocked				(const GS::Guid& guid) const = 0;
	virtual  GS::Array<GS::UniString>		GetLinkedChangeIds			(EDB::GeneralElemConstRef generalElemRef) const = 0;
	virtual void							GetPropertyObjects			(const GS::Guid& guid, GS::Array<GS::UniString>& objNames) const = 0;
	virtual VBElem::RoomConstRef			GetZoneToElem				(EDB::GeneralElemConstRef generalElemRef) const = 0;
	virtual void							GetRoomConnections			(EDB::GeneralElemConstRef generalElemRef, VBElem::RoomConstRef* fromRoom, VBElem::RoomConstRef* toRoom) const = 0;
	virtual VBElem::RoomConstRefList		GetCollidingRooms			(EDB::GeneralElemConstRef generalElemRef) const = 0;
	virtual EDB::GeneralElemConstRefList	GetCollidingElements		(VBElem::RoomConstRef roomRef) const = 0;
	virtual GS::UniString					GetType						(EDB::GeneralElemConstRef generalElemRef) const = 0;
	virtual GS::UniString					GetChangeName				(const VBElem::ChangeMarkerConstRef& changeMarker, bool& nameIsAvailable) const = 0;
	virtual GS::UniString					GetDrawingEffectiveName		(const VBElem::DrawingConstRef& drawing)  const = 0;
	virtual double							GetCurrentFloorLevel		() const = 0;
	virtual void							CallGDLElemParamScript		(EDB::GeneralElemRef generalElemRef, GS::UniString modifiedParName) const = 0;
	virtual double							GetDScale					() const = 0;
	virtual void							CalcRoomWallsData			(
																		VBElem::RoomConstRef	room,
																		double					minOpeningSize,
																		double*					roomWalls_prm,
																		double*					roomWalls_surf,
																		double*					roomDoors_wid,
																		double*					roomDoors_surf,
																		double*					roomWinds_wid,
																		double*					roomWinds_surf) const = 0;
	virtual void						CalcRoomSurfVol				(VBElem::RoomConstRef	pRoom, CalcRoomSurfVol_Data& toCalc) const = 0;
	virtual void						FillGDLGlobalCalcEnvir		(VBCalculations::GDLGlobalCalcEnvir& gdlGlobals, VBES::ElemSetConstRef elemSet) const = 0;
	virtual GS::UniString				GetDrawingEffectiveId		(VBElem::DrawingConstRef drawing) const = 0;
	virtual bool						HasExtendedSymbolInterface	(const VBElem::SymbConstRef& symb) const = 0;
	virtual GS::Array<Int32>			GetMEPSystemsForSymb		(const VBElem::SymbConstRef& symb) const = 0;
};


class PROPERTY_OPERATIONS_DLL_EXPORT IFCAccessor : public GS::SharedObject
{
public:
	virtual ~IFCAccessor ();

	virtual bool		IsDummy () = 0;
	virtual GSErrCode	GetIFCGuid (const GS::Guid& elemGuid, GS::Guid& actualIFCGuid, GS::Guid& originalIFCGuid) = 0;
	virtual GSErrCode	GSGuid2IFCGuid (const GS::Guid& gsGuid, GS::UniString& ifcGuid) = 0;
};


class PROPERTY_OPERATIONS_DLL_EXPORT PropertyEvaluationEnvironmentSource : public GS::SharedObject
{
public:
	static PropertyEvaluationEnvironmentSourceConstPtr Create (const GS::ConstSharedPtr<PropertyEvaluationAuxiliaryData>&	auxiliaryData,
															   const GS::SharedPtr<PropertyValueCache>&						propertyValueCache,
															   const GS::SharedPtr<QuantityCalculatorProvider>&				quantityCalculatorProvider,
															   const GS::ConstSharedPtr<ArchicadAccessor>&					archicadAccessor,
															   const GS::SharedPtr<IFCAccessor>&							ifcAccessor);

	virtual ~PropertyEvaluationEnvironmentSource ();

private:
	friend class UnsafeEvaluationEnvironmentImp;

	GS::ConstSharedPtr<PropertyEvaluationAuxiliaryData>	auxiliaryData;
	GS::SharedPtr<PropertyValueCache>					propertyValueCache;		// TODO B-470 const?
	GS::SharedPtr<QuantityCalculatorProvider>			quantityCalculatorProvider;
	GS::ConstSharedPtr<ArchicadAccessor>				archicadAccessor;
	GS::SharedPtr<IFCAccessor>							ifcAccessor;

	PropertyEvaluationEnvironmentSource ();
	PropertyEvaluationEnvironmentSource (const PropertyEvaluationEnvironmentSource&);
	PropertyEvaluationEnvironmentSource& operator= (const PropertyEvaluationEnvironmentSource&);

	PropertyEvaluationEnvironmentSource (const GS::ConstSharedPtr<PropertyEvaluationAuxiliaryData>&	auxiliaryData,
										 const GS::SharedPtr<PropertyValueCache>&					propertyValueCache,
										 const GS::SharedPtr<QuantityCalculatorProvider>&			quantityCalculatorProvider,
										 const GS::ConstSharedPtr<ArchicadAccessor>&				archicadAccessor,
										 const GS::SharedPtr<IFCAccessor>&							ifcAccessor);
};

}

#endif
