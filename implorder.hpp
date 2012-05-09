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

#include "implpass.hpp"
#include "isbase.hpp"
#include "ordertags.hpp"
#include "passtags.hpp"
#include "resulttags.hpp"

namespace yarr {
    template <class Config, class Category>
    struct impl_order;

    template <class Config>
    struct impl_order<Config, tags::order::sequential>:
        impl_pass<Config, typename Config::pass_config::category>
    {
    };

    namespace aux {
        template <class Config, bool>
        struct impl_order: yarr::impl_order<Config, tags::order::sequential> {
            typedef typename Config::order_config::pos_type pos_type;
            virtual typename yarr::impl_order<Config, tags::order::sequential
                >::result_type
            operator [](pos_type pos) const = 0;
        };

        template <class Config>
        struct impl_order<Config, true>:
            yarr::impl_order<Config, tags::order::sequential>
        {
            typedef typename Config::order_config::pos_type pos_type;
            virtual typename yarr::impl_order<Config, tags::order::sequential
                >::result_type
            operator [](pos_type pos) const {
                return *(&this->front() + pos);
            }
        };
    }

    template <class Config>
    struct impl_order<Config, tags::order::random>:
        aux::impl_order<Config,
            is_base<tags::result::solid,
                typename Config::result_config::category>::value
            && is_base<tags::pass::forward,
                typename Config::pass_config::category>::value>
    {
    };
}

#endif

