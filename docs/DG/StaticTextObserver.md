# Class StaticTextObserver

## Inherit

* ItemObserver

## Methods
```
__init__(self,StaticText,iTerm.ACExport) -> None
```

## Events

* StaticTextClicked = (StaticTextClickEvent ev) -> None
* StaticTextDoubleClicked = (StaticTextDoubleClickEvent ev) -> None
* StaticTextMouseMoved = (StaticTextMouseMoveEvent ev) -> bool

## Class StaticTextClickEvent

### Inherit

* ItemDoubleClickEvent

### Methods

* GetSource(self) -> StaticText

## Class StaticTextMouseMoveEvent

### Inherit

* ItemMouseMoveEvent
* StaticItemEventProperty

### Methods

* GetSource(self) -> StaticText

## Class StaticTextDoubleClickEvent

### Inherit

* ItemDoubleClickEvent

### Methods

* GetSource(self) -> StaticText
