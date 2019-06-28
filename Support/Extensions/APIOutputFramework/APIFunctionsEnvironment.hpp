#ifndef __APIFUNCTIONSENVIRONMENT_HPP__
#define __APIFUNCTIONSENVIRONMENT_HPP__

// includes and defines needed by API functions
#ifdef _WIN32
	#pragma warning (push, 3)
	#include <Win32Interface.hpp>
	#pragma warning (pop)

	#ifndef WINDOWS
	#define WINDOWS
	#endif
#endif

#ifdef macintosh
	#include <CoreServices/CoreServices.h>
#endif

#ifndef ACExtension
	#define	ACExtension
#endif

#ifdef WINDOWS
	#pragma warning (disable: 4068 4786)
#endif

#include <ACAPinc.h>

#ifdef WINDOWS
	#pragma warning (default: 4068)
#endif

#endif //__APIFUNCTIONSENVIRONMENT_HPP__
