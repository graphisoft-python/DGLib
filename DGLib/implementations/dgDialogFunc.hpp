#include "../stdafx.h"

#include "DGDialog.hpp"
#include "ACCast.h"

using namespace DG;

void load_dg_Dialog(py::module m) {
	py::class_<Dialog, Panel> m_dialog(m, "Dialog");
	
	py::enum_<Dialog::DialogType>(m_dialog, "DialogType")
		.value("Modal",Dialog::DialogType::Modal)
		.value("Modeless", Dialog::DialogType::Modeless)
		.value("Palette", Dialog::DialogType::Palette)
		.export_values();

	py::enum_<Dialog::GrowType>(m_dialog, "GrowType")
		.value("NoGrow", Dialog::GrowType::NoGrow)
		.value("HGrow", Dialog::GrowType::HGrow)
		.value("VGrow", Dialog::GrowType::VGrow)
		.value("HVGrow", Dialog::GrowType::HVGrow)
		.export_values();

	py::enum_<Dialog::CloseType>(m_dialog, "CloseType")
		.value("NoClose", Dialog::CloseType::NoClose)
		.value("Close", Dialog::CloseType::Close)
		.export_values();

	py::enum_<Dialog::MinimizeType>(m_dialog, "MinimizeType")
		.value("NoMinimize", Dialog::MinimizeType::NoMinimize)
		.value("Minimize", Dialog::MinimizeType::Minimize);

	py::enum_<Dialog::MaximizeType>(m_dialog, "MaximizeType")
		.value("NoMaximize", Dialog::MaximizeType::NoMaximize)
		.value("Maximize", Dialog::MaximizeType::Maximize);

	py::enum_<Dialog::CaptionType>(m_dialog, "CaptionType")
		.value("TopCaption", Dialog::CaptionType::TopCaption)
		.value("LeftCaption", Dialog::CaptionType::LeftCaption)
		.value("NoCaption", Dialog::CaptionType::NoCaption)
		.export_values();

	py::enum_<Dialog::FrameType>(m_dialog, "FrameType")
		.value("NormalFrame", Dialog::FrameType::NormalFrame)
		.value("ThickFrame", Dialog::FrameType::ThickFrame)
		.value("NoFrame", Dialog::FrameType::NoFrame)
		.export_values();

	py::enum_<Dialog::FixPoint>(m_dialog, "FixPoint")
		.value("CenterPoint", Dialog::FixPoint::CenterPoint)
		.value("TopLeft", Dialog::FixPoint::TopLeft)
		.value("CenterLeft", Dialog::FixPoint::CenterLeft)
		.value("BottomLeft", Dialog::FixPoint::BottomLeft)
		.value("BottomCenter", Dialog::FixPoint::BottomCenter)
		.value("BottomRight", Dialog::FixPoint::BottomRight)
		.value("CenterRight", Dialog::FixPoint::CenterRight)
		.value("TopRight", Dialog::FixPoint::TopRight)
		.value("TopCenter", Dialog::FixPoint::TopCenter)
		.export_values();

	py::enum_<Dialog::GrowBoxForm>(m_dialog, "GrowBoxForm")
		.value("Triangle", Dialog::GrowBoxForm::Triangle)
		.value("Square", Dialog::GrowBoxForm::Square)
		.export_values();

	py::enum_<Dialog::SpecialFeatures>(m_dialog, "SpecialFeatures")
		.value("NothingSpecial", Dialog::SpecialFeatures::NothingSpecial)
		.value("NoUpdate", Dialog::SpecialFeatures::NoUpdate)
		.value("FrameDialog", Dialog::SpecialFeatures::FrameDialog)
		.export_values();
	
	
	m_dialog
		.def("GetDialogType", &Dialog::GetDialogType)
		.def("IsDGDialog", &Dialog::IsDGDialog)

		.def("Center", &Dialog::Center)
		.def("Move", (void (Dialog::*)
			(short, short))	&Dialog::Move)
		.def("Move", (void (Dialog::*)
			(const NativeUnit &, const NativeUnit &)) &Dialog::Move)
		.def("Resize", &Dialog::Resize,
			py::arg("hGrow"), 
			py::arg("vGrow"), 
			py::arg("fixPoint") = Dialog::FixPoint::TopLeft, 
			py::arg("keepOld") = false)

		.def("SetGrowType", &Dialog::SetGrowType)
		.def("GetGrowType", &Dialog::GetGrowType)

		.def("GetOriginalClientWidth", &Dialog::GetOriginalClientWidth)
		.def("GetOriginalClientHeight", &Dialog::GetOriginalClientHeight)

		.def("SetMinClientSize", &Dialog::SetMinClientSize)
		.def("SetMinClientWidth", &Dialog::SetMinClientWidth)
		.def("SetMinClientHeight", &Dialog::SetMinClientHeight)

		.def("GetMinClientWidth", &Dialog::GetMinClientWidth)
		.def("GetMinClientHeight", &Dialog::GetMinClientHeight)

		.def("SetClientPosition", (void (Dialog::*)
			(const NativePoint &)) &Dialog::SetClientPosition)
		.def("SetClientPosition", (void (Dialog::*)
			(const NativeUnit &, const NativeUnit &)) &Dialog::SetClientPosition)

		.def("SetClientRect", &Dialog::SetClientRect,
			py::arg("rect"),
			py::arg("fixPoint") = Dialog::FixPoint::TopLeft, 
			py::arg("keepOld") = false)

		.def("SetClientSize", &Dialog::SetClientSize,
			py::arg("width"), 
			py::arg("height"),
			py::arg("fixPoint") = Dialog::FixPoint::TopLeft, 
			py::arg("keepOld") = false)
		.def("SetClientWidth", &Dialog::SetClientWidth, 
			py::arg("width"),
			py::arg("fixPoint") = Dialog::FixPoint::TopLeft, 
			py::arg("keepOld") = false)
		.def("SetClientHeight", &Dialog::SetClientHeight, 
			py::arg("height"),
			py::arg("fixPoint") = Dialog::FixPoint::TopLeft, 
			py::arg("keepOld") = false)

		.def("GetClientPosition", &Dialog::GetClientPosition)

		.def("GetClientRect", &Dialog::GetClientRect)

		.def("GetClientWidth", &Dialog::GetClientWidth)
		.def("GetClientHeight", &Dialog::GetClientHeight)

		.def("GetOriginalFrameWidth", &Dialog::GetOriginalFrameWidth)
		.def("GetOriginalFrameHeight", &Dialog::GetOriginalFrameHeight)

		.def("SetMinFrameSize", &Dialog::SetMinFrameSize)
		.def("SetMinFrameWidth", &Dialog::SetMinFrameWidth)
		.def("SetMinFrameHeight", &Dialog::SetMinFrameHeight)

		.def("GetMinFrameWidth", &Dialog::GetMinFrameWidth)
		.def("GetMinFrameHeight", &Dialog::GetMinFrameHeight)

		.def("SetFramePosition", (void (Dialog::*)
			(const NativePoint &)) &Dialog::SetFramePosition)
		.def("SetFramePosition", (void (Dialog::*)
			(const NativeUnit &, const NativeUnit &)) &Dialog::SetFramePosition)

		.def("SetFrameRect", &Dialog::SetFrameRect, 
			py::arg("rect"),
			py::arg("fixPoint") = Dialog::FixPoint::TopLeft, 
			py::arg("keepOld") = false)
		.def("SetFrameSize", &Dialog::SetFrameSize, 
			py::arg("width"), 
			py::arg("height"),
			py::arg("fixPoint") = Dialog::FixPoint::TopLeft, 
			py::arg("keepOld") = false)
		.def("SetFrameWidth", &Dialog::SetFrameWidth, 
			py::arg("width"),
			py::arg("fixPoint") = Dialog::FixPoint::TopLeft, 
			py::arg("keepOld") = false)
		.def("SetFrameHeight", &Dialog::SetFrameHeight, 
			py::arg("height"),
			py::arg("fixPoint") = Dialog::FixPoint::TopLeft, 
			py::arg("keepOld") = false)

		.def("GetFramePosition", &Dialog::GetFramePosition)
		.def("GetFrameRect", &Dialog::GetFrameRect)
		.def("GetFrameWidth", &Dialog::GetFrameWidth)
		.def("GetFrameHeight", &Dialog::GetFrameHeight)

		.def("BeginMoveResizeItems", &Dialog::BeginMoveResizeItems)
		.def("EndMoveResizeItems", &Dialog::EndMoveResizeItems)

		.def("SetTitle", &Dialog::SetTitle)
		.def("GetTitle", &Dialog::GetTitle)

		.def("EnableIdleEvent", &Dialog::EnableIdleEvent,
			py::arg("sendForInactiveApp") = false)

		.def("EnableNormalUpdate", &Dialog::EnableNormalUpdate)
		.def("DisableNormalUpdate", &Dialog::DisableNormalUpdate)

		.def("SetPopupStyle", &Dialog::SetPopupStyle)
		.def("HasPopupStyle", &Dialog::HasPopupStyle)

		.def("EnableGrowBox", &Dialog::EnableGrowBox)
		.def("DisableGrowBox", &Dialog::DisableGrowBox)
		.def("IsGrowBoxEnabled", &Dialog::IsGrowBoxEnabled)

		.def("SetGrowBoxSize", &Dialog::SetGrowBoxSize)
		.def("GetGrowBoxSize", &Dialog::GetGrowBoxSize)

		.def("SetGrowBoxForm", &Dialog::SetGrowBoxForm)
		.def("GetGrowBoxForm", &Dialog::GetGrowBoxForm)

		.def("RegisterDragAndDrop", &Dialog::RegisterDragAndDrop)
		.def("RevokeDragAndDrop", &Dialog::RevokeDragAndDrop)

		.def("EnableDraw", &Dialog::EnableDraw)
		.def("DisableDraw", &Dialog::DisableDraw)
		.def("Redraw", &Dialog::Redraw)

		.def("SetCursorPosition", &Dialog::SetCursorPosition)

		.def("KeepInScreen", &Dialog::KeepInScreen)

		.def("HasChangedDialogItems", &Dialog::HasChangedDialogItems)
		.def("ResetDialogItemChanges", &Dialog::ResetDialogItemChanges);
}

