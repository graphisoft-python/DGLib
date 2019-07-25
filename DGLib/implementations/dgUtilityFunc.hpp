#pragma once

#include "../stdafx.h"

#include "DGWImageCache.hpp"
#include "DGUtility.hpp"

using namespace DG;


//namespace DG::EOL -----------------------------------------------------------------------

void load_dg_EOL(py::module m) {
	py::enum_<EOL::Type>(m, "Type")
		.value("Default", EOL::Type::Default)
		.value("CR", EOL::Type::CR)
		.value("CRLF", EOL::Type::CRLF)
		.export_values();
}


// --- namespace DG::Search ---------------------------------------------------------------

//void load_dg_Search(py::module m) {
//	py::enum_<Search::Dir>(m, "Dir")
//		.value("Down", Search::Dir::Down)
//		.value("Up", Search::Dir::Up)
//		.export_values();
//
//	py::enum_<Search::Case>(m, "Case")
//		.value("InSensitive", Search::Case::InSensitive)
//		.value("Sensitive", Search::Case::Sensitive)
//		.export_values();
//
//	py::enum_<Search::Word>(m, "Word")
//		.value("NoMatchWord", Search::Word::NoMatchWord)
//		.value("MatchWord", Search::Word::MatchWord)
//		.export_values();
//}


// --- namespace DG::UC -------------------------------------------------------------------

//void load_dg_UC(py::module m) {
//	py::enum_<UC::UC257CellSkinType>(m, "UC257CellSkinType")
//		.value("FillSkin", UC::UC257CellSkinType::FillSkin)
//		.value("EmptySkin", UC::UC257CellSkinType::EmptySkin)
//		.value("SurfaceSkin", UC::UC257CellSkinType::SurfaceSkin)
//		.value("MissingSkin", UC::UC257CellSkinType::MissingSkin)
//		.value("DefaultSkin", UC::UC257CellSkinType::DefaultSkin)
//		.export_values();
//}


// --- GS::Range<Int32> -------------------------------------------------------------------

void load_dg_CharRange(py::module m) {
	py::class_<CharRange>(m, "CharRange")
		.def(py::init<>())
		.def(py::init<Int32 &, Int32 &>())

		.def("Set", &CharRange::Set)
		.def("SetWithLength", &CharRange::SetWithLength)

		.def("GetMin", &CharRange::GetMin)
		.def("GetMax", &CharRange::GetMax)
		.def("GetLength", &CharRange::GetLength)

		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("IsOverlapping", &CharRange::IsOverlapping)
		.def("IsInside", &CharRange::IsInside)
		.def("IsEmpty", &CharRange::IsEmpty)

		.def("Union", &CharRange::Union)
		.def("Intersection", &CharRange::Intersection)

		.def("Unify", &CharRange::Unify)
		.def("Intersect", &CharRange::Intersect);
}


// --- namespace DG::Unit -----------------------------------------------------------------

//void load_dg_Unit(py::module m) {
//	py::enum_<Unit::Type>(m, "Type")
//		.value("Unit_MM", Unit::Type::Unit_MM)
//		.value("Unit_CM", Unit::Type::Unit_CM)
//		.value("Unit_DM", Unit::Type::Unit_DM)
//		.value("Unit_M", Unit::Type::Unit_M)
//		.value("Unit_KM", Unit::Type::Unit_KM)
//
//		.value("Unit_DecInch", Unit::Type::Unit_DecInch)
//		.value("Unit_FootInch", Unit::Type::Unit_FootInch)
//		.value("Unit_Inch", Unit::Type::Unit_Inch)
//		.value("Unit_FootDecInch", Unit::Type::Unit_FootDecInch)
//		.value("Unit_DecFoot", Unit::Type::Unit_DecFoot)
//
//		.value("Unit_DecDegree", Unit::Type::Unit_DecDegree)
//		.value("Unit_DegMinSec", Unit::Type::Unit_DegMinSec)
//		.value("Unit_Grad", Unit::Type::Unit_Grad)
//		.value("Unit_Radian", Unit::Type::Unit_Radian)
//		.value("Unit_Surveyors", Unit::Type::Unit_Surveyors)
//		.export_values();
//}


