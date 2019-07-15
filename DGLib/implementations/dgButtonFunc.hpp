#pragma once

#include "../stdafx.h"

#include "DGUtility.hpp"
#include "DGPanel.hpp"
#include "DGItem.hpp"
#include "DGItemProperty.hpp"
#include "DGButton.hpp"

using namespace DG;


// --- ButtonClickEvent

//void load_dg_ButtonClickEvent(py::module m) {
//	py::class_<ButtonClickEvent, ItemClickEvent>(m, "ButtonClickEvent")
//		.def("GetSource", &ButtonClickEvent::GetSource, py::return_value_policy::reference);
//}


// --- ButtonItemObserver

//void load_dg_ButtonItemObserver(py::module m) {
//	py::class_<ButtonItemObserver, ItemObserver>(m, "ButtonItemObserver")
//		.def(py::init<>());
//}


// --- ButtonItem

void load_dg_ButtonItem(py::module m) {
	py::class_<ButtonItem, Item>(m, "ButtonItem");
		//.def("Attach", &SplitButton::Attach)
		//.def("Detach", &SplitButton::Detach)
}


// --- Button

void load_dg_Button(py::module m) {
	py::class_<Button, ButtonItem, ItemFontProperty, ItemTextProperty/*, ItemIconProperty*/> m_button(m, "Button");

	py::enum_<Button::ButtonType>(m_button, "ButtonType")
		.value("Normal", Button::ButtonType::Normal)
		.value("BevelEdge", Button::ButtonType::BevelEdge)
		.value("RoundedBevelEdge", Button::ButtonType::RoundedBevelEdge)
		.export_values();

	py::enum_<Button::FrameType>(m_button, "FrameType")
		.value("NoFrame", Button::FrameType::NoFrame)
		.value("Frame", Button::FrameType::Frame)
		.export_values();

	py::enum_<Button::Alignment>(m_button, "Alignment")
		.value("LeftAligned", Button::Alignment::LeftAligned)
		.value("CenterAligned", Button::Alignment::CenterAligned)
		.value("RightAligned", Button::Alignment::RightAligned)
		.export_values();


	m_button
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, Button::ButtonType, Button::FrameType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = Button::ButtonType::Normal,
			py::arg("frameType") = Button::FrameType::Frame)

		.def("SetAsDefault", &Button::SetAsDefault)
		.def("SetAsCancel", &Button::SetAsCancel)

		.def("SetAlignment", &Button::SetAlignment)
		.def("GetAlignment", &Button::GetAlignment);
}


// --- IconButton

void load_dg_IconButton(py::module m) {
	py::class_<IconButton, ButtonItem/*, ItemIconProperty*/> m_IconButton(m, "IconButton");

	py::enum_<IconButton::ButtonForm>(m_IconButton, "ButtonForm")
		.value("BevelEdge", IconButton::ButtonForm::BevelEdge)
		.value("RoundedBevelEdge", IconButton::ButtonForm::RoundedBevelEdge)
		.export_values();

	py::enum_<IconButton::FrameType>(m_IconButton, "FrameType")
		.value("NoFrame", IconButton::FrameType::NoFrame)
		.value("Frame", IconButton::FrameType::Frame)
		.export_values();


	m_IconButton
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, IconButton::ButtonForm, IconButton::FrameType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("form") = IconButton::ButtonForm::BevelEdge,
			py::arg("frameType") = IconButton::FrameType::Frame);
}


// --- SplitButtonBase

void load_dg_SplitButtonBase(py::module m) {
	py::class_<SplitButtonBase, ButtonItem, ItemFontProperty, ItemTextProperty/*, ItemIconProperty*/> m_splitButtonBase(m, "SplitButtonBase");

	py::enum_<SplitButtonBase::ButtonForm>(m_splitButtonBase, "ButtonForm")
		.value("Normal", SplitButtonBase::ButtonForm::Normal)
		.value("BevelEdge", SplitButtonBase::ButtonForm::BevelEdge)
		.value("RoundedBevelEdge", SplitButtonBase::ButtonForm::RoundedBevelEdge)
		.export_values();

	py::enum_<SplitButtonBase::Alignment>(m_splitButtonBase, "Alignment")
		.value("LeftAligned", SplitButtonBase::Alignment::LeftAligned)
		.value("CenterAligned", SplitButtonBase::Alignment::CenterAligned)
		.value("RightAligned", SplitButtonBase::Alignment::RightAligned)
		.export_values();


	m_splitButtonBase
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, SplitButtonBase::ButtonForm>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = SplitButtonBase::ButtonForm::Normal)

		.def("SetButtonAlignment", &SplitButtonBase::SetButtonAlignment)
		.def("GetButtonAlignment", &SplitButtonBase::GetButtonAlignment)

		.def("SetArrowPartWidth", &SplitButtonBase::SetArrowPartWidth)
		.def("GetArrowPartWidth", &SplitButtonBase::GetArrowPartWidth);
}


