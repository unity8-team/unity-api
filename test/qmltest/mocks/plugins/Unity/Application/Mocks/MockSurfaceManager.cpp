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
#include <Mocks/MockSurfaceItem.h>

using namespace unity::shell::application;

MockSurfaceManager::MockSurfaceManager(QObject* parent): SurfaceManagerInterface(parent)
{
//    MockApplicationInfo *item = new MockApplicationInfo("phone-app", "Phone App", "Telephony application", QUrl("/usr/share/pixmaps/some/icon.png"));
//    m_list.append(item);
//    item = new MockApplicationInfo("camera-app", "Camera App", "Lets you take pictures with the camera.", QUrl("/usr/share/pixmaps/some/icon.png"));
//    m_list.append(item);
//    item = new MockApplicationInfo("calendar-app", "Calendar App", "5 missed reminders", QUrl("/usr/share/pixmaps/some/icon.png"));
//    m_list.append(item);
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
    return QVariant();
}
