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

/**
 * @brief The SurfaceManager is a model which holds all the available surfaces.
 *
 * This is the main class to interact with surfaces.
 */

class UNITY_API SurfaceManagerInterface : public QAbstractListModel
{
    Q_OBJECT

    /**
     * @brief The count of the surfaces known to the manager.
     *
     * This is the same as rowCount, added in order to keep compatibility with QML ListModels.
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    virtual ~SurfaceManagerInterface() {}

    /// @cond
    virtual QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> roles;
        // TODO: what roles do we need?
        return roles;
    }

    int count() const {
        return rowCount();
    }
    /// @endcond

protected:
    /// @cond
    SurfaceManagerInterface(QObject *parent = 0):
        QAbstractListModel(parent)
    {
        connect(this, &QAbstractListModel::rowsInserted, this, &SurfaceManagerInterface::countChanged);
        connect(this, &QAbstractListModel::rowsRemoved, this, &SurfaceManagerInterface::countChanged);
        connect(this, &QAbstractListModel::modelReset, this, &SurfaceManagerInterface::countChanged);
    }
    /// @endcond

Q_SIGNALS:
    /// @cond
    void countChanged();
    /// @endcond

    /**
     * @brief Indicates that a new surface has been created.
     *
     * This will be emitted when a new surface has been created and added
     * to the model. It is the same as the rowsInserted() but more QML friendly.
     */
    void surfaceCreated(SurfaceItemInterface* surface);

    /**
     * @brief Indicates that a surface has been destroyed.
     *
     * This will be emitted when a surface has been destroyed and removed
     * from the model. It is the same as the rowsRemoved() but more QML friendly.
     */
    void surfaceDestroyed(SurfaceItemInterface* surface);

};

} // namespace application
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_APPLICATION_SURFACEMANGERINTERFACE_H
