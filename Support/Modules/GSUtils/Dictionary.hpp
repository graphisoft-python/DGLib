// ****************************************************************************
// Description:		Dictionary for .po files
// Module:			GSUtils
// Namespace:		GS
// Contact person:	TaB
//
// ****************************************************************************

#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "GSUtilsExport.h"
#include "Definitions.hpp"
#include "HashTable.hpp"
#include "Pair.hpp"
#include "UniString.hpp"

typedef GS::Pair<GS::UniString, GS::UniString>		DictionaryKey;
typedef GS::HashTable<DictionaryKey, GS::UniString>	DictionaryTable;

namespace IO {
	class File;
}

namespace Localization {

class GSUTILS_DLL_EXPORT_CPP Dictionary {
	bool isValid;
	bool inited;
	DictionaryTable	dictionary;
	DictionaryTable missingKeys;
	DictionaryTable foundKeys;
	GS::Array<GS::UniString> errorMessages;

public:
	Dictionary ();
	virtual ~Dictionary ();
	
	GSErrCode	SetPoDictionary (IO::File& inPoDictionary);
	GSErrCode	WriteMissingToPoDictionary (IO::File& outPoDictionary);
	GSErrCode	WriteFoundToPoDictionary (IO::File& outPoDictionary);
	GSErrCode	Translate (const GS::UniString& context, const GS::UniString& inputString, GS::UniString& translated);

	bool		IsValid () const {return isValid;}
	UInt32		GetMissingKeysNum () const {return missingKeys.GetSize ();}
	const GS::Array<GS::UniString>& GetErrorMessages () const;
};

} // namespace GS 

#endif
