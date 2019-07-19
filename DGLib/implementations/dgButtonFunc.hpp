#pragma once

#include "../stdafx.h"

#include "DGUtility.hpp"
#include "DGPanel.hpp"
#include "DGItem.hpp"
#include "DGItemProperty.hpp"
#include "DGButton.hpp"

using namespace DG;
using namespace PyEnv;


// --- ButtonItemObserver -------------------------------------------------------------------

class PyButtonItemObserver : ButtonItemObserver {

public:
	PyButtonItemObserver(ButtonItem &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyButtonItemObserver() {
		this->m_parent.Detach(*this);
	}

	//short SpecClicked(const ItemClickEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecClicked", ev);
	//}

	void ButtonClicked(const ButtonClickEvent& ev) override {
		OBSERVER_CALL_EVENT("ButtonClicked", ev);
	}

private:
	ButtonItem		&m_parent;
	PyThreadState	*m_state;
};


// --- ButtonItem -------------------------------------------------------------------

void load_dg_ButtonItem(py::module m) {
	py::class_<ButtonClickEvent/*, ItemClickEvent*/>(m, "ButtonClickEvent")
		.def("GetSource", &ButtonClickEvent::GetSource, py::return_value_policy::reference);

	py::class_<PyButtonItemObserver>(m, "ButtonItemObserver", py::dynamic_attr())
		.def(py::init<ButtonItem &, ACExport &>());


	py::class_<ButtonItem, Item>(m, "ButtonItem");
}


// --- Button -------------------------------------------------------------------

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


// --- IconButton -------------------------------------------------------------------

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


// --- SplitButtonBase -------------------------------------------------------------------

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


// --- SplitButtonObserver -------------------------------------------------------------------

class PySplitButtonObserver : SplitButtonObserver {

public:
	PySplitButtonObserver(SplitButton &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PySplitButtonObserver() {
		this->m_parent.Detach(*this);
	}

	//short SpecChanged(const ItemChangeEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecChanged", ev);
	//}

	void SplitButtonPopupChanged(const SplitButtonChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("SplitButtonPopupChanged", ev);
	}

private:
	SplitButton		&m_parent;
	PyThreadState	*m_state;
};


// --- SplitButton -------------------------------------------------------------------

void load_dg_SplitButton(py::module m) {
	py::class_<SplitButtonChangeEvent/*, ItemChangeEvent*/>(m, "SplitButtonChangeEvent")
		.def("GetSource", &SplitButtonChangeEvent::GetSource, py::return_value_policy::reference);

	py::class_<PySplitButtonObserver>(m, "SplitButtonObserver", py::dynamic_attr())
		.def(py::init<SplitButton &, ACExport &>());


	py::class_<SplitButton, SplitButtonBase>(m, "SplitButton")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, SplitButtonBase::ButtonForm>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = SplitButtonBase::ButtonForm::Normal)
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


// --- CustomSplitButtonObserver -------------------------------------------------------------------

class PyCustomSplitButtonObserver : CustomSplitButtonObserver {

public:
	PyCustomSplitButtonObserver(CustomSplitButton &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyCustomSplitButtonObserver() {
		this->m_parent.Detach(*this);
	}

	void SplitButtonOpenRequested(const CustomSplitButtonOpenRequestedEvent& ev) override {
		OBSERVER_CALL_EVENT("SplitButtonOpenRequested", ev);
	}

private:
	CustomSplitButton	&m_parent;
	PyThreadState		*m_state;
};


// --- CustomSplitButton -------------------------------------------------------------------

void load_dg_CustomSplitButton(py::module m) {
	py::class_<CustomSplitButtonOpenRequestedEvent/*, ItemEvent*/>(m, "CustomSplitButtonOpenRequestedEvent")
		.def("GetSource", &CustomSplitButtonOpenRequestedEvent::GetSource, py::return_value_policy::reference);

	py::class_<PyCustomSplitButtonObserver>(m, "CustomSplitButtonObserver", py::dynamic_attr())
		.def(py::init<CustomSplitButton &, ACExport &>());


	py::class_<CustomSplitButton, SplitButtonBase>(m, "CustomSplitButton")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, SplitButtonBase::ButtonForm>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("type") = SplitButtonBase::ButtonForm::Normal)
		.def("EnableArrowPart", &CustomSplitButton::EnableArrowPart)
		.def("DisableArrowPart", &CustomSplitButton::DisableArrowPart)
		.def("SetArrowPartStatus", &CustomSplitButton::SetArrowPartStatus)
		.def("IsArrowPartEnabled", &CustomSplitButton::IsArrowPartEnabled);
}