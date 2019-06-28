// Contact person :	KiP

#ifndef CLASSID_HPP
#define CLASSID_HPP

#pragma once

// === Includes ========================================================================================================

// from GSRoot
#include "HashCommon.hpp"

// from PropertyOperations
#include "PropertyOperationsExport.hpp"
#include "PropertyOperationsTypes.hpp"

// =====================================================================================================================

namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ClassId
{
public:
	ClassId ();
	explicit ClassId (const GS::ClassInfo* classInfo);
	ClassId (const ClassId& source);
	~ClassId ();

	template <typename T> static ClassId Create ();

	ClassId& operator= (const ClassId& source);

	bool operator== (const ClassId& other) const;
	bool operator!= (const ClassId& other) const;

	bool					IsCompatibleWith (const ClassId& other) const;
	const GS::ClassInfo*	GetClassInfo () const;

	operator GS::HashValue () const;

	GSErrCode	Read (GS::IChannel& ic);
	GSErrCode	Write (GS::OChannel& oc) const;

private:
	const GS::ClassInfo* classInfo;
};

template <typename T>
ClassId ClassId::Create ()
{
	return ClassId (T::GetClassInfoStatic ());
}

}

#endif
