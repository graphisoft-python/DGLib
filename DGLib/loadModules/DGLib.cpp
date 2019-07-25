// DGLib.cpp : 定义 DLL 应用程序的导出函数。

#include "../stdafx.h"

#include "../implementations/dgBarControlFunc.hpp"
#include "../implementations/dgButtonFunc.hpp"
#include "../implementations/dgDialogFunc.hpp"
#include "../implementations/dgEditControlFunc.hpp"
#include "../implementations/dgItemFunc.hpp"
#include "../implementations/dgItemPropertyFunc.hpp"
#include "../implementations/dgListBoxFunc.hpp"
#include "../implementations/dgPanelFunc.hpp"
#include "../implementations/dgStaticItemFunc.hpp"
#include "../implementations/dgUtilityFunc.hpp"
#include "../implementations/dgUserItemFunc.hpp"


PYBIND11_MODULE(DGLib, m) {

	m.def("version", []() {	return "version 0.0.3"; });

// --- Add bindings here ------------------------------------------------------------------

// --- DGItem
	load_dg_ItemBase(m);
	load_dg_Item(m);

// --- DGItemProperty
	load_dg_Font(m.def_submodule("Font"));
	load_dg_ItemBaseEX(m);

// --- DGUtility
	load_dg_EOL(m.def_submodule("EOL"));
	load_dg_Key(m.def_submodule("Key"));
	load_dg_CharRange(m);
	load_dg_NativeUnit(m);
	load_dg_TPointEX(m);
	load_dg_TRectEX(m);
	load_dg_MousePosData(m);

// --- DGPanel
	load_dg_Panel(m);

// --- DGDialog
	load_dg_Dialog(m);
	load_dg_DialogEX(m);
	load_dg_ModelessBaseEX(m);

// --- DGButton
	load_dg_ButtonItem(m);
	load_dg_ButtonItemEX(m);
	load_dg_SplitButton(m);
	load_dg_CustomSplitButton(m);

// --- DGEditControl	
	load_dg_EditControl(m);
	load_dg_PosIntEdit(m);
	load_dg_IntEdit(m);
	load_dg_RealEdit(m);
	load_dg_RealEditEX(m);
	load_dg_TextEditBase(m);
	load_dg_TextEditBaseEX(m);
	load_dg_ShortcutEdit(m);

// --- DGListBox
	load_dg_ListBox(m);
	load_dg_ListBoxEX(m);

// --- BarControl
	load_dg_BarControl(m);
	load_dg_BarControlEX(m);
	load_dg_ScrollBar(m);
	load_dg_ProgressBar(m);

// --- DGStaticItem
	load_dg_StaticItemEventProperty(m);
	load_dg_StaticText(m);
	load_dg_StaticTextEX(m);
	load_dg_GroupBox(m);
	load_dg_Separator(m);

// --- DGUserItem
	load_dg_UserItemEventProperty(m);
	load_dg_UserItem(m);

// --- Add bindings end -------------------------------------------------------------------
}