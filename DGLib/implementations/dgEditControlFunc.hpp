#include "../stdafx.h"
#include "DGItem.hpp"
#include "DGItemProperty.hpp"
#include "DGEditControl.hpp"

using namespace DG;

void load_dg_EditControl(py::module m) {
	py::class_<EditControl, Item, ItemFontProperty, FocusableProperty> m_editControl(m, "EditControl");

	py::enum_<EditControl::FrameType>(m_editControl, "FrameType")
		.value("Frame", EditControl::FrameType::Frame)
		.value("NoFrame", EditControl::FrameType::NoFrame)
		.export_values();

	py::enum_<EditControl::UpdateType>(m_editControl, "UpdateType")
		.value("Update", EditControl::UpdateType::Update)
		.value("NoUpdate", EditControl::UpdateType::NoUpdate)
		.value("NoDelay", EditControl::UpdateType::NoDelay)
		.export_values();


	py::enum_<EditControl::ReadOnlyType>(m_editControl, "ReadOnlyType")
		.value("Editable", EditControl::ReadOnlyType::Editable)
		.value("ReadOnly", EditControl::ReadOnlyType::ReadOnly)
		.export_values();
}

void load_dg_PosIntEdit(py::module m) {
	py::class_<PosIntEdit, EditControl, ItemVariousProperty> m_posIntEdit(m, "PosIntEdit");

	py::enum_<PosIntEdit::AbsRelType>(m_posIntEdit, "AbsRelType")
		.value("Absolute", PosIntEdit::AbsRelType::Absolute)
		.value("Relative", PosIntEdit::AbsRelType::Relative)
		.export_values();


	m_posIntEdit
		.def(py::init<Panel &, Rect &, PosIntEdit::FrameType, PosIntEdit::AbsRelType, PosIntEdit::UpdateType, PosIntEdit::ReadOnlyType>(),
			py::arg("panel"), 
			py::arg("rect"),
			py::arg("frame") = PosIntEdit::FrameType::Frame,
			py::arg("absRel") = PosIntEdit::AbsRelType::Absolute,
			py::arg("update") = PosIntEdit::UpdateType::Update,
			py::arg("readOnly") = PosIntEdit::ReadOnlyType::Editable)

		.def("SetMin", &PosIntEdit::SetMin)
		.def("SetMax", &PosIntEdit::SetMax)
		.def("SetValue", &PosIntEdit::SetValue)

		.def("GetMin", &PosIntEdit::GetMin)
		.def("GetMax", &PosIntEdit::GetMax)
		.def("GetValue", &PosIntEdit::GetValue);
}

void load_dg_IntEdit(py::module m) {
	py::class_<IntEdit, EditControl, ItemVariousProperty> m_intEdit(m, "IntEdit");

	py::enum_<IntEdit::AbsRelType>(m_intEdit, "AbsRelType")
		.value("Absolute", IntEdit::AbsRelType::Absolute)
		.value("Relative", IntEdit::AbsRelType::Relative)
		.export_values();


	m_intEdit
		.def(py::init<Panel &, Rect &, IntEdit::FrameType, IntEdit::AbsRelType, IntEdit::UpdateType, IntEdit::ReadOnlyType>(),
			py::arg("panel"), 
			py::arg("rect"),
			py::arg("frame") = IntEdit::FrameType::Frame,
			py::arg("absRel") = IntEdit::AbsRelType::Absolute,
			py::arg("update") = IntEdit::UpdateType::Update,
			py::arg("readOnly") = IntEdit::ReadOnlyType::Editable)

		.def("SetMin", &IntEdit::SetMin)
		.def("SetMax", &IntEdit::SetMax)
		.def("SetValue", &IntEdit::SetValue)

		.def("GetMin", &IntEdit::GetMin)
		.def("GetMax", &IntEdit::GetMax)
		.def("GetValue", &IntEdit::GetValue);
}

