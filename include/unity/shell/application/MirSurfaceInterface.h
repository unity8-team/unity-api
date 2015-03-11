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

#ifndef MIRSURFACE_H
#define MIRSURFACE_H

// Qt
#include <QObject>
#include <QSize>

// mir
//#include <mir_toolkit/common.h>
//#include <mir/scene/surface.h>

// local
#include "Globals.h"
//#include "session_interface.h"

class SurfaceObserver;
class MirShell;

namespace unity
{
namespace shell
{
namespace application
{

class MirSurfaceManager;
class Application;

class MirSurface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)
    Q_PROPERTY(MirSurface* parent READ parentSurface NOTIFY parentSurfaceChanged)
    Q_PROPERTY(QList<MirSurface*> children READ childSurfaces NOTIFY childSurfacesChanged)

    Q_PROPERTY(Globals::SurfaceType type READ type NOTIFY typeChanged)
    Q_PROPERTY(Globals::SurfaceState state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(bool focus READ focus WRITE setFocus NOTIFY focusChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(Qt::ScreenOrientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(Qt::ScreenOrientations preferredOrientations READ preferredOrientations NOTIFY preferredOrientationsChanged)

    Q_PROPERTY(Globals::PixelFormat pixelFormat READ pixelFormat CONSTANT)
    Q_PROPERTY(bool supportsInput READ supportsInput CONSTANT)


public:
    explicit MirSurface(QObject *parent = 0);

    // getters
    virtual QSize size() const = 0;
    virtual MirSurface* parentSurface() const = 0;
    virtual QList<MirSurface*> childSurfaces() const = 0;
    virtual Globals::SurfaceType type() const = 0;
    virtual Globals::SurfaceState state() const = 0;
    virtual QString name() const = 0;
    virtual bool focus() const = 0;
    virtual bool visible() const = 0;
    virtual Qt::ScreenOrientation orientation() const = 0;
    virtual Qt::ScreenOrientations preferredOrientations() const = 0;
    virtual Globals::PixelFormat pixelFormat() const = 0;
    virtual bool supportsInput() const = 0;

    virtual bool isFirstFrameDrawn() const = 0;

    // setters
    virtual void setFocus(const bool focus) = 0;
    virtual void setVisible(const bool focus) = 0;
    virtual void setOrientation(const Qt::ScreenOrientation orientation) = 0;

    // others
    Q_INVOKABLE virtual void requestSize(const QSize &size) = 0;
    Q_INVOKABLE virtual void requestClose() = 0;
    virtual void sendEvent(QEvent *event) = 0;

    virtual void allowFramedropping(const bool allow) = 0;

Q_SIGNALS:
    void sizeChanged();
    void parentSurfaceChanged();
    void childSurfacesChanged();
    void typeChanged();
    void stateChanged();
    void nameChanged();
    void focusChanged();
    void visibleChanged();
    void orientationChanged();
    void preferredOrientationsChanged();

    void firstFrameDrawn();
    void damaged(const QRegion &rect);
};

} // application
} // shell
} // unity

#endif // MIRSURFACE_H
