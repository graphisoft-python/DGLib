# Class IntEditObserver

## Inherit

* ItemObserver

## Methods
```
__init__(self,IntEdit,iTerm.ACExport) -> None
```

## Events

* IntEditChanged = (IntEditChangeEvent ev) -> None

## Class IntEditChangeEvent

### Inherit

* ItemChangeEvent

### Methods

* GetSource(self) -> IntEdit
* GetPreviousValue(self) -> Int32
* WasRelativeInput(self) -> bool
