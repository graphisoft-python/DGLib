// Contact person : KiP

#ifndef SHELLBASE_QUANTITY_HPP
#define SHELLBASE_QUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from QuantityTakeoff
#include "VBModelElemQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST ShellBaseQuantityCalculator : protected VBModelElemQuantityCalculator
{
public:
	ShellBaseQuantityCalculator (const VBElem::ModelElementConstRef vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~ShellBaseQuantityCalculator ();

	GSErrCode	CalcShellBasePerimeter (const CONV2LISTREC& listParams, double *perimeter,
										double *ridgesLength = nullptr, double *valleysLength = nullptr, double *gablesLength = nullptr,
										double *hipsLength = nullptr, double *eavesLength = nullptr, double *peaksLength = nullptr,
										double *sideWallConLength = nullptr, double *endWallConLength = nullptr,
										double *domeConLength = nullptr, double *hollowConLength = nullptr) const;

protected:
	const VBElem::ShellBaseConstRef& GetShellBase () const;
	virtual VBEO::ModelElemComponentId GetComponentId (const Modeler::MeshBody& body) const override;

	void											GetNumberOfHolesAndSkyligths (Int32& numOfHoles, Int32& numOfSkylights) const;

	virtual	Int32									GetNumberOfContourHoles () const = 0;

	virtual	IPolygonSurfaceType*					GetPolygonSurfaceType () const override;
};

}

#endif