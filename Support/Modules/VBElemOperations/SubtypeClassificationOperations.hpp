#ifndef SUBTYPE_CLASSIFICATION_OPERATIONS_HPP
#define SUBTYPE_CLASSIFICATION_OPERATIONS_HPP

#include "GSUnID.hpp"
#include "SymbTypes.hpp"
#include "ClassificationTypes.hpp"
#include "VBElemOperationsExport.hpp"

namespace VBElem {
	class SymbDefault;
}

namespace LM {
	class LibrarySet;
}

namespace CLS {

VB_ELEM_OPERATIONS_DLL_EXPORT GSErrCode	AddDefaultClassificationForSubtype	(const VBElem::SymbDefault*						symbDefault,
																			 const LM::LibrarySet*							librarySet,
																			 CLS::ClassificationSystemContainerSetConstRef	containerSet,
																			 const CLS::ClassificationItemConstRef&			classificationItem);

VB_ELEM_OPERATIONS_DLL_EXPORT GSErrCode AddDefaultClassificationsForSubtypes (const GS::HashTable<GS::UnID, CLS::ClassificationItemConstRef>&		subtypeClassifications,
																			 CLS::ClassificationSystemContainerSetConstRef							containerSet);

VB_ELEM_OPERATIONS_DLL_EXPORT GSErrCode	RemoveDefaultClassificationForSubtype (const VBElem::SymbDefault*							symbDefault,
																			   const LM::LibrarySet*								librarySet,
																			   CLS::ClassificationSystemContainerSetConstRef		containerSet,
																			   const CLS::ClassificationItemConstRef&				classificationItem);

VB_ELEM_OPERATIONS_DLL_EXPORT GSErrCode	SetSubtypeBasedDefaultClassificationsForSymbDefault (VBElem::SymbDefault*									symbDefault,
																							 const LM::LibrarySet*									librarySet,
																							 const CLS::ClassificationSystemContainerSetConstRef&	containerSet);

}

#endif