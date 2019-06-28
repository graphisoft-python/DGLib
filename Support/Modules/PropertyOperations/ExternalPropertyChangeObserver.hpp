// *********************************************************************************************************************
// Description:		Class to observe the changes of the properties in hotlinked modules.
// Module:			PropertyOperations
// Contact person:	KiP
// *********************************************************************************************************************

#ifndef	EXTERNAL_PROPERTY_CHANGE_OBSERVER_HPP
#define EXTERNAL_PROPERTY_CHANGE_OBSERVER_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "PropertyOperationsExport.hpp"

// from ReferenceElemManager
#include "ReferenceElemManager.hpp"

// === Predeclarations =================================================================================================

// =====================================================================================================================

namespace PropertyOperations {

class PROPERTY_OPERATIONS_DLL_EXPORT ExternalPropertyAndClassificationChangeObserver : public SRM::ReferenceElemManagerObserver
{
public:
	ExternalPropertyAndClassificationChangeObserver ();
	virtual ~ExternalPropertyAndClassificationChangeObserver ();

	virtual void	ProxyObjectsGenerated			(SRM::ReferenceElemManagerEvent& event) override;
	virtual void	ObjectsReplacedByProxyObjects	(SRM::ReferenceElemManagerEvent& event) override;
	virtual void	ProxyObjectsReplacedByObjects	(SRM::ReferenceElemManagerEvent& event) override;

private:
	void			NotifyContainerSet				(SRM::ReferenceElemManagerEvent& event);
};

} // namespace PropertyOperations

#endif // EXTERNAL_PROPERTY_CHANGE_OBSERVER_HPP
