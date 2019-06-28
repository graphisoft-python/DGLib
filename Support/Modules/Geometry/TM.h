// *****************************************************************************
// GLOBAL CONSTANTS AND PROTOTYPES, FOR TM... ROUTINES
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************

#ifndef	TM_H
#define	TM_H

#pragma once

#include	"GeometricDefinitions.h"
#include	"MatrixData.h"
#include	"Point3DData.h"


struct PlaneEq;

enum TMTranCode {
		TM_ADD_X,
		TM_ADD_Y,
		TM_ADD_Z,
		TM_ROT_X,
		TM_ROT_Y,
		TM_ROT_Z,
		TM_SCA_X,
		TM_SCA_Y,
		TM_SCA_Z
};

/*================================	PROTOTYPES	============================*/

namespace Geometry {

	GEOMETRY_DLL_EXPORT void 	GEOM_CALL	IVTranMat (GS::PlatformSign inplatform, TRANMAT *tran);
	GEOMETRY_DLL_EXPORT void 	GEOM_CALL	IVTranMat (GS::PlatformSign inplatform, GS::PlatformSign toplatform, TRANMAT *tran);

	GEOMETRY_DLL_EXPORT void 	GEOM_CALL	TMGetLinPart (LINTRAN& linPart, const TRANMAT& tran);
	GEOMETRY_DLL_EXPORT void 	GEOM_CALL	TMFromLinPart (TRANMAT& tran, const LINTRAN& linPart);
	GEOMETRY_DLL_EXPORT void 	GEOM_CALL	TMFromLinPartAndTranslation (TRANMAT& tran, const LINTRAN& linPart, const Vector3D& translation);
	
	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMIdentity (TRANMAT *tran);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMTranslation (TRANMAT *tran, double x, double y, double z);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMRotation_X (TRANMAT *tran, double angle);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMRotation_Y (TRANMAT *tran, double angle);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMRotation_Z (TRANMAT *tran, double angle);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMScale3D (TRANMAT *tran, double scaleFactor);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMRotation (TRANMAT *tran, const COORD3 *t, double alpha);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMCompute (TRANMAT *tran, Int32 ntran, const TMTranCode *code, const double *value);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMCompute (TRANMAT* tran, Int32 ntran, const TRANMAT* trans);

	GEOMETRY_DLL_EXPORT TRANMAT GEOM_CALL	TMComposeTransformations (const TRANMAT& tranLeft, const TRANMAT& tranRight);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMSweep (
							const TRANMAT *tran,
							double alpha,
							double scale,
							double dx, double dy, double dz,
							double *ee1x, double *ee1y, double *ee1z,
							double *ee3x, double *ee3y, double *ee3z,
							double e3x, double e3y, double e3z);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMCoorTran (TRANMAT *tran, const COORD3 *e1, const COORD3 *e2, const COORD3 *e3);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMCoorTran (TRANMAT &tran, const COORD3 &e1, const COORD3 &e2, const COORD3 &e3);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMWorldToLocal	(TRANMAT* tr, const Coord3D& start, const Coord3D& xAxis, const Coord3D& yAxis);
	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMLocalToWorld	(TRANMAT* tr, const Coord3D& start, const Coord3D& xAxis, const Coord3D& yAxis);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMWorldToLocal2D	(TRANMAT* tr, const Coord& start, const Vector2d& xAxis);
	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMLocalToWorld2D	(TRANMAT* tr, const Coord& start, const Vector2d& xAxis);
	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMMirror2D			(TRANMAT* tr, const Coord& axisPoint, const Vector& axisDir);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMProjectionToPlane	(TRANMAT* tr, const Vector3D& direction, const PlaneEq& plane);

	GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL	TMFit2D (TRANMAT* tr,
													 const Coord& originalPoint1,
													 const Coord& originalPoint2,
													 const Coord& originalPoint3,
													 const Coord& transformedPoint1,
													 const Coord& transformedPoint2,
													 const Coord& transformedPoint3);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMPoint (const TRANMAT *tran, double *x, double *y, double *z);
	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMPoint (const TRANMAT *tran, Coord3D *point);
	GEOMETRY_DLL_EXPORT Coord3D	GEOM_CALL	TMGetTransformedPoint (const TRANMAT& tran, const Coord3D& point);

	//GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMBackPoint (const TRANMAT *tran, double *x, double *y, double *z);

	inline				void	TMPoint0 (const double *tran, double *x, double *y, double *z);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMVector (const TRANMAT *tran, double *x, double *y, double *z);
	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMVector (const TRANMAT *tran, Vector3D *vector);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMBackVector (const TRANMAT *tran, double *x, double *y, double *z);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMVector0 (const double *tran, double *x, double *y, double *z);

	GEOMETRY_DLL_EXPORT  void	GEOM_CALL	TMPlaneWithInverse (
												const TRANMAT& tran,
												const TRANMAT& inverse,
												double& pa,
												double& pb,
												double& pc,
												double& pd);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMPlane (
												const TRANMAT& tran,
												double& pa,
												double& pb,
												double& pc,
												double& pd);
	
	GEOMETRY_DLL_EXPORT  void	GEOM_CALL	TMPlaneWithInverse (
												const TRANMAT& tran,
												const TRANMAT& inverse,
												PlaneEq& plane);
	
	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMPlane (const TRANMAT& tran, PlaneEq& plane);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMDirVector (const TRANMAT *tran, double *x, double *y, double *z);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMLenVector (const TRANMAT *tran, double *x, double *y, double *z);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMPosDir2Tran (
							short axis,
							double posx, double posy, double posz,
							double dirx, double diry, double dirz,
							TRANMAT *tran);


	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TM2dFillStatus (TRANMAT *tran);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TM2dPoint (const TRANMAT *tran, double *x, double *y);

	//GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMBack2dPoint (const TRANMAT *tran, double *x, double *y);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TM2dDecompose (
							const TRANMAT *tran,
							double *angle,
							double *xs, double *ys,
							double *xd, double *yd);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TM2dNoRot (double xs, double ys, double xd, double yd, TRANMAT *tran);

	GEOMETRY_DLL_EXPORT GSErr	GEOM_CALL	TMDecomposeMat2 (const TRANMAT *tran, double *c1, double *c2, double *alpha, double *beta);

	GEOMETRY_DLL_EXPORT void	GEOM_CALL	TMCalcArc (
							double x0, double y0,
							double r1, double r2,
							double alpha, double beta,
							Int32 *ncs,
							TRANMAT *tran,
							double *coords);


	GEOMETRY_DLL_EXPORT double GEOM_CALL	GetTrScale (const TRANMAT*	tran);

	GEOMETRY_DLL_EXPORT void GEOM_CALL		TranAngle (const TRANMAT*	tran, double* angle);

	GEOMETRY_DLL_EXPORT void GEOM_CALL		TranVectxy (const TRANMAT* tran, double* vx, double* vy);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL		TranDecompose (
							const TRANMAT	*tran,
							double			*angle,
							double			*xs,
							double			*ys,
							double			*xt,
							double			*yt,
							double			eps = EPS);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL		TranValid (const TRANMAT *tran);

	GEOMETRY_DLL_EXPORT inline bool			TMIsIdentical (const TRANMAT &tran);

	GEOMETRY_DLL_EXPORT	bool GEOM_CALL		IsUnitaryTransformation (const TRANMAT& tran);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL		TMIsPreserveArc (const TRANMAT& tran);
	GEOMETRY_DLL_EXPORT bool GEOM_CALL		TMAreIdentical (const TRANMAT &T1, const TRANMAT &T2, double geomSize); //compares T1 and T2 with tolerance (EPS), geomSize must be the typical size of your geometry.

	GEOMETRY_DLL_EXPORT void GEOM_CALL		Def_SyTranMatrix (const Vector*		loc,
															  double			angle,
															  double			xs,
															  double			ys,
															  TRANMAT*			tran);

	GEOMETRY_DLL_EXPORT GSErrCode	GEOM_CALL	ReadTRANMATXML (GS::XMLIChannel& ic, TRANMAT& tran, const char* tagName = nullptr);
	GEOMETRY_DLL_EXPORT GSErrCode	GEOM_CALL	WriteTRANMATXML (GS::XMLOChannel& oc, const TRANMAT& tran, const char* tagName = nullptr);
	inline GSErrCode	ReadXML (GS::XMLIChannel& ic, TRANMAT& tran)	{ return Geometry::ReadTRANMATXML (ic, tran); }
	inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const TRANMAT& tran)	{ return Geometry::WriteTRANMATXML (oc, tran); }