void load_dg_RealEdit(py::module m) {
	py::class_<RealEdit, EditControl, ItemVariousProperty> m_realEdit(m, "RealEdit");

	py::enum_<RealEdit::AbsRelType>(m_realEdit, "AbsRelType")
		.value("Absolute", RealEdit::AbsRelType::Absolute)
		.value("Relative", RealEdit::AbsRelType::Relative)
		.export_values();


	m_realEdit
		.def(py::init<Panel &, Rect &, RealEdit::FrameType, RealEdit::AbsRelType, RealEdit::UpdateType, RealEdit::ReadOnlyType>(), 
			py::arg("panel"), 
			py::arg("rect"),
			py::arg("frame") = RealEdit::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = RealEdit::UpdateType::Update,
			py::arg("readOnly") = RealEdit::ReadOnlyType::Editable)

		.def("SetMin", &RealEdit::SetMin)
		.def("SetMax", &RealEdit::SetMax)
		.def("SetValue", &RealEdit::SetValue)

		.def("GetMin", &RealEdit::GetMin)
		.def("GetMax", &RealEdit::GetMax)
		.def("GetValue", &RealEdit::GetValue);
}

void load_dg_LengthEdit(py::module m) {
	py::class_<LengthEdit, RealEdit> m_lengthEdit(m, "LengthEdit");

	py::enum_<LengthEdit::ChangeFontType>(m_lengthEdit, "ChangeFontType")
		.value("ChangeFont", LengthEdit::ChangeFontType::ChangeFont)
		.value("NoChangeFont", LengthEdit::ChangeFontType::NoChangeFont)
		.export_values();


	m_lengthEdit
		.def(py::init<Panel &, Rect &, LengthEdit::ChangeFontType, LengthEdit::FrameType, LengthEdit::AbsRelType, LengthEdit::UpdateType, LengthEdit::ReadOnlyType>(),
			py::arg("panel"), 
			py::arg("rect"),
			py::arg("chgFont") = LengthEdit::ChangeFontType::ChangeFont,
			py::arg("frame") = LengthEdit::FrameType::Frame,
			py::arg("absRel") = LengthEdit::AbsRelType::Absolute,
			py::arg("update") = LengthEdit::UpdateType::Update,
			py::arg("readOnly") = LengthEdit::ReadOnlyType::Editable);
}

void load_dg_AreaEdit(py::module m) {
	py::class_<AreaEdit, RealEdit> (m, "AreaEdit")
		.def(py::init<Panel &, Rect &, AreaEdit::FrameType, AreaEdit::AbsRelType, AreaEdit::UpdateType, AreaEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = AreaEdit::FrameType::Frame,
			py::arg("absRel") = AreaEdit::AbsRelType::Absolute,
			py::arg("update") = AreaEdit::UpdateType::Update,
			py::arg("readOnly") = AreaEdit::ReadOnlyType::Editable);
}

void load_dg_VolumeEdit(py::module m) {
	py::class_<VolumeEdit, RealEdit>(m, "VolumeEdit")
		.def(py::init<Panel &, Rect &, VolumeEdit::FrameType, VolumeEdit::AbsRelType, VolumeEdit::UpdateType, VolumeEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = VolumeEdit::FrameType::Frame,
			py::arg("absRel") = VolumeEdit::AbsRelType::Absolute,
			py::arg("update") = VolumeEdit::UpdateType::Update,
			py::arg("readOnly") = VolumeEdit::ReadOnlyType::Editable);
}

void load_dg_AngleEdit(py::module m) {
	py::class_<AngleEdit, RealEdit>(m, "AngleEdit")
		.def(py::init<Panel &, Rect &, AngleEdit::FrameType, AngleEdit::AbsRelType, AngleEdit::UpdateType, AngleEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = AngleEdit::FrameType::Frame,
			py::arg("absRel") = AngleEdit::AbsRelType::Absolute,
			py::arg("update") = AngleEdit::UpdateType::Update,
			py::arg("readOnly") = AngleEdit::ReadOnlyType::Editable);
}

