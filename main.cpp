/*
    SPDX-FileCopyrightText: 2026 Touchpad Gesture Blocker contributors
    SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <plugin.h>

#include "gestureblocker.h"

class KWIN_EXPORT TouchpadGestureBlockerFactory : public KWin::PluginFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginFactory_iid FILE "metadata.json")
    Q_INTERFACES(KWin::PluginFactory)

public:
    std::unique_ptr<KWin::Plugin> create() const override
    {
        return std::make_unique<TouchpadGestureBlocker>();
    }
};

#include "main.moc"
