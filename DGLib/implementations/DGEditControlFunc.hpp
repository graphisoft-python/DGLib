#pragma once

#include "../stdafx.h"

#include "DGItem.hpp"
#include "DGItemProperty.hpp"
#include "DGEditControl.hpp"
#include "DGUtility.hpp"

using namespace DG;


// --- PyPosIntEditObserver ----------------------------------------------------------------

class PyPosIntEditObserver : PosIntEditObserver {

public:
	PyPosIntEditObserver(PosIntEdit &item)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = GetCurrentAppState();
	}

	~PyPosIntEditObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS
	EDITDRAGSOURCEOBSERVER
	EDITDRAGTARGETOBSERVER

	void  PosIntEditChanged(const PosIntEditChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("PosIntEditChanged", ev);
	}

private:
	PosIntEdit		&m_parent;
	PyThreadState	*m_state;
};


// --- PyIntEditObserver -------------------------------------------------------------------

class PyIntEditObserver : IntEditObserver {

public:
	PyIntEditObserver(IntEdit &item)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = GetCurrentAppState();
	}

	~PyIntEditObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS
	EDITDRAGSOURCEOBSERVER
	EDITDRAGTARGETOBSERVER

	void  IntEditChanged(const IntEditChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("IntEditChanged", ev);
	}

private:
	IntEdit			&m_parent;
	PyThreadState	*m_state;
};


// --- PyRealEditObserver ------------------------------------------------------------------

class PyRealEditObserver : RealEditObserver {

public:
	PyRealEditObserver(RealEdit &item)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = GetCurrentAppState();
	}

	~PyRealEditObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS
	EDITDRAGSOURCEOBSERVER
	EDITDRAGTARGETOBSERVER

	void  RealEditChanged(const RealEditChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("RealEditChanged", ev);
	}

private:
	RealEdit		&m_parent;
	PyThreadState	*m_state;
};


// --- PyTextEditBaseObserver --------------------------------------------------------------

class PyTextEditBaseObserver : TextEditBaseObserver {

public:
	PyTextEditBaseObserver(TextEditBase &item)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = GetCurrentAppState();
	}

	~PyTextEditBaseObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS
	EDITDRAGSOURCEOBSERVER
	EDITDRAGTARGETOBSERVER

	void  TextEditChanged(const TextEditChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("TextEditChanged", ev);
	}

private:
	TextEditBase	&m_parent;
	PyThreadState	*m_state;
};


// --- PyShortcutEditObserver --------------------------------------------------------------

class PyShortcutEditObserver : ShortcutEditObserver/* ,ItemObserver*/ {

public:
	PyShortcutEditObserver(ShortcutEdit &item)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = GetCurrentAppState();
	}

	~PyShortcutEditObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS

	void  ShortcutHit(const ShortcutHitEvent& ev) override {
		OBSERVER_CALL_EVENT("ShortcutHit", ev);
	}

private:
	ShortcutEdit	&m_parent;
	PyThreadState	*m_state;
};


// --- EditControl -------------------------------------------------------------------------

