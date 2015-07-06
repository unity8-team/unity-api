/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UNITY_SHELL_APPLICATION_MIRSURFACEITEM_H
#define UNITY_SHELL_APPLICATION_MIRSURFACEITEM_H

#include "Mir.h"

#include <QQuickItem>

namespace unity
{
namespace shell
{
namespace application
{

class MirSurfaceInterface;

/*
   Renders a MirSurface in a QML scene and forwards the input events it receives to it.

   You can have multiple MirSurfaceItems displaying the same MirSurface. But care must
   be taken that only one of them feeds the MirSurface with input events and also only
   one resizes it.
 */
class MirSurfaceItemInterface : public QQuickItem
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(State)
    Q_ENUMS(OrientationAngle)

    // Type of the given surface or Mir.UnknownType if no surface is set
    Q_PROPERTY(Mir::Type type READ type NOTIFY typeChanged)

    // State of the given surface or Mir.UnknownState if no surface is set
    Q_PROPERTY(Mir::State surfaceState READ surfaceState NOTIFY surfaceStateChanged)

    // Name of the given surface or an empty string if no surface is set
    Q_PROPERTY(QString name READ name CONSTANT)

    // True if the item has a surface and that surface has a mir client bound to it.
    // A "zombie" (live == false) surface never becomes alive again.
    Q_PROPERTY(bool live READ live NOTIFY liveChanged)

    // Orientation angle of the given surface
    //
    // How many degrees, clockwise, the UI in the surface has to rotate to match shell's UI orientation
    Q_PROPERTY(Mir::OrientationAngle orientationAngle READ orientationAngle WRITE setOrientationAngle
               NOTIFY orientationAngleChanged DESIGNABLE false)

    // The surface to be displayed
    Q_PROPERTY(unity::shell::application::MirSurfaceInterface* surface READ surface WRITE setSurface NOTIFY surfaceChanged)

    // Whether the item will resize its surface match his size.
    // It's true by default.
    // Only one item should have this property enabled for a given surface.
    Q_PROPERTY(bool resizeSurfaceToItem READ resizeSurfaceToItem
                                        WRITE setResizeSurfaceToItem
                                        NOTIFY resizeSurfaceToItemChanged)

    // Whether the item will forward activeFocus, touch events, mouse events and key events
    // to its surface.
    // It's true by default.
    // Only one item should have this property enabled for a given surface.
    Q_PROPERTY(bool surfaceInputEnabled READ surfaceInputEnabled
                                        WRITE setSurfaceInputEnabled
                                        NOTIFY surfaceInputEnabledChanged)

public:
    MirSurfaceItemInterface(QQuickItem *parent = 0) : QQuickItem(parent) {}
    virtual ~MirSurfaceItemInterface() {}

    virtual Mir::Type type() const = 0;
    virtual Mir::State surfaceState() const = 0;
    virtual QString name() const = 0;
    virtual bool live() const = 0;

    virtual Mir::OrientationAngle orientationAngle() const = 0;
    virtual void setOrientationAngle(Mir::OrientationAngle angle) = 0;

    virtual MirSurfaceInterface* surface() const = 0;
    virtual void setSurface(MirSurfaceInterface*) = 0;

    virtual bool resizeSurfaceToItem() const = 0;
    virtual void setResizeSurfaceToItem(bool value) = 0;

    virtual bool surfaceInputEnabled() const = 0;
    virtual void setSurfaceInputEnabled(bool value) = 0;

Q_SIGNALS:
    void typeChanged(Mir::Type);
    void surfaceStateChanged(Mir::State);
    void liveChanged(bool live);
    void orientationAngleChanged(Mir::OrientationAngle angle);
    void surfaceChanged(MirSurfaceInterface*);
    void resizeSurfaceToItemChanged(bool value);
    void surfaceInputEnabledChanged(bool value);
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_MIRSURFACEITEM_H
