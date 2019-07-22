#pragma once

#include "../stdafx.h"

#include "DGItem.hpp"
#include "DGBarControl.hpp"

using namespace DG;


// --- PyBarControlObserver ----------------------------------------------------

class PyBarControlObserver : BarControlObserver {
public:
	PyBarControlObserver(BarControl &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyBarControlObserver() {
		this->m_parent.Detach(*this);
	}

	//short SpecChanged(const ItemChangeEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecChanged", ev);
	//}

	//short SpecTrackEntered(const ItemTrackEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecTrackEntered", ev);
	//}

	//short SpecTracked(const ItemTrackEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecTracked", ev);
	//}

	//short SpecTrackExited(const ItemTrackEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecTrackExited", ev);
	//}
	
	void BarControlChanged(const BarControlChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("BarControlChanged", ev);
	}

	void BarControlTrackEntered(const BarControlTrackEvent& ev) override {
		OBSERVER_CALL_EVENT("BarControlTrackEntered", ev);
	}

	void BarControlTracked(const BarControlTrackEvent& ev) override {
		OBSERVER_CALL_EVENT("BarControlTracked", ev);
	}

	void BarControlTrackExited(const BarControlTrackEvent& ev) override {
		OBSERVER_CALL_EVENT("BarControlTrackExited", ev);
	}

private:
	BarControl		&m_parent;
	PyThreadState	*m_state;
};


// --- PyScrollBarObserver -----------------------------------------------------

class PyScrollBarObserver : ScrollBarObserver {
public:
	PyScrollBarObserver(ScrollBar &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyScrollBarObserver() {
		this->m_parent.Detach(*this);
	}

	//short SpecChanged(const ItemChangeEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecChanged", ev);
	//}

	//short SpecTrackEntered(const ItemTrackEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecTrackEntered", ev);
	//}

	//short SpecTracked(const ItemTrackEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecTracked", ev);
	//}

	//short SpecTrackExited(const ItemTrackEvent& ev) override {
	//	OBSERVER_CALL_EVENT("SpecTrackExited", ev);
	//}

	void ScrollBarChanged(const ScrollBarChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("ScrollBarChanged", ev);
	}

	void ScrollBarTrackEntered(const ScrollBarTrackEvent& ev) override {
		OBSERVER_CALL_EVENT("ScrollBarTrackEntered", ev);
	}

	void ScrollBarTracked(const ScrollBarTrackEvent& ev) override {
		OBSERVER_CALL_EVENT("ScrollBarTracked", ev);
	}

	void ScrollBarTrackExited(const ScrollBarTrackEvent& ev) override {
		OBSERVER_CALL_EVENT("ScrollBarTrackExited", ev);
	}

private:
	ScrollBar		&m_parent;
	PyThreadState	*m_state;
};


// --- BarControl --------------------------------------------------------------

void load_dg_BarControl(py::module m) {
	// --- BarControlChangeEvent -----------------------------------------------
	py::class_<BarControlChangeEvent, ItemChangeEvent>(m, "BarControlChangeEvent")
		.def("GetSource", &BarControlChangeEvent::GetSource, py::return_value_policy::reference)
		.def("GetPreviousValue", &BarControlChangeEvent::GetPreviousValue);

	// --- BarControlTrackEvent ------------------------------------------------
	py::class_<BarControlTrackEvent, ItemTrackEvent>(m, "BarControlTrackEvent")
		.def("GetSource", &BarControlTrackEvent::GetSource, py::return_value_policy::reference);

	// --- BarControlObserver --------------------------------------------------
	py::class_<PyBarControlObserver>(m, "BarControlObserver", py::dynamic_attr())
		.def(py::init<BarControl &, ACExport &>());

	// --- BarControl ----------------------------------------------------------
	py::class_<BarControl, Item>(m, "BarControl")		
		.def("SetMin", &BarControl::SetMin)
		.def("SetMax", &BarControl::SetMax)
		.def("SetValue", &BarControl::SetValue)
		.def("GetMin", &BarControl::GetMin)
		.def("GetMax", &BarControl::GetMax)
		.def("GetValue", &BarControl::GetValue);
}

// --- BarControlEX ------------------------------------------------------------

void load_dg_BarControlEX(py::module m) {
	// --- SingleSpin ----------------------------------------------------------
	py::class_<SingleSpin, BarControl>(m, "SingleSpin")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &>());

	// --- EditSpin ------------------------------------------------------------
	py::class_<EditSpin, BarControl>(m, "EditSpin")
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, PosIntEdit &>())
		.def(py::init<Panel &, Rect &, IntEdit &>());

	// --- Slider --------------------------------------------------------------
	py::class_<Slider, BarControl> m_Slider(m, "Slider");

	py::enum_<Slider::SliderType>(m_Slider, "SliderType")
		.value("BottomRight", Slider::SliderType::BottomRight)
		.value("TopLeft", Slider::SliderType::TopLeft)
		.export_values();

	m_Slider
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, short, Slider::SliderType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("ticks"),
			py::arg("type") = Slider::SliderType::BottomRight);
}


