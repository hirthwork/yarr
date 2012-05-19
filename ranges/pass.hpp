/*
 * pass.hpp                 -- range function for pass tags
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

#ifndef __RANGES__PASS_HPP__2012_05_07__
#define __RANGES__PASS_HPP__2012_05_07__

#include <functional>

#include <assert/predicates.hpp>

#include <reinvented-wheels/enableif.hpp>

#include <impls/impl.hpp>
#include <tags/length.hpp>
#include <tags/pass.hpp>
#include <utils/isbase.hpp>

#include "order.hpp"

namespace yarr {
    namespace ranges {
        namespace aux {
            template <class Range, class Message>
            typename reinvented_wheels::enable_if<
                is_base<
                    tags::length::endless,
                    typename Range::config_type::length::category
                >::value
            >::type
            check_not_empty(const Range*, Message) {
            }

            template <class Range, class Message>
            typename reinvented_wheels::enable_if<
                is_base<
                    tags::length::unlimited,
                    typename Range::config_type::length::category
                >::value
            >::type
            check_not_empty(const Range* range, Message message) {
                typedef typename Range::config_type::assert_type
                    assert_type;
                assert_type::assert(assert::bind(std::logical_not<bool>(),
                    assert::bind(range, &Range::empty)), message);
            }
        }

        template <class Config, class Category>
        struct pass;

        template <class Config>
        struct pass<Config, tags::pass::one_pass>:
            order<Config, typename Config::order::category>
        {
            explicit pass(impls::impl<typename Config::config_type>* impl)
                : order<Config, typename Config::order::category>(impl)
            {
            }

            typename Config::result::result_type next() {
                aux::check_not_empty(this, "next() called on empty range");
                return this->get()->next();
            }
        };

        template <class Config>
        struct pass<Config, tags::pass::swappable>:
            pass<Config, tags::pass::one_pass>
        {
            explicit pass(impls::impl<typename Config::config_type>* impl)
                : pass<Config, tags::pass::one_pass>(impl)
            {
            }

            using pass<Config, tags::pass::one_pass>::swap;
        };

        template <class Config>
        struct pass<Config, tags::pass::forward>:
            pass<Config, tags::pass::swappable>
        {
            explicit pass(impls::impl<typename Config::config_type>* impl)
                : pass<Config, tags::pass::swappable>(impl)
            {
            }

            typename Config::result::result_type front() const {
                aux::check_not_empty(this, "front() called on empty range");
                return this->get()->front();
            }

            void pop() {
                aux::check_not_empty(this, "pop() called on empty range");
                this->get()->pop();
            }
        };

        template <class Config>
        struct pass<Config, tags::pass::double_ended>:
            pass<Config, tags::pass::forward>
        {
            explicit pass(impls::impl<typename Config::config_type>* impl)
                : pass<Config, tags::pass::forward>(impl)
            {
            }

            typename Config::result::result_type prev() {
                aux::check_not_empty(this, "prev() called on empty range");
                return this->get()->prev();
            }

            typename Config::result::result_type back() const {
                aux::check_not_empty(this, "back() called on empty range");
                return this->get()->back();
            }

            void pop_back() {
                aux::check_not_empty(this, "pop_back() called on empty range");
                this->get()->pop_back();
            }

            void pop_front() {
                this->pop();
            }
        };
    }
}

#endif

