/*
 * result.hpp               -- implementation result functions builder
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

#ifndef __IMPLS__RESULT_HPP__2012_05_08__
#define __IMPLS__RESULT_HPP__2012_05_08__

#include <tags/result.hpp>

namespace yarr {
    namespace impls {
        template <class Config, class Category>
        struct result;

        template <class Config>
        struct result<Config, tags::result::value>
        {
            typedef typename Config::result::result_type result_type;

            virtual ~result() {
            }
        };

        template <class Config>
        struct result<Config, tags::result::reference>:
            result<Config, tags::result::value>
        {
        };

        template <class Config>
        struct result<Config, tags::result::solid>:
            result<Config, tags::result::reference>
        {
        };
    }
}

#endif