//namespace DG::Key -----------------------------------------------------------------------
void load_dg_Key(py::module m) {
	py::enum_<Key::Modifier>(m, "Modifier")
		.value("NoModifier", Key::Modifier::NoModifier)
		.value("Command", Key::Modifier::Command)
		.value("Option", Key::Modifier::Option)
		.value("Shift", Key::Modifier::Shift)
		.value("Ctrl", Key::Modifier::Ctrl)
		.export_values();

	py::enum_<Key::Special> (m, "Special")
		.value("Back", Key::Special::Back)
		.value("Tab", Key::Special::Tab)
		.value("Enter", Key::Special::Enter)
		.value("Return", Key::Special::Return)
		.value("Escape", Key::Special::Escape)

		.value("Left", Key::Special::Left)
		.value("Right", Key::Special::Right)
		.value("Up", Key::Special::Up)
		.value("Down", Key::Special::Down)

		.value("Insert", Key::Special::Insert)
		.value("Delete", Key::Special::Delete)
		.value("Home", Key::Special::Home)
		.value("End", Key::Special::End)
		.value("PageUp", Key::Special::PageUp)
		.value("PageDown", Key::Special::PageDown)

		.value("F1", Key::Special::F1)
		.value("F2", Key::Special::F2)
		.value("F3", Key::Special::F3)
		.value("F4", Key::Special::F4)
		.value("F5", Key::Special::F5)
		.value("F6", Key::Special::F6)
		.value("F7", Key::Special::F7)
		.value("F8", Key::Special::F8)
		.value("F9", Key::Special::F9)
		.value("F10", Key::Special::F10)
		.value("F11", Key::Special::F11)
		.value("F12", Key::Special::F12)
		.value("F13", Key::Special::F13)
		.value("F14", Key::Special::F14)
		.value("F15", Key::Special::F15)

		.value("Help", Key::Special::Help)
		.export_values();

	py::class_<Key::Code>(m, "Code")
		.def(py::init<>())
		.def(py::init<Key::Special>())
		.def(py::init<char>())

		.def("IsSpecial", &Key::Code::IsSpecial)
		.def("GetChar", &Key::Code::GetChar)
		.def("GetSpecialKey", &Key::Code::GetSpecialKey)
		.def("GetValue", &Key::Code::GetValue)

		.def(py::self == py::self)
		.def(py::self != py::self);
}


// --- Image ------------------------------------------------------------------------------ 

//void load_dg_Image(py::module m) {
//	py::class_<Image>(m, "Image")
//		.def(py::init<>())
//		.def(py::init<GSResModule, short>())
//		.def(py::init<void*>())
//
//		.def(py::self == py::self)
//		.def(py::self != py::self)
//
//		.def("GetResourceModule", &Image::GetResourceModule)
//		.def("GetResourceId", &Image::GetResourceId)
//		.def("GetData", &Image::GetData, py::return_value_policy::reference)
//
//		.def("IsEmpty", &Image::IsEmpty)
//		.def("IsValid", &Image::IsValid);
//}


// --- Icon -------------------------------------------------------------------------------

//void load_dg_Icon(py::module m) {
//	py::class_<Icon, Image>(m, "Icon")
//		.def(py::init<>())
//		.def(py::init<GSResModule, short>())
//		.def(py::init<void*>())
//		
//		.def("IsValid", &Icon::IsValid);
//}


// --- Picture ----------------------------------------------------------------------------

//void load_dg_Picture(py::module m) {
//	py::class_<Picture, Image>(m, "Picture")
//		.def(py::init<>())
//		.def(py::init<GSResModule, short>())
//		.def(py::init<void*>());
//}


// --- NativeImage ------------------------------------------------------------------------

//void load_dg_NativeImage(py::module m) {
//	py::class_<NativeImage>(m, "NativeImage")
//		.def(py::init<>())
//		.def(py::init<void*, double>())
//		.def(py::init<GSResModule, GSResID, double>())
//		.def(py::init<GSResModule, GSResID, UInt32, UInt32, double>())
//		.def(py::init<Image &, double>())
//
//		.def("GetNativeImage", &NativeImage::GetNativeImage);
//}


// --- NativeUnit -------------------------------------------------------------------------

void load_dg_NativeUnit(py::module m) {
	py::class_<NativeUnit>(m, "NativeUnit")
		.def(py::init<>())
		.def(py::init<short>())
		.def(py::init<short, double>())
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def(py::self > py::self)
		.def(py::self >= py::self)
		.def(py::self < py::self)
		.def(py::self <= py::self)
		//.def(py::self = py::self)
		.def(py::self += py::self)
		.def(py::self -= py::self)
		.def(py::self + py::self)
		.def(py::self - py::self)
		.def(py::self * short())
		.def(py::self / short())
		.def(-py::self)
		.def("Add", &NativeUnit::Add)
		.def("GetValue",&NativeUnit::GetValue);
}

