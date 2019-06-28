// *****************************************************************************
// 2D Ellipse and its operations
// Geometry, platform-independent
//
// Namespaces:        Contact person:
//     Geometry          RJ, FGY
//
// *****************************************************************************
#if !defined (ELLIPSE_H)
#define ELLIPSE_H

#pragma once

#include "GeometricDefinitions.h"
#include "Point2DData.h"
#include "Sector2DData.h"

struct Circle;
struct ArcDivParams;

namespace Geometry
{

class GenArc;

class GEOMETRY_DLL_EXPORT Ellipse
{
public:
	Ellipse ();
	Ellipse (const Coord& origo, double radius, double mainAxisDir);
	Ellipse (const Coord& origo, double mainAxisLength, double axisLengthRatio, double mainAxisDir);

	const Coord&	GetOrigo () const;
	double			GetMainAxisLength () const;
	double			GetOtherAxisLength () const;
	double			GetMainAxisDir () const;
	double			GetAxisLengthRatio () const;
	bool			IsElliptic () const;

	void			SetOrigo (const Coord& origo);
	void			SetMainAxisLength (double mainAxisLength);
	void			SetMainAxisDir (double mainAxisDir);
	void			SetAxisLengthRatio (double axisLengthRatio);
	void			Set (const Coord& origo, double mainAxisLength, double axisLengthRatio, double mainAxisDir);
	void			SetToCircle (const Coord& origo, double radius, double mainAxisDir);

	bool			IsPointOn (const Coord& point) const;
	double			CalcAngle (const Coord& ellipsePoint) const;
	Coord			CalcEllipsePoint (double angle) const;
	Geometry::Vector2d CalcOutNormal (double angle) const;
	void			Snap (Coord& p) const;

	GSErrCode		Write (GS::OChannel& oc) const;
	GSErrCode		Read (GS::IChannel& ic);
	GSErrCode		WriteXML (GS::XMLOChannel& oc) const;
	GSErrCode		ReadXML (GS::XMLIChannel& ic);

private:
	Coord	m_origo;
	double	m_mainAxisLength;
	double	m_axisLengthRatio;	// mainAxis / otherAxis		
	double	m_mainAxisDir;
};



	GEOMETRY_DLL_EXPORT double GEOM_CALL ComputeEllipseFi (const GenArc* pArc, const Coord* pt);

	GEOMETRY_DLL_EXPORT double GEOM_CALL ComputeEllipse_t (const GenArc* pArc, const Coord* pt);

	GEOMETRY_DLL_EXPORT void GEOM_CALL ComputeEllipseCoord (const GenArc* pArc, double fi, Coord* pt);

	GEOMETRY_DLL_EXPORT Coord GEOM_CALL ComputeEllipseCoord (const GenArc& pArc, double givenLen);

	GEOMETRY_DLL_EXPORT void GEOM_CALL GetEllipseVal (const GenArc* pArc, double	t/* parameter 0..1 */, Coord* ptResult);

	GEOMETRY_DLL_EXPORT void GEOM_CALL GetEllipseTan (const GenArc* ell, const Coord* c, Vector* tan);

	GEOMETRY_DLL_EXPORT double GEOM_CALL EllipseLen (
							double	a,									/* sm176 */
							double	b,
							double	t1,
							double	t2,
							Int32	*nDiv);

	GEOMETRY_DLL_EXPORT double GEOM_CALL EllipseLen (const GenArc& genArc);

	GEOMETRY_DLL_EXPORT double GEOM_CALL Ellipse_ax (
							double 		ax1,								/* sm176 */
							double		ax2,
							double		a,
							double		endAng,
							double		givenLen);




	GEOMETRY_DLL_EXPORT void GEOM_CALL DoAffinPt (const Sector 	*ax,			/* affinitas tengelye, egysegvektor! sm121 */
					Coord			*c,
					double			ratio);

	GEOMETRY_DLL_EXPORT char GEOM_CALL XEllipseLineEps (
							const GenArc* elli,			/* sm065 */
							const Sector* sLin,
							Sector*       sResult,
							double		  eps);


