
// *****************************************************************************
//
//                               Class BinIProtocol
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined BINIPROTOCOL_HPP
#define BINIPROTOCOL_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"



// ============================ Class BinIProtocol =============================

namespace IO {

class IO_DLL_EXPORT BinIProtocol: public GS::IProtocol {
private:
	inline GSErrCode	ReadData (GS::IChannel& input, char* destination, USize charCount);

public:
		// User interface

	virtual	GSErrCode	Read (GS::IChannel& input, char& c) override;
	virtual GSErrCode	Read (GS::IChannel& input, unsigned char& c) override;
	virtual GSErrCode	Read (GS::IChannel& input, bool& b) override;
	virtual GSErrCode	Read (GS::IChannel& input, short& s) override;
	virtual GSErrCode	Read (GS::IChannel& input, unsigned short& s) override;
	virtual GSErrCode	Read (GS::IChannel& input, int& i) override;
	virtual GSErrCode	Read (GS::IChannel& input, unsigned int& i) override;
	virtual GSErrCode	Read (GS::IChannel& input, long& l) override;
	virtual GSErrCode	Read (GS::IChannel& input, unsigned long& l) override;
	virtual GSErrCode	Read (GS::IChannel& input, Int64& l) override;
	virtual GSErrCode	Read (GS::IChannel& input, UInt64& l) override;
	virtual GSErrCode	Read (GS::IChannel& input, float& f) override;
	virtual GSErrCode	Read (GS::IChannel& input, double& d) override;
	virtual GSErrCode	Read (GS::IChannel& input, long double& d) override;
	virtual GSErrCode	Read (GS::IChannel& input, char* cStr) override;

	virtual GSErrCode	Read (GS::IChannel& input, GS::Object& obj) override;

	virtual GSErrCode	Read (GS::IChannel& input, GS::Guid& guid) override;
};


IO_DLL_EXPORT extern BinIProtocol	binIProtocol;	// default BinIProtocol instance
													// (BinIProtocol has no internal state so this single instance is sufficient)
}	// namespace IO

// ____________________________ Class BinIProtocol _____________________________


#endif
