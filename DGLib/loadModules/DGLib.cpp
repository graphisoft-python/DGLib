// DGLib.cpp : 定义 DLL 应用程序的导出函数。

#include "../stdafx.h"

#include "../implementations/BarControlFunc.hpp"
#include "../implementations/ButtonFunc.hpp"
#include "../implementations/DialogFunc.hpp"
#include "../implementations/EditControlFunc.hpp"
#include "../implementations/ItemFunc.hpp"
#include "../implementations/ItemPropertyFunc.hpp"
#include "../implementations/ListBoxFunc.hpp"
#include "../implementations/PanelFunc.hpp"
#include "../implementations/StaticItemFunc.hpp"
#include "../implementations/UtilityFunc.hpp"
#include "../implementations/UserItemFunc.hpp"


PYBIND11_MODULE(DGLib, m) {

	m.def("version", []() {	return "version 0.0.3"; });

// --- Add bindings here ------------------------------------------------------------------

// --- DGItem
	load_ItemBase(m);
	load_Item(m);

// --- DGItemProperty
	load_Font(m.def_submodule("Font"));
	load_ItemBaseEX(m);

// --- DGUtility
	load_EOL(m.def_submodule("EOL"));
	load_Key(m.def_submodule("Key"));
	load_CharRange(m);
	load_NativeUnit(m);
	load_TPointEX(m);
	load_TRectEX(m);
	load_MousePosData(m);

// --- DGPanel
	load_Panel(m);

// --- DGDialog
	load_Dialog(m);
	load_DialogEX(m);
	load_ModelessBaseEX(m);

// --- DGButton
	load_ButtonItem(m);
	load_ButtonItemEX(m);
	load_SplitButton(m);
	load_CustomSplitButton(m);

// --- DGEditControl	
	load_EditControl(m);
	load_PosIntEdit(m);
	load_IntEdit(m);
	load_RealEdit(m);
	load_RealEditEX(m);
	load_TextEditBase(m);
	load_TextEditBaseEX(m);
	load_ShortcutEdit(m);

// --- DGListBox
	load_ListBox(m);
	load_ListBoxEX(m);

// --- BarControl
	load_BarControl(m);
	load_BarControlEX(m);
	load_ScrollBar(m);
	load_ProgressBar(m);

// --- DGStaticItem
	load_StaticItemEventProperty(m);
	load_StaticText(m);
	load_StaticTextEX(m);
	load_GroupBox(m);
	load_Separator(m);

// --- DGUserItem
	load_UserItemEventProperty(m);
	load_UserItem(m);

// --- Add bindings end -------------------------------------------------------------------
}