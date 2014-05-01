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

#ifndef MOCKSURFACEINFO_H
#define MOCKSURFACEINFO_H

#include <SurfaceItemInterface.h>

#include <QUrl>

using namespace unity::shell::application;

class UNITY_API MockSurfaceItem: public SurfaceItemInterface
{
    Q_OBJECT
public:
    MockSurfaceItem(QQuickItem* parent = 0);

private:
};

#endif // MOCKSURFACEINFO_H
