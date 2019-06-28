// *********************************************************************************************************************
// Priority value converter functions.
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	KV
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (PRIORITYVALUES_HPP)
#define PRIORITYVALUES_HPP

#pragma once

#include "Definitions.hpp"
#include "VBUtilsExport.hpp"

namespace VBUtil {

//******************************* Junction Priority *******************************


Int32 VBUTILS_DLL_EXPORT GetUIPriorityMinimum ();
Int32 VBUTILS_DLL_EXPORT GetUIPriorityMaximum ();

Int32 VBUTILS_DLL_EXPORT GetElemPriorityMinimum ();
Int32 VBUTILS_DLL_EXPORT GetElemPriorityMaximum ();

Int32 VBUTILS_DLL_EXPORT UI2ElemPriority (Int32 priority);
Int32 VBUTILS_DLL_EXPORT Elem2UIPriority (Int32 priority);

Int32 VBUTILS_DLL_EXPORT ConvertElemPriority2Elem16Priority (Int32 priority);


//******************************* Sequence *******************************

Int32 VBUTILS_DLL_EXPORT GetUISequenceMinimum ();
Int32 VBUTILS_DLL_EXPORT GetUISequenceMaximum ();

Int32 VBUTILS_DLL_EXPORT GetElemSequenceMinimum ();
Int32 VBUTILS_DLL_EXPORT GetElemSequenceMaximum ();

Int32 VBUTILS_DLL_EXPORT UI2ElemSequence (Int32 sequence);
Int32 VBUTILS_DLL_EXPORT Elem2UISequence (Int32 sequence);

Int32 VBUTILS_DLL_EXPORT ConvertElemSequence2Elem16Sequence (Int32 sequence);

//******************************* Composition Priority *******************************

Int32 VBUTILS_DLL_EXPORT GetUICompositonPriorityMinimum ();
Int32 VBUTILS_DLL_EXPORT GetUICompositonPriorityMaximum ();

Int32 VBUTILS_DLL_EXPORT GetElemCompositonPriorityMinimum ();
Int32 VBUTILS_DLL_EXPORT GetElemCompositonPriorityMaximum ();

Int32 VBUTILS_DLL_EXPORT UI2ElemCompositonPriority (Int32 priority);
Int32 VBUTILS_DLL_EXPORT Elem2UICompositonPriority (Int32 priority);

Int32 VBUTILS_DLL_EXPORT ConvertElemCompositonPriority2Elem16CompositonPriority (Int32 priority);

}

#endif
