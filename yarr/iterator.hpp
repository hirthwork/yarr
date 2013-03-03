/*
 * iterator                 iterators pair wrapping range
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

#ifndef __YARR__ITERATOR_HPP__2013_03_03__
#define __YARR__ITERATOR_HPP__2013_03_03__

#include <iterator>

#if __cplusplus >= 201103L
#include <utility>
#else
#include <algorithm>
#endif

#include "config.hpp"
#include "tags.hpp"

namespace yarr {
    namespace iterator {
        namespace impl {
            template <class IteratorCategory>
            struct pass;

            template <>
            struct pass<std::input_iterator_tag> {
                typedef tags::pass::swappable tag;
            };

            template <>
            struct pass<std::forward_iterator_tag> {
                typedef tags::pass::forward tag;
            };

            template <>
            struct pass<std::bidirectional_iterator_tag> {
                typedef tags::pass::double_ended tag;
            };

            template <>
            struct pass<std::random_access_iterator_tag> {
                typedef tags::pass::double_ended tag;
            };

            namespace aux {
                template <class IteratorCategory>
                struct order_tag {
                    typedef tags::order::sequential tag;
                };

                template <>
                struct order_tag<std::random_access_iterator_tag> {
                    typedef tags::order::random tag;
                };

                template <class Iterator, class OrderTag>
                struct order {
                    typedef yarr::config::order<OrderTag> config;
                };

                template <class Iterator>
                struct order<Iterator, tags::order::random> {
                    typedef yarr::config::order<tags::order::random,
                        typename std::iterator_traits<
                            Iterator>::difference_type> config;
                };
            }

            template <class Iterator>
            struct order: aux::order<Iterator, typename aux::order_tag<
                    typename std::iterator_traits<Iterator>::iterator_category
                >::tag>
            {
            };

            namespace aux {
                template <class Iterator, class IteratorCategory>
                struct length {
                    typedef yarr::config::length<tags::length::finite> config;
                };

                template <class Iterator>
                struct length<Iterator, std::random_access_iterator_tag> {
                    typedef yarr::config::length<tags::length::fixed,
                        typename std::iterator_traits<
                            Iterator>::difference_type> config;
                };
            }

            template <class Iterator>
            struct length: aux::length<Iterator,
                typename std::iterator_traits<Iterator>::iterator_category>
            {
            };

            template <class Iterator,
                class ResultTag = tags::result::reference>
            struct config {
                typedef yarr::config::config<
                    yarr::config::pass<typename pass<
                        typename std::iterator_traits<
                            Iterator>::iterator_category>::tag>,
                    typename order<Iterator>::config,
                    yarr::config::iotype<tags::iotype::input>,
                    typename length<Iterator>::config,
                    yarr::config::result<ResultTag,
                        typename std::iterator_traits<Iterator>::value_type,
                        typename std::iterator_traits<Iterator>::reference>
                > type;
            };

            template <class Iterator, class Config, class Tag>
            struct iterator: iterator<Iterator, Config,
                typename tags::next_tag<Tag, Config>::tag>
            {
                iterator(Iterator begin, Iterator end)
                    : iterator<Iterator, Config,
                        typename tags::next_tag<Tag, Config>::tag>(begin, end)
                {
                }
            };

            // Minimal configuration is:
            // swappable, sequential, input, finite, reference
            template <class Iterator, class Config>
            class iterator<Iterator, Config, void> {
            protected:
                Iterator begin;
                Iterator end;

            public:
                typedef typename Config::result::value_type value_type;
                typedef typename Config::result::reference reference;

                iterator(Iterator begin, Iterator end)
                    : begin(begin)
                    , end(end)
                {
                }

                // TODO: force noexcept
                void swap(iterator& rhs) {
                    std::swap(begin, rhs.begin);
                    std::swap(end, rhs.end);
                }

                value_type next() {
                    return *begin++;
                }

                void pop() {
                    ++begin;
                }

                reference front() const {
                    return *begin();
                }

                bool empty() const {
                    return begin == end;
                }
            };

            template <class Iterator, class Config>
            struct iterator<Iterator, Config, tags::length::fixed>:
                iterator<Iterator, Config,
                    typename tags::next_tag<tags::length::fixed, Config>::tag>
            {
                typedef iterator<Iterator, Config,
                    typename tags::next_tag<tags::length::fixed, Config>::tag>
                    base;
                typedef typename Config::length::size_type size_type;

                iterator(Iterator begin, Iterator end)
                    : base(begin, end)
                {
                }

                size_type size() const {
                    return this->end - this->begin;
                }
            };

            template <class Iterator, class Config>
            struct iterator<Iterator, Config, tags::order::random>:
                iterator<Iterator, Config,
                    typename tags::next_tag<tags::order::random, Config>::tag>
            {
                typedef iterator<Iterator, Config,
                    typename tags::next_tag<tags::order::random, Config>::tag>
                    base;
                typedef typename Config::order::pos_type pos_type;

                iterator(Iterator begin, Iterator end)
                    : base(begin, end)
                {
                }

                typename base::reference at(pos_type n) const {
                    return this->begin[n];
                }

                void skip(pos_type n) {
                    this->begin += n;
                }
            };

            namespace aux {
                template <class Iterator, class Config, class OrderTag>
                struct iterator: impl::iterator<Iterator, Config,
                    typename tags::next_tag<tags::pass::double_ended,
                        Config>::tag>
                {
                    typedef impl::iterator<Iterator, Config,
                        typename tags::next_tag<tags::pass::double_ended,
                            Config>::tag> base;

                    iterator(Iterator begin, Iterator end)
                        : base(begin, end)
                    {
                    }
                };

                template <class Iterator, class Config>
                struct iterator<Iterator, Config, tags::order::random>:
                    impl::iterator<Iterator, Config,
                        typename tags::next_tag<tags::pass::double_ended,
                            Config>::tag>
                {
                    typedef impl::iterator<Iterator, Config,
                        typename tags::next_tag<tags::pass::double_ended,
                            Config>::tag> base;

                    iterator(Iterator begin, Iterator end)
                        : base(begin, end)
                    {
                    }

                    typename base::reference rat(
                        typename base::pos_type n) const
                    {
                        return this->end[-++n];
                    }

                    void truncate(typename base::pos_type n) {
                        this->end -= n;
                    }
                };
            }

            template <class Iterator, class Config>
            struct iterator<Iterator, Config, tags::pass::double_ended>:
                aux::iterator<Iterator, Config, typename Config::order::tag>
            {
                typedef aux::iterator<Iterator, Config,
                    typename Config::order::tag> base;

                iterator(Iterator begin, Iterator end)
                    : base(begin, end)
                {
                }

                typename base::value_type prev() {
                    return *--this->end;
                }

                typename base::reference back() const {
                    Iterator iter = this->end;
                    return *--iter;
                }

                void pop_back() {
                    --this->end;
                }
            };

            template <class Iterator, class Config>
            struct start: iterator<Iterator, Config,
                typename tags::root_tag<Config>::tag>
            {
                start(Iterator begin, Iterator end)
                    : iterator<Iterator, Config,
                        typename tags::root_tag<Config>::tag>(begin, end)
                {
                }
            };
        }

        template <class Iterator>
        struct iterator: impl::start<Iterator,
            typename impl::config<Iterator>::type>
        {
            // XXX: select ref or copy
            iterator(Iterator begin, Iterator end)
                : impl::start<Iterator,
                    typename impl::config<Iterator>::type>(begin, end)
            {
            }
        };
    }
}

namespace std {
    template <class Iterator>
    void swap(yarr::iterator::iterator<Iterator>& lhs,
        yarr::iterator::iterator<Iterator>& rhs)
    {
        lhs.swap(rhs);
    }
}

#endif

