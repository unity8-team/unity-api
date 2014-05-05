/*
 * Copyright 2013 Canonical Ltd.
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

#include <TestApplicationPlugin.h>
#include <Mocks/MockApplicationManager.h>
#include <Mocks/MockApplicationInfo.h>
#include <Mocks/MockSurfaceManager.h>
#include <Mocks/MockSurfaceItem.h>
#include <Mocks/MockSurface.h>

#include <ApplicationManagerInterface.h>
#include <ApplicationInfoInterface.h>
#include <SurfaceManagerInterface.h>
#include <SurfaceItemInterface.h>
#include <SurfaceInterface.h>

#include <QtQml/qqml.h>

using namespace unity::shell::application;

static QObject* applicationManagerProvider(QQmlEngine* /* engine */, QJSEngine* /* scriptEngine */)
{
    return new MockApplicationManager();
}

static QObject* surfaceManagerProvider(QQmlEngine* /* engine */, QJSEngine* /* scriptEngine */)
{
    return new MockSurfaceManager();
}

// cppcheck-suppress unusedFunction
void TestApplicationPlugin::registerTypes(const char* uri)
{
    // @uri Unity.Application
    qmlRegisterUncreatableType<ApplicationManagerInterface>(uri, 0, 1, "ApplicationManagerInterface", "Interface for the ApplicationManager");
    qmlRegisterUncreatableType<ApplicationInfoInterface>(uri, 0, 1, "ApplicationInfoInterface", "Interface for ApplicationInfo");

    qmlRegisterSingletonType<MockApplicationManager>(uri, 0, 1, "ApplicationManager", applicationManagerProvider);
    qmlRegisterUncreatableType<MockApplicationInfo>(uri, 0, 1, "ApplicationInfo", "Can't create ApplicationInfos in QML. Get them from the ApplicationManager");

    qmlRegisterUncreatableType<SurfaceManagerInterface>(uri, 0, 1, "SurfaceManagerInterface", "Interface for the SurfaceManager");
    qmlRegisterUncreatableType<SurfaceItemInterface>(uri, 0, 1, "SurfaceItemInterface", "Interface for SurfaceItem");
    qmlRegisterUncreatableType<SurfaceInterface>(uri, 0, 1, "SurfaceInterface", "Interface for Surface");

    qmlRegisterSingletonType<MockSurfaceManager>(uri, 0, 1, "SurfaceManager", surfaceManagerProvider);
    qmlRegisterUncreatableType<MockSurface>(uri, 0, 1, "Surface", "Can't create Surfaces in QML. Get them from the SurfaceManager");
    qmlRegisterType<MockSurfaceItem>(uri, 0, 1, "SurfaceItem");
}
