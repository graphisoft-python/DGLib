// *********************************************************************************************************************
// Description:		RailingFloorPlanGeometryCache
//
// Module:			VBElemOperations
// Namespace:		VBElemOperations
// Contact person:	NYD
//
// SG compatible
// *********************************************************************************************************************
#if !defined _RAILING_FLOORPLAN_GEOMETRY_CACHE_HPP_
#define _RAILING_FLOORPLAN_GEOMETRY_CACHE_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "Array.hpp"
#include "Md5.hpp"

// from VBElements
#include "VBElements/RailingTypes.hpp"

// from VBElemOperations
#include "RailingModelViewOption.hpp"
#include "RailingFloorPlanCalculator.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------
namespace VBCalculations
{
	struct GDLGlobalCalcEnvir;
}

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------
namespace VBCalculations
{

class RailingCacheExplicitUpdater : public ODB::Object
{
	DECLARE_DYNAMIC_CLASS_INFO (RailingCacheExplicitUpdater);
private:

#define _RailingCacheExplicitUpdater_DATA_MEMBERS_										\
	volatile Int64			cacheInvalidationValue;										\

	_RailingCacheExplicitUpdater_DATA_MEMBERS_

	class IsolatedState : public ODB::Object::IsolatedState
	{
	private:
		friend class RailingCacheExplicitUpdater;
		_RailingCacheExplicitUpdater_DATA_MEMBERS_
	public:
		virtual ~IsolatedState ();
	};

public:
	RailingCacheExplicitUpdater ();
	virtual ~RailingCacheExplicitUpdater ();

	virtual RailingCacheExplicitUpdater*				Clone (void) const override;
	virtual	GSErrCode									StoreIsolatedState (ODB::Object::IsolatedState* isolatedState) const override;
	virtual	GSErrCode									RestoreIsolatedState (const ODB::Object::IsolatedState* isolatedState) override;
	virtual	void										Isolate (void) override;
	virtual	ODB::Object::IsolatedState*					CreateIsolatedState (void) const override;
	virtual USize										GetIsolatedSize (void) const override;
	virtual	GSErrCode									WriteIsolatedState (GS::OChannel& oc) const override;
	virtual	GSErrCode									ReadIsolatedState (GS::IChannel& ic) override;

public:
	static Int64										GetCurrentIdForRailing (const VBElem::RailingConstRef& railingRef);
	static void											UpdateCacheForRailing (const VBElem::RailingConstRef& railingRef);
};


// === class RailingFloorPlanGeometryCache ===============================================================================
class RailingFloorPlanGeometryCache
{
public:
	class Data : public ODB::Object
	{
		DECLARE_DYNAMIC_CLASS_INFO (Data)
	public:
		template<typename RefType, typename ValType>
		using HashTable1N = GS::HashTable<RefType, GS::Array<ValType>>;

#define _RailingFloorPlanGeometryCache_DATA_MEMBERS_											\
	private:																					\
		UInt64														m_railingModiStamp;					\
		short														m_actFloor;							\
		double														m_actFloorLevel;					\
		double														m_actFloorHeight;					\
		double														m_belowFloorHeight;					\
		double														m_actFloorCutLevel;					\
		VBElem::RailingGridType										m_gridType;							\
		RailingModelViewOption										m_railingMVO;						\
		RailingFloorPlanCalculator::RailingParts					m_railingParts;						\
		HashTable1N<VBElem::RailingSubElementConstRef, double>		m_fullPartPolygonGeometry;			\
		HashTable1N<VBElem::RailingSubElementConstRef, double>		m_lowerPartPolygonGeometry;			\
		HashTable1N<VBElem::RailingSubElementConstRef, double>		m_middlePartPolygonGeometry;		\
		HashTable1N<VBElem::RailingSubElementConstRef, double>		m_upperPartPolygonGeometry;			\
		HashTable1N<VBElem::RailingSubElementConstRef, double>		m_fullPartCenterPolylineGeometry;	\
		HashTable1N<VBElem::RailingSubElementConstRef, double>		m_lowerPartCenterPolylineGeometry;	\
		HashTable1N<VBElem::RailingSubElementConstRef, double>		m_middlePartCenterPolylineGeometry;	\
		HashTable1N<VBElem::RailingSubElementConstRef, double>		m_upperPartCenterPolylineGeometry;	\
		HashTable1N<VBElem::RailingSubElementConstRef, double>		m_fullPolylineGeometry;				\
		HashTable1N<VBElem::RailingSubElementConstRef, Int32>		m_fullPartPolygonFlags;				\
		HashTable1N<VBElem::RailingSubElementConstRef, Int32>		m_lowerPartPolygonFlags;			\
		HashTable1N<VBElem::RailingSubElementConstRef, Int32>		m_middlePartPolygonFlags;			\
		HashTable1N<VBElem::RailingSubElementConstRef, Int32>		m_upperPartPolygonFlags;			\
		HashTable1N<VBElem::RailingSubElementConstRef, Int32>		m_fullPartCenterPolylineFlags;		\
		HashTable1N<VBElem::RailingSubElementConstRef, Int32>		m_lowerPartCenterPolylineFlags;		\
		HashTable1N<VBElem::RailingSubElementConstRef, Int32>		m_middlePartCenterPolylineFlags;	\
		HashTable1N<VBElem::RailingSubElementConstRef, Int32>		m_upperPartCenterPolylineFlags;		\
		HashTable1N<VBElem::RailingSubElementConstRef, Int32>		m_fullPolylineFlags;				\
		GS::HashTable<VBElem::RailingSubElementConstRef, RailingGeometry::RailingAttributeSet>		m_fullPartAttributeSet;				\
		GS::HashTable<VBElem::RailingSubElementConstRef, RailingGeometry::RailingAttributeSet>		m_lowerPartAttributeSet;			\
		GS::HashTable<VBElem::RailingSubElementConstRef, RailingGeometry::RailingAttributeSet>		m_middlePartAttributeSet;			\
		GS::HashTable<VBElem::RailingSubElementConstRef, RailingGeometry::RailingAttributeSet>		m_upperPartAttributeSet;			\
		HashTable1N<VBElem::RailBaseConstRef, double>												m_postPositions;					\
		MD5::FingerPrint											m_associatedElemsFingerprint;										\
		HashTable1N<VBElem::RailingSegmentConstRef, double>			m_breakMarkIntervals;												\
		Int64														m_updaterId;														\


