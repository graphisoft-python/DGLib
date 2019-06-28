// Contact person : KiP

#ifndef ROOFQUANTITY_HPP
#define ROOFQUANTITY_HPP

#pragma once

// === Includes ========================================================================================================

// from VBElements
#include "VBElements/RoofTypes.hpp"

// from QuantityTakeoff
#include "ShellBaseQuantity.hpp"

// =====================================================================================================================

namespace QT {

class QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST RoofQuantityCalculator : public ShellBaseQuantityCalculator
{
public:
	RoofQuantityCalculator (VBElem::ModelElementConstRef vbElem, const QuantityModelConstPtr& quantityModel);
	virtual ~RoofQuantityCalculator ();

protected:
	void			AdjustRoofEdgeLengthByType (double* ridgesLength,
												double* valleysLength,
												double* hipsLength,
												double* domeConLength,
												double* hollowConLength) const;

	virtual	Int32	GetNumberOfContourHoles () const override;

private:
	const VBElem::RoofConstRef& GetRoof () const;

};

}

#endif