// Contact person: KiP

#ifndef DYNAMIC_BUILTIN_PROPERTY_DEFINITION_GROUP_HPP
#define DYNAMIC_BUILTIN_PROPERTY_DEFINITION_GROUP_HPP

#pragma once

// === Includes ========================================================================================================

// form PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT DynamicBuiltInPropertyDefinitionGroup : public ODB::Object
{
	DECLARE_CLASS_INFO

protected:
	class PROPERTY_OPERATIONS_DLL_EXPORT IsolatedState : public ODB::Object::IsolatedState
	{
	public:
		virtual ~IsolatedState ();
	};

	DynamicBuiltInPropertyDefinitionGroup (const GS::ClassInfo* finalClassinfo);

public:
	virtual ~DynamicBuiltInPropertyDefinitionGroup ();

	virtual GS::Guid											GetGuid () const = 0;
	virtual	GS::UniString										GetName () const = 0;
	virtual	PropertyDefinitionGroupUserId						GetUserId () const = 0;

	virtual	bool												IsEmpty () const;
	virtual	bool												Contains (const GS::Guid& guid) const = 0;
	virtual	bool												Contains (const PropertyDefinitionUserId& userId) const;

	virtual	DynamicBuiltInPropertyDefinitionConstPtr			GetPropertyDefinition (const GS::Guid& guid) const = 0;
	virtual	DynamicBuiltInPropertyDefinitionConstPtr			GetPropertyDefinition (const PropertyDefinitionUserId& userId) const;

	virtual void												Enumerate (const std::function<void (const DynamicBuiltInPropertyDefinitionConstPtr&)>& processor) const = 0;

	virtual DynamicBuiltInPropertyDefinitionContainerConstRef	GetContainer () const;

	// ... read / write methods (Object interface) .....................................................................
public:
	virtual	GSErrCode							Read (GS::IChannel& ic) override;
	virtual	GSErrCode							Write (GS::OChannel& oc) const override;
	virtual	GSErrCode							ReadXML (GS::XMLIChannel& ic) override;
	virtual	GSErrCode							WriteXML (GS::XMLOChannel& oc) const override;

	// ... transaction management methods ..............................................................................
public:
	virtual GSErrCode							StoreIsolatedState (ODB::Object::IsolatedState* isolatedState) const override;
	virtual GSErrCode							RestoreIsolatedState (const ODB::Object::IsolatedState* isolatedState) override;
	virtual void								Isolate () override;
	virtual ODB::Object::IsolatedState*			CreateIsolatedState () const override;
	virtual USize								GetIsolatedSize () const override;
	virtual GSErrCode							ReadIsolatedState (GS::IChannel& ic) override;
	virtual GSErrCode							WriteIsolatedState (GS::OChannel& oc) const override;
private:
			GSErrCode							ReadIsolatedStateVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);
			GSErrCode							WriteIsolatedStateVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
};

PropertyDefinitionGroupConstPtr CreateAdapter (const DynamicBuiltInPropertyDefinitionGroupConstRef& group);

}

#endif
