// Contact person : AACS

#ifndef PROPERTY_EVALUATION_ENVIRONMENT_HPP
#define PROPERTY_EVALUATION_ENVIRONMENT_HPP

#pragma  once

// === Includes ========================================================================================================

// from VBAttributes
#include "ADBGeneralDefinitions.hpp"

// from Property
#include "PropertyCallbackPermissions.hpp"

// from PropertyOperations
#include "PropertyEvaluationEnvironmentData.hpp"

// === Predeclarations =================================================================================================

// =====================================================================================================================

namespace Property {

template <Int32 permissionFlags>
class EvaluationEnvironment;


class PROPERTY_OPERATIONS_DLL_EXPORT UnsafeEvaluationEnvironmentImp
{
	template<Int32 permissionFlags> friend class EvaluationEnvironment;

private:
	UnsafeEvaluationEnvironmentImp ();
	UnsafeEvaluationEnvironmentImp (const UnsafeEvaluationEnvironmentImp& other, Int32 permissionFlags);
	UnsafeEvaluationEnvironmentImp (const PropertyEvaluationEnvironmentSourceConstPtr& source, Int32 permissionFlags);

	bool			SourceEquals (const UnsafeEvaluationEnvironmentImp& other) const;

	EDB::ProjectConstRef										GetProject () const;
	ADB::AttributeSetConstRef									GetAttributeSet () const;
	EDB::FloorStructureConstRef									GetFloorStructure () const;
	ODB::IdSpace*												GetIdSpace () const;
	const LM::LibrarySet*										GetLibrarySet () const;

	bool														IsPBCEnabled () const;
	double														GetFirstReferenceLevel () const;
	double														GetSecondReferenceLevel () const;
	double														GetSeaLevelAltitude () const;

	VBElem::RoomConstRef										GetZoneToElem (ODB::ConstRef<EDB::GeneralElem>& genElem) const;

	const PropertyValueCachePtr&								GetPropertyValueCache () const;	// TODO B-470 Const?
	const GS::SharedPtr<QuantityCalculatorProvider>&			GetQuantityCalculatorAccessor () const;
	const GS::ConstSharedPtr<ArchicadAccessor>&					GetArchicadAccessor () const;
	const GS::SharedPtr<IFCAccessor>&							GetIFCAccessor () const;

	StaticBuiltInPropertyDefinitionContainerConstPtr			GetExpressionBuiltInPropertyContainer () const;
	PropertyOperations::ExpressionEvaluationAuxiliaryData		GetExpressionEvaluationAuxiliaryData () const;
	bool														IsExpressionEvaluationEnabled () const;

private:
	PropertyEvaluationEnvironmentSourceConstPtr		source;
	Int32											permissionFlags;
};


template <Int32 permissionFlags = CallbackPermissions::NoPermissions>
class EvaluationEnvironment
{
	template <Int32 otherFlags> friend class ::Property::EvaluationEnvironment;

public:
	EvaluationEnvironment ();
	template <Int32 otherFlags>
	EvaluationEnvironment (const EvaluationEnvironment<otherFlags>& other);
	EvaluationEnvironment (const PropertyEvaluationEnvironmentSourceConstPtr& source);

	bool operator== (const EvaluationEnvironment<permissionFlags>& other) const;


	// Compile-time access validation of Property Accessors
#define REQUIRES_PERMISSION(PERM_FLAGS, RET_TYPE) \
	template <Int32 i = permissionFlags> \
	typename std::enable_if_t<(i & (PERM_FLAGS)) == (PERM_FLAGS), RET_TYPE>
	
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, EDB::ProjectConstRef)				GetProject () const { return imp.GetProject (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, ADB::AttributeSetConstRef)			GetAttributeSet () const { return imp.GetAttributeSet (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, EDB::FloorStructureConstRef)		GetFloorStructure () const { return imp.GetFloorStructure (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, ODB::IdSpace*)						GetIdSpace () const { return imp.GetIdSpace (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, const LM::LibrarySet*)				GetLibrarySet () const { return imp.GetLibrarySet (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, bool)								IsPBCEnabled () const { return imp.IsPBCEnabled (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, double)							GetFirstReferenceLevel () const { return imp.GetFirstReferenceLevel (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, double)							GetSecondReferenceLevel () const { return imp.GetSecondReferenceLevel (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, double)							GetSeaLevelAltitude () const { return imp.GetSeaLevelAltitude (); }
	REQUIRES_PERMISSION (CallbackPermissions::ArchicadPermission, VBElem::RoomConstRef)			GetZoneToElem (ODB::ConstRef<EDB::GeneralElem> genElem) const { return imp.GetZoneToElem (genElem); }

	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, StaticBuiltInPropertyDefinitionContainerConstPtr)						GetExpressionBuiltInPropertyContainer () const { return imp.GetExpressionBuiltInPropertyContainer (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, PropertyOperations::ExpressionEvaluationAuxiliaryData)					GetExpressionEvaluationAuxiliaryData () const { return imp.GetExpressionEvaluationAuxiliaryData (); }
	REQUIRES_PERMISSION (CallbackPermissions::NoPermissions, bool)																	IsExpressionEvaluationEnabled () const { return imp.IsExpressionEvaluationEnabled (); }
	REQUIRES_PERMISSION (CallbackPermissions::ValueCachePermission, const PropertyValueCachePtr&)									GetPropertyValueCache () const { return imp.GetPropertyValueCache (); }
	REQUIRES_PERMISSION (CallbackPermissions::QuantityCalculatorPermission, const GS::SharedPtr<QuantityCalculatorProvider>&)		GetQuantityCalculatorAccessor () const { return imp.GetQuantityCalculatorAccessor (); }
	REQUIRES_PERMISSION (CallbackPermissions::ArchicadPermission, const GS::ConstSharedPtr<ArchicadAccessor>&)						GetArchicadAccessor () const { return imp.GetArchicadAccessor (); }
	REQUIRES_PERMISSION (CallbackPermissions::IFCPermission, const GS::SharedPtr<IFCAccessor>&)										GetIFCAccessor () const { return imp.GetIFCAccessor (); }

#undef REQUIRES_PERMISSION

private:

	UnsafeEvaluationEnvironmentImp	imp;
};



template <Int32 permissionFlags>
EvaluationEnvironment<permissionFlags>::EvaluationEnvironment ()
{
}

template <Int32 permissionFlags>
template <Int32 otherFlags>
EvaluationEnvironment<permissionFlags>::EvaluationEnvironment (const EvaluationEnvironment<otherFlags>& other) :
	imp (other.imp, permissionFlags)
{
	static_assert ((otherFlags & permissionFlags) == permissionFlags, "Property::EvaluationEnvironment<> can not be initialized from other instance, which has less permissions in template argument");
}

template <Int32 permissionFlags>
EvaluationEnvironment<permissionFlags>::EvaluationEnvironment (const PropertyEvaluationEnvironmentSourceConstPtr& source) :
	imp (source, permissionFlags)
{
}

template <Int32 permissionFlags>
bool EvaluationEnvironment<permissionFlags>::operator== (const EvaluationEnvironment<permissionFlags>& other) const
{
	return this->imp.SourceEquals (other.imp);
}

}

#endif
