/*
 * impl.hpp                 -- internal range interface
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

#ifndef __IMPL_HPP_2012_04_26__
#define __IMPL_HPP_2012_04_26__

#include "implbase.hpp"

namespace yarr {
    template <class impl_config>
    struct impl: impl_base<impl_config, typename impl_config::allocator_type> {
    };
}

#endif

