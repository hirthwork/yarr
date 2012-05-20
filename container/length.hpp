/*
 * length.hpp               -- container wrapper length impl
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

#ifndef __CONTAINTER__LENGTH_HPP__2012_05_13__
#define __CONTAINTER__LENGTH_HPP__2012_05_13__

#include <impls/impl.hpp>
#include <tags/length.hpp>

#include "result.hpp"

namespace yarr {
    namespace impls {
        namespace container {
            template <class Config, class InputIterator, class Allocator,
                class Category>
            struct length;

            // NOTE: There is no endless containers

            template <class Config, class InputIterator, class Allocator>
            struct length<Config, InputIterator, Allocator,
                tags::length::unlimited>:
                    result<Config, InputIterator, Allocator,
                        typename Config::result::category>
            {
                length(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : result<Config, InputIterator, Allocator,
                        typename Config::result::category>(first, last,
                            allocator)
                {
                }

                bool empty() const {
                    return this->first == this->last;
                }
            };

            // NOTE: limited containers assumes random-access iterators,
            // the converse doesn't hold
            template <class Config, class InputIterator, class Allocator>
            struct length<Config, InputIterator, Allocator,
                tags::length::limited>:
                    length<Config, InputIterator, Allocator,
                        tags::length::unlimited>
            {
                typedef typename impl<Config>::size_type size_type;

                length(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : length<Config, InputIterator, Allocator,
                        tags::length::unlimited>(first, last, allocator)
                {
                }

                size_type size() const {
                    return this->last - this->first;
                }
            };
        }
    }
}

#endif

