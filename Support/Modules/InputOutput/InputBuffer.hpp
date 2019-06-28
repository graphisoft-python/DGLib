
// *****************************************************************************
//
//                               Class InputBuffer
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined INPUTBUFFER_HPP
#define INPUTBUFFER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"



// ============================= Class InputBuffer =============================

namespace IO {

class IO_DLL_EXPORT InputBuffer {
public:
	class IO_DLL_EXPORT BinInput {	// source of the binary data for the input buffer
	public:
		virtual GSErrCode	InternalRead (char* destination, USize nOfCharToRead, USize* read);
	};

private:
	static BinInput		defaultBinInput;	// default binary input which always indicates end-of-input

	char*		buffer;				// points to the buffer, it can be nullptr to allow lazy memory allocation (and also when object's status is ErrMemoryFull)
	USize		bufferCapacity;		// capacity of the buffer
	bool		ownsBuffer;			// true if the InputBuffer owns the buffer
	USize		capacityLimit;		// maximum allowed capacity of the buffer

	UIndex		dataPos;			// index of the first character in the buffer
	USize		dataSize;			// size of the data stored in the buffer in characters

	BinInput*	binInput;			// input (source) of the binary data

	bool		isBufferingEnabled;	// indicates whether is the buffering enabled

	double		pushBackRatio;		// ratio (in range of [0, 1]) of the PushBack block in the buffer
	USize		readBlockLength;	// readBlockLength = bufferCapacity	* (1 - pushBackRatio)
									// determines default length of the read block in normal circumstances;
									// remaining space is reserved for the PushBack () operation,
									// but when it is necessary a Look method can consume the
									// PushBack block and PushBack method can consume the Read block
									// (when it is not possible, because buffer is full, reallocation
									// will be performed)

	GSErrCode	status;				// state of the object
	GSErrCode	delayedStatus;		// state delayed because there's valid data in buffer


	InputBuffer	(const InputBuffer& source);				// disabled
	InputBuffer&	operator= (const InputBuffer& source);	// disabled

	USize			ReadData (char* destination, USize minCharCount, USize maxCharCount);

	bool			ReadDataToBuffer	   (USize minSizeToRead);
	bool			ReallocBuffer		   (USize newCapacity);
	void			ComputeReadBlockLength (void);
	UIndex			CopyDataFromBuffer	   (char* destination, USize nOfCharToCopy);
	inline void		MoveDataFromBuffer	   (char* destination, USize nOfCharToMove);
	USize			GetRest				   (char* destination, USize nOfCharToGet);

	inline char*	GetBuffer (void);

	char*			AllocateBuffer (USize charCount);

public:
		// Constants

	static const USize		DefaultInitialCapacity;	// default initial buffer capacity
	static const USize		MinInitialCapacity;		// minimum initial buffer capacity
	static const USize		MaxInitialCapacity;		// maximum initial buffer capacity
	static const double		DefaultPushBackRatio;	// default ratio of PushBack area

		// Constructors

	InputBuffer (BinInput* bi		  = nullptr,
				 char*	   initBuf	  = nullptr,
				 USize	   initBufCap = 0,
				 USize	   capLimit	  = 0,
				 double	   pbRatio	  = DefaultPushBackRatio);
   ~InputBuffer ();

		// User interface

	inline GSErrCode	GetStatus	 (void) const;
	void				ResetInputStatus (void);
	void				ResetEOI	 (void);

	void				SetBinInput  (BinInput& bi);
	BinInput&			GetBinInput  (void) const;

	void				ClearBinInput (void);	// sets binary input which always indicates end-of-input

	GSErrCode			Get			 (char* c);
	inline GSErrCode	Get			 (char* destination, USize nOfCharToGet, USize* gotten);

	GSErrCode			Copy		 (char* destination, USize nOfCharToCopy, USize* copied);

	GSErrCode			Look		 (char* c);
	GSErrCode			Look		 (UIndex idx, char* c);

	GSErrCode			PushBack	 (char c);
	GSErrCode			PushBack	 (const char* source, USize nOfCharToPushBack);

	GSErrCode			Skip		 (UInt64 nOfCharToSkip, UInt64* skipped);

	void				ClearContent (void);
	void				Reset		 (void);

	inline bool			IsEOI		 (void);
	inline bool			IsEmpty		 (void) const;
	inline USize		GetDataSize	 (void) const;

	GSErrCode			DirectAccess (USize nOfCharToAccess, char** source, USize* accessible);

	void				EnableBuffering	   (void);
	void				DisableBuffering   (void);
	bool				IsBufferingEnabled (void) const;
};

}	// namespace IO



inline GSErrCode	IO::InputBuffer::GetStatus (void) const
{
	return status;
}


inline bool		IO::InputBuffer::IsEOI (void)
{
	if (dataSize > 0)
		return false;

	return (!ReadDataToBuffer (1));
}


inline bool		IO::InputBuffer::IsEmpty (void) const
{
	return (dataSize == 0);
}


inline USize	IO::InputBuffer::GetDataSize (void) const
{
	return dataSize;
}


	// MoveDataFromBuffer moves nOfCharToMove number of characters to destination
	// from the buffer. dataPos and dataSize will be adjusted accordingly.
	// This method doesn't perform any check so nOfCharToMove must be less or
	// equal than dataSize.

inline void		IO::InputBuffer::MoveDataFromBuffer (char* destination, USize nOfCharToMove)
{
	dataPos	= CopyDataFromBuffer (destination, nOfCharToMove);
	dataSize -= nOfCharToMove;
}


	// inline part of the Get method

inline GSErrCode	IO::InputBuffer::Get (char* destination, USize nOfCharToGet, USize* gotten)
{
	DBASSERT (!(destination == nullptr && nOfCharToGet != 0));
	DBASSERT (gotten != nullptr);

	if (nOfCharToGet <= dataSize) {		// OK: all the data can be moved from the buffer
		MoveDataFromBuffer (destination, nOfCharToGet);
		*gotten = nOfCharToGet;
	} else {
		*gotten = GetRest (destination, nOfCharToGet);
	}

	return status;
}
// _____________________________ Class InputBuffer _____________________________


#endif
