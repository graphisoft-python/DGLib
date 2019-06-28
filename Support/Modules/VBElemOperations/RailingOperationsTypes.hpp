// *********************************************************************************************************************
// Description:		RailingOperationsTypes
//
// Module:			VBElemOperations
// Namespace:		
// Contact person:	NYD, PaP, JG, CSP, KG
//
// SG compatible
// *********************************************************************************************************************

#ifndef _RAILINGOPERATIONSTYPES_HPP_
#define _RAILINGOPERATIONSTYPES_HPP_

#include "Definitions.hpp"

namespace RailingMVO {

enum Railing3DDetailLevel {
	// Controls the way Railings are displayed in 3D
	RailingFullDrawing = 1,
	RailingSimplifiedDrawing = 2,	// former schematic
	RailingSchematicFrameDrawing = 3
};

enum Railing2DDisplayComponentsFlag {
	// Components that the 2D display may use
	RailingPosts					= 0x0001,
	RailingTopRail					= 0x0002,
	RailingHandrails				= 0x0004,
	RailingRails					= 0x0008,
	RailingInnerPosts				= 0x0010,
	RailingBalusters				= 0x0020,
	RailingPanels					= 0x0040
};

inline Railing2DDisplayComponentsFlag operator~ (Railing2DDisplayComponentsFlag a) { return (Railing2DDisplayComponentsFlag) ~(Int32) a; }
inline Railing2DDisplayComponentsFlag operator| (Railing2DDisplayComponentsFlag a, Railing2DDisplayComponentsFlag b) { return (Railing2DDisplayComponentsFlag) ((Int32) a | (Int32) b); }
inline Railing2DDisplayComponentsFlag operator& (Railing2DDisplayComponentsFlag a, Railing2DDisplayComponentsFlag b) { return (Railing2DDisplayComponentsFlag) ((Int32) a & (Int32) b); }
inline Railing2DDisplayComponentsFlag operator^ (Railing2DDisplayComponentsFlag a, Railing2DDisplayComponentsFlag b) { return (Railing2DDisplayComponentsFlag) ((Int32) a ^ (Int32) b); }
inline Railing2DDisplayComponentsFlag& operator|= (const Railing2DDisplayComponentsFlag& a, Railing2DDisplayComponentsFlag b) { return (Railing2DDisplayComponentsFlag&) ((Int32&) a |= (Int32) b); }
inline Railing2DDisplayComponentsFlag& operator&= (const Railing2DDisplayComponentsFlag& a, Railing2DDisplayComponentsFlag b) { return (Railing2DDisplayComponentsFlag&) ((Int32&) a &= (Int32) b); }
inline Railing2DDisplayComponentsFlag& operator^= (const Railing2DDisplayComponentsFlag& a, Railing2DDisplayComponentsFlag b) { return (Railing2DDisplayComponentsFlag&) ((Int32&) a ^= (Int32) b); }
};

#endif // _RAILINGOPERATIONSTYPES_HPP_
