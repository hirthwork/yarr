/*
 * iotype.hpp               -- ranges concatenation iotype implementation
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

#ifndef __CONCAT__IOTYPE_HPP__2012_05_20__
#define __CONCAT__IOTYPE_HPP__2012_05_20__

#include <tags/iotype.hpp>

#include "length.hpp"

namespace yarr {
    namespace impls {
        namespace concat {
            template <class Config, class Impl1, class Impl2, class Allocator,
                class Category>
            struct iotype;

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct iotype<Config, Impl1, Impl2, Allocator,
                tags::iotype::input>:
                    length<Config, Impl1, Impl2, Allocator,
                        typename Config::length::category>
            {
                iotype(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : length<Config, Impl1, Impl2, Allocator,
                        typename Config::length::category>(impl1, impl2,
                            allocator)
                {
                }
            };

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct iotype<Config, Impl1, Impl2, Allocator,
                tags::iotype::output>:
                    length<Config, Impl1, Impl2, Allocator,
                        typename Config::length::category>
            {
                iotype(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : length<Config, Impl1, Impl2, Allocator,
                        typename Config::length::category>(impl1, impl2,
                            allocator)
                {
                }
            };

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct iotype<Config, Impl1, Impl2, Allocator,
                tags::iotype::input_output>:
                    length<Config, Impl1, Impl2, Allocator,
                        typename Config::length::category>
            {
                iotype(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : length<Config, Impl1, Impl2, Allocator,
                        typename Config::length::category>(impl1, impl2,
                            allocator)
                {
                }
            };
        }
    }
}

#endif

