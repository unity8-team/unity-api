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

#ifndef MOCKSURFACE_H
#define MOCKSURFACE_H

#include <SurfaceInterface.h>

#include <QUrl>

using namespace unity::shell::application;

class UNITY_API MockSurface: public SurfaceInterface
{
    Q_OBJECT
public:
    MockSurface(const QString &appId, const QString &name, QObject* parent = 0);

    QString appId() const override;
    SurfaceInterface::Type type() const override;
    SurfaceInterface::SurfaceState surfaceState() const override;
    QString name() const override;

private:
    QString m_appId;
    QString m_name;
};

#endif // MOCKSURFACE_H
