/*
 * pass.hpp                 -- ranges concatenation pass implementation
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

#ifndef __CONCAT__PASS_HPP__2012_05_20__
#define __CONCAT__PASS_HPP__2012_05_20__

#include <impls/holder.hpp>
#include <impls/impl.hpp>
#include <tags/length.hpp>
#include <tags/pass.hpp>
#include <utils/isbase.hpp>
#include <utils/proxy.hpp>

#include "order.hpp"

namespace yarr {
    namespace impls {
        namespace concat {
            template <class Config, class Impl1, class Impl2, class Allocator,
                class Category>
            struct pass;

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct pass<Config, Impl1, Impl2, Allocator, tags::pass::one_pass>:
                order<Config, Impl1, Impl2, Allocator,
                    typename Config::order::category>
            {
                pass(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : order<Config, Impl1, Impl2, Allocator,
                        typename Config::order::category>(impl1, impl2,
                            allocator)
                {
                }

                typename impl<Config>::result_type next() {
                    return first<holder<Impl1> >::get()->empty() ?
                        second<holder<Impl2> >::get()->next()
                        : first<holder<Impl1> >::get()->next();
                }
            };

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct pass<Config, Impl1, Impl2, Allocator,
                tags::pass::swappable>:
                    pass<Config, Impl1, Impl2, Allocator, tags::pass::one_pass>
            {
                pass(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : pass<Config, Impl1, Impl2, Allocator,
                        tags::pass::one_pass>(impl1, impl2, allocator)
                {
                }
            };

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct pass<Config, Impl1, Impl2, Allocator, tags::pass::forward>:
                pass<Config, Impl1, Impl2, Allocator, tags::pass::swappable>
            {
                pass(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : pass<Config, Impl1, Impl2, Allocator,
                        tags::pass::swappable>(impl1, impl2, allocator)
                {
                }

                typename impl<Config>::result_type front() const {
                    return first<holder<Impl1> >::get()->empty() ?
                        second<holder<Impl2> >::get()->front()
                        : first<holder<Impl1> >::get()->front();
                }

                void pop() {
                    if (first<holder<Impl1> >::get()->empty()) {
                        second<holder<Impl2> >::get()->pop();
                    } else {
                        first<holder<Impl1> >::get()->pop();
                    }
                }
            };

            namespace aux {
                template <class Config, class Impl1, class Impl2,
                    class Allocator, bool>
                struct pass:
                    concat::pass<Config, Impl1, Impl2, Allocator,
                        tags::pass::forward>
                {
                    pass(Impl1* impl1, Impl2* impl2,
                        const Allocator& allocator)
                        : concat::pass<Config, Impl1, Impl2, Allocator,
                            tags::pass::forward>(impl1, impl2, allocator)
                    {
                    }

                    typename impl<Config>::result_type prev() {
                        return second<holder<Impl2> >::get()->prev();
                    }

                    typename impl<Config>::result_type back() const {
                        return second<holder<Impl2> >::get()->back();
                    }

                    void pop_back() {
                        second<holder<Impl2> >::get()->pop_back();
                    }
                };

                template <class Config, class Impl1, class Impl2,
                    class Allocator>
                struct pass<Config, Impl1, Impl2, Allocator, false>:
                    concat::pass<Config, Impl1, Impl2, Allocator,
                        tags::pass::forward>
                {
                    pass(Impl1* impl1, Impl2* impl2,
                        const Allocator& allocator)
                        : concat::pass<Config, Impl1, Impl2, Allocator,
                            tags::pass::forward>(impl1, impl2, allocator)
                    {
                    }

                    typename impl<Config>::result_type prev() {
                        return second<holder<Impl2> >::get()->empty() ?
                            first<holder<Impl1> >::get()->prev()
                            : second<holder<Impl2> >::get()->prev();
                    }

                    typename impl<Config>::result_type back() const {
                        return second<holder<Impl2> >::get()->empty() ?
                            first<holder<Impl1> >::get()->back()
                            : second<holder<Impl2> >::get()->back();
                    }

                    void pop_back() {
                        if (second<holder<Impl2> >::get()->empty()) {
                            first<holder<Impl1> >::get()->pop_back();
                        } else {
                            second<holder<Impl2> >::get()->pop_back();
                        }
                    }
                };
            }

            template <class Config, class Impl1, class Impl2, class Allocator>
            struct pass<Config, Impl1, Impl2, Allocator,
                tags::pass::double_ended>:
                    aux::pass<Config, Impl1, Impl2, Allocator,
                        is_base<tags::length::unlimited,
                            typename Config::length::category>::value
                    >
            {
                pass(Impl1* impl1, Impl2* impl2, const Allocator& allocator)
                    : aux::pass<Config, Impl1, Impl2, Allocator,
                        is_base<tags::length::unlimited,
                            typename Config::length::category>::value
                        >(impl1, impl2, allocator)
                {
                }
            };
        }
    }
}

#endif

