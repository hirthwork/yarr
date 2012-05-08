/*
 * ordertags.hpp            -- range order tags
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

#ifndef __ORDERTAGS_HPP_2012_05_08__
#define __ORDERTAGS_HPP_2012_05_08__

namespace yarr {
    namespace tags {
        // access order tags
        // defines order in which elements of range can be accessed
        namespace order {
            // elements of such ranges can be accesses one by one using
            // front(), next() or back() functions
            struct sequental {};

            // in addition to sequental ranges element access functions, random
            // access ranges provides operator[] function
            struct random: sequental {};
        }
    }
}

#endif

