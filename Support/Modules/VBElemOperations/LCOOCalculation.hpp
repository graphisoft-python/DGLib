// *********************************************************************************************************************
// Description:		Texture local coordinate calculation utilities
//
// Module:			VBElemOperations
// Namespace:		
// Contact person:	PP
//
// SG compatible
// ********************************************************************************************************************* 

#pragma once  
#ifndef	LCOOCALCULATION_HPP
#define	LCOOCALCULATION_HPP


// from VBElemOperations
#include	"VBElemOperationsExport.hpp"

// from Geometry
#include	"Poly2DTypes.hpp"

// from VBElements
#include	"WallTypes.hpp"
#include	"CrossSectType.hpp"
#include	"VBElementsBase/LocalCoordsType.hpp"


namespace LCOOCalculation {

VB_ELEM_OPERATIONS_DLL_EXPORT
bool	GetUser_LocalCoordinates (const VBElem::LocalCoordsType*	pLcoo, 
								  const Coord*						begC,
								  double							rotfi, 
								  double							fi, 
								  double							elemZ,
								  VBElem::LocalCoordsType*			localCoords);
											 
VB_ELEM_OPERATIONS_DLL_EXPORT
VBElem::LocalCoordsType		GenerateComplexCurvedWallLCOO (const Box2DData&		profileBound,
														   const double			offset,
														   const double			snapOffset,
														   const double			snapAngle,
														   const double			refRadius,
														   const ULong			vertCnt = 0,
														   const double*		xCrds = nullptr,
														   const double*		yCrds = nullptr);

VB_ELEM_OPERATIONS_DLL_EXPORT
VBElem::LocalCoordsType		GenerateComplexStraightWallLCOO (const Box2DData&	profileBound,
															 const double		len,
															 bool				alignTexture);

VB_ELEM_OPERATIONS_DLL_EXPORT
void	GetWallLCOOGlobalTrafo (const char								wallKind,
								const CrossSectType						crossSectType,
								const bool								flipped, 
								const double							offset, 
								const double							angle, 
								const double							logHeight,
								const Coord&							begC,
								const Coord&							endC,
								const Coord&							offsetedBegC,
								const Coord&							offsetedEndC,
								const double							begThickness, 
								const double							endThickness,
								const double							wallHeight,
								const double							zLevel,
								const double							zMin,
								TRANMAT&								tran);

VB_ELEM_OPERATIONS_DLL_EXPORT
VBElem::LocalCoordsType		GetWallLCOO (const char								wallKind,
										 const CrossSectType					crossSectType,
										 const bool								flipped, 
										 const double							offset, 
										 const double							angle, 
										 const double							logHeight,
										 const Coord&							begC,
										 const Coord&							endC,
										 const Coord&							offsetedBegC,
										 const Coord&							offsetedEndC,
										 const VBElem::LocalCoordsType*			origWallLCOO,
										 const Geometry::IrregularPolygon2D&	wPoly,
										 const double							begThickness, 
										 const double							endThickness,
										 const double							wallHeight,
										 const bool								alignTexture,
										 const double							zLevel,
										 const double							zMin,
										 const Box2DData&						profileBound,
										 const bool								trapezWallCompatibility = false);

VB_ELEM_OPERATIONS_DLL_EXPORT
VBElem::LocalCoordsType		GetWallLCOO_Global (const char								wallKind,
												const CrossSectType						crossSectType,
												const bool								flipped, 
												const double							offset, 
												const double							angle, 
												const double							logHeight,
												const Coord&							begC,
												const Coord&							endC,
												const Coord&							offsetedBegC,
												const Coord&							offsetedEndC,
												const VBElem::LocalCoordsType*			origWallLCOO,
												const Geometry::IrregularPolygon2D&		wPoly,
												const double							begThickness, 
												const double							endThickness,
												const double							wallHeight,
												const bool								alignTexture,
												const double							zLevel,
												const double							zMin,
												const Box2DData&						profileBound,
												const bool								trapezWallCompatibility = false);


} // namespace LCOOCalculation


#endif	// LCOOCALCULATION_HPP
