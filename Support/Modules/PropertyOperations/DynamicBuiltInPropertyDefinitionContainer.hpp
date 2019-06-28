// Contact person: KiP

#ifndef DYNAMIC_BUILTIN_PROPERTY_DEFINITION_CONTAINER_HPP
#define DYNAMIC_BUILTIN_PROPERTY_DEFINITION_CONTAINER_HPP

#pragma once

// === Includes ========================================================================================================

// from Property"
#include "OrderedAssociationIterator.hpp"

// form PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"

// from VBElements
#include "ProjectTypes.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT DynamicBuiltInPropertyDefinitionContainer : public ODB::Object
{
	DECLARE_DYNAMIC_CLASS_INFO (DynamicBuiltInPropertyDefinitionContainer)

private:
	class PROPERTY_OPERATIONS_DLL_EXPORT IsolatedState : public ODB::Object::IsolatedState
	{
	public:
		virtual ~IsolatedState ();
	};

	// ... iterator ....................................................................................................
public:
	typedef OrderedAssociationConstIterator<DynamicBuiltInPropertyDefinitionGroup> ConstIterator;
	typedef OrderedAssociationIterator<DynamicBuiltInPropertyDefinitionGroup> Iterator;
	ConstIterator	Begin () const;
	Iterator		Begin ();

	// ... constructors and destructor .................................................................................
public:
	DynamicBuiltInPropertyDefinitionContainer ();
	virtual ~DynamicBuiltInPropertyDefinitionContainer ();

	virtual	DynamicBuiltInPropertyDefinitionContainer*	Clone						() const override;

	// ... query methods ...............................................................................................
public:
	bool												IsEmpty						() const;
	bool												ContainsGroup				(const GS::Guid& guid) const;
	bool												ContainsGroup				(const PropertyDefinitionGroupUserId& userId) const;
	bool												ContainsDefinition			(const GS::Guid& guid) const;
	bool												ContainsDefinition			(const PropertyDefinitionUserId& userId) const;

	DynamicBuiltInPropertyDefinitionGroupConstRef		GetPropertyDefinitionGroup	(const GS::Guid& guid) const;
	DynamicBuiltInPropertyDefinitionGroupConstRef		GetPropertyDefinitionGroup	(const PropertyDefinitionGroupUserId& userId) const;
	DynamicBuiltInPropertyDefinitionConstPtr			GetPropertyDefinition		(const GS::Guid& guid) const;
	DynamicBuiltInPropertyDefinitionConstPtr			GetPropertyDefinition		(const PropertyDefinitionUserId& userId) const;

	void												EnumerateGroups				(const std::function<void (const DynamicBuiltInPropertyDefinitionGroupConstRef&)>& processor) const;
	void												EnumerateDefinitions		(const std::function<void (const DynamicBuiltInPropertyDefinitionConstPtr&)>& processor) const;

	// ... modify container ............................................................................................
public:
			void										AddPropertyDefinitionGroup	(const DynamicBuiltInPropertyDefinitionGroupRef& groupToAdd);

	// ... static helper methods to access associations ................................................................
public:
	static	bool												HasContainer		(const DynamicBuiltInPropertyDefinitionGroupConstRef& propertyDefinitionGroup);
	static	DynamicBuiltInPropertyDefinitionContainerConstRef	GetConstContainer	(const DynamicBuiltInPropertyDefinitionGroupConstRef& propertyDefinitionGroup);
	static	DynamicBuiltInPropertyDefinitionContainerRef		GetContainer		(const DynamicBuiltInPropertyDefinitionGroupRef& propertyDefinitionGroup);

	static	DynamicBuiltInPropertyDefinitionContainerConstRef	GetConstContainer	(const EDB::ProjectConstRef& project);
	static	EDB::ProjectConstRef								GetConstProject		(const DynamicBuiltInPropertyDefinitionContainerConstRef& container);
	static	void												InitializeContainer (const EDB::ProjectRef& project, const std::function<void (DynamicBuiltInPropertyDefinitionContainerRef&)>& createAdditionalGroups);

	// ... read / write methods (Object interface) .....................................................................
public:
	virtual	GSErrCode									Read						(GS::IChannel& ic) override;
	virtual	GSErrCode									Write						(GS::OChannel& oc) const override;
	virtual	GSErrCode									ReadXML						(GS::XMLIChannel& ic) override;
	virtual	GSErrCode									WriteXML					(GS::XMLOChannel& oc) const override;

	// ... transaction management methods ..............................................................................
public:
	virtual GSErrCode									StoreIsolatedState			(ODB::Object::IsolatedState* isolatedState) const override;
	virtual GSErrCode									RestoreIsolatedState		(const ODB::Object::IsolatedState* isolatedState) override;
	virtual void										Isolate						() override;
	virtual ODB::Object::IsolatedState*					CreateIsolatedState			() const override;
	virtual USize										GetIsolatedSize				() const override;
	virtual GSErrCode									ReadIsolatedState			(GS::IChannel& ic) override;
	virtual GSErrCode									WriteIsolatedState			(GS::OChannel& oc) const override;
private:
			GSErrCode									ReadIsolatedStateVersion1	(GS::IChannel& ic, const GS::InputFrame& frame);
			GSErrCode									WriteIsolatedStateVersion1	(GS::OChannel& oc, const GS::OutputFrame& frame) const;

	// ... disabled methods ............................................................................................
private:
	DynamicBuiltInPropertyDefinitionContainer (const DynamicBuiltInPropertyDefinitionContainer&);
	DynamicBuiltInPropertyDefinitionContainer& operator= (const DynamicBuiltInPropertyDefinitionContainer&);
};

PROPERTY_OPERATIONS_DLL_EXPORT
PropertyDefinitionContainerConstPtr CreateAdapter (const DynamicBuiltInPropertyDefinitionContainerConstRef& container);

}

#endif
