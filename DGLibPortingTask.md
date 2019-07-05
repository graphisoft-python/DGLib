# Namespace DG::Key

## Special  ( DGUtility.h )

* Back
* Tab
* Enter
* Return
* Escape
* Left
* Right
* Up
* Down
* Insert
* Delete
* Home
* End
* PageUp
* PageDown
* F1
* F2
* F3
* F4
* F5
* F6
* F7
* F8
* F9
* F10
* F11
* F12
* F13
* F14
* F15
* Help

## Modifier ( DGUtility.h )

* NoModifier
* Command
* Option
* Shift
* Ctrl

## Code ( DGUtility.h )

* Code ()
* Code (Special code)
* Code (char code)
* IsSpecial
* GetChar
* GetSpecialKey
* GetValue
* operator==
* operator!=

# Namespace DG::Font

## Size (DGItemProperty.h)

* Large
* Small
* ExtraSmall
* DefaultSize

## Style (DGItemProperty.h)

* Plain
* Bold
* Italic
* Underline
* Shadow
* Outline
* DefaultStyle

# Namespace DG

## CharRange ( DGUtility.h )

* CharRange ()
* CharRange (const Int32& bound1, const Int32& bound2)
* Set
* SetWithLength
* GetMin
* GetMax
* GetLength
* operator==
* operator!=
* IsOverlapping
* IsInside
* IsEmpty
* Union
* Intersection
* Unify
* Intersect

## TPoint< short > -> ShortPoint  ( DGUtility.h )

* operator==
* operator!=
* Set
* SetX
* GetX
* SetY
* GetY
* Offset

## NativeUnit ( DGUtility.h )

* NativeUnit ()
* NativeUnit (short value)
* NativeUnit (short value, double scale)
* operator==
* operator!=
* operator>
* operator>=
* operator<
* operator<=
* operator=
* operator+=
* operator-=
* operator+
* operator-
* operator/
* operator*
* operator-
* Add
* GetValue

## TPoint< NativeUnit > -> NativeUnitPoint ( DGUtility.h )

* operator==
* operator!=
* Set
* SetX
* GetX
* SetY
* GetY
* Offset

## TRect< NativeUnit > -> NativeUnitRect ( DGUtility.h )

* operator==
* operator!=
* Set (const TRect< NativeUnit >& sourceRect)
* Set (const TPoint< NativeUnit >& pt1, const TPoint< NativeUnit >& pt2)
* Set (const TPoint< NativeUnit >& pt, const NativeUnit& width, const NativeUnit& height)
* Set (const NativeUnit& left, const NativeUnit& top, const NativeUnit& right, const NativeUnit& bottom)
* SetLeft
* GetLeft
* SetTop
* GetTop
* SetRight
* GetRight
* SetBottom
* GetBottom
* SetLeftTop
* GetLeftTop
* SetLeftBottom
* GetLeftBottom
* SetRightTop
* GetRightTop
* SetRightBottom
* GetRightBottom
* SetCenter
* GetCenter
* SetWidth
* GetWidth
* SetHeight
* GetHeight
* SetSize
* Move
* Resize
* Inflate
* IsEmpty
* Contains
* Contains
* IsIntersecting
* Intersect

## NativePoint ( DGUtility.h )

* NativePoint (const NativeUnit& x, const NativeUnit& y)
* Scale

## Point ( DGUtility.h )

* Point (short x, short y)
* Scale

## NativeRect ( DGUtility.h )

* NativeRect ()
* NativeRect (const NativePoint& pt1, const NativePoint& pt2)
* NativeRect (const NativePoint& pt, const NativeUnit& width, const NativeUnit& height)
* NativeRect (const NativeUnit& left, const NativeUnit& top, const NativeUnit& right, const NativeUnit& bottom)
* Scale

## Rect ( DGUtility.h )

* Rect (const Point& pt1, const Point& pt2)
* Rect (const Point& pt, const short width, short height)
* Rect (short left, short top, short right, short bottom)
* Scale

## ItemBase ( Item.h )

* IsValid
* GetPanel
* GetPanelId
* GetId

