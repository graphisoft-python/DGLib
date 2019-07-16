#pragma once

#include "../stdafx.h"

#include "DGPanel.hpp"

#include	"ACObserver.h"
#include	"Lock.hpp"

using namespace DG;

static GS::Lock	g_lock;

class PyPanelObserver :PanelObserver {
public:
	PyPanelObserver(Panel &item,UINT64 vState)
		:m_parent(item)
	{
		this->m_parent.Attach(*this);
		this->m_state = (PyThreadState *)vState;
	}

	~PyPanelObserver() {
		this->m_parent.Detach(*this);
	}

	void PanelClosed(const PanelCloseEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelClosed", ev);
	}

	void PanelCloseRequested(const PanelCloseRequestEvent& ev, bool* accepted) override {
		//OBSERVER_CALL_EVENT_WITH_RETURN("PanelCloseRequested", ev, accepted, bool);
	}

	void PanelContextHelpRequested(const PanelHelpEvent& ev, GS::UniString* contextHelpAnchor) override {
		//OBSERVER_CALL_EVENT_WITH_RETURN("PanelContextHelpRequested", ev, contextHelpAnchor, GS::UniString);
	}

	void PanelContextMenuRequested(const PanelContextMenuEvent& ev, bool* needHelp, bool* processed) override {
		//OBSERVER_CALL_EVENT_WITH_RETURN_AND_SET_PROCESSED("PanelContextMenuRequested", ev, needHelp, bool, processed);
	}

	void PanelDragEntered(const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent) override {
		// not impl
	}

	void PanelDragEntered(const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent, bool* rightDragMenu)override {
		// not impl
	}

	void PanelDragMoved(const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent) override {
		// not impl
	}

	void PanelDragLeft(const PanelDropTargetEvent& ev, bool* handleEvent) override {
		// not impl
	}

	void PanelDropped(const PanelDropTargetEvent& ev, DragDrop::Effect* effect, bool* handleEvent) override {
		// not impl
	}

	void PanelHotkeyPressed(const PanelHotKeyEvent& ev, bool* processed) override {
		//OBSERVER_CALL_EVENT_SET_PROCESSED("PanelHotkeyPressed", ev, processed);
	}

	void PanelIdle(const PanelIdleEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelIdle", ev);
	}

	void PanelOpened(const PanelOpenEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelOpened", ev);
	}

	void PanelResizeEntered(const PanelResizeEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelResizeEntered", ev);
	}

	void PanelResizing(const PanelResizeEvent& ev, Point* growValues) override {
		//py::gil_scoped_acquire acq;
		//g_lock.Acquire(true);
		PyThreadState *_ts = PyThreadState_GET();

		if (_ts != this->m_state) {
			PyThreadState_Swap(this->m_state);
		}

		//py::gil_scoped_acquire acq;
		try {
			py::object py_obsr = py::cast(this);
			if (py::hasattr(py_obsr, "PanelResizing")) {
				py::object result = py_obsr.attr("PanelResizing")(ev);
				if (!result.is_none()) {
					*growValues = result.cast<Point>();
				}
			}
		}
		catch (py::error_already_set & err) {
			err.restore();
			if (PyErr_Occurred()) {
				PyErr_Print();
			}
		}
		//
		//g_lock.Release();
		
		//OBSERVER_CALL_EVENT_WITH_RETURN("PanelResizing", ev, growValues, Point);
	}

	void PanelResized(const PanelResizeEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelResized", ev);
	}

	void PanelResizeExited(const PanelResizeEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelResizeExited", ev);
	}

	void PanelMoveEntered(const PanelMoveEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelMoveEntered", ev);
	}

	void PanelMoving(const PanelMoveEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelMoving", ev);
	}

	void PanelMoved(const PanelMoveEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelMoved", ev);
	}

	void PanelMoveExited(const PanelMoveEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelMoveExited", ev);
	}

	void PanelScaleChanged(const PanelScaleChangeEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelScaleChanged", ev);
	}

	void PanelToolTipRequested(const PanelHelpEvent& ev, GS::UniString* toolTipText) override {
		//OBSERVER_CALL_EVENT_WITH_RETURN("PanelToolTipRequested", ev, toolTipText, GS::UniString);
	}

	void PanelTopStatusGained(const PanelTopStatusEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelTopStatusGained", ev);
	}

	void PanelTopStatusLost(const PanelTopStatusEvent& ev) override {
		//g_lock.Acquire(true);
		PyThreadState *_ts = PyThreadState_GET();

		if (_ts != this->m_state) {
			PyThreadState_Swap(this->m_state);
		}

		//py::gil_scoped_acquire acq;
		try {
			py::object py_obsr = py::cast(this);
			if (py::hasattr(py_obsr, "PanelTopStatusLost")) {
				py_obsr.attr("PanelTopStatusLost")(ev);
			}
		}
		catch (py::error_already_set & err) {
			err.restore();
			if (PyErr_Occurred()) {
				PyErr_Print();
			}
		}

		//g_lock.Release();
		//OBSERVER_CALL_EVENT("PanelTopStatusLost", ev);
	}

