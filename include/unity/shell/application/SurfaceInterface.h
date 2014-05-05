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

#ifndef SURFACEINTERFACE_H
#define SURFACEINTERFACE_H

#include <unity/SymbolExport.h>

#include <QObject>

namespace unity
{
namespace shell
{
namespace application
{

class SurfaceManagerInterface;
class ApplicationInfoInterface;

/**
 * @brief A class that holds information about an application's surface
 *
 * The items hold all the information required for the visual representation
 * of a surface.
 */

class UNITY_API SurfaceInterface: public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(SurfaceState)

    /**
     * @brief The type of this surface.
     *
     * Gives information about the type of this surface. E.g. it is a normal window or a modal popup.
     */
    Q_PROPERTY(Type type READ type NOTIFY typeChanged)

    /**
     * @brief The state of this surface.
     *
     * Holds information about the state of this surface. E.g. it is shown normally or minimized.
     */
    Q_PROPERTY(SurfaceState surfaceState READ surfaceState NOTIFY surfaceStateChanged)

    /**
     * @brief The name of this surface.
     *
     * Holds the name of this surface. Can be used e.g. for the window title.
     */
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

    /**
     * @brief The application this surface belongs to.
     *
     * A 1:n connection between surfaces and applications. A surface always refers to one
     * application, while an application might have many surfaces.
     */
    Q_PROPERTY(QString appId READ appId CONSTANT)

public:
    /**
     * @brief The type of a surface.
     *
     * This enum defines all possible values for Surface types.
     */
    enum Type {
        TypeNormal,
        TypeUtility,
        TypeDialog,
        TypeOverlay,
        TypeFreestyle,
        TypePopover,
        TypeInputMethod,
    };

    /**
     * @brief The state of a surface.
     *
     * This enum defines all possible values for Surface states.
     */
    enum SurfaceState {
        SurfaceStateUnknown,
        SurfaceStateRestored,
        SurfaceStateMinimized,
        SurfaceStateMaximized,
        SurfaceStateVertMaximized,
        /* SurfaceStateSemiMaximized, // see mircommon/mir_toolbox/common.h*/
        SurfaceStateFullscreen,
    };

    /**
     * @brief Constructs a new Surface.
     *
     * Usually Surfaces are only created by the ApplicationManager and/or SurfaceManager.
     */
    explicit SurfaceInterface(QObject *parent = 0): QObject(parent) {}
    virtual ~SurfaceInterface() {}

    /// @cond
    virtual QString appId() const = 0;
    virtual Type type() const = 0;
    virtual SurfaceState surfaceState() const = 0;
    virtual QString name() const = 0;
    /// @endcond

Q_SIGNALS:
    /// @cond
    void typeChanged();
    void surfaceStateChanged();
    void nameChanged();
    void appIdChanged();
    void surfaceDestroyed();
    /// @endcond
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // SURFACEINTERFACE_H
