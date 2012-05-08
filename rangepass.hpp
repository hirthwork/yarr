/*
 * rangepass.hpp            -- range function for pass tags
 *
 * Copyright (C) 2012 Dmitry Potapov <potapov.d@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __RANGEPASS_HPP_2012_05_07__
#define __RANGEPASS_HPP_2012_05_07__

#include "rangeorder.hpp"
#include "passtags.hpp"

namespace yarr {
    template <class impl_type, class Allocator, class category>
    struct range_pass;

    // Pre: there should be impl_holder on the top of hierarchy, which forbids
    // copy costruction and copy assignment
    template <class impl_type, class Allocator>
    struct range_pass<impl_type, Allocator, tags::pass::one_pass>:
        range_order<impl_type, Allocator, typename impl_type::order_category>
    {
        range_pass(const Allocator& allocator)
            : range_order<impl_type, Allocator,
                typename impl_type::order_category>(allocator)
        {
        }

        typename range_order<impl_type, Allocator,
            typename impl_type::order_category>::result_type next()
        {
            return this->get()->next();
        }
    };

    template <class impl_type, class Allocator>
    struct range_pass<impl_type, Allocator, tags::pass::swappable>:
        range_pass<impl_type, Allocator, tags::pass::one_pass>
    {
        range_pass(const Allocator& allocator)
            : range_pass<impl_type, Allocator, tags::pass::one_pass>(allocator)
        {
        }

        using impl_holder<impl_type, Allocator>::swap;
    };

    template <class impl_type, class Allocator>
    struct range_pass<impl_type, Allocator, tags::pass::forward>:
        range_pass<impl_type, Allocator, tags::pass::swappable>
    {
        range_pass(const Allocator& allocator)
            : range_pass<impl_type, Allocator, tags::pass::swappable>(
                allocator)
        {
        }

        typename range_pass<impl_type, Allocator,
            tags::pass::swappable>::result_type front() const
        {
            return this->get()->front();
        }

        void pop() {
            this->get()->pop();
        }
    };

    template <class impl_type, class Allocator>
    struct range_pass<impl_type, Allocator, tags::pass::double_ended>:
        range_pass<impl_type, Allocator, tags::pass::forward>
    {
        range_pass(const Allocator& allocator)
            : range_pass<impl_type, Allocator, tags::pass::forward>(allocator)
        {
        }

        typename range_pass<impl_type, Allocator,
            tags::pass::forward>::result_type back() const
        {
            return this->get()->back();
        }

        void pop_back() {
            this->get()->pop_back();
        }

        void pop_front() {
            this->pop();
        }
    };
}

#endif

