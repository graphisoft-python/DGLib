# Class ShortcutEditObserver

## Inherit

* ItemObserver

## Methods
```
__init__(self,ShortcutEdit,iTerm.ACExport) -> None
```

## Events

* ShortcutHit = (ShortcutHitEvent ev) -> None

## Class ShortcutHitEvent

### Inherit

* ItemChangeEvent

### Methods

* GetKey(self) -> DG.Key.Code
* GetModifierFlags(self) -> ULong
* GetSource(self) -> ShortcutEdit
