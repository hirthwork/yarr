/*
 * isbase.hpp               -- class hierarchy type traits
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

#ifndef __ISBASE_HPP_2012_05_07__
#define __ISBASE_HPP_2012_05_07__

namespace yarr {
    template <class base, class child>
    class is_base {
        typedef char two_chars[2];

        static char test(base*);
        static two_chars& test(...);

    public:
        static const bool value = sizeof(test((child*)0)) == 1;
    };
}

#endif

