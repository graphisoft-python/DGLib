// *********************************************************************************************************************
// Description:		GetPolyRoofSinglePlanesRunnable class definition from ListSel.c
//
// Module:			QuantityTakeoff
// Namespace:
// Contact person:	TaB
//
// SG compatible
// *********************************************************************************************************************

#ifndef GETPOLYROOFSINGLEPLANESRUNNABLE_HPP
#define GETPOLYROOFSINGLEPLANESRUNNABLE_HPP

// from GSRoot
#include	"Runnable.hpp"

// from Modeler
#include	"CandidateElem.hpp"
#include	"RoofConstruct.hpp"
#include	"Model3D/Model3DUtils.hpp"
#include	"BOG.h"

class GetPolyRoofSinglePlanesRunnable : public TT::Runnable {
private:
	GS::AtomicCounter*					counter;
	Modeler::ConstElemPtr				perBodyElem;
	Modeler::ConstElemPtr				fullRoof;
	Modeler::AttributesPtr				attribs;
	short								edgePenIdx;
	short								materialIdx;
	Modeler::PolygonId					cutSurfacePolygonId;
	GDL3DComponent						component;
	GS::Array<GS::Guid>					bodyUDResGIds;
	LM::LibrarySet const *				librarySet;

	virtual void Run () override
	{
		if (librarySet == nullptr)
			return;

		LM::LibrarySet::AccessGuard libraryAccessGuard (librarySet);

		Modeler::Attributes::Viewer attrViewer (attribs);
		Modeler::Attributes::Modifier attrModifier (attribs);
		GS::Guid	baseGroupId;
		GS::Guid	toolGroupId;
		GS::Guid	resultGroupId;

		DBASSERT (component.data != nullptr);
		BOGElemBegin (component);

		// tool elem
		CDCopyElemAsCSGGroup (component, *fullRoof, attrViewer, GS::NULLGuid, &baseGroupId);

		const ULong bodyCnt = perBodyElem->GetTessellatedBodyCount ();
		UIndex currBodyIdx;
		Modeler::CandidateElem ce (attribs);
		while ((currBodyIdx = (*counter)++) < bodyCnt)
		try {
			const Modeler::MeshBody&	currBody = perBodyElem->GetConstTessellatedBody (currBodyIdx);

			AttributeReader attReader (GetCurrentAttributeSet ());
			ce.NewElem ();
			ce.MergeBody (attReader, currBody, reinterpret_cast<const TRANMAT*>(&perBodyElem->GetConstTrafo ()),
						  M_SOLID, edgePenIdx, materialIdx, 0, nullptr);
			for (ULong ipgon = 0; ipgon < ce.GetPolygonCount (); ++ipgon) {
				ce.SetPolygonId (ipgon, cutSurfacePolygonId);
			}
			Modeler::ConstElemPtr onePlaneElem = ce.CommitElem (Modeler::VOCA (), GetProcessControl (), nullptr, GS::NULLGuid, nullptr, attReader, nullptr, nullptr, CalculateMPUIDs);

			// base elem
			CDCopyElemAsCSGGroup (component, *onePlaneElem, attrViewer, GS::NULLGuid, &toolGroupId);
			// intersect
			CDOperationGroups (component, nullptr, CG_INTERSECT, 0, baseGroupId, toolGroupId, GS::NULLGuid, &resultGroupId, 0 /*cutLineColor*/, 0 /*cutSurfaceGlima*/, 0 /*cutSurfaceGlimaColor*/,
								Modeler::PolygonId (PolyRoofEdgeBetweenPlanesSurfaceType), Modeler::ForceToolIds, Modeler::OGDefault);
			CDClearGroup (component, nullptr, toolGroupId);

			GS::Guid bodyUDResGId;
			CDCreateGroupWithUserData (component, resultGroupId, GS::NULLGuid, &bodyUDResGId,
									   RFC::BodyPolyRoofData::bodyPolyRoofDataId, currBody.GetBodyUserData (RFC::BodyPolyRoofData::bodyPolyRoofDataId));
			CDClearGroup (component, nullptr, resultGroupId);

			bodyUDResGIds.Push (bodyUDResGId);
		} catch (const GS::Exception&) {
			DBBREAK ();
			ce.ResetCandElem ();
		}

		CDClearGroup (component, nullptr, baseGroupId);
		BOGElemEnd (component, Modeler::VOCA (), attribs);
	}

public:
	GetPolyRoofSinglePlanesRunnable (void) :
	    librarySet (nullptr),
		counter (nullptr),
		perBodyElem (nullptr),
		fullRoof (nullptr),
		attribs (nullptr),
		edgePenIdx (0),
		materialIdx (0)
	{
		component.data = nullptr;
	}

	virtual ~GetPolyRoofSinglePlanesRunnable ();

	void	Init (GS::AtomicCounter*		cntr,
				  Modeler::ConstElemPtr		elem,
				  Modeler::ConstElemPtr		fullElem,
				  Modeler::AttributesPtr	attributes,
				  const AttributeReader&	attReader,
				  const LM::LibrarySet*		librarySetIn)
	{
		librarySet = librarySetIn;
		counter = cntr;
		perBodyElem = elem;
		fullRoof = fullElem;
		attribs = attributes;
		edgePenIdx = fullElem->GetTessellatedBodyCount () > 0 ? fullElem->GetConstTessellatedBody (0).GetEdgePenIdx () : 0;
		materialIdx = fullElem->GetTessellatedBodyCount () > 0 ? fullElem->GetConstTessellatedBody (0).GetMaterialIdx () : 0;
		SetPackedPolygonId (cutSurfacePolygonId,
							Modeler::PolygonId (PolyRoofInnerSurfaceType),
							BitFieldTran<Modeler::PolygonId::ValueType> (FirstByte));
		component = BOGGetGeneratorComponent (GetProcessControl (), attribs, &attReader);
	}

	ULong	GetResElemCount (void) const
	{
		return bodyUDResGIds.GetSize ();
	}

	Modeler::ConstElemPtr	GetResElem (ULong idx) const
	{
		Modeler::ConstElemPtr elem;
		CDCopyCSGGroupAsElem (component, bodyUDResGIds[idx], *attribs, elem);
		return elem;
	}
};

GetPolyRoofSinglePlanesRunnable::~GetPolyRoofSinglePlanesRunnable ()
{
	for (ULong i = 0; i < bodyUDResGIds.GetSize (); ++i) {
		CDClearGroup (component, nullptr, bodyUDResGIds[i]);
	}
	BOGReleaseGeneratorComponent (&component);
}

#endif
