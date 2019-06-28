#ifndef PROPERTYOPERATIONS_SPECIAL_CONSTANTS_HPP
#define PROPERTYOPERATIONS_SPECIAL_CONSTANTS_HPP

#pragma once

// from PropertyOperations
#include "PropertyOperationsExport.hpp"

namespace PropertyOperations {

enum SpecialVariantValues {
	NotLinkedStoryNumber = -31001
};

//TODO B-466 KiP Be kellene vezetni az ElemStructure interface-t,
//es akkor le lehetne rakni ezt a kodot a VBElemOperations-ba ezzel az enummal egyutt.

enum PenOverrideType : Int32 {
	None = 1,
	ForegroundOnly = 2,
	BackgroundOnly = 3,
	Both = 4
};

PROPERTY_OPERATIONS_DLL_EXPORT extern const char* CWFrameInvisibleTypeIdStr;
PROPERTY_OPERATIONS_DLL_EXPORT extern const char* CWFrameGenericTypeIdStr;
PROPERTY_OPERATIONS_DLL_EXPORT extern const char* CWFrameButtGlazedTypeIdStr;

PROPERTY_OPERATIONS_DLL_EXPORT extern const char* CWPanelGenericTypeIdStr;

PROPERTY_OPERATIONS_DLL_EXPORT extern const GS::Guid NoHotlinkSourceId;

} // namespace PropertyOperations

#endif
