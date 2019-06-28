// *********************************************************************************************************************
// Description:		Definitions for GIS (Geographic Information System) reference
//
// Module:			GIS
// Namespace:		---
//
// *********************************************************************************************************************

#if !defined (GISDefs_HPP)
#define GISDefs_HPP

#pragma once


#define GISNameLen		128		// maximum length of EPSG names

typedef enum {
	CST_Unknown		= 0,	// Unknown Coordinate System
	CST_Geographic	= 1,	// Geographic Coordinate System (on the earth using longitude & latitude angles)
	CST_Projected	= 2		// Projected Coordinate System (with a map projection using linear lengths)
} GISCoordinateSystemType;

// units of measure source is the "www.epsg.org"

typedef enum {								// EPSG UOM Code
		LU_NotDefined				= 0,	// ----

		LU_BinWidth12d5Meters		= 1,	// 9209
		LU_BinWidth165USSurveyFeet	= 2,	// 9205
		LU_BinWidth25Metres			= 3,	// 9208
		LU_BinWidth3d125Metres		= 4,	// 9211
		LU_BinWidth330USSurveyFeet	= 5,	// 9204
		LU_BinWidth37d5Metres		= 6,	// 9207
		LU_BinWidth6d25Metres		= 7,	// 9210
		LU_BinWidth82d5USSurveyFeet	= 8,	// 9206

		LU_BritishChainBenoit1895A	= 9,	// 9052
		LU_BritishChainBenoit1895B	= 10,	// 9062
		LU_BritishChainSears1922	= 11,	// 9042
		LU_BritishFoot1865			= 12,	// 9070
		LU_BritishFootBenoit1895A	= 13,	// 9051
		LU_BritishFootBenoit1895B	= 14,	// 9061
		LU_BritishFootSears1922		= 15,	// 9041
		LU_BritishLinkBenoit1895A	= 16,	// 9053
		LU_BritishLinkBenoit1895B	= 17,	// 9063
		LU_BritishLinkSears1922		= 18,	// 9043
		LU_BritishYardBenoit1895A	= 19,	// 9050
		LU_BritishYardBenoit1895B	= 20,	// 9060
		LU_BritishYardSears1922		= 21,	// 9040

		LU_ClarkesChain				= 22,	// 9038
		LU_ClarkesFoot				= 23,	// 9005
		LU_ClarkesLink				= 24,	// 9039
		LU_ClarkesYard				= 25,	// 9037

		LU_Fathom					= 26,	// 9014
		LU_Foot						= 27,	// 9002

		LU_GermanLegalMetre			= 28,	// 9031
		LU_GoldCoastFoot			= 29,	// 9094

		LU_IndianFoot				= 30,	// 9080
		LU_IndianFoot1937			= 31,	// 9081
		LU_IndianFoot1962			= 32,	// 9082
		LU_IndianFoot1975			= 33,	// 9083
		LU_IndianYard				= 34,	// 9084
		LU_IndianYard1937			= 35,	// 9085
		LU_IndianYard1962			= 36,	// 9086
		LU_IndianYard1975			= 37,	// 9087

		LU_Kilometre				= 38,	// 9036
		LU_Metre					= 39,	// 9001 SI

		LU_NauticalMile				= 40,	// 9030
		LU_StatuteMile				= 41,	// 9093

		LU_USSurveyChain			= 42,	// 9033
		LU_USSurveyFoot				= 43,	// 9003
		LU_USSurveyLink				= 44,	// 9034
		LU_USSurveyMile				= 45,	// 9035

		LU__Count		= 46

} GISLinearUnit;

typedef enum {					// UOM Code, description, used data members
		AU_NotDefined				= 0,	// ----

		AU_ArcMinute				= 1,	// 9103, 1/60th degree, angleDouble
		AU_ArcSecond				= 2,	// 9104, 1/60th arc minute, angleDouble
		AU_CentesimalMinute			= 3,	// 9112, 1/100 of a grad, angleDouble
		AU_CentesimalSecond			= 4,	// 9113, 1/100 of centesimal minute, angleDouble

		AU_Degree					= 5,	// 9102, pi/180 radians, angleDouble
		AU_DegreeMinute				= 6,	// 9115, degree + minutes, angleDeg : degrees + angleDouble : minutes
		AU_DegreeMinuteSecond		= 7,	// 9107, degree + minutes + Seconds, angleDeg : degrees + angleMin : minutes + angleDouble : seconds

		AU_Gon						= 8,	// 9106, pi/200 radians, angleDouble
		AU_Grad						= 9,	// 9105, pi/200 radians, angleDouble

		AU_Microradian				= 10,	// 9109, radian/10e+6, angleDouble
		AU_Mil6400					= 11,	// 9114, 1/6400 of circle, angleDouble
		AU_Radian					= 12,	// 9101, SI standard unit, angleDouble
		AU_SexagesimalDM			= 13,	// 9111, degree + minutes, angleDeg : degrees + angleMin : minutes + angleDouble : fraction of minutes
		AU_SexagesimalDMS			= 14,	// 9110, degree + minutes, angleDeg : degrees + angleMin : minutes + angleSec : seconds + angleDouble : fraction of seconds
		AU_SexagesimalDMSds			= 15,	// 9121, degree + minutes, angleDeg : degrees + angleMin : minutes + angleDouble : seconds (with fractions)

		AU_Degree_Hemi				= 16,	// 9116 or 9117 degree, angleDouble + hemiletter
		AU_DegreeMinute_Hemi		= 17,	// 9118 or 9119 degree + minutes + hemiletter :  angleDeg angleDouble hemiLetter
		AU_DegreeMinuteSecond_Hemi	= 18,	// 9108 or 9120 degree + minutes + seconds + hemiletter: angleDeg angleMin angleDouble hemiLetter

		AU__Count		= 19

} GISAngularUnit;

#endif
