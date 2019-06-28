#if !defined (GENARC2DDATA_H)
#define GENARC2DDATA_H

#pragma once

#include "GeometricDefinitions.h"
#include "MatrixData.h"
#include "Point2DData.h"
#include "Box2DData.h"
#include "Circle2DData.h"
#include "Sector2DData.h"
#include "XMLChannel.hpp"
#include "Ellipse2DData.h"

/****************************************************************************/

namespace GS {
template <class Type> class Array;
}

/****************************************************************************/
/*																			*/
/*				2D Generic Arc and its operations							*/
/*																			*/
/****************************************************************************/

namespace Geometry
{

enum SetArcResult
{
	ArcCanNotBeCreatedFromParameters,
	ArcIsCreated
};

class GEOMETRY_DLL_EXPORT GenArc
{
	DECLARE_ROOT_CLASS_INFO

public:
	GenArc ();

	virtual ~GenArc ();

	static GenArc	CreateFullCircle	(const Coord& origo, double radius, bool reflected = false);
	static GenArc	CreateCircleArc		(const Coord& origo, const Coord& begC, const Coord& endC, bool reflected = false);
	static GenArc	CreateCircleArc		(const Coord& begC, const Coord& endC, double angle);
	static GenArc	CreateCircleArc		(const Coord& origo, double radius, double begAng, double endAng, bool reflected = false);
	static GenArc	CreateFullEllipse	(const Ellipse& ellipse, bool reflected = false);
	static GenArc	CreateEllipseArc	(const Ellipse& ellipse, const Coord& begC, const Coord& endC, bool reflected = false);
	static GenArc	CreateEllipseArc	(const Ellipse& ellipse, double begAng, double endAng, bool reflected = false);
	static GenArc	CreateEllipseArc	(const Coord& origo, const Coord& begC, const Coord& endC, double mainAxisDir, double axisLengthRatio, bool reflected = false);
	static GenArc	CreateArc			(const GS::Array <Coord>& onArcPoints, const Coord& begC, const Coord& endC, bool reflected);

	static bool		IsValidEllipseArc	(const Coord& origo, const Coord& begC, const Coord& endC, double mainAxisDir, double axisLengthRatio);

	// getters
	const Ellipse&	GetEllipse			() const { return m_ellipse; }
	const Coord&	GetOrigo			() const { return m_ellipse.GetOrigo (); }
	double			GetMainAxisLength	() const { return m_ellipse.GetMainAxisLength (); }
	double			GetOtherAxisLength	() const { return m_ellipse.GetOtherAxisLength (); }
	double			GetMainAxisDir		() const { return m_ellipse.GetMainAxisDir (); }
	double			GetAxisLengthRatio	() const { return m_ellipse.GetAxisLengthRatio (); }
	bool			IsElliptic			() const { return m_ellipse.IsElliptic (); }
	const Coord&	GetBegC				() const { return m_begC; }
	const Coord&	GetEndC				() const { return m_endC; }
	double			GetBegAng			() const { return m_begAng; }
	double			GetEndAng			() const { return m_endAng; }
	double			GetArcAngle			() const;
	bool			IsReflected			() const { return m_reflected; }
	bool			IsWhole				() const { return m_whole; }

	SetArcResult	SetToFullCircle		(const Coord& origo, double radius, double mainAxisDir = 0.0, bool reflected = false);
	SetArcResult	SetToCircleArc		(const Coord& origo, const Coord& begC, const Coord& endC, bool reflected = false);
	SetArcResult	SetToCircleArc		(const Coord& begC, const Coord& endC, double angle);
	SetArcResult	SetToCircleArc		(const Coord& origo, double radius, double begAng, double endAng, bool reflected = false);

