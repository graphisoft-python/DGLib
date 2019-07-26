# Class PosIntEditObserver

## Inherit

* ItemObserver

## Methods
```
__init__(self,PosIntEdit,iTerm.ACExport) -> None
```

## Events

* PosIntEditChanged = (PosIntEditChangeEvent ev) -> None

## Class PosIntEditChangeEvent

### Inherit

* ItemChangeEvent

### Methods

* GetSource(self) -> PosIntEdit
* GetPreviousValue(self) -> UInt32
* WasRelativeInput(self) -> bool
