#ifndef VECTORIMAGETRANSFORMER_HPP
#define VECTORIMAGETRANSFORMER_HPP

#pragma once

// from Geometry
#include "TRANMAT.h"
#include "TM.h"
#include "Point2D.hpp"
#include "BezierDetails.hpp"

// from VectorImage
#include "SyHot.hpp"
#include "SyLine.hpp"
#include "SyArc.hpp"
#include "SyText.hpp"
#include "SyRichText.hpp"
#include "SyPixMap.hpp"
#include "SySpline.hpp"
#include "ProfileVectorImageParameter.hpp"
#include "Anchor.hpp"
#include "StretchData.hpp"

// from Pattern
#include "PolygonDrawingDirection.hpp"

namespace VI
{

class VI_DLL_CLASS_EXPORT Transformer
{
private:
	TRANMAT		tranMat;
	bool		changeHatchTypeToKeepAppearance;
public:

	Transformer () : changeHatchTypeToKeepAppearance (false) { Geometry::TMIdentity (&tranMat); }
	Transformer (const TRANMAT& tranMat) : tranMat (tranMat), changeHatchTypeToKeepAppearance (false) {}
	virtual ~Transformer ();

	const TRANMAT*	GetTranMat () const { return &tranMat; };
	bool			ChangeHatchTypeToKeepAppearance () const { return changeHatchTypeToKeepAppearance; };
	void			ChangeHatchTypeToKeepAppearance (bool changeHatchType) { changeHatchTypeToKeepAppearance = changeHatchType; };

	virtual void Transform (Sy_HotType& hots)													const { hots.Transform (tranMat); }
	virtual void Transform (Sy_LinType& line)													const { line.Transform (tranMat); }
	virtual void Transform (Sy_ArcType& arc)													const { arc.Transform (tranMat); }
	virtual void Transform (Sy_TextType& text, double textScale)								const { text.Transform (tranMat, textScale); }
	virtual void Transform (Sy_RichTextType& richText)											const { richText.Transform (tranMat); }
	virtual void Transform (Sy_SplineType& spline, Coord* pCoords, Geometry::DirType* pDirs)	const { spline.Transform (tranMat, pCoords, pDirs); }
	virtual void TransformInVectorImage (Sy_SplineType& spline)									const { spline.TransformInVectorImage (tranMat); }
	virtual void Transform (Sy_PixMapType& pixMap)												const { pixMap.Transform (tranMat); }
	virtual void Transform (PVI::ProfileVectorImageParameter& /*profileParameter*/)				const {}
	virtual void Transform (PVI::Anchor& anchor)												const { anchor.Transform (tranMat); }
	virtual void Transform (PVI::StretchData& stretchData)										const { stretchData.Transform (tranMat); }

	// transform the base arc of the curved curtain wall
	virtual	void TransformCWBaseArc (Sy_HotType& hots1, Sy_HotType& hots2) const;
};

}

#endif
