// *****************************************************************************
//
//	              Class	IElemAttributeModifier
//
// Module:			AC
// Namespace:		Phasing
// Contact person:	BB
//
// SG compatible
//
// *****************************************************************************


#if !defined ATTRIBUTEMODIFIER_HPP
#define ATTRIBUTEMODIFIER_HPP

#include "PhasingExport.hpp"
#include "GSPix.h"

namespace Phasing {

// ======================= Class IElemAttributeModifier ===========================

class PHASING_DLL_EXPORT IElemAttributeModifier {

public:
	// line
	virtual short		GetLineType	(void) const = 0;
	virtual short		GetLinePen	(void) const = 0;

	// fill
	virtual short		GetFillType			(void) const = 0;
	virtual short		GetForegroundPen	(void) const = 0;
	virtual short		GetBackgroundPen	(void) const = 0;
	virtual GS_RGBColor	GetBackgroundColor	(void) const = 0;
	virtual GS_RGBColor	GetForegroundColor	(void) const = 0;

	virtual ~IElemAttributeModifier ();
};

} // namespace Phasing

#endif // ATTRIBUTEMODIFIER_HPP
