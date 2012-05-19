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

#ifndef __IMPLS__HOLDER_HPP__2012_05_06__
#define __IMPLS__HOLDER_HPP__2012_05_06__

// include swap(..., ...)
#if __cplus_plus < 201103L
#include <algorithm>
#else
#include <utility>
#endif

#include <reinvented-wheels/enableif.hpp>

#include <utils/isbase.hpp>
#include <tags/length.hpp>

namespace yarr {
    namespace impls {
        namespace aux {
            template <class Impl>
            typename reinvented_wheels::enable_if<is_base<
                tags::length::endless,
                typename Impl::config_type::length::category
            >::value, bool>::type
            need_clone(const Impl* impl) {
                return impl;
            }

            template <class Impl>
            typename reinvented_wheels::enable_if<is_base<
                tags::length::unlimited,
                typename Impl::config_type::length::category
            >::value, bool>::type
            need_clone(const Impl* impl) {
                return impl && !impl->empty();
            }
        }

        template <class Impl>
        class holder {
            Impl* impl;

        protected:
            Impl* get() const {
                return impl;
            }

            void destroy()
            {
                if (impl) {
                    impl->destroy();
                }
            }

            void set(Impl* impl) {
                destroy();
                this->impl = impl;
            }

            void swap(holder& other) {
                std::swap(impl, other.impl);
            }

        public:
            Impl* release() {
                Impl* result = impl;
                impl = 0;
                return result;
            }

            typedef Impl impl_type;

            explicit holder(Impl* impl)
                : impl(impl)
            {
            }

            holder(const holder& other)
                : impl(aux::need_clone(other.get()) ?
                    static_cast<Impl*>(other.get()->clone()) : 0)
            {
            }

            holder& operator =(holder other)
            {
                set(other.release());
            }

            ~holder()
            {
                destroy();
            }

            void clear() {
                destroy();
                impl = 0;
            }
        };
    }
}

#endif

