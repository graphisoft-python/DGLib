// Contact person : AACS

#ifndef I_CW_QUANTITY_CALCULATOR_HPP
#define I_CW_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================


namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ICurtainWallQuantityCalculator : public IModelElementQuantityCalculator
{
public:
	virtual ~ICurtainWallQuantityCalculator ();

	virtual UInt32 GetNumOfPanels () const = 0;
	virtual double GetLength () const = 0;
	virtual double GetSlantAngle () const = 0;
	virtual double GetContourSurfaceArea () const = 0;
	virtual double GetBoundarySurfaceArea () const = 0;
	virtual double GetLengthOfFrames () const = 0;
	virtual double GetLengthOfContourFrames () const = 0;
	virtual double GetLengthOfMainAxisFrames () const = 0;
	virtual double GetLengthOfSecAxisFrames () const = 0;
	virtual double GetLengthOfCustomFrames () const = 0;
	virtual double GetSurfAreaOfPanels () const = 0;
	virtual double GetSurfAreaOfNPanels () const = 0;
	virtual double GetSurfAreaOfSPanels () const = 0;
	virtual double GetSurfAreaOfEPanels () const = 0;
	virtual double GetSurfAreaOfWPanels () const = 0;
	virtual double GetSurfAreaOfNEPanels () const = 0;
	virtual double GetSurfAreaOfNWPanels () const = 0;
	virtual double GetSurfAreaOfSEPanels () const = 0;
	virtual double GetSurfAreaOfSWPanels () const = 0;
	virtual double GetCountorSurfaceArea () const = 0;
};

}

#endif