## Item ( Item.h )

* operator==
* operator!=
* Show
* Hide
* SetVisibility
* IsVisible
* Flash
* Enable
* Disable
* SetStatus
* IsEnabled
* Move
* Resize
* MoveAndResize
* SetPosition (const Point& pt)
* SetPosition (short hPos, short vPos)
* SetRect
* SetSize
* SetWidth
* SetHeight
* GetPosition
* GetRect
* GetWidth
* GetHeight
* GetNativeRectInScreenSpace
* Invalidate
* Redraw
* ResetModified
* IsModified
* InvokeDragDrop
* GetResolutionFactor

## Panel ( Panel.h )

* IsValid
* IsExist
* GetId
* GetItemCount
* GetItem
* GetWidth
* GetHeight
* ClearFocus
* ShowItems
* HideItems
* SetItemVisibility
* MaskItemsVisibility
* EnableItems
* DisableItems
* SetItemStatus
* MoveItems
* RedrawItems
* RegisterHotKey (Key::Special keyCode)
* RegisterHotKey (Key::Special keyCode, Key::Modifier mod1)
* RegisterHotKey (Key::Special keyCode, Key::Modifier mod1,Key::Modifier mod2)
* RegisterHotKey (Key::Special keyCode, Key::Modifier mod1,Key::Modifier mod2, Key::Modifier mod3)
* RegisterHotKey (short keyCode)
* RegisterHotKey (short keyCode, Key::Modifier mod1)
* RegisterHotKey (short keyCode, Key::Modifier mod1,Key::Modifier mod2)
* RegisterHotKey (short keyCode, Key::Modifier mod1,Key::Modifier mod2, Key::Modifier mod3)
* UnregisterHotKey
* EnableHotKeys
* DisableHotKeys
* EnableDragAndDropEvent
* EnableInputFiltering
* DisableInputFiltering
* GetScaleFactor
* IsDGDialog
* IsSystemDialog
* IsTabPage

## Dialog.DialogType (DGDialog.h)

* Modal
* Modeless
* Palette

## Dialog.GrowType (DGDialog.h)

* NoGrow
* HGrow
* VGrow
* HVGrow

## Dialog.CloseType (DGDialog.h)

* NoClose
* Close

## Dialog.MinimizeType (DGDialog.h)

* NoMinimize
* Minimize

## Dialog.MaximizeType (DGDialog.h)

* NoMaximize
* Maximize

## Dialog.CaptionType (DGDialog.h)

* TopCaption
* LeftCaption
* NoCaption

## Dialog.FrameType (DGDialog.h)

* NormalFrame
* ThickFrame
* NoFrame

## Dialog.FixPoint (DGDialog.h)

* CenterPoint
* TopLeft
* CenterLeft
* BottomLeft
* BottomCenter
* BottomRight
* CenterRight
* TopRight
* TopCenter

## Dialog.GrowBoxForm (DGDialog.h)

* Triangle
* Square

## Dialog.SpecialFeatures (DGDialog.h)

* NothingSpecial
* NoUpdate
* FrameDialog

## Dialog (DGDialog.h)

