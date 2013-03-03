/*
 * rational.hpp             rational numbers generator
 *
 * Copyright (C) 2013 Dmitry Potapov <potapov.d@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#ifndef __YARR__RATIONAL_HPP__2013_01_26__
#define __YARR__RATIONAL_HPP__2013_01_26__

#include <utility>

#include "config.hpp"
#include "tags.hpp"

namespace yarr {
    namespace rational {
        namespace impl {
            template <class Value>
            struct config {
                typedef yarr::config::config<
                    yarr::config::pass<tags::pass::forward>,
                    yarr::config::order<tags::order::sequential>,
                    yarr::config::iotype<tags::iotype::input>,
                    yarr::config::length<tags::length::endless>,
                    yarr::config::result<tags::result::value, Value>
                > type;
            };

            template <class T>
            struct traits {
                // XXX: noexcept?
                static inline bool is_one(T t) {
                    return !--t;
                }

                static bool is_coprime(T first, T second) {
                    T zero = T();
                    while (true) {
                        second %= first;
                        if (second == zero) {
                            return is_one(first);
                        }
                        first %= second;
                        if (first == zero) {
                            return is_one(second);
                        }
                    }
                }
            };
        }

        template <class T = unsigned, class V = std::pair<T, T> >
        class rational {
            T denominator;
            T numerator;
            bool up;

        public:
            typedef typename impl::config<V>::type range_config;
            typedef V value_type;

            inline rational()
                : denominator()
                , numerator(denominator++)
                , up(true)
            {
            }

            value_type next() {
                if (up) {
                    ++numerator;
                    if (numerator == denominator) {
                        ++denominator;
                        up = false;
                    } else {
                        while (!impl::traits<T>::is_coprime(numerator,
                            denominator))
                        {
                            ++numerator;
                        }
                    }
                } else {
                    if (impl::traits<T>::is_one(numerator)) {
                        ++denominator;
                        up = true;
                    } else {
                        do {
                            --numerator;
                        } while (!impl::traits<T>::is_coprime(numerator,
                            denominator));
                    }
                }
                return value_type(numerator, denominator);
            }
        };
    }
}

#endif

