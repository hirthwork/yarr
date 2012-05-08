/*
 * impliotype.hpp           -- implementation I/O type functions builder
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

#ifndef __IMPLIOTYPE_HPP_2012_05_08__
#define __IMPLIOTYPE_HPP_2012_05_08__

#include "implsize.hpp"
#include "iotypetags.hpp"

namespace yarr {
    template <class Config, class Category>
    struct impl_iotype;

    template <class Config>
    struct impl_iotype<Config, tags::iotype::input>:
        impl_size<Config, typename Config::size_config::category>
    {
    };

    template <class Config>
    struct impl_iotype<Config, tags::iotype::output>:
        impl_size<Config, typename Config::size_config::category>
    {
    };
}

#endif

