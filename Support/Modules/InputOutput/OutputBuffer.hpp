
// *****************************************************************************
//
//                              Class OutputBuffer
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined OUTPUTBUFFER_HPP
#define OUTPUTBUFFER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "Array.hpp"



// ============================ Class OutputBuffer =============================

namespace IO {

class IO_DLL_EXPORT OutputBuffer {
public:
	class BinOutput;

private:
	GS::ArrayFB<char*, 4> bufferPages;		// stores buffer pages
	USize				  bufferPageSize;	// size of a buffer page in characters

	UIndex		writePage;			// buffer page used for the next write (Put) operation
	char*		writePtr;			// pointer used for the next write (Put) operation (it can be nullptr when buffering is disabled or no buffer has been allocated yet)
	char*		writeEndPtr;		// limit for the writePtr, it points one character after the writePage (it can be nullptr when buffering is disabled or no buffer has been allocated yet)

	bool		isOffsetted;		// indicates whether is buffer in the offsetted mode
	char*		savedWritePtr;		// stores the writePtr when buffer is in offsetted mode

	GS::ArrayFB<UIndex, 8>	marks;	// stores position markers

	BinOutput*	binOutput;			// output (destination) of the binary data
	UInt64      writtenBytes;       // number of bytes sent to BinOutput

	bool		isBufferingEnabled;	// indicates whether is the buffering enabled

	GSErrCode	status;				// state of the object


	OutputBuffer (const OutputBuffer& source);				// disabled
	OutputBuffer&	operator= (const OutputBuffer& source);	// disabled

	void	InitializeBuffer   (void);
	void	ReinitializeBuffer (void);
	void	DeleteBuffer	   (void);

	void	WriteData (const char* source, USize nOfCharToWrite);

	void	CopyToBuffer (const char* source, USize nOfCharToCopy);

	USize	GetFreeSpace	 (void) const;
	UIndex	GetWritePosition (void) const;

public:
		// Constants

	static const USize	DefaultBufferPageSize;	// default size of a buffer page in characters

		// Constructors

	OutputBuffer (BinOutput* binOutput = nullptr, USize bufferPageSize = 0);
   ~OutputBuffer ();

		// User interface

	inline GSErrCode	GetStatus (void) const;
	void				ResetOutputStatus (void);

	void				SetBinOutput (BinOutput& newBinOutput);
	BinOutput&			GetBinOutput (void) const;

	void				ClearBinOutput (void);	// sets default binary output which always indicates that output is full

	GSErrCode			Put (const char* source, USize nOfCharToPut);
	inline GSErrCode	Put (char c);

	inline UInt64       GetWrittenBytes (void) const;

	GSErrCode			Flush		 (void);
	void				ClearContent (void);
	void				Reset		 (void);

	bool				IsEmpty		 (void) const;
	USize				GetDataSize	 (void) const;

	GSErrCode			PushMark	 (void);
	GSErrCode			PopMark		 (void);
	USize				GetOffset	 (void) const;
	void				ResetOffset	 (void);
	bool				IsInMarkMode (void) const;

	GSErrCode			DirectAccess (UIndex startPosition, char** output, USize* accessibleDataSize);

	void				EnableBuffering	   (void);
	void				DisableBuffering   (void);
	bool				IsBufferingEnabled (void) const;

		// Types

	class IO_DLL_EXPORT BinOutput {		// destination of the binary data for the output buffer
	public:
		virtual GSErrCode	InternalWrite (const char* source, USize nOfCharToWrite, USize* written);
	};
};

}	// namespace IO



inline GSErrCode	IO::OutputBuffer::GetStatus (void) const
{
	return status;
}


inline UInt64	IO::OutputBuffer::GetWrittenBytes (void) const
{
	return writtenBytes;
}


inline GSErrCode	IO::OutputBuffer::Put (char c)
{
	return Put (&c, sizeof (char));
}
// ____________________________ Class OutputBuffer _____________________________


#endif
