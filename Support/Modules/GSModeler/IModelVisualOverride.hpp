#ifndef IMODELVISUALOVERRIDE_HPP
#define IMODELVISUALOVERRIDE_HPP

#pragma once

#include "IModelVisualOverrideTypes.hpp"
#include "IVisualOverrideTemplate.hpp"
#include "GSModelerPrivExp.h"
#include "CountedPtr.hpp"

class ModVisualizationEngine; 

namespace Modeler {
	class BaseUserData;
}

namespace VisualOverride
{
	enum SurfaceOrigin3D {
		UndefinedSurfaceOrigin		= -1,	// a ctor erre inicializalja, igy latjuk, ha valahol elfelejtjuk beallitani
		UnCutSurface				= 0,
		CGOPCutSurface				= 1,	// Is a cut surface due to CG operation!
		SectionCutSurface			= 2		// is a cut surface due to section-plane-cut
	};

	enum LineOrigin3D {
		UndefinedLineOrigin3D		= -1,	// a ctor erre inicializalja, igy latjuk, ha valahol elfelejtjuk beallitani
		UnCutLine3D					= 0,
		CutLine3D					= 1
	};

	enum LineRole3D {
		UndefinedLineRole3D			= -1,	// a ctor erre inicializalja, igy latjuk, ha valahol elfelejtjuk beallitani
		ContourLine3D				= 2,
		HatchLine3D					= 3,
		SilhouetteContourLine3D		= 4,
		ShadowContourLine3D			= 5
	};

	class GSMODELER_PRIVATE_EXPORT IModelDrawSpecifics
	{
	public: 
		IModelDrawSpecifics () {}
		virtual ~IModelDrawSpecifics ();

		virtual GS::Guid						GetElemGuid () const = 0;

		virtual SurfaceOrigin3D					GetSurfaceOrigin () const = 0;
		virtual LineOrigin3D					GetLineOrigin () const = 0;
		virtual LineRole3D						GetLineRole () const = 0;

		virtual const Modeler::BaseUserData*	GetBodyUserData (const GS::Guid& userDataGuid) const = 0;
		virtual UInt32							GetAllBodyUserDataUniqueId () const = 0;	// unique in an Elem

		virtual bool							IsShadow () const = 0;
	}; 

	class GSMODELER_PRIVATE_EXPORT ModelVisualOverrideDecoratorBase : public VisualOverrideDecoratorBaseTemplate<IModelVisualOverride>
	{
	public:
		explicit ModelVisualOverrideDecoratorBase (const GS::CountedPtr<const IModelVisualOverride>& decoratedOverride) :
		VisualOverrideDecoratorBaseTemplate (decoratedOverride)
		{
		}
		virtual ~ModelVisualOverrideDecoratorBase (void);
	};

	class GSMODELER_PRIVATE_EXPORT ModelVisualOverrideViewSettingsDecorator : public ModelVisualOverrideDecoratorBase
	{
	public:
		explicit ModelVisualOverrideViewSettingsDecorator (
			const GS::CountedPtr<const IModelVisualOverride>&		decoratedOverride, 
			const ModVisualizationEngine&								visEngineInit, 
			const short													solidBkgFillIndexInit) 

			: ModelVisualOverrideDecoratorBase (decoratedOverride)
			, visEngine (visEngineInit)
			, solidBkgFillIndex (solidBkgFillIndexInit)
		{
		}
		virtual ~ModelVisualOverrideViewSettingsDecorator (void);


		virtual VisualOverride::OverrideStatus			OverrideFillType				(const VisualOverride::IModelDrawSpecifics& drawSpec, short& fillType) const override;

	protected: 
		const ModVisualizationEngine&					visEngine;
		const short										solidBkgFillIndex; 
	};

	class GSMODELER_PRIVATE_EXPORT NoModelVisualOverride : public NoVisualOverride<IModelVisualOverride>
	{
	public: 
		NoModelVisualOverride (void); 
		virtual ~NoModelVisualOverride (void);
	};

} //VisualOverride


#endif //IMODELVISUALOVERRIDE_HPP
