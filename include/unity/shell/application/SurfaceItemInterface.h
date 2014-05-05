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

class UNITY_API SurfaceItemInterface: public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(SurfaceInterface* surface MEMBER m_surface NOTIFY surfaceChanged)

public:
    explicit SurfaceItemInterface(QQuickItem *parent = 0): QQuickItem(parent) {}
    virtual ~SurfaceItemInterface() {}

Q_SIGNALS:
    void surfaceChanged();

private:
    SurfaceInterface *m_surface;
};

} // namespace application
} // namespace shell
} // namespace unity

#endif // SURFACEITEMINTERFACE_H
