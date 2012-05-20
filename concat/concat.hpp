/*
 * concat.hpp               -- ranges concatenation
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

#ifndef __CONCAT__CONCAT_HPP__2012_05_20__
#define __CONCAT__CONCAT_HPP__2012_05_20__

#include <memory>

#include <reinvented-wheels/enableif.hpp>

#include <impls/impl.hpp>
#include <tags/pass.hpp>
#include <utils/isbase.hpp>
#include <utils/proxy.hpp>

#include "pass.hpp"
#include "config.hpp"

namespace yarr {
    namespace impls {
        namespace concat {
            template <class Config, class Impl1, class Impl2, class Allocator>
            struct concat:
                pass<Config, Impl1, Impl2, Allocator,
                    typename Config::pass::category>
            {
                concat(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : pass<Config, Impl1, Impl2, Allocator,
                        typename Config::pass::category>(impl1, impl2,
                            allocator)
                {
                }

                void destroy() {
                    typedef concat<Config, Impl1, Impl2, Allocator> type;
                    impl<Config>::template destroy<type, Allocator>(*this);
                }

                typename reinvented_wheels::enable_if<
                    is_base<tags::pass::forward,
                        typename Config::pass::category>::value,
                    concat<Config, Impl1, Impl2, Allocator>*>::type
                clone() const {
                    typedef concat<Config, Impl1, Impl2, Allocator> type;
                    typename Allocator::template rebind<type>::other
                        new_allocator(*this);
                    type* p = new_allocator.allocate(1);
                    try {
                        // TODO: exception safety
                        Impl1* impl1 = first<holder<Impl1> >::get()->clone();
                        Impl2* impl2 = second<holder<Impl2> >::get()->clone();
                        new_allocator.construct(p, type(impl1, impl2, *this));
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

    // NOTE: concat function takes impl ownership
    template <class Config, class Allocator, class Impl1, class Impl2>
    impls::impl<Config>* concat(Impl1* impl1, Impl2* impl2,
        const Allocator& allocator = Allocator())
    {
        typedef impls::concat::concat<typename configs::copy<Config>::type,
            Impl1, Impl2, Allocator> concat_type;
        typename Allocator::template rebind<concat_type>::other
            new_allocator(allocator);
        concat_type* p = new_allocator.allocate(1);
        try {
            // NOTE: no exception safety required as constructor will newer
            // throw exception
            // TODO: is this so ↑?
            // TODO: remove code duplication with clone() here and in other
            // impls
            new_allocator.construct(p, concat_type(impl1, impl2, allocator));
            p->set_allocator(new_allocator);
            return p;
        } catch (...) {
            new_allocator.deallocate(p, 1);
            throw;
        }
    }

    template <class Config, class Impl1, class Impl2>
    impls::impl<Config>* concat(Impl1* impl1, Impl2* impl2)
    {
        return concat<Config>(impl1, impl2, std::allocator<void*>());
    }
}

#endif

