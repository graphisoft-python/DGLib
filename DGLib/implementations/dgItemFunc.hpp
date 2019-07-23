#pragma once

#include "../stdafx.h"

#include "DGPanel.hpp"
#include "DGItem.hpp"

using namespace DG;

// --- PyItemObserver ------------------------------------------------------------------------

class  PyItemObserver : ItemObserver {
public:
	PyItemObserver(Item &item, ACExport &acExport)
		:m_parent(item) {
		this->m_parent.Attach(*this);
		this->m_state = acExport.m_state;
	}

	~PyItemObserver() {
		this->m_parent.Detach(*this);
	}

	void ItemChangeRequested(const ItemMouseDownEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemChangeRequested", ev);
	}

	void ItemChanged(const ItemChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemChanged", ev);
	}

	void ItemCharEntered(const ItemCharEnterEvent& ev, bool* denyChar) override {
		OBSERVER_CALL_EVENT_WITH_RETURN("ItemCharEntered", ev, denyChar, bool);
	}

	void ItemClicked(const ItemClickEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemClicked", ev);
	}

	void ItemMouseDown(const ItemMouseDownEvent& ev, bool* processed) override {
		OBSERVER_CALL_EVENT_SET_PROCESSED("ItemMouseDown", ev, processed);
	}

	void ItemContextHelpRequested(const ItemHelpEvent& ev, GS::UniString* contextHelpAnchor) override {
		OBSERVER_CALL_EVENT_WITH_RETURN("ItemContextHelpRequested", ev, contextHelpAnchor, GS::UniString);
	}

	void ItemContextMenuRequested(const ItemContextMenuEvent& ev, bool* needHelp, bool* processed) override {
		OBSERVER_CALL_EVENT_WITH_RETURN_AND_SET_PROCESSED("ItemContextMenuRequested", ev, needHelp, bool, processed);
	}

	void ItemDoubleClicked(const ItemDoubleClickEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemDoubleClicked", ev);
	}

	void ItemFocusGained(const ItemFocusEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemFocusGained", ev);
	}

	void ItemFocusLost(const ItemFocusEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemFocusLost", ev);
	}

	void ItemMouseMoved(const ItemMouseMoveEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemMouseMoved", ev);
	}

	void ItemToolTipRequested(const ItemHelpEvent& ev, GS::UniString* toolTipText) override {
		OBSERVER_CALL_EVENT_WITH_RETURN("ItemToolTipRequested", ev, toolTipText, GS::UniString);
	}

	void ItemTrackEntered(const ItemTrackEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemTrackEntered", ev);
	}

	void ItemTracked(const ItemTrackEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemTracked", ev);
	}

	void ItemTrackExited(const ItemTrackEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemTrackExited", ev);
	}

	void ItemUpdate(const ItemUpdateEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemUpdate", ev);
	}

	void ItemWheelTrackEntered(const ItemWheelEvent& ev, bool* processed) override {
		OBSERVER_CALL_EVENT_SET_PROCESSED("ItemWheelTrackEntered", ev, processed);
	}

	void ItemWheelTracked(const ItemWheelTrackEvent& ev, bool* processed) override {
		OBSERVER_CALL_EVENT_SET_PROCESSED("ItemWheelTracked", ev, processed);
	}

	void ItemWheelTrackExited(const ItemWheelEvent& ev, bool* processed) override {
		OBSERVER_CALL_EVENT_SET_PROCESSED("ItemWheelTrackExited", ev, processed);
	}

	void ItemResolutionFactorChanged(const ItemResolutionFactorChangeEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemResolutionFactorChanged", ev);
	}

	void ItemHoverStarted(const ItemHoverEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemHoverStarted", ev);
	}

	void ItemHoverEnded(const ItemHoverEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemHoverEnded", ev);
	}

	void ItemPressed(const ItemPressedEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemPressed", ev);
	}

	void ItemOverlayUpdate(const ItemUpdateEvent& ev) override {
		OBSERVER_CALL_EVENT("ItemOverlayUpdate", ev);
	}

	//short SpecChangeRequested(const ItemMouseDownEvent& ev) override {
	
	//}

	//short SpecChanged(const ItemChangeEvent& ev) override {
	
	//}

	//short SpecClicked(const ItemClickEvent& ev) override {
	
	//}

	//short SpecMouseDown(const ItemMouseDownEvent& ev, bool* processed) override {
	
	//}

	//short SpecContextMenuRequested(const ItemContextMenuEvent& ev) override {
	
	//}

	//short SpecDoubleClicked(const ItemDoubleClickEvent& ev) override {
	
