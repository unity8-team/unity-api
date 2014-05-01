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

#ifndef SURFACEITEMINTERFACE_H
#define SURFACEITEMINTERFACE_H

#include <unity/SymbolExport.h>

#include <QQuickItem>

namespace unity
{
namespace shell
{
namespace application
{

class SurfaceManagerInterface;
class Application;

class UNITY_API SurfaceItemInterface: public QQuickItem
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(State)

    Q_PROPERTY(Type type READ type NOTIFY typeChanged)
    Q_PROPERTY(SurfaceState surfaceState READ surfaceState NOTIFY surfaceStateChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(Application* application READ application CONSTANT)

public:
    enum Type {
        TypeNormal,
        TypeUtility,
        TypeDialog,
        TypeOverlay,
        TypeFreestyle,
        TypePopover,
        TypeInputMethod,
    };

    enum SurfaceState {
        SurfaceStateUnknown,
        SurfaceStateRestored,
        SurfaceStateMinimized,
        SurfaceStateMaximized,
        SurfaceStateVertMaximized,
        /* SurfaceStateSemiMaximized, // see mircommon/mir_toolbox/common.h*/
        SurfaceStateFullscreen,
    };

    explicit SurfaceItemInterface(QQuickItem *parent = 0): QQuickItem(parent) {}
    virtual ~SurfaceItemInterface() {}

    virtual Application* application() const = 0;
    virtual Type type() const = 0;
    virtual SurfaceState surfaceState() const = 0;
    virtual QString name() const = 0;

Q_SIGNALS:
    void typeChanged();
    void surfaceStateChanged();
    void nameChanged();
    void surfaceDestroyed();
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // SURFACEITEMINTERFACE_H
