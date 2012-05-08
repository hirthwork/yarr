/*
 * rangesize.hpp            -- range function for size tags
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

#ifndef __RANGESIZE_HPP_2012_05_06__
#define __RANGESIZE_HPP_2012_05_06__

#include "rangeresult.hpp"
#include "sizetags.hpp"

namespace yarr {
    template <class impl_type, class Allocator, class category>
    struct range_size;

    template <class impl_type, class Allocator>
    struct range_size<impl_type, Allocator, tags::size::endless>:
        range_result<impl_type, Allocator, typename impl_type::result_category>
    {
        range_size(const Allocator& allocator)
            : range_result<impl_type, Allocator,
                typename impl_type::result_category>(allocator)
        {
        }
    };

    template <class impl_type, class Allocator>
    struct range_size<impl_type, Allocator, tags::size::unlimited>:
        range_result<impl_type, Allocator, typename impl_type::result_category>
    {
        range_size(const Allocator& allocator)
            : range_result<impl_type, Allocator,
                typename impl_type::result_category>(allocator)
        {
        }

        bool empty() const {
            return !this->get() || this->get()->empty();
        }
    };

    template <class impl_type, class Allocator>
    struct range_size<impl_type, Allocator, tags::size::limited>:
        range_size<impl_type, Allocator, tags::size::unlimited>
    {
        typedef typename impl_type::size_type size_type;

        range_size(const Allocator& allocator)
            : range_size<impl_type, Allocator, tags::size::limited>(allocator)
        {
        }

        // TODO: investigate if check for get() nullness required
        size_type size() const {
            if (!this->get()) {
                return size_type();
            } else {
                return this->get()->size();
            }
        }
    };
}

#endif

