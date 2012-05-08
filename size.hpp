/*
 * size.hpp                 -- size function forward ranges
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

#ifndef __SIZE_HPP_2012_05_08__
#define __SIZE_HPP_2012_05_08__

#include <cstddef>

#include <reinvented-wheels/enableif.hpp>

#include "isbase.hpp"
#include "passtags.hpp"
#include "range.hpp"
#include "sizetags.hpp"

namespace yarr {
    template <bool, class>
    struct size_traits_impl {
        static const bool limited = false;
        typedef std::size_t size_type;
    };

    template <class SizeConfig>
    struct size_traits_impl<true, SizeConfig> {
        static const bool limited = true;
        typedef typename SizeConfig::size_type size_type;
    };

    template <class SizeConfig>
    struct size_traits: size_traits_impl<is_base<tags::size::limited,
        typename SizeConfig::category>::value, SizeConfig>
    {
    };

    template <class RangeConfig, class Assert, class Allocator>
    typename reinvented_wheels::enable_if<
        size_traits<typename RangeConfig::size_config>::limited,
        typename size_traits<typename RangeConfig::size_config>::size_type
        >::type size(const range<RangeConfig, Assert, Allocator>& r)
    {
        return r.size();
    }

    template <class RangeConfig, class Assert, class Allocator>
    typename reinvented_wheels::enable_if<
        !size_traits<typename RangeConfig::size_config>::limited
        && is_base<tags::size::unlimited,
            typename RangeConfig::size_config::category>::value
        && is_base<tags::pass::forward,
            typename RangeConfig::pass_config::category>::value,
        typename size_traits<typename RangeConfig::size_config>::size_type
        >::type size(range<RangeConfig, Assert, Allocator> r)
    {
        typedef typename size_traits<typename RangeConfig::size_config
            >::size_type size_type;
        size_type result = size_type();
        while (!r.empty()) {
            ++result;
            r.pop();
        }
        return result;
    }
}

#endif