// --- TPointEX ---------------------------------------------------------------------------

void load_dg_TPointEX(py::module m) {
	// --- TPoint<short> ------------------------------------------------------------------
	py::class_<TPoint<short>>(m, "ShortPoint")
		//.def(py::init<>())
		//.def(py::init<short &, short &>())
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("Set", &TPoint<short>::Set)
		.def("SetX", &TPoint<short>::SetX)
		.def("GetX", &TPoint<short>::GetX)
		.def("SetY", &TPoint<short>::SetY)
		.def("GetY", &TPoint<short>::GetY)
		.def("Offset", &TPoint<short>::Offset);

	// --- TPoint<NativeUnit> -------------------------------------------------------------
	py::class_<TPoint<NativeUnit>>(m, "NativeUnitPoint")
		//.def(py::init<>())
		//.def(py::init<NativeUnit &, NativeUnit &>())
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("Set", &TPoint<NativeUnit>::Set)
		.def("SetX", &TPoint<NativeUnit>::SetX)
		.def("GetX", &TPoint<NativeUnit>::GetX)
		.def("SetY", &TPoint<NativeUnit>::SetY)
		.def("GetY", &TPoint<NativeUnit>::GetY)
		.def("Offset", &TPoint<NativeUnit>::Offset);

	// --- Point --------------------------------------------------------------------------
	py::class_<Point, TPoint<short>>(m, "Point")
		//.def(py::init<>())
		//.def(py::init<TPoint<short> &>())
		.def(py::init<short, short>())
		.def("Scale", &Point::Scale)
		.def("__str__", [](const Point &p) {
			return "Point = (" + std::to_string(p.GetX()) + "," + std::to_string(p.GetY()) + ")"; });

	// --- NativePoint	-------------------------------------------------------------------
	py::class_<NativePoint, TPoint<NativeUnit>>(m, "NativePoint")
		//.def(py::init<TPoint<NativeUnit> &>())
		.def(py::init<NativeUnit &, NativeUnit &>())
		.def("Scale", &NativePoint::Scale);
}


