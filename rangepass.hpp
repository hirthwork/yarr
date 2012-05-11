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

#include <functional>

#include <assert/predicates.hpp>

#include <reinvented-wheels/enableif.hpp>

#include "isbase.hpp"
#include "passtags.hpp"
#include "rangeorder.hpp"
#include "sizetags.hpp"

namespace yarr {
    namespace aux {
        template <class Range, class Message>
        typename reinvented_wheels::enable_if<is_base<tags::size::endless,
            typename Range::impl_type::config_type::size::category>::value
            >::type
        check_not_empty(const Range*, Message) {
        }

        template <class Range, class Message>
        typename reinvented_wheels::enable_if<is_base<tags::size::unlimited,
            typename Range::impl_type::config_type::size::category>::value
            >::type
        check_not_empty(const Range* range, Message message) {
            typedef typename Range::impl_type::config_type::assert_type
                assert_type;
            assert_type::assert(assert::bind(std::logical_not<bool>(),
                assert::bind(range, &Range::empty)), message);
        }
    }

    template <class Impl, class Category>
    struct range_pass;

    template <class Impl>
    struct range_pass<Impl, tags::pass::one_pass>:
        range_order<Impl, typename Impl::config_type::order::category>
    {
        range_pass(Impl* impl)
            : range_order<Impl, typename Impl::config_type::order::category>(
                impl)
        {
        }

        typename range_order<Impl,
            typename Impl::config_type::order::category>::result_type
        next()
        {
            aux::check_not_empty(this, "next() called on empty range");
            return this->get()->next();
        }
    };

    template <class Impl>
    struct range_pass<Impl, tags::pass::swappable>:
        range_pass<Impl, tags::pass::one_pass>
    {
        range_pass(Impl* impl)
            : range_pass<Impl, tags::pass::one_pass>(impl)
        {
        }

        using impl_holder<Impl>::swap;
    };

    template <class Impl>
    struct range_pass<Impl, tags::pass::forward>:
        range_pass<Impl, tags::pass::swappable>
    {
        range_pass(Impl* impl)
            : range_pass<Impl, tags::pass::swappable>(impl)
        {
        }

        typename range_pass<Impl, tags::pass::swappable>::result_type
        front() const
        {
            aux::check_not_empty(this, "front() called on empty range");
            return this->get()->front();
        }

        void pop() {
            aux::check_not_empty(this, "pop() called on empty range");
            this->get()->pop();
        }
    };

    template <class Impl>
    struct range_pass<Impl, tags::pass::double_ended>:
        range_pass<Impl, tags::pass::forward>
    {
        range_pass(Impl* impl)
            : range_pass<Impl, tags::pass::forward>(impl)
        {
        }

        typename range_pass<Impl, tags::pass::forward>::result_type prev() {
            aux::check_not_empty(this, "prev() called on empty range");
            return this->get()->prev();
        }

        typename range_pass<Impl, tags::pass::forward>::result_type
        back() const
        {
            aux::check_not_empty(this, "back() called on empty range");
            return this->get()->back();
        }

        void pop_back() {
            aux::check_not_empty(this, "pop_back() called on empty range");
            this->get()->pop_back();
        }

        void pop_front() {
            this->pop();
        }
    };
}

#endif

