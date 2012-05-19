/*
 * range.hpp                -- yet another reinvented range
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

#ifndef __RANGE_HPP__2012_04_26__
#define __RANGE_HPP__2012_04_26__

#include <assert/empty.hpp>

#include "configs/config.hpp"
#include "impls/impl.hpp"
#include "ranges/base.hpp"

namespace yarr {
    template <class Config, class Assert = assert::empty>
    struct range:
        ranges::base<configs::complete<Config, Assert> >
    {
        typedef configs::complete<Config, Assert> config_type;
        explicit range(impls::impl<Config>* impl = 0)
            : ranges::base<config_type>(impl)
        {
        }
    };
}

#endif

