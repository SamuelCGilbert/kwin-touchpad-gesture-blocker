# KWin Touchpad Gesture Blocker

KWin (Plasma 6, Wayland) handles every touchpad swipe and pinch with 3 or more
fingers itself (virtual desktop switching, Overview, Grid). There is no
setting to turn this off. Tools that read the same gestures from libinput,
like [Touchégg](https://github.com/SamuelCGilbert/touchegg) (a fork that works on
Plasma Wayland), then trigger a second action for every gesture.

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

## Build

KWin has no stable plugin API, so the plugin must be built against the headers of
the exact KWin version you run, and rebuilt after every Plasma update.

Needs `kwin-dev`, `qt6-base-dev`, `qt6-declarative-dev` and `libkf6config-dev`.

```sh
cmake -B build
cmake --build build
sudo cmake --install build
```

Log out and back in. The plugin is enabled by default.

To install without root, copy `touchpadgestureblocker.so` to
`~/.local/opt/kwin-plugins/kwin/plugins` and set
`QT_PLUGIN_PATH=~/.local/opt/kwin-plugins` for your Plasma session.

## Limits

- Only KDE Plasma 6 (Wayland). Tested on Plasma 6.8.
- It blocks KWin's own gestures with that many fingers everywhere. Touchpad
  gestures with fewer fingers, and touchscreen gestures, are left alone.
- Other KWin plugins that handle touchpad gestures, such as Input Actions, may
  not see the blocked gestures either.

Written with help from an AI assistant (Claude) and shared as-is.

## License

GPL-2.0-or-later
