/*
 * issame.hpp               -- class hierarchy type traits
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

#ifndef __UTILS__ISSAME_HPP__2012_05_13__
#define __UTILS__ISSAME_HPP__2012_05_13__

namespace yarr {
    template <class T, class U>
    struct is_same {
        static const bool value = false;
    };

    template <class T>
    struct is_same<T, T> {
        static const bool value = true;
    };
}

#endif

