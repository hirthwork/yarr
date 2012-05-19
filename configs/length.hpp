/*
 * length.hpp               -- length tag configuration trait
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

#ifndef __CONFIGS__LENGTH_HPP__2012_05_08__
#define __CONFIGS__LENGTH_HPP__2012_05_08__

#include <tags/length.hpp>

#include "config.hpp"

namespace yarr {
    namespace configs {
        template <class Category, class = void>
        struct length;

        template <>
        struct length<tags::length::endless, void> {
            typedef tags::length::endless category;
        };

        template <>
        struct length<tags::length::unlimited, void> {
            typedef tags::length::unlimited category;
        };

        template <class SizeType>
        struct length<tags::length::limited, SizeType> {
            typedef tags::length::limited category;
            typedef SizeType size_type;
        };

        template <class Config, class Length>
        struct set_length {
            typedef range<
                typename Config::pass,
                typename Config::order,
                typename Config::iotype,
                Length,
                typename Config::result> type;
        };
    }
}

#endif

