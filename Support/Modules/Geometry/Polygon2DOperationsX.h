// *****************************************************************************
// 2D POLYGON OPERATIONS
// Combination of the struct and the callback functions
//
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

#if !defined (POLYGON2DOPERATIONSX_H)
#define POLYGON2DOPERATIONSX_H

#pragma once

#include "VA.hpp"

#include "GeometricDefinitions.h"
#include "Point2DData.h"
#include "Box2DData.h"
#include "HalfPlane2DData.h"
#include "Plane3DData.h"
#include "Polygon2DOperations.h"

namespace Geometry {

DECLARE_EXCEPTION_CLASS (SelfIntersectingPGPolygonException,	GeometryIllegalArgumentException,			  PGSelfintersect,	GEOMETRY_DLL_EXPORT)


// Whole polygon operations

GEOMETRY_DLL_EXPORT double	GEOM_CALL	PGXPolyAreaExt (
					const PGPOLYEXT*	polygon,
					double*				thole)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyRemoveHolesExt (
					const PGPOLYEXT*	polygon,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXIsPolyRegularExt (
					const PGPOLYEXT*	originalPolygon,
					bool*				isPolyRegular)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException,
						GS::AbortException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyMakeRegular2Ext (
					const PGPOLYEXT*		originalPolygon,
					PGRESPOLYEXT*			newPolygons,
					bool					resolveSelfInters,
					GS::AbortInterfaceBase*	breaker = nullptr,
					PGRegulHoleHandling		holeHandling = ThrowInvalidHoles,
					PGRelPolyPosExt*		status = nullptr,
					PolyRegularizationMode	mode = PolyRegularizationMode_Default)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException,
						GS::AbortException));

// Contour operations

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyResizeContourExt (
					const PGPOLYEXT*	originalPolygon,
					UIndex				contourIdx,
					double				offset,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

// Vertex operations

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyMoveVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				movedVertexIdx,
					const Coord&		newVertexPosition,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyGetMaxVertexFilletExt (
					const PGPOLYEXT*	poly,
					UIndex				filletedVertexIdx,
					double*				maxFilletRadius)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyFilletVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				filletedVertexIdx,
					double				filletRadius,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyFilletContourExt (
					const PGPOLYEXT*	polygon,
					UIndex				filletedContourIdx,
					double				filletRadius,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyChamferVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				chamferedVertexIdx,
					double				chamferRadius,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyChamferContourExt (
					const PGPOLYEXT*	polygon,
					UIndex				chamferedContourIdx,
					double				chamferRadius,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

// Edge operations

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyInsertVertexExt (
					const PGPOLYEXT*	polygon,
					UIndex				breakedEdgeIdx,
					const Coord&		newVertexPosition,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolySetEdgeAngleExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					double				viewAngle,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyOffsetEdgeExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					double				offset,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyOffsetEdgeFixAreaExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					UIndex				vertIdx,
					double				offset,
					double				area,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

//C-018
GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyDeleteEdgeExt (
					const PGPOLYEXT*	polygon,
					UIndex				edgeIdx,
					bool*				deleteAble,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

// Polygon - Point operations

GEOMETRY_DLL_EXPORT PGPositionExt GEOM_CALL	PGXCoordInPolyExt (
					const PGPOLYEXT*	polygon,
					const Coord*		p,
					bool				mainContOnly)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

// Polygon - Point operations with arcs

GEOMETRY_DLL_EXPORT PGPositionExt GEOM_CALL	PGXPoint2DPosition (
					const Geometry::PGPOLYEXT*	polygon,
					const Coord*				p,
					bool						mainContOnly)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

// Polygon - Sector operations

GEOMETRY_DLL_EXPORT PGPositionExt	GEOM_CALL PGXSegmentInPolyExt (
					const PGPOLYEXT*		polygon,
					Coord*					bp,
					Coord*					ep,
					bool					complement,
					PGRESSECTOREXT*			newSectors,
					GS::AbortInterfaceBase*	breaker = nullptr)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException,
						GS::AbortException));

// Polygon - polygon operations

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyPositionExt (
					const PGPOLYEXT*			polygon1,
					const PGPOLYEXT*			polygon2,
					PGRelPolyPosExt*			status,
					GS::AbortInterfaceBase*		breaker = nullptr)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException,
						GS::AbortException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyUnionExt (
					const PGPOLYEXT*	polygon1,
					const PGPOLYEXT*	polygon2,
					PGRESPOLYEXT*		newPolygons,
					PGRelPolyPosExt*	status)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException,
						GS::AbortException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyIntersectionExt (
					const PGPOLYEXT*	polygon1,
					const PGPOLYEXT*	polygon2,
					PGRESPOLYEXT*		newPolygons,
					PGRelPolyPosExt*	status)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException,
						GS::AbortException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyDifferenceExt (
					const PGPOLYEXT*			polygon1,
					const PGPOLYEXT*			polygon2,
					PGRESPOLYEXT*				newPolygons,
					PGRelPolyPosExt*			status,
					GS::AbortInterfaceBase*		breaker = nullptr)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException,
						GS::AbortException));

GEOMETRY_DLL_EXPORT void	GEOM_CALL	PGXPolyCreateCommonEdgeSectionsExt (
					const PGPOLYEXT*	polygon1,
					const PGPOLYEXT*	polygon2,
					PGRESPOLYEXT*		newPolygons)

					CAN_THROW ((
						GS::OutOfMemoryException,
						GeometryException));

}

#endif
