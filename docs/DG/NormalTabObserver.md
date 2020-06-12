# Class NormalTabObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self, DGLib.NormalTab) -> None
```

## Events

* NormalTabChanged = (NormalTabChangeEvent ev) -> None
* NormalTabClicked = (NormalTabClickEvent ev, bool* denyChange) -> None

## Class NormalTabChangeEvent

### Inherit

* [ItemObserver](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.NormalTab
* GetPreviousItem(self) -> int

## Class NormalTabClickEvent

### Inherit

* [ItemObserver](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.NormalTab
* GetRequestedItem(self) -> int
