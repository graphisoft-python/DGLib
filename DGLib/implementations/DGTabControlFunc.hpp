#pragma once

#include "../stdafx.h"

#include "DGTabControl.hpp"
#include "DGItemProperty.hpp"

using namespace DG;

// --- PyNormalTabObserver --------------------------------------------------------------------

class PyNormalTabObserver : NormalTabObserver {

public:
	PyNormalTabObserver(NormalTab &item)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = GetCurrentAppState();
	}

	~PyNormalTabObserver() {
		this->m_parent.Detach(*this);
	}

	ITEMOBSERVER_METHODS

	void NormalTabChanged(const NormalTabChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("NormalTabChanged", ev);
	}

	void NormalTabClicked(const NormalTabClickEvent& ev, bool* denyChange) override {
		OBSERVER_CALL_EVENT("NormalTabClicked", ev, denyChange);
	}

private:
	NormalTab		&m_parent;
	PyThreadState	*m_state;
};

// --- TabControl ------------------------------------------------------------------------------

void load_TabControl(py::module m) {
	py::class_<TabControl, Item> m_tabControl(m, "TabControl");

	py::enum_<TabControl::ItemType>(m_tabControl, "ItemType")
		.value("AllItems",TabControl::ItemType::AllItems)
		.value("FirstItem", TabControl::ItemType::FirstItem)
		.value("LastItem", TabControl::ItemType::LastItem)
		.export_values();

	m_tabControl
		.def("AppendItem", &TabControl::AppendItem)
		.def("InsertItem", &TabControl::InsertItem)
		.def("DeleteItem", &TabControl::DeleteItem)
		.def("GetItemCount", &TabControl::GetItemCount)

		.def("EnableItem", &TabControl::EnableItem)
		.def("DisableItem", &TabControl::DisableItem)
		.def("SetItemStatus", &TabControl::SetItemStatus)
		.def("IsItemEnabled", &TabControl::IsItemEnabled)

		.def("SelectItem", &TabControl::SelectItem)
		.def("GetSelectedItem", &TabControl::GetSelectedItem)

		.def("SetClientSize", &TabControl::SetClientSize)
		.def("SetClientWidth", &TabControl::SetClientWidth)
		.def("SetClientHeight", &TabControl::SetClientHeight)

		.def("GetClientRect", &TabControl::GetClientRect)
		.def("GetClientWidth", &TabControl::GetClientWidth)
		.def("GetClientHeight", &TabControl::GetClientHeight)

		.def("ClientRectFromFrameRect", &TabControl::ClientRectFromFrameRect)
		.def("ClientWidthFromFrameWidth", &TabControl::ClientWidthFromFrameWidth)
		.def("ClientHeightFromFrameHeight", &TabControl::ClientHeightFromFrameHeight)

		.def("FrameRectFromClientRect", &TabControl::FrameRectFromClientRect)
		.def("FrameWidthFromClientWidth", &TabControl::FrameWidthFromClientWidth)
		.def("FrameHeightFromClientHeight", &TabControl::FrameHeightFromClientHeight)
		
		.def("GetTabPage", &TabControl::GetTabPage, py::return_value_policy::reference);
}

// --- NormalTab ------------------------------------------------------------------------------

void load_NormalTab(py::module m) {
	py::class_<NormalTab, TabControl, ItemFontProperty>(m, "NormalTab")
		.def(py::init<Panel &, Rect &>(), py::arg("panel"), py::arg("rect"))

		.def("SetItemText", &NormalTab::SetItemText)
		.def("GetItemText", &NormalTab::GetItemText);

	// --- NormalTabChangeEvent---------------------------------------------------------------------
	py::class_<NormalTabChangeEvent, ItemChangeEvent>(m, "NormalTabChangeEvent")
		.def("GetSource", &NormalTabChangeEvent::GetSource, py::return_value_policy::reference)
		.def("GetPreviousItem", &NormalTabChangeEvent::GetPreviousItem);

	// --- NormalTabClickEvent---------------------------------------------------------------------
	py::class_<NormalTabClickEvent, ItemClickEvent>(m, "NormalTabClickEvent")
		.def("GetSource", &NormalTabClickEvent::GetSource, py::return_value_policy::reference)
		.def("GetRequestedItem", &NormalTabClickEvent::GetRequestedItem);

	// --- PyNormalTabObserver ------------------------------------------------------------------
	py::class_<PyNormalTabObserver>(m, "NormalTabObserver", py::dynamic_attr())
		.def(py::init<NormalTab &>());
}