/*
 * pass.hpp                 -- impl pass rebinder
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

#ifndef __REBIND__PASS_HPP__2012_05_19__
#define __REBIND__PASS_HPP__2012_05_19__

#include <impls/impl.hpp>
#include <tags/pass.hpp>

#include "order.hpp"

namespace yarr {
    namespace impls {
        namespace rebind {
            template <class Config, class Impl, class Allocator,
                class Category>
            struct pass;

            template <class Config, class Impl, class Allocator>
            struct pass<Config, Impl, Allocator, tags::pass::one_pass>:
                order<Config, Impl, Allocator,
                    typename Config::order::category>
            {
                pass(Impl* impl, const Allocator& allocator)
                    : order<Config, Impl, Allocator,
                        typename Config::order::category>(impl, allocator)
                {
                }

                typename impls::impl<Config>::result_type
                next() {
                    return this->get()->next();
                }
            };

            template <class Config, class Impl, class Allocator>
            struct pass<Config, Impl, Allocator, tags::pass::swappable>:
                pass<Config, Impl, Allocator, tags::pass::one_pass>
            {
                pass(Impl* impl, const Allocator& allocator)
                    : pass<Config, Impl, Allocator, tags::pass::one_pass>(impl,
                        allocator)
                {
                }
            };

            template <class Config, class Impl, class Allocator>
            struct pass<Config, Impl, Allocator, tags::pass::forward>:
                pass<Config, Impl, Allocator, tags::pass::swappable>
            {
                pass(Impl* impl, const Allocator& allocator)
                    : pass<Config, Impl, Allocator, tags::pass::swappable>(
                        impl, allocator)
                {
                }

                typename impls::impl<Config>::result_type
                front() const {
                    return this->get()->front();
                }

                void pop() {
                    this->get()->pop();
                }
            };

            template <class Config, class Impl, class Allocator>
            struct pass<Config, Impl, Allocator, tags::pass::double_ended>:
                pass<Config, Impl, Allocator, tags::pass::forward>
            {
                pass(Impl* impl, const Allocator& allocator)
                    : pass<Config, Impl, Allocator, tags::pass::forward>(impl,
                        allocator)
                {
                }

                typename impls::impl<Config>::result_type
                prev() {
                    return this->get()->prev();
                }

                typename impls::impl<Config>::result_type
                back() const {
                    return this->get()->back();
                }

                void pop_back() {
                    this->get()->pop_back();
                }
            };
        }
    }
}

#endif

