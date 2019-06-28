// *********************************************************************************************************************
// Description:		LineProperties class
//
// Module:			VBUtils
// Namespace:		VBUtil
// Contact person:	KovG
//
// SG compatible
// *********************************************************************************************************************

#if !defined (LINEPROPERTIES_HPP)
#define LINEPROPERTIES_HPP

#pragma once


// --- Includes	--------------------------------------------------------------------------------------------------------
#include "GSRoot.hpp"
#include "VBUtilsExport.hpp"
#include "GSUtilsDefs.h"

// --- Type definitions	------------------------------------------------------------------------------------------------

namespace VBUtil {

class VBUTILS_DLL_EXPORT LineProperties {

	DECLARE_ROOT_CLASS_INFO

private:
	short	pen;
	short	lType;
	bool	isVisible;

public:
	LineProperties ();
	LineProperties (short pen, short lType);		//only for compatibility, do not use it in new code! 
	LineProperties (short pen, short lType, bool isVisible);

	short	GetPen			(void) const;
	short	GetLType		(void) const;
	bool	IsVisible		(void) const;
	void	SetPen			(short newPen);
	void	SetLType		(short newLType);
	void	SetVisible		(bool visible);

	bool operator== (const LineProperties& other) const;
	virtual ~LineProperties ();
};

inline LineProperties::LineProperties ()
	: pen(Pen_First)
	, lType(SolidLineIndex)
	, isVisible(true)
{
}

inline LineProperties::LineProperties (short pen_init, short lType_init)		//only for compatibility, do not use it in new code! 
	: pen (pen_init)
	, lType (lType_init)
	, isVisible (true)
{
	if (pen == Pen_Transparent) {
		isVisible = false;
		pen = Pen_First;		//do not want to have pen == 0!
	}

	if (lType < SolidLineIndex) {
		DBBREAK_STR ("Invalid line type was used to initialize LineProperties!");
		lType = SolidLineIndex;
	}
}

inline LineProperties::LineProperties (short pen, short lType, bool isVisible)
	: pen(pen)
	, lType(lType)
	, isVisible(isVisible)
{
	DBASSERT (pen != Pen_Transparent);
	DBASSERT (lType >= SolidLineIndex);
}

inline short LineProperties::GetPen (void) const
{
	DBASSERT (pen != Pen_Transparent);
	return pen;
}

inline short LineProperties::GetLType (void) const
{
	DBASSERT (lType >= SolidLineIndex);
	return lType;
}

inline bool LineProperties::IsVisible (void) const
{
	return isVisible;
}

inline void LineProperties::SetPen (short newPen)
{
	pen = newPen;
	DBASSERT (pen != Pen_Transparent);
}

inline void LineProperties::SetLType (short newLType)
{
	lType = newLType;
	DBASSERT (lType >= SolidLineIndex);
}

inline void LineProperties::SetVisible (bool visible)
{
	isVisible = visible;
}

inline bool LineProperties::operator== (const LineProperties& other) const
{
	return pen == other.pen && lType == other.lType;
}

} // namespace

#endif
