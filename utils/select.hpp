/*
 * select.hpp               -- class hierarchy type traits
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

#ifndef __UTILS__SELECT_HPP__2012_05_14__
#define __UTILS__SELECT_HPP__2012_05_14__

namespace yarr {
    template <bool, class T, class U>
    struct select {
        typedef T type;
    };

    template <class T, class U>
    struct select<false, T, U> {
        typedef U type;
    };
}

#endif

