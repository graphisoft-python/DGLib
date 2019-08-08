# Class IntEditObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self,IntEdit) -> None
```

## Events

* IntEditChanged = (IntEditChangeEvent ev) -> None

## Class IntEditChangeEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> IntEdit
* GetPreviousValue(self) -> Int32
* WasRelativeInput(self) -> bool
