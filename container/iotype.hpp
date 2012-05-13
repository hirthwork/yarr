/*
 * iotype.hpp               -- container wrapper iotype impl
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

#ifndef __CONTAINTER__IOTYPE_HPP__2012_05_13__
#define __CONTAINTER__IOTYPE_HPP__2012_05_13__

#include <tags/iotype.hpp>

#include "length.hpp"

namespace yarr {
    namespace impls {
        namespace container {
            template <class Config, class InputIterator, class Allocator,
                class Category>
            struct iotype;

            template <class Config, class InputIterator, class Allocator>
            struct iotype<Config, InputIterator, Allocator,
                tags::iotype::input>:
                    length<Config, InputIterator, Allocator,
                        typename Config::length::category>
            {
                iotype(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : length<Config, InputIterator, Allocator,
                        typename Config::length::category>(first, last,
                            allocator)
                {
                }
            };

            template <class Config, class InputIterator, class Allocator>
            struct iotype<Config, InputIterator, Allocator,
                tags::iotype::output>:
                    length<Config, InputIterator, Allocator,
                        typename Config::length::category>
            {
                iotype(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : length<Config, InputIterator, Allocator,
                        typename Config::length::category>(first, last,
                            allocator)
                {
                }
            };

            template <class Config, class InputIterator, class Allocator>
            struct iotype<Config, InputIterator, Allocator,
                tags::iotype::input_output>:
                    length<Config, InputIterator, Allocator,
                        typename Config::length::category>
            {
                iotype(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : length<Config, InputIterator, Allocator,
                        typename Config::length::category>(first, last,
                            allocator)
                {
                }
            };
        }
    }
}

#endif

