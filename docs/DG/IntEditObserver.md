# Class IntEditObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self,DGLib.IntEdit) -> None
```

## Events

* IntEditChanged = (IntEditChangeEvent ev) -> None

## Class IntEditChangeEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.IntEdit
* GetPreviousValue(self) -> int
* WasRelativeInput(self) -> bool
