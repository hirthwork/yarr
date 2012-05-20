/*
 * result.hpp               -- impl result rebinder
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

#ifndef __REBIND__RESULT_HPP__2012_05_17__
#define __REBIND__RESULT_HPP__2012_05_17__

#include <impls/holder.hpp>
#include <impls/impl.hpp>
#include <tags/result.hpp>

namespace yarr {
    namespace impls {
        namespace rebind {
            template <class Config, class Impl, class Allocator,
                class Category>
            class result;

            template <class Config, class Impl, class Allocator>
            struct result<Config, Impl, Allocator, tags::result::value>:
                impl<Config>, holder<Impl>, Allocator
            {
                result(Impl* impl, const Allocator& allocator)
                    : holder<Impl>(impl)
                    , Allocator(allocator)
                {
                }

                void set_allocator(const Allocator& allocator) {
                    Allocator::operator =(allocator);
                }
            };

            template <class Config, class Impl, class Allocator>
            struct result<Config, Impl, Allocator, tags::result::reference>:
                result<Config, Impl, Allocator, tags::result::value>
            {
                result(Impl* impl, const Allocator& allocator)
                    : result<Config, Impl, Allocator, tags::result::value>(
                        impl, allocator)
                {
                }
            };

            template <class Config, class Impl, class Allocator>
            struct result<Config, Impl, Allocator, tags::result::solid>:
                result<Config, Impl, Allocator, tags::result::reference>
            {
                result(Impl* impl, const Allocator& allocator)
                    : result<Config, Impl, Allocator, tags::result::reference>(
                        impl, allocator)
                {
                }
            };
        }
    }
}

#endif

