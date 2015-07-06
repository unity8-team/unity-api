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

#ifndef UNITY_SHELL_APPLICATION_MIRSURFACE_H
#define UNITY_SHELL_APPLICATION_MIRSURFACE_H

#include <QObject>

#include "Mir.h"

namespace unity
{
namespace shell
{
namespace application
{

/*
    Holds a Mir surface. Pretty much an opaque class.

    All surface manipulation is done by giving it to a MirSurfaceItem and then
    using MirSurfaceItem's properties.
 */
class MirSurfaceInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Mir::Type type READ type NOTIFY typeChanged)

public:
    MirSurfaceInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~MirSurfaceInterface() {}

    virtual Mir::Type type() const = 0;

Q_SIGNALS:
    void typeChanged(Mir::Type);
};

} // namespace application
} // namespace shell
} // namespace unity

Q_DECLARE_METATYPE(unity::shell::application::MirSurfaceInterface*)

#endif // UNITY_SHELL_APPLICATION_MIRSURFACE_H