void load_dg_ModaDialog(py::module m) {
	py::class_<ModalDialog, Dialog> m_modalDialog(m,"ModalDialog");
	
	py::enum_<ModalDialog::ModalResponse>(m_modalDialog, "ModalResponse")
		.value("Accept", ModalDialog::ModalResponse::Accept)
		.value("Cancel", ModalDialog::ModalResponse::Cancel)
		.export_values();


	m_modalDialog
		.def(py::init<NativePoint &, short, short, GS::Guid &, ModalDialog::GrowType, ModalDialog::CaptionType, ModalDialog::FrameType>(),
			py::arg("position"), 
			py::arg("width"), 
			py::arg("height"), 
			py::arg("guid"), 
			py::arg("growType") = ModalDialog::GrowType::NoGrow,
			py::arg("captionType") = ModalDialog::CaptionType::TopCaption,
			py::arg("frameType") = ModalDialog::FrameType::NormalFrame)

		.def("Invoke", &ModalDialog::Invoke)
		.def("Abort", &ModalDialog::Abort)

		.def("PostCloseRequest", &ModalDialog::PostCloseRequest)

		.def("GetNextModalDialog", &ModalDialog::GetNextModalDialog,py::return_value_policy::reference)
		.def("GetPrevModalDialog", &ModalDialog::GetPrevModalDialog,py::return_value_policy::reference);
}

