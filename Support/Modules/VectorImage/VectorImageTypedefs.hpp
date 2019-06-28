#ifndef VECTORIMAGE_TYPEDEFS_HPP
#define VECTORIMAGE_TYPEDEFS_HPP

#pragma once

#include "GSGuid.hpp"
#include "UniString.hpp"
#include "XMLChannel.hpp"

template <int IndexTypeID>
class GUIDType
{
public:
	GUIDType () {}
	explicit GUIDType  (const GS::Guid& init) : myGuid (init) {}

	inline bool		operator== (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator!= (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator<  (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator>  (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator<= (const GUIDType<IndexTypeID>& rightOp) const;
	inline bool		operator>= (const GUIDType<IndexTypeID>& rightOp) const;

	GSErrCode		Generate (void)
	{
		return myGuid.Generate ();
	}

	inline GSErrCode	Read (GS::IChannel& ic)
	{
		return myGuid.Read (ic);
	};

	inline GSErrCode	Write (GS::OChannel& oc) const
	{
		return myGuid.Write (oc);
	}

	inline GSErrCode	ReadXML (const char* XMLTag, GS::XMLIChannel& ic)
	{
		return ic.ReadXML (XMLTag, myGuid);
	}

	inline GSErrCode	WriteXML (const char* XMLTag, GS::XMLOChannel& oc) const
	{
		return oc.WriteXML (XMLTag, myGuid);
	}

	inline GS::UniString	ToUniString (void) const
	{ 
		return myGuid.ToUniString ();
	}

private:
	GS::Guid			myGuid; 

	friend ULong		GenerateHashValue (const GUIDType<IndexTypeID>& arg);
	friend GSErrCode	Read (GS::IChannel& ic, GUIDType<IndexTypeID>& arg);
	friend GSErrCode	Write (GS::OChannel& oc, const GUIDType<IndexTypeID>& arg);

	GS::Guid&			CastToGuid () { return myGuid; }
	const GS::Guid&		CastToGuid () const { return myGuid; }
};


inline ULong	GenerateHashValue (const GUIDType<1>& arg)
{
	return GenerateHashValue (arg.CastToGuid ());
}


inline GSErrCode	Read (GS::IChannel& ic, GUIDType<1>& arg)
{
	return Read (ic, arg.CastToGuid ());
}


inline GSErrCode	Write (GS::OChannel& oc, const GUIDType<1>& arg)
{
	return Write (oc, arg.CastToGuid ());
}


inline ULong	GenerateHashValue (const GUIDType<2>& arg)
{
	return GenerateHashValue (arg.CastToGuid ());
}


inline GSErrCode	Read (GS::IChannel& ic, GUIDType<2>& arg)
{
	return Read (ic, arg.CastToGuid ());
}


inline GSErrCode	Write (GS::OChannel& oc, const GUIDType<2>& arg)
{
	return Write (oc, arg.CastToGuid ());
}


inline ULong	GenerateHashValue (const GUIDType<3>& arg)
{
	return GenerateHashValue (arg.CastToGuid ());
}


inline GSErrCode	Read (GS::IChannel& ic, GUIDType<3>& arg)
{
	return Read (ic, arg.CastToGuid ());
}


inline GSErrCode	Write (GS::OChannel& oc, const GUIDType<3>& arg)
{
	return Write (oc, arg.CastToGuid ());
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator== (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid == rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator!= (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid != rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator< (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid < rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator<= (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid <= rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator> (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid > rightOp.myGuid;
}


template <int IndexTypeID>
inline bool		GUIDType<IndexTypeID>::operator>= (const GUIDType<IndexTypeID>& rightOp) const
{
	return myGuid >= rightOp.myGuid;
}



namespace PVI {

	typedef GS::Guid	ProfileParameterId;
	typedef GS::Guid	ProfileBuiltInParameterId;
	typedef GUIDType<1> ProfileParameterSetupId;
	typedef GUIDType<2> ProfileAnchorId;
	typedef GUIDType<3> ProfileDimControlToolId;

}


#endif
