#pragma once

#include "../stdafx.h"

#include "DGItem.hpp"
#include "DGItemProperty.hpp"
#include "DGEditControl.hpp"
#include "DGUtility.hpp"

using namespace DG;


// --- EditDragSourceEvent

//	py::class_<EditDragSourceEvent, ItemDragSourceEvent>(m, "EditDragSourceEvent")
//		.def("GetSource", &EditDragSourceEvent::GetSource, py::return_value_policy::reference);


// --- EditDropTargetEvent

//	py::class_<EditDropTargetEvent, ItemDropTargetEvent>(m, "EditDropTargetEvent")
//		.def("GetSource", &EditDropTargetEvent::GetSource, py::return_value_policy::reference)
//		.def("GetCaretPosition", &EditDropTargetEvent::GetCaretPosition);


// --- PyEditDragSourceObserver ------------------------------------------------

class PyEditDragSourceObserver : EditDragSourceObserver {

public:
	//PyEditDragSourceObserver(PosIntEdit &item, ACExport &acExport)
	//	:m_parent(item) {
	//	this->m_parent.Attach(*this);
	//	this->m_state = acExport.m_state;
	//}

	//~PyEditDragSourceObserver() {
	//	this->m_parent.Detach(*this);
	//}

	//void EditDragStarting(const EditDragSourceEvent& ev, bool* canStart) override {

	//}

	//void EditDragStarted(const EditDragSourceEvent& ev, UShort* effect) override {

	//}

	//void EditDragStarted(const ItemDragSourceEvent& ev, UShort* effect, bool* rightDragMenu) override {

	//}

	//void EditDragEnded(const EditDragSourceEvent& ev, DragDrop::Effect effect) override {

	//}

	//void EditDragSetDelayedData(const EditDragSourceEvent& ev) override {

	//}

//private:
//	PosIntEdit		&m_parent;
//	PyThreadState	*m_state;
};


// --- PyEditDragSourceObserver ------------------------------------------------

class PyEditDropTargetObserver : EditDropTargetObserver {

public:
	//PyEditDropTargetObserver(PosIntEdit &item, ACExport &acExport)
	//	:m_parent(item) {
	//	this->m_parent.Attach(*this);
	//	this->m_state = acExport.m_state;
	//}

	//~PyEditDropTargetObserver() {
	//	this->m_parent.Detach(*this);
	//}

	//void EditDragEntered(const EditDropTargetEvent& ev, , DragDrop::Effect* effect, bool* defBehaviour) override {

	//}

	//void EditDragEntered(const EditDropTargetEvent& ev, DragDrop::Effect* effect, bool* defBehaviour, bool* rightDragMenu) override {

	//}

	//void EditDragMoved(const EditDropTargetEvent& ev, DragDrop::Effect* effect, DragDrop::Feedback* denyFeedback) override {

	//}

	//void EditDragLeft(const EditDragSourceEvent& ev,  DragDrop::Effect* effect) override {

	//}

	//void EditDropped(const EditDragSourceEvent& ev, DragDrop::Effect* effect) override {

	//}

//private:
//	PosIntEdit		&m_parent;
//	PyThreadState	*m_state;
};


//----------------------------------------------------------------------------------------------------------------------------------


// --- PyPosIntEditObserver ------------------------------------------------

