// Contact person : KiP

#ifndef RAILING_SEGMENT_OPERATIONS__HPP
#define RAILING_SEGMENT_OPERATIONS__HPP

// === Includes ========================================================================================================

// from VBElements
#include "RailingSegmentTypes.hpp"
#include "RailTypes.hpp"
#include "RailingTypes.hpp"
#include "HandrailTypes.hpp"
#include "InnerPostTypes.hpp"
#include "BalusterSetTypes.hpp"
#include "BalusterTypes.hpp"
#include "RailingPanelTypes.hpp"

#include "StairOperations.hpp"

// from VBElemOperations
#include "VBElemOperationsExport.hpp"

// =====================================================================================================================

class VB_ELEM_OPERATIONS_DLL_EXPORT RailingSegmentOperations
{
public:
	static bool HasToprail (const VBElem::RailingSegmentConstRef& railingSegment);
	
	static bool HasUpperHandrail (const VBElem::RailingSegmentConstRef& railingSegment);
	
	static bool HasLowerHandrail (const VBElem::RailingSegmentConstRef& railingSegment);

	static Int32 GetRailingSegmentIndex (const VBElem::RailingSegmentConstRef& railingSegment);

	static void	EnumerateHandrails (const VBElem::RailingSegmentConstRef& railingSegment, const std::function<void (const VBElem::HandrailConstRef&)>& enumerator);

	static void EnumerateRails (const VBElem::RailingSegmentConstRef& railingSegment, const std::function<void (const VBElem::RailConstRef&)>& enumerator);

	static void EnumerateGeneratedPanels (const VBElem::RailingSegmentConstRef& railingSegment, const std::function<void (const VBElem::RailingPanelConstRef&)>& enumerator);

	static void EnumerateGeneratedInnerPosts (const VBElem::RailingSegmentConstRef& railingSegment, const std::function<void (const VBElem::InnerPostConstRef&)>& enumerator);

	static void EnumerateGeneratedBalusterSets (const VBElem::RailingSegmentConstRef& railingSegment, const std::function<void (const VBElem::BalusterSetConstRef&)>& enumerator);

	static void EnumerateGeneratedBalusters (const VBElem::RailingSegmentConstRef& railingSegment, const std::function<void (const VBElem::BalusterConstRef&)>& enumerator);

	static VBElem::RailingGridType GetEffectiveGridTypeOnFloor (const VBElem::RailingSegmentConstRef& railingSegment, const short floorNum, bool& upperBreakMarkMissing, bool& lowerBreakMarkMissing, const VBCalculations::GDLGlobalCalcEnvir* gdlGlobals = nullptr);
};

#endif

