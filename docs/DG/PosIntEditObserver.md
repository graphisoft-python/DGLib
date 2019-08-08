# Class PosIntEditObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self,PosIntEdit) -> None
```

## Events

* PosIntEditChanged = (PosIntEditChangeEvent ev) -> None

## Class PosIntEditChangeEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> PosIntEdit
* GetPreviousValue(self) -> UInt32
* WasRelativeInput(self) -> bool