class PyPosIntEditObserver : PosIntEditObserver {

public:
	PyPosIntEditObserver(PosIntEdit &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyPosIntEditObserver() {
		this->m_parent.Detach(*this);
	}

	//short SpecChanged(const ItemChangeEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecChanged", ev);
	//}

	//short SpecDragStarting(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragStarted(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEnded(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragSetDelayedData(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEntered(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragMoved(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragLeft(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDropped(const ItemDropTargetEvent& ev) override {

	//}

	void  PosIntEditChanged(const PosIntEditChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("PosIntEditChanged", ev);
	}

private:
	PosIntEdit		&m_parent;
	PyThreadState	*m_state;
};


// --- PyIntEditObserver ---------------------------------------------------

class PyIntEditObserver : IntEditObserver {

public:
	PyIntEditObserver(IntEdit &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyIntEditObserver() {
		this->m_parent.Detach(*this);
	}

	//short SpecChanged(const ItemChangeEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecChanged", ev);
	//}

	//short SpecDragStarting(const ItemDragSourceEvent& ev) override {
	//}

	//short SpecDragStarted(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEnded(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragSetDelayedData(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEntered(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragMoved(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragLeft(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDropped(const ItemDropTargetEvent& ev) override {

	//}

	void  IntEditChanged(const IntEditChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("IntEditChanged", ev);
	}

private:
	IntEdit		&m_parent;
	PyThreadState	*m_state;
};


// --- PyRealEditObserver --------------------------------------------------

class PyRealEditObserver : RealEditObserver {

public:
	PyRealEditObserver(RealEdit &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyRealEditObserver() {
		this->m_parent.Detach(*this);
	}

	//short SpecChanged(const ItemChangeEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecChanged", ev);
	//}

	//short SpecDragStarting(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragStarted(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEnded(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragSetDelayedData(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEntered(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragMoved(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragLeft(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDropped(const ItemDropTargetEvent& ev) override {

	//}

	void  RealEditChanged(const RealEditChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("RealEditChanged", ev);
	}

private:
	RealEdit		&m_parent;
	PyThreadState	*m_state;
};


// --- PyTextEditBaseObserver ----------------------------------------------

class PyTextEditBaseObserver : TextEditBaseObserver {

public:
	PyTextEditBaseObserver(TextEditBase &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyTextEditBaseObserver() {
		this->m_parent.Detach(*this);
	}

	//short SpecChanged(const ItemChangeEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecChanged", ev);
	//}

	//short SpecDragStarting(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragStarted(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEnded(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragSetDelayedData(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEntered(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragMoved(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragLeft(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDropped(const ItemDropTargetEvent& ev) override {

	//}

	void  TextEditChanged(const TextEditChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("TextEditChanged", ev);
	}

private:
	TextEditBase	&m_parent;
	PyThreadState	*m_state;
};


// --- PyShortcutEditObserver ----------------------------------------------

class PyShortcutEditObserver : ShortcutEditObserver {

public:
	PyShortcutEditObserver(ShortcutEdit &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyShortcutEditObserver() {
		this->m_parent.Detach(*this);
	}

	//short SpecChanged(const ItemChangeEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecChanged", ev);
	//}

	void  ShortcutHit(const ShortcutHitEvent& ev) override {
		OBSERVER_CALL_EVENT("ShortcutHit", ev);
	}

private:
	ShortcutEdit	&m_parent;
	PyThreadState	*m_state;
};


// --- EditControl ---------------------------------------------------------

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


// --- PosIntEdit ----------------------------------------------------------

void load_dg_PosIntEdit(py::module m) {
	// --- PosIntEditChangeEvent -------------------------------------------
	py::class_<PosIntEditChangeEvent, ItemChangeEvent>(m, "PosIntEditChangeEvent")
		.def("GetSource", &PosIntEditChangeEvent::GetSource, py::return_value_policy::reference)
		.def("GetPreviousValue", &PosIntEditChangeEvent::GetPreviousValue)
		.def("WasRelativeInput", &PosIntEditChangeEvent::WasRelativeInput);

	// --- PosIntEditObserver ----------------------------------------------
	py::class_<PyPosIntEditObserver>(m, "PosIntEditObserver", py::dynamic_attr())
		.def(py::init<PosIntEdit &, ACExport &>());

	// --- PosIntEdit ------------------------------------------------------
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
		.def("SetMin", &PosIntEdit::SetMin)
		.def("SetMax", &PosIntEdit::SetMax)
		.def("SetValue", &PosIntEdit::SetValue)
		.def("GetMin", &PosIntEdit::GetMin)
		.def("GetMax", &PosIntEdit::GetMax)
		.def("GetValue", &PosIntEdit::GetValue);
}


// --- IntEdit -------------------------------------------------------------

void load_dg_IntEdit(py::module m) {
	// --- IntEditChangeEvent ----------------------------------------------
	py::class_<IntEditChangeEvent, ItemChangeEvent>(m, "IntEditChangeEvent")
		.def("GetSource", &IntEditChangeEvent::GetSource, py::return_value_policy::reference)
		.def("GetPreviousValue", &IntEditChangeEvent::GetPreviousValue)
		.def("WasRelativeInput", &IntEditChangeEvent::WasRelativeInput);

	// --- IntEditObserver -------------------------------------------------
	py::class_<PyIntEditObserver>(m, "IntEditObserver", py::dynamic_attr())
		.def(py::init<IntEdit &, ACExport &>());

	// --- IntEdit ---------------------------------------------------------
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
		.def("SetMin", &IntEdit::SetMin)
		.def("SetMax", &IntEdit::SetMax)
		.def("SetValue", &IntEdit::SetValue)
		.def("GetMin", &IntEdit::GetMin)
		.def("GetMax", &IntEdit::GetMax)
		.def("GetValue", &IntEdit::GetValue);
}


// --- RealEdit ------------------------------------------------------------

void load_dg_RealEdit(py::module m) {
	// --- RealEditChangeEvent ---------------------------------------------
	py::class_<RealEditChangeEvent, ItemChangeEvent>(m, "RealEditChangeEvent")
		.def("GetSource", &RealEditChangeEvent::GetSource, py::return_value_policy::reference)
		.def("GetPreviousValue", &RealEditChangeEvent::GetPreviousValue)
		.def("WasRelativeInput", &RealEditChangeEvent::WasRelativeInput);

	// --- RealEditObserver
	py::class_<PyRealEditObserver>(m, "RealEditObserver", py::dynamic_attr())
		.def(py::init<RealEdit &, ACExport &>());

	// --- RealEdit ---------------------------------------------------------
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
		.def("SetMin", &RealEdit::SetMin)
		.def("SetMax", &RealEdit::SetMax)
		.def("SetValue", &RealEdit::SetValue)
		.def("GetMin", &RealEdit::GetMin)
		.def("GetMax", &RealEdit::GetMax)
		.def("GetValue", &RealEdit::GetValue);
}


// --- RealEditEX ----------------------------------------------------------

void load_dg_RealEditEX(py::module m) {
	// --- LengthEdit ------------------------------------------------------
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

	// --- AreaEdit ---------------------------------------------------------
	py::class_<AreaEdit, RealEdit>(m, "AreaEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);

	// --- VolumeEdit -------------------------------------------------------
	py::class_<VolumeEdit, RealEdit>(m, "VolumeEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);

	// --- AngleEdit --------------------------------------------------------
	py::class_<AngleEdit, RealEdit>(m, "AngleEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);
	
	// --- PolarAngleEdit ---------------------------------------------------
	py::class_<PolarAngleEdit, RealEdit>(m, "PolarAngleEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, EditControl::FrameType, RealEdit::AbsRelType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);

	// --- MMPointEdit ------------------------------------------------------
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


// --- TextEditBase --------------------------------------------------------

void load_dg_TextEditBase(py::module m) {
	// --- TextEditChangeEvent ---------------------------------------------
	py::class_<TextEditChangeEvent, ItemChangeEvent>(m, "TextEditChangeEvent")
		.def("GetSource",&TextEditChangeEvent::GetSource, py::return_value_policy::reference);

	// --- RealEditObserver ------------------------------------------------
	py::class_<PyTextEditBaseObserver>(m, "TextEditBaseObserver", py::dynamic_attr())
		.def(py::init<TextEditBase &, ACExport &>());

	// --- TextEditBase ----------------------------------------------------
	py::class_<TextEditBase, EditControl, ItemTextProperty>(m, "TextEditBase")
		.def("SetSelection", &TextEditBase::SetSelection)
		.def("GetSelection", &TextEditBase::GetSelection);
}


// --- TextEditBaseEX ------------------------------------------------------
void load_dg_TextEditBaseEX(py::module m) {
	// --- TextEdit --------------------------------------------------------
	py::class_<TextEdit, TextEditBase, ItemVariousProperty, ItemTextLengthLimitProperty>(m, "TextEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, short, EditControl::FrameType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);

	// --- PasswordEdit ----------------------------------------------------
	py::class_<PasswordEdit, TextEditBase, ItemTextLengthLimitProperty>(m, "PasswordEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, short, EditControl::FrameType, EditControl::UpdateType, EditControl::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("update") = EditControl::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable);

	// --- MultiLineEdit ---------------------------------------------------
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


// --- ShortcutEdit --------------------------------------------------------

void load_dg_ShortcutEdit(py::module m) {
	// --- ShortcutHitEvent ------------------------------------------------
	py::class_<ShortcutHitEvent, ItemChangeEvent>(m, "ShortcutHitEvent")
		.def("GetKey", &ShortcutHitEvent::GetKey)
		.def("GetModifierFlags", &ShortcutHitEvent::GetModifierFlags)
		.def("GetSource",&ShortcutHitEvent::GetSource, py::return_value_policy::reference);

	// --- PosIntEditObserver ----------------------------------------------
	py::class_<PyShortcutEditObserver>(m, "ShortcutEditObserver", py::dynamic_attr())
		.def(py::init<ShortcutEdit &, ACExport &>());

	// --- ShortcutEdit ----------------------------------------------------
	py::class_<ShortcutEdit, TextEditBase, ItemTextLengthLimitProperty>(m, "ShortcutEdit")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, short, EditControl::FrameType, EditControl::UpdateType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = EditControl::FrameType::Frame,
			py::arg("update") = EditControl::UpdateType::Update);
}
