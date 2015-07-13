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

#include <unity/SymbolExport.h>

#include <QObject>

namespace unity
{
namespace shell
{
namespace application
{

/**
 * @brief Global enumerations
 *
 * This class defines commonly used enumerations in QtMir which are shared between
 * the QPA plugin and the shell implementation.
 */

class UNITY_API Globals
{
    Q_GADGET
    Q_ENUMS(SurfaceState)
    Q_ENUMS(SurfaceType)

public:
    /**
     * @brief The Surface Types supported by Mir
     *
     * See the Mir Window Management documentation for more details
     */
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

    /**
     * @brief The Surface States supported by Mir
     *
     * See the Mir Window Management documentation for more details
     */
    enum SurfaceState {
        Unknown,
        Restored,
        Minimized,
        Maximized,
        VertMaximized,
        Fullscreen
    };

    /**
     * @brief The Pixel formats supported by Mir Surfaces
     *
     * See the Mir documentation for more details
     */
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
