#pragma once

#include "../stdafx.h"

#include "DGUtility.hpp"
#include "DGPanel.hpp"
#include "DGItem.hpp"
#include "DGItemProperty.hpp"
#include "DGButton.hpp"

//#include "ACCast.h"

using namespace DG;

void load_dg_ButtonItem(py::module m) {
	py::class_<ButtonItem, Item>(m, "ButtonItem");
}

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
		.def(py::init<Panel &, short>())
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
		.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, SplitButtonBase::ButtonForm>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = SplitButtonBase::ButtonForm::Normal)

		.def("SetButtonAlignment", &SplitButtonBase::SetButtonAlignment)
		.def("GetButtonAlignment", &SplitButtonBase::GetButtonAlignment)
		.def("SetArrowPartWidth", &SplitButtonBase::SetArrowPartWidth)
		.def("GetArrowPartWidth", &SplitButtonBase::GetArrowPartWidth);
}

void load_dg_SplitButton(py::module m) {
	//py::class_<SplitButton, SplitButtonBase>(m, "SplitButton")
	//	.def(py::init<Panel &, short>())
	//	.def(py::init<Panel &, Rect &, SplitButton::ButtonForm>(),
	//		py::arg("panel"),
	//		py::arg("rect"),
	//		py::arg("type") = SplitButton::ButtonForm::Normal)

	//	.def("AppendSeparator", &SplitButton::AppendSeparator)
	//	.def("InsertSeparator", &SplitButton::InsertSeparator)
	//	.def("DeleteItem", &SplitButton::DeleteItem)
	//	.def("DeleteAllItems", &SplitButton::DeleteAllItems)

		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
		//.def("DeleteItem", &SplitButton::DeleteItem)
}