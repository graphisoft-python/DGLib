// *****************************************************************************
//
//                  			BitManipulation
//                            
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************

#include "Definitions.hpp"

namespace GS {

// ============================ Bit test set clear =============================

bool GSROOT_DLL_EXPORT TestBit (const void* bytePtr, Int32 bitNum);
void GSROOT_DLL_EXPORT SetBit (void* bytePtr, Int32 bitNum);
void GSROOT_DLL_EXPORT ClearBit (void* bytePtr, Int32 bitNum);

}