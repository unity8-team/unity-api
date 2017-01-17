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

#ifndef UNITY_UTIL_GOBJECTMEMORY_H
#define UNITY_UTIL_GOBJECTMEMORY_H

#include <memory>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wcast-qual"
#include <glib-object.h>

namespace unity
{

namespace util
{

/**
 * This class is meant for automatically managing the lifetime of C objects derived
 * from gobject. Its API perfectly mirrors the API of unique_ptr except that you
 * can't define your own deleter function as it is always g_object_unref.
 *
 * API/ABI stability is not guaranteed. If you need to pass the object across an ABI
 * boundary, pass the plain gobject.
 *
 * This is how you would use gobj_ptr 99% of the time:
 * \code{.cpp}
 * gobj_ptr<GSomeType> o(g_some_type_new(...));
 * \endcode
 *
 * There are also helper functions, in-case your GObject class doesn't have a factory
 * method:
 * \code{.cpp}
 * make_gobject<GSomeType>(G_TYPE_SOME, nullptr);
 * \endcode
 *
 * More specifically, the object will decrement the gobject reference count
 * of the object it points to when it goes out of scope. It will never increment it.
 * Thus you should only assign to it when already holding a reference. gobj_ptr
 * will then take ownership of that particular reference.
 *
 * Floating gobjects can not be put in this container as they are meant to be put
 * into native gobject aware containers immediately upon construction. Trying to insert
 * a floating gobject into a gobj_ptr will throw an invalid_argument exception. To
 * prevent accidental memory leaks, the floating gobject is unreffed in this case.
 */
template <typename T>
class gobj_ptr final
{
private:
    T* u;

    void validate_float(T* t)
    {
        if (t != nullptr && g_object_is_floating(G_OBJECT(t)))
        {
            // LCOV_EXCL_START  // False negative from gcovr.
            throw std::invalid_argument("Tried to add a floating gobject into a gobj_ptr.");
            // LCOV_EXCL_STOP
        }
    }

public:
    typedef T element_type;
    typedef T* pointer;
    typedef decltype(g_object_unref) deleter_type;

    constexpr gobj_ptr() noexcept : u(nullptr)
    {
    }

    explicit gobj_ptr(T* t)
        : u(t)
    {
        // What should we do if validate throws? Unreffing unknown objs
        // is dodgy but not unreffing runs the risk of
        // memory leaks. Currently unrefs as u is destroyed
        // when this exception is thrown.
        validate_float(t);
    }

    constexpr gobj_ptr(std::nullptr_t) noexcept : u(nullptr){};
    gobj_ptr(gobj_ptr&& o) noexcept
    {
        u = o.u;
        o.u = nullptr;
    }

    gobj_ptr(const gobj_ptr& o)
        : u(nullptr)
    {
        *this = o;
    }

    gobj_ptr& operator=(const gobj_ptr& o)
    {
        if (o.u != nullptr)
        {
            g_object_ref(o.u);
        }
        reset(o.u);
        return *this;
    }

    ~gobj_ptr()
    {
        reset();
    }

    deleter_type& get_deleter() noexcept
    {
        return g_object_unref;
    }

    deleter_type& get_deleter() const noexcept
    {
        return g_object_unref;
    }

    void swap(gobj_ptr<T>& o) noexcept
    {
        T* tmp = u;
        u = o.u;
        o.u = tmp;
    }

    void reset(pointer p = pointer())
    {
        if (u != nullptr)
        {
            g_object_unref(G_OBJECT(u));
            u = nullptr;
        }
        // Same throw dilemma as in pointer constructor.
        u = p;
        validate_float(p);
    }

    T* release() noexcept
    {
        T* r = u;
        u = nullptr;
        return r;
    }

    T* get() const noexcept
    {
        return u;
    }

    T& operator*() const
    {
        return *u;
    }

    T* operator->() const noexcept
    {
        return u;
    }

    explicit operator bool() const noexcept
    {
        return u != nullptr;
    }

    gobj_ptr& operator=(gobj_ptr&& o) noexcept
    {
        reset();
        u = o.u;
        o.u = nullptr;
        return *this;
    }

    gobj_ptr& operator=(std::nullptr_t) noexcept
    {
        reset();
        return *this;
    }

    bool operator==(const gobj_ptr<T>& o) const noexcept
    {
        return u == o.u;
    }

    bool operator!=(const gobj_ptr<T>& o) const noexcept
    {
        return u != o.u;
    }

    bool operator<(const gobj_ptr<T>& o) const noexcept
    {
        return u < o.u;
    }

    bool operator<=(const gobj_ptr<T>& o) const noexcept
    {
        return u <= o.u;
    }

    bool operator>(const gobj_ptr<T>& o) const noexcept
    {
        return u > o.u;
    }

    bool operator>=(const gobj_ptr<T>& o) const noexcept
    {
        return u >= o.u;
    }
};

/**
\brief Helper method to construct a gobj_ptr-wrapped GObject class.

Uses the same signature as the g_object_new() method.

Example:
\code{.cpp}
auto obj = make_gobject<FooBar>(FOO_TYPE_BAR, "name", "banana", nullptr);
\endcode
*/
template<typename T, typename... Args>
inline gobj_ptr<T> make_gobject(GType object_type, const gchar *first_property_name, Args&&... args)
{
    return gobj_ptr<T>(G_TYPE_CHECK_INSTANCE_CAST(g_object_new(object_type, first_property_name, std::forward<Args>(args)...), object_type, T));
}

/**
\brief Used by the make_gobject and share_gobject as the shared_ptr's deleter.

Useful if for some reason the normal helper methods are not suitable for your needs.

Example:
\code{.cpp}
auto obj = shared_ptr<FooBar>(foo_bar_new("name"), &g_object_deleter);
\endcode
*/
inline void g_object_deleter(void *ptr) {
    g_return_if_fail(G_IS_OBJECT(ptr));
    g_object_unref(ptr);
}

/**
\brief Helper method to wrap a shared_ptr around an existing GObject.

Useful if the GObject class you are constructing already has a
dedicated factory from the C library it comes from, and you
intend to share it.

Example:
\code{.cpp}
auto obj = share_gobject<FooBar>(foo_bar_new("name"));
\endcode
*/
template<typename T>
inline std::shared_ptr<T>
share_gobject(T* ptr)
{
    return std::shared_ptr<T>(ptr, &g_object_deleter);
}

/**
\brief Helper method to convert a gobj_ptr to a shared_ptr.

Useful if the GObject class you are constructing already has a
gobj_ptr factory method, but you want to have a shared
instance.

Example:
\code{.cpp}
gobj_ptr<FooBar> newFooBar();
// ...
auto obj = share_gobject(newFooBar());
\endcode
*/
template<typename T>
inline std::shared_ptr<T>
share_gobject(gobj_ptr<T> ptr)
{
    return std::shared_ptr<T>(ptr.release(), &g_object_deleter);
}

}  // namespace until

}  // namespace unity

namespace std {

template<typename T>
    struct hash<unity::util::gobj_ptr<T>> : public __hash_base<size_t, unity::util::gobj_ptr<T>> {
        size_t operator()(const unity::util::gobj_ptr<T>& obj) const noexcept {
            typedef unity::util::gobj_ptr<T> _GP;
            return std::hash<typename _GP::pointer>()(obj.get());
        }
    };

} // namespace std

#pragma GCC diagnostic pop

#endif
