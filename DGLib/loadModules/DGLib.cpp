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


// --- For testting

#define TEST 0;

#if TEST == 1
class Pet {
public:
	Pet() {}
	Pet(const std::string &name) { this->name = name; }

	void setName(const std::string &name_) { name = name_; }
	const std::string &getName() const { return name; }

	int add(int a = 1, int b = 5) { return a + b; }

	std::string name;
};

void load_test(py::module m) {
	py::class_<Pet> m_pet(m, "Pet");
	m_pet
		.def(py::init<>())
		.def(py::init<const std::string &>())

		.def("setName", &Pet::setName)
		.def("getName", &Pet::getName)
		.def("add", &Pet::add, py::arg("a"), py::arg("b") = 5)

		.def("__str__", [](const Pet &p) {
			return "name is " + p.name;
		});
}
#endif // TEST == 1


PYBIND11_MODULE(DGLib, m) {

	m.doc() = "version 2019.7.17";

// --- Add bindings here

#if  TEST == 1
	load_test(m);
#else
// --- BarControl
	load_dg_BarControl(m);
	load_dg_SingleSpin(m);
	load_dg_EditSpin(m);
	load_dg_Slider(m);
	load_dg_ScrollBar(m);
	load_dg_ProgressBar(m);

// --- DGButton
	load_dg_ButtonItem(m);
	load_dg_Button(m);
	load_dg_IconButton(m);
	load_dg_SplitButtonBase(m);
	load_dg_SplitButton(m);
	load_dg_CustomSplitButton(m);

// --- DGDialog
	load_dg_Dialog(m);
	load_dg_ModaDialog(m);
	load_dg_ModelessBase(m);
	load_dg_ModelessDialog(m);
	load_dg_Palette(m);

// --- DGEditControl	
	load_dg_EditControl(m);
	load_dg_PosIntEdit(m);
	load_dg_IntEdit(m);
	load_dg_RealEdit(m);
	load_dg_LengthEdit(m);
	load_dg_AreaEdit(m);
	load_dg_VolumeEdit(m);
	load_dg_AngleEdit(m);
	load_dg_PolarAngleEdit(m);
	load_dg_MMPointEdit(m);
	load_dg_TextEditBase(m);
	load_dg_TextEdit(m);
	load_dg_PasswordEdit(m);
	load_dg_ShortcutEdit(m);
	load_dg_MultiLineEdit(m);

// --- DGItem
	load_dg_ItemBase(m);
	load_dg_Item(m);

// --- DGItemProperty
	load_dg_Font(m.def_submodule("Font"));
	load_dg_ItemFontProperty(m);
	load_dg_FocusableProperty(m);
	load_dg_ItemVariousProperty(m);
	load_dg_ItemTextLengthLimitProperty(m);
	load_dg_ItemTextProperty(m);

// --- DGListBox
	load_dg_ListBox(m);
	load_dg_SingleSelListBox(m);
	load_dg_MultiSelListBox(m);

// --- DGPanel
	load_dg_Panel(m);

// --- DGStaticItem
	load_dg_StaticText(m);
	load_dg_CenterText(m);
	load_dg_LeftText(m);
	load_dg_RightText(m);
	load_dg_GroupBox(m);
	load_dg_Separator(m);

// --- DGUtility
	load_dg_EOL( m.def_submodule("EOL") );
	load_dg_Key( m.def_submodule("Key") );
	load_dg_CharRange(m);
	load_dg_ShortPoint(m);
	load_dg_NativeUnit(m);
	load_dg_NativeUnitPoint(m);
	load_dg_NativeUnitRect(m);
	load_dg_NativePoint(m);
	load_dg_Point(m);
	load_dg_NativeRect(m);
	load_dg_ShortRect(m);
	load_dg_Rect(m);


#endif //  TEST == 1

// --- Add bindings end
}