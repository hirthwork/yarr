/*
 * implorder.hpp            -- implementation order functions builder
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

#ifndef __IMPLORDER_HPP_2012_05_08__
#define __IMPLORDER_HPP_2012_05_08__

#include "impliotype.hpp"
#include "ordertags.hpp"

namespace yarr {
    template <class impl_config, class category>
    struct impl_order;

    template <class impl_config>
    struct impl_order<impl_config, tags::order::sequential>:
        impl_iotype<impl_config, typename impl_config::iotype_config::category>
    {
    };

    template <class impl_config>
    struct impl_order<impl_config, tags::order::random>:
        impl_order<impl_config, tags::order::sequential>
    {
        typedef typename impl_config::order_config::pos_type pos_type;
        virtual typename impl_order<impl_config, tags::order::sequential
            >::result_type operator [](pos_type pos) const = 0;
    };
}

#endif

