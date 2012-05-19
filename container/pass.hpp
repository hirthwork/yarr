/*
 * pass.hpp                 -- container wrapper pass impl
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

#ifndef __CONTAINTER__PASS_HPP__2012_05_13__
#define __CONTAINTER__PASS_HPP__2012_05_13__

#include <impls/impl.hpp>
#include <tags/pass.hpp>

#include "order.hpp"

namespace yarr {
    namespace impls {
        namespace container {
            template <class Config, class InputIterator, class Allocator,
                class Category>
            struct pass;

            template <class Config, class InputIterator, class Allocator>
            struct pass<Config, InputIterator, Allocator,
                tags::pass::one_pass>:
                    order<Config, InputIterator, Allocator,
                        typename Config::order::category>
            {
                pass(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : order<Config, InputIterator, Allocator,
                        typename Config::order::category>(first, last,
                            allocator)
                {
                }

                typename impls::impl<Config>::result_type
                next() {
                    return *this->first++;
                }
            };

            template <class Config, class InputIterator, class Allocator>
            struct pass<Config, InputIterator, Allocator,
                tags::pass::swappable>:
                    pass<Config, InputIterator, Allocator,
                        tags::pass::one_pass>
            {
                pass(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : pass<Config, InputIterator, Allocator,
                        tags::pass::one_pass>(first, last, allocator)
                {
                }
            };

            template <class Config, class InputIterator, class Allocator>
            struct pass<Config, InputIterator, Allocator,
                tags::pass::forward>:
                    pass<Config, InputIterator, Allocator,
                        tags::pass::swappable>
            {
                pass(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : pass<Config, InputIterator, Allocator,
                        tags::pass::swappable>(first, last, allocator)
                {
                }

                typename impls::impl<Config>::result_type
                front() const {
                    return *this->first;
                }

                void pop() {
                    ++this->first;
                }
            };

            // NOTE: double ended containers assumes bidirectional iterators
            template <class Config, class InputIterator, class Allocator>
            struct pass<Config, InputIterator, Allocator,
                tags::pass::double_ended>:
                    pass<Config, InputIterator, Allocator, tags::pass::forward>
            {
                pass(InputIterator first, InputIterator last,
                    const Allocator& allocator)
                    : pass<Config, InputIterator, Allocator,
                        tags::pass::forward>(first, last, allocator)
                {
                }

                typename impls::impl<Config>::result_type
                prev() {
                    return *--this->last;
                }

                typename impls::impl<Config>::result_type
                back() const {
                    InputIterator iter = this->last;
                    return *--iter;
                }

                void pop_back() {
                    --this->last;
                }
            };
        }
    }
}

#endif

