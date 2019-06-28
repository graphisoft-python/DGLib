// *********************************************************************************************************************
// Description:		Try to generate stair baseline solutions by eliminating constraints
//
// Module:			VBElemOperations
// Namespace:		StairOperations::Solving
// Contact person:	BaP
//
// SG compatible
// *********************************************************************************************************************
#if !defined _STAIRSOLVERIMAGEGENERATOR_HPP_
#define _STAIRSOLVERIMAGEGENERATOR_HPP_

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from VBElemOperations
#include "StairSolverStrategy.hpp"

// from Graphix
#include "NativeImage.hpp"

// from GSDisplay
#include "Transformation2D.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace SL
{
	class Transformation2D;
}

// --- Type definitions	------------------------------------------------------------------------------------------------

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Declaration -----------------------------------------------------------------------------------------------------
namespace StairOperations {
namespace Solving {

class ImageGenerator
{
public:
	class EdgeDrawingInfo {
	public:
		bool	visible;
		UInt32	lineWidth;

		EdgeDrawingInfo () : visible (true), lineWidth (1) {}
		EdgeDrawingInfo (const UInt32 lineWidth) : visible (true), lineWidth (lineWidth) {}
		EdgeDrawingInfo (const bool visible, const UInt32 lineWidth) : visible (visible), lineWidth (lineWidth) {}
	};


	class TreadDrawingInfo {
	public:
		EdgeDrawingInfo	leadingEdge;
		EdgeDrawingInfo	leftSideEdge;
		EdgeDrawingInfo	rightSideEdge;
		EdgeDrawingInfo	trailingEdge;
		bool			fill;

		TreadDrawingInfo () : leadingEdge (), leftSideEdge (), rightSideEdge (), trailingEdge (), fill (false) {}
		TreadDrawingInfo (const UInt32 lineWidth) : leadingEdge (lineWidth), leftSideEdge (lineWidth), rightSideEdge (lineWidth), trailingEdge (lineWidth), fill (false) {}
	};

	class ColorSet {
	public:
		enum Index {
			First = 1,
			Blue = First,
			Default = Blue,
			Red = 2,
			Green = 3,
			Yellow = 4,
			Orange = 5,
			Pink = 6,
			Purple = 7,
			Last = Purple
		};

		typedef GS::HashTable<Index, ColorSet> Table;

		Gfx::Color	basic;
		Gfx::Color	highlight;
		Gfx::Color	fill;

		ColorSet () : basic (), highlight (), fill () {}
		ColorSet (const Gfx::Color& basic, const Gfx::Color& highlight, const Gfx::Color& fill) : basic (basic), highlight (highlight), fill (fill) {}

		static const Table	GetColorSetTable (void);
		static const Index	Next (Index index);
	};

private:
	VBElem::StairConstRef	m_stair;
	const StrategyRef		m_strategy;
	const double			m_resolutionFactor;
	SL::Transformation2D	m_tran;
	ColorSet				m_colorSet;

	static const UInt32		ImageWidth;
	static const UInt32		ImageHeight;
	static const double		WalkinglineArrowHeadSize;

	static const ColorSet::Table	ColorSetTable;
	static ColorSet::Index			ColorSetIndex;

public:
	ImageGenerator (VBElem::StairConstRef stair, const StrategyRef strategy, const double viewAngle, double resolutionFactor);
	~ImageGenerator ();

	NewDisplay::NativeImage GetImage (void) const;

	static void	NextColorSet (void);

private:
	void	DrawTreadPoly (NewDisplay::NativeContext& context, VBElem::TreadPolygon treadPoly, const TreadDrawingInfo& drawingInfo) const;
	void	DrawWalkingline (NewDisplay::NativeContext& context, VBElem::StairPolyline walkingline, const UInt32 lineWidth = 1) const;
	void	DrawPolyline (NewDisplay::NativeContext& context, VBElem::StairPolyline walkingline, const UInt32 lineWidth = 1) const;
	void	DrawPolylineArrowHead (NewDisplay::NativeContext& context, VBElem::StairPolyline walkingline, const UInt32 lineWidth = 1) const;

	static const ColorSet	GetColorSet (const ColorSet::Index index);
};

} // namespace Solving
} // namespace StairOperations


//namespace GS {
//inline ULong	GenerateHashValue (const StairOperations::Solving::ImageGenerator::ColorSet::Index& index);
//}	// namespace GS
//
//inline ULong	GS::GenerateHashValue (const StairOperations::Solving::ImageGenerator::ColorSet::Index& index)
//{
//	return static_cast<ULong> (index);
//}

#endif	// _STAIRSOLVERIMAGEGENERATOR_HPP_