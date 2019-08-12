# Class ScrollBarObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self,ScrollBar) -> None
```

## Events

* ScrollBarChanged = (ScrollBarChangeEvent ev) -> None
* ScrollBarTrackEntered = (ScrollBarTrackEvent ev) -> None
* ScrollBarTracked = (ScrollBarTrackEvent ev) -> None
* ScrollBarTrackExited = (ScrollBarTrackEvent ev) -> None

## Class ScrollBarChangeEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetSource(self) -> ScrollBar
* GetPreviousValue(self) -> Int32

## Class ScrollBarTrackEvent

### Inherit

* [ItemTrackEvent](ItemObserver.md)

### Methods

* GetSource(self) -> ScrollBar
* IsLineUp(self) -> bool
* IsLineLeft(self) -> bool
* IsLineDown(self) -> bool
* IsLineRight(self) -> bool
* IsPageUp(self) -> bool
* IsPageLeft(self) -> bool
* IsPageDown(self) -> bool
* IsPageRight(self) -> bool
* IsTop(self) -> bool
* IsLeft(self) -> bool
* IsBottom(self) -> bool
* IsRight(self) -> bool
* IsThumbTrack(self) -> bool