// --- TRectEX ----------------------------------------------------------------------------
void load_dg_TRectEX(py::module m) {
	// --- TRect<short>
	py::class_<TRect<short>>(m, "ShortRect")
		//.def(py::init<>())
		//.def(py::init<TPoint<short> &, TPoint<short> &>())
		//.def(py::init<TPoint<short> &, short &, short &>())
		//.def(py::init<short &, short &, short &, short &>())
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("Set", (void (TRect<short>::*)
		(const TRect<short> &)) &TRect<short>::Set)
		.def("Set", (void (TRect<short>::*)
		(const TPoint<short> &, const TPoint<short> &)) &TRect<short>::Set)
		.def("Set", (void (TRect<short>::*)
		(const TPoint<short> &, const short &, const short &)) &TRect<short>::Set)
		.def("Set", (void (TRect<short>::*)
		(const short &, const short &, const short &, const short &)) &TRect<short>::Set)
		.def("SetLeft", &TRect<short>::SetLeft)
		.def("GetLeft", &TRect<short>::GetLeft)
		.def("SetTop", &TRect<short>::SetTop)
		.def("GetTop", &TRect<short>::GetTop)
		.def("SetRight", &TRect<short>::SetRight)
		.def("GetRight", &TRect<short>::GetRight)
		.def("SetBottom", &TRect<short>::SetBottom)
		.def("GetBottom", &TRect<short>::GetBottom)
		.def("SetLeftTop", &TRect<short>::SetLeftTop)
		.def("GetLeftTop", &TRect<short>::GetLeftTop)
		.def("SetLeftBottom", &TRect<short>::SetLeftBottom)
		.def("GetLeftBottom", &TRect<short>::GetLeftBottom)
		.def("SetRightTop", &TRect<short>::SetRightTop)
		.def("GetRightTop", &TRect<short>::GetRightTop)
		.def("SetRightBottom", &TRect<short>::SetRightBottom)
		.def("GetRightBottom", &TRect<short>::GetRightBottom)
		.def("SetCenter", &TRect<short>::SetCenter)
		.def("GetCenter", &TRect<short>::GetCenter)
		.def("SetWidth", &TRect<short>::SetWidth)
		.def("GetWidth", &TRect<short>::GetWidth)
		.def("SetHeight", &TRect<short>::SetHeight)
		.def("GetHeight", &TRect<short>::GetHeight)
		.def("SetSize", &TRect<short>::SetSize)
		.def("Move", &TRect<short>::Move)
		.def("Resize", &TRect<short>::Resize)
		.def("Inflate", &TRect<short>::Inflate)
		.def("IsEmpty", &TRect<short>::IsEmpty)
		.def("Contains", (bool (TRect<short>::*)
		(const TPoint<short> &)const) &TRect<short>::Contains)
		.def("Contains", (bool (TRect<short>::*)
		(const short &, const short &)const) &TRect<short>::Contains)
		//.def("ToGSRect", &TRect<short>::ToGSRect)
		.def("IsIntersecting", &TRect<short>::IsIntersecting)
		.def("Intersect", &TRect<short>::Intersect);
	
	// --- TRect<NativeUnit>
	py::class_<TRect<NativeUnit>>(m, "NativeUnitRect")
		//.def(py::init<>())
		//.def(py::init<TPoint<NativeUnit> &, TPoint<NativeUnit> &>())
		//.def(py::init<TPoint<NativeUnit> &, NativeUnit &, NativeUnit &>())
		//.def(py::init<NativeUnit &, NativeUnit &, NativeUnit &, NativeUnit &>())
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def("Set", (void (TRect<NativeUnit>::*)
		(const TRect<NativeUnit> &)) &TRect<NativeUnit>::Set)
		.def("Set", (void (TRect<NativeUnit>::*)
		(const TPoint<NativeUnit> &, const TPoint<NativeUnit> &)) &TRect<NativeUnit>::Set)
		.def("Set", (void (TRect<NativeUnit>::*)
		(const TPoint<NativeUnit> &, const NativeUnit &, const NativeUnit &)) &TRect<NativeUnit>::Set)
		.def("Set", (void (TRect<NativeUnit>::*)
		(const NativeUnit &, const NativeUnit &, const NativeUnit &, const NativeUnit &)) &TRect<NativeUnit>::Set)
		.def("SetLeft", &TRect<NativeUnit>::SetLeft)
		.def("GetLeft", &TRect<NativeUnit>::GetLeft)
		.def("SetTop", &TRect<NativeUnit>::SetTop)
		.def("GetTop", &TRect<NativeUnit>::GetTop)
		.def("SetRight", &TRect<NativeUnit>::SetRight)
		.def("GetRight", &TRect<NativeUnit>::GetRight)
		.def("SetBottom", &TRect<NativeUnit>::SetBottom)
		.def("GetBottom", &TRect<NativeUnit>::GetBottom)
		.def("SetLeftTop", &TRect<NativeUnit>::SetLeftTop)
		.def("GetLeftTop", &TRect<NativeUnit>::GetLeftTop)
		.def("SetLeftBottom", &TRect<NativeUnit>::SetLeftBottom)
		.def("GetLeftBottom", &TRect<NativeUnit>::GetLeftBottom)
		.def("SetRightTop", &TRect<NativeUnit>::SetRightTop)
		.def("GetRightTop", &TRect<NativeUnit>::GetRightTop)
		.def("SetRightBottom", &TRect<NativeUnit>::SetRightBottom)
		.def("GetRightBottom", &TRect<NativeUnit>::GetRightBottom)
		.def("SetCenter", &TRect<NativeUnit>::SetCenter)
		.def("GetCenter", &TRect<NativeUnit>::GetCenter)
		.def("SetWidth", &TRect<NativeUnit>::SetWidth)
		.def("GetWidth", &TRect<NativeUnit>::GetWidth)
		.def("SetHeight", &TRect<NativeUnit>::SetHeight)
		.def("GetHeight", &TRect<NativeUnit>::GetHeight)
		.def("SetSize", &TRect<NativeUnit>::SetSize)
		.def("Move", &TRect<NativeUnit>::Move)
		.def("Resize", &TRect<NativeUnit>::Resize)
		.def("Inflate", &TRect<NativeUnit>::Inflate)
		.def("IsEmpty", &TRect<NativeUnit>::IsEmpty)
		.def("Contains", (bool (TRect<NativeUnit>::*)
		(const TPoint<NativeUnit> &)const) &TRect<NativeUnit>::Contains)
		.def("Contains", (bool (TRect<NativeUnit>::*)
		(const NativeUnit &, const NativeUnit &)const) &TRect<NativeUnit>::Contains)
		//.def("ToGSRect", &TRect<NativeUnit>::ToGSRect)
		.def("IsIntersecting", &TRect<NativeUnit>::IsIntersecting)
		.def("Intersect", &TRect<NativeUnit>::Intersect);
	
	// --- NativeRect
	py::class_<NativeRect, TRect<NativeUnit>>(m, "NativeRect")
		.def(py::init<>())
		//.def(py::init<TRect<NativeUnit> &>())
		.def(py::init< NativePoint &, NativePoint &>())
		.def(py::init< NativePoint &, NativeUnit &, NativeUnit &>())
		.def(py::init<NativeUnit &, NativeUnit &, NativeUnit &, NativeUnit &>())
		.def("Scale", &NativeRect::Scale);
	
	// --- Rect
	py::class_<Rect, TRect<short>>(m, "Rect")
		//.def(py::init<>())
		//.def(py::init<TRect<short> &>())
		.def(py::init<Point &, Point &>())
		.def(py::init<Point &, short, short>())
		.def(py::init<short, short, short, short>())

		.def("Scale", &Rect::Scale)

		.def("__str__", [](const Rect &r) {
			return "Rect = (" + std::to_string(r.GetTop()) + "," + std::to_string(r.GetLeft())
				+ "," + std::to_string(r.GetRight()) + "," + std::to_string(r.GetBottom()) + ")"; });
}


