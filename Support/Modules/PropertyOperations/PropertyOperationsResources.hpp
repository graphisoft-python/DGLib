// *********************************************************************************************************************
// Description:		Resource handler for properties
// Module:			PropertyOperations
// namespace:		PropertyOperations
// *********************************************************************************************************************

#ifndef PROPERTYOPERATIONSRESOURCES_HPP
#define PROPERTYOPERATIONSRESOURCES_HPP

// from GSRoot
#include "UniString.hpp"
#include "RSTypes.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"

namespace PropertyOperations
{

	enum ResIds
	{
		//RINT ResIds
		MiscellaneousStringsId = 100,
		TopStoryStringsId = 101,
		LayerNameStringsId = 102,
		ProfileParameterStringsId = 103
	};

	// The resource values are cached, so the real resource access only happens on the first query of
	// the given resource indices.
	PROPERTY_OPERATIONS_DLL_EXPORT GS::UniString GetResourceString (GSResID resID, Int32 index);

	enum MiscellaneousStringsIds
	{
		CustomProfile				 = 1,
		DisplayNameForEmptyFloorName = 2,
		MissingAttribute			 = 3,
		GeneralSurface				 = 4
	};

	enum TopStoryStringIds
	{
		RelativeTopStorySTR = 1,
		TopStoryNotLinkedSTR = 2,
		TopLinkHome_n_StoryFRMT = 3
	};

	enum LayerNameStringsIds
	{
		ArchichadLayerNameSTR = 1,
		MissingLayerNameSTR = 2
	};

	enum ProfileParameterStringsIds
	{
		ProfileParametersGroupNameSTR = 1,
		HorizontalStretchZoneNameSTR = 2,
		VerticalStretchZoneNameSTR = 3,
		HorizontalTotalSizeNameSTR = 4,
		VerticalTotalSizeNameSTR = 5,
		HorizontalNominalSizeNameSTR = 6,
		VerticalNominalSizeNameSTR = 7
	};

}

#endif
