
#include "EmbeddedAndLinkedLibrariesWrapper.hpp"

// API
#include "ACAPinc.h"
#include "APIPrivateIntf.hpp"

// ACPM
#include "EmbeddedLibContainerBase.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

// --- Type definitions ------------------------------------------------------------------------------------------------


// --- Variable definitions --------------------------------------------------------------------------------------------

// --- Function definitions --------------------------------------------------------------------------------------------

// =====================================================================================================================
//
// Main Function group
//
// =====================================================================================================================

Extensions::Utilities::EmbeddedAndLinkedLibrariesWrapper::EmbeddedAndLinkedLibrariesWrapper ()
{
	ACAPI_Internal (APIInternal_StoreCurrentEmbeddedAndLinkedLibrariesID, &savedEmbeddedLibraryItems, &savedLinkedLibraryLocations);
}


Extensions::Utilities::EmbeddedAndLinkedLibrariesWrapper::~EmbeddedAndLinkedLibrariesWrapper ()
{
	ACAPI_Internal (APIInternal_RestoreCurrentEmbeddedAndLinkedLibrariesID, &savedEmbeddedLibraryItems, &savedLinkedLibraryLocations);
}