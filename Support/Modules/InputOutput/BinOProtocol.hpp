
// *****************************************************************************
//
//                               Class BinOProtocol
//
// Module: IO
// Namespace: IO
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined BINOPROTOCOL_HPP
#define BINOPROTOCOL_HPP

#pragma once


// --------------------------------- Includes ----------------------------------

#include "IOBase.hpp"



// ============================ Class BinOProtocol =============================

namespace IO {

class IO_DLL_EXPORT BinOProtocol: public GS::OProtocol {
public:
		// User interface

	virtual GSErrCode	Write (GS::OChannel& output, char c) override;
	virtual GSErrCode	Write (GS::OChannel& output, unsigned char c) override;
	virtual GSErrCode	Write (GS::OChannel& output, bool b) override;
	virtual GSErrCode	Write (GS::OChannel& output, short s) override;
	virtual GSErrCode	Write (GS::OChannel& output, unsigned short s) override;
	virtual GSErrCode	Write (GS::OChannel& output, int i) override;
	virtual GSErrCode	Write (GS::OChannel& output, unsigned int i) override;
	virtual GSErrCode	Write (GS::OChannel& output, long l) override;
	virtual GSErrCode	Write (GS::OChannel& output, unsigned long l) override;
	virtual GSErrCode	Write (GS::OChannel& output, Int64 l) override;
	virtual GSErrCode	Write (GS::OChannel& output, UInt64 l) override;
	virtual GSErrCode	Write (GS::OChannel& output, float f) override;
	virtual GSErrCode	Write (GS::OChannel& output, double d) override;
	virtual GSErrCode	Write (GS::OChannel& output, long double d) override;
	virtual GSErrCode	Write (GS::OChannel& output, const void* p) override;
	virtual GSErrCode	Write (GS::OChannel& output, const char* cStr) override;

	virtual GSErrCode	Write (GS::OChannel& output, const GS::Object& obj) override;

	virtual GSErrCode	Write (GS::OChannel& output, const GS::Guid& guid) override;
};


IO_DLL_EXPORT extern BinOProtocol	binOProtocol;	// default BinOProtocol instance
													// (BinOProtocol has no internal state so this single instance is sufficient)
}	// namespace IO

// ____________________________ Class BinOProtocol _____________________________


#endif
