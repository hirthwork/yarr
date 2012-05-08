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
    template <class impl_config, class category>
    struct impl_size;

    template <class impl_config>
    struct impl_size<impl_config, tags::size::endless>:
        impl_result<impl_config, typename impl_config::result_config::category>
    {
    };

    template <class impl_config>
    struct impl_size<impl_config, tags::size::unlimited>:
        impl_result<impl_config, typename impl_config::result_config::category>
    {
        virtual bool empty() const = 0;
    };

    template <class impl_config>
    struct impl_size<impl_config, tags::size::limited>:
        impl_size<impl_config, tags::size::unlimited>
    {
        typedef typename impl_config::size_config::size_type size_type;
        virtual size_type size() const = 0;
    };
}

#endif

