#ifndef EDGE_OVERRIDEDATA_HPP__
#define EDGE_OVERRIDEDATA_HPP__

#pragma once

#include "Channel.hpp"
#include "XMLChannel.hpp"
#include "ClassInfo.hpp"
#include "Object.hpp"

#include "VectorImageExport.h"

namespace PVI { // ProfileVectorImage


class VI_DLL_CLASS_EXPORT EdgeOverrideData : public GS::Object 
{
	DECLARE_CLASS_INFO

public:
	EdgeOverrideData ();
	EdgeOverrideData (short	inInnerLineType, short inOuterLineType, short inInnerPen, short inOuterPen, bool inOverrideSectionLines);

	bool operator== (const EdgeOverrideData& other) const;
	bool operator!= (const EdgeOverrideData& other) const;

	short	GetInnerLineType () const;
	short	GetOuterLineType () const;
	short	GetInnerPen () const;
	short	GetOuterPen () const;
	bool	GetOverrideSectionLines () const;

	virtual GSErrCode	Read (GS::IChannel& ic) override;
	virtual GSErrCode	Write (GS::OChannel& oc) const	override;
	GSErrCode	ReadXML (GS::XMLIChannel& ic);
	GSErrCode	WriteXML (GS::XMLOChannel& oc) const;

private:
	short		innerLineType;
	short		outerLineType;
	short		innerPen;
	short		outerPen;
	bool		overrideSectionLines;

	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;
};

}

#endif
