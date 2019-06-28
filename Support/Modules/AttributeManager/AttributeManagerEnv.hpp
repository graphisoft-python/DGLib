// *****************************************************************************
// The compiler settings of the attribute manager
//
// Namespaces:        Contact person:
//
// [SG compatible]
// *****************************************************************************

#if !defined (ATTRIBUTEMANAGERENV_HPP)
#define ATTRIBUTEMANAGERENV_HPP

#pragma once

#include "PlatformDLLExport.hpp" // from GSRoot

#if defined (ATTRIBUTEMANAGER_DLL_COMPILE)
	#define ATTRIBUTE_DLL_EXPORT	PLATFORM_DLL_EXPORT
#else
	#define ATTRIBUTE_DLL_EXPORT	PLATFORM_DLL_IMPORT
#endif

#endif
