/*
 * resulttags.hpp           -- range result tags
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

#ifndef __RESULTTAGS_HPP_2012_05_08__
#define __RESULTTAGS_HPP_2012_05_08__

namespace yarr {
    namespace tags {
        // return value tags
        // these tags defines category of the values returned by front(),
        // back() and operator[]
        namespace result {
            // this tag requires range to return element by value
            // ranges with this tag must provide result_type typedef,
            // which can be a reference for non-copyable objects
            struct value {};

            // ranges with this tag should return const reference from their
            // element access functions and this references must stay valid
            // until range destruction
            // these ranges must provide const_reference typedef
            struct reference: value {};

            // ranges which elements goes one-by-one in memory and can be
            // accessed by "*(&front() + n)"
            struct solid: reference {};
        }
    }
}

#endif

