# Plank Keymap v3.1

This keymap was designed for programming.

## Flashing

```
make planck/rev6:tk:flash
```

## Design

### Layers

The function of each key is determined by the active keyboard layer. All layers are activated by holding down their corresponding layer-keys. 

Currently there are 7 distinct layers which can be accessed from 3 layer-keys. Those layer-keys include: `LOWER`, `RAISE`, and `FN`. A helpful mnemonic is that `LOWER` is on the **l**eft side, and `RAISE` is on the **r**ight side. The `FN` key occurs on both sides.

By default, the keyboard is in the `BASE` layer. Holding down `FN` activates the `F` layer. Tapping either `LOWER` or `RAISE` activates the `L1` and `R1` layers respectively while the layer-key is held down. Double-tapping either `LOWER` or `RAISE` activates the `L2` and `R2` layers respectively while the layer-key is held down. Holding `LOWER` and `RAISE` down together activates the `ADJUST` layer.

### Considerations

Regarding design decisions, there are two important considerations:
1. Whether the desired key is on the same side as the layer-key.
2. Whether the layer-key must be tapped once or twice to activate the desired layer.

If the desired key is on the same side as the layer-key, it can be accessed with one hand - otherwise both hands must be on the keyboard. This is a useful quality for frequently accessed keys (e.g. numbers) and keys that are accessed repeatably or for long durations (e.g. arrows, mouse movement).

If the layer-key must be tapped once rather than twice, it is easier to access quickly and repeatable - otherwise there is a slightly longer delay before the desired key can be typed. This is a useful quality for frequently accessed keys (e.g. numbers, symbols, arrows).

## Keymap

### `BASE`

```
|-----------------------------------------------------------------------------------------------|
| Rotary|   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |BkSpace|
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|  Tab  |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   | Enter |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|  Esc  |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |   '   |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
| HYPER |D1 Play|D2 Play| CtlSh | LOWER1| Super | Space | RAISE1|  Del  |  Meta |  Caps | HYPER |
|-----------------------------------------------------------------------------------------------|
```

// TODO

### `F`

// TODO

### `L1`

```
|-----------------------------------------------------------------------------------------------|
|       |   1   |   2   |   3   |   $   |   *   |   /   |       |       |       |       |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |   4   |   5   |   6   |   .   |   +   |   =   |   [   |   ]   |   {   |   }   |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |   7   |   8   |   9   |   0   |   -   |   _   |   (   |   )   |   <   |   >   |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |       |       |       | LOWER2|       |       | ADJUST|       |       |       |       |
|-----------------------------------------------------------------------------------------------|   
```

On the layer-key side is a **numberpad** for very quick access. While it is unusual for the numberpad to appear on the left-side of a keyboard, it enables the simultaneous use of a mouse with the right hand. I have found this combination to be efficient for many cases.

On the right-side are all the **bracket** keys placed together in a logical order. I typically access these keys when I am programming, so I generally already have both hands on the keyboard.

### `R1`

```
|-----------------------------------------------------------------------------------------------|
|       |   !   |   @   |   #   |       |   *   |   /   | Home  | Pg Dn | Pg Up |  End  |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |   $   |   %   |   ^   |       |   +   |   =   | Left  | Down  |  Up   | Right |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |   &   |   *   |   (   |   )   |   -   |   _   |   ~   |   `   |   |   |   \   |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |       |       |       | ADJUST|       |       | RAISE2|       |       |       |       |
|-----------------------------------------------------------------------------------------------|
```

On the layer-key side right under the home-row are the **arrow** keys for very quick access. Above the home-row are additional **navigation** keys which I have found to be very useful when easy to access. Below the home-row are the remaining **symbols** that aren't found on other layers. I use these symbols moderately and they are very easy to access. The `\` key is laid over the `/` key from the base layer.

On the left-side is the **shifted-numberpad**, laid over the numberpad in `L1`. Like the brackets in `L1`, I typically access these keys when I am programming, so I generally already have both hands on the keyboard.

### `L2`

```
|-----------------------------------------------------------------------------------------------|
|       |       |       |[email]|       |       |       |       |       |       |[phone]|[clear]|
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |       |shebang|       |       |       |       |       |       |       |       |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       | chmod |       | commit|  venv |       | [name]|       |       |       |       |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |       |       |       |  BASE |       |       |  xXx  |       |       |       |       |
|-----------------------------------------------------------------------------------------------|
```

This layer contains my **static macros**. They are laid over the alphabets in `BASE` mnemonically (e.g. `[email]` is laid over `E` in `BASE`).

### `R2`

```
|-----------------------------------------------------------------------------------------------|
|       |       |       |       |       |       |       | S lt  | S up  | S dn  | S rt  |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |       |       |       |       |       |       | M lt  | M dn  | M up  | M rt  |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |       |       |       |       |       |       | L Ck  | R ck  | Slow  | Fast  |       |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|       |       |       |       |  xXx  |       |       |  BASE |       |       |       |       |
|-----------------------------------------------------------------------------------------------|
```

This layer contains mouse-navigation keys on the layer-side.


### `ADJUST`

```
|-----------------------------------------------------------------------------------------------|
|       |       |       |       |       |       |       |scrll h|scrll v|scrll v|scrll h| Power |
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|T Audio|       |       |       |       |       |       |arrow h|arrow v|arrow v|arrow h|T Piano|
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
|T Click|       |       |       |  vol  | bright|       | media |       |       |       |C Piano|
|-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
| Reset |       |       |       |  xXx  |  BASE |  BASE |  xXx  |       |       |       | Reset |
|-----------------------------------------------------------------------------------------------|
```

// TODO