/*
 * length.hpp               -- range function for length tags
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

#ifndef __RANGES__LENGTH_HPP__2012_05_06__
#define __RANGES__LENGTH_HPP__2012_05_06__

#include <tags/length.hpp>

#include "result.hpp"

namespace yarr {
    namespace ranges {
        template <class Impl, class Category>
        struct length;

        template <class Impl>
        struct length<Impl, tags::length::endless>:
            result<Impl, typename Impl::config_type::result::category>
        {
            explicit length(Impl* impl)
                : result<Impl, typename Impl::config_type::result::category>(
                    impl)
            {
            }
        };

        template <class Impl>
        struct length<Impl, tags::length::unlimited>:
            result<Impl, typename Impl::config_type::result::category>
        {
            explicit length(Impl* impl)
                : result<Impl, typename Impl::config_type::result::category>(
                    impl)
            {
            }

            bool empty() const {
                return !this->get() || this->get()->empty();
            }
        };

        template <class Impl>
        struct length<Impl, tags::length::limited>:
            length<Impl, tags::length::unlimited>
        {
            typedef typename Impl::size_type size_type;

            explicit length(Impl* impl)
                : length<Impl, tags::length::unlimited>(impl)
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
}

#endif

