
// *****************************************************************************
//
//                                Class Cloneable
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined CLONEABLE_HPP
#define CLONEABLE_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Definitions.hpp"


// ============================== Class Cloneable ==============================

namespace GS {

template <typename Type>
struct DefaultCloneOperations {
	static Type*	Clone  (const Type& data) { return data.Clone (); }
	static void		Delete (Type* data)		  { delete data; }
};


template <typename Type, template <typename> class CloneOperations = DefaultCloneOperations>
class Cloneable {
private:
	Type* value = nullptr;

public:
	Cloneable () = default;
	Cloneable (Type* value);
   	Cloneable (const Cloneable& source);
	Cloneable (Cloneable&& source);
	Cloneable&	operator= (const Cloneable& source);
	Cloneable&  operator= (Cloneable&& source);
	Cloneable&  operator= (Type* newValue);
	Cloneable&  operator= (std::nullptr_t);
   ~Cloneable ();

	Type&		operator* ();
	const Type&	operator* () const;
	Type*		operator-> ();
	const Type*	operator-> () const;
};

}	// namespace GS


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>::Cloneable (Type* value):
	value (value)
{
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>::Cloneable (const Cloneable& source):
	value (source.value != nullptr ? CloneOperations<Type>::Clone (*source.value) : nullptr)
{
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>::Cloneable (Cloneable&& source):
	value (source.value)
{
	source.value = nullptr;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>&	GS::Cloneable<Type, CloneOperations>::operator= (const Cloneable& source)
{
	if (&source != this) {
		CloneOperations<Type>::Delete (value);
		value = source.value != nullptr ? CloneOperations<Type>::Clone (*source.value) : nullptr;
	}

	return *this;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>&  GS::Cloneable<Type, CloneOperations>::operator= (Cloneable&& source)
{
	value = source.value;
	source.value = nullptr;

	return *this;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>&  GS::Cloneable<Type, CloneOperations>::operator= (Type* newValue)
{
	CloneOperations<Type>::Delete (value);
	value = newValue;

	return *this;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>&  GS::Cloneable<Type, CloneOperations>::operator= (std::nullptr_t)
{
	CloneOperations<Type>::Delete (value);
	value = nullptr;

	return *this;
}


template <typename Type, template <typename> class CloneOperations>
GS::Cloneable<Type, CloneOperations>::~Cloneable ()
{
	CloneOperations<Type>::Delete (value);
}


template <typename Type, template <typename> class CloneOperations>
Type&	GS::Cloneable<Type, CloneOperations>::operator* ()
{
	return *value;
}


template <typename Type, template <typename> class CloneOperations>
const Type&		GS::Cloneable<Type, CloneOperations>::operator* () const
{
	return *value;
}


template <typename Type, template <typename> class CloneOperations>
Type*	GS::Cloneable<Type, CloneOperations>::operator-> ()
{
	return value;
}


template <typename Type, template <typename> class CloneOperations>
const Type*		GS::Cloneable<Type, CloneOperations>::operator-> () const
{
	return value;
}


#endif
