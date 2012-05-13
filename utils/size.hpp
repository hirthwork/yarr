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

#ifndef __UTILS__SIZE_HPP__2012_05_08__
#define __UTILS__SIZE_HPP__2012_05_08__

#include <cstddef>

#include <reinvented-wheels/enableif.hpp>

#include <range.hpp>
#include <tags/length.hpp>
#include <tags/pass.hpp>

#include "isbase.hpp"

namespace yarr {
    namespace aux {
        template <bool, class>
        struct size_traits {
            static const bool limited = false;
            typedef std::size_t size_type;
        };

        template <class LengthConfig>
        struct size_traits<true, LengthConfig> {
            static const bool limited = true;
            typedef typename LengthConfig::size_type size_type;
        };
    }

    template <class LengthConfig>
    struct size_traits: aux::size_traits<is_base<tags::length::limited,
        typename LengthConfig::category>::value, LengthConfig>
    {
    };

    template <class RangeConfig, class Assert>
    typename reinvented_wheels::enable_if<
        size_traits<typename RangeConfig::length>::limited,
        typename size_traits<typename RangeConfig::length>::size_type
        >::type
    size(const range<RangeConfig, Assert>& r)
    {
        return r.size();
    }

    template <class RangeConfig, class Assert>
    typename reinvented_wheels::enable_if<
        !size_traits<typename RangeConfig::length>::limited
        && is_base<tags::length::unlimited,
            typename RangeConfig::length::category>::value
        && is_base<tags::pass::forward,
            typename RangeConfig::pass::category>::value,
        typename size_traits<typename RangeConfig::length>::size_type
        >::type
    size(range<RangeConfig, Assert> r)
    {
        typedef typename size_traits<typename RangeConfig::length>::size_type
            size_type;
        size_type result = size_type();
        while (!r.empty()) {
            ++result;
            r.pop();
        }
        return result;
    }
}

#endif