* GetDialogType
* IsDGDialog
* Center
* Move (short hDisp, short vDisp)
* Move (const DG::NativeUnit& hDisp, const DG::NativeUnit& vDisp)
* Resize
* SetGrowType
* GetGrowType
* GetOriginalClientWidth
* GetOriginalClientHeight
* SetMinClientSize
* SetMinClientWidth
* SetMinClientHeight
* GetMinClientWidth
* GetMinClientHeight
* SetClientPosition
* SetClientPosition
* SetClientRect (const NativeRect& rect)
* SetClientRect (const NativeRect& rect, FixPoint fixPoint)
* SetClientRect (const NativeRect& rect, FixPoint fixPoint, bool keepOld)
* SetClientSize (short width, short height, FixPoint fixPoint)
* SetClientSize (short width, short height, FixPoint fixPoint, bool keepOld)
* SetClientWidth (short width, FixPoint fixPoint)
* SetClientWidth (short width, FixPoint fixPoint, bool keepOld)
* SetClientHeight (short height, FixPoint fixPoint)
* SetClientHeight (short height, FixPoint fixPoint, bool keepOld)
* GetClientPosition
* GetClientRect
* GetClientWidth
* GetClientHeight
* GetOriginalFrameWidth
* GetOriginalFrameHeight
* SetMinFrameSize
* SetMinFrameWidth
* SetMinFrameHeight
* GetMinFrameWidth
* GetMinFrameHeight
* SetFramePosition
* SetFramePosition
* SetFrameRect (const NativeRect& rect, FixPoint fixPoint)
* SetFrameRect (const NativeRect& rect, FixPoint fixPoint, bool keepOld)
* SetFrameSize (const NativeUnit& width, const NativeUnit& height, FixPoint fixPoint)
* SetFrameSize (const NativeUnit& width, const NativeUnit& height, FixPoint fixPoint, bool keepOld)
* SetFrameWidth (const NativeUnit& width, FixPoint fixPoint)
* SetFrameWidth (const NativeUnit& width, FixPoint fixPoint, bool keepOld)
* SetFrameHeight (const NativeUnit& height, FixPoint fixPoint)
* SetFrameHeight (const NativeUnit& height, FixPoint fixPoint, bool keepOld)
* GetFramePosition
* GetFrameRect
* GetFrameWidth
* GetFrameHeight
* BeginMoveResizeItems
* EndMoveResizeItems
* EnableIdleEvent
* EnableNormalUpdate
* DisableNormalUpdate
* SetPopupStyle
* HasPopupStyle
* EnableGrowBox
* DisableGrowBox
* IsGrowBoxEnabled
* SetGrowBoxSize
* GetGrowBoxSize
* SetGrowBoxForm
* GetGrowBoxForm
* RegisterDragAndDrop
* RevokeDragAndDrop
* EnableDraw
* DisableDraw
* Redraw
* SetCursorPosition
* KeepInScreen
* HasChangedDialogItems
* ResetDialogItemChanges

## ModalDialog.ModalResponse (DGDialog.h)

* Accept
* Cancel

## ModalDialog (DGDialog.h)

* ModalDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType)
* ModalDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CaptionType captionType)
* ModalDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CaptionType captionType,FrameType frameType)
* Invoke
* Abort
* PostCloseRequest
* GetNextModalDialog
* GetPrevModalDialog

## ModelessBase.DialogStatus (DGDialog.h)

* Normal
* Enabled
* Disabled
* Edited

## ModelessBase (DGDialog.h)

* BeginEventProcessing
* EndEventProcessing
* SendCloseRequest
* BringToFront
* SendToBack
* Show ()
* Show (short refDialId)
* Hide
* SetVisibility
* IsVisible
* Activate
* IsActive
* SetStatus
* GetStatus

## ModelessDialog.DialogState (DGDialog.h)

* Maximized
* Minimized
* Restored

## ModelessDialog.DockState (DGDialog.h)

* Docked
* Undocked

## ModelessDialog (DGDialog.h)

* ModelessDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid)
* ModelessDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType)
* ModelessDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType)
* ModelessDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType,MinimizeType minimizeType)
* ModelessDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType,MinimizeType minimizeType, MaximizeType maximizeType)
* ModelessDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType,MinimizeType minimizeType, MaximizeType maximizeType,CaptionType captionType)
* ModelessDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType,MinimizeType minimizeType, MaximizeType maximizeType,CaptionType captionType, FrameType frameType)
* ModelessDialog (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType,MinimizeType minimizeType, MaximizeType maximizeType,CaptionType captionType, FrameType frameType, SpecialFeatures specialFeatures)
* SendBehind
* GetNextModelessDialog
* GetPrevModelessDialog
* GetNextVisibleModelessDialog
* GetPrevVisibleModelessDialog
* GetRestoredClientPosition
* GetRestoredClientWidth
* GetRestoredClientHeight
* GetRestoredFramePosition
* GetRestoredFrameRect
* GetRestoredFrameWidth
* GetRestoredFrameHeight
* Maximize ()
* Maximize (bool beforeDock)
* Minimize
* Restore
* SetState (DialogState state)
* SetState (DialogState state, bool beforeDock)
* IsMaximizedState
* IsMinimizedState
* IsRestoredState
* GetState
* Dock
* Undock
* IsDocked
* SetDockState
* GetDockState