	//}

	//short SpecDragStarting(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragStarted(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEnded(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragSetDelayedData(const ItemDragSourceEvent& ev) override {

	//}

	//short SpecDragEntered(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragMoved(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDragLeft(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecDropped(const ItemDropTargetEvent& ev) override {

	//}

	//short SpecMouseMoved(const ItemMouseMoveEvent& ev) override {
	
	//}

	//short SpecTrackEntered(const ItemTrackEvent& ev) override {
	
	//}

	//short SpecTracked(const ItemTrackEvent& ev) override {
	
	//}

	//short SpecTrackExited(const ItemTrackEvent& ev) override {
	
	//}

	//short SpecUpdate(const ItemUpdateEvent& ev) override {
	
	//}

	//short SpecResolutionFactorChanged(const ItemResolutionFactorChangeEvent& ev) override {
	
	//}

	//short SpecHoverStarted(const ItemHoverEvent& ev) override {
	
	//}

	//short SpecHoverEnded(const ItemHoverEvent& ev) override {

	//}

	//short SpecPressed(const ItemPressedEvent& ev) override {
	
	//}

	//short SpecOverlayUpdate(const ItemUpdateEvent& ev) override {
	
	//}

private:
	Item			&m_parent;
	PyThreadState	*m_state;
};


// --- ItemBase ------------------------------------------------------------------------------

void load_dg_ItemBase(py::module m) {
	py::class_<ItemBase> (m, "ItemBase")
		.def("IsValid", &ItemBase::IsValid)
		.def("GetPanel", &ItemBase::GetPanel, py::return_value_policy::reference)
		.def("GetPanelId", &ItemBase::GetPanelId)
		.def("GetId", &ItemBase::GetId);
}

// --- Item ----------------------------------------------------------------------------------

