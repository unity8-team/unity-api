/*
 * Copyright (C) 2013-2014 Canonical, Ltd.
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

#ifndef MIRSURFACEITEM_H
#define MIRSURFACEITEM_H

#include <unity/SymbolExport.h>

// Std
#include <memory>

// Qt
#include <QPointer>
#include <QSet>
#include <QQuickItem>
#include <QTimer>
#include <QQmlListProperty>

// mir
//#include <mir/scene/surface.h>
//#include <mir_toolkit/common.h>

// local
#include "MirSurfaceInterface.h"
//#include "session_interface.h"

class SurfaceObserver;
class MirShell;

namespace unity {
namespace shell {
namespace application {

class MirSurfaceManager;
class QSGMirSurfaceNode;
class QMirSurfaceTextureProvider;
class Application;

class MirSurfaceItemInterface : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(Globals::SurfaceType type READ type NOTIFY typeChanged)
    Q_PROPERTY(Globals::SurfaceState state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(bool live READ live NOTIFY liveChanged)
    Q_PROPERTY(Qt::ScreenOrientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged DESIGNABLE false)

public:
    explicit MirSurfaceItemInterface(QQuickItem *parent = 0): QQuickItem(parent) {}
    ~MirSurfaceItemInterface() {}

    //getters
    virtual Globals::SurfaceType type() const = 0;
    virtual Globals::SurfaceState state() const = 0;
    virtual QString name() const = 0;
    virtual bool live() const = 0;
    virtual Qt::ScreenOrientation orientation() const = 0;

    // Item surface/texture management
    virtual bool isTextureProvider() const = 0;
    virtual QSGTextureProvider *textureProvider() const = 0;

    virtual void stopFrameDropper() = 0;
    virtual void startFrameDropper() = 0;

    virtual void setOrientation(const Qt::ScreenOrientation orientation) = 0;

Q_SIGNALS:
    void typeChanged();
    void stateChanged();
    void nameChanged();
    void orientationChanged();
    void liveChanged(bool live);
    void firstFrameDrawn(MirSurfaceItemInterface *item);
};

} // namespace application
} // namespace shell
} // namespace unity

Q_DECLARE_METATYPE(unity::shell::application::MirSurfaceItemInterface*)

#endif // MIRSURFACEITEM_H
