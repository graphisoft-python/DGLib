// *****************************************************************************
//
//						Public Functions for Model Generation
//
// Contact person:	BA
//
// *****************************************************************************

#ifndef	_BOG_H_
#define	_BOG_H_

#include	"GSModelerExport.h"
#include	"GSModelerVers.h"
#include	"GDLProc.h"	// GDL3DComponent
#include	"GDLWrapping.hpp"
#include	"SharedPtr.hpp"

namespace Modeler {
	class Model3D;
	typedef GS::SharedPtr<Model3D>		Model3DPtr;
	typedef GS::ConstSharedPtr<Model3D>	ConstModel3DPtr;
	class Sight;
	typedef GS::SharedPtr<Sight>		SightPtr;
	typedef GS::ConstSharedPtr<Sight>	ConstSightPtr;
	class Model3DViewer;
	class Model3DModifier;
	class Attributes;
	typedef GS::SharedPtr<Attributes>		AttributesPtr;
	typedef GS::ConstSharedPtr<Attributes>	ConstAttributesPtr;
	class Elem;
	typedef GS::ConstSharedPtr<Elem>	ConstElemPtr;
	class IAttributeReader;
}


namespace ModelerAPI {
	class Model;
}

namespace Modeler {
	struct	VOCA;
	class	MeshBody;
	class	BaseUserData;
	class	UserDataContainer;
}

namespace GS {
	class ProcessControl;
}

struct CUT_RECORD;
class Model3DGeneratorState;

GSMODELER_DLL_EXPORT
GDL3DComponent	GSM_CALL	BOGGetGeneratorComponent (GS::ProcessControl& processControl, const Modeler::IAttributeReader* attReader);

GSMODELER_DLL_EXPORT
GDL3DComponent	GSM_CALL	BOGGetGeneratorComponent (GS::ProcessControl& processControl, const Modeler::ConstAttributesPtr& targetAttributes, const Modeler::IAttributeReader* attReader);

GSMODELER_DLL_EXPORT
void	GSM_CALL	BOGReleaseGeneratorComponent (GDL3DComponent* genStateComponent);

GSMODELER_DLL_EXPORT
GDLAttributeComponent	GSM_CALL	BOGGetAttributeGeneratorComponent (GDL3DComponent* genStateComponent);

GSMODELER_DLL_EXPORT
void	GSM_CALL	BOGBeginModelGeneration (Modeler::Model3DModifier&	modelModifier,
											 Modeler::AttributesPtr		attributes);

GSMODELER_DLL_EXPORT
void	GSM_CALL	BOGEndModelGeneration (Modeler::Model3DModifier&	modelModifier,
										   ULong						firstNewElemIdx);

GSMODELER_DLL_EXPORT
void	GSM_CALL		BOGCutSection (GS::ProcessControl&			processControl, 
									   const Modeler::IAttributeReader& attReader,
									   Modeler::SightPtr			sight,
									   Modeler::Model3DModifier&	modelModifier,
									   const GS::Array<CUT_RECORD>&	cutrecs);

GSMODELER_DLL_EXPORT
void	GSM_CALL		BOGElemBegin (GDL3DComponent component);

GSMODELER_DLL_EXPORT
void	GSM_CALL		BOGBeginDebugElem (GDL3DComponent component);

GSMODELER_DLL_EXPORT
Int32	GSM_CALL		BOGElemEnd (GDL3DComponent component, const Modeler::VOCA& voca, Modeler::Model3DModifier& modifier);

GSMODELER_DLL_EXPORT
Modeler::ConstElemPtr GSM_CALL BOGElemEnd (GDL3DComponent component, const Modeler::VOCA& voca, Modeler::AttributesPtr attributes);

GSMODELER_DLL_EXPORT
void GSM_CALL BOGElemAbort (GDL3DComponent component); // You want to BOGReleaseGeneratorComponent without BOGElemEnd

GSMODELER_DLL_EXPORT
void	GSM_CALL BOGCreateDebugElem (GDL3DComponent component, Modeler::Model3DModifier& modelModifier);

GSMODELER_DLL_EXPORT
void	GSM_CALL		BOGBodyEnd (GDL3DComponent component);

GSMODELER_DLL_EXPORT
void	GSM_CALL	BOGCopySightEntity (
						Modeler::Model3DViewer& sourceModelViewer,
						Modeler::Model3DModifier& destModelModifier,
						const Modeler::VOCA *newVoca, ULong elemIdx);

GSMODELER_DLL_EXPORT
void	GSM_CALL		BOGMode (GDL3DComponent&	component,
								 short				mode);


GSMODELER_DLL_EXPORT
short	BOGetCandElemSolidState (GDL3DComponent component);
GSMODELER_DLL_EXPORT
GSErr	BOSetCandElemCutplanes (GDL3DComponent component, const GS::Array<CUT_RECORD>* cutplanes);
GSMODELER_DLL_EXPORT
void	BOSetCandElemShapeType (GDL3DComponent component, short btype);
GSMODELER_DLL_EXPORT
void	BOSetCandElemWrapping (GDL3DComponent component, Wrapping wrapping);
GSMODELER_DLL_EXPORT
Wrapping	BOGetCandElemWrapping (GDL3DComponent component);
GSMODELER_DLL_EXPORT
void	BOGGetCandElemInfo (GDL3DComponent component, TRANMAT& tran);

GSMODELER_DLL_EXPORT
void	GSM_CALL BOGBody (
		GDL3DComponent component, const Modeler::MeshBody& baseElem, const TRANMAT* tran, short defaultColor, short defaultGlima, Int32 defaultEdgeStatus,
		const GS::Array<short> *glimaPerPoly = nullptr, const GS::Array<short> *colorPerEdge = nullptr, const GS::Array<Int32> *statusPerEdge = nullptr
	);

GSMODELER_DLL_EXPORT
void GSM_CALL BOGSetBodyUserData (GDL3DComponent component, const GS::Guid& guid, const Modeler::BaseUserData* bodyUserData);

GSMODELER_DLL_EXPORT
void GSM_CALL BOGSetElemUserData (GDL3DComponent component, const GS::Guid& guid, const Modeler::BaseUserData* elemUserData);

GSMODELER_DLL_EXPORT
void GSM_CALL BOGSetElemUserDataContainer (GDL3DComponent component, const Modeler::UserDataContainer* elemUserDataContainer);

GSMODELER_DLL_EXPORT
void GSM_CALL BOGSetElemGuidForReport (GDL3DComponent component, const GS::Guid& guid);


#endif