void load_dg_PolarAngleEdit(py::module m) {
	py::class_<PolarAngleEdit, RealEdit>(m, "PolarAngleEdit")
		.def(py::init<Panel &, Rect &, PolarAngleEdit::FrameType, PolarAngleEdit::AbsRelType, PolarAngleEdit::UpdateType, PolarAngleEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = PolarAngleEdit::FrameType::Frame,
			py::arg("absRel") = PolarAngleEdit::AbsRelType::Absolute,
			py::arg("update") = PolarAngleEdit::UpdateType::Update,
			py::arg("readOnly") = PolarAngleEdit::ReadOnlyType::Editable);
}

void load_dg_MMPointEdit(py::module m) {
	py::class_<MMPointEdit, RealEdit>(m, "MMPointEdit")
		.def(py::init<Panel &, Rect &, MMPointEdit::FrameType, MMPointEdit::AbsRelType, MMPointEdit::UpdateType, MMPointEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = MMPointEdit::FrameType::Frame,
			py::arg("absRel") = MMPointEdit::AbsRelType::Absolute,
			py::arg("update") = MMPointEdit::UpdateType::Update,
			py::arg("readOnly") = MMPointEdit::ReadOnlyType::Editable);
}

void load_dg_TextEditBase(py::module m) {
	py::class_<TextEditBase, EditControl, ItemTextProperty>(m, "TextEditBase")
		.def("SetSelection", &TextEditBase::SetSelection)
		.def("GetSelection", &TextEditBase::GetSelection);
}

void load_dg_TextEdit(py::module m) {
	py::class_<TextEdit, TextEditBase, ItemVariousProperty, ItemTextLengthLimitProperty>(m, "TextEdit")
		.def(py::init<Panel &, Rect &, short, TextEdit::FrameType, TextEdit::UpdateType, TextEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = TextEdit::FrameType::Frame,
			py::arg("update") = TextEdit::UpdateType::Update,
			py::arg("readOnly") = TextEdit::ReadOnlyType::Editable);
}

void load_dg_PasswordEdit(py::module m) {
	py::class_<PasswordEdit, TextEditBase, ItemTextLengthLimitProperty>(m, "PasswordEdit")
		.def(py::init<Panel &, Rect &, short, PasswordEdit::FrameType, PasswordEdit::UpdateType, PasswordEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = PasswordEdit::FrameType::Frame,
			py::arg("update") = PasswordEdit::UpdateType::Update,
			py::arg("readOnly") = PasswordEdit::ReadOnlyType::Editable);
}

void load_dg_ShortcutEdit(py::module m) {
	py::class_<ShortcutEdit, TextEditBase, ItemTextLengthLimitProperty>(m, "ShortcutEdit")
		.def(py::init<Panel &, Rect &, short, ShortcutEdit::FrameType, ShortcutEdit::UpdateType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = ShortcutEdit::FrameType::Frame,
			py::arg("update") = ShortcutEdit::UpdateType::Update);
}

void load_dg_MultiLineEdit(py::module m) {
	py::class_<MultiLineEdit, TextEditBase> m_multiLineEdit(m, "MultiLineEdit");
	
	py::enum_<MultiLineEdit::ScrollType>(m_multiLineEdit, "ScrollType")
		.value("NoScroll", MultiLineEdit::ScrollType::NoScroll)
		.value("HScroll", MultiLineEdit::ScrollType::HScroll)
		.value("VScroll", MultiLineEdit::ScrollType::VScroll)
		.value("HVScroll", MultiLineEdit::ScrollType::HVScroll)
		.export_values();
	

	m_multiLineEdit
		.def(py::init<Panel &, Rect &, MultiLineEdit::ScrollType, MultiLineEdit::FrameType, MultiLineEdit::UpdateType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("scroll") = MultiLineEdit::ScrollType::NoScroll,
			py::arg("frame") = MultiLineEdit::FrameType::Frame,
			py::arg("update") = MultiLineEdit::UpdateType::Update);
}