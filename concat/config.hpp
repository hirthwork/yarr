/*
 * config.hpp               -- ranges concatenation config
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

#ifndef __CONCAT__CONFIG_HPP__2012_05_20__
#define __CONCAT__CONFIG_HPP__2012_05_20__

#include <configs/config.hpp>
#include <configs/iotype.hpp>
#include <configs/length.hpp>
#include <configs/order.hpp>
#include <configs/pass.hpp>
#include <configs/result.hpp>
#include <tags/length.hpp>
#include <utils/selectweaker.hpp>

namespace yarr {
    namespace configs {
        template <class T, class U>
        struct concat {
            typedef range<
                typename concat<typename T::pass, typename U::pass>::type,
                typename concat<typename T::order, typename U::order>::type,
                typename concat<typename T::iotype, typename U::iotype>::type,
                typename concat<typename T::length, typename U::length>::type,
                typename concat<typename T::result, typename U::result>::type>
                    type;
        };
    }
}

#endif

