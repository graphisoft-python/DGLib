# Class BarControlObserver

## Inherit

* ItemObserver

## Methods

```
__init__(self,BarControl,iTerm.ACExport) -> None
```

## Events

* BarControlChanged = (BarControlChangeEvent ev) -> None
* BarControlTrackEntered = (BarControlTrackEvent ev) -> None
* BarControlTracked = (BarControlTrackEvent ev) -> None
* BarControlTrackExited = (BarControlTrackEvent ev) -> None

## Class BarControlChangeEvent

### Inherit

* ItemChangeEvent

### Methods

* GetSource(self) -> BarControl
* GetPreviousValue(self) -> Int32

## Class BarControlTrackEvent

### Inherit

* ItemTrackEvent

### Methods

* GetSource(self) -> BarControl
