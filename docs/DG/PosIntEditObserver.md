# Class PosIntEditObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self, DGLib.PosIntEdit) -> None
```

## Events

* PosIntEditChanged = (PosIntEditChangeEvent ev) -> None

## Class PosIntEditChangeEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.PosIntEdit
* GetPreviousValue(self) -> int
* WasRelativeInput(self) -> bool
