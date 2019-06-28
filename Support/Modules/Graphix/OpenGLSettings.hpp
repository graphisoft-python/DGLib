// *****************************************************************************
// File:			OpenGLSettings.hpp
//
// Description:
//
// Project:
//
// Contact person:	NAT
//
// SG compatible
// *****************************************************************************

#ifndef OPENGLSETTINGS_HPP
#define OPENGLSETTINGS_HPP

// --- Includes ----------------------------------------------------------------

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT

namespace	NewDisplay {

// --- Class declarations ------------------------------------------------------

class GRAPHIX_DLL_EXPORT OpenGLSettings
{
private:
	static bool		multiSample3D;
	static bool		multiSample2D;
	static bool		msaaTestResult;
	static bool		roundLineCoordinates;

public:
	enum MultiSampling {
		MultiSampling_On,
		MultiSampling_Off,
		MultiSampling_ForceOn4x
	};

	static bool		GetMultiSample3D (void);
	static void		SetMultiSample3D (bool);

	static bool		GetMultiSample2D (void);
	static void		SetMultiSample2D (bool);

	static bool		GetMSAATestResult (void);
	static void		SetMSAATestResult (bool);

	static bool		GetRoundLineCoordinates ();
	static void		SetRoundLineCoordinates (bool b);
};

}

#endif
