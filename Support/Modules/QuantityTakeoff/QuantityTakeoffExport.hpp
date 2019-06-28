// *********************************************************************************************************************
// Description:		QuantityTakeoff dll export macros definition
//
// Module:			QuantityTakeoff
// Namespace:
// Contact person:	TaB
//
// SG compatible
// *********************************************************************************************************************

#ifndef QUANTITYTAKEOFFEXPORT_HPP
#define QUANTITYTAKEOFFEXPORT_HPP

#if defined (QUANTITYTAKEOFF_DLL_COMPILE)
	#define	QUANTITYTAKEOFF_DLL_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define	QUANTITYTAKEOFF_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif

#if defined (QUANTITYTAKEOFF_DLL_COMPILE)
	#define	QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST	PLATFORM_DLL_EXPORT
#elif defined (QUANTITYTAKEOFF_TEST_DLL_COMPILE)
	#define	QUANTITYTAKEOFF_DLL_EXPORT_FOR_TEST	PLATFORM_DLL_IMPORT
#endif

#endif
