// Contact person : KiP

#ifndef I_CWFRAME_QUANTITY_CALCULATOR_HPP
#define I_CWFRAME_QUANTITY_CALCULATOR_HPP

#pragma once

// === Includes ========================================================================================================

// from PropertyOperations
#include "IModelElementQuantityCalculator.hpp"

// =====================================================================================================================


namespace Property {

class PROPERTY_OPERATIONS_DLL_EXPORT ICWFrameQuantityCalculator : public IModelElementQuantityCalculator
{
public:
  virtual ~ICWFrameQuantityCalculator ();

  virtual UIndex GetClass () const = 0;
  virtual double GetDirection () const = 0;
  virtual double GetWidth () const = 0;
  virtual double GetDepth () const = 0;
  virtual double GetLength () const = 0;
  virtual short GetMaterial () const = 0;
};

}

#endif
