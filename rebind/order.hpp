/*
 * order.hpp                -- impl order rebinder
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

#ifndef __ORDER__ORDER_HPP__2012_05_19__
#define __ORDER__ORDER_HPP__2012_05_19__

#include <impls/impl.hpp>
#include <tags/order.hpp>
#include <tags/pass.hpp>
#include <utils/isbase.hpp>

#include "iotype.hpp"

namespace yarr {
    namespace rebind {
        template <class Config, class Impl, class Allocator, class Category>
        struct order;

        template <class Config, class Impl, class Allocator>
        struct order<Config, Impl, Allocator, tags::order::sequential>:
            iotype<Config, Impl, Allocator, typename Config::iotype::category>
        {
            order(Impl* impl, const Allocator& allocator)
                : iotype<Config, Impl, Allocator,
                    typename Config::iotype::category>(impl, allocator)
            {
            }
        };

        namespace aux {
            template <class Config, class Impl, class Allocator,
                bool>
            struct order:
                rebind::order<Config, Impl, Allocator, tags::order::sequential>
            {
                typedef typename impls::impl<Config>::pos_type pos_type;
                order(Impl* impl, const Allocator& allocator)
                    : rebind::order<Config, Impl, Allocator,
                        tags::order::sequential>(impl, allocator)
                {
                }

                typename impls::impl<Config>::result_type
                at(pos_type pos) const
                {
                    return this->get()->at(pos);
                }

                void skip(pos_type n) {
                    this->get()->skip(n);
                }
            };

            template <class Config, class Impl, class Allocator>
            struct order<Config, Impl, Allocator, true>:
                order<Config, Impl, Allocator, false>
            {
                order(Impl* impl, const Allocator& allocator)
                    : order<Config, Impl, Allocator, false>(impl, allocator)
                {
                }

                typename impls::impl<Config>::result_type
                rat(typename impls::impl<Config>::pos_type pos) const
                {
                    return this->get()->rat(pos);
                }

                void truncate(typename impls::impl<Config>::pos_type n) {
                    this->get()->truncate(n);
                }
            };
        }

        template <class Config, class Impl, class Allocator>
        struct order<Config, Impl, Allocator, tags::order::random>:
                aux::order<Config,
                    Impl,
                    Allocator,
                    is_base<tags::pass::double_ended,
                        typename Config::pass::category>::value >
        {
            order(Impl* impl, const Allocator& allocator)
                : aux::order<Config,
                    Impl,
                    Allocator,
                    is_base<tags::pass::double_ended,
                        typename Config::pass::category>::value
                    >(impl, allocator)
            {
            }
        };
    }
}

#endif

