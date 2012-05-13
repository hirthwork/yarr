/*
 * length.hpp               -- implementation length functions builder
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

#ifndef __IMPLS__LENGTH_HPP__2012_05_08__
#define __IMPLS__LENGTH_HPP__2012_05_08__

#include <tags/length.hpp>

#include "result.hpp"

namespace yarr {
    namespace impls {
        template <class Config, class Category>
        struct length;

        template <class Config>
        struct length<Config, tags::length::endless>:
            result<Config, typename Config::result::category>
        {
        };

        template <class Config>
        struct length<Config, tags::length::unlimited>:
            result<Config, typename Config::result::category>
        {
            virtual bool empty() const = 0;
        };

        template <class Config>
        struct length<Config, tags::length::limited>:
            length<Config, tags::length::unlimited>
        {
            typedef typename Config::length::size_type size_type;
            virtual size_type size() const = 0;
        };
    }
}

#endif

