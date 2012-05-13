/*
 * base.hpp                 -- range implementation base class
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

#ifndef __IMPLS__BASE_HPP__2012_05_06__
#define __IMPLS__BASE_HPP__2012_05_06__

#include "pass.hpp"

namespace yarr {
    namespace impls {
        template <class Config>
        struct base: pass<Config, typename Config::pass::category>
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

            using pass<Config, typename Config::pass::category>::destroy;
        };
    }
}

#endif

