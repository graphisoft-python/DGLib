# Class RealEditObserver

## Inherit

* ItemObserver

## Methods
```
__init__(self,RealEdit,iTerm.ACExport) -> None
```

## Events

* RealEditChanged = (RealEditChangeEvent ev) -> None

## Class RealEditChangeEvent

### Inherit

* ItemChangeEvent

### Methods

* GetSource(self) -> RealEdit
* GetPreviousValue(self) -> double
* WasRelativeInput(self) -> bool
