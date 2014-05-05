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

#ifndef MOCKSURFACEMANAGER_H
#define MOCKSURFACEMANAGER_H

#include <SurfaceManagerInterface.h>

using namespace unity::shell::application;

class MockSurfaceItem;

class UNITY_API MockSurfaceManager: public SurfaceManagerInterface
{
   Q_OBJECT

public:
    MockSurfaceManager(QObject* parent = 0);
    ~MockSurfaceManager();

    int rowCount(const QModelIndex& parent) const;

    QVariant data(const QModelIndex& index, int role) const;

private:
    QList<MockSurfaceItem*> m_list;
};

#endif // MOCKSURFACEMANAGER_H