# KWin Touchpad Gesture Blocker

KWin (Plasma 6, Wayland) handles every touchpad swipe and pinch with 3 or more
fingers itself (virtual desktop switching, Overview, Grid). There is no
setting to turn this off. Tools that read the same gestures from libinput,
like [Touchégg](https://github.com/JoseExposito/touchegg), then trigger a
second action for every gesture.

This KWin plugin consumes those gestures before KWin's built-in gesture
shortcuts see them, restoring the X11 session behaviour.

## Configuration (`~/.config/kwinrc`)

```ini
[Plugin-touchpadgestureblocker]
MinimumFingers=3   # block swipes/pinches with at least this many fingers
BlockPinch=true
```

Disable the plugin with `touchpadgestureblockerEnabled=false` in the
`[Plugins]` group of `kwinrc`.

## Building

The plugin must be built against the headers of the exact KWin version that is
installed, and rebuilt after every Plasma update. `build.sh` expects a sysroot
with the matching `kwin-dev` and KF6 (`kconfig`, `kcoreaddons`,
`kwindowsystem`) development headers.
