/*
 * rangeresult.hpp          -- range function for result tags
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

#ifndef __RANGERESULT_HPP_2012_05_07__
#define __RANGERESULT_HPP_2012_05_07__

#include "implholder.hpp"
#include "resulttags.hpp"

namespace yarr {
    template <class Impl, class Allocator, class Category>
    struct range_result;

    template <class Impl, class Allocator>
    struct range_result<Impl, Allocator, tags::result::value>:
        impl_holder<Impl, Allocator>
    {
        typedef typename Impl::result_type result_type;

        range_result(const Allocator& allocator)
            : impl_holder<Impl, Allocator>(allocator)
        {
        }
    };

    template <class Impl, class Allocator>
    struct range_result<Impl, Allocator, tags::result::reference>:
        range_result<Impl, Allocator, tags::result::value>
    {
        range_result(const Allocator& allocator)
            : range_result<Impl, Allocator, tags::result::value>(
                allocator)
        {
        }
    };

    template <class Impl, class Allocator>
    struct range_result<Impl, Allocator, tags::result::solid>:
        range_result<Impl, Allocator, tags::result::reference>
    {
        range_result(const Allocator& allocator)
            : range_result<Impl, Allocator, tags::result::reference>(
                allocator)
        {
        }
    };
}

#endif

