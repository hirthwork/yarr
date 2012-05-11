/*
 * rangeiotype.hpp          -- range function for I/O tags
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

#ifndef __RANGEIOTYPE_HPP_2012_05_06__
#define __RANGEIOTYPE_HPP_2012_05_06__

#include "rangesize.hpp"
#include "iotypetags.hpp"

namespace yarr {
    template <class Impl, class Category>
    struct range_iotype;

    template <class Impl>
    struct range_iotype<Impl, tags::iotype::input>:
        range_size<Impl, typename Impl::config_type::size::category>
    {
        range_iotype(Impl* impl)
            : range_size<Impl, typename Impl::config_type::size::category>(
                impl)
        {
        }
    };

    template <class Impl>
    struct range_iotype<Impl, tags::iotype::output>:
        range_size<Impl, typename Impl::config_type::size::category>
    {
        range_iotype(Impl* impl)
            : range_size<Impl, typename Impl::config_type::size::category>(
                impl)
        {
        }
    };
}

#endif

