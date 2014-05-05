/*
 * Copyright (C) 2014 Canonical, Ltd.
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

#ifndef UNITY_SHELL_APPLICATION_SURFACEITEMINTERFACE_H
#define UNITY_SHELL_APPLICATION_SURFACEITEMINTERFACE_H

#include <unity/SymbolExport.h>

#include "SurfaceInterface.h"

#include <QQuickItem>

namespace unity
{
namespace shell
{
namespace application
{

class SurfaceManagerInterface;
class Application;

/**
 * @brief A class that paints a SurfaceInterface in QML.
 *
 * This class doesn't hold any data on its own but is used to paint a SurfaceInterface
 * in QML. SurfaceItems can be created and destroyed by the QML context as if they
 * were plain Rectangles. By assigning a SurfaceInterface to it, application
 * surfaces can be painted in the shell.
 */

class UNITY_API SurfaceItemInterface: public QQuickItem
{
    Q_OBJECT

    /**
     * @brief The surface that should be painted.
     *
     * Set this to the Surface you want to have painted by this SurfaceItem.
     */
    Q_PROPERTY(SurfaceInterface* surface MEMBER m_surface NOTIFY surfaceChanged)

public:

    /**
     * @brief Constructs a SurfaceItem.
     *
     * Usually SurfaceItems are created within QML.
     */
    explicit SurfaceItemInterface(QQuickItem *parent = 0): QQuickItem(parent) {}
    virtual ~SurfaceItemInterface() {}

Q_SIGNALS:
    /// @cond
    void surfaceChanged();
    /// @endcond

private:
    SurfaceInterface *m_surface;
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_SURFACEITEMINTERFACE_H
