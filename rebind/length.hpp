/*
 * length.hpp               -- impl length rebinder
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

#ifndef __REBIND__LENGTH_HPP__2012_05_17__
#define __REBIND__LENGTH_HPP__2012_05_17__

#include <impls/impl.hpp>
#include <tags/length.hpp>

#include "result.hpp"

namespace yarr {
    namespace impls {
        namespace rebind {
            template <class Config, class Impl, class Allocator,
                class Category>
            struct length;

            template <class Config, class Impl, class Allocator>
            struct length<Config, Impl, Allocator, tags::length::endless>:
                result<Config, Impl, Allocator,
                    typename Config::result::category>
            {
                length(Impl* impl, const Allocator& allocator)
                    : result<Config, Impl, Allocator,
                        typename Config::result::category>(impl, allocator)
                {
                }
            };

            template <class Config, class Impl, class Allocator>
            struct length<Config, Impl, Allocator, tags::length::unlimited>:
                result<Config, Impl, Allocator,
                    typename Config::result::category>
            {
                length(Impl* impl, const Allocator& allocator)
                    : result<Config, Impl, Allocator,
                        typename Config::result::category>(impl, allocator)
                {
                }

                bool empty() const {
                    return this->get()->empty();
                }
            };

            template <class Config, class Impl, class Allocator>
            struct length<Config, Impl, Allocator, tags::length::limited>:
                length<Config, Impl, Allocator, tags::length::unlimited>
            {
                typedef typename impl<Config>::size_type size_type;

                length(Impl* impl, const Allocator& allocator)
                    : length<Config, Impl, Allocator, tags::length::unlimited>(
                        impl, allocator)
                {
                }

                size_type size() const {
                    return this->get()->size();
                }
            };
        }
    }
}

#endif

