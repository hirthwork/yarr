/*
 * holder.hpp               -- range implementation holder
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

#ifndef __IMPLHOLDER_HPP_2012_05_06__
#define __IMPLHOLDER_HPP_2012_05_06__

// include swap(..., ...)
#if __cplus_plus < 201103L
#include <algorithm>
#else
#include <utility>
#endif

#include "isbase.hpp"
#include "sizetags.hpp"

namespace yarr {
    namespace aux {
        template <class Impl>
        typename reinvented_wheels::enable_if<is_base<tags::size::endless,
            typename Impl::config_type::size::category>::value, bool>::type
        need_clone(const Impl* impl) {
            return impl;
        }

        template <class Impl>
        typename reinvented_wheels::enable_if<is_base<tags::size::unlimited,
            typename Impl::config_type::size::category>::value, bool>::type
        need_clone(const Impl* impl) {
            return impl && !impl->empty();
        }
    }

    template <class Impl, class Allocator>
    class impl_holder: public Allocator {
        Impl* impl;

    protected:
        Impl* get() const {
            return impl;
        }

        void destroy()
        {
            if (impl) {
                impl->destroy(*static_cast<Allocator*>(this));
            }
        }

        // it is assumed, that impl pointer was allocated using *this allocator
        void set(Impl* impl) {
            destroy();
            this->impl = impl;
        }

        void swap(impl_holder& other) {
            std::swap(impl, other.impl);
            std::swap(static_cast<Allocator&>(*this),
                static_cast<Allocator&>(other));
        }

    public:
        typedef Impl impl_type;
        typedef Allocator allocator_type;
        typedef impl_holder<impl_type, Allocator> holder_type;

        impl_holder(const Allocator& allocator)
            : Allocator(allocator)
            , impl(0)
        {
        }

        impl_holder(const impl_holder& other)
            : Allocator(other)
            , impl(aux::need_clone(other.get()) ?
                static_cast<Impl*>(other.get()->clone(*this)) : 0)
        {
        }

        impl_holder& operator =(const impl_holder& other)
        {
            Allocator::operator =(other);
            if (aux::need_clone(other.get())) {
                set(static_cast<Impl*>(other.get()->clone(*this)));
            } else {
                clear();
            }
        }

        ~impl_holder()
        {
            destroy();
        }

        void clear() {
            destroy();
            impl = 0;
        }

        allocator_type get_allocator() const {
            return *this;
        }
    };
}

#endif

