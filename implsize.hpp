/*
 * implsize.hpp             -- implementation size functions builder
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

#ifndef __IMPLSIZE_HPP_2012_05_08__
#define __IMPLSIZE_HPP_2012_05_08__

#include "implresult.hpp"
#include "sizetags.hpp"

namespace yarr {
    template <class Config, class Category>
    struct impl_size;

    template <class Config>
    struct impl_size<Config, tags::size::endless>:
        impl_result<Config, typename Config::result_config::category>
    {
    };

    template <class Config>
    struct impl_size<Config, tags::size::unlimited>:
        impl_result<Config, typename Config::result_config::category>
    {
        virtual bool empty() const = 0;
    };

    template <class Config>
    struct impl_size<Config, tags::size::limited>:
        impl_size<Config, tags::size::unlimited>
    {
        typedef typename Config::size_config::size_type size_type;
        virtual size_type size() const = 0;

        bool empty() const {
            return !size();
        }
    };
}

#endif