// --- ScrollBar ---------------------------------------------------------------

void load_dg_ScrollBar(py::module m) {
	// --- ScrollBarChangeEvent ------------------------------------------------
	py::class_<ScrollBarChangeEvent, ItemChangeEvent>(m, "ScrollBarChangeEvent")
		.def("GetSource", &ScrollBarChangeEvent::GetSource, py::return_value_policy::reference)
		.def("GetPreviousValue", &ScrollBarChangeEvent::GetPreviousValue);

	// --- ScrollBarTrackEvent ------------------------------------------------
	py::class_<ScrollBarTrackEvent, ItemTrackEvent>(m, "ScrollBarTrackEvent")
		.def("GetSource", &ScrollBarTrackEvent::GetSource, py::return_value_policy::reference)
		.def("IsLineUp", &ScrollBarTrackEvent::IsLineUp)
		.def("IsLineLeft", &ScrollBarTrackEvent::IsLineLeft)
		.def("IsLineDown", &ScrollBarTrackEvent::IsLineDown)
		.def("IsLineRight", &ScrollBarTrackEvent::IsLineRight)
		.def("IsPageUp", &ScrollBarTrackEvent::IsPageUp)
		.def("IsPageLeft", &ScrollBarTrackEvent::IsPageLeft)
		.def("IsPageDown", &ScrollBarTrackEvent::IsPageDown)
		.def("IsPageRight", &ScrollBarTrackEvent::IsPageRight)
		.def("IsTop", &ScrollBarTrackEvent::IsTop)
		.def("IsLeft", &ScrollBarTrackEvent::IsLeft)
		.def("IsBottom", &ScrollBarTrackEvent::IsBottom)
		.def("IsRight", &ScrollBarTrackEvent::IsRight)
		.def("IsThumbTrack", &ScrollBarTrackEvent::IsThumbTrack);

	// --- ScrollBarObserver ------------------------------------------------
	py::class_<PyScrollBarObserver>(m, "ScrollBarObserver", py::dynamic_attr())
		.def(py::init<ScrollBar &, ACExport &>());

	// --- ScrollBar --------------------------------------------------------
	py::class_<ScrollBar, Item> m_scrollBar(m, "ScrollBar");

	py::enum_<ScrollBar::ThumbType>(m_scrollBar, "ThumbType")
		.value("Normal", ScrollBar::ThumbType::Normal)
		.value("Proportional", ScrollBar::ThumbType::Proportional)
		.export_values();

	py::enum_<ScrollBar::FocusableType>(m_scrollBar, "FocusableType")
		.value("Focusable", ScrollBar::FocusableType::Focusable)
		.value("NonFocusable", ScrollBar::FocusableType::NonFocusable)
		.export_values();

	py::enum_<ScrollBar::AutoScrollType>(m_scrollBar, "AutoScrollType")
		.value("AutoScroll", ScrollBar::AutoScrollType::AutoScroll)
		.value("NoAutoScroll", ScrollBar::AutoScrollType::NoAutoScroll)
		.export_values();

	m_scrollBar
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, ScrollBar::ThumbType, ScrollBar::FocusableType, ScrollBar::AutoScrollType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("thumb") = ScrollBar::ThumbType::Normal,
			py::arg("focus") = ScrollBar::FocusableType::Focusable,
			py::arg("autoScroll") = ScrollBar::AutoScrollType::AutoScroll)
		.def("SetMin", &ScrollBar::SetMin)
		.def("SetMax", &ScrollBar::SetMax)
		.def("SetValue", &ScrollBar::SetValue)
		.def("GetMin", &ScrollBar::GetMin)
		.def("GetMax", &ScrollBar::GetMax)
		.def("GetValue", &ScrollBar::GetValue)
		.def("SetPageSize", &ScrollBar::SetPageSize)
		.def("GetPageSize", &ScrollBar::GetPageSize);
}


// --- ProgressBar -------------------------------------------------------------

void load_dg_ProgressBar(py::module m) {
	py::class_<ProgressBar, Item> m_progressBar(m, "ProgressBar");

	py::enum_<ProgressBar::FrameType>(m_progressBar, "FrameType")
		.value("NoFrame", ProgressBar::FrameType::NoFrame)
		.value("StaticFrame", ProgressBar::FrameType::StaticFrame)
		.value("ClientFrame", ProgressBar::FrameType::ClientFrame)
		.value("ModalFrame", ProgressBar::FrameType::ModalFrame)
		.export_values();

	m_progressBar
		//.def(py::init<Panel &, short>())
		.def(py::init<Panel &, Rect &, ProgressBar::FrameType>(),
			py::arg("panel"),
			py::arg("rect"),
			py::arg("autoScroll") = ProgressBar::FrameType::NoFrame)
		.def("SetMin", &ProgressBar::SetMin)
		.def("SetMax", &ProgressBar::SetMax)
		.def("SetValue", &ProgressBar::SetValue)
		.def("GetMin", &ProgressBar::GetMin)
		.def("GetMax", &ProgressBar::GetMax)
		.def("GetValue", &ProgressBar::GetValue);
}