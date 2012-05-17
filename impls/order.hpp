/*
 * order.hpp                -- implementation order functions builder
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

#ifndef __IMPLS__ORDER_HPP__2012_05_08__
#define __IMPLS__ORDER_HPP__2012_05_08__

#include <tags/order.hpp>
#include <tags/pass.hpp>
#include <utils/isbase.hpp>

#include "iotype.hpp"

namespace yarr {
    namespace impls {
        template <class Config, class Category>
        struct order;

        template <class Config>
        struct order<Config, tags::order::sequential>:
            iotype<Config, typename Config::iotype::category>
        {
        };

        namespace aux {
            template <class Config, bool>
            struct order: impls::order<Config, tags::order::sequential> {
                typedef typename Config::order::pos_type pos_type;

                virtual typename Config::result::result_type
                at(pos_type pos) const = 0;

                virtual void skip(pos_type n) = 0;
            };

            template <class Config>
            struct order<Config, true>: order<Config, false> {
                typedef typename Config::order::pos_type pos_type;

                virtual typename Config::result::result_type
                rat(pos_type pos) const = 0;

                virtual void truncate(pos_type n) = 0;
            };
        }

        template <class Config>
        struct order<Config, tags::order::random>:
            aux::order<Config, is_base<tags::pass::double_ended,
                typename Config::pass::category>::value>
        {
        };
    }
}

#endif