	void PanelWheelTrackEntered(const PanelWheelEvent& ev, bool* processed) override {
		//OBSERVER_CALL_EVENT_SET_PROCESSED("PanelWheelTrackEntered", ev, processed);
	}

	void PanelWheelTracked(const PanelWheelTrackEvent& ev, bool* processed) override {
		//OBSERVER_CALL_EVENT_SET_PROCESSED("PanelWheelTracked", ev, processed);
	}

	void PanelWheelTrackExited(const PanelWheelEvent& ev, bool* processed) override {
		//OBSERVER_CALL_EVENT_SET_PROCESSED("PanelWheelTrackExited", ev, processed);
	}

	void PanelBackgroundPaint(const PanelBackgroundPaintEvent& ev, bool* processed) override {
		//OBSERVER_CALL_EVENT_SET_PROCESSED("PanelBackgroundPaint", ev, processed);
	}

	void PanelBackgroundPostPaint(const PanelBackgroundPaintEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelBackgroundPostPaint", ev);
	}

	void PanelActivated(const PanelActivateEvent& ev) override {
		//OBSERVER_CALL_EVENT("PanelActivated", ev);
	}

	void PanelChangeRegistrationRequested(const Item* item, bool* allowRegistration) override {
		//OBSERVER_CALL_EVENT_WITH_RETURN("PanelChangeRegistrationRequested", item, allowRegistration, bool);
	}

private:
	Panel			&m_parent;
	PyThreadState	*m_state;

private:
	
};

