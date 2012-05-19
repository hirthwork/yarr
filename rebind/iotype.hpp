/*
 * iotype.hpp               -- impl iotype rebinder
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

#ifndef __REBIND__IOTYPE_HPP__2012_05_17__
#define __REBIND__IOTYPE_HPP__2012_05_17__

#include <tags/iotype.hpp>

#include "length.hpp"

namespace yarr {
    namespace rebind {
        template <class Config, class Impl, class Allocator, class Category>
        struct iotype;

        template <class Config, class Impl, class Allocator>
        struct iotype<Config, Impl, Allocator, tags::iotype::input>:
            length<Config, Impl, Allocator, typename Config::length::category>
        {
            iotype(Impl* impl, const Allocator& allocator)
                : length<Config, Impl, Allocator,
                    typename Config::length::category>(impl, allocator)
            {
            }
        };

        template <class Config, class Impl, class Allocator>
        struct iotype<Config, Impl, Allocator, tags::iotype::output>:
            length<Config, Impl, Allocator, typename Config::length::category>
        {
            iotype(Impl* impl, const Allocator& allocator)
                : length<Config, Impl, Allocator,
                    typename Config::length::category>(impl, allocator)
            {
            }
        };

        template <class Config, class Impl, class Allocator>
        struct iotype<Config, Impl, Allocator, tags::iotype::input_output>:
            length<Config, Impl, Allocator, typename Config::length::category>
        {
            iotype(Impl* impl, const Allocator& allocator)
                : length<Config, Impl, Allocator,
                    typename Config::length::category>(impl, allocator)
            {
            }
        };
    }
}

#endif

