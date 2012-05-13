/*
 * swap.hpp                 -- swap function specialization for range
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

#ifndef __UTILS__SWAP_HPP__2012_05_08__
#define __UTILS__SWAP_HPP__2012_05_08__

#include <reinvented-wheels/enableif.hpp>

#include <range.hpp>
#include <tags/pass.hpp>

#include "isbase.hpp"

namespace std {
    template <class RangeConfig, class Assert>
    typename reinvented_wheels::enable_if<yarr::is_base<
        yarr::tags::pass::swappable,
        typename RangeConfig::pass::category>::value
        >::type
    swap(yarr::range<RangeConfig, Assert>& lhs,
        yarr::range<RangeConfig, Assert>& rhs)
    {
        lhs.swap(rhs);
    }
}

#endif
