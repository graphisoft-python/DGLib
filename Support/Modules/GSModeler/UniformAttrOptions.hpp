// *********************************************************************************************************************
// Description:		Options for Section, Elevation, Interior Elevation and 3D document presentation
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	FGY
//
// SG compatible
// *********************************************************************************************************************

#if !defined (UNIFORMATTROPTIONS_HPP)
#define UNIFORMATTROPTIONS_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"

#include	"GSModelerExport.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace Modeler {


class GSMODELER_DLL_EXPORT UniformAttrOptions : public GS::Object
{
	DECLARE_CLASS_INFO
public:

	enum	CutSurfFills {
		VectorFilles		= 1,
		UniformMaterial		= 2,
		OwnMaterial			= 3,
		OwnShadedMaterial	= 4
	};

	enum	UncutSurfaceFill {
		PenColor				= 1,
		MaterialColorShaded		= 2,
		MaterialColorNonShaded	= 3
	};

	enum	HiddenEdgeVisibility {
				HideHiddenEdges,
				ShowHiddenEdges
	};

	enum	OnCutPlaneVisibility {
				DontShowOnCutPlanes,
				ShowOnCutPlanes
	};

	CutSurfFills		fillCutSurfacesWith;


	bool	 			shouldUseUniformCutAttributes;	// or each one's own
	short				uniformLineIdx;
	short				uniformFillPenIdx;
	short				uniformFillBkgPenIdx;

	bool				shouldUseUncutSurfaceFill;
	UncutSurfaceFill	uncutSurfaceFillType;
	short				uncutSurfaceBkgPenIdx;

	bool				shouldUseElemPen;
	short				elemPenIdx;

	short				shadFillIdx;
	short				shadFillPenIdx;
	short				shadFillBkgPenIdx;
	short				shadContPenIdx;

	HiddenEdgeVisibility	hiddenEdgeVisibility;
	OnCutPlaneVisibility	onCutPlaneVisibility;
	short					hiddenEdgeLineType;
	short					hiddenEdgeLinePen;

	UniformAttrOptions ();

	void Clear ();

	// Object I/O
	GSErrCode	Read (GS::IChannel& ic) override;
	GSErrCode	Write (GS::OChannel& oc) const override;

	GSErrCode	ReadVersion1  (GS::IChannel& ic);
	GSErrCode	WriteVersion1 (GS::OChannel& oc) const;

	GSErrCode	ReadVersion2  (GS::IChannel& ic);
	GSErrCode	WriteVersion2 (GS::OChannel& oc) const;

	GSErrCode	ReadVersion3  (GS::IChannel& ic);
	GSErrCode	WriteVersion3 (GS::OChannel& oc) const;

	GSErrCode	ReadVersion4  (GS::IChannel& ic);
	GSErrCode	WriteVersion4 (GS::OChannel& oc) const;

	// XML I/O
	GSErrCode	ReadXML (GS::XMLIChannel& ic);
	GSErrCode	WriteXML (GS::XMLOChannel& oc) const;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace

#endif
