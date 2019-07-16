# Class Key.Code

## Inherit

* object

## Enum

### Modifier

* NoModifier
* Command
* Option
* Shift
* Ctrl

### Special

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

## Methods
```
__init__(self) -> None
__init__(self,Special) -> None
__init__(self,unicode) -> None
IsSpecial(self) -> bool
GetChar(self) -> unicode
GetSpecialKey(self,Alignment) -> Special
GetValue(self) -> ushort
__eq__(self,Code) -> bool
__ne__(self,Code) -> bool
Read(self,GS.IChannel) -> GSErrCode
Write(self,GS.OChannel) -> GSErrCode
```
