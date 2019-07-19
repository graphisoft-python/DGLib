#pragma once

#include "../stdafx.h"

#include "DGItem.hpp"
#include "DGItemProperty.hpp"
#include "DGEditControl.hpp"
#include "DGUtility.hpp"

using namespace DG;


// --- EditDragSourceEvent

//void load_dg_EditDragSourceEvent(py::module m) {
//	py::class_<EditDragSourceEvent, ItemDragSourceEvent>(m, "EditDragSourceEvent")
//		.def("GetSource", &EditDragSourceEvent::GetSource, py::return_value_policy::reference);
//}


// --- EditDragSourceObserver

//void load_dg_EditDragSourceObserver(py::module m) {
//	py::class_<EditDragSourceObserver>(m, "EditDragSourceObserver")
//		.def("EditDragStarting", &EditDragSourceObserver::EditDragStarting)
//		.def("EditDragStarted", (void (EditDragSourceObserver::*)
//			(const EditDragSourceEvent &, UShort *)) &EditDragSourceObserver::EditDragStarted)
//		.def("EditDragStarted", (void(EditDragSourceObserver::*) 
//			(const EditDragSourceEvent &, UShort *, bool *)) &EditDragSourceObserver::EditDragStarted)
//		.def("EditDragEnded", &EditDragSourceObserver::EditDragEnded)
//		.def("EditDragSetDelayedData", &EditDragSourceObserver::EditDragSetDelayedData);
//}


// --- EditDropTargetEvent

//void load_dg_EditDropTargetEvent(py::module m) {
//	py::class_<EditDropTargetEvent, ItemDropTargetEvent>(m, "EditDropTargetEvent")
//		.def("GetSource", &EditDropTargetEvent::GetSource, py::return_value_policy::reference)
//
//		.def("GetCaretPosition", &EditDropTargetEvent::GetCaretPosition);
//}


// --- EditDropTargetObserver

//void load_dg_EditDropTargetObserver(py::module m) {
//	py::class_<EditDropTargetObserver>(m, "EditDropTargetObserver")
//		.def("EditDragEntered", (void (EditDropTargetObserver::*)
//			(const EditDropTargetEvent &, DragDrop::Effect *, bool *)) &EditDropTargetObserver::EditDragEntered)
//		.def("EditDragEntered", (void (EditDropTargetObserver::*)
//			(const EditDropTargetEvent &, DragDrop::Effect *, bool *, bool *)) &EditDropTargetObserver::EditDragEntered)
//		.def("EditDragMoved", &EditDropTargetObserver::EditDragMoved)
//		.def("EditDragLeft", &EditDropTargetObserver::EditDragLeft)
//		.def("EditDropped", &EditDropTargetObserver::EditDropped);
//}


// --- PosIntEditChangeEvent

//void load_dg_PosIntEditChangeEvent(py::module m) {
//	py::class_<PosIntEditChangeEvent, ItemChangeEvent>(m, "PosIntEditChangeEvent")
//		.def("GetSource", &PosIntEditChangeEvent::GetSource, py::return_value_policy::reference)
//
//		.def("GetPreviousValue", &PosIntEditChangeEvent::GetPreviousValue)
//		.def("WasRelativeInput", &PosIntEditChangeEvent::WasRelativeInput);
//}


// --- PosIntEditObserver

//void load_dg_PosIntEditObserver(py::module m) {
//	py::class_<PosIntEditObserver, ItemObserver, EditDragSourceObserver, EditDropTargetObserver>(m, "PosIntEditObserver")
//		.def(py::init<>());
//}


// --- IntEditChangeEvent

//void load_dg_IntEditChangeEvent(py::module m) {
//	py::class_<IntEditChangeEvent, ItemChangeEvent>(m, "IntEditChangeEvent")
//		.def("GetSource", &IntEditChangeEvent::GetSource, py::return_value_policy::reference)
//
//		.def("GetPreviousValue", &IntEditChangeEvent::GetPreviousValue)
//		.def("WasRelativeInput", &IntEditChangeEvent::WasRelativeInput);
//}


// --- IntEditObserver

//void load_dg_IntEditObserver(py::module m) {
//	py::class_<IntEditObserver, ItemObserver, EditDragSourceObserver, EditDropTargetObserver>(m, "IntEditObserver")
//		.def(py::init<>());
//}


// --- RealEditChangeEvent

