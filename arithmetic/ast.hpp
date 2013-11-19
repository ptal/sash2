/*
	Copyright (C) 2013 by Pierre Talbot <ptalbot@hyc.io>
	Part of the Battle for Wesnoth Project http://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

#ifndef SASH_AST_HPP
#define SASH_AST_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace sash{
namespace math{

/* The tutorial of boost::variant provides a starting point for the 
  implementation of the arithmetic structures. We thanks the authors
  as it is a good source of inspiration.
*/
struct addTag{};
struct subTag{};
struct mulTag{};
struct divTag{};

template <class OpTag>
class binary_op;

typedef binary_op<addTag> add_op;
typedef binary_op<subTag> sub_op;
typedef binary_op<mulTag> mul_op;
typedef binary_op<divTag> div_op;

typedef int arithmetic_type;

typedef boost::variant<
      arithmetic_type
    , boost::recursive_wrapper<add_op>
    , boost::recursive_wrapper<sub_op>
    , boost::recursive_wrapper<mul_op>
    , boost::recursive_wrapper<div_op>
> expression;

template <class OpTag>
struct binary_op
{
  expression left;
  expression right;

  binary_op(const expression& lhs, const expression& rhs)
  : left(lhs), right(rhs)
  {}
};

}} // namespace sash::math

#endif // SASH_AST_HPP
