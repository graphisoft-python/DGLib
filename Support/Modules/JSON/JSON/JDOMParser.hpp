
// *****************************************************************************
//
// Declaration of JDOMParser class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_JDOMPARSER_HPP
#define JSON_JDOMPARSER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"
#include "JSON/JSONException.hpp"
#include "JSON/Value.hpp"

#include "IBinaryChannel.hpp"


namespace JSON {

// -------------------------------- JDOMParser ---------------------------------

class JSON_API JDOMParser {

public:
	JDOMParser ();
	~JDOMParser ();

	ValueRef Parse (GS::IBinaryChannel& source);

private:
	JDOMParser& operator= (const JDOMParser& source);	// disabled
	JDOMParser (const JDOMParser& source);				// disabled

};

// ------------------------------ JDOMStringParser ------------------------------

class JSON_API JDOMStringParser {

public:
	JDOMStringParser ();
	~JDOMStringParser ();

	ValueRef Parse (const GS::UniString& source);

private:
	JDOMStringParser& operator= (const JDOMStringParser& source);	// disabled
	JDOMStringParser (const JDOMStringParser& source);				// disabled

};


}

#endif
