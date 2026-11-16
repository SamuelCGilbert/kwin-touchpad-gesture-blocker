/*
    SPDX-FileCopyrightText: 2026 Touchpad Gesture Blocker contributors
    SPDX-License-Identifier: GPL-2.0-or-later

    KWin handles every touchpad swipe/pinch with 3 or more fingers itself
    (virtual desktop switching, Overview, Grid) and there is no setting to turn
    that off. When an external tool such as Touchégg reads the same gestures
    from libinput, every gesture triggers two actions.

    This plugin consumes those gestures before KWin's global shortcut filter
    sees them, giving the X11-session behaviour back on Wayland.
*/
#pragma once

#include "input.h"
#include "input_event.h"
#include "plugin.h"

class TouchpadGestureBlocker : public KWin::Plugin, public KWin::InputEventFilter
{
    Q_OBJECT

public:
    TouchpadGestureBlocker();

    bool swipeGestureBegin(KWin::PointerSwipeGestureBeginEvent *event) override;
    bool swipeGestureUpdate(KWin::PointerSwipeGestureUpdateEvent *event) override;
    bool swipeGestureEnd(KWin::PointerSwipeGestureEndEvent *event) override;
    bool swipeGestureCancelled(KWin::PointerSwipeGestureCancelEvent *event) override;

    bool pinchGestureBegin(KWin::PointerPinchGestureBeginEvent *event) override;
    bool pinchGestureUpdate(KWin::PointerPinchGestureUpdateEvent *event) override;
    bool pinchGestureEnd(KWin::PointerPinchGestureEndEvent *event) override;
    bool pinchGestureCancelled(KWin::PointerPinchGestureCancelEvent *event) override;

private:
    void loadConfig();

    int m_minimumFingers = 3;
    bool m_blockPinch = true;
    bool m_blockingSwipe = false;
    bool m_blockingPinch = false;
};
