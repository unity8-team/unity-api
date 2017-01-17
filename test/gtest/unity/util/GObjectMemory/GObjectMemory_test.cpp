/*
 * Copyright (C) 2013-2017 Canonical Ltd.
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
 * Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>
 *              Pete Woods <pete.woods@canonical.com>
 */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wcast-qual"

#include <unity/util/GObjectMemory.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <unordered_set>

using namespace std;
using namespace unity::util;

class GObjectMemoryTest: public testing::Test {
};

TEST_F(GObjectMemoryTest, trivial) {
    gobj_ptr<GObject> basic(G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr)));
    EXPECT_TRUE(bool(basic));
    EXPECT_TRUE(G_IS_OBJECT(basic.get()));
}

TEST_F(GObjectMemoryTest, compare) {
    GObject* o1 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    GObject* o2 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    if (o1 > o2) {
        std::swap(o1, o2);
    }
    ASSERT_TRUE(o1 < o2);
    gobj_ptr<GObject> u1(o1);
    gobj_ptr<GObject> u2(o2);

    EXPECT_TRUE(!(u1 == nullptr));
    EXPECT_TRUE(u1 != nullptr);
    EXPECT_TRUE(u1 != u2);
    EXPECT_TRUE(!(u1 == u2));
    EXPECT_TRUE(u1 < u2);
    EXPECT_TRUE(!(u2 < u1));
    EXPECT_TRUE(!(u1 == u2));
    EXPECT_TRUE(!(u2 == u1));
    EXPECT_TRUE(u1 <= u2);
    EXPECT_TRUE(!(u2 <= u1));
}

// This is its own thing due to need to avoid double release.

TEST_F(GObjectMemoryTest, equality) {
    GObject* o = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    gobj_ptr<GObject> u1(o);
    g_object_ref(o);
    gobj_ptr<GObject> u2(o);
    EXPECT_TRUE(u1 == u2);
    EXPECT_TRUE(u2 == u1);
    EXPECT_TRUE(!(u1 != u2));
    EXPECT_TRUE(!(u2 != u1));
}

TEST_F(GObjectMemoryTest, release) {
    GObject* o = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    gobj_ptr<GObject> u(o);
    EXPECT_TRUE(u != nullptr);
    EXPECT_TRUE(u.get() != nullptr);
    EXPECT_TRUE(o == u.release());
    EXPECT_TRUE(!u);
    EXPECT_TRUE(u.get() == nullptr);
    g_object_unref(o);
}

TEST_F(GObjectMemoryTest, refcount) {
    GObject* o = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    EXPECT_EQ(1, o->ref_count);
    g_object_ref(o);

    {
        EXPECT_EQ(2, o->ref_count);
        gobj_ptr<GObject> u(o);
        EXPECT_EQ(2, o->ref_count);
        // Now it dies and refcount is reduced.
    }

    EXPECT_EQ(1, o->ref_count);
    g_object_unref(o);
}

TEST_F(GObjectMemoryTest, copy) {
    GObject* o = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    gobj_ptr<GObject> u(o);
    EXPECT_EQ(1, u->ref_count);
    gobj_ptr<GObject> u2(u);
    EXPECT_EQ(2, u->ref_count);
    gobj_ptr<GObject> u3 = u2;
    EXPECT_EQ(3, u->ref_count);
    u3.reset();
    u2.reset();
    EXPECT_EQ(1, u->ref_count);
}

TEST_F(GObjectMemoryTest, swap) {
    GObject* o1 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    GObject* o2 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    gobj_ptr<GObject> u1(o1);
    gobj_ptr<GObject> u2(o2);

    u1.swap(u2);
    EXPECT_EQ(o2, u1.get());
    EXPECT_EQ(o1, u2.get());

    std::swap(u1, u2);
    EXPECT_EQ(o1, u1.get());
    EXPECT_EQ(o2, u2.get());
}

TEST_F(GObjectMemoryTest, floating) {
    GObject* o = G_OBJECT(g_object_new(G_TYPE_INITIALLY_UNOWNED, nullptr));
    try
    {
        gobj_ptr<GObject> u(o);
        FAIL();
    }
    catch (const invalid_argument& c)
    {
        EXPECT_EQ("Tried to add a floating gobject into a gobj_ptr.", string(c.what()));
    }
    // Object accepted after sinking.
    g_object_ref_sink(o);
    gobj_ptr<GObject> u(o);
}

TEST_F(GObjectMemoryTest, move) {
    GObject* o1 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    GObject* o2 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    g_object_ref(o1);
    gobj_ptr<GObject> u1(o1);
    gobj_ptr<GObject> u2(o2);
    u1 = std::move(u2);
    EXPECT_TRUE(u1.get() == o2);
    EXPECT_TRUE(!u2);
    EXPECT_TRUE(o1->ref_count == 1);
    g_object_unref(o1);
}

TEST_F(GObjectMemoryTest, null) {
    GObject* o1 = NULL;
    GObject* o3 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    gobj_ptr<GObject> u1(o1);
    gobj_ptr<GObject> u2(nullptr);
    gobj_ptr<GObject> u3(o3);

    EXPECT_TRUE(!u1);
    EXPECT_TRUE(!u2);
    u3 = nullptr;
    EXPECT_TRUE(!u3);
}

TEST_F(GObjectMemoryTest, reset) {
    GObject* o1 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    GObject* o2 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    gobj_ptr<GObject> u(o1);

    u.reset(o2);
    EXPECT_EQ(o2, u.get());
    u.reset(nullptr);
    EXPECT_TRUE(!u);
}

TEST_F(GObjectMemoryTest, sizeoftest) {
    EXPECT_EQ(sizeof(GObject*), sizeof(gobj_ptr<GObject>));
}

TEST_F(GObjectMemoryTest, deleter) {
    gobj_ptr<GObject> u1;
    EXPECT_TRUE(g_object_unref == u1.get_deleter());
}

TEST_F(GObjectMemoryTest, hash) {
    unordered_set<gobj_ptr<GObject>> s;
    auto a = make_gobject<GObject>(G_TYPE_OBJECT, nullptr);
    auto b = make_gobject<GObject>(G_TYPE_OBJECT, nullptr);
    auto c = make_gobject<GObject>(G_TYPE_OBJECT, nullptr);

    s.emplace(a);
    EXPECT_EQ(1, s.size());
    EXPECT_FALSE(s.end() == s.find(a));

    s.emplace(b);
    EXPECT_EQ(2, s.size());
    EXPECT_FALSE(s.end() == s.find(b));

    s.emplace(c);
    EXPECT_EQ(3, s.size());
    EXPECT_FALSE(s.end() == s.find(c));

    // Shouldn't add the duplicates
    s.emplace(a);
    s.emplace(b);
    s.emplace(c);
    EXPECT_EQ(3, s.size());

    s.erase(a);
    EXPECT_EQ(2, s.size());

    s.erase(b);
    EXPECT_EQ(1, s.size());

    s.erase(c);
    EXPECT_TRUE(s.empty());
}

#pragma GCC diagnostic pop
