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

#ifndef SASH_MATH_AST_HPP
#define SASH_MATH_AST_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

namespace sash{
namespace math{
namespace ast{

struct addTag;
struct subTag;
struct mulTag;
struct divTag;

template <class OpTag>
struct binary_op;

struct neg_op;

typedef binary_op<addTag> add_op;
typedef binary_op<subTag> sub_op;
typedef binary_op<mulTag> mul_op;
typedef binary_op<divTag> div_op;

typedef long arithmetic_type;

typedef boost::variant<
      arithmetic_type
    , boost::recursive_wrapper<add_op>
    , boost::recursive_wrapper<sub_op>
    , boost::recursive_wrapper<mul_op>
    , boost::recursive_wrapper<div_op>
    , boost::recursive_wrapper<neg_op>
> expression;

template <class OpTag>
struct binary_op
{
  typedef OpTag operation_type;

  expression left;
  expression right;

  binary_op(const expression& lhs, const expression& rhs)
  : left(lhs), right(rhs)
  {}

  binary_op() = default;
  binary_op(const binary_op&) = default;
};

struct neg_op
{
  expression expr;

  neg_op(const expression& expr)
  : expr(expr)
  {}

  neg_op() = default;
  neg_op(const neg_op&) = default;
};

}}} // namespace sash::math::ast

// Fusion AST adaptation.
BOOST_FUSION_ADAPT_STRUCT(
  sash::math::ast::neg_op,
  (sash::math::ast::expression, expr)
);

BOOST_FUSION_ADAPT_TPL_STRUCT(
  (OpTag),
  (sash::math::ast::binary_op) (OpTag),
  (sash::math::ast::expression, left)
  (sash::math::ast::expression, right)
);
#endif // SASH_MATH_AST_HPP
