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

#include <assert/nullarypredicates.hpp>

#include "rangeorder.hpp"
#include "passtags.hpp"

namespace yarr {
    template <class Impl, class Allocator, class Category>
    struct range_pass;

    // Pre: there should be impl_holder on the top of hierarchy, which forbids
    // copy costruction and copy assignment
    template <class Impl, class Allocator>
    struct range_pass<Impl, Allocator, tags::pass::one_pass>:
        range_order<Impl, Allocator, typename Impl::order_category>
    {
        range_pass(const Allocator& allocator)
            : range_order<Impl, Allocator,
                typename Impl::order_category>(allocator)
        {
        }

        typename range_order<Impl, Allocator,
            typename Impl::order_category>::result_type next()
        {
            /*typedef typename Impl::assert_type assert_type;
            assert_type::assert(
                assert::negate(assert::bind(this, &this_type::empty)),
                "next() called on empty range");*/
            return this->get()->next();
        }
    };

    template <class Impl, class Allocator>
    struct range_pass<Impl, Allocator, tags::pass::swappable>:
        range_pass<Impl, Allocator, tags::pass::one_pass>
    {
        range_pass(const Allocator& allocator)
            : range_pass<Impl, Allocator, tags::pass::one_pass>(allocator)
        {
        }

        using impl_holder<Impl, Allocator>::swap;
    };

    template <class Impl, class Allocator>
    struct range_pass<Impl, Allocator, tags::pass::forward>:
        range_pass<Impl, Allocator, tags::pass::swappable>
    {
        range_pass(const Allocator& allocator)
            : range_pass<Impl, Allocator, tags::pass::swappable>(
                allocator)
        {
        }

        typename range_pass<Impl, Allocator,
            tags::pass::swappable>::result_type front() const
        {
            return this->get()->front();
        }

        void pop() {
            this->get()->pop();
        }
    };

    template <class Impl, class Allocator>
    struct range_pass<Impl, Allocator, tags::pass::double_ended>:
        range_pass<Impl, Allocator, tags::pass::forward>
    {
        range_pass(const Allocator& allocator)
            : range_pass<Impl, Allocator, tags::pass::forward>(allocator)
        {
        }

        typename range_pass<Impl, Allocator,
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

