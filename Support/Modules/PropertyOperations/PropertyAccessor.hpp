// Contact person : KiP

#ifndef PROPERTY_ACCESSOR_HPP
#define PROPERTY_ACCESSOR_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "ProjectTypes.hpp"

// from PropertyOperations
#include "StaticBuiltInPropertyDefinitionContainer.hpp"
#include "DynamicBuiltInPropertyDefinitionContainer.hpp"
#include "UserDefinedPropertyDefinitionEquivalenceClassContainer.hpp"
#include "PropertyDefinitionExtension.hpp"
#include "PropertyStatusCache.hpp"

//======================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT PropertyAccessor
{
public:
	enum SelectorFlags
	{
		UserDefined		= 0x0001,
		StaticBuiltIn	= 0x0002,
		DynamicBuiltIn  = 0x0004,
		All = UserDefined | StaticBuiltIn | DynamicBuiltIn
	};

	PropertyAccessor (const PropertyEvaluationEnvironmentSourceConstPtr& envData, const StaticBuiltInPropertyDefinitionContainerConstPtr& staticBuiltInContainer);
	PropertyAccessor (const PropertyEvaluationEnvironmentSourceConstPtr& envData, const StaticBuiltInPropertyDefinitionContainerConstPtr& staticBuiltInContainer, const PropertyOperations::PropertyStatusCachePtr& statusCache);
	PropertyAccessor (const PropertyEvaluationEnvironmentSourceConstPtr& envData, const GS::Array<StaticBuiltInPropertyDefinitionContainerConstPtr>& staticBuiltInContainers);
	~PropertyAccessor ();

	bool									IsExistingProperty			(const PropertyDefinitionUserId& userId, UInt32 selector = All) const;
	bool									IsExistingProperty			(const GS::Guid& guid, UInt32 selector = All) const;
	bool									IsExistingPropertyGroup		(const PropertyDefinitionGroupUserId& userId, UInt32 selector = All) const;
	bool									IsExistingPropertyGroup		(const GS::Guid& guid, UInt32 selector = All) const;

	PropertyDefinitionExtensionConstPtr		GetProperty					(const PropertyDefinitionUserId& userId, UInt32 selector = All) const;
	PropertyDefinitionExtensionConstPtr		GetProperty					(const GS::Guid& guid, UInt32 selector = All) const;
	PropertyDefinitionGroupConstPtr			GetPropertyGroup			(const PropertyDefinitionGroupUserId& userId, UInt32 selector = All) const;
	PropertyDefinitionGroupConstPtr			GetPropertyGroup			(const GS::Guid& guid, UInt32 selector = All) const;

	void	EnumerateProperties				(UInt32 selector, const std::function<void (const PropertyDefinitionExtensionConstPtr&)>& processor) const;
	void	EnumerateAvailableProperties	(UInt32 selector, const PropertyOwner& propertyOwner, const std::function<void (const PropertyDefinitionExtensionConstPtr&)>& processor) const;
	void	EnumeratePropertyGroups			(UInt32 selector, const std::function<void (const PropertyDefinitionGroupConstPtr&)>& processor) const;

private:
	UserDefinedPropertyDefinitionEquivalenceClassContainerConstRef	userDefinedPC;
	GS::Array<StaticBuiltInPropertyDefinitionContainerConstPtr>		staticBuiltInPCs;
	DynamicBuiltInPropertyDefinitionContainerConstRef				dynamicBuiltInPC;
	PropertyEvaluationEnvironmentSourceConstPtr						propEvalEnv;
	PropertyOperations::PropertyStatusCachePtr						statusCache;

	void InitUserDefinedAndDynamicContainers ();

	template <typename IdType>
	bool IsExistingPropertyTemplate (const IdType& id, UInt32 selector) const
	{
		if ((selector & StaticBuiltIn)) {
			for (UIndex i = 0; i < staticBuiltInPCs.GetSize (); ++i) {
				const StaticBuiltInPropertyDefinitionContainerConstPtr& staticBuiltInPC = staticBuiltInPCs[i];
				if (DBVERIFY (staticBuiltInPC != nullptr) && staticBuiltInPC->ContainsDefinition (id)) {
					return true;
				}
			}
		}
		if ((selector & DynamicBuiltIn) && DBVERIFY (dynamicBuiltInPC != nullptr) && dynamicBuiltInPC->ContainsDefinition (id)) {
			return true;
		}
		if ((selector & UserDefined) && DBVERIFY (userDefinedPC != nullptr) && userDefinedPC->ContainsDefinition (id)) {
			return true;
		}
		return false;
	}

	template <typename IdType>
	bool IsExistingPropertyGroupTemplate (const IdType& id, UInt32 selector) const
	{
		if ((selector & StaticBuiltIn)) {
			for (UIndex i = 0; i < staticBuiltInPCs.GetSize (); ++i) {
				const StaticBuiltInPropertyDefinitionContainerConstPtr& staticBuiltInPC = staticBuiltInPCs[i];
				if (DBVERIFY (staticBuiltInPC != nullptr) && staticBuiltInPC->ContainsGroup (id)) {
					return true;
				}
			}
		}
		if ((selector & DynamicBuiltIn) && DBVERIFY (dynamicBuiltInPC != nullptr) && dynamicBuiltInPC->ContainsGroup (id)) {
			return true;
		}
		if ((selector & UserDefined) && DBVERIFY (userDefinedPC != nullptr) && userDefinedPC->ContainsGroup (id)) {
			return true;
		}
		return false;
	}

	template <typename IdType>
	PropertyDefinitionExtensionConstPtr GetPropertyTemplate (const IdType& id, UInt32 selector) const
	{
		if ((selector & StaticBuiltIn)) {
			for (UIndex i = 0; i < staticBuiltInPCs.GetSize (); ++i) {
				const StaticBuiltInPropertyDefinitionContainerConstPtr& staticBuiltInPC = staticBuiltInPCs[i];
				if (DBVERIFY (staticBuiltInPC != nullptr)) {
					StaticBuiltInPropertyDefinitionConstPtr staticBuiltInProperty = staticBuiltInPC->GetPropertyDefinition (id);
					if (staticBuiltInProperty != nullptr) {
						return CreatePropertyDefintionExtension (staticBuiltInProperty, propEvalEnv);
					}
				}
			}
		}
		if ((selector & DynamicBuiltIn) && DBVERIFY (dynamicBuiltInPC != nullptr)) {
			DynamicBuiltInPropertyDefinitionConstPtr dynamicBuiltInProperty = dynamicBuiltInPC->GetPropertyDefinition (id);
			if (dynamicBuiltInProperty != nullptr) {
				return CreatePropertyDefintionExtension (dynamicBuiltInProperty, propEvalEnv);
			}
		}
		if ((selector & UserDefined) && DBVERIFY (userDefinedPC != nullptr)) {
			UserDefinedPropertyDefinitionEquivalenceClassConstRef userDefinedProperty = userDefinedPC->GetPropertyDefinitionEquivalenceClass (id);
			if (userDefinedProperty != nullptr) {
				return CreatePropertyDefintionExtension (userDefinedProperty, propEvalEnv, statusCache);
			}
		}
		return nullptr;
	}

	template <typename IdType>
	PropertyDefinitionGroupConstPtr GetPropertyGroupTemplate (const IdType& id, UInt32 selector) const
	{
		if ((selector & StaticBuiltIn)) {
			for (UIndex i = 0; i < staticBuiltInPCs.GetSize (); ++i) {
				const StaticBuiltInPropertyDefinitionContainerConstPtr& staticBuiltInPC = staticBuiltInPCs[i];
				if (DBVERIFY (staticBuiltInPC != nullptr) && staticBuiltInPC->ContainsGroup (id)) {
					return CreateAdapter (staticBuiltInPC->GetPropertyDefinitionGroup (id));
				}
			}
		}
		if ((selector & DynamicBuiltIn) && DBVERIFY (dynamicBuiltInPC != nullptr) && dynamicBuiltInPC->ContainsGroup (id)) {
			return CreateAdapter (dynamicBuiltInPC->GetPropertyDefinitionGroup (id));
		}
		if ((selector & UserDefined) && DBVERIFY (userDefinedPC != nullptr) && userDefinedPC->ContainsGroup (id)) {
			return CreateAdapter (userDefinedPC->GetPropertyDefinitionEquivalenceClassGroup (id));
		}
		return nullptr;
	}
};

}

#endif
