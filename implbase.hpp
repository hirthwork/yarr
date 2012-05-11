/*
 * implbase.hpp             -- range implementation base class
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

#ifndef __IMPLBASE_HPP_2012_05_06__
#define __IMPLBASE_HPP_2012_05_06__

#include "implpass.hpp"

namespace yarr {
    template <class Config>
    struct impl_base: impl_pass<Config, typename Config::pass::category>
    {
        typedef Config config_type;

        template <class Impl, class Allocator>
        void destroy(
            typename Allocator::template rebind<Impl>::other allocator)
        {
            Impl* pthis = static_cast<Impl*>(this);
            try {
                allocator.destroy(pthis);
            } catch (...) {
                allocator.deallocate(pthis, 1);
                throw;
            }
        }

        using impl_pass<Config,
            typename Config::pass::category>::destroy;
    };
}

#endif

