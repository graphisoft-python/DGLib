// Contact person: KiP

#ifndef STATIC_BUILTIN_PROPERTY_DEFINITION_CONTAINER_HPP
#define STATIC_BUILTIN_PROPERTY_DEFINITION_CONTAINER_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "HashTable.hpp"
#include "SharedObject.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"
#include "StaticBuiltInPropertyDefinitionGroup.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT StaticBuiltInPropertyDefinitionContainer : public GS::SharedObject
{
	DECLARE_ROOT_CLASS_INFO

public:
	StaticBuiltInPropertyDefinitionContainer (const GS::Guid& guid);
	~StaticBuiltInPropertyDefinitionContainer ();

	const GS::Guid&									GetGuid							() const;

	bool											IsEmpty							() const;
	bool											ContainsGroup					(const GS::Guid& guid) const;
	bool											ContainsGroup					(const PropertyDefinitionGroupUserId& userId) const;
	bool											ContainsDefinition				(const GS::Guid& guid) const;
	bool											ContainsDefinition				(const PropertyDefinitionUserId& userId) const;

	StaticBuiltInPropertyDefinitionGroupConstPtr	GetPropertyDefinitionGroup		(const GS::Guid& guid) const;
	StaticBuiltInPropertyDefinitionGroupConstPtr	GetPropertyDefinitionGroup		(const PropertyDefinitionGroupUserId& userId) const;
	StaticBuiltInPropertyDefinitionConstPtr			GetPropertyDefinition			(const GS::Guid& guid) const;
	StaticBuiltInPropertyDefinitionConstPtr			GetPropertyDefinition			(const PropertyDefinitionUserId& userId) const;

	void											EnumerateGroups					(const std::function<void (const StaticBuiltInPropertyDefinitionGroupConstPtr&)>& processor) const;
	void											EnumerateDefinitions			(const std::function<void (const StaticBuiltInPropertyDefinitionConstPtr&)>& processor) const;

	void											AddPropertyDefinitionGroup		(StaticBuiltInPropertyDefinitionGroupPtr groupToAdd, StaticBuiltInPropertyDefinitionGroupConstPtr nextGroup = nullptr);
	void											AddPropertyDefinition			(StaticBuiltInPropertyDefinitionPtr definitionToAdd, StaticBuiltInPropertyDefinitionGroupPtr targetGroup, StaticBuiltInPropertyDefinitionConstPtr nextDefinition = nullptr);

	typedef GS::Array<StaticBuiltInPropertyDefinitionGroupConstPtr>::ConstIterator ConstIterator;
	ConstIterator									Begin							() const;

private:
	const GS::Guid															guid;
	GS::Array<StaticBuiltInPropertyDefinitionGroupConstPtr>					groups;
	GS::HashTable<GS::Guid, StaticBuiltInPropertyDefinitionGroupConstPtr>	groupsTable;
	GS::HashTable<GS::Guid, StaticBuiltInPropertyDefinitionConstPtr>		definitionsTable;

	UIndex GetGroupIndex (const StaticBuiltInPropertyDefinitionGroupConstPtr& group) const;

	StaticBuiltInPropertyDefinitionContainer ();														// disabled
	StaticBuiltInPropertyDefinitionContainer (const StaticBuiltInPropertyDefinitionContainer&);				// disabled
	StaticBuiltInPropertyDefinitionContainer& operator= (const StaticBuiltInPropertyDefinitionContainer&);	// disabled
};


PROPERTY_OPERATIONS_DLL_EXPORT
PropertyDefinitionContainerConstPtr CreateAdapter (const StaticBuiltInPropertyDefinitionContainerConstPtr& container);

}

#endif
