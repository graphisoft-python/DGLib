#pragma once

#include "../stdafx.h"

#include "DGItemProperty.hpp"
#include "DGStaticItem.hpp"

using namespace DG;


// --- StaticItemEventProperty

//void load_dg_StaticItemEventProperty(py::module m) {
//	py::class_<StaticItemEventProperty>(m, "StaticItemEventProperty")
//		.def("GetMouseOffset", &StaticItemEventProperty::GetMouseOffset)
//
//		.def("IsCommandPressed", &StaticItemEventProperty::IsCommandPressed)
//		.def("IsOptionPressed", &StaticItemEventProperty::IsOptionPressed)
//		.def("IsShiftPressed", &StaticItemEventProperty::IsShiftPressed)
//
//		.def("IsLeftButtonPressed", &StaticItemEventProperty::IsLeftButtonPressed)
//		.def("IsRightButtonPressed", &StaticItemEventProperty::IsRightButtonPressed)
//		.def("IsWheelButtonPressed", &StaticItemEventProperty::IsWheelButtonPressed);
//}


// --- StaticTextClickEvent

//void load_dg_StaticTextClickEvent(py::module m) {
//	py::class_<StaticTextClickEvent, ItemClickEvent>(m, "StaticTextClickEvent")
//		.def("GetSource", &StaticTextClickEvent::GetSource, py::return_value_policy::reference);
//}


// --- StaticTextDoubleClickEvent

//void load_dg_StaticTextDoubleClickEvent(py::module m) {
//	py::class_<StaticTextDoubleClickEvent, ItemDoubleClickEvent>(m, "StaticTextDoubleClickEvent")
//		.def("GetSource", &StaticTextDoubleClickEvent::GetSource, py::return_value_policy::reference);
//}


// --- StaticTextMouseMoveEvent

//void load_dg_StaticTextMouseMoveEvent(py::module m) {
//	py::class_<StaticTextMouseMoveEvent, ItemMouseMoveEvent, StaticItemEventProperty>(m, "StaticTextMouseMoveEvent")
//		.def("GetSource", &StaticTextMouseMoveEvent::GetSource, py::return_value_policy::reference);
//}


// --- StaticTextObserver

//void load_dg_StaticTextObserver(py::module m) {
//	py::class_<StaticTextObserver, ItemObserver>(m, "StaticTextObserver")
//		.def(py::init<>());
//}


// --- StaticText

void load_dg_StaticText(py::module m) {
	py::class_<StaticText, Item, ItemFontProperty, ItemTextProperty/*, ItemColorProperty*/> m_staticText(m, "StaticText");
		
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
		//.def("Attach", &StaticText::Attach)
		//.def("Detach", &StaticText::Detach)

		.def("EnableMouseMoveEvent", &StaticText::EnableMouseMoveEvent);
}


// --- CenterText

void load_dg_CenterText(py::module m) {
	py::class_<CenterText, StaticText>(m, "CenterText")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, StaticText::FrameType, StaticText::VAlignType, StaticText::Truncation>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = StaticText::FrameType::NoFrame,
			py::arg("align") = StaticText::VAlignType::VTop,
			py::arg("truncate") = StaticText::Truncation::NoTruncate);
}


// --- LeftText

void load_dg_LeftText(py::module m) {
	py::class_<LeftText, StaticText>(m, "LeftText")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, StaticText::FrameType, StaticText::VAlignType, StaticText::Truncation>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = StaticText::FrameType::NoFrame,
			py::arg("align") = StaticText::VAlignType::VTop,
			py::arg("truncate") = StaticText::Truncation::NoTruncate);
}


// --- RightText

void load_dg_RightText(py::module m) {
	py::class_<RightText, StaticText>(m, "RightText")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, StaticText::FrameType, StaticText::VAlignType, StaticText::Truncation>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = StaticText::FrameType::NoFrame,
			py::arg("align") = StaticText::VAlignType::VTop,
			py::arg("truncate") = StaticText::Truncation::NoTruncate);
}


// --- GroupBox

void load_dg_GroupBox(py::module m) {
	py::class_<GroupBox, Item, ItemFontProperty, ItemTextProperty> m_groupBox(m, "GroupBox");

	py::enum_<GroupBox::GroupBoxType>(m_groupBox, "GroupBox")
		.value("Primary", GroupBox::GroupBoxType::Primary)
		.value("Secondary", GroupBox::GroupBoxType::Secondary)
		.export_values();


	m_groupBox
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, GroupBox::GroupBoxType>());
}


// --- Separator

void load_dg_Separator(py::module m) {
	py::class_<Separator, Item> (m, "Separator")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &>());
}



