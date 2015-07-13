/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranties of MERCHANTABILITY,
 * SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UNITY_SHELL_APPLICATION_GLOBALS_H
#define UNITY_SHELL_APPLICATION_GLOBALS_H

#include <QObject>

namespace unity
{
namespace shell
{
namespace application
{

class Globals
{
    Q_GADGET
    Q_ENUMS(SurfaceState)
    Q_ENUMS(SurfaceType)

public:
    enum SurfaceType {
        Normal,
        Utility,
        Dialog,
        Gloss,
        Freestyle,
        Menu,
        InputMethod,
        Satellite,
        Tip
    };

    enum SurfaceState {
        Unknown,
        Restored,
        Minimized,
        Maximized,
        VertMaximized,
        Fullscreen
    };

    enum PixelFormat {
        Invalid,
        ABGR8888,
        XBGR8888,
        ARGB8888,
        XRGB8888,
        BGR888
    };

private:
    Globals() = default;
    ~Globals() = default;
};

} // namespace application
} // shell
} // application

#endif // UNITY_SHELL_APPLICATION_GLOBALS_H
