/*
 * rangebase.hpp            -- base range class
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

#ifndef __RANGEBASE_HPP_2012_05_06__
#define __RANGEBASE_HPP_2012_05_06__

#include "rangepass.hpp"

namespace yarr {
    template <class Impl, class Allocator>
    struct range_base:
        range_pass<Impl, Allocator, typename Impl::pass_category>
    {
        range_base(const Allocator& allocator)
            : range_pass<Impl, Allocator, typename Impl::pass_category>(
                allocator)
        {
        }
    };
}

#endif