void load_EditControl(py::module m) {
	// --- EditDragSourceEvent -------------------------------------------------------------
	//py::class_<EditDragSourceEvent, ItemDragSourceEvent>(m, "EditDragSourceEvent")
	//	.def("GetSource", &EditDragSourceEvent::GetSource, py::return_value_policy::reference);

	// --- EditDropTargetEvent -------------------------------------------------------------
	//py::class_<EditDropTargetEvent, ItemDropTargetEvent>(m, "EditDropTargetEvent")
	//	.def("GetSource", &EditDropTargetEvent::GetSource, py::return_value_policy::reference)
	//	.def("GetCaretPosition", &EditDropTargetEvent::GetCaretPosition);

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


// --- PosIntEdit --------------------------------------------------------------------------

void load_PosIntEdit(py::module m) {
	// --- PosIntEdit ----------------------------------------------------------------------
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

	// --- PosIntEditChangeEvent -----------------------------------------------------------
	py::class_<PosIntEditChangeEvent, ItemChangeEvent>(m, "PosIntEditChangeEvent")
		.def("GetSource", &PosIntEditChangeEvent::GetSource, py::return_value_policy::reference)
		.def("GetPreviousValue", &PosIntEditChangeEvent::GetPreviousValue)
		.def("WasRelativeInput", &PosIntEditChangeEvent::WasRelativeInput);

	// --- PosIntEditObserver --------------------------------------------------------------
	py::class_<PyPosIntEditObserver>(m, "PosIntEditObserver", py::dynamic_attr())
		.def(py::init<PosIntEdit &>());
}


// --- IntEdit -----------------------------------------------------------------------------

void load_IntEdit(py::module m) {
	// --- IntEdit -------------------------------------------------------------------------
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

	// --- IntEditChangeEvent --------------------------------------------------------------
	py::class_<IntEditChangeEvent, ItemChangeEvent>(m, "IntEditChangeEvent")
		.def("GetSource", &IntEditChangeEvent::GetSource, py::return_value_policy::reference)
		.def("GetPreviousValue", &IntEditChangeEvent::GetPreviousValue)
		.def("WasRelativeInput", &IntEditChangeEvent::WasRelativeInput);

	// --- IntEditObserver -----------------------------------------------------------------
	py::class_<PyIntEditObserver>(m, "IntEditObserver", py::dynamic_attr())
		.def(py::init<IntEdit &>());
}


// --- RealEdit ----------------------------------------------------------------------------

void load_RealEdit(py::module m) {
	// --- RealEdit -------------------------------------------------------------------------
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

	// --- RealEditChangeEvent -------------------------------------------------------------
	py::class_<RealEditChangeEvent, ItemChangeEvent>(m, "RealEditChangeEvent")
		.def("GetSource", &RealEditChangeEvent::GetSource, py::return_value_policy::reference)
		.def("GetPreviousValue", &RealEditChangeEvent::GetPreviousValue)
		.def("WasRelativeInput", &RealEditChangeEvent::WasRelativeInput);

	// --- RealEditObserver
	py::class_<PyRealEditObserver>(m, "RealEditObserver", py::dynamic_attr())
		.def(py::init<RealEdit &>());
}


// --- RealEditEX --------------------------------------------------------------------------

void load_RealEditEX(py::module m) {
	// --- LengthEdit ----------------------------------------------------------------------
	py::class_<LengthEdit, RealEdit> m_lengthEdit(m, "LengthEdit");

	py::enum_<LengthEdit::ChangeFontType>(m_lengthEdit, "ChangeFontType")
		.value("ChangeFont", LengthEdit::ChangeFontType::ChangeFont)
		.value("NoChangeFont", LengthEdit::ChangeFontType::NoChangeFont)
		.export_values();

	m_lengthEdit
		.def(py::init<Panel &, Rect &, LengthEdit::ChangeFontType, LengthEdit::FrameType, RealEdit::AbsRelType, LengthEdit::UpdateType, LengthEdit::ReadOnlyType>(),
			py::arg("panel"), 
			py::arg("rect"),
			py::arg("chgFont") = LengthEdit::ChangeFontType::ChangeFont,
			py::arg("frame") = LengthEdit::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = LengthEdit::UpdateType::Update,
			py::arg("readOnly") = LengthEdit::ReadOnlyType::Editable);

	// --- AreaEdit ------------------------------------------------------------------------
	py::class_<AreaEdit, RealEdit>(m, "AreaEdit")
		.def(py::init<Panel &, Rect &, AreaEdit::FrameType, RealEdit::AbsRelType, AreaEdit::UpdateType, AreaEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = AreaEdit::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = AreaEdit::UpdateType::Update,
			py::arg("readOnly") = AreaEdit::ReadOnlyType::Editable);

	// --- VolumeEdit ----------------------------------------------------------------------
	py::class_<VolumeEdit, RealEdit>(m, "VolumeEdit")
		.def(py::init<Panel &, Rect &, VolumeEdit::FrameType, RealEdit::AbsRelType, VolumeEdit::UpdateType, VolumeEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = VolumeEdit::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = VolumeEdit::UpdateType::Update,
			py::arg("readOnly") = VolumeEdit::ReadOnlyType::Editable);

	// --- AngleEdit -----------------------------------------------------------------------
	py::class_<AngleEdit, RealEdit>(m, "AngleEdit")
		.def(py::init<Panel &, Rect &, AngleEdit::FrameType, RealEdit::AbsRelType, AngleEdit::UpdateType, AngleEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = AngleEdit::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = AngleEdit::UpdateType::Update,
			py::arg("readOnly") = AngleEdit::ReadOnlyType::Editable);
	
	// --- PolarAngleEdit ------------------------------------------------------------------
	py::class_<PolarAngleEdit, RealEdit>(m, "PolarAngleEdit")
		.def(py::init<Panel &, Rect &, PolarAngleEdit::FrameType, RealEdit::AbsRelType, PolarAngleEdit::UpdateType, PolarAngleEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = PolarAngleEdit::FrameType::Frame,
			py::arg("absRel") = RealEdit::AbsRelType::Absolute,
			py::arg("update") = PolarAngleEdit::UpdateType::Update,
			py::arg("readOnly") = PolarAngleEdit::ReadOnlyType::Editable);

	// --- MMPointEdit ---------------------------------------------------------------------
	py::class_<MMPointEdit, RealEdit>(m, "MMPointEdit")
		.def(py::init<Panel &, Rect &, MMPointEdit::FrameType, RealEdit::AbsRelType, MMPointEdit::UpdateType, MMPointEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("frame") = MMPointEdit::FrameType::Frame,
			py::arg("absRel") = MMPointEdit::AbsRelType::Absolute,
			py::arg("update") = MMPointEdit::UpdateType::Update,
			py::arg("readOnly") = MMPointEdit::ReadOnlyType::Editable);
}


// --- TextEditBase ------------------------------------------------------------------------

void load_TextEditBase(py::module m) {
	// --- TextEditBase --------------------------------------------------------------------
	py::class_<TextEditBase, EditControl, ItemTextProperty>(m, "TextEditBase")
		.def("SetSelection", &TextEditBase::SetSelection)
		.def("GetSelection", &TextEditBase::GetSelection);

	// --- TextEditChangeEvent -------------------------------------------------------------
	py::class_<TextEditChangeEvent, ItemChangeEvent>(m, "TextEditChangeEvent")
		.def("GetSource",&TextEditChangeEvent::GetSource, py::return_value_policy::reference);

	// --- RealEditObserver ----------------------------------------------------------------
	py::class_<PyTextEditBaseObserver>(m, "TextEditBaseObserver", py::dynamic_attr())
		.def(py::init<TextEditBase &>());
}


// --- TextEditBaseEX ----------------------------------------------------------------------
void load_TextEditBaseEX(py::module m) {
	// --- TextEdit ------------------------------------------------------------------------
	py::class_<TextEdit, TextEditBase, ItemVariousProperty, ItemTextLengthLimitProperty>(m, "TextEdit")
		.def(py::init<Panel &, Rect &, short, TextEdit::FrameType, TextEdit::UpdateType, TextEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = TextEdit::FrameType::Frame,
			py::arg("update") = TextEdit::UpdateType::Update,
			py::arg("readOnly") = TextEdit::ReadOnlyType::Editable);

	// --- PasswordEdit --------------------------------------------------------------------
	py::class_<PasswordEdit, TextEditBase, ItemTextLengthLimitProperty>(m, "PasswordEdit")
		.def(py::init<Panel &, Rect &, short, PasswordEdit::FrameType, PasswordEdit::UpdateType, PasswordEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = PasswordEdit::FrameType::Frame,
			py::arg("update") = PasswordEdit::UpdateType::Update,
			py::arg("readOnly") = PasswordEdit::ReadOnlyType::Editable);

	// --- MultiLineEdit -------------------------------------------------------------------
	py::class_<MultiLineEdit, TextEditBase> m_multiLineEdit(m, "MultiLineEdit");

	py::enum_<MultiLineEdit::ScrollType>(m_multiLineEdit, "ScrollType")
		.value("NoScroll", MultiLineEdit::ScrollType::NoScroll)
		.value("HScroll", MultiLineEdit::ScrollType::HScroll)
		.value("VScroll", MultiLineEdit::ScrollType::VScroll)
		.value("HVScroll", MultiLineEdit::ScrollType::HVScroll)
		.export_values();

	m_multiLineEdit
		.def(py::init<Panel &, Rect &, MultiLineEdit::ScrollType, MultiLineEdit::FrameType, MultiLineEdit::UpdateType, MultiLineEdit::ReadOnlyType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("scroll") = MultiLineEdit::ScrollType::NoScroll,
			py::arg("frame") = MultiLineEdit::FrameType::Frame,
			py::arg("update") = MultiLineEdit::UpdateType::Update,
			py::arg("readOnly") = EditControl::ReadOnlyType::Editable)
		.def("GetText", &MultiLineEdit::GetText,
			py::arg("eolType") = EOL::Default);
}


// --- ShortcutEdit ------------------------------------------------------------------------

void load_ShortcutEdit(py::module m) {
	// --- ShortcutEdit --------------------------------------------------------------------
	py::class_<ShortcutEdit, TextEditBase, ItemTextLengthLimitProperty>(m, "ShortcutEdit")
		.def(py::init<Panel &, Rect &, short, ShortcutEdit::FrameType, ShortcutEdit::UpdateType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("lengthLimit") = 0,
			py::arg("frame") = ShortcutEdit::FrameType::Frame,
			py::arg("update") = ShortcutEdit::UpdateType::Update);

	// --- ShortcutHitEvent ----------------------------------------------------------------
	py::class_<ShortcutHitEvent, ItemChangeEvent>(m, "ShortcutHitEvent")
		.def("GetKey", &ShortcutHitEvent::GetKey)
		.def("GetModifierFlags", &ShortcutHitEvent::GetModifierFlags)
		.def("GetSource",&ShortcutHitEvent::GetSource, py::return_value_policy::reference);

	// --- ShortcutEditObserver ------------------------------------------------------------
	py::class_<PyShortcutEditObserver>(m, "ShortcutEditObserver", py::dynamic_attr())
		.def(py::init<ShortcutEdit &>());
}