// --- SplitButtonChangeEvent

//void load_dg_SplitButtonChangeEvent(py::module m) {
//	py::class_<SplitButtonChangeEvent, ItemChangeEvent>(m, "SplitButtonChangeEvent")
//		.def("GetSource", &SplitButtonChangeEvent::GetSource, py::return_value_policy::reference);
//}


// --- SplitButtonObserver

//void load_dg_SplitButtonObserver(py::module m) {
//	py::class_<SplitButtonObserver, ButtonItemObserver>(m, "SplitButtonObserver")
//		.def(py::init<>());
//}


// --- SplitButton

void load_dg_SplitButton(py::module m) {
	py::class_<SplitButton, SplitButtonBase>(m, "SplitButton")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, SplitButton::ButtonForm>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = SplitButton::ButtonForm::Normal)

		//.def("Attach", &SplitButton::Attach)
		//.def("Detach", &SplitButton::Detach)

		//.def("AppendItem", &SplitButton::AppendItem)
		.def("AppendSeparator", &SplitButton::AppendSeparator)
		//.def("InsertItem", &SplitButton::InsertItem)
		.def("InsertSeparator", &SplitButton::InsertSeparator)
		.def("DeleteItem", &SplitButton::DeleteItem)
		.def("DeleteAllItems", &SplitButton::DeleteAllItems)

		.def("GetItemCount", &SplitButton::GetItemCount)
		.def("GetSelectedItem", &SplitButton::GetSelectedItem)

		//.def("SetItemIcon", &SplitButton::SetItemIcon)
		//.def("GetItemIcon", &SplitButton::GetItemIcon)

		.def("SetItemText", &SplitButton::SetItemText)
		.def("GetItemText", &SplitButton::GetItemText)

		.def("SetItemTextSize", &SplitButton::SetItemTextSize)
		.def("GetItemTextSize", &SplitButton::GetItemTextSize)

		.def("SetItemTextStyle", &SplitButton::SetItemTextStyle)
		.def("GetItemTextStyle", &SplitButton::GetItemTextStyle)

		//.def("SetItemData", &SplitButton::SetItemData)
		//.def("GetItemData", &SplitButton::GetItemData)

		//.def("SetItemObjectData", &SplitButton::SetItemObjectData)
		//.def("GetItemObjectData", &SplitButton::GetItemObjectData)

		.def("EnableItem", &SplitButton::EnableItem)
		.def("DisableItem", &SplitButton::DisableItem)
		.def("SetItemStatus", &SplitButton::SetItemStatus)
		.def("IsItemEnabled", &SplitButton::IsItemEnabled)

		.def("IsSeparatorItem", &SplitButton::IsSeparatorItem)

		.def("EnableDraw", &SplitButton::EnableDraw)
		.def("DisableDraw", &SplitButton::DisableDraw);
}


// --- CustomSplitButtonOpenRequestedEvent

//void load_dg_CustomSplitButtonOpenRequestedEvent(py::module m) {
//	py::class_<CustomSplitButtonOpenRequestedEvent, ItemEvent>(m, "CustomSplitButtonOpenRequestedEvent")
//		.def("GetSource", &CustomSplitButtonOpenRequestedEvent::GetSource, py::return_value_policy::reference);
//}


// --- CustomSplitButtonObserver

//void load_dg_CustomSplitButtonObserver(py::module m) {
//	py::class_<CustomSplitButtonObserver, ButtonItemObserver>(m, "CustomSplitButtonObserver")
//		.def(py::init<>());
//}


// --- CustomSplitButton

void load_dg_CustomSplitButton(py::module m) {
	py::class_<CustomSplitButton, SplitButtonBase>(m, "CustomSplitButton")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, SplitButton::ButtonForm>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = SplitButton::ButtonForm::Normal)

		//.def("Attach", &SplitButton::Attach)
		//.def("Detach", &SplitButton::Detach)

		.def("EnableArrowPart", &CustomSplitButton::EnableArrowPart)
		.def("DisableArrowPart", &CustomSplitButton::DisableArrowPart)
		.def("SetArrowPartStatus", &CustomSplitButton::SetArrowPartStatus)
		.def("IsArrowPartEnabled", &CustomSplitButton::IsArrowPartEnabled);
}