void load_dg_Panel(py::module m) {

	py::class_<PanelEvent>(m, "PanelEvent")
		.def("GetSource", &PanelEvent::GetSource, py::return_value_policy::reference)
		;

	py::class_<PanelCloseEvent, PanelEvent>(m, "PanelCloseEvent")
		.def("IsAccepted", &PanelCloseEvent::IsAccepted)
		.def("IsCancelled", &PanelCloseEvent::IsCancelled)
		;

	py::class_< PanelCloseRequestEvent, PanelEvent>(m, "PanelCloseRequestEvent")
		.def("IsAccepted", &PanelCloseRequestEvent::IsAccepted)
		.def("IsCancelled", &PanelCloseRequestEvent::IsCancelled)
		;

	py::class_< PanelContextMenuEvent, PanelEvent>(m, "PanelContextMenuEvent")
		.def("GetPanel", &PanelContextMenuEvent::GetPanel, py::return_value_policy::reference)
		.def("GetItem", &PanelContextMenuEvent::GetItem, py::return_value_policy::reference)
		.def("GetPosition", &PanelContextMenuEvent::GetPosition)
		;

	py::class_< PanelDropTargetEvent, PanelEvent/*,DropTargetEventProperty*/>(m, "PanelDropTargetEvent")
		;

	py::class_< PanelHelpEvent, PanelEvent>(m, "PanelHelpEvent")
		.def("GetItem", &PanelHelpEvent::GetItem, py::return_value_policy::reference)
		;

	py::class_< PanelHotKeyEvent, PanelEvent>(m, "PanelHotKeyEvent")
		.def("GetKeyId", &PanelHotKeyEvent::GetKeyId)
		;

	py::class_< PanelIdleEvent, PanelEvent>(m, "PanelIdleEvent")
		;

	py::class_< PanelOpenEvent, PanelEvent>(m, "PanelOpenEvent")
		.def("IsSavedPosition", &PanelOpenEvent::IsSavedPosition)
		.def("IsDefaultPosition", &PanelOpenEvent::IsDefaultPosition)
		.def("IsAdjustedPosition", &PanelOpenEvent::IsAdjustedPosition)
		;

	py::class_< PanelResizeEvent, PanelEvent>(m, "PanelResizeEvent")
		.def("IsUserResize", &PanelResizeEvent::IsUserResize)
		.def("GetHorizontalChange", &PanelResizeEvent::GetHorizontalChange)
		.def("GetVerticalChange", &PanelResizeEvent::GetVerticalChange)
		;

	py::class_< PanelScaleChangeEvent, PanelEvent>(m, "PanelScaleChangeEvent")
		.def("GetOldScale", &PanelScaleChangeEvent::GetOldScale)
		.def("GetNewScale", &PanelScaleChangeEvent::GetNewScale)
		;

	py::class_< PanelMoveEvent, PanelEvent>(m, "PanelMoveEvent")
		;

	py::class_< PanelTopStatusEvent, PanelEvent>(m, "PanelTopStatusEvent")
		.def("GetPreviousTopStatusPanel", &PanelTopStatusEvent::GetPreviousTopStatusPanel, py::return_value_policy::reference)
		.def("GetNextTopStatusPanel", &PanelTopStatusEvent::GetNextTopStatusPanel, py::return_value_policy::reference)
		.def("ByUser", &PanelTopStatusEvent::ByUser)
		;

	py::class_< PanelWheelEvent, PanelEvent>(m, "PanelWheelEvent")
		.def("GetItem", &PanelWheelEvent::GetItem, py::return_value_policy::reference)
		;

	py::class_< PanelWheelTrackEvent, PanelWheelEvent>(m, "PanelWheelTrackEvent")
		.def("GetXTrackValue", &PanelWheelTrackEvent::GetXTrackValue)
		.def("GetYTrackValue", &PanelWheelTrackEvent::GetYTrackValue)
		.def("GetMouseOffset", &PanelWheelTrackEvent::GetMouseOffset)
		.def("IsCommandPressed", &PanelWheelTrackEvent::IsCommandPressed)
		.def("IsOptionPressed", &PanelWheelTrackEvent::IsOptionPressed)
		.def("IsShiftPressed", &PanelWheelTrackEvent::IsShiftPressed)
		;

	py::class_< PanelBackgroundPaintEvent, PanelEvent>(m, "PanelBackgroundPaintEvent")
		.def("GetWidth", &PanelBackgroundPaintEvent::GetWidth)
		.def("GetHeight", &PanelBackgroundPaintEvent::GetHeight)
		//.def("GetDrawContext", &PanelBackgroundPaintEvent::GetDrawContext)
		;

	py::class_< PanelActivateEvent, PanelEvent>(m, "PanelActivateEvent")
		;

	py::class_<PyPanelObserver>(m, "PanelObserver",py::dynamic_attr())
		.def(py::init<Panel &,UINT64>())
		;


	py::class_<Panel/*, GS::EventSource*/>(m, "Panel")
		//.def("Attach", &Panel::Attach)
		//.def("Detach", &Panel::Detach)

		.def("IsValid", &Panel::IsValid)
		.def("IsExist", &Panel::IsExist)

		.def("GetId", &Panel::GetId)
		//.def("GetResourceId", &Panel::GetResourceId)

		//.def("SetResourceModule", &Panel::SetResourceModule)
		//.def("GetResourceModule", &Panel::GetResourceModule)

		.def("GetAnchorString", &Panel::GetAnchorString)

		.def("GetItemCount", &Panel::GetItemCount)
		.def("GetItem", &Panel::GetItem,py::return_value_policy::reference)

		.def("GetWidth", &Panel::GetWidth)
		.def("GetHeight", &Panel::GetHeight)

		.def("ClearFocus", &Panel::ClearFocus)

		.def("ShowItems", &Panel::ShowItems)
		.def("HideItems", &Panel::HideItems)
		.def("SetItemVisibility", &Panel::SetItemVisibility)
		.def("MaskItemsVisibility", &Panel::MaskItemsVisibility)

		.def("EnableItems", &Panel::EnableItems)
		.def("DisableItems", &Panel::DisableItems)
		.def("SetItemStatus", &Panel::SetItemStatus)

		.def("MoveItems", &Panel::MoveItems)

		.def("RedrawItems", &Panel::RedrawItems)

		.def("RegisterHotKey",
			(short (Panel::*)(Key::Special, Key::Modifier, Key::Modifier, Key::Modifier)) &Panel::RegisterHotKey,
			py::arg("keyCode"), 
			py::arg("mod1")=Key::NoModifier, 
			py::arg("mod2")= Key::NoModifier, 
			py::arg("mod3")= Key::NoModifier)
		.def("RegisterHotKey",
			(short (Panel::*)(short, Key::Modifier, Key::Modifier, Key::Modifier)) &Panel::RegisterHotKey,
			py::arg("keyCode"), 
			py::arg("mod1") = Key::NoModifier, 
			py::arg("mod2") = Key::NoModifier,
			py::arg("mod3") = Key::NoModifier)

		.def("UnregisterHotKey", &Panel::UnregisterHotKey)
		.def("EnableHotKeys", &Panel::EnableHotKeys)
		.def("DisableHotKeys", &Panel::DisableHotKeys)

		.def("EnableDragAndDropEvent", &Panel::EnableDragAndDropEvent)

		.def("EnableInputFiltering", &Panel::EnableInputFiltering)
		.def("DisableInputFiltering", &Panel::DisableInputFiltering)

		.def("GetScaleFactor", &Panel::GetScaleFactor)

		.def("IsDGDialog", &Panel::IsDGDialog)
		.def("IsSystemDialog", &Panel::IsSystemDialog)
		.def("IsTabPage", &Panel::IsTabPage);
}



