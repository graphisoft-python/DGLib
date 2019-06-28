// *********************************************************************************************************************
// File:			KeyPressedHandler.hpp
//
// Description:		Handles pressed keys
//
// Project:			ACPM
//
// Contact person:	AKI
// *********************************************************************************************************************

#pragma once

// Includes ------------------------------------------------------------------------------------------------------------

#include "UDDefinitions.hpp"
#include "DGUtility.hpp"

// Prototypes ----------------------------------------------------------------------------------------------------------

class UD_DLL_EXPORT KeyPressedHandler {
public:
	virtual ~KeyPressedHandler ();

	bool	Do (const DG::Key::Code& code)
	{
		if (!SearchFieldIsFocused () && (!code.IsSpecial () || code.GetValue () == DG::Key::Back)) {
			SendToSearchField ();
			return true;
		}

		if (SearchFieldIsFocused () && !IsModifierPressed () && IsListNavigationKey (code)) {
			SendToList ();
			return true;
		}
		return false;
	}

	static bool IsListNavigationKey (const DG::Key::Code& code)
	{
		return	code.GetValue () == DG::Key::Left || code.GetValue () == DG::Key::Right ||
			code.GetValue () == DG::Key::Up || code.GetValue () == DG::Key::Down;
	}

private:
	virtual bool	SearchFieldIsFocused () = 0;
	virtual void	SendToSearchField () = 0;
	virtual void	SendToList () = 0;
	virtual bool	IsModifierPressed () = 0;
};