void load_dg_ModelessBase(py::module m) {
	py::class_<ModelessBase, Dialog> m_modalDialog(m, "ModelessBase");

	py::enum_<ModelessBase::DialogStatus>(m_modalDialog, "DialogStatus")
		.value("Normal", ModelessBase::DialogStatus::Normal)
		.value("Enabled", ModelessBase::DialogStatus::Enabled)
		.value("Disabled", ModelessBase::DialogStatus::Disabled)
		.value("Edited", ModelessBase::DialogStatus::Edited)
		.export_values();


	m_modalDialog
		.def("BeginEventProcessing", &ModelessBase::BeginEventProcessing)
		.def("EndEventProcessing", &ModelessBase::EndEventProcessing)
		.def("SendCloseRequest", &ModelessBase::SendCloseRequest)

		.def("BringToFront", &ModelessBase::BringToFront)
		.def("SendToBack", &ModelessBase::SendToBack)

		.def("Show", &ModelessBase::Show,
			py::arg("refDialId")= DG_DF_FIRST)
		.def("Hide", &ModelessBase::Hide)
		.def("SetVisibility", &ModelessBase::SetVisibility)
		.def("IsVisible", &ModelessBase::IsVisible)

		.def("Activate", &ModelessBase::Activate)
		.def("IsActive", &ModelessBase::IsActive)

		.def("SetStatus", &ModelessBase::SetStatus)
		.def("GetStatus", &ModelessBase::GetStatus);
}

