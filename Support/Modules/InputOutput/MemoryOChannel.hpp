
// *****************************************************************************
//
//	                          Class MemoryOChannel
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined MEMORYOCHANNEL_HPP
#define MEMORYOCHANNEL_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "OChannelAdapter.hpp"



// =========================== Class MemoryOChannel ============================

namespace IO {

class IO_DLL_EXPORT MemoryOChannel: public OChannelAdapter,
									private OutputBuffer::BinOutput
{
public:
	enum OwnershipType { OriginalOwnership, PassOwnership, GrantOwnership };
	enum MemoryAllocationMode { BMAllocation, CppAllocation };

private:
	char*	destination;	// destination buffer which receives the data
	USize	size;			// size of the data stored in the destination buffer in characters
	USize	sizeLimit;		// maximum allowed size of the data in characters
	USize	capacity;		// actual capacity of the destination buffer (in characters)
	bool	ownsDest;		// specifies whether this object owns the destination buffer
	MemoryAllocationMode memoryAllocationMode;	// specifies whether to use BM functions or native C++ memory operators for the memory allocation and deletion

	MemoryOChannel (const MemoryOChannel& source);				// disabled
	MemoryOChannel&	operator= (const MemoryOChannel& source);	// disabled

	GSErrCode	Init (USize initialCapacity, USize maxSize);
	void		Init (char* destBuffer, USize destBufferSize, USize maxSize, OwnershipType ot);

	virtual GSErrCode	InternalWrite (const char* source, USize nOfCharToWrite, USize* written) override;

	char*	AllocateMemory (UInt32 size);
	void	DeleteMemory   (char* ptr);

public:
		// Constructors

	explicit MemoryOChannel (MemoryAllocationMode memoryAllocationMode);
	explicit MemoryOChannel (USize initialCapacity = 0, USize maxSize = 0, MemoryAllocationMode memoryAllocationMode = BMAllocation);
	MemoryOChannel (char* destBuffer, USize destBufferSize, USize maxSize = 0, OwnershipType ot = OriginalOwnership, MemoryAllocationMode memoryAllocationMode = BMAllocation);
   ~MemoryOChannel ();

		// User interface

	GSErrCode	GetStatus (void) const;

	GSErrCode	SetDestination (USize initialCapacity = 0, USize maxSize = 0);
	void		SetDestination (char* destBuffer, USize destBufferSize, USize maxSize = 0, OwnershipType ot = OriginalOwnership);
	char*		GetDestination (OwnershipType ot = OriginalOwnership);
	const char*	GetDestination (void) const;
	USize		GetDataSize	   (void) const;
	GSErrCode   SetDataSize    (USize newSize);

	virtual GSErrCode   GetOutputPosition (UInt64* pos) const override;

	virtual	void	SetDefaultOutputProtocol (void) override;
};

}	// namespace IO
// ___________________________ Class MemoryOChannel ____________________________


#endif
