/*
 * order.hpp                -- range function for order tags
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

#ifndef __RANGES__ORDER_HPP__2012_05_07__
#define __RANGES__ORDER_HPP__2012_05_07__

#include <functional>

#include <assert/predicates.hpp>

#include <reinvented-wheels/enableif.hpp>

#include <tags/length.hpp>
#include <tags/order.hpp>
#include <tags/pass.hpp>
#include <utils/isbase.hpp>

#include "iotype.hpp"

namespace yarr {
    namespace ranges {
        namespace aux {
            template <class Range, class Message>
            typename reinvented_wheels::enable_if<
                is_base<
                    tags::length::endless,
                    typename Range::impl_type::config_type::length::category
                >::value
            >::type
            check_bounds(const Range*,
                typename Range::impl_type::config_type::order::pos_type,
                Message)
            {
            }

            template <class Range, class Message>
            typename reinvented_wheels::enable_if<
                is_base<
                    tags::length::limited,
                    typename Range::impl_type::config_type::length::category
                >::value
                && !is_base<tags::pass::double_ended,
                        typename Range::impl_type::config_type::pass::category
                    >::value
                >::type
            check_bounds(const Range* range,
                typename Range::impl_type::config_type::order::pos_type pos,
                Message message)
            {
                typedef typename Range::impl_type::config_type::order::pos_type
                    pos_type;
                typedef typename Range::impl_type::config_type::assert_type
                    assert_type;
                assert_type::out_of_range(
                    assert::bind(std::less<pos_type>(),
                        assert::bind(pos), assert::bind(range, &Range::size)),
                    message);
            }

            template <class Range, class Message>
            typename reinvented_wheels::enable_if<
                is_base<
                    tags::length::limited,
                    typename Range::impl_type::config_type::length::category
                >::value
                && is_base<tags::pass::double_ended,
                        typename Range::impl_type::config_type::pass::category
                    >::value
                >::type
            check_bounds(const Range* range,
                typename Range::impl_type::config_type::order::pos_type pos,
                Message message)
            {
                typedef typename
                    Range::impl_type::config_type::order::pos_type pos_type;
                typedef typename
                    Range::impl_type::config_type::assert_type assert_type;
                assert_type::out_of_range(
                    assert::select(
                        assert::bind(std::less<pos_type>(),
                            assert::bind(pos),
                            assert::const_value<pos_type>()),
                        assert::bind(std::less_equal<pos_type>(),
                            assert::bind(std::negate<pos_type>(),
                                assert::bind(pos)),
                            assert::bind(range, &Range::size)),
                        assert::bind(std::less<pos_type>(), assert::bind(pos),
                            assert::bind(range, &Range::size))),
                    message);
            }
        }

        template <class Impl, class Category>
        struct order;

        template <class Impl>
        struct order<Impl, tags::order::sequential>:
            iotype<Impl, typename Impl::config_type::iotype::category>
        {
            order(Impl* impl)
                : iotype<Impl, typename Impl::config_type::iotype::category>(
                    impl)
            {
            }
        };

        template <class Impl>
        struct order<Impl, tags::order::random>:
            order<Impl, tags::order::sequential>
        {
            typedef typename Impl::pos_type pos_type;

            order(Impl* impl)
                : order<Impl, tags::order::sequential>(impl)
            {
            }

            typename order<Impl, tags::order::sequential>::result_type
            operator [](pos_type pos) const
            {
                aux::check_bounds(this, pos, "boundary check failed");
                return this->get()->operator [](pos);
            }

            void advance(pos_type n) {
                aux::check_bounds(this, n, "boundary check failed");
                return this->get()->advance(n);
            }
        };
    }
}

#endif

