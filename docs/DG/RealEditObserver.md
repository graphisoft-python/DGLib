# Class RealEditObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self,RealEdit) -> None
```

## Events

* RealEditChanged = (RealEditChangeEvent ev) -> None

## Class RealEditChangeEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> RealEdit
* GetPreviousValue(self) -> double
* WasRelativeInput(self) -> bool