## Palette (DGDialog.h)

* Palette (const DG::NativePoint& position, short width, short height, const GS::Guid& guid)
* Palette (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType)
* Palette (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType)
* Palette (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType,CaptionType captionType)
* Palette (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType,CaptionType captionType, FrameType frameType)
* Palette (const DG::NativePoint& position, short width, short height, const GS::Guid& guid, GrowType growType, CloseType closeType,CaptionType captionType, FrameType frameType, SpecialFeatures specialFeatures)
* SendBehind
* GetNextPalette
* GetPrevPalette
* GetNextVisiblePalette
* GetPrevVisiblePalette
* DisableDock
* Dock
* UnDock
* IsDocked
* GetCaptionType

## ItemFontProperty (DGItemProperty.h)

* SetFontSize
* GetFontSize
* SetFontStyle
* GetFontStyle

## FocusableProperty (DGItemProperty.h)

* SetFocus
* IsFocused

## ItemVariousProperty (DGItemProperty.h)

* SetVariousState
* GetVariousState

## ItemTextLengthLimitProperty (DGItemProperty.h)

* SetMaxTextLength
* GetMaxTextLength

## EditControl.FrameType (DGEditControl.h)

* Frame
* NoFrame

## EditControl.UpdateType (DGEditControl.h)

* Update
* NoUpdate
* NoDelay

## EditControl.ReadOnlyType (DGEditControl.h)

* Editable
* ReadOnly

## EditControl (DGEditControl.h)


## PosIntEdit.AbsRelType (DGEditControl.h)

* Absolute
* Relative

## PosIntEdit (DGEditControl.h)

* PosIntEdit(const Panel& panel, const Rect& rect)
* PosIntEdit(const Panel& panel, const Rect& rect, FrameType frame)
* PosIntEdit(const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel)
* PosIntEdit(const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update)
* PosIntEdit(const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update, ReadOnlyType readOnly)
* SetMin
* SetMax
* SetValue
* GetMin
* GetMax
* GetValue

## IntEdit.AbsRelType (DGEditControl.h)

* Absolute
* Relative

## IntEdit (DGEditControl.h)

* IntEdit (const Panel& panel, const Rect& rect)
* IntEdit (const Panel& panel, const Rect& rect, FrameType frame)
* IntEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel)
* IntEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update)
* IntEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update, ReadOnlyType readOnly)
* SetMin
* SetMax
* SetValue
* GetMin
* GetMax
* GetValue

## RealEdit.AbsRelType (DGEditControl.h)

* Absolute
* Relative

## RealEdit (DGEditControl.h)

* RealEdit (const Panel& panel, const Rect& rect)
* RealEdit (const Panel& panel, const Rect& rect, FrameType frame)
* RealEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel)
* RealEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update)
* RealEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update, ReadOnlyType readOnly)
* SetMin
* SetMax
* SetValue
* GetMin
* GetMax
* GetValue

## LengthEdit.ChangeFontType (DGEditControl.h)

* ChangeFont
* NoChangeFont

## LengthEdit (DGEditControl.h)

* LengthEdit (const Panel& panel, const Rect& rect)
* LengthEdit (const Panel& panel, const Rect& rect, ChangeFontType chgFont)
* LengthEdit (const Panel& panel, const Rect& rect, ChangeFontType chgFont,FrameType frame)
* LengthEdit (const Panel& panel, const Rect& rect, ChangeFontType chgFont,FrameType frame, AbsRelType absRel)
* LengthEdit (const Panel& panel, const Rect& rect, ChangeFontType chgFont,FrameType frame, AbsRelType absRel, UpdateType update)
* LengthEdit (const Panel& panel, const Rect& rect, ChangeFontType chgFont,FrameType frame, AbsRelType absRel, UpdateType update,ReadOnlyType readOnly)