void load_dg_Item(py::module m) {
	// --- ItemEvent -------------------------------------------------------------------------
	py::class_<ItemEvent/*, GS::Event*/>(m, "ItemEvent")
		.def("GetSource", &ItemEvent::GetSource, py::return_value_policy::reference);

	// --- ItemChangeEvent -------------------------------------------------------------------
	py::class_<ItemChangeEvent, ItemEvent>(m, "ItemChangeEvent");

	// --- ItemResizeEvent -------------------------------------------------------------------
	py::class_<ItemResizeEvent, ItemEvent>(m, "ItemResizeEvent");

	// --- ItemCharEnterEvent ----------------------------------------------------------------
	py::class_<ItemCharEnterEvent, ItemEvent>(m, "ItemCharEnterEvent")
		.def("GetCharCode",&ItemCharEnterEvent::GetCharCode);

	// --- ItemClickEvent --------------------------------------------------------------------
	py::class_<ItemClickEvent, ItemEvent>(m, "ItemClickEvent");

	// --- ItemMouseDownEvent ----------------------------------------------------------------
	py::class_<ItemMouseDownEvent, ItemEvent>(m, "ItemMouseDownEvent")
		.def("IsHovered",&ItemMouseDownEvent::IsHovered);

	// --- ItemContextMenuEvent --------------------------------------------------------------
	py::class_<ItemContextMenuEvent, ItemEvent>(m, "ItemContextMenuEvent")
		.def("GetPosition", &ItemContextMenuEvent::GetPosition);

	// --- ItemDoubleClickEvent --------------------------------------------------------------
	py::class_<ItemDoubleClickEvent, ItemEvent>(m, "ItemDoubleClickEvent");

	// --- ItemDragSourceEvent ---------------------------------------------------------------
	//py::class_<ItemDragSourceEvent, ItemEvent, ItemDragDropData>(m, "ItemDragSourceEvent")
	//	.def("GetDragData",&ItemDragSourceEvent::GetDragData, py::return_value_policy::reference);

	// --- ItemDropTargetEvent ---------------------------------------------------------------
	//py::class_<ItemDropTargetEvent, ItemEvent, DropTargetEventProperty>(m, "ItemDropTargetEvent");

	// --- ItemFocusEvent --------------------------------------------------------------------
	py::class_<ItemFocusEvent, ItemEvent>(m, "ItemFocusEvent");

	// --- ItemHelpEvent ---------------------------------------------------------------------
	py::class_<ItemHelpEvent, ItemEvent>(m, "ItemHelpEvent")
		.def("GetSubItem", &ItemHelpEvent::GetSubItem)
		.def("GetTreeItem", &ItemHelpEvent::GetTreeItem)
		.def("GetTabBarItemId", &ItemHelpEvent::GetTabBarItemId);

	// --- ItemMouseMoveEvent ----------------------------------------------------------------
	py::class_<ItemMouseMoveEvent, ItemEvent>(m, "ItemMouseMoveEvent");

	// --- ItemTrackEvent --------------------------------------------------------------------
	py::class_<ItemTrackEvent, ItemEvent>(m, "ItemTrackEvent");

	// --- ItemUpdateEvent -------------------------------------------------------------------
	py::class_<ItemUpdateEvent, ItemEvent>(m, "ItemUpdateEvent");

	// --- ItemWheelEvent --------------------------------------------------------------------
	py::class_<ItemWheelEvent, ItemEvent>(m, "ItemWheelEvent");

	// --- ItemWheelTrackEvent ---------------------------------------------------------------
	py::class_<ItemWheelTrackEvent, ItemWheelEvent>(m, "ItemWheelTrackEvent")
		.def("GetXTrackValue", &ItemWheelTrackEvent::GetXTrackValue)
		.def("GetYTrackValue", &ItemWheelTrackEvent::GetYTrackValue)
		.def("GetMouseOffset", &ItemWheelTrackEvent::GetMouseOffset)
		.def("IsCommandPressed", &ItemWheelTrackEvent::IsCommandPressed)
		.def("IsOptionPressed", &ItemWheelTrackEvent::IsOptionPressed)
		.def("IsShiftPressed", &ItemWheelTrackEvent::IsShiftPressed)
		.def("IsCommandProcessed", &ItemWheelTrackEvent::IsCommandProcessed)
		.def("IsOptionProcessed", &ItemWheelTrackEvent::IsOptionProcessed)
		.def("IsShiftProcessed", &ItemWheelTrackEvent::IsShiftProcessed)
		.def("IsFromTouchCapableDevice", &ItemWheelTrackEvent::IsFromTouchCapableDevice);

	// --- ItemResolutionFactorChangeEvent ----------------------------------------------------
	py::class_<ItemResolutionFactorChangeEvent, ItemEvent>(m, "ItemResolutionFactorChangeEvent")
		.def("GetOldResolutionFactor", &ItemResolutionFactorChangeEvent::GetOldResolutionFactor);

	// --- ItemHoverEvent ---------------------------------------------------------------------
	py::class_<ItemHoverEvent, ItemEvent>(m, "ItemHoverEvent");

	// --- ItemPressedEvent -------------------------------------------------------------------
	py::class_<ItemPressedEvent, ItemEvent>(m, "ItemPressedEvent");

	// --- PyItemObserver ---------------------------------------------------------------------
	py::class_<PyItemObserver>(m, "ItemObserver", py::dynamic_attr())
		.def(py::init<Item &, ACExport &>());

	// --- Item -------------------------------------------------------------------------------
	py::class_<Item, ItemBase/*, GS::EventSource*/>(m, "Item")
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("Show", &Item::Show)
		.def("Hide", &Item::Hide)
		.def("SetVisibility", &Item::SetVisibility)
		.def("IsVisible", &Item::IsVisible)
		.def("Flash", &Item::Flash)
		.def("Enable", &Item::Enable)
		.def("Disable", &Item::Disable)
		.def("SetStatus", &Item::SetStatus)
		.def("IsEnabled", &Item::IsEnabled)
		.def("Move", &Item::Move)
		.def("Resize", &Item::Resize)
		.def("MoveAndResize", &Item::MoveAndResize)
		.def("SetPosition", (void (Item::*)
			(const Point &)) &Item::SetPosition)
		.def("SetPosition", (void (Item::*)
			(short, short)) &Item::SetPosition)
		.def("SetRect", &Item::SetRect)
		.def("SetSize", &Item::SetSize)
		.def("SetWidth", &Item::SetWidth)
		.def("SetHeight", &Item::SetHeight)
		.def("GetPosition", &Item::GetPosition)
		.def("GetRect", &Item::GetRect)
		.def("GetWidth", &Item::GetWidth)
		.def("GetHeight", &Item::GetHeight)
		.def("GetNativeRectInScreenSpace", &Item::GetNativeRectInScreenSpace)
		.def("Invalidate", &Item::Invalidate)
		.def("Redraw", &Item::Redraw)
		.def("ResetModified", &Item::ResetModified)
		.def("IsModified", &Item::IsModified)
		.def("GetTooltipString", &Item::GetTooltipString)
		.def("GetAnchorString", &Item::GetAnchorString)
		.def("InvokeDragDrop", &Item::InvokeDragDrop)
		.def("GetResolutionFactor", &Item::GetResolutionFactor);
}
