/*
 * array.hpp                -- container range construction from array
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

#ifndef __CONTAINTER__ARRAY_HPP__2012_05_16__
#define __CONTAINTER__ARRAY_HPP__2012_05_16__

#include <cstddef>
#include <memory>

#include <assert/empty.hpp>

#include <configs/config.hpp>
#include <configs/iotype.hpp>
#include <configs/length.hpp>
#include <configs/order.hpp>
#include <configs/pass.hpp>
#include <configs/result.hpp>
#include <impls/impl.hpp>
#include <tags/iotype.hpp>
#include <tags/length.hpp>
#include <tags/order.hpp>
#include <tags/pass.hpp>
#include <tags/result.hpp>
#include <utils/isconst.hpp>
#include <utils/select.hpp>

#include "container.hpp"

namespace yarr {
    template <class Allocator, class T, std::size_t N>
    impls::impl<
        configs::range<
            configs::pass<tags::pass::double_ended>,
            configs::order<tags::order::random,
                typename Allocator::size_type>,
            configs::iotype<typename select<
                is_const<T>::value,
                tags::iotype::input,
                tags::iotype::input_output>::type>,
            configs::length<tags::length::limited,
                typename Allocator::size_type>,
            configs::result<tags::result::solid, T&> > >*
    container_range(T (&array)[N], const Allocator& allocator = Allocator()) {
        typedef impls::container::container<
            configs::range<
                configs::pass<tags::pass::double_ended>,
                configs::order<tags::order::random,
                    typename Allocator::size_type>,
                configs::iotype<typename select<
                    is_const<T>::value,
                    tags::iotype::input,
                    tags::iotype::input_output>::type>,
                configs::length<tags::length::limited,
                    typename Allocator::size_type>,
                configs::result<tags::result::solid, T&> >,
            T*,
            Allocator> container;
        typename Allocator::template rebind<container>::other new_allocator(
            allocator);
        container* impl = new_allocator.allocate(1);
        try {
            new_allocator.construct(impl,
                container(array, array + N, allocator));
            impl->set_allocator(new_allocator);
            return impl;
        } catch (...) {
            new_allocator.deallocate(impl, 1);
            throw;
        }
    }

    template <class Assert, class T, std::size_t N>
    impls::impl<
        configs::range<
            configs::pass<tags::pass::double_ended>,
            configs::order<tags::order::random,
                std::allocator<void*>::size_type>,
            configs::iotype<typename select<
                is_const<T>::value,
                tags::iotype::input,
                tags::iotype::input_output>::type>,
            configs::length<tags::length::limited,
                std::allocator<void*>::size_type>,
            configs::result<tags::result::solid, T&> > >*
    container_range(T (&array)[N]) {
        return container_range(array, std::allocator<void*>());
    }
}

#endif

