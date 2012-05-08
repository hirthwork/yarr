/*
 * implresult.hpp           -- implementation result functions builder
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

#ifndef __IMPLRESULT_HPP_2012_05_08__
#define __IMPLRESULT_HPP_2012_05_08__

#include "resulttags.hpp"

namespace yarr {
    template <class Config, class Category>
    struct impl_result;

    template <class Config>
    struct impl_result<Config, tags::result::value>
    {
        typedef typename Config::result_config::result_type result_type;

        virtual ~impl_result() {
        }
    };

    template <class Config>
    struct impl_result<Config, tags::result::reference>:
        impl_result<Config, tags::result::value>
    {
    };

    template <class Config>
    struct impl_result<Config, tags::result::solid>:
        impl_result<Config, tags::result::reference>
    {
    };
}

#endif
