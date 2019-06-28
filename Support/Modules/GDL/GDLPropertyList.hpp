// *********************************************************************************************************************
// Description:		GDLPropertyList.hpp
//
// Module:			GDL
// Namespace:		GDL
// Contact person:	HK
//
// *********************************************************************************************************************

#ifndef GDLPROPERTYLIST_HPP
#define GDLPROPERTYLIST_HPP

#include "PropertyList.hpp"


namespace GDL {

template<class UserDataType>
class PropertyList : public GS::PropertyList<UserDataType>
{
public:
	void Create (ULong nr);

	GSHandle WriteToAddParHandle () const;
	void ReadFromAddParHandle (GSConstHandle addPar);
};

}


#include "GDLPropertyListImp.hpp"

#endif
