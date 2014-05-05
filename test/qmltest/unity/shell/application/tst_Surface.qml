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

import QtQuick 2.0
import QtTest 1.0
import TestUtil 0.1
import Unity.Application 0.1

Item {

    SignalSpy {
        id: signalSpy
    }

    Verifier {
        id: checkModelVerifier

        property var model: SurfaceManager

        function test_model_data() {
            return [
                { tag: "SurfaceManager[object]", type: "object" },
                { tag: "SurfaceManager[SurfaceManagerInterface]", type: "unity::shell::application::SurfaceManagerInterface" },
            ];
        }

        function test_model(data) {
            object = model;
            name = "SurfaceManager"

            verifyData(data);
        }
    }

    Verifier {
        when: checkModelVerifier.completed

        Repeater {
            id: repeater
            model: SurfaceManager
            delegate: Item {
                property var roles: model
            }
        }

        SurfaceItem {
            id: surfaceItem
            surface: SurfaceManager.get(0)
        }

        /* make sure all the required roles are exposed on SurfaceManager */
        function test_model_roles_enum_data() {
            return [
                        { enum: "RoleType" },
                        { enum: "RoleSurfaceState" },
                        { enum: "RoleName" },
                        { enum: "RoleApplicationId" },
                    ];
        }

        function test_model_roles_enum(data) {
            name = "SurfaceManager"
            object = SurfaceManager

            verifyData(data);
        }

        function test_model_roles_data() {
            return [
                        { tag: "SurfaceManager.roles[appId]", role: "appId", type: "string" },
                        { tag: "SurfaceManager.roles[name]", role: "name", type: "string" },
                        { tag: "SurfaceManager.roles[type]", role: "type", type: "number" },
                        { tag: "SurfaceManager.roles[surfaceState]", role: "surfaceState", type: "number" },
                    ];
        }

        function test_model_roles(data) {
            name = "SurfaceManager"
            try {
                object = repeater.itemAt(0).roles;
            } catch(err) {
                object = undefined;
            }

            verifyData(data);
        }

        function test_model_methods_data() {
            return [
                { tag: "SurfaceManager.methods[surfaceCreated]", method: "surfaceCreated" },
                { tag: "SurfaceManager.methods[surfaceDestroyed]", method: "surfaceDestroyed" },
            ];
        }

        function test_model_methods(data) {
            name = "SurfaceManager";
            object = SurfaceManager;
            verifyData(data);
        }

        function test_model_properties_data() {
            return [
                { tag: "SurfaceManager.count", property: "count", type: "number" },
            ];
        }

        function test_model_properties(data) {
            name = "SurfaceManager";
            object = SurfaceManager;
            verifyData(data);
        }

        function test_surface_properties_data() {
            return [
                { tag: "Surface.properties[type]", constant: "type", type: "number" },
                { tag: "Surface.properties[surfaceState]", property: "surfaceState", type: "number" },
                { tag: "Surface.properties[name]", property: "name", type: "string" },
                { tag: "Surface.properties[appId]", property: "appId", type: "string" },
            ];
        }

        function test_surface_properties(data) {
            name = "Surface"
            try {
                object = SurfaceManager.get(0)
            } catch(err) {
                object = undefined;
                print(err)
            }

            verifyData(data)
        }

        function test_surfaceitem_properties_data() {
            return [
                { tag: "SurfaceItem.properties[surface]", property: "surface", type: "object" },
            ];
        }

        function test_surfaceitem_properties(data) {
            name = "SurfaceItem"
            try {
                object = surfaceItem;
            } catch(err) {
                object = undefined;
                print(err)
            }

            verifyData(data)
        }
    }
}
