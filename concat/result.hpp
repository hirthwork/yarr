/*
 * result.hpp               -- ranges concatenation result implementation
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

#ifndef __CONCAT__RESULT_HPP__2012_05_20__
#define __CONCAT__RESULT_HPP__2012_05_20__

#include <impls/holder.hpp>
#include <impls/impl.hpp>
#include <tags/result.hpp>
#include <utils/proxy.hpp>

namespace yarr {
    namespace impls {
        namespace concat {
            template <class Config, class Impl1, class Impl2, class Allocator,
                class Category>
            class result;

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct result<Config, Impl1, Impl2, Allocator,
                tags::result::value>:
                    impl<Config>,
                    first<holder<Impl1> >,
                    second<holder<Impl2> >,
                    Allocator
            {
                result(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : first<holder<Impl1> >(impl1)
                    , second<holder<Impl2> >(impl2)
                    , Allocator(allocator)
                {
                }

                void set_allocator(const Allocator& allocator) {
                    Allocator::operator =(allocator);
                }
            };

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct result<Config, Impl1, Impl2, Allocator,
                tags::result::reference>:
                    result<Config, Impl1, Impl2, Allocator,
                        tags::result::value>
            {
                result(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : result<Config, Impl1, Impl2, Allocator,
                        tags::result::value>(impl1, impl2, allocator)
                {
                }
            };

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct result<Config, Impl1, Impl2, Allocator,
                tags::result::solid>:
                    result<Config, Impl1, Impl2, Allocator,
                        tags::result::reference>
            {
                result(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : result<Config, Impl1, Impl2, Allocator,
                        tags::result::reference>(impl1, impl2, allocator)
                {
                }
            };
        }
    }
}

#endif

