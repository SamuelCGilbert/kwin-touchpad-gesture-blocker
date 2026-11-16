/*
    SPDX-FileCopyrightText: 2026 Touchpad Gesture Blocker contributors
    SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "gestureblocker.h"

#include <KConfigGroup>
#include <KSharedConfig>

TouchpadGestureBlocker::TouchpadGestureBlocker()
    // Run before InputFilterOrder::GlobalShortcut, where KWin recognizes its
    // built-in gestures. Lock screen, screen edges and drag and drop run first.
    : KWin::InputEventFilter(KWin::InputFilterOrder::TabBox)
{
    loadConfig();
    KWin::input()->installInputEventFilter(this);
}

void TouchpadGestureBlocker::loadConfig()
{
    // ~/.config/kwinrc
    // [Plugin-touchpadgestureblocker]
    // MinimumFingers=3
    // BlockPinch=true
    const KConfigGroup group = KSharedConfig::openConfig(QStringLiteral("kwinrc"))->group(QStringLiteral("Plugin-touchpadgestureblocker"));
    m_minimumFingers = std::max(3, group.readEntry("MinimumFingers", 3));
    m_blockPinch = group.readEntry("BlockPinch", true);
}

bool TouchpadGestureBlocker::swipeGestureBegin(KWin::PointerSwipeGestureBeginEvent *event)
{
    m_blockingSwipe = event->fingerCount >= m_minimumFingers;
    return m_blockingSwipe;
}

bool TouchpadGestureBlocker::swipeGestureUpdate(KWin::PointerSwipeGestureUpdateEvent *)
{
    return m_blockingSwipe;
}

bool TouchpadGestureBlocker::swipeGestureEnd(KWin::PointerSwipeGestureEndEvent *)
{
    return std::exchange(m_blockingSwipe, false);
}

bool TouchpadGestureBlocker::swipeGestureCancelled(KWin::PointerSwipeGestureCancelEvent *)
{
    return std::exchange(m_blockingSwipe, false);
}

bool TouchpadGestureBlocker::pinchGestureBegin(KWin::PointerPinchGestureBeginEvent *event)
{
    m_blockingPinch = m_blockPinch && event->fingerCount >= m_minimumFingers;
    return m_blockingPinch;
}

bool TouchpadGestureBlocker::pinchGestureUpdate(KWin::PointerPinchGestureUpdateEvent *)
{
    return m_blockingPinch;
}

bool TouchpadGestureBlocker::pinchGestureEnd(KWin::PointerPinchGestureEndEvent *)
{
    return std::exchange(m_blockingPinch, false);
}

bool TouchpadGestureBlocker::pinchGestureCancelled(KWin::PointerPinchGestureCancelEvent *)
{
    return std::exchange(m_blockingPinch, false);
}
