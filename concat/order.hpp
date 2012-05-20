/*
 * order.hpp                -- ranges concatenation order implementation
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

#ifndef __CONCAT__ORDER_HPP__2012_05_20__
#define __CONCAT__ORDER_HPP__2012_05_20__

#include <impls/holder.hpp>
#include <impls/impl.hpp>
#include <tags/length.hpp>
#include <tags/order.hpp>
#include <tags/pass.hpp>
#include <utils/isbase.hpp>
#include <utils/proxy.hpp>

#include "iotype.hpp"

namespace yarr {
    namespace impls {
        namespace concat {
            template <class Config, class Impl1, class Impl2, class Allocator,
                class Category>
            struct order;

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct order<Config, Impl1, Impl2, Allocator,
                tags::order::sequential>:
                    iotype<Config, Impl1, Impl2, Allocator,
                        typename Config::iotype::category>
            {
                order(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : iotype<Config, Impl1, Impl2, Allocator,
                        typename Config::iotype::category>(impl1, impl2,
                            allocator)
                {
                }
            };

            namespace aux {
                template <class Config, class Impl1, class Impl2,
                    class Allocator, bool>
                struct order:
                    concat::order<Config, Impl1, Impl2, Allocator,
                        tags::order::sequential>
                {
                    typedef typename impl<Config>::pos_type pos_type;
                    order(Impl1* impl1, Impl2* impl2,
                        const Allocator& allocator)
                        : concat::order<Config, Impl1, Impl2, Allocator,
                            tags::order::sequential>(impl1, impl2, allocator)
                    {
                    }

                    typename impl<Config>::result_type
                    at(pos_type pos) const
                    {
                        return pos < first<holder<Impl1> >::get()->size() ?
                            first<holder<Impl1> >::get()->at(pos)
                            : second<holder<Impl2> >::get()->at(
                                pos - first<holder<Impl1> >::get()->size());
                    }

                    void skip(pos_type n) {
                        if (n > first<holder<Impl1> >::get()->size()) {
                            second<holder<Impl2> >::get()->skip(
                                n - first<holder<Impl1> >::get()->size());
                            first<holder<Impl1> >::get()->skip(
                                first<holder<Impl1> >::get()->size());
                        } else {
                            first<holder<Impl1> >::get()->skip(n);
                        }
                    }
                };

                template <class Config, class Impl1, class Impl2,
                    class Allocator, bool>
                struct ending: order<Config, Impl1, Impl2, Allocator, false> {
                    ending(Impl1* impl1, Impl2* impl2,
                        const Allocator& allocator)
                        : order<Config, Impl1, Impl2, Allocator, false>(impl1,
                            impl2, allocator)
                    {
                    }

                    typename impl<Config>::result_type
                    rat(typename impl<Config>::pos_type pos) const
                    {
                        return pos < second<holder<Impl2> >::get()->size() ?
                            second<holder<Impl2> >::get()->rat(pos)
                            : first<holder<Impl1> >::get()->rat(
                                pos - second<holder<Impl2> >::get()->size());
                    }

                    void truncate(typename impl<Config>::pos_type n) {
                        if (n > second<holder<Impl2> >::get()->size()) {
                            first<holder<Impl1> >::get()->truncate(
                                n - second<holder<Impl2> >::get()->size());
                            second<holder<Impl2> >::get()->truncate(
                                second<holder<Impl2> >::get()->size());
                        } else {
                            second<holder<Impl2> >::get()->truncate(n);
                        }
                    }
                };

                template <class Config, class Impl1, class Impl2,
                    class Allocator>
                struct ending<Config, Impl1, Impl2, Allocator, false>:
                    order<Config, Impl1, Impl2, Allocator, false>
                {
                    ending(Impl1* impl1, Impl2* impl2,
                        const Allocator& allocator)
                        : order<Config, Impl1, Impl2, Allocator, false>(impl1,
                            impl2, allocator)
                    {
                    }

                    typename impl<Config>::result_type
                    rat(typename impl<Config>::pos_type pos) const
                    {
                        return second<holder<Impl2> >::get()->rat(pos);
                    }

                    void truncate(typename impl<Config>::pos_type n) {
                        second<holder<Impl2> >::get()->truncate(n);
                    }
                };

                template <class Config, class Impl1, class Impl2,
                    class Allocator>
                struct order<Config, Impl1, Impl2, Allocator, true>:
                    ending<Config, Impl1, Impl2, Allocator,
                        is_base<tags::length::limited,
                            typename Config::length::category>::value>
                {
                    order(Impl1* impl1, Impl2* impl2,
                        const Allocator& allocator)
                        : ending<Config, Impl1, Impl2, Allocator,
                            is_base<tags::length::limited,
                                typename Config::length::category>::value
                            >(impl1, impl2, allocator)
                    {
                    }
                };
            }

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct order<Config, Impl1, Impl2, Allocator, tags::order::random>:
                    aux::order<Config,
                        Impl1,
                        Impl2,
                        Allocator,
                        is_base<tags::pass::double_ended,
                            typename Config::pass::category>::value >
            {
                order(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : aux::order<Config,
                        Impl1,
                        Impl2,
                        Allocator,
                        is_base<tags::pass::double_ended,
                            typename Config::pass::category>::value
                        >(impl1, impl2, allocator)
                {
                }
            };
        }
    }
}

#endif

