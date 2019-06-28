// *****************************************************************************
// Spline and its operations.
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

#if !defined (SPLINE_H)
#define SPLINE_H

#pragma once

#include "GeometricDefinitions.h"
#include "Box2DData.h"
#include "Circle2DData.h"
#include "GenArc2DData.h"

CmpResult CmpDoubles (const void	*p1,
					  const void	*p2);


namespace Geometry {

struct DirType;

class BezierDetails;


/*							CALCULATIONS ON SPLINES						*/

GEOMETRY_DLL_EXPORT void GEOM_CALL CubicToBezier (
						Coord 	*pco0, 				/* sm007 */
						Coord 	*pco1,
						Coord 	*pco2,
						Coord 	*pco3,
						const double  *x0,
						const double  *y0,
						const double  *x1,
						const double  *y1,
						const double  *x2,
						const double  *y2,
						const double  *x3,
						const double  *y3);

GEOMETRY_DLL_EXPORT void GEOM_CALL BezierToCubic (
						const Coord 	*pco0, 				/* sm007 */
						const Coord 	*pco1,
						const Coord 	*pco2,
						const Coord 	*pco3,
						double  *x0,
						double  *y0,
						double  *x1,
						double  *y1,
						double  *x2,
						double  *y2,
						double  *x3,
						double  *y3);

GEOMETRY_DLL_EXPORT void GEOM_CALL CalcSplineCoeffs ( bool opened,
						bool cyclic,
						Int32 	n,
						double  **x0,
						double  **y0,
						double  **x1,
						double  **y1,
						double  **x2,
						double  **y2,
						double  **x3,
						double  **y3,
						double  xtf,
						double  ytf,
						double  xtl,
						double  ytl);

GEOMETRY_DLL_EXPORT void GEOM_CALL GetBezierDirCoords (const Coord	*pCo,
						 const DirType	*pDir,
						 Coord			*cPrev,
						 Coord			*cNext);

GEOMETRY_DLL_EXPORT void GEOM_CALL SetBezierDirType (const Coord	*pCo,
					   DirType		*pDir,
					   const Coord	*cPrev,
					   const Coord	*cNext);

GEOMETRY_DLL_EXPORT void GEOM_CALL SetBezierDirType (const Coord	&pCo,
						 DirType		&pDir,
						 const Coord	&cPrev,
						 const Coord	&cNext);

GEOMETRY_DLL_EXPORT bool GEOM_CALL CalcSpline (	const Coord* const	coords,				/* sm009 */
												DirType* const		dirs,
												const Int32			nCo,
												const bool			closed);

GEOMETRY_DLL_EXPORT double GEOM_CALL SplineLen (
								Int32			nCo,
								const Coord		*coords,			/* sm175 */
								const DirType	*dirs,
								double 			a,
								double 			b);

GEOMETRY_DLL_EXPORT double GEOM_CALL SplineLen (
								const BezierDetails&	bezDet,
								double 					a,
								double 					b);

GEOMETRY_DLL_EXPORT double GEOM_CALL Spline_ax (
								Int32			nCo,
								const Coord		*coords,			/* sm175 */
								const DirType	*dirs,
								double 			a,
								double			givenLen,
								bool			closed);

GEOMETRY_DLL_EXPORT double GEOM_CALL Spline_ax (
								const BezierDetails&	bezDet,
								double 					a,
								double					givenLen,
								bool					closed);


GEOMETRY_DLL_EXPORT double GEOM_CALL GetSplineParam (double   	x0,
						double   	y0,
						double   	x1,
						double   	y1,
						double   	x2,
						double   	y2,
						double   	x3,
						double   	y3,
						const Coord	*cc);

GEOMETRY_DLL_EXPORT double	GEOM_CALL GetSplineSegmCloseCoord (Int32					segment,
															   Int32					nCoords,
															   const Coord				*coords,
															   const Geometry::DirType	*dirs,
															   const Coord				*co,
															   Coord	  				*prCo);

GEOMETRY_DLL_EXPORT double GEOM_CALL GetSplineCloseCoord (
								Int32			nCoords,
								const Coord		*coords,
								const DirType	*dirs,
								bool			closed,
								const Coord		*co,
								Coord	  		*prCo);

GEOMETRY_DLL_EXPORT double GEOM_CALL GetSplineCloseCoord (
								const BezierDetails&	bezDet,
								const Coord				*co,
								Coord	  				*prCo);

GEOMETRY_DLL_EXPORT double GEOM_CALL GetSplineMaxDist (const Coord			*coords,		/*hot00.02.22 - dev. for Tillberg */
						  const DirType		*dirs,
						  Int32			segment,
						  Coord			**cc,
						  Int32			nCoords);

GEOMETRY_DLL_EXPORT void  GEOM_CALL BezierPoints (
					const Coord*	pCoords,
					const DirType*	pDirs,
					Int32		ibeg,
					Int32		iend,				/* sm012 */
					Coord 		*bezp);			// array of 4 Coords required!

GEOMETRY_DLL_EXPORT void  GEOM_CALL BezierPoints4 (
					const Coord		*coords,			/* sm007 */
					const DirType		*dirs,
					Int32		ibeg,
					Int32		iend,				/* sm012 */
					Coord 		*p0,
					Coord 		*p1,
					Coord 		*p2,
					Coord 		*p3);

GEOMETRY_DLL_EXPORT void  GEOM_CALL BezierPoints4 (
					const BezierDetails&	bezDet,
					Int32					ibeg,
					Coord 					*p0,
					Coord 					*p1,
					Coord 					*p2,
					Coord 					*p3);

GEOMETRY_DLL_EXPORT Coord GEOM_CALL GetSplineVal (
					Int32			nCoords,
					const Coord*	pCoords,
					const DirType*	pDirs,
					double 			t);

GEOMETRY_DLL_EXPORT Coord GEOM_CALL GetSplineVal (
					const BezierDetails&	bezDet,
					double 			t);

GEOMETRY_DLL_EXPORT Vector2d GEOM_CALL GetSplineTan (
					Int32			nCo,
					const Coord*	coords,
					const DirType*	dirs,
					double 			t,
					bool			forw,
					bool			norm);

GEOMETRY_DLL_EXPORT Vector2d GEOM_CALL GetSplineTan (
					const BezierDetails&	bezDet,
					double 					t,
					bool					forw,
					bool					norm);

GEOMETRY_DLL_EXPORT void GEOM_CALL SegmentToBox (Box2DData	*boundbox,			/* sm009 */
					  double	x0,
					  double	y0,
					  double	x1,
					  double	y1,
					  double	x2,
					  double	y2,
					  double	x3,
					  double	y3,
					  double	a,
					  double	b);					/* sm012 */

GEOMETRY_DLL_EXPORT Box2DData GEOM_CALL SplineToBox (const BezierDetails&	bezier);

GEOMETRY_DLL_EXPORT void GEOM_CALL GetSplineDMinDMax (
						const double* const    p,
						const double		   a,
						const double		   b,
						const Coord&		   fa,
						const Coord&		   fb,
						double*				   dmin,
						double*				   dmax);

GEOMETRY_DLL_EXPORT bool	SameSplines (
						const BezierDetails&	bezDet1,
						const BezierDetails&	bezDet2);

GEOMETRY_DLL_EXPORT Int32	XSplineLine (
					Int32					nCo,
					const Coord				*coords,
					const Geometry::DirType	*dirs,
					bool					closed,
					Int32					segment,			/* sm122 */
					const Sector			*s,
					double					**hSect);

GEOMETRY_DLL_EXPORT Int32	XSplineLine (
					const BezierDetails&	bezDet,
					Int32					segment,			/* sm122 */
					const Sector			*s,
					double					**hSect);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XSplineSector (
						Int32					nCo,
						const Coord				*coords,
						const Geometry::DirType	*dirs,
						bool					closed,
						const Sector			*s,
						double					**hSect);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XSplineSector (
						const BezierDetails&	bezDet,
						const Sector			*s,
						double					**hSect);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL	XSplineCircle  (
						Int32 					nCo,
						const Coord				*coords,
						const Geometry::DirType	*dirs,
						bool					closed,
						Int32					segment,											/* sm122 */
						const Circle			*c,
						bool					elliptic,				/* ellipszis */				/* sm121 */
						double					angle,					/* tengely szoge */
						double					ratio,					/* == a/b */
						double					**hSect);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL	XSplineCircle  (
						const BezierDetails&	bezDet,
						Int32					segment,											/* sm122 */
						const Circle			*c,
						bool					elliptic,				/* ellipszis */				/* sm121 */
						double					angle,					/* tengely szoge */
						double					ratio,					/* == a/b */
						double					**hSect);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XSplineGenArc  (
						Int32					nCo,
						const Coord				*coords,
						const Geometry::DirType	*dirs,
						bool					closed,
						const	GenArc			*arcT,
						double					**hSect);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XSplineGenArc  (
						const BezierDetails&	bezDet,
						const	GenArc			*arcT,
						double					**hSect);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XSplineSpline (
								 Int32 				nCo1,
								 const Coord		*coords1,
								 const DirType		*dirs1,
								 bool				closed1,
								 Int32 				nCo2,
								 const Coord		*coords2,
								 const DirType		*dirs2,
								 bool				closed2,
								 double				**hSect1,
								 double				**hSect2,
								 Int32				limitedToSegment_1 = 0,
								 Int32				limitedToSegment_2 = 0);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XSplineSpline (
								 const BezierDetails&	bezDet1,
								 const BezierDetails&	bezDet2,
								 double					**hSect1,
								 double					**hSect2);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL	SplineSegNormTangPoints (
								Int32 			nCo,
								const Coord		*coords,
								const DirType	*dirs,
								Int32			segment,
								const Coord		*baseC,
								double			**hSect,
								double			xPixelSize, /* calcInWin->p_X */
								bool			isNormal);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL	SplineSegNormTangPoints (
								const BezierDetails&	bezDet,
								Int32			segment,
								const Coord		*baseC,
								double			**hSect,
								double			xPixelSize, /* calcInWin->p_X */
								bool			isNormal);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL	SplineSegNormTangPoints (
								const BezierDetails&	bezDet,
								const Coord		*cursor,
								const Coord		*baseC,
								double			**hSect,
								double			xPixelSize, /* calcInWin->p_X */
								bool			isNormal);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL DivSplinePart (
							  Int32 						nCo,
							  const Coord				*coords,
							  const Geometry::DirType	*dirs,
							  bool						closed,
							  bool						forw,
							  const Coord&				startCo,
							  double					partLength,
							  double					**hSect);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL DivSplineDiff (
							  Int32						nCo,
							  const Coord				*coords,
							  const Geometry::DirType	*dirs,
							  bool						closed,
							  bool						forw,
							  double					diff,
							  double					**hSect);

GEOMETRY_DLL_EXPORT bool  GEOM_CALL  TangentCircle (
							   Int32						nCo,
							   const Coord				*coords,
							   const Geometry::DirType	*dirs,
							   double					t1,
							   double					t2,
							   const Coord&				f1,
							   const Coord&				f2,
							   double					arcDiff,
							   Coord					*origo,
							   bool 					*exist);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL DivSplineDiff_Arc (
								  Int32 						nCo,
								  const Coord				*coords,
								  const Geometry::DirType	*dirs,
								  bool						closed,
								  bool						forw,
								  double					diff,
								  double					**hSect);

GEOMETRY_DLL_EXPORT void GEOM_CALL	IVDir (GS::PlatformSign inplatform, DirType *pDir);
GEOMETRY_DLL_EXPORT void GEOM_CALL	IVDir (GS::PlatformSign inplatform, GS::PlatformSign toplatform, DirType *pDir);


GEOMETRY_DLL_EXPORT Int32 GEOM_CALL	ACSpline2NUBS (
						Int32 				nCo,
						const Coord			*coords,
						const DirType		*dirs,
						bool				closed,
						double				**knots,
						Coord				**cpts);

GEOMETRY_DLL_EXPORT Int32 GEOM_CALL NUBS2ACSpline (
						Int32				m,
						Int32				nLev,
						double				**knots,
						Coord				**cpts,
						Coord				**coords,
						Geometry::DirType	**dirs,
						Int32				**endIndices);

GEOMETRY_DLL_EXPORT GSErrCode	ReadXMLDirType (GS::XMLIChannel& ic, Geometry::DirType& dt);
GEOMETRY_DLL_EXPORT GSErrCode	WriteXMLDirType (GS::XMLOChannel& oc, const Geometry::DirType& dt);
inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Geometry::DirType& dt)	{ return Geometry::ReadXMLDirType (ic, dt); }
inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Geometry::DirType& dt)	{ return Geometry::WriteXMLDirType (oc, dt); }

}


#endif
