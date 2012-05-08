/*
 * orderconfig.hpp          -- order tag configuration trait
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

#ifndef __ORDERCONFIG_HPP_2012_05_08__
#define __ORDERCONFIG_HPP_2012_05_08__

#include "ordertags.hpp"

namespace yarr {
    template <class Category, class = void>
    struct order_config;

    template <>
    struct order_config<tags::order::sequental, void> {
        typedef tags::order::sequental category;
    };

    template <class PosType>
    struct order_config<tags::order::random, PosType> {
        typedef tags::order::random category;
        typedef PosType pos_type;
    };
}

#endif

