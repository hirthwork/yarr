/*
 * iotype.hpp               -- range function for I/O tags
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

#ifndef __RANGES__IOTYPE_HPP__2012_05_06__
#define __RANGES__IOTYPE_HPP__2012_05_06__

#include <tags/iotype.hpp>

#include "length.hpp"

namespace yarr {
    namespace ranges {
        template <class Impl, class Category>
        struct iotype;

        template <class Impl>
        struct iotype<Impl, tags::iotype::input>:
            length<Impl, typename Impl::config_type::length::category>
        {
            iotype(Impl* impl)
                : length<Impl, typename Impl::config_type::length::category>(
                    impl)
            {
            }
        };

        template <class Impl>
        struct iotype<Impl, tags::iotype::output>:
            length<Impl, typename Impl::config_type::length::category>
        {
            iotype(Impl* impl)
                : length<Impl, typename Impl::config_type::length::category>(
                    impl)
            {
            }
        };

        template <class Impl>
        struct iotype<Impl, tags::iotype::input_output>:
            length<Impl, typename Impl::config_type::length::category>
        {
            iotype(Impl* impl)
                : length<Impl, typename Impl::config_type::length::category>(
                    impl)
            {
            }
        };
    }
}

#endif

