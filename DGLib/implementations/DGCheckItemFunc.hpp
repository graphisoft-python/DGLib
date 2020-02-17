#pragma once

#include "../stdafx.h"

#include "DGCheckItem.hpp"

using namespace DG;


// --- PyCheckItemObserver --------------------------------------------------------------------

class PyCheckItemObserver : CheckItemObserver {
public:
	PyCheckItemObserver(CheckItem &item)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = GetCurrentAppState();
	}

	~PyCheckItemObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS

	void CheckItemChanged(const CheckItemChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("CheckItemChanged", ev);
	}

	void CheckItemDoubleClicked(const CheckItemDoubleClickEvent& ev) override {
		OBSERVER_CALL_EVENT("CheckItemDoubleClicked", ev);
	}

private:
	CheckItem		&m_parent;
	PyThreadState	*m_state;
};


// --- CheckItem ------------------------------------------------------------------------------

void load_CheckItem(py::module m) {
	// --- CheckItem --------------------------------------------------------------------------
	py::class_<CheckItem, Item>(m, "CheckItem")
		.def("Check", &CheckItem::Check)
		.def("Uncheck", &CheckItem::Uncheck)
		.def("SetState", &CheckItem::SetState)
		.def("IsChecked", &CheckItem::IsChecked);

	// --- CheckItemChangeEvent ---------------------------------------------------------------
	py::class_<CheckItemChangeEvent, ItemChangeEvent>(m, "CheckItemChangeEvent")
		.def("GetSource", &CheckItemChangeEvent::GetSource,py::return_value_policy::reference);

	// --- CheckItemDoubleClickEvent ----------------------------------------------------------
	py::class_<CheckItemDoubleClickEvent, ItemDoubleClickEvent>(m, "CheckItemDoubleClickEvent")
		.def("GetSource", &CheckItemDoubleClickEvent::GetSource, py::return_value_policy::reference);

	// --- CheckItemObserver ------------------------------------------------------------------
	py::class_<PyCheckItemObserver>(m, "CheckItemObserver", py::dynamic_attr())
		.def(py::init<CheckItem &>());
}


// --- CheckItemEX ----------------------------------------------------------------------------

void load_CheckItemEX(py::module m) {
	// --- CheckBox ---------------------------------------------------------------------------
	py::class_<CheckBox, CheckItem, ItemFontProperty, ItemTextProperty>(m, "CheckBox")
		.def(py::init<Panel &, Rect &>());

	// --- IconCheckBox -----------------------------------------------------------------------
	py::class_<IconCheckBox, CheckItem, ItemIconProperty>(m, "IconCheckBox")
		.def(py::init<Panel &, Rect &>());

	// --- PushCheck --------------------------------------------------------------------------
	py::class_<PushCheck, CheckItem, ItemFontProperty, ItemTextProperty, ItemIconProperty>m_pushCheck(m, "PushCheck");

	py::enum_<PushCheck::ButtonForm>(m_pushCheck, "ButtonForm")
		.value("BevelEdge", PushCheck::ButtonForm::BevelEdge)
		.value("RoundedBevelEdge", PushCheck::ButtonForm::RoundedBevelEdge)
		.export_values();

	py::enum_<PushCheck::FrameType>(m_pushCheck, "FrameType")
		.value("NoFrame", PushCheck::FrameType::NoFrame)
		.value("Frame", PushCheck::FrameType::Frame)
		.export_values();

	py::enum_<PushCheck::Alignment>(m_pushCheck, "Alignment")
		.value("LeftAligned", PushCheck::Alignment::LeftAligned)
		.value("CenterAligned", PushCheck::Alignment::CenterAligned)
		.value("RightAligned", PushCheck::Alignment::RightAligned)
		.export_values();

	py::enum_<PushCheck::ArrowType>(m_pushCheck, "ArrowType")
		.value("None", PushCheck::ArrowType::None)
		.value("Right", PushCheck::ArrowType::Right)
		.value("Down", PushCheck::ArrowType::Down)
		.export_values();

	m_pushCheck
		.def(py::init<Panel &, Rect &, PushCheck::ButtonForm, PushCheck::FrameType>(),
			py::arg("panel"),
			py::arg("rect"), 
			py::arg("form") = PushCheck::ButtonForm::BevelEdge,
			py::arg("frameType") = PushCheck::FrameType::Frame)
		.def("SetAlignment", &PushCheck::SetAlignment)
		.def("GetAlignment", &PushCheck::GetAlignment)
		.def("SetArrowType", &PushCheck::SetArrowType)
		.def("GetArrowType", &PushCheck::GetArrowType);

	// --- IconPushCheck ----------------------------------------------------------------------
	py::class_<IconPushCheck, CheckItem, ItemIconProperty>m_iconPushCheck(m, "IconPushCheck");

	py::enum_<IconPushCheck::ButtonForm>(m_iconPushCheck, "ButtonForm")
		.value("BevelEdge", IconPushCheck::ButtonForm::BevelEdge)
		.value("RoundedBevelEdge", IconPushCheck::ButtonForm::RoundedBevelEdge)
		.export_values();

	py::enum_<IconPushCheck::FrameType>(m_iconPushCheck, "FrameType")
		.value("NoFrame", IconPushCheck::FrameType::NoFrame)
		.value("Frame", IconPushCheck::FrameType::Frame)
		.export_values();

	m_iconPushCheck
		.def(py::init<Panel &, Rect &, IconPushCheck::ButtonForm, IconPushCheck::FrameType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("form") = IconPushCheck::ButtonForm::BevelEdge,
			py::arg("frameType") = IconPushCheck::FrameType::Frame);
}