// *****************************************************************************
// File:			Color.hpp
//
// Description:		Color class
//
// Project:			GSRoot
//
// Namespace:		Gfx
//
// Contact person:	BM
//
// SG compatible
// *****************************************************************************

#ifndef COLOR_HPP
#define COLOR_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "GSRootExport.hpp"
#include "Definitions.hpp"

namespace Gfx {

// --- Color class declaration -------------------------------------------------

class GSROOT_DLL_EXPORT Color
{
private:
	UChar	red;
	UChar	green;
	UChar	blue;
	UChar	alpha;

public:
	enum UShortSelector { AsUShort };

	static const Color	Black;
	static const Color	DarkGray;
	static const Color	Gray;
	static const Color	LightGray;
	static const Color	White;

	static const Color	Red;
	static const Color	Green;
	static const Color	Blue;

	static const Color	Cyan;
	static const Color	Magenta;
	static const Color	Yellow;

	inline	Color ();
	inline	Color (UChar r, UChar g, UChar b, UChar a = 0xFF);
			Color (UShortSelector, UShort r, UShort g, UShort b, UShort a = 0xFFFF);

	inline	void	Set (UChar r, UChar g, UChar b, UChar a = 0xFF);
			void	Set (UShortSelector, UShort r, UShort g, UShort b, UShort a = 0xFFFF);

	inline	void	SetRed   (UChar r);
	inline	void	SetGreen (UChar g);
	inline	void	SetBlue  (UChar b);
	inline	void	SetAlpha (UChar a);

			void	SetRed   (UShortSelector, UShort r);
			void	SetGreen (UShortSelector, UShort g);
			void	SetBlue  (UShortSelector, UShort b);
			void	SetAlpha (UShortSelector, UShort a);

	inline	UChar	GetRed   (void) const;
	inline	UChar	GetGreen (void) const;
	inline	UChar	GetBlue  (void) const;
	inline	UChar	GetAlpha (void) const;

			UShort	GetRed   (UShortSelector) const;
			UShort	GetGreen (UShortSelector) const;
			UShort	GetBlue  (UShortSelector) const;
			UShort	GetAlpha (UShortSelector) const;

			bool	operator== (const Color& rightOp) const;
			bool	operator!= (const Color& rightOp) const;
};


// --- Color class definition --------------------------------------------------

inline Color::Color ()
{
	Set (0, 0, 0, 0xFF);
}


inline Color::Color (UChar r, UChar g, UChar b, UChar a)
{
	Set (r, g, b, a);
}


inline void		Color::Set (UChar r, UChar g, UChar b, UChar a)
{
	SetRed   (r);
	SetGreen (g);
	SetBlue  (b);
	SetAlpha (a);
}


inline void		Color::SetRed (UChar r)
{
	red = r;
}


inline void		Color::SetGreen (UChar g)
{
	green = g;
}


inline void		Color::SetBlue (UChar b)
{
	blue = b;
}


inline void		Color::SetAlpha (UChar a)
{
	alpha = a;
}


inline UChar	Color::GetRed (void) const
{
	return red;
}


inline UChar	Color::GetGreen (void) const
{
	return green;
}


inline UChar	Color::GetBlue (void) const
{
	return blue;
}


inline UChar	Color::GetAlpha (void) const
{
	return alpha;
}


inline GSROOT_DLL_EXPORT ULong	GenerateHashValue (const Color& color)
{
	return ((ULong)color.GetRed () << 24) | ((ULong)color.GetGreen () << 16) | ((ULong)color.GetBlue () << 8) | color.GetAlpha ();
}
}	// namespace Gfx

#endif
