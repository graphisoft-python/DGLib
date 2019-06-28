// *********************************************************************************************************************
// Description:		SStackImp.hpp
//
// Module:			Modeler
// Contact person:	HK
//
// *********************************************************************************************************************

template<typename Type>
GS_FORCE_INLINE SStack<Type>::SStack (MemAlloc8K* memAlloc) :
	SList<Type> (memAlloc)
{
}

template<typename Type>
GS_FORCE_INLINE SStack<Type>::SStack (const SStack& source) :
	SList<Type> (source)
{
}

template<typename Type>
GS_FORCE_INLINE const SStack<Type>& SStack<Type>::operator= (const SStack& source)
{
	SList<Type>::operator= (source);
	return *this;
}

template<typename Type>
GS_FORCE_INLINE void SStack<Type>::Push ()
{
	SList<Type>::InsertAfter (SListNullPos);
}

template<typename Type>
GS_FORCE_INLINE void SStack<Type>::Push (const Type& t)
{
	SList<Type>::InsertAfter (SListNullPos, t);
}

template<typename Type>
inline Type SStack<Type>::Pop ()
{
	Type t = this->operator[] (SList<Type>::NextPos (SListNullPos));
	SList<Type>::DeleteAfter (SListNullPos);
	return t;
}

template<typename Type>
GS_FORCE_INLINE const Type& SStack<Type>::Top () const
{
	return this->operator[] (SList<Type>::NextPos (SListNullPos));
}

template<typename Type>
GS_FORCE_INLINE Type& SStack<Type>::Top ()
{
	return this->operator[] (SList<Type>::NextPos (SListNullPos));
}

template<typename Type>
GS_FORCE_INLINE void SStack<Type>::Clear ()
{
	SList<Type>::Clear ();
}

template<typename Type>
GS_FORCE_INLINE bool SStack<Type>::IsEmpty () const
{
	return SList<Type>::IsEmpty ();
}