#ifdef DEBUVERS
	inline void								TMDBPrintf (const TRANMAT &tran);
#endif
}


/****************************************************************************/
/*																			*/
/*					TRANSFORMATION OF A POINT WITHOUT SHIFT					*/
/*																			*/
/****************************************************************************/

inline void	Geometry::TMPoint0 (const double *tran, double *x, double *y, double *z)

{	double	x1, y1, z1;

	x1 = tran[0] * *x + tran[1] * *y + tran[2] * *z;
	y1 = tran[3] * *x + tran[4] * *y + tran[5] * *z;
	z1 = tran[6] * *x + tran[7] * *y + tran[8] * *z;
	*x = x1;
	*y = y1;
	*z = z1;
}

inline bool Geometry::TMIsIdentical (const TRANMAT &tran)
{
	return (tran.status & TR_IDENT) > 0;
}

#ifdef DEBUVERS
inline void Geometry::TMDBPrintf (const TRANMAT &tran)
{
	DBPRINTF ("tran\n");
	DBPRINTF ("\t.status=%x -> ", static_cast<int>(tran.status));
	if (tran.status & TR_IDENT)			DBPRINTF ("TR_IDENT ");
	if (tran.status & TR_DET_1)			DBPRINTF ("TR_DET_1 ");
	if (tran.status & TR_SINGULAR)		DBPRINTF ("TR_SINGULAR ");
	if (tran.status & TR_MIRROR)		DBPRINTF ("TR_MIRROR ");
	if (tran.status & TR_TRANSL_ONLY)	DBPRINTF ("TR_TRANSL_ONLY ");
	if (tran.status & TR_SCALE_ONLY)	DBPRINTF ("TR_SCALE_ONLY ");
	if (tran.status & TR_ROTATE_ONLY)	DBPRINTF ("TR_ROTATE_ONLY ");
	if (tran.status & TR_TRANSL_INCL)	DBPRINTF ("TR_TRANSL_INCL ");
	if (tran.status & TR_SCALE_INCL)	DBPRINTF ("TR_SCALE_INCL ");
	if (tran.status & TR_UNDECOMPOSED)	DBPRINTF ("TR_UNDECOMPOSED");
	DBPRINTF ("\n");
	DBPRINTF ("\t.dummy1=%x\n", static_cast<int>(tran.dummy1));
	DBPRINTF ("\t.dummy2=%x\n", static_cast<int>(tran.dummy2));
	DBPRINTF ("\t.dummy3=%x\n", static_cast<int>(tran.dummy3));
		DBPRINTF (\
		"\t.tmx={{%f, %f, %f, %f}, {%f, %f, %f, %f}, {%f, %f, %f, %f}}\n", \
		tran.tmx.Get (0,0), tran.tmx.Get (0,1), tran.tmx.Get (0,2), tran.tmx.Get (0,3), \
		tran.tmx.Get (1,0), tran.tmx.Get (1,1), tran.tmx.Get (1,2), tran.tmx.Get (1,3), \
		tran.tmx.Get (2,0), tran.tmx.Get (2,1), tran.tmx.Get (2,2), tran.tmx.Get (2,3)\
		);

	DBPRINTF ("end tran\n");
}
#endif

#endif
