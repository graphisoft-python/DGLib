#ifndef UDSIMPLECONTEXTMENU_HPP
#define UDSIMPLECONTEXTMENU_HPP

#pragma once

#include "DGCommandDescriptor.hpp"
#include "DGCommandEvent.hpp"

#include "UDDefinitions.hpp"

namespace DG {
	class MenuObserver;
	class MenuItem;
	class Menu;
}

namespace UD {

class UD_DLL_EXPORT SimpleContextMenu {
public:
	typedef std::function<void ()> Function;

	explicit SimpleContextMenu (DG::MenuObserver* observer);

	void AddItem (const GS::UniString&			text,
				  const Function&				fn,
				  bool							isEnabled = true,
				  bool							isChecked = false,
				  const DG::Icon				icon = DG::Icon ());

	void AddItem (const DG::CommandDescriptor*	command,
				  const	Function&				fn,
				  bool							isEnabled = true);

	void AddSeparator ();

	void StartPopupMenu (const GS::UniString& menuName);

	void EndPopupMenu ();

	void Display (const DG::NativePoint& position);

private:
	struct UD_DLL_EXPORT ItemBase {
		ItemBase ();

		virtual ~ItemBase ();

		GS::Ref<DG::MenuItem>	menuItem;
		Function				fn;
	};

	struct UD_DLL_EXPORT SimpleItem : public ItemBase {
	public:
		SimpleItem (UIndex					index,
					const GS::UniString&	text,
					const DG::Icon&			icon,
					const GS::UniString&	description,
					const Function&			fn,
					bool					status,
					bool					isChecked);

		virtual ~SimpleItem ();

		DG::Command					command;
		DG::CommandDescriptor		commandDesc;
	};


	struct UD_DLL_EXPORT SeparatorItem : public ItemBase {
	public:
		SeparatorItem ();

		virtual ~SeparatorItem ();
	};


	struct UD_DLL_EXPORT PopupMenuStartItem : public ItemBase {
	public:
		PopupMenuStartItem (const GS::UniString& menuName);

		virtual ~PopupMenuStartItem ();

		GS::Ref<DG::Menu> popupMenu;
	};


	struct UD_DLL_EXPORT PopupMenuEndItem : public ItemBase {
	public:
		PopupMenuEndItem ();

		virtual ~PopupMenuEndItem ();
	};

	GS::Array<GS::Ref<ItemBase>>	items;
	DG::MenuObserver*				observer;
};

} //namespace UD

#endif //UDSIMPLECONTEXTMENU_HPP
