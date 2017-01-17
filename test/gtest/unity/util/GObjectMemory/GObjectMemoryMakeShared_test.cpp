/*
 * Copyright (C) 2017 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Pete Woods <pete.woods@canonical.com>
 */

#include <unity/util/GObjectMemory.h>

#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace unity;
using namespace unity::util;

namespace {

//
// Below here is a basic implementation of a GObject type
//

// "public" header

G_BEGIN_DECLS

#define FOO_TYPE_BAR foo_bar_get_type ()
G_DECLARE_FINAL_TYPE (FooBar, foo_bar, FOO, BAR, GObject)

FooBar *foo_bar_new (void);

G_END_DECLS

// private implementation

struct _FooBar {
    GObject parent_instance;

    gchar *name;

    guint id;
};

G_DEFINE_TYPE (FooBar, foo_bar, G_TYPE_OBJECT)

enum
{
  PROP_NAME = 1,
  PROP_ID,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void foo_bar_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
    FooBar *self = FOO_BAR (object);

    switch (property_id) {
        case PROP_NAME:
            g_free(self->name);
            self->name = g_value_dup_string(value);
            break;

        case PROP_ID:
            self->id = g_value_get_uint(value);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void foo_bar_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
    FooBar *self = FOO_BAR(object);

    switch (property_id) {
        case PROP_NAME:
            g_value_set_string(value, self->name);
            break;

        case PROP_ID:
            g_value_set_uint(value, self->id);
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void foo_bar_finalize (GObject *gobject) {
    FooBar* self = FOO_BAR(gobject);

    g_free (self->name);

    G_OBJECT_CLASS (foo_bar_parent_class)->finalize (gobject);
}

static void foo_bar_class_init (FooBarClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->set_property = foo_bar_set_property;
    object_class->get_property = foo_bar_get_property;
    object_class->finalize = foo_bar_finalize;

    obj_properties[PROP_NAME] =
      g_param_spec_string ("name",
                           "Name",
                           "Name of the file to load and display from.",
                           "default-name"  /* default value */,
                           (GParamFlags) (G_PARAM_READWRITE));

    obj_properties[PROP_ID] =
      g_param_spec_uint ("id",
                         "ID",
                         "ID of this dummy class",
                         0  /* minimum value */,
                         10 /* maximum value */,
                         2  /* default value */,
                         (GParamFlags) G_PARAM_READWRITE);

    g_object_class_install_properties (object_class,
                                       N_PROPERTIES,
                                       obj_properties);
}

static void foo_bar_init (FooBar *) {
}

FooBar *foo_bar_new (const gchar* const name, guint id) {
    return FOO_BAR(g_object_new(FOO_TYPE_BAR, "name", name, "id", id, NULL));
}

//
// Test cases
//

typedef pair<const char*, guint> GObjectMemoryMakeSharedTestParam;

class GObjectMemoryMakeHelperMethodsTest: public testing::TestWithParam<GObjectMemoryMakeSharedTestParam> {
protected:
    /**
     * We test for multiple properties so that we can be sure the various
     * helper methods correctly pass through different data types and
     * multiple combinations of arguments correctly.
     */
    static void checkProperties(gpointer obj, const char* expectedName, guint expectedId) {
        char* name = NULL;
        guint id = 0;

        g_object_get(obj, "name", &name, "id", &id, NULL);
        EXPECT_STREQ(expectedName, name);
        EXPECT_EQ(expectedId, id);

        g_free(name);
    }
};

TEST_P(GObjectMemoryMakeHelperMethodsTest, make_gobject_passes_arguments)
{
    auto p = GetParam();
    auto obj = make_gobject<FooBar>(FOO_TYPE_BAR, "name", p.first, "id", p.second, nullptr);
    checkProperties(obj.get(), p.first, p.second);
}

TEST_P(GObjectMemoryMakeHelperMethodsTest, make_gobject_no_arguments)
{
    auto p = GetParam();
    auto obj = make_gobject<FooBar>(FOO_TYPE_BAR, nullptr);
    g_object_set(obj.get(), "name", p.first, "id", p.second, nullptr);
    checkProperties(obj.get(), p.first, p.second);
}

TEST_P(GObjectMemoryMakeHelperMethodsTest, foo_bar_new)
{
    auto p = GetParam();
    auto obj = gobj_ptr<FooBar>(foo_bar_new(p.first,p.second));
    checkProperties(obj.get(), p.first, p.second);
}

TEST_P(GObjectMemoryMakeHelperMethodsTest, share_gobject_from_gobj_ptr)
{
    auto p = GetParam();
    auto obj = share_gobject(make_gobject<FooBar>(FOO_TYPE_BAR, "name", p.first, "id", p.second, nullptr));
    checkProperties(obj.get(), p.first, p.second);
}

TEST_P(GObjectMemoryMakeHelperMethodsTest, share_gobject_from_raw_gobject)
{
    auto p = GetParam();
    auto obj = share_gobject(foo_bar_new(p.first, p.second));
    checkProperties(obj.get(), p.first, p.second);
}

INSTANTIATE_TEST_CASE_P(BunchOfNames,
                        GObjectMemoryMakeHelperMethodsTest,
                        ::testing::Values(GObjectMemoryMakeSharedTestParam{"meeny", 1},
                                          GObjectMemoryMakeSharedTestParam{"miny", 2},
                                          GObjectMemoryMakeSharedTestParam{"moe", 3}));

}
