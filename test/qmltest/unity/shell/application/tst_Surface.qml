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

        /* make sure all the required roles are exposed on SurfaceManager */
        function test_model_roles_enum_data() {
            return [
                        { enum: "RoleAppId" },
                        { enum: "RoleName" },
                        { enum: "RoleComment" },
                        { enum: "RoleIcon" },
                        { enum: "RoleStage" },
                        { enum: "RoleState" },
                        { enum: "RoleFocused" },
                        { enum: "RoleScreenshot" },
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
                        { tag: "SurfaceManager.roles[comment]", role: "comment", type: "string" },
                        { tag: "SurfaceManager.roles[icon]", role: "icon", type: "object" },
                        { tag: "SurfaceManager.roles[stage]", role: "stage", type: "number" },
                        { tag: "SurfaceManager.roles[state]", role: "state", type: "number" },
                        { tag: "SurfaceManager.roles[focused]", role: "focused", type: "boolean" },
                        { tag: "SurfaceManager.roles[screenshot]", role: "screenshot", type: "object" },
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
                { tag: "SurfaceManager.methods[get]", method: "get" },
                { tag: "SurfaceManager.methods[findApplication]", method: "findApplication" },
                { tag: "SurfaceManager.methods[requestFocusApplication]", method: "requestFocusApplication" },
                { tag: "SurfaceManager.methods[focusApplication]", method: "focusApplication" },
                { tag: "SurfaceManager.methods[unfocusCurrentApplication]", method: "unfocusCurrentApplication" },
                { tag: "SurfaceManager.methods[startApplication]", method: "startApplication" },
                { tag: "SurfaceManager.methods[stopApplication]", method: "stopApplication" },
                { tag: "SurfaceManager.methods[updateScreenshot]", method: "updateScreenshot" },
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
                { tag: "SurfaceManager.focusedApplicationId", property: "focusedApplicationId", type: "string" },
                { tag: "SurfaceManager.suspended", property: "suspended", type: "boolean" },
            ];
        }

        function test_model_properties(data) {
            name = "SurfaceManager";
            object = SurfaceManager;
            verifyData(data);
        }

        function test_item_properties_data() {
            return [
                { tag: "ApplicationInfo.properties[appId]", constant: "appId", type: "string" },
                { tag: "ApplicationInfo.properties[name]", property: "name", type: "string" },
                { tag: "ApplicationInfo.properties[comment]", property: "comment", type: "string" },
                { tag: "ApplicationInfo.properties[icon]", property: "icon", type: "object" },
                { tag: "ApplicationInfo.properties[stage]", property: "stage", type: "number" },
                { tag: "ApplicationInfo.properties[state]", property: "state", type: "number" },
                { tag: "ApplicationInfo.properties[focused]", property: "focused", type: "boolean" },
                { tag: "ApplicationInfo.properties[screenshot]", property: "screenshot", type: "object" },
            ];
        }

        function test_item_properties(data) {
            name = "ApplicationInfo"
            try {
                object = SurfaceManager.get(0)
            } catch(err) {
                object = undefined;
                print(err)
            }

            verifyData(data)
        }
    }
}
