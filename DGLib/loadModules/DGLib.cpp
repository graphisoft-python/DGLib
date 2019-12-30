// DGLib.cpp : 定义 DLL 应用程序的导出函数。

#include "../stdafx.h"

#include "../implementations/DGBarControlFunc.hpp"
#include "../implementations/DGButtonFunc.hpp"
#include "../implementations/DGDialogFunc.hpp"
#include "../implementations/DGEditControlFunc.hpp"
#include "../implementations/DGItemFunc.hpp"
#include "../implementations/DGItemPropertyFunc.hpp"
#include "../implementations/DGListBoxFunc.hpp"
#include "../implementations/DGPanelFunc.hpp"
#include "../implementations/DGStaticItemFunc.hpp"
#include "../implementations/DGUtilityFunc.hpp"
#include "../implementations/DGUserItemFunc.hpp"
#include "../implementations/DGCheckItemFunc.hpp"
#include "../implementations/DGImageFunc.hpp"


PYBIND11_MODULE(DGLib, m) {

	m.def("version", []() {	return "version 0.1.1"; });

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
	load_Image(m);
	load_ImageEX(m);
	load_NativeImage(m);
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

	// --- DGCheckItem
	load_CheckItem(m);
	load_CheckItemEX(m);

	// --- DGImage
	load_ImageItem(m);
	load_ImageItemEX(m);

// --- Add bindings end -------------------------------------------------------------------
}