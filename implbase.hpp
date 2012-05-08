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
    template <class impl_config, class Allocator>
    class impl_base: public impl_pass<impl_config,
        typename impl_config::pass_config::category>
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
        typedef typename impl_config::pass_config::category pass_category;
        typedef typename impl_config::order_config::category order_category;
        typedef typename impl_config::iotype_config::category iotype_category;
        typedef typename impl_config::size_config::category size_category;
        typedef typename impl_config::result_config::category result_category;

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

        using impl_pass<impl_config,
            typename impl_config::pass_config::category>::destroy;
    };
}

#endif