		_RailingFloorPlanGeometryCache_DATA_MEMBERS_

		class IsolatedState : public ODB::Object::IsolatedState {
		private:
			friend class Data;

			_RailingFloorPlanGeometryCache_DATA_MEMBERS_

		public:
			virtual ~IsolatedState ();
	};

	public:
		Data ();

	// ... ODB::Object interface ..........................................................................................
	public:
		virtual Data*										Clone							(void) const override;
		virtual	GSErrCode									StoreIsolatedState   			(ODB::Object::IsolatedState* isolatedState) const override;
		virtual	GSErrCode									RestoreIsolatedState 			(const ODB::Object::IsolatedState* isolatedState) override;
		virtual	void										Isolate							(void) override;
		virtual	ODB::Object::IsolatedState*					CreateIsolatedState				(void) const override;
		virtual USize										GetIsolatedSize					(void) const override;
		virtual	GSErrCode									WriteIsolatedState   			(GS::OChannel& oc) const override;
		virtual	GSErrCode									ReadIsolatedState 				(GS::IChannel& ic) override;

	private:
		GSErrCode											WriteIsolatedStateVersion2		(GS::OChannel& oc, const GS::OutputFrame& frame) const;
		GSErrCode											ReadIsolatedStateVersion2		(GS::IChannel& ic, const GS::InputFrame& frame);
		GSErrCode											WriteForContentIdGeneration		(GS::OChannel& oc) const;

		void												Clear							(void);

	// ... content Id generation .........................................................................................
	public:
		void												FillBasicData					(const VBElem::RailingConstRef& railing, const GDLGlobalCalcEnvir& envir);

		ODB::Id												GetContentId					(void) const;

	// ... content conversion ...........................................................................................
	public:
		void												Fill							(const VBElem::RailingConstRef& railing, const GDLGlobalCalcEnvir& envir, const RailingFloorPlanCalculator::RailingParts& parts);

	// ... accessors ......................................................................................................
	public:
		const GS::Array<double>*							GetFullPolygonGeometry				(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<double>*							GetLowerPolygonGeometry				(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<double>*							GetMiddlePolygonGeometry			(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<double>*							GetUpperPolygonGeometry				(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<Int32>*								GetFullPolygonFlags					(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<Int32>*								GetLowerPolygonFlags				(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<Int32>*								GetMiddlePolygonFlags				(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<Int32>*								GetUpperPolygonFlags				(const VBElem::RailingSubElementConstRef& rail) const;

		const GS::Array<double>*							GetFullCenterPolylineGeometry		(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<double>*							GetLowerCenterPolylineGeometry		(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<double>*							GetMiddleCenterPolylineGeometry		(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<double>*							GetUpperCenterPolylineGeometry		(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<Int32>*								GetFullCenterPolylineFlags			(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<Int32>*								GetLowerCenterPolylineFlags			(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<Int32>*								GetMiddleCenterPolylineFlags		(const VBElem::RailingSubElementConstRef& rail) const;
		const GS::Array<Int32>*								GetUpperCenterPolylineFlags			(const VBElem::RailingSubElementConstRef& rail) const;

		const GS::Array<double>*							GetSubElemCenterPolylineGeometry	(const VBElem::RailingSubElementConstRef& railSubElem) const;
		const GS::Array<double>*							GetPostCoordsForSegment				(const VBElem::RailBaseConstRef& railRef) const;
		const GS::Array<double>*							GetBreakMarkIntervalData			(const VBElem::RailingSegmentConstRef& segment) const;

		const RailingFloorPlanCalculator::RailingParts&		GetRailingParts						() const;

		RailingGeometry::RailingAttributeSet				GetFullAttributeSet					(const VBElem::RailingSubElementConstRef& railSubElem) const;
		RailingGeometry::RailingAttributeSet				GetLowerAttributeSet				(const VBElem::RailingSubElementConstRef& railSubElem) const;
		RailingGeometry::RailingAttributeSet				GetMiddleAttributeSet				(const VBElem::RailingSubElementConstRef& railSubElem) const;
		RailingGeometry::RailingAttributeSet				GetUpperAttributeSet				(const VBElem::RailingSubElementConstRef& railSubElem) const;
	};
public:
	static ODB::ConstRef<Data>								GetData								(const VBElem::RailingConstRef& railing, const GDLGlobalCalcEnvir& gdlGlobals);
	static ODB::ConstRef<Data>								GetCachedData						(const VBElem::RailingConstRef& railing, const GDLGlobalCalcEnvir& gdlGlobals);

	static ODB::Id											GetContentId						(const VBElem::RailingConstRef& railing, const GDLGlobalCalcEnvir& gdlGlobals);
	static MD5::FingerPrint									GetAssociatedElemsFingerprint		(const VBElem::RailingConstRef& railing);
};

}		// namespace VBCalculations

#endif	// _RAILING_FLOORPLAN_GEOMETRY_CACHE_HPP_