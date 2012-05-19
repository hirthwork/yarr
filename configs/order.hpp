/*
 * order.hpp                -- order tag configuration trait
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

#ifndef __CONFIGS__ORDER_HPP__2012_05_08__
#define __CONFIGS__ORDER_HPP__2012_05_08__

#include <tags/order.hpp>

#include "config.hpp"

namespace yarr {
    namespace configs {
        template <class Category, class = void>
        struct order;

        template <>
        struct order<tags::order::sequential, void> {
            typedef tags::order::sequential category;
        };

        template <class PosType>
        struct order<tags::order::random, PosType> {
            typedef tags::order::random category;
            typedef PosType pos_type;
        };

        template <class Config, class Order>
        struct set_order {
            typedef range<
                typename Config::pass,
                Order,
                typename Config::iotype,
                typename Config::length,
                typename Config::result> type;
        };
    }
}

#endif

