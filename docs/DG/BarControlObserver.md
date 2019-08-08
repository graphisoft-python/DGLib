# Class BarControlObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods

```
__init__(self,BarControl) -> None
```

## Events

* BarControlChanged = (BarControlChangeEvent ev) -> None
* BarControlTrackEntered = (BarControlTrackEvent ev) -> None
* BarControlTracked = (BarControlTrackEvent ev) -> None
* BarControlTrackExited = (BarControlTrackEvent ev) -> None

## Class BarControlChangeEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> BarControl
* GetPreviousValue(self) -> Int32

## Class BarControlTrackEvent

### Inherit

* [ItemTrackEvent](ItemObserver.md)

### Methods

* GetSource(self) -> BarControl
