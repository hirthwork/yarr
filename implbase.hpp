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

#include "implorder.hpp"

namespace yarr {
    template <class Config, class Allocator>
    class impl_base: public impl_order<Config,
        typename Config::order::category>
    {
        template <class Impl, class From>
        class deallocator {
            Impl* const pointer;
            From& from;
            Allocator& to;

        public:
            deallocator(Impl* pointer, From& from, Allocator& to)
                : pointer(pointer)
                , from(from)
                , to(to)
            {
            }

            ~deallocator()
            {
                from.deallocate(pointer, 1);
                to = from;
            }
        };

    public:
        typedef Config config_type;

        template <class Impl>
        void destroy(Allocator& allocator) {
            typedef typename Allocator::template rebind<Impl>::other
                new_allocator_type;
            new_allocator_type new_allocator(allocator);
            typedef deallocator<Impl, new_allocator_type> deallocator_type;
            Impl* pthis = static_cast<Impl*>(this);
            deallocator_type deallocator(pthis, new_allocator, allocator);
            new_allocator.destroy(pthis);
        }

        using impl_order<Config,
            typename Config::order::category>::destroy;
    };
}

#endif

