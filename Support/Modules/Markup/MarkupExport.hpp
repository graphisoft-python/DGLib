// *****************************************************************************
//
//                     Export definitions for Markup module
//
// Module:			Markup
// Namespace:
// Contact person:	BeA
//
// SG compatible
//
// *****************************************************************************

#ifndef MARKUPEXPORT_HPP
#define MARKUPEXPORT_HPP

#pragma once

#if defined (_MSC_VER) && !defined (WINDOWS)
#define	WINDOWS
#endif

#include "PlatformDLLExport.hpp"

#if defined (MARKUP_DLL_COMPILE)
#define MARKUP_DLL_EXPORT		PLATFORM_DLL_EXPORT
#else
#define MARKUP_DLL_EXPORT		PLATFORM_DLL_IMPORT
#endif

#endif // MARKUPEXPORT_HPP
