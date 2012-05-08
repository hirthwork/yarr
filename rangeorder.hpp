/*
 * rangeorder.hpp           -- range function for order tags
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

#ifndef __RANGEORDER_HPP_2012_05_07__
#define __RANGEORDER_HPP_2012_05_07__

#include "rangeiotype.hpp"
#include "ordertags.hpp"

namespace yarr {
    template <class Impl, class Allocator, class Category>
    struct range_order;

    template <class Impl, class Allocator>
    struct range_order<Impl, Allocator, tags::order::sequential>:
        range_iotype<Impl, Allocator, typename Impl::iotype_category>
    {
        range_order(const Allocator& allocator)
            : range_iotype<Impl, Allocator,
                typename Impl::iotype_category>(allocator)
        {
        }
    };

    template <class Impl, class Allocator>
    struct range_order<Impl, Allocator, tags::order::random>:
        range_order<Impl, Allocator, tags::order::sequential>
    {
        typedef typename Impl::pos_type pos_type;

        range_order(const Allocator& allocator)
            : range_order<Impl, Allocator, tags::order::sequential>(
                allocator)
        {
        }

        typename range_order<Impl, Allocator, tags::order::sequential>::
            result_type operator [](pos_type pos) const
        {
            return this->get()->operator [](pos);
        }
    };
}

#endif

