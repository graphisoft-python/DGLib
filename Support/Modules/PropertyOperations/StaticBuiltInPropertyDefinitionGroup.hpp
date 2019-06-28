// Contact person: KiP

#ifndef STATIC_BUILTIN_PROPERTY_DEFINITION_GROUP_HPP
#define STATIC_BUILTIN_PROPERTY_DEFINITION_GROUP_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "HashTable.hpp"
#include "SharedObject.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"
#include "StaticBuiltInPropertyDefinition.hpp"
#include "StaticBuiltInPropertyDefinitionContainer.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT StaticBuiltInPropertyDefinitionGroup : public GS::SharedObject
{
	DECLARE_ROOT_CLASS_INFO

public:
	StaticBuiltInPropertyDefinitionGroup (const GS::Guid& guid, const GS::UniString& name);
	~StaticBuiltInPropertyDefinitionGroup ();

	const GS::Guid&										GetGuid					() const;
	const GS::UniString&								GetName					() const;
	const PropertyDefinitionGroupUserId					GetUserId				() const;

	bool												IsEmpty					() const;
	bool												Contains				(const GS::Guid& guid) const;
	bool												Contains				(const PropertyDefinitionUserId& userId) const;

	StaticBuiltInPropertyDefinitionConstPtr				GetPropertyDefinition	(const GS::Guid& guid) const;
	StaticBuiltInPropertyDefinitionConstPtr				GetPropertyDefinition	(const PropertyDefinitionUserId& userId) const;
	StaticBuiltInPropertyDefinitionContainerConstPtr	GetContainer			() const;

	void												Enumerate				(const std::function<void (const StaticBuiltInPropertyDefinitionConstPtr&)>& processor) const;

	typedef GS::Array<StaticBuiltInPropertyDefinitionConstPtr>::ConstIterator ConstIterator;
	ConstIterator										Begin					() const;

private:
	const GS::Guid														guid;
	const GS::UniString													name;
	GS::Array<StaticBuiltInPropertyDefinitionConstPtr>					definitions;
	const StaticBuiltInPropertyDefinitionContainer*							container;
	GS::HashTable<GS::Guid, StaticBuiltInPropertyDefinitionConstPtr>	definitionsTable;

	friend class StaticBuiltInPropertyDefinitionContainer;
	void AddPropertyDefinition (StaticBuiltInPropertyDefinitionPtr definitionToAdd, StaticBuiltInPropertyDefinitionConstPtr nextDefinition = nullptr);
	void SetContainer (const StaticBuiltInPropertyDefinitionContainer* container);
	UIndex GetDefinitionIndex (const StaticBuiltInPropertyDefinitionConstPtr& definition) const;

	StaticBuiltInPropertyDefinitionGroup ();													// disabled
	StaticBuiltInPropertyDefinitionGroup (const StaticBuiltInPropertyDefinitionGroup&);				// disabled
	StaticBuiltInPropertyDefinitionGroup& operator= (const StaticBuiltInPropertyDefinitionGroup&);	// disabled
};

PropertyDefinitionGroupConstPtr CreateAdapter (const StaticBuiltInPropertyDefinitionGroupConstPtr& group);

}

#endif
