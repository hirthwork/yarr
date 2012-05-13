/*
 * length.hpp               -- range length tags
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

#ifndef __TAGS__LENGTH_HPP__2012_05_08__
#define __TAGS__LENGTH_HPP__2012_05_08__

namespace yarr {
    namespace tags {
        // length tags
        namespace length {
            // endless range, which always have next element.
            // for example, prime numbers returning range
            struct endless {};

            // defines ranges which is possibly unlimited, whether or no, all
            // ranges must provide empty() function
            struct unlimited {};

            // defines ranges which size can be obtained using size() function
            // provided by range
            struct limited: unlimited {};
        }
    }
}

#endif

