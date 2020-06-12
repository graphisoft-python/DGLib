# Class ButtonItemObserver

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

* GetSource(self) -> DGLib.NormalTa
* GetPreviousItem(self) -> int

## Class NormalTabClickEvent

### Inherit

* [ItemObserver](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.NormalTa
* GetRequestedItem(self) -> int
