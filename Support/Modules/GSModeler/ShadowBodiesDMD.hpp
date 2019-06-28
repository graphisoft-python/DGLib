// *********************************************************************************************************************
// Description:		ShadowBodies DerivedModelData
//					Shadows for Internal Rendering
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	VSZG
//
// SG compatible
// *********************************************************************************************************************

// ShadowBody's polygons are not ShadowPolygons and
// ShadowPolygons' body is not a ShadowBody.
// These are different concepts.

#if !defined (SHADOWBODIESDMD_HPP)
#define SHADOWBODIESDMD_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"SharedPtr.hpp"

// from GSModeler
#include	"Model3D/Model3D.hpp"
#include	"Sight.hpp"
#include	"Conditions.hpp"

#include	"GSModelerExport.h"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------


namespace ShadowBodyCondition {
	enum Condition {
		SunShadow = 12,
		LightShadow = 15
	};
}


class ShadowBodyConditions : public Modeler::Conditions <ShadowBodyCondition::Condition, 2>
{
public:
	ShadowBodyConditions ();
private:
	static const ShadowBodyCondition::Condition	conditions[2];
	static const short							defaults[2];
};


class GSMODELER_DLL_EXPORT ShadowBodiesDMD // : public DerivedModelData		elobb-utobb
{
public:
	//
	ShadowBodiesDMD (const Model3D* model);
	~ShadowBodiesDMD ();

	//
	Model3DPtr		GetShadowModel ();
	SightPtr		GetShadowSight ();

	//
	void							ClearAllConditions ();
	const ShadowBodyConditions&		GetConditions () const;
	void							SetConditions (const ShadowBodyConditions& src);
	const ShadowBodyConditions&		GetProgressConditions () const;
	void							SetProgressConditions (const ShadowBodyConditions& src);

	void		PrintConditions ();

	void		SyncBodiesAfterDelete ();
	void		UpdateShadowSight (const Modeler::Camera&		cam,
						const Modeler::SunSettings&	sun);

private:
	class GSMODELER_DLL_EXPORT Model3DObserver : public IModel3DObserver
	{
	public:
		Model3DObserver (ShadowBodiesDMD*	parent) : m_shadowBodiesDMD (parent) {}

		void AllConditionsCleared (const Model3D& /*model3D*/) override
		{
			m_shadowBodiesDMD->ClearAllConditions ();
		}

		void EventBeforeClear (const Model3D& /*model3D*/) override
		{
			m_shadowBodiesDMD->SyncBodiesAfterDelete ();
		}

        virtual ~Model3DObserver ();

	private:
		ShadowBodiesDMD*	m_shadowBodiesDMD;
	};

private:
	const Model3D*			m_model;
	Model3DPtr				m_shadowModel;
	SightPtr				m_shadowSight;
	ShadowBodyConditions	m_progress;
	ShadowBodyConditions	m_condition;
	Model3DObserver			m_modelObserver;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


GSMODELER_DLL_EXPORT
const ShadowBodyConditions&		GetShadowBodiesCondition (ConstModel3DPtr model);

GSMODELER_DLL_EXPORT
const ShadowBodyConditions&		GetShadowBodiesCondition (const Model3DViewer& viewer);

GSMODELER_DLL_EXPORT
const ShadowBodyConditions&		GetShadowBodiesProgressCondition (ConstModel3DPtr model);

GSMODELER_DLL_EXPORT
const ShadowBodyConditions&		GetShadowBodiesProgressCondition (const Model3DViewer& viewer);

GSMODELER_DLL_EXPORT
void	SetShadowBodiesCondition (ConstModel3DPtr model, const ShadowBodyConditions& src);

GSMODELER_DLL_EXPORT
void	SetShadowBodiesCondition (const Model3DViewer& viewer, const ShadowBodyConditions& src);

GSMODELER_DLL_EXPORT
void	SetShadowBodiesProgressCondition (ConstModel3DPtr model, const ShadowBodyConditions& src);

GSMODELER_DLL_EXPORT
void	SetShadowBodiesProgressCondition (const Model3DViewer& viewer, const ShadowBodyConditions& src);



}	// namespace Modeler


inline Modeler::ShadowBodyConditions::ShadowBodyConditions () :
	Modeler::Conditions<Modeler::ShadowBodyCondition::Condition, 2> (conditions, defaults)
{
}



#endif
