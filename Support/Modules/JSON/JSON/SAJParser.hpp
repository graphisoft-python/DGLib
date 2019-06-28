
// *****************************************************************************
//
// Declaration of SAJParser class
//
// Module:			JSON
// Namespace:		JSON
// Contact person:	KOVA
//
// *****************************************************************************

#ifndef JSON_SAJPARSER_HPP
#define JSON_SAJPARSER_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "JSON/JSONExport.hpp"
#include "JSON/JSONException.hpp"
#include "JSON/SAJParseHandler.hpp"

#include "IBinaryChannel.hpp"


namespace JSON {

// -------------------------------- SAJParser ----------------------------------

class JSON_API SAJParser {

public:
	SAJParser ();
	~SAJParser ();

	void Parse (GS::IBinaryChannel& source, SAJParseHandler& handler);

private:
	SAJParser& operator= (const SAJParser& source);	// disabled
	SAJParser (const SAJParser& source);			// disabled

};

// ----------------------------- SAJStringParser -------------------------------

class JSON_API SAJStringParser {

public:
	SAJStringParser ();
	~SAJStringParser ();

	void Parse (const GS::UniString& source, SAJParseHandler& handler);

private:
	SAJStringParser& operator= (const SAJStringParser& source);	// disabled
	SAJStringParser (const SAJStringParser& source);			// disabled

};

}

#endif
