#pragma once

#include "../stdafx.h"

#include "DGTabPage.hpp"
#include "DGTabControl.hpp"

using namespace DG;


// --- TabPage ------------------------------------------------------------------------------

py::class_<TabPage> init_TabPage(py::module m) {
	py::class_<TabPage, Panel> m_tabPage(m, "TabPage");

	return m_tabPage;
}

void load_TabPage(py::class_<TabPage> m_tabPage) {

	py::enum_<TabPage::GrowType>(m_tabPage, "GrowType")
		.value("NoGrow",TabPage::GrowType::NoGrow)
		.value("HGrow", TabPage::GrowType::HGrow)
		.value("VGrow", TabPage::GrowType::VGrow)
		.value("HVGrow", TabPage::GrowType::HVGrow)
		.export_values();

	py::enum_<TabPage::FixPoint>(m_tabPage, "FixPoint")
		.value("CenterPoint", TabPage::FixPoint::CenterPoint)
		.value("TopLeft", TabPage::FixPoint::TopLeft)
		.value("CenterLeft", TabPage::FixPoint::CenterLeft)
		.value("BottomLeft", TabPage::FixPoint::BottomLeft)
		.value("BottomCenter", TabPage::FixPoint::BottomCenter)
		.value("BottomRight", TabPage::FixPoint::BottomRight)
		.value("CenterRight", TabPage::FixPoint::CenterRight)
		.value("TopRight", TabPage::FixPoint::TopRight)
		.value("TopCenter", TabPage::FixPoint::TopCenter)
		.export_values();

	m_tabPage
		.def(py::init<TabControl &, short, short, short>(), py::arg("tabControl"), py::arg("tabItem"), py::arg("width"), py::arg("height"))

		.def("GetParentDialog", &TabPage::GetParentDialog, py::return_value_policy::reference)
		.def("GetParentControl", &TabPage::GetParentControl, py::return_value_policy::reference)

		.def("SetGrowType", &TabPage::SetGrowType)
		.def("GetGrowType", &TabPage::GetGrowType)

		.def("SetFixPoint", &TabPage::SetFixPoint)
		.def("GetFixPoint", &TabPage::GetFixPoint)

		.def("SetSize", &TabPage::SetSize)
		.def("SetWidth", &TabPage::SetWidth)
		.def("SetHeight", &TabPage::SetHeight)

		.def("GetRect", &TabPage::GetRect)
		.def("GetWidth", &TabPage::GetWidth)
		.def("GetHeight", &TabPage::GetHeight)

		.def("SetMinSize", &TabPage::SetMinSize)
		.def("SetMinWidth", &TabPage::SetMinWidth)
		.def("SetMinHeight", &TabPage::SetMinHeight)

		.def("GetMinWidth", &TabPage::GetMinWidth)
		.def("GetMinHeight", &TabPage::GetMinHeight)

		.def("IsTabPage", &TabPage::IsTabPage);
}
