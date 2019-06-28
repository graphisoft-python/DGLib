#ifndef	STRETCHDATA_HPP	
#define	STRETCHDATA_HPP	

#pragma once

#include "VectorImageExport.h"
#include "ClassInfo.hpp"
#include "Channel.hpp"
#include "XMLChannel.hpp"
#include "TRANMAT.h"

namespace PVI
{
	
class VI_DLL_CLASS_EXPORT StretchData : public GS::Object
{
	DECLARE_CLASS_INFO

private:
	bool			hasHorizontalZone;
	double			horizontalZone1;
	double			horizontalZone2;
	bool			hasVericalZone;
	double			verticalZone1;
	double			verticalZone2;

	GSErrCode	ReadVersion1 (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

public: 
	StretchData ();
	bool			HasHorizontalZone () const;
	bool			HasVerticalZone () const;
	double			GetHorizontalZoneMax () const;
	double			GetHorizontalZoneMin () const;
	double			GetVerticalZoneMax () const;
	double			GetVerticalZoneMin () const;
	double			GetStretchZoneWidth () const;
	double			GetStretchZoneHeight () const;
	void			GetHorizontalZone (double& zoneMin, double& zoneMax) const;
	void			GetVerticalZone (double& zoneMin, double& zoneMax) const;

	void SetHorizontalZone (double newMin, double newMax);
	void SetVerticalZone (double newMin, double newMax);
	void RemoveHorizontalZone ();
	void RemoveVerticalZone ();

	void Clear ();
	bool IsEqual (const StretchData& other) const;
	bool operator== (const StretchData& other) const;
	void Transform (const TRANMAT& transformer);
	
	GSErrCode	Write (GS::OChannel& channel) const override;
	GSErrCode	Read (GS::IChannel& channel) override;
	GSErrCode	WriteXML (GS::XMLOChannel& channel) const;
	GSErrCode	ReadXML (GS::XMLIChannel& channel);
};

}
#endif
