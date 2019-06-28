// *********************************************************************************************************************
// File:			UDAutoTestSupport.hpp
//
// Description:		Support functions for the AutoTest system
//
// Project:			GRAPHISOFT Dialog Manager (DGLib)
//
// Namespace:
//
// Contact person:	VM
// *********************************************************************************************************************

#if !defined UDAUTOTESTSUPPORT_HPP
#define UDAUTOTESTSUPPORT_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

#include "GSAutoTester.hpp"
#include "UDDefinitions.hpp"


// --- Predeclarations -------------------------------------------------------------------------------------------------

UD_DLL_EXPORT bool	CCALL		UDProcessAutoTesterEvent	(t_CommBlock& actCommBlock);
UD_DLL_EXPORT int	CCALL		UDGetCurrentAutotestStep	();

#endif
