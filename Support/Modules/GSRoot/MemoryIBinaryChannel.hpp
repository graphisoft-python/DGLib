
// *****************************************************************************
//
// Declaration of MemoryIBinaryChannel class
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SN
//
// *****************************************************************************

#ifndef GS_MEMORYIBINARYCHANNEL_HPP
#define GS_MEMORYIBINARYCHANNEL_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "IBinaryChannel.hpp"



// --- MemoryIBinaryChannel class ----------------------------------------------

namespace GS {

class GSROOT_DLL_EXPORT MemoryIBinaryChannel : public IBinaryChannel {

// Data members:
private:
	const char*						m_buffer;
	USize							m_bufferSize;
	bool							m_bufferOwnership;
	USize							m_position;
	bool							m_closed;

// Construction / destruction:
public:
			 MemoryIBinaryChannel (const char* buffer, USize bufferSize, bool passBufferOwnership = false);
private:
			 MemoryIBinaryChannel (const MemoryIBinaryChannel&); // Disabled
public:
	virtual	~MemoryIBinaryChannel ();

// Operator overloading:
private:
	const MemoryIBinaryChannel&		operator = (const MemoryIBinaryChannel&); // Disabled

// IBinaryChannel interface implementation:
public:
	virtual USize					Read (char* buffer, USize bufferSize, ReadSomeModeSelector readSomeMode = ReadSomeMode) override;
	virtual UInt64					GetAvailable () const override;
	virtual void					Close () override;

// Implementation:
private:
	void							CheckOpened (const char* sourceFile, GS::UInt32 sourceLine) const;

};

}

#endif // GS_MEMORYIBINARYCHANNEL_HPP
