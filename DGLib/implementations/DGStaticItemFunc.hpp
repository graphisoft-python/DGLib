#pragma once

#include "../stdafx.h"

#include "DGItemProperty.hpp"
#include "DGStaticItem.hpp"

using namespace DG;


// --- PyStaticTextObserver --------------------------------------------------------------------

class PyStaticTextObserver : StaticTextObserver {
public:
	PyStaticTextObserver(StaticText &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyStaticTextObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS

	void StaticTextClicked(const StaticTextClickEvent& ev) override {
		OBSERVER_CALL_EVENT("StaticTextClicked", ev);
	}

	void StaticTextDoubleClicked(const StaticTextDoubleClickEvent& ev) override {
		OBSERVER_CALL_EVENT("StaticTextDoubleClicked", ev);
	}

	void StaticTextMouseMoved(const StaticTextMouseMoveEvent& ev, bool* noDefaultCursor) override {
		OBSERVER_CALL_EVENT_WITH_RETURN("StaticTextMouseMoved", ev, noDefaultCursor, bool);
	}

private:
	StaticText		&m_parent;
	PyThreadState	*m_state;
};


// --- StaticItemEventProperty -----------------------------------------------------------------

void load_StaticItemEventProperty(py::module m) {
	py::class_<StaticItemEventProperty>(m, "StaticItemEventProperty")
		.def("GetMouseOffset", &StaticItemEventProperty::GetMouseOffset)
		.def("IsCommandPressed", &StaticItemEventProperty::IsCommandPressed)
		.def("IsOptionPressed", &StaticItemEventProperty::IsOptionPressed)
		.def("IsShiftPressed", &StaticItemEventProperty::IsShiftPressed)
		.def("IsLeftButtonPressed", &StaticItemEventProperty::IsLeftButtonPressed)
		.def("IsRightButtonPressed", &StaticItemEventProperty::IsRightButtonPressed)
		.def("IsWheelButtonPressed", &StaticItemEventProperty::IsWheelButtonPressed);
}


// --- StaticText ------------------------------------------------------------------------------

void load_StaticText(py::module m) {
	// --- StaticTextClickEvent
	py::class_<StaticTextClickEvent, ItemClickEvent>(m, "StaticTextClickEvent")
		.def("GetSource", &StaticTextClickEvent::GetSource, py::return_value_policy::reference);

	// --- StaticTextDoubleClickEvent
	py::class_<StaticTextDoubleClickEvent, ItemDoubleClickEvent>(m, "StaticTextDoubleClickEvent")
		.def("GetSource", &StaticTextDoubleClickEvent::GetSource, py::return_value_policy::reference);
	
	// --- StaticTextMouseMoveEvent
		py::class_<StaticTextMouseMoveEvent, ItemMouseMoveEvent, StaticItemEventProperty>(m, "StaticTextMouseMoveEvent")
			.def("GetSource", &StaticTextMouseMoveEvent::GetSource, py::return_value_policy::reference);

	// --- BarControlObserver ------------------------------------------------------------------
	py::class_<PyStaticTextObserver>(m, "StaticTextObserver", py::dynamic_attr())
		.def(py::init<StaticText &, ACExport &>());

	// --- StaticText --------------------------------------------------------------------------
	py::class_<StaticText, Item, ItemFontProperty, ItemTextProperty, ItemColorProperty> m_staticText(m, "StaticText");
		
	py::enum_<StaticText::VAlignType>(m_staticText, "VAlignType")
		.value("VTop", StaticText::VAlignType::VTop)
		.value("VCenter", StaticText::VAlignType::VCenter)
		.value("VBottom", StaticText::VAlignType::VBottom)
		.export_values();

	py::enum_<StaticText::Truncation>(m_staticText, "Truncation")
		.value("NoTruncate", StaticText::Truncation::NoTruncate)
		.value("EndTruncate", StaticText::Truncation::EndTruncate)
		.value("MiddleTruncate", StaticText::Truncation::MiddleTruncate)
		.export_values();

	py::enum_<StaticText::FrameType>(m_staticText, "FrameType")
		.value("NoFrame", StaticText::FrameType::NoFrame)
		.value("StaticFrame", StaticText::FrameType::StaticFrame)
		.value("ClientFrame", StaticText::FrameType::ClientFrame)
		.value("ModalFrame", StaticText::FrameType::ModalFrame)
		.export_values();

	m_staticText
		.def("EnableMouseMoveEvent", &StaticText::EnableMouseMoveEvent);
}


// --- StaticTextEX ----------------------------------------------------------------------------

void load_StaticTextEX(py::module m) {
	// --- CenterText --------------------------------------------------------------------------
	py::class_<CenterText, StaticText>(m, "CenterText")
		.def(py::init<Panel &, Rect &, CenterText::FrameType, CenterText::VAlignType, CenterText::Truncation>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = CenterText::FrameType::NoFrame,
			py::arg("align") = CenterText::VAlignType::VTop,
			py::arg("truncate") = CenterText::Truncation::NoTruncate);

	// --- LeftText ----------------------------------------------------------------------------
	py::class_<LeftText, StaticText>(m, "LeftText")
		.def(py::init<Panel &, Rect &, LeftText::FrameType, LeftText::VAlignType, LeftText::Truncation>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = LeftText::FrameType::NoFrame,
			py::arg("align") = LeftText::VAlignType::VTop,
			py::arg("truncate") = LeftText::Truncation::NoTruncate);

	// --- RightText ---------------------------------------------------------------------------
	py::class_<RightText, StaticText>(m, "RightText")
		.def(py::init<Panel &, Rect &, RightText::FrameType, RightText::VAlignType, RightText::Truncation>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = RightText::FrameType::NoFrame,
			py::arg("align") = RightText::VAlignType::VTop,
			py::arg("truncate") = RightText::Truncation::NoTruncate);
}


// --- GroupBox --------------------------------------------------------------------------------

void load_GroupBox(py::module m) {
	py::class_<GroupBox, Item, ItemFontProperty, ItemTextProperty> m_groupBox(m, "GroupBox");

	py::enum_<GroupBox::GroupBoxType>(m_groupBox, "GroupBoxType")
		.value("Primary", GroupBox::GroupBoxType::Primary)
		.value("Secondary", GroupBox::GroupBoxType::Secondary)
		.export_values();

	m_groupBox
		.def(py::init<Panel &, Rect &, GroupBox::GroupBoxType>());
}


// --- Separator -------------------------------------------------------------------------------

void load_Separator(py::module m) {
	py::class_<Separator, Item> (m, "Separator")
		.def(py::init<Panel &, Rect &>());
}



