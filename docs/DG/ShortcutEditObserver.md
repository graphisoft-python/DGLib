# Class ShortcutEditObserver

## Inherit

* [ItemObserver](ItemObserver.md)

## Methods
```
__init__(self,ShortcutEdit) -> None
```

## Events

* ShortcutHit = (ShortcutHitEvent ev) -> None

## Class ShortcutHitEvent

### Inherit

* [ItemChangeEvent](ItemObserver.md)

### Methods

* GetKey(self) -> DG.Key.Code
* GetModifierFlags(self) -> ULong
* GetSource(self) -> ShortcutEdit