//void load_dg_RealEditChangeEvent(py::module m) {
//	py::class_<RealEditChangeEvent, ItemChangeEvent>(m, "RealEditChangeEvent")
//		.def("GetSource", &RealEditChangeEvent::GetSource, py::return_value_policy::reference)
//
//		.def("GetPreviousValue", &RealEditChangeEvent::GetPreviousValue)
//		.def("WasRelativeInput", &RealEditChangeEvent::WasRelativeInput);
//}


// --- RealEditObserver
//void load_dg_RealEditObserver(py::module m) {
//	py::class_<RealEditObserver, ItemObserver, EditDragSourceObserver, EditDropTargetObserver>(m, "RealEditObserver")
//		.def(py::init<>());
//}


// --- TextEditChangeEvent

//void load_dg_TextEditChangeEvent(py::module m) {
//	py::class_<TextEditChangeEvent, ItemChangeEvent>(m, "TextEditChangeEvent")
//		.def("GetSource",&TextEditChangeEvent::GetSource, py::return_value_policy::reference);
//}


// --- TextEditBaseObserver

//void load_dg_TextEditBaseObserver(py::module m) {
//	py::class_<TextEditBaseObserver, ItemObserver, EditDragSourceObserver, EditDropTargetObserver>(m, "TextEditBaseObserver")
//		.def(py::init<>());
//}


// --- ShortcutHitEvent

//void load_dg_ShortcutHitEvent(py::module m) {
//	py::class_<ShortcutHitEvent, ItemChangeEvent>(m, "ShortcutHitEvent")
//		.def("GetKey", &ShortcutHitEvent::GetKey)
//		.def("GetModifierFlags", &ShortcutHitEvent::GetModifierFlags)
//
//		.def("GetSource",&ShortcutHitEvent::GetSource, py::return_value_policy::reference);
//}


// --- ShortcutEditObserver

//void load_dg_ShortcutHitEvent(py::module m) {
//	py::class_<ShortcutEditObserver, ItemObserver>(m, "ShortcutEditObserver")
//		.def(py::init<>());
//}


// --- EditControl

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


// --- PosIntEdit

void load_dg_PosIntEdit(py::module m) {
	py::class_<PosIntEdit, EditControl, ItemVariousProperty> m_posIntEdit(m, "PosIntEdit");

	py::enum_<PosIntEdit::AbsRelType>(m_posIntEdit, "AbsRelType")
		.value("Absolute", PosIntEdit::AbsRelType::Absolute)
		.value("Relative", PosIntEdit::AbsRelType::Relative)
		.export_values();


	m_posIntEdit
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, PosIntEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"), 
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = PosIntEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable)

		//.def("Attach", &PosIntEdit::Attach)
		//.def("Detach", &PosIntEdit::Detach)

		.def("SetMin", &PosIntEdit::SetMin)
		.def("SetMax", &PosIntEdit::SetMax)
		.def("SetValue", &PosIntEdit::SetValue)

		.def("GetMin", &PosIntEdit::GetMin)
		.def("GetMax", &PosIntEdit::GetMax)
		.def("GetValue", &PosIntEdit::GetValue);
}


// --- IntEdit

void load_dg_IntEdit(py::module m) {
	py::class_<IntEdit, EditControl, ItemVariousProperty> m_intEdit(m, "IntEdit");

	py::enum_<IntEdit::AbsRelType>(m_intEdit, "AbsRelType")
		.value("Absolute", IntEdit::AbsRelType::Absolute)
		.value("Relative", IntEdit::AbsRelType::Relative)
		.export_values();


	m_intEdit
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, IntEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"), 
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = IntEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable)

		//.def("Attach", &PosIntEdit::Attach)
		//.def("Detach", &PosIntEdit::Detach)

		.def("SetMin", &IntEdit::SetMin)
		.def("SetMax", &IntEdit::SetMax)
		.def("SetValue", &IntEdit::SetValue)

		.def("GetMin", &IntEdit::GetMin)
		.def("GetMax", &IntEdit::GetMax)
		.def("GetValue", &IntEdit::GetValue);
}


// --- RealEdit

