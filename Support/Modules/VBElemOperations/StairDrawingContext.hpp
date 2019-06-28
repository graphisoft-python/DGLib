#ifndef __STAIR_DRAWING_CONTEXT_HPP__
#define __STAIR_DRAWING_CONTEXT_HPP__


// from GSRoot
#include "Definitions.hpp"
#include "Ref.hpp"
#include "Optional.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"
#include "StairBreakMarkDescription.hpp"

// from VBElements
#include "StairTypes.hpp"

namespace VBCalculations {

const GS::Array<StairBreakMarkDescription::BreakMarkPosition>& GetBreakMarkDrawOrder ();

class VB_ELEM_OPERATIONS_DLL_EXPORT StairDrawingContext // Threadsafe globally usable class
{
public:
	enum StairDrawAttributeSet
	{
		StairVisibleAttributeSet = 1,		// for below break mark parts (or middle parts in case of two break lines)
		StairHiddenAttributeSet = 2			// for above break mark parts (or upper and lower parts in case of two break lines)
	};

	enum Rendering
	{
		StairRenderingUninitalized,
		StairRenderingGrid,
		StairRenderingBreakMark,
		StairRenderingTreads,
		StairRenderingStructures,
		StairRenderingOther
	};

	enum PartPhaseType
	{
		StairUndefinedPartPhase,
		StairLowerPartPhase,
		StairMiddlePartPhase,
		StairUpperPartPhase,
		StairEntireStairPhase
	};

	class Data {
	public:
		friend class StairDrawingContext;
	private:
		UInt32						m_gridDrawingPhase;
		PartPhaseType				m_treadsDrawingPhase;
		PartPhaseType				m_structuresDrawingPhase;
		bool						m_isReflectedCeilingPlanDisplay;

		VBElem::StairGridType		m_currentStairGridType;

		Rendering					m_rendering;

		VBElem::StairStoryRelevancy	m_currentStairStoryRelevancy;

		bool						m_lowerBreakMarkPositionValid;
		bool						m_upperBreakMarkPositionValid;
	public:
		Data ();
	};

private:
	VBElem::StairConstRef		m_stairRef;
	GS::Ref<Data>				m_data;

public:

	~StairDrawingContext					();
	StairDrawingContext						(const StairDrawingContext& original);
	StairDrawingContext						(StairDrawingContext&& original);
	const StairDrawingContext& operator=	(const StairDrawingContext& original);

private:
	StairDrawingContext (VBElem::StairConstRef stairRef, const bool isReflectedCeilingPlanDisplay);
	StairDrawingContext (VBElem::StairConstRef stairRef, const GS::Ref<Data>& data);

private:
	void						Register ();
	void						SetInitialGridPhase ();

	bool						TestGridCriteria () const;

	StairDrawAttributeSet		GetCurrentGridAttributeSet () const;
	StairDrawAttributeSet		GetCurrentTreadsAttributeSet () const;
	StairDrawAttributeSet		GetCurrentStructuresAttributeSet () const;

public:
	StairDrawAttributeSet		GetCurrentStairDrawAttributeSet () const;

	bool						ProgressGridType ();
	void						SetTreadsPhase (PartPhaseType partPhaseType);
	void						SetStructuresPhase (PartPhaseType partPhaseType);
	void						SetRenderedType (Rendering rendering);
	Rendering					GetRenderedType () const;

	VBElem::StairStoryRelevancy	GetStairStoryRelevancy (void) const;
	void						SetStairStoryRelevancy (VBElem::StairStoryRelevancy stairStoryRelevancy);

	VBElem::StairGridType		GetStairGridType (void) const;
	void						SetStairGridType (VBElem::StairGridType	currentStairGridType);

	void						SetBreakMarkValidity (GS::Optional<bool> lowerBreakMarkValid, GS::Optional<bool> upperBreakMarkValid);
	bool						GetLowerBreakMarkValid () const;
	bool						GetUpperBreakMarkValid () const;

	static bool								Exists (VBElem::StairConstRef stairRef);
	static StairDrawingContext				Get (VBElem::StairConstRef stairRef); // CAN THROW
	static StairDrawingContext				Create (VBElem::StairConstRef stairRef, const bool isReflectedCeilingPlanDisplay); // CAN THROW
	static StairDrawingContext				GetOrCreate (VBElem::StairConstRef stairRef, const bool isReflectedCeilingPlanDisplay);
};

}

#endif //__STAIR_DRAWING_CONTEXT_HPP__
