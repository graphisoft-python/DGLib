// Contact person: KV

#ifndef CLASSIFICATION_SYSTEM_BUILTIN_PROPERTY_DEFINITION_GROUP_HPP
#define CLASSIFICATION_SYSTEM_BUILTIN_PROPERTY_DEFINITION_GROUP_HPP

#pragma once

// === Includes ========================================================================================================

// from Classification
#include "ClassificationTypes.hpp"

// from PropertyOperations
#include "DynamicBuiltInPropertyDefinitionGroup.hpp"

// === Predeclarations =================================================================================================

namespace Property {
	class ClassificationSystemBuiltInPropertyDefinitionGroup;
	typedef ODB::Ref<ClassificationSystemBuiltInPropertyDefinitionGroup> ClassificationSystemBuiltInPropertyDefinitionGroupRef;
	typedef ODB::ConstRef<ClassificationSystemBuiltInPropertyDefinitionGroup> ClassificationSystemBuiltInPropertyDefinitionGroupConstRef;
}

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ClassificationSystemBuiltInPropertyDefinitionGroup : public DynamicBuiltInPropertyDefinitionGroup
{
	DECLARE_DYNAMIC_CLASS_INFO (ClassificationSystemBuiltInPropertyDefinitionGroup)

private:
	class IsolatedState : public DynamicBuiltInPropertyDefinitionGroup::IsolatedState
	{
	public:
		virtual ~IsolatedState ();
	};

public:
	ClassificationSystemBuiltInPropertyDefinitionGroup ();
	virtual ~ClassificationSystemBuiltInPropertyDefinitionGroup ();

	// ... DynamicBuiltInPropertyDefinitionGroup interface .............................................................
public:
	virtual GS::Guid											GetGuid () const override;
	virtual	GS::UniString										GetName () const override;
	virtual	PropertyDefinitionGroupUserId						GetUserId () const override;

	virtual	bool												Contains (const GS::Guid& guid) const override;
	virtual	DynamicBuiltInPropertyDefinitionConstPtr			GetPropertyDefinition (const GS::Guid& guid) const override;

	virtual void												Enumerate (const std::function<void (const DynamicBuiltInPropertyDefinitionConstPtr&)>& processor) const override;

	// ... read / write methods (Object interface) .....................................................................
public:
	static GS::Guid								GetFixGuid ();
	static GS::UniString						GetFixName ();
	static PropertyDefinitionGroupUserId		GetFixUserId ();

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

private:
	CLS::IClassificationSystemContainerConstRef		GetClassificationSystemContainer () const;

	ClassificationSystemBuiltInPropertyDefinitionGroup (const ClassificationSystemBuiltInPropertyDefinitionGroup&);				// disabled
	ClassificationSystemBuiltInPropertyDefinitionGroup& operator= (const ClassificationSystemBuiltInPropertyDefinitionGroup&);	// disabled	
};

}

#endif
