/*
 * Copyright 2014 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Michael Zanetti <michael.zanetti@canonical.com>
 */

#include <Mocks/MockSurfaceManager.h>
#include <Mocks/MockSurface.h>

using namespace unity::shell::application;

MockSurfaceManager::MockSurfaceManager(QObject* parent): SurfaceManagerInterface(parent)
{
    MockSurface *item = new MockSurface("dialer-app", "surface1", this);
    m_list.append(item);
}

MockSurfaceManager::~MockSurfaceManager()
{
    while (!m_list.empty())
    {
        m_list.takeFirst()->deleteLater();
    }
}

// cppcheck-suppress unusedFunction
int MockSurfaceManager::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_list.count();
}

QVariant MockSurfaceManager::data(const QModelIndex& index, int role) const
{
    switch (role) {
    case RoleApplicationId:
        return m_list.at(index.row())->appId();
    case RoleName:
        return m_list.at(index.row())->name();
    case RoleType:
        return m_list.at(index.row())->type();
    case RoleSurfaceState:
        return m_list.at(index.row())->surfaceState();
    }

    return QVariant();
}

SurfaceInterface *MockSurfaceManager::get(int index) const
{
    if (m_list.count() > index) {
        return m_list.at(index);
    }
    return nullptr;
}
