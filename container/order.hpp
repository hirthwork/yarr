/*
 * order.hpp                -- container wrapper order impl
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

#ifndef __CONTAINTER__ORDER_HPP__2012_05_13__
#define __CONTAINTER__ORDER_HPP__2012_05_13__

#include <impls/impl.hpp>
#include <tags/order.hpp>
#include <tags/pass.hpp>
#include <utils/isbase.hpp>

#include "iotype.hpp"

namespace yarr {
    namespace impls {
        namespace container {
            template <class Config, class InputIterator, class Allocator,
                class Category>
            struct order;

            template <class Config, class InputIterator, class Allocator>
            struct order<Config, InputIterator, Allocator,
                tags::order::sequential>:
                    iotype<Config, InputIterator, Allocator,
                        typename Config::iotype::category>
            {
                order(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : iotype<Config, InputIterator, Allocator,
                        typename Config::iotype::category>(first, last,
                            allocator)
                {
                }
            };

            namespace aux {
                template <class Config, class InputIterator, class Allocator,
                    bool>
                struct order_pass: order<Config, InputIterator, Allocator,
                    tags::order::sequential>
                {
                    order_pass(InputIterator first, InputIterator last,
                        const Allocator& allocator)
                        : order<Config, InputIterator, Allocator,
                            tags::order::sequential>(first, last, allocator)
                    {
                    }

                    typename impls::impl<Config>::result_type
                    operator [] (
                        typename impls::impl<Config>::pos_type pos) const
                    {
                        return this->first[pos];
                    }

                    void advance(typename impls::impl<Config>::pos_type n) {
                        this->first += n;
                    }
                };

                template <class Config, class InputIterator, class Allocator>
                struct order_pass<Config, InputIterator, Allocator, true>:
                    order<Config, InputIterator, Allocator,
                        tags::order::sequential>
                {
                    order_pass(InputIterator first, InputIterator last,
                        const Allocator& allocator)
                        : order<Config, InputIterator, Allocator,
                            tags::order::sequential>(first, last, allocator)
                    {
                    }

                    typename impls::impl<Config>::result_type
                    at (typename impls::impl<Config>::pos_type pos) const
                    {
                        return this->first[pos];
                    }

                    typename impls::impl<Config>::result_type
                    rat (typename impls::impl<Config>::pos_type pos) const
                    {
                        return this->last[-++pos];
                    }

                    void skip(typename impls::impl<Config>::pos_type n) {
                        this->first += n;
                    }

                    void truncate(typename impls::impl<Config>::pos_type n) {
                        this->last -= n;
                    }
                };
            }

            template <class Config, class InputIterator, class Allocator>
            struct order<Config, InputIterator, Allocator,
                tags::order::random>:
                    aux::order_pass<Config,
                        InputIterator,
                        Allocator,
                        is_base<tags::pass::double_ended,
                            typename Config::pass::category>::value >
            {
                order(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : aux::order_pass<Config,
                        InputIterator,
                        Allocator,
                        is_base<tags::pass::double_ended,
                            typename Config::pass::category>::value
                        >(first, last, allocator)
                {
                }
            };
        }
    }
}

#endif