void load_dg_ModelessDialog(py::module m) {
	py::class_<ModelessDialog, ModelessBase> m_modelessDialog(m, "ModelessDialog");

	py::enum_<ModelessDialog::DialogState>(m_modelessDialog, "DialogState")
		.value("Maximized", ModelessDialog::DialogState::Maximized)
		.value("Minimized", ModelessDialog::DialogState::Minimized)
		.value("Restored", ModelessDialog::DialogState::Restored)
		.export_values();

	py::enum_<ModelessDialog::DockState>(m_modelessDialog, "DockState")
		.value("Docked", ModelessDialog::DockState::Docked)
		.value("Undocked", ModelessDialog::DockState::Undocked)
		.export_values();


	m_modelessDialog
		.def(py::init<NativePoint &, short, short, GS::Guid &, ModelessDialog::GrowType, ModelessDialog::CloseType, ModelessDialog::MinimizeType, ModelessDialog::MaximizeType, ModelessDialog::CaptionType, ModelessDialog::FrameType, ModelessDialog::SpecialFeatures>(),
			py::arg("position"), 
			py::arg("width"), 
			py::arg("height"), 
			py::arg("guid"), 
			py::arg("growType") = ModelessDialog::GrowType::NoGrow,
			py::arg("closeType") = ModelessDialog::CloseType::NoClose,
			py::arg("minimizeType") = ModelessDialog::MinimizeType::NoMinimize,
			py::arg("maximizeType") = ModelessDialog::MaximizeType::NoMaximize,
			py::arg("captionType") = ModelessDialog::CaptionType::TopCaption,
			py::arg("frameType") = ModelessDialog::FrameType::NormalFrame,
			py::arg("specialFeatures") = ModelessDialog::SpecialFeatures::NothingSpecial)

		.def("SendBehind", &ModelessDialog::SendBehind)

		.def("GetNextModelessDialog", &ModelessDialog::GetNextModelessDialog, py::return_value_policy::reference)
		.def("GetPrevModelessDialog", &ModelessDialog::GetPrevModelessDialog, py::return_value_policy::reference)
		.def("GetNextVisibleModelessDialog", &ModelessDialog::GetNextVisibleModelessDialog, py::return_value_policy::reference)
		.def("GetPrevVisibleModelessDialog", &ModelessDialog::GetPrevVisibleModelessDialog, py::return_value_policy::reference)

		.def("GetRestoredClientPosition", &ModelessDialog::GetRestoredClientPosition)
		.def("GetRestoredClientWidth", &ModelessDialog::GetRestoredClientWidth)
		.def("GetRestoredClientHeight", &ModelessDialog::GetRestoredClientHeight)

		.def("GetRestoredFramePosition", &ModelessDialog::GetRestoredFramePosition)
		.def("GetRestoredFrameRect", &ModelessDialog::GetRestoredFrameRect)
		.def("GetRestoredFrameWidth", &ModelessDialog::GetRestoredFrameWidth)
		.def("GetRestoredFrameHeight", &ModelessDialog::GetRestoredFrameHeight)

		.def("Maximize", &ModelessDialog::Maximize, 
			py::arg("beforeDock") = false)
		.def("Minimize", &ModelessDialog::Minimize)
		.def("Restore", &ModelessDialog::Restore)
		.def("SetState", &ModelessDialog::SetState, 
			py::arg("state"), 
			py::arg("beforeDock") = false)

		.def("IsMaximizedState", &ModelessDialog::IsMaximizedState)
		.def("IsMinimizedState", &ModelessDialog::IsMinimizedState)
		.def("IsRestoredState", &ModelessDialog::IsRestoredState)
		.def("GetState", &ModelessDialog::GetState)

		.def("Dock", &ModelessDialog::Dock)
		.def("Undock", &ModelessDialog::Undock)
		.def("IsDocked", &ModelessDialog::IsDocked)
		.def("SetDockState", &ModelessDialog::SetDockState)
		.def("GetDockState", &ModelessDialog::GetDockState);
}

void load_dg_Palette(py::module m) {
	py::class_<Palette, ModelessBase>(m, "Palette")
		.def(py::init<NativePoint &, short, short, GS::Guid &, Palette::GrowType, Palette::CloseType, Palette::CaptionType, Palette::FrameType, Palette::SpecialFeatures>(),
			py::arg("position"), 
			py::arg("width"), 
			py::arg("height"), 
			py::arg("guid"), 
			py::arg("growType") = Palette::GrowType::NoGrow,
			py::arg("closeType") = Palette::CloseType::NoClose,
			py::arg("captionType") = Palette::CaptionType::TopCaption,
			py::arg("frameType") = Palette::FrameType::NormalFrame,
			py::arg("specialFeatures") = Palette::SpecialFeatures::NothingSpecial)

		.def("SendBehind", &Palette::SendBehind)

		.def("GetNextPalette", &Palette::GetNextPalette, py::return_value_policy::reference)
		.def("GetPrevPalette", &Palette::GetPrevPalette, py::return_value_policy::reference)
		.def("GetNextVisiblePalette", &Palette::GetNextVisiblePalette, py::return_value_policy::reference)
		.def("GetPrevVisiblePalette", &Palette::GetPrevVisiblePalette, py::return_value_policy::reference)
		
		.def("DisableDock", &Palette::DisableDock)

		.def("Dock", &Palette::Dock)
		.def("UnDock", &Palette::UnDock)

		.def("IsDocked", &Palette::IsDocked)

		.def("GetCaptionType", &Palette::GetCaptionType);
}