	SetArcResult	SetToFullEllipse	(const Ellipse& ellipse, bool reflected = false);
	SetArcResult	SetToEllipseArc		(const Ellipse& ellipse, const Coord& begC, const Coord& endC, bool reflected = false);
	SetArcResult	SetToEllipseArc		(const Ellipse& ellipse, double begAng, double endAng, bool reflected = false);
	SetArcResult	SetToEllipseArc		(const Coord& origo, const Coord& begC, const Coord& endC, double mainAxisDir, double axisLengthRatio, bool reflected = false);

	// other modifiers
	void			Reflect ();
	void			Offset (const Vector& offset);		// modifies begC and endC
	void			Resize (double newMainAxisLength);	// modifies begC and endC

	bool			IsEqual (const GenArc& other) const;

	// calculations
	void			Snap (Coord& p) const;

	// I/O
	GSErrCode		Write (GS::OChannel& oc) const;
	GSErrCode		Read (GS::IChannel& ic);
	GSErrCode		WriteXML (GS::XMLOChannel& oc) const;
	GSErrCode		ReadXML (GS::XMLIChannel& ic);
private:
	GSErrCode		WriteVersion1 (GS::OChannel& oc, const GS::OutputFrame& frame) const;
	GSErrCode		ReadVersion1 (GS::IChannel& ic, const GS::InputFrame& frame);

private:
	Ellipse		m_ellipse;
	Coord		m_begC;
	Coord		m_endC;
	double		m_begAng;		// derived data	
	double		m_endAng;		// derived data
	bool		m_reflected;
	bool		m_whole;

	void RecalcBegCoord ();
	void RecalcEndCoord ();
	void RecalcBegAng ();
	void RecalcEndAng ();
};

}

using Geometry::GenArc;

struct GEOMETRY_DLL_EXPORT ArcDivParams {
	bool				preferSegmentedArcEnds;
	bool				preferCircArcsOverStraightSegments;
	bool				preferArcsBasedSegmentation;
	bool				preferStaticSegmentation;		//only when preferArcsBasedSegmentation is true!

	double				maxDifference;
	const Box2DData*	boxToKeepMaxDifferenceIn;

	ArcDivParams ();
	ArcDivParams (double maxDifference);
	ArcDivParams (double maxDifference, const Box2DData* boxToKeepMaxDifferenceIn);
};

namespace Geometry {

	GEOMETRY_DLL_EXPORT GenArc* GEOM_CALL SetGenArcPtr (
							GenArc	*arc,
							const Coord&	begC,
							const Coord&	endC,
							double	arcAngle);

	GEOMETRY_DLL_EXPORT GenArc GEOM_CALL SetGenArc (const Coord&	begC,
					   const Coord&	endC,
					   double	arcAngle);



	GEOMETRY_DLL_EXPORT	SetArcResult GEOM_CALL SetArc (const Coord& origo, const Coord& begC, const Coord& endC, GenArc& resultArc);

	GEOMETRY_DLL_EXPORT GenArc GEOM_CALL SetGenArcCircle (const Coord& origoC, double radius);
	GEOMETRY_DLL_EXPORT GenArc GEOM_CALL SetGenArcEllipse (const Ellipse& ell);

	
	GEOMETRY_DLL_EXPORT void GEOM_CALL ArcToBox (
						Box2DData*		box,
						const Coord*	begC,
						const Coord*	endC,
						const Coord*	origC);

	GEOMETRY_DLL_EXPORT Box2DData GEOM_CALL GetGenArcBoundBox (const GenArc& genArc);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL FindAngArc (const Coord&		orientC,
						const Coord&		begC,
						const Coord&		endC,
						bool		*pIsArc,
						Coord		*pOrigC,
						Coord		*pOrientC,
						bool		*pnegArc);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL ArcGetOrigo (const Coord	*begC,
						 const Coord	*endC,
						 double			angle,
						 Coord			*origo);

	GEOMETRY_DLL_EXPORT double GEOM_CALL GetArcAngle (const Coord		*origo,		/* sm031 */
						const Coord		*begC,
						const Coord		*midCArc,
						const Coord		*endC);

