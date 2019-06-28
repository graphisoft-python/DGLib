
// *****************************************************************************
//
//	                          Class MemoryIChannel
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined MEMORYICHANNEL_HPP
#define MEMORYICHANNEL_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "IChannelAdapter.hpp"



// =========================== Class MemoryIChannel ============================

namespace IO {

class IO_DLL_EXPORT MemoryIChannel: public IChannelAdapter,
									private InputBuffer::BinInput
{
public:
	enum OwnershipType { OriginalOwnership, PassOwnership };

private:
	const char*		source;		// source of the data
	USize			length;		// length of the source in characters
	bool			ownsSrc;	// specifies whether this object owns the source
	UIndex			srcPos;		// position in the source

	MemoryIChannel (const MemoryIChannel& source);				// disabled
	MemoryIChannel&	operator= (const MemoryIChannel& source);	// disabled

	void	Init (void);
	void	Init (const char* sourceData, USize sourceDataLength, OwnershipType ot);

	virtual GSErrCode	InternalRead (char* destination, USize nOfCharToRead, USize* read) override;

public:
		// Types

	struct InputBuffer {
		char* buffer;
		USize capacity;

		InputBuffer (): buffer (nullptr), capacity (0) {}
		InputBuffer (char* buffer, USize capacity): buffer (buffer), capacity (capacity) {}
	};

		// Constructors

	MemoryIChannel (const InputBuffer& inputBuffer = InputBuffer ());
	MemoryIChannel (const char* sourceData, USize sourceDataLength, OwnershipType ot = OriginalOwnership, const InputBuffer& inputBuffer = InputBuffer ());
   ~MemoryIChannel ();

		// User interface

	void			SetSource	  (const char* sourceData, USize sourceDataLength, OwnershipType ot = OriginalOwnership);
	const char*		GetSource	  (void) const;
	USize			GetDataLength (void) const;
	void			RemoveSource  (void);
	void			ResetSource	  (void);

	virtual GSErrCode	GetInputPosition (UInt64* position) const override;
	virtual GSErrCode	GetAvailable     (UInt64* available) const override;

	virtual void	SetDefaultInputProtocol (void) override;
};

}	// namespace IO
// ___________________________ Class MemoryIChannel ____________________________


#endif
