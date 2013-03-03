/*
 * type_traits.hpp          type traits definition
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

#ifndef __YARR__TYPE_TRAITS_HPP__2013_01_26__
#define __YARR__TYPE_TRAITS_HPP__2013_01_26__

#if __cplusplus >= 201103L

#include <type_traits>

// import to separate namespace in order to avoid conflicts in std namespace
namespace yarr {
    using std::is_base_of;
    using std::is_same;
    using std::is_const;
    using std::remove_reference;
}

#else

namespace yarr {
    // integral_constant definition
    template <class T, T v>
    struct integral_constant {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
    }

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    // is_base_of definition
    namespace aux {
        template <class Base, class Derived>
        class is_base_of {
            typedef char two_chars[2];

            static char test(Base*);
            static two_chars& test(...);

        public:
            static const bool value = sizeof(test((Derived*)0)) == 1;
        };
    }

    template <class Base, class Derived>
    struct is_base_of:
        integral_constant<bool, aux::is_base_of<Base, Derived>::value>
    {
    };

    // is_const definition
    template <class T>
    struct is_const: false_type {
    };

    template <class T>
    struct is_const<const T>: true_type {
    };

    // is_same definition
    template <class T, class U>
    struct is_same: false_type {
    };

    template <class T>
    struct is_same<T, T>: true_type {
    };

    // remove_reference definition
    template <class T>
    struct remove_reference {
        typedef T type;
    }

    template <class T>
    struct remove_reference<T&> {
        typedef T type;
    }
}

#endif

namespace yarr {
    // select definition
    namespace aux {
        template <bool, class T, class U>
        struct select {
            typedef T type;
        };

        template <class T, class U>
        struct select<false, T, U> {
            typedef U type;
        };
    }

    template<class Cond, class T, class U>
    struct select: aux::select<Cond::value, T, U> {
    };

    // enable_if definition
    namespace aux {
        template <bool, class>
        struct enable_if {
        };

        template <class T>
        struct enable_if<true, T> {
            typedef T type;
        };
    }

    template<class Cond, class T = void>
    struct enable_if: aux::enable_if<Cond::value, T> {
    };
}

#endif