	GEOMETRY_DLL_EXPORT void GEOM_CALL ReflectGenArc (GenArc& arc);

	GEOMETRY_DLL_EXPORT GenArc GEOM_CALL GetGenArcComplement (const GenArc& arc);

	GEOMETRY_DLL_EXPORT void GEOM_CALL GetViewAngle (const Coord 	*corig,				/* RJ003 */
													 const Coord 	*cbeg,
													 const Coord 	*cend,
													 double			orifi,
													 Int32			ind,
													 double			*newfi);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL GetCornerFilletCentre (
				Coord 		*cprev,			/* RJ003 */
				Coord 		*c0,
				Coord 		*cnext,
				Int32		indf,
				Coord		*oprev,
				double		fprev,
				Int32		inds,
				Coord		*onext,
				double		fnext,
				bool 		d1,
				bool 		d2,
				double 		disp,
				bool     	dflag,
				Coord		*newc,
				bool		*degen = nullptr);

	GEOMETRY_DLL_EXPORT double GEOM_CALL CalcAngleRelToGenArcBeg (const GenArc	*arc,		/* sm038 */
									double			ang);

	GEOMETRY_DLL_EXPORT void GEOM_CALL TraBackToGenArcSys (const GenArc	*a,
								Coord			*c);

	GEOMETRY_DLL_EXPORT void GEOM_CALL TraBackToGenArcSys (double mainAxisDir, const Coord& origo, double axisLengthRatio, Coord*  c);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL ValidGenArcPoint (const GenArc	*a,
							  const Coord	*c);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL ValidGenArcPoint (const GenArc&	a,
							const Coord&	c);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL ValidGenArcPointEps (const GenArc	*a,
								 const Coord	*c,
								 double			eps);

	GEOMETRY_DLL_EXPORT void GEOM_CALL CalcGenArcBegEndCo (GenArc* pArc);

	GEOMETRY_DLL_EXPORT Direction2D GEOM_CALL GetGenArcBegDirection (const GenArc& genArc);

	GEOMETRY_DLL_EXPORT Direction2D GEOM_CALL GetGenArcEndDirection (const GenArc& genArc);

//	GEOMETRY_DLL_EXPORT GSErr GEOM_CALL TransformArc (const TRANMAT* tran, GenArc* pArc, bool scaleArc);
	GEOMETRY_DLL_EXPORT bool  GEOM_CALL TransformArc (const TRANMAT& trafo, GenArc& arc, Sector& s) CAN_THROW ((std::bad_alloc, GeometryException));

	GEOMETRY_DLL_EXPORT void GEOM_CALL CalcWithSectorArc (Sector		*s,		/* RJ(W)087 */
							double		angle,
							double 		width);


	GEOMETRY_DLL_EXPORT char GEOM_CALL XGenArcLineEps (const 	GenArc	*a,
							  const 	Sector	*s,
							  Sector	*xs,
							  double	eps);

	GEOMETRY_DLL_EXPORT char GEOM_CALL XGenArcSectorEps (
							const 	GenArc*	a,
							const 	Sector*	s,
							Sector*			xs,
							double			eps);

	GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XLineArc (
							const Sector*	s1,
							const Sector*	s2,
							double			ang2,
							Coord*			xc);

	GEOMETRY_DLL_EXPORT short GEOM_CALL PGSectArcInt (
							const Coord*	sb,
							const Coord*	se,
							const Coord*	ab,
							const Coord*	ae,
							Coord*			qint1,
							Coord*			qint2,
							const Coord*	arcOrigo,
							double			arcRadius,
							Geometry::Orientation arcStatus,
							bool			wholeArc,
							double			pgEps);

	GEOMETRY_DLL_EXPORT short GEOM_CALL SectorGenArcIntEps (
							const Coord& sectBeg, const Coord& sectEnd,
							const GenArc& genArc,
							Coord& qint1, Coord& qint2,
							double	pgEps);

