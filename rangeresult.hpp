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
    template <class impl_type, class Allocator, class category>
    struct range_result;

    template <class impl_type, class Allocator>
    struct range_result<impl_type, Allocator, tags::result::value>:
        impl_holder<impl_type, Allocator>
    {
        typedef typename impl_type::result_type result_type;

        range_result(const Allocator& allocator)
            : impl_holder<impl_type, Allocator>(allocator)
        {
        }
    };

    template <class impl_type, class Allocator>
    struct range_result<impl_type, Allocator, tags::result::reference>:
        range_result<impl_type, Allocator, tags::result::value>
    {
        range_result(const Allocator& allocator)
            : range_result<impl_type, Allocator, tags::result::value>(
                allocator)
        {
        }
    };

    template <class impl_type, class Allocator>
    struct range_result<impl_type, Allocator, tags::result::solid>:
        range_result<impl_type, Allocator, tags::result::reference>
    {
        range_result(const Allocator& allocator)
            : range_result<impl_type, Allocator, tags::result::reference>(
                allocator)
        {
        }
    };
}

#endif

