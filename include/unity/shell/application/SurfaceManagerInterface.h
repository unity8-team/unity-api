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

#ifndef UNITY_SHELL_APPLICATION_SURFACEMANGERINTERFACE_H
#define UNITY_SHELL_APPLICATION_SURFACEMANGERINTERFACE_H

#include <unity/SymbolExport.h>

#include <QAbstractListModel>

namespace unity
{
namespace shell
{
namespace application
{

class SurfaceItemInterface;


class UNITY_API SurfaceManagerInterface : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    SurfaceManagerInterface(QObject *parent = 0) {}
    virtual ~SurfaceManagerInterface() {}

    virtual QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        // TODO: what roles do we need?
        return roles;
    }

    int count() const {
        return rowCount();
    }

Q_SIGNALS:
    void countChanged();

    void surfaceCreated(SurfaceItemInterface* surface);
    void surfaceDestroyed(SurfaceItemInterface* surface);

};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_SURFACEMANGERINTERFACE_H
