#if !defined (SIMPLEPOLYGON2DDATA_H)
#define SIMPLEPOLYGON2DDATA_H

#pragma once

namespace Geometry {

	GEOMETRY_DLL_EXPORT void GEOM_CALL	Cut_ToBox (Int32* nCoords, Coord** cah, const Box2DData* bounds);
}

#endif
