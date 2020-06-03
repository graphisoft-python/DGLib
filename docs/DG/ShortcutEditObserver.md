# Class ShortcutEditObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self,DGLib.ShortcutEdit) -> None
```

## Events

* ShortcutHit = (ShortcutHitEvent ev) -> None

## Class ShortcutHitEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetKey(self) -> DG.Key.Code
* GetModifierFlags(self) -> int
* GetSource(self) -> DGLib.ShortcutEdit
