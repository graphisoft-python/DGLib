
// *****************************************************************************
//
//                                 Struct Buffer
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#if !defined BUFFER_HPP
#define BUFFER_HPP

#pragma once



// --------------------------------- Includes ----------------------------------

#include <new>



// =============================== Struct Buffer ===============================

namespace GS {

template <class Type, UInt32 FixBufferCapacity = 1>
struct Buffer {
	Type	FixBuffer[FixBufferCapacity];
	Type*	ptr;
	UInt32	capacity;

	inline Buffer ();
	inline ~Buffer ();

	void	Set (Type* newPtr, UInt32 newCapacity);

	void	EnsureCapacity (UInt32 newCapacity);
};

}	// namespace GS



template <class Type, UInt32 FixBufferCapacity>
inline GS::Buffer<Type, FixBufferCapacity>::Buffer ():
	ptr (FixBuffer),
	capacity (FixBufferCapacity)
{
}


template <class Type, UInt32 FixBufferCapacity>
inline GS::Buffer<Type, FixBufferCapacity>::~Buffer ()
{
	if (ptr != FixBuffer)
		delete [] ptr;
}


template <class Type, UInt32 FixBufferCapacity>
void	GS::Buffer<Type, FixBufferCapacity>::Set (Type* newPtr, UInt32 newCapacity)
{
	if (ptr != FixBuffer)
		delete [] ptr;

	ptr		 = newPtr;
	capacity = newCapacity;
}


template <class Type, UInt32 FixBufferCapacity>
void	GS::Buffer<Type, FixBufferCapacity>::EnsureCapacity (UInt32 newCapacity)
{
   if (newCapacity > capacity) {
	   if (ptr != FixBuffer)
		   delete [] ptr;

	   ptr		= new Type[newCapacity];
	   capacity = newCapacity;
   }
}
// _______________________________ Struct Buffer _______________________________


#endif