// --- MousePosData -----------------------------------------------------------------------

void load_dg_MousePosData(py::module m) {
	py::class_<MousePosData>(m, "MousePosData")
		.def(py::init<>())

		.def("Retrieve", (bool (MousePosData::*)
		(void)) &MousePosData::Retrieve)
		.def("Retrieve", (bool (MousePosData::*)
		(const Panel &)) &MousePosData::Retrieve)
		.def("Retrieve", (bool (MousePosData::*)
		(const Item &)) &MousePosData::Retrieve)

		.def("RetrieveFailSafe", (void (MousePosData::*)
		(void)) &MousePosData::RetrieveFailSafe)
		.def("RetrieveFailSafe", (void (MousePosData::*)
		(const Panel &)) &MousePosData::RetrieveFailSafe)
		.def("RetrieveFailSafe", (void (MousePosData::*)
		(const Item &)) &MousePosData::RetrieveFailSafe)

		.def("GetPanel", &MousePosData::GetPanel, py::return_value_policy::reference)
		.def("GetItem", &MousePosData::GetItem, py::return_value_policy::reference)

		.def("GetRect", &MousePosData::GetRect)
		.def("GetMouseOffsetInLogicalUnits", &MousePosData::GetMouseOffsetInLogicalUnits)
		.def("GetMouseOffsetInNativeUnits", &MousePosData::GetMouseOffsetInNativeUnits)

		.def("IsCommandPressed", &MousePosData::IsCommandPressed)
		.def("IsOptionPressed", &MousePosData::IsOptionPressed)
		.def("IsShiftPressed", &MousePosData::IsShiftPressed)

		.def("IsLeftButtonPressed", &MousePosData::IsLeftButtonPressed)
		.def("IsRightButtonPressed", &MousePosData::IsRightButtonPressed)
		.def("IsWheelButtonPressed", &MousePosData::IsWheelButtonPressed);
}


// --- Definitions ------------------------------------------------------------------------

//void load_dg_DragDrop(py::module m) {
//	py::enum_<DragDrop::Effect>(m, "Effect")
//		.value("Reject", DragDrop::Effect::Reject)
//		.value("Accept", DragDrop::Effect::Accept)
//		.value("Copy", DragDrop::Effect::Copy)
//		.value("Move", DragDrop::Effect::Move)
//		.value("Link", DragDrop::Effect::Link)
//		.value("Delete", DragDrop::Effect::Delete)
//		.export_values();
//
//	py::enum_<DragDrop::Feedback>(m, "Feedback")
//		.value("AcceptSelAndIns", DragDrop::Feedback::AcceptSelAndIns)
//		.value("RejectSelection", DragDrop::Feedback::RejectSelection)
//		.value("RejectInsertion", DragDrop::Feedback::RejectInsertion)
//		.value("RejectSelAndIns", DragDrop::Feedback::RejectSelAndIns)
//		.export_values();
//
//	py::enum_<DragDrop::RelativePos>(m, "RelativePos")
//		.value("InsertOn", DragDrop::RelativePos::InsertOn)
//		.value("InsertUnder", DragDrop::RelativePos::InsertUnder)
//		.value("InsertAbove", DragDrop::RelativePos::InsertAbove)
//		.export_values();
//
//	py::enum_<DragDrop::Scope>(m, "Scope")
//		.value("Item", DragDrop::Scope::Item)
//		.value("Dialog", DragDrop::Scope::Dialog)
//		.value("Module", DragDrop::Scope::Module)
//		.value("Application", DragDrop::Scope::Application)
//		.value("System", DragDrop::Scope::System)
//		.export_values();
//}


