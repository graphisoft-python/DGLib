# Class RealEditObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self,DGLib.RealEdit) -> None
```

## Events

* RealEditChanged = (RealEditChangeEvent ev) -> None

## Class RealEditChangeEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.RealEdit
* GetPreviousValue(self) -> float
* WasRelativeInput(self) -> bool
