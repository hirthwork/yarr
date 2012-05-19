/*
 * rebind.hpp               -- implementation rebinder
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

#ifndef __REBIND__REBIND_HPP__2012_05_19__
#define __REBIND__REBIND_HPP__2012_05_19__

#include <memory>

#include <reinvented-wheels/enableif.hpp>

#include <tags/pass.hpp>
#include <utils/isbase.hpp>

#include "pass.hpp"

namespace yarr {
    namespace impls {
        namespace rebind {
            template <class Config, class Impl, class Allocator>
            struct rebind:
                pass<Config, Impl, Allocator, typename Config::pass::category>
            {
                rebind(Impl* impl, const Allocator& allocator)
                    : pass<Config, Impl, Allocator,
                        typename Config::pass::category>(impl, allocator)
                {
                }

                void destroy() {
                    typedef rebind<Config, Impl, Allocator> type;
                    impls::impl<Config>::template destroy<type, Allocator>(
                        *this);
                }

                typename reinvented_wheels::enable_if<
                    is_base<tags::pass::forward,
                        typename Config::pass::category>::value,
                    rebind<Config, Impl, Allocator>*>::type
                clone() const {
                    typedef rebind<Config, Impl, Allocator> type;
                    typename Allocator::template rebind<type>::other
                        new_allocator(*this);
                    type* p = new_allocator.allocate(1);
                    try {
                        Impl* i = this->get()->clone();
                        new_allocator.construct(p, type(i, *this));
                        p->set_allocator(new_allocator);
                    } catch (...) {
                        new_allocator.deallocate(p, 1);
                        throw;
                    }
                    return p;
                }
            };
        }
    }

    // NOTE: rebind function takes impl ownership
    template <class Config, class Allocator, class Impl>
    impls::impl<Config>* rebind(Impl* impl,
        const Allocator& allocator = Allocator())
    {
        typedef impls::rebind::rebind<typename configs::copy<Config>::type,
            Impl, Allocator> rebind_type;
        typename Allocator::template rebind<rebind_type>::other
            new_allocator(allocator);
        rebind_type* p = new_allocator.allocate(1);
        try {
            new_allocator.construct(p, rebind_type(impl, allocator));
            p->set_allocator(new_allocator);
            return p;
        } catch (...) {
            new_allocator.deallocate(p, 1);
            throw;
        }
    }

    template <class Config, class Impl>
    impls::impl<Config>* rebind(Impl* impl)
    {
        return rebind<Config>(impl, std::allocator<void*>());
    }
}

#endif