	GEOMETRY_DLL_EXPORT char GEOM_CALL XEllipseRayEps (
							const GenArc* elli,
							const Sector* sLin,
							Sector*       sResult,
							double		  eps);


	GEOMETRY_DLL_EXPORT char GEOM_CALL XEllipseSectorEps (
							const GenArc* elli,
							const Sector* sLin,
							Sector*       sResult,
							double		  eps);


	GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XEllipseCircle (const GenArc* ell1,			/* sm120 */
												const Circle* cir2,
												Coord*        sect);		/* 4 koordinatanak kell hely! */

	GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XEllipseEllipse (const GenArc* ell1,		/* sm120 */
												 const GenArc* ell2,
												 Coord*        sect);		/* 4 koordinatanak kell hely! */

	GEOMETRY_DLL_EXPORT void GEOM_CALL GetEllipseNearPt (const GenArc* ell1,		/* sm122 */
												  const Coord*  basePt,		/* bazispont (innen nezzuk) */
												  double        estimDist,	/* becsult tavolsag */
												  Coord*        nearPt);	/* eredmeny */

	GEOMETRY_DLL_EXPORT void GEOM_CALL DistortEllipse (
							Ellipse			*ell,				/* bemenet/kimenet */			/* sm126 */
							double			factor);			/* torzitas aranya: y *= factor	*/

	GEOMETRY_DLL_EXPORT Int32 GEOM_CALL DivEllipsePart (
							const GenArc 	*pEll,					/* sm123 */
							bool			forw,
							const Coord		*startCo,
							double			partLength,
							Coord			**hCo);

	GEOMETRY_DLL_EXPORT Int32 GEOM_CALL DivEllipseDiff (
							const GenArc*	pEll,			/* sm123 */
							bool			forw,
							double			diff,
							Coord**			hCo);

	GEOMETRY_DLL_EXPORT void GEOM_CALL DivideEllArcToCo (
							const GenArc&	ellipseArc,
							double			maxArcDifference,
							Coord**         hCo,
							USize* const    nCo);

	GEOMETRY_DLL_EXPORT void GEOM_CALL DivideEllArcToCo (
							const GenArc&	ellipseArc,
							double			maxArcDifference,
							GS::Array<Coord>&	co); /* throw (GSException) */

	GEOMETRY_DLL_EXPORT void GEOM_CALL DivideEllArcToArcs (
							const GenArc&		ellipseArc,
							const ArcDivParams&	params,
							GS::Array<Coord>&	co, 
							GS::Array<Coord>&	arcCenters); /* throw (GSException) */

	GEOMETRY_DLL_EXPORT bool GEOM_CALL CanArcBeReplacedWithSegment (
		const GenArc&		ellipseArc);


	GEOMETRY_DLL_EXPORT bool GEOM_CALL EllipseTangentCircle (const GenArc	*pEll,				/* sm123 */
							const Coord		*f1,
							const Coord		*f2,
							Coord			*origo,
						   double			arcDiff,
							bool 		*exist);

	GEOMETRY_DLL_EXPORT Int32 GEOM_CALL DivEllipseDiff_Arc (const GenArc	*pEll,			/* sm123 */
							 bool		forw,
							 double			diff,
							 Coord			**hCo);

	GEOMETRY_DLL_EXPORT Ellipse GEOM_CALL GetEllipse (const GenArc& arc);

	GEOMETRY_DLL_EXPORT Sector GEOM_CALL GetAffineAxis (const GenArc& arc);

	GEOMETRY_DLL_EXPORT Coord GEOM_CALL AffineTransform (const Coord& c, const Sector& axis, double ratio);

	GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL ReadXMLEllipse (GS::XMLIChannel& ic, Geometry::Ellipse& ellipse);
	GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL WriteXMLEllipse (GS::XMLOChannel& oc, const Geometry::Ellipse& ellipse);
	inline GSErrCode	ReadXML (GS::XMLIChannel& ic, Geometry::Ellipse& ellipse)	{ return Geometry::ReadXMLEllipse (ic, ellipse); }
	inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const Geometry::Ellipse& ellipse)	{ return Geometry::WriteXMLEllipse (oc, ellipse); }

}

#endif