	GEOMETRY_DLL_EXPORT char GEOM_CALL XGenArcRayEps (const 	GenArc	*a,
							  const 	Sector	*s,
							  Sector	*xs,
							  double	eps);

	GEOMETRY_DLL_EXPORT char GEOM_CALL XGenArcCircleEps (const GenArc	*a1,
							  const Circle	*a2,
							  Coord			xs[4],
							  double		eps);			/* sm061 */

	GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XGenArcs (
							const GenArc*	a1,
							const GenArc*	a2,
							Coord			xs[4]);			/* sm061 */

	GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XGenArcsEps (
							const GenArc*	a1,
							const GenArc*	a2,
							Coord			xs[4],
							double			eps);

	GEOMETRY_DLL_EXPORT Int32 GEOM_CALL XArcsOverLap (
								const Sector* s1,
								double        ang1,
								const Sector* s2,
								double        ang2,
								Coord*		  xc);

	GEOMETRY_DLL_EXPORT void GEOM_CALL DivideArcToCo (
							const Coord*		pOrigC,
							const Coord*		pBegC,
							double				arcAngle,
							const ArcDivParams& arcDivParams,
							Coord**				hCo,
							Int32*				nCo);

	GEOMETRY_DLL_EXPORT void GEOM_CALL DivideArcToCo (
							const Coord*		pOrigC,
							const Coord*		pBegC,
							double				arcAngle,
							const ArcDivParams& arcDivParams,
							GS::Array<Coord>&	co); /* throws (GSException) */

	GEOMETRY_DLL_EXPORT void GEOM_CALL DivideArcToCo (
							const GenArc&		arc,
							const ArcDivParams& arcDivParams,
							GS::Array<Coord>&	co); /* throws (GSException) */

	GEOMETRY_DLL_EXPORT double GEOM_CALL CalcGenArcAngle (const GenArc* pArc);

	GEOMETRY_DLL_EXPORT double GEOM_CALL LenGenArc (const GenArc& arc);

	GEOMETRY_DLL_EXPORT bool GEOM_CALL IsOnSameArc (const GenArc& arc1, const GenArc& arc2);
	GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL ReadGenArcXML (GS::XMLIChannel& ic, GenArc& genArc);
	GEOMETRY_DLL_EXPORT GSErrCode GEOM_CALL WriteGenArcXML (GS::XMLOChannel& oc, const GenArc& genArc);
	inline GSErrCode	WriteXML (GS::XMLOChannel& oc, const GenArc& genarc)	{ return Geometry::WriteGenArcXML (oc, genarc); }
	inline GSErrCode	ReadXML (GS::XMLIChannel& ic, GenArc& genarc)	{ return Geometry::ReadGenArcXML (ic, genarc); }


	GEOMETRY_DLL_EXPORT GenArc GEOM_CALL CreateExtendedCurve (const GenArc& arc);
	
	GEOMETRY_DLL_EXPORT void GEOM_CALL TangentLines (const Coord& p, const GenArc& arc, SectorResultFn fn);
	GEOMETRY_DLL_EXPORT void GEOM_CALL TangentLines (const Sector& s, const GenArc& arc, SectorResultFn fn);
	GEOMETRY_DLL_EXPORT void GEOM_CALL TangentLines (const GenArc& arc1, const GenArc& arc2, SectorResultFn fn);
	GEOMETRY_DLL_EXPORT void GEOM_CALL NormalLines (const Coord& p, const GenArc& arc, SectorResultFn fn);
	GEOMETRY_DLL_EXPORT void GEOM_CALL NormalLines (const Sector& s, const GenArc& arc, SectorResultFn fn);

	GEOMETRY_DLL_EXPORT double SpecDistPointToArc (const Coord& c, const GenArc& arc, double* overHang = nullptr);

	GEOMETRY_DLL_EXPORT void GetTangentPointsByDirection (const GenArc& arc, const Vector& direction, GS::Array<Coord>& resultPoints);
	
}
	
#endif
