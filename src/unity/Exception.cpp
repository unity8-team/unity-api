/*
 * Copyright (C) 2012 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

#include <unity/Exception.h>
#include <unity/internal/ExceptionImpl.h>

using namespace std;

namespace unity
{

Exception::
Exception(shared_ptr<internal::ExceptionImpl> const& derived)
    : p_(derived)
{
}

Exception::
Exception(Exception const&) = default;

Exception&
Exception::
operator=(Exception const&) = default;

Exception::
~Exception() noexcept = default;

string
Exception::
reason() const
{
    return p_->reason();
}

string
Exception::
to_string(string const& indent) const
{
    return p_->to_string(*this, 0, indent);
}

string
Exception::
to_string(int indent_level, string const& indent) const
{
    return p_->to_string(*this, indent_level, indent);
}

exception_ptr
Exception::
remember(exception_ptr earlier_exception)
{
    return p_->remember(this, earlier_exception);
}

exception_ptr
Exception::
get_earlier() const noexcept
{
    return p_->get_earlier();
}

internal::ExceptionImpl*
Exception::
pimpl() const noexcept
{
    return p_.get();
}

} // namespace unity
