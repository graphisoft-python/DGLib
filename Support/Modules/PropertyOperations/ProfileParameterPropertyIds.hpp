// Contact person: RA

#ifndef PROFILEPARAMETER_PROPERTY_IDS_HPP
#define PROFILEPARAMETER_PROPERTY_IDS_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "GSGuid.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"

// =====================================================================================================================

namespace Property {

	PROPERTY_OPERATIONS_DLL_EXPORT	extern const GS::Guid	 ProfileParameterPropertyGroupId;

	PROPERTY_OPERATIONS_DLL_EXPORT  extern const GS::Guid	HorizontalStretchProfileParameterPropertyId;
	PROPERTY_OPERATIONS_DLL_EXPORT  extern const GS::Guid	VerticalStretchProfileParameterPropertyId;

	PROPERTY_OPERATIONS_DLL_EXPORT  extern const GS::Guid	HorizontalTotalSizeProfileParameterPropertyId;
	PROPERTY_OPERATIONS_DLL_EXPORT  extern const GS::Guid	VerticalTotalSizeProfileParameterPropertyId;

	PROPERTY_OPERATIONS_DLL_EXPORT  extern const GS::Guid	HorizontalNominalSizeProfileParameterPropertyId;
	PROPERTY_OPERATIONS_DLL_EXPORT  extern const GS::Guid	VerticalNominalSizeProfileParameterPropertyId;
	
}

#endif
