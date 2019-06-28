// Contact person : KiP

#ifndef CURTAINWALL_QUANTITY_HPP
#define CURTAINWALL_QUANTITY_HPP

#pragma  once

// === Includes ========================================================================================================

// from PropertyOperations
#include "ICurtainWallQuantityCalculator.hpp"

// from VBElements
#include "CurtainWallTypes.hpp"

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST CurtainWallQuantityCalculator : public Property::ICurtainWallQuantityCalculator, protected VBModelElemQuantityCalculator
{
public:
	CurtainWallQuantityCalculator (const VBElem::ModelElementConstRef& vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~CurtainWallQuantityCalculator ();

	virtual UInt32											GetNumOfPanels						() const override;
	virtual double											GetLength							() const override;
	virtual double											GetSlantAngle						() const override;
	virtual double											GetContourSurfaceArea				() const override;
	virtual double											GetBoundarySurfaceArea				() const override;
	virtual double											GetLengthOfFrames					() const override;
	virtual double											GetLengthOfContourFrames			() const override;
	virtual double											GetLengthOfMainAxisFrames			() const override;
	virtual double											GetLengthOfSecAxisFrames			() const override;
	virtual double											GetLengthOfCustomFrames				() const override;
	virtual double											GetSurfAreaOfPanels					() const override;
	virtual double											GetSurfAreaOfNPanels				() const override;
	virtual double											GetSurfAreaOfSPanels				() const override;
	virtual double											GetSurfAreaOfEPanels				() const override;
	virtual double											GetSurfAreaOfWPanels				() const override;
	virtual double											GetSurfAreaOfNEPanels				() const override;
	virtual double											GetSurfAreaOfNWPanels				() const override;
	virtual double											GetSurfAreaOfSEPanels				() const override;
	virtual double											GetSurfAreaOfSWPanels				() const override;
	virtual double											GetCountorSurfaceArea				() const override;

	virtual	double											GetNetVolume						() const override;
	virtual	double											GetTotalSurfaceArea					() const override;

	virtual GS::HashSet<VBEO::ModelElemComponentId>			GetComponents						() const override;
	virtual	UIndex											GetComponentBuildingMaterialIdx		(const VBEO::ModelElemComponentId& componentId) const override;
	virtual double											GetComponentVolume					(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	bool											HasComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;
	virtual	double											GetComponentProjectedArea			(const VBEO::ModelElemComponentId& componentId) const override;

	virtual GS::HashSet<ModelCalculations::SurfaceId>		GetVisibleSurfaces					() const override;
	virtual GS::HashSet<VBEO::ModelElemComponentSurfaceId>	GetComponentSurfaces				() const override;
	virtual	double											GetExposedSurfaceArea				(const VBEO::ModelElemComponentSurfaceId& componentSurfaceId) const override;

private:
	void	CalcCurtainWallData (const Int32*	globalsBits,
								 double*		framesLength,
								 double*		contourFramesLength,
								 double*		mainaxisFramesLength,
								 double*		secaxisFramesLength,
								 double*		customFramesLength,
								 double*		panelsSurface,
								 double*		panelsSurfaceN,
								 double*		panelsSurfaceS,
								 double*		panelsSurfaceE,
								 double*		panelsSurfaceW,
								 double*		panelsSurfaceNE,
								 double*		panelsSurfaceNW,
								 double*		panelsSurfaceSE,
								 double*		panelsSurfaceSW,
								 double*		contourSurface,
								 double*		boundarySurface,
								 double*		nominalVolume,
								 double*		length,
								 double*		height,
								 double*		slantAngle,
								 UInt32*		numOfPanels) const;

	const VBElem::CurtainWallConstRef&	GetCurtainWall () const;

	virtual VBEO::ModelElemComponentId		GetComponentId (const Modeler::MeshBody& body) const override;

	virtual void					EnumerateModelElemSubElements (const std::function<void (const VBElem::ModelElementConstRef&)>& processor) const override;
};

}
#endif
