// *********************************************************************************************************************
// Description:		NURBS class
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	TaB
//
// SG compatible
// *********************************************************************************************************************

#ifndef NURBSCURVE2D_hpp
#define NURBSCURVE2D_hpp

#include	"GSRoot.hpp"
#include	"GeometricDefinitions.h"
#include	"NurbsCurveBase.hpp"
#include	"Coord.h"
#include	"Array.hpp"
#include	"XMLChannel.hpp"
#include	"TM.h"
#include	"ClassInfo.hpp"
#include	"SharedObject.hpp"
#include	"Box2DData.h"

namespace Geometry {
	class PolyId;

	template <class VertexUserData, class EdgeUserData, class ContourUserData, class PolygonUserData> 
	class CustomPolygon2D;
	typedef CustomPolygon2D<PolyId, PolyId, PolyId, PolyId> Polygon2D;

	template <class VertexUserData, class EdgeUserData, class PolygonUserData>
	class CustomPolyline2D;
	typedef CustomPolyline2D<PolyId, PolyId, PolyId> Polyline2D;
}


namespace Geometry {



	class GEOMETRY_DLL_EXPORT NurbsCurve2D : public Geometry::NurbsCurveBase <Coord, Box2DData, Vector>
	{
		DECLARE_ROOT_CLASS_INFO
	public: 

		using CoordinateType = Coord;
		using BoxDataType = Box2DData;
		using VectorType = Vector;

		NurbsCurve2D () = default;
		NurbsCurve2D (const GS::Array<Coord>& controlPoints_, UInt32 degree_);
		NurbsCurve2D (const GS::Array<Coord>& controlPoints_, const GS::Array<double>& knotvector_, const GS::Array<double>& weights_ = GS::Array<double>());

		void	CreateCircle (Coord origo, double r);
		void	CreateArc (Coord begC, Coord endC, double angle);
		void	CreateHalfCircle (Coord begC, Coord endC);

		bool	IsLine () const;
		bool	IsCloserToControlPoints (double eps) const;

		void				SegmentUp (double eps, Polyline2D& resultPolyline, Box2DData* visibleBox = nullptr) const;
		GS::Array<Coord>	SegmentUp (double eps, Box2DData* visibleBox = nullptr, UInt32 depthCounter = 0) const;
		GS::Array<Coord>	IntersectSector (Coord a, Vector b, UInt32 depthCounter = 0) const;
		Polygon2D			GetConvexHull () const;

		virtual GSErrCode Read		(GS::IChannel& ic) override;
		virtual GSErrCode Write		(GS::OChannel& oc) const override;
		virtual GSErrCode ReadXML	(GS::XMLIChannel& ic) override;
		virtual GSErrCode WriteXML	(GS::XMLOChannel& oc) const override;

		GS::UniString DebugControlPolygon () const;
		GS::UniString DebugCurve (Int32 count = 15) const;
		GS::UniString DebugKnotPoints () const;
		GS::UniString DebugBoundingBox () const;
		GS::UniString DebugSegmentedCurve (double eps = 1) const;
	
		static const char* XMLTag_NurbsCurve2D;
	};


}

#endif