## AreaEdit (DGEditControl.h)

* AreaEdit (const Panel& panel, const Rect& rect)
* AreaEdit (const Panel& panel, const Rect& rect, FrameType frame)
* AreaEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel)
* AreaEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update)
* AreaEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update, ReadOnlyType readOnly)

## VolumeEdit  (DGEditControl.h)

* VolumeEdit (const Panel& panel, const Rect& rect)
* VolumeEdit (const Panel& panel, const Rect& rect, FrameType frame)
* VolumeEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel)
* VolumeEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update)
* VolumeEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update, ReadOnlyType readOnly)

## AngleEdit (DGEditControl.h)

* AngleEdit (const Panel& panel, const Rect& rect)
* AngleEdit (const Panel& panel, const Rect& rect, FrameType frame)
* AngleEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel)
* AngleEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update)
* AngleEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update, ReadOnlyType readOnly)

## PolarAngleEdit (DGEditControl.h)

* PolarAngleEdit (const Panel& panel, const Rect& rect)
* PolarAngleEdit (const Panel& panel, const Rect& rect, FrameType frame)
* PolarAngleEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel)
* PolarAngleEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update)
* PolarAngleEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update, ReadOnlyType readOnly)

## MMPointEdit (DGEditControl.h)

* MMPointEdit (const Panel& panel, const Rect& rect)
* MMPointEdit (const Panel& panel, const Rect& rect, FrameType frame)
* MMPointEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel)
* MMPointEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update)
* MMPointEdit (const Panel& panel, const Rect& rect, FrameType frame,AbsRelType absRel, UpdateType update, ReadOnlyType readOnly)

## TextEditBase (DGEditControl.h)

* SetSelection
* GetSelection

## TextEdit (DGEditControl.h)

* TextEdit (const Panel& panel, const Rect& rect)
* TextEdit (const Panel& panel, const Rect& rect, short lengthLimit)
* TextEdit (const Panel& panel, const Rect& rect, short lengthLimit,FrameType frame)
* TextEdit (const Panel& panel, const Rect& rect, short lengthLimit,FrameType frame, UpdateType update)
* TextEdit (const Panel& panel, const Rect& rect, short lengthLimit,FrameType frame, UpdateType update, ReadOnlyType readOnly)

## PasswordEdit (DGEditControl.h)

* PasswordEdit (const Panel& panel, const Rect& rect)
* PasswordEdit (const Panel& panel, const Rect& rect, short lengthLimit)
* PasswordEdit (const Panel& panel, const Rect& rect, short lengthLimit,FrameType frame)
* PasswordEdit (const Panel& panel, const Rect& rect, short lengthLimit,FrameType frame, UpdateType update)
* PasswordEdit (const Panel& panel, const Rect& rect, short lengthLimit,FrameType frame, UpdateType update, ReadOnlyType readOnly)

## ShortcutEdit (DGEditControl.h)

* ShortcutEdit (const Panel& panel, const Rect& rect)
* ShortcutEdit (const Panel& panel, const Rect& rect, short lengthLimit)
* ShortcutEdit (const Panel& panel, const Rect& rect, short lengthLimit,FrameType frame)
* ShortcutEdit (const Panel& panel, const Rect& rect, short lengthLimit,FrameType frame, UpdateType update)

## MultiLineEdit.ScrollType (DGEditControl.h)

* NoScroll
* HScroll
* VScroll
* HVScroll

## MultiLineEdit (DGEditControl.h)

* MultiLineEdit (const Panel& panel, const Rect& rect)
* MultiLineEdit (const Panel& panel, const Rect& rect, ScrollType scroll)
* MultiLineEdit (const Panel& panel, const Rect& rect, ScrollType scroll,FrameType frame)
* MultiLineEdit (const Panel& panel, const Rect& rect, ScrollType scroll,FrameType frame, UpdateType update)
* MultiLineEdit (const Panel& panel, const Rect& rect, ScrollType scroll,FrameType frame, UpdateType update, ReadOnlyType readOnly)
