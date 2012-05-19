/*
 * result.hpp               -- container wrapper result impl
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

#ifndef __CONTAINTER__RESULT_HPP__2012_05_13__
#define __CONTAINTER__RESULT_HPP__2012_05_13__

#include <impls/impl.hpp>
#include <tags/result.hpp>

namespace yarr {
    namespace impls {
        namespace container {
            template <class Config, class InputIterator, class Allocator,
                class Category>
            class result;

            template <class Config, class InputIterator, class Allocator>
            class result<Config, InputIterator, Allocator,
                tags::result::value>: public impl<Config>, public Allocator
            {
            protected:
                InputIterator first;
                InputIterator last;

            public:
                result(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : Allocator(allocator)
                    , first(first)
                    , last(last)
                {
                }

                void set_allocator(const Allocator& allocator) {
                    Allocator::operator =(allocator);
                }
            };

            template <class Config, class InputIterator, class Allocator>
            struct result<Config, InputIterator, Allocator,
                tags::result::reference>:
                    result<Config, InputIterator, Allocator,
                        tags::result::value>
            {
                result(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : result<Config, InputIterator, Allocator,
                        tags::result::value>(first, last, allocator)
                {
                }
            };

            template <class Config, class InputIterator, class Allocator>
            struct result<Config, InputIterator, Allocator,
                tags::result::solid>:
                    result<Config, InputIterator, Allocator,
                        tags::result::reference>
            {
                result(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : result<Config, InputIterator, Allocator,
                        tags::result::reference>(first, last, allocator)
                {
                }
            };
        }
    }
}

#endif

