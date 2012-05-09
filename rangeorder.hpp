/*
 * rangeorder.hpp           -- range function for order tags
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

#ifndef __RANGEORDER_HPP_2012_05_07__
#define __RANGEORDER_HPP_2012_05_07__

#include <functional>

#include <assert/predicates.hpp>

#include <reinvented-wheels/enableif.hpp>

#include "isbase.hpp"
#include "ordertags.hpp"
#include "passtags.hpp"
#include "rangeiotype.hpp"
#include "sizetags.hpp"

namespace yarr {
    namespace aux {
        template <class Range, class Message>
        typename reinvented_wheels::enable_if<is_base<tags::size::endless,
            typename Range::impl_type::size_category>::value>::type
        check_bounds(const Range*,
            typename Range::impl_type::config_type::order_config::pos_type,
            Message)
        {
        }

        template <class Range, class Message>
        typename reinvented_wheels::enable_if<is_base<tags::size::limited,
            typename Range::impl_type::size_category>::value
            && !is_base<tags::pass::double_ended,
                typename Range::impl_type::pass_category>::value>::type
        check_bounds(const Range* range,
            typename Range::impl_type::config_type::order_config::pos_type pos,
            Message message)
        {
            typedef typename
                Range::impl_type::config_type::order_config::pos_type pos_type;
            typedef typename
                Range::impl_type::config_type::assert_type assert_type;
            assert_type::out_of_range_assert(
                assert::bind(std::less<pos_type>(),
                    assert::bind(pos), assert::bind(range, &Range::size)),
                message);
        }

        template <class Range, class Message>
        typename reinvented_wheels::enable_if<is_base<tags::size::limited,
            typename Range::impl_type::size_category>::value
            && is_base<tags::pass::double_ended,
                typename Range::impl_type::pass_category>::value>::type
        check_bounds(const Range* range,
            typename Range::impl_type::config_type::order_config::pos_type pos,
            Message message)
        {
            typedef typename
                Range::impl_type::config_type::order_config::pos_type pos_type;
            typedef typename
                Range::impl_type::config_type::assert_type assert_type;
            assert_type::out_of_range_assert(
                assert::select(
                    assert::bind(std::less<pos_type>(),
                        assert::bind(pos), assert::const_value<pos_type>()),
                    assert::bind(std::less_equal<pos_type>(),
                        assert::bind(std::negate<pos_type>(),
                            assert::bind(pos)),
                        assert::bind(range, &Range::size)),
                    assert::bind(std::less<pos_type>(), bind(pos),
                        assert::bind(range, &Range::size))),
                message);
        }
    }

    template <class Impl, class Allocator, class Category>
    struct range_order;

    template <class Impl, class Allocator>
    struct range_order<Impl, Allocator, tags::order::sequential>:
        range_iotype<Impl, Allocator, typename Impl::iotype_category>
    {
        range_order(const Allocator& allocator)
            : range_iotype<Impl, Allocator,
                typename Impl::iotype_category>(allocator)
        {
        }
    };

    template <class Impl, class Allocator>
    struct range_order<Impl, Allocator, tags::order::random>:
        range_order<Impl, Allocator, tags::order::sequential>
    {
        typedef typename Impl::pos_type pos_type;

        range_order(const Allocator& allocator)
            : range_order<Impl, Allocator, tags::order::sequential>(
                allocator)
        {
        }

        typename range_order<Impl, Allocator, tags::order::sequential>::
            result_type operator [](pos_type pos) const
        {
            aux::check_bounds(this, pos, "boundary check failed");
            return this->get()->operator [](pos);
        }
    };
}

#endif

