/*
 * length.hpp               -- ranges concatenation length implementation
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

#ifndef __CONCAT__LENGTH_HPP__2012_05_20__
#define __CONCAT__LENGTH_HPP__2012_05_20__

#include <impls/holder.hpp>
#include <impls/impl.hpp>
#include <tags/length.hpp>
#include <utils/proxy.hpp>

#include "result.hpp"

namespace yarr {
    namespace impls {
        namespace concat {
            template <class Config, class Impl1, class Impl2, class Allocator,
                class Category>
            struct length;

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct length<Config, Impl1, Impl2, Allocator,
                tags::length::endless>:
                    result<Config, Impl1, Impl2, Allocator,
                        typename Config::result::category>
            {
                length(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : result<Config, Impl1, Impl2, Allocator,
                        typename Config::result::category>(impl1, impl2,
                            allocator)
                {
                }
            };

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct length<Config, Impl1, Impl2, Allocator,
                tags::length::unlimited>:
                    result<Config, Impl1, Impl2, Allocator,
                        typename Config::result::category>
            {
                length(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : result<Config, Impl1, Impl2, Allocator,
                        typename Config::result::category>(impl1, impl2,
                            allocator)
                {
                }

                bool empty() const {
                    return first<holder<Impl1> >::get()->empty()
                        && second<holder<Impl2> >::get()->empty();
                }
            };

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct length<Config, Impl1, Impl2, Allocator,
                tags::length::limited>:
                    length<Config, Impl1, Impl2, Allocator,
                        tags::length::unlimited>
            {
                typedef typename impl<Config>::size_type size_type;

                length(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : length<Config, Impl1, Impl2, Allocator,
                        tags::length::unlimited>(impl1, impl2, allocator)
                {
                }

                size_type size() const {
                    return first<holder<Impl1> >::get()->size()
                        + second<holder<Impl2> >::get()->size();
                }
            };
        }
    }
}

#endif

