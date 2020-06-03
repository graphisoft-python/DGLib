# Class StaticTextObserver

## Inherit

* [](ItemObserver.md)

## Methods
```
__init__(self, DGLib.StaticText) -> None
```

## Events

* StaticTextClicked = (StaticTextClickEvent ev) -> None
* StaticTextDoubleClicked = (StaticTextDoubleClickEvent ev) -> None
* StaticTextMouseMoved = (StaticTextMouseMoveEvent ev) -> bool

## Class StaticTextClickEvent

### Inherit

* [ItemDoubleClickEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.StaticText

## Class StaticTextMouseMoveEvent

### Inherit

* [ItemMouseMoveEvent](ItemObserver.md)
* [StaticItemEventProperty](StaticItemEventProperty.md)

### Methods

* GetSource(self) -> DGLib.StaticText

## Class StaticTextDoubleClickEvent

### Inherit

* [ItemDoubleClickEvent](ItemObserver.md)

### Methods

* GetSource(self) -> DGLib.StaticText
