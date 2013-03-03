/*
 * array                    array wrapping range
 *
 * Copyright (C) 2013 Dmitry Potapov <potapov.d@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef __YARR__ARRAY_HPP__2013_03_03__
#define __YARR__ARRAY_HPP__2013_03_03__

#include <cstddef>

#include "iterator.hpp"
#include "tags.hpp"

namespace yarr {
    namespace array {
        template <class T>
        struct array: iterator::impl::start<T*,
            typename iterator::impl::config<T*,
                tags::result::contiguous>::type>
        {
            template <size_t N>
            array(T (&t)[N])
                : iterator::impl::start<T*,
                    typename iterator::impl::config<T*,
                        tags::result::contiguous>::type>(t, t + N)
            {
            }
        };
    }
}

#endif

