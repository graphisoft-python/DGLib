
// *****************************************************************************
//
//	                          Class IChannelAdapter
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ICHANNELADAPTER_HPP
#define ICHANNELADAPTER_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"

#include "InputBuffer.hpp"



// =========================== Class IChannelAdapter ===========================

namespace IO {

class IO_DLL_EXPORT IChannelAdapter: public GS::IChannel {
private:
	InputBuffer		inputBuffer;	// input buffer for the IChannelAdapter

	IChannelAdapter (const IChannelAdapter& source);				// disabled
	IChannelAdapter&	operator= (const IChannelAdapter& source);	// disabled

protected:
		// Constructors

	explicit IChannelAdapter (GS::IProtocol& ip, char* inputBuffer = nullptr, USize inputBufferCapacity = 0);

		// Protected user interface

	void	SetBinInput	  (InputBuffer::BinInput& bi);
	void	ClearBinInput (void);	// sets binary input which always indicates end-of-input

	InputBuffer::BinInput&	GetBinInput (void) const;

	USize	GetDataSizeInInputBuffer (void) const;

	void	ResetInputBuffer (void);

public:
		// Destructor

   ~IChannelAdapter () {}

		// User interface

	virtual GSErrCode	ReadBin	 (char* destination, USize nOfCharToRead, USize* read = nullptr) override;
	virtual GSErrCode	CopyBin	 (char* destination, USize nOfCharToCopy, USize* copied = nullptr) override;
	virtual GSErrCode	Look	 (UIndex idx, char* c) override;
	virtual	GSErrCode	PushBack (const char* source, USize nOfChar) override;
	virtual	GSErrCode	PushBack (char c) override;
	virtual	GSErrCode	Skip	 (UInt64 nOfCharToSkip, UInt64* skipped = nullptr) override;
	virtual	GSErrCode	DirectInputAccess (USize nOfCharToAccess, char** source, USize* accessible = nullptr) override;

	virtual GSErrCode	GetInputStatus	 (void) const override;
	virtual void		ResetInputStatus (void) override;

	void	EnableInputBuffering	(void);
	void	DisableInputBuffering   (void);
	bool	IsInputBufferingEnabled (void) const;
};

}	// namespace IO
// ___________________________ Class IChannelAdapter ___________________________


#endif
