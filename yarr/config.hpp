/*
 * config.hpp               range config manipulation utilities
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

#ifndef __YARR__CONFIG_HPP__2013_01_26__
#define __YARR__CONFIG_HPP__2013_01_26__

#include "tags.hpp"

namespace yarr {
    namespace config {
        template <class Pass, class Order, class IOType, class Length,
            class Result>
        struct config {
            typedef Pass pass;
            typedef Order order;
            typedef IOType iotype;
            typedef Length length;
            typedef Result result;
        };

        template <class Tag>
        struct pass {
            typedef Tag tag;
        };

        template <class Config, class Pass>
        struct set_pass {
            typedef config<
                Pass,
                typename Config::order,
                typename Config::iotype,
                typename Config::length,
                typename Config::result> type;
        };

        template <class Tag, class = void>
        struct order;

        template <>
        struct order<tags::order::sequential, void> {
            typedef tags::order::sequential tag;
        };

        template <class PosType>
        struct order<tags::order::random, PosType> {
            typedef tags::order::random tag;
            typedef PosType pos_type;
        };

        template <class Config, class Order>
        struct set_order {
            typedef config<
                typename Config::pass,
                Order,
                typename Config::iotype,
                typename Config::length,
                typename Config::result> type;
        };

        template <class Tag, class = void>
        struct iotype;

        template <>
        struct iotype<tags::iotype::input, void> {
            typedef tags::iotype::input tag;
        };

        template <class Pred>
        struct iotype<tags::iotype::ordered, Pred> {
            typedef tags::iotype::ordered tag;
            typedef Pred pred;
        };

        template <class Pred>
        struct iotype<tags::iotype::strictly_ordered, Pred> {
            typedef tags::iotype::strictly_ordered tag;
            typedef Pred pred;
        };

        template <>
        struct iotype<tags::iotype::output, void> {
            typedef tags::iotype::output tag;
        };

        template <class Config, class IOType>
        struct set_iotype {
            typedef config<
                typename Config::pass,
                typename Config::order,
                IOType,
                typename Config::length,
                typename Config::result> type;
        };

        template <class Tag, class = void>
        struct length;

        template <>
        struct length<tags::length::endless, void> {
            typedef tags::length::endless tag;
        };

        template <>
        struct length<tags::length::finite, void> {
            typedef tags::length::finite tag;
        };

        template <class SizeType>
        struct length<tags::length::fixed, SizeType> {
            typedef tags::length::fixed tag;
            typedef SizeType size_type;
        };

        template <class Config, class Length>
        struct set_length {
            typedef config<
                typename Config::pass,
                typename Config::order,
                typename Config::iotype,
                Length,
                typename Config::result> type;
        };

        template <class Tag, class ValueType, class Reference = void>
        struct result;

        template <class ValueType>
        struct result<tags::result::value, ValueType, void> {
            typedef tags::result::reference tag;
            typedef ValueType value_type;
        };

        template <class ValueType, class Reference>
        struct result<tags::result::reference, ValueType, Reference> {
            typedef tags::result::reference tag;
            typedef ValueType value_type;
            typedef Reference reference;
        };

        template <class ValueType, class Reference>
        struct result<tags::result::contiguous, ValueType, Reference> {
            typedef tags::result::contiguous tag;
            typedef ValueType value_type;
            typedef Reference reference;
        };

        template <class Config, class Result>
        struct set_result {
            typedef config<
                typename Config::pass,
                typename Config::order,
                typename Config::iotype,
                typename Config::length,
                Result> type;
        };
    }
}

#endif

