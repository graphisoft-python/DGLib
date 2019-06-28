// *********************************************************************************************************************
// Description:		
// Module:			GSATLib
// Contact person:	
// *********************************************************************************************************************

#ifndef GS_GSAT_UTILITY_HPP
#define GS_GSAT_UTILITY_HPP

#pragma once

// === Includes ========================================================================================================

#include "GSATLibExport.hpp"

// from Geometry
#include "Box2DData.h"

// from GSRoot
#include "Definitions.hpp"
#include "GSException.hpp"
#include "Ref.hpp"


// === Predeclarations =================================================================================================

namespace IO {
	class Location;
}

namespace GSAT {
	class Data;
}

namespace NewDisplay {
	class NativeContext;
	class NativeImage;
}

namespace SL {
	class Transformation2D;
}


// === Function prototypes  ============================================================================================

namespace GSAT {


typedef GS::Ref<Data>		DataRef;
typedef GS::Ref<const Data>	DataConstRef;


class GSATLIB_DLL_EXPORT DataContainer {
public:
	DataContainer ();
	DataContainer (const Box2DData& modelBox, const double pixelsPerMeter);

	bool					Compare (const DataContainer& other) const;

	void					Add (DataRef dataRef);
	DataRef					operator[] (const GS::UIndex index);
	DataConstRef			operator[] (const GS::UIndex index) const;

	const Box2DData&		GetModelBox	() const;
	double					GetWidth	() const;
	double					GetHeight	() const;
	GS::USize				GetSize		() const;

	SL::Transformation2D	GetModelToScreen	() const;

	void					ToContext	(NewDisplay::NativeContext& context) const;

	GSErrCode				Read	(GS::IChannel& ic);
	GSErrCode				Write	(GS::OChannel& oc) const;

private:
	Box2DData				modelBox;
	double					pixelsPerMeter;
	GS::Array<DataRef>		gsatDataArray;

	GSErrCode				WriteHeader (GS::OChannel& oc) const;
};


DECLARE_EXCEPTION_CLASS (BadImageSizeException, GS::GeneralException, Error, GSATLIB_DLL_EXPORT)


GSATLIB_DLL_EXPORT
GSErrCode	Read (GS::IChannel& ic, DataRef& dataRef);

GSATLIB_DLL_EXPORT
GSErrCode	ReadFile (const IO::Location& location, DataContainer& dataContainer);

GSATLIB_DLL_EXPORT
bool	Compare (const IO::Location& leftFile, const IO::Location& rightFile);

GSATLIB_DLL_EXPORT
NewDisplay::NativeImage	ToImage (const DataContainer& dataContainer);

GSATLIB_DLL_EXPORT
void	ExportToPNG (const IO::Location& location, const NewDisplay::NativeImage& img);


}	// namespace GSAT

#endif
