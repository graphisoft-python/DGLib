// *****************************************************************************
//
//                     Export definitions for Phasing module
//
// Module:			Phasing
// Namespace:
// Contact person:	BeA
//
// SG compatible
//
// *****************************************************************************

#ifndef PHASINGEXPORT_HPP
#define PHASINGEXPORT_HPP

#pragma once

#if defined (_MSC_VER) && !defined (WINDOWS)
#define	WINDOWS
#endif

#include "PlatformDLLExport.hpp"

#if defined (PHASING_DLL_COMPILE)
#define PHASING_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
#define PHASING_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif // PHASINGEXPORT_HPP