// --- ItemDragDropData -------------------------------------------------------------------

//void load_dg_ItemDragDropData(py::module m) {
//	py::class_<ItemDragDropData>(m, "ItemDragDropData")
//		.def("HasDataFormat", &ItemDragDropData::HasDataFormat)
//		.def("GetDataSize", &ItemDragDropData::GetDataSize)
//		.def("GetData", &ItemDragDropData::GetData)
//		.def("GetFileData", &ItemDragDropData::GetFileData)
//
//		.def("GetText", &ItemDragDropData::GetText)
//
//		.def("GetLocationCount", &ItemDragDropData::GetLocationCount)
//		.def("GetLocation", &ItemDragDropData::GetLocation)
//
//		.def("GetSourceItem", &ItemDragDropData::GetSourceItem, py::return_value_policy::reference)
//		.def("GetListBoxSource", &ItemDragDropData::GetListBoxSource, py::return_value_policy::reference)
//		.def("GetListViewSource", &ItemDragDropData::GetListViewSource, py::return_value_policy::reference)
//		.def("GetTreeViewSource", &ItemDragDropData::GetTreeViewSource, py::return_value_policy::reference)
//
//		.def("GetItemCount", &ItemDragDropData::GetItemCount)
//		.def("GetTreeViewItem", &ItemDragDropData::GetTreeViewItem)
//		.def("GetListBoxItem", &ItemDragDropData::GetListBoxItem)
//		.def("GetListViewItem", &ItemDragDropData::GetListViewItem);
//}


// --- DragSourceEventProperty ------------------------------------------------------------

//void load_dg_DragSourceEventProperty(py::module m) {
//	py::class_<DragSourceEventProperty>(m, "DragSourceEventProperty")
//		.def(py::init<>())
//
//		.def("Init", &DragSourceEventProperty::Init)
//
//		.def("SetData", &DragSourceEventProperty::SetData)
//		.def("SetDelayedData", &DragSourceEventProperty::SetDelayedData)
//		.def("SetLocationData", &DragSourceEventProperty::SetLocationData)
//		.def("ModifyBaseFormat", &DragSourceEventProperty::ModifyBaseFormat)
//
//		.def("GetSourcePosition", &DragSourceEventProperty::GetSourcePosition)
//		.def("GetRequestedDragFormat", &DragSourceEventProperty::GetRequestedDragFormat)
//		.def("GetFolderPath", &DragSourceEventProperty::GetFolderPath, py::return_value_policy::reference)
//		.def("SetSourceFeedback", &DragSourceEventProperty::SetSourceFeedback);
//}


// --- DropTargetEventProperty ------------------------------------------------------------

//void load_dg_DropTargetEventProperty(py::module m) {
//	py::class_<DropTargetEventProperty, ItemDragDropData>(m, "DropTargetEventProperty")
//		.def("GetTargetPosition", &DropTargetEventProperty::GetTargetPosition);
//}


// --- CompoundItemObserver ---------------------------------------------------------------

//void load_dg_CompoundItemObserver(py::module m) {
//	py::class_<CompoundItemObserver>(m, "CompoundItemObserver")
//		.def("AttachToAllItems", &CompoundItemObserver::AttachToAllItems)
//		.def("DetachFromAllItems", &CompoundItemObserver::DetachFromAllItems);
//}


// ---- SetAndRestoreEditUpdateDelay ------------------------------------------------------

//void load_dg_SetAndRestoreEditUpdateDelay(py::module m) {
//	py::class_<SetAndRestoreEditUpdateDelay>(m, "SetAndRestoreEditUpdateDelay");
//}