void load_dg_RealEdit(py::module m) {
	py::class_<RealEdit, EditControl, ItemVariousProperty> m_realEdit(m, "RealEdit");

	py::enum_<RealEdit::AbsRelType>(m_realEdit, "AbsRelType")
		.value("Absolute", RealEdit::AbsRelType::Absolute)
		.value("Relative", RealEdit::AbsRelType::Relative)
		.export_values();


	m_realEdit
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"), 
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable)

		//.def("Attach", &PosIntEdit::Attach)
		//.def("Detach", &PosIntEdit::Detach)

		.def("SetMin", &RealEdit::SetMin)
		.def("SetMax", &RealEdit::SetMax)
		.def("SetValue", &RealEdit::SetValue)

		.def("GetMin", &RealEdit::GetMin)
		.def("GetMax", &RealEdit::GetMax)
		.def("GetValue", &RealEdit::GetValue);
}


// --- LengthEdit

void load_dg_LengthEdit(py::module m) {
	py::class_<LengthEdit, RealEdit> m_lengthEdit(m, "LengthEdit");

	py::enum_<LengthEdit::ChangeFontType>(m_lengthEdit, "ChangeFontType")
		.value("ChangeFont", LengthEdit::ChangeFontType::ChangeFont)
		.value("NoChangeFont", LengthEdit::ChangeFontType::NoChangeFont)
		.export_values();


	m_lengthEdit
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, LengthEdit::ChangeFontType, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"), 
			py::arg("rect"),
			py::arg("chgFont") = LengthEdit::ChangeFontType::ChangeFont,
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);
}


// --- AreaEdit

void load_dg_AreaEdit(py::module m) {
	py::class_<AreaEdit, RealEdit> (m, "AreaEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);
}


// --- VolumeEdit

void load_dg_VolumeEdit(py::module m) {
	py::class_<VolumeEdit, RealEdit>(m, "VolumeEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);
}


// --- AngleEdit

void load_dg_AngleEdit(py::module m) {
	py::class_<AngleEdit, RealEdit>(m, "AngleEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);
}


// --- PolarAngleEdit

void load_dg_PolarAngleEdit(py::module m) {
	py::class_<PolarAngleEdit, RealEdit>(m, "PolarAngleEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);
}


// --- MMPointEdit

void load_dg_MMPointEdit(py::module m) {
	py::class_<MMPointEdit, RealEdit>(m, "MMPointEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);
}


// --- TextEditBase

void load_dg_TextEditBase(py::module m) {
	py::class_<TextEditBase, EditControl, ItemTextProperty>(m, "TextEditBase")
		//.def("Attach", &PosIntEdit::Attach)
		//.def("Detach", &PosIntEdit::Detach)

		.def("SetSelection", &TextEditBase::SetSelection)
		.def("GetSelection", &TextEditBase::GetSelection);
}


// --- TextEdit

void load_dg_TextEdit(py::module m) {
	py::class_<TextEdit, TextEditBase, ItemVariousProperty, ItemTextLengthLimitProperty>(m, "TextEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, short, EditControl::FrameType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);
}


// --- PasswordEdit

void load_dg_PasswordEdit(py::module m) {
	py::class_<PasswordEdit, TextEditBase, ItemTextLengthLimitProperty>(m, "PasswordEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, short, EditControl::FrameType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);
}


// --- ShortcutEdit

void load_dg_ShortcutEdit(py::module m) {
	py::class_<ShortcutEdit, TextEditBase, ItemTextLengthLimitProperty>(m, "ShortcutEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, short, EditControl::FrameType, EditControl::UpdateType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("update") = EditControl::UpdateType::Update);

		//.def("Attach", &PosIntEdit::Attach)
		//.def("Detach", &PosIntEdit::Detach)
}


// --- MultiLineEdit

void load_dg_MultiLineEdit(py::module m) {
	py::class_<MultiLineEdit, TextEditBase> m_multiLineEdit(m, "MultiLineEdit");
	
	py::enum_<MultiLineEdit::ScrollType>(m_multiLineEdit, "ScrollType")
		.value("NoScroll", MultiLineEdit::ScrollType::NoScroll)
		.value("HScroll", MultiLineEdit::ScrollType::HScroll)
		.value("VScroll", MultiLineEdit::ScrollType::VScroll)
		.value("HVScroll", MultiLineEdit::ScrollType::HVScroll)
		.export_values();
	

	m_multiLineEdit
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, MultiLineEdit::ScrollType, EditControl::FrameType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("scroll") = MultiLineEdit::ScrollType::NoScroll,
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable)

		.def("GetText", &MultiLineEdit::GetText,
			py::arg("eolType") = EOL::Default);
}
