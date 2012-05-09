/*
 * sizeconfig.hpp           -- size tag configuration trait
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

#ifndef __SIZECONFIG_HPP_2012_05_08__
#define __SIZECONFIG_HPP_2012_05_08__

#include "sizetags.hpp"

namespace yarr {
    namespace configs {
        template <class Category, class = void>
        struct size;

        template <>
        struct size<tags::size::endless, void> {
            typedef tags::size::endless category;
        };

        template <>
        struct size<tags::size::unlimited, void> {
            typedef tags::size::unlimited category;
        };

        template <class SizeType>
        struct size<tags::size::limited, SizeType> {
            typedef tags::size::limited category;
            typedef SizeType size_type;
        };

        template <class RangeConfig, class SizeConfig>
        struct set_size: RangeConfig {
            typedef SizeConfig size;
        };
    }
}

#endif

