/*
  Copyright (C) 2013 by Pierre Talbot <ptalbot@hyc.io> & Inigo Mediavilla

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
#include <boost/optional.hpp>

namespace sash{
namespace math{
namespace ast{

// Arithmetic operators.
struct addTag;
struct subTag;
struct mulTag;
struct divTag;

// Comparison operators.
struct ltTag;
struct gtTag;
struct eqTag;
struct leTag;
struct geTag;
struct neTag;

// Logical operators;
// struct andTag;
// struct orTag;
// struct notTag;

// Forward declaration to define the expression variant.
template <class OpTag>
struct binary_op;

struct neg_op;
struct if_expr;

typedef binary_op<addTag> add_op;
typedef binary_op<subTag> sub_op;
typedef binary_op<mulTag> mul_op;
typedef binary_op<divTag> div_op;

typedef binary_op<ltTag> lt_op;
typedef binary_op<gtTag> gt_op;
typedef binary_op<eqTag> eq_op;
typedef binary_op<leTag> le_op;
typedef binary_op<geTag> ge_op;
typedef binary_op<neTag> ne_op;

typedef long arithmetic_type;

typedef boost::variant<
      arithmetic_type
    , boost::recursive_wrapper<add_op>
    , boost::recursive_wrapper<sub_op>
    , boost::recursive_wrapper<mul_op>
    , boost::recursive_wrapper<div_op>
    , boost::recursive_wrapper<lt_op>
    , boost::recursive_wrapper<gt_op>
    , boost::recursive_wrapper<eq_op>
    , boost::recursive_wrapper<le_op>
    , boost::recursive_wrapper<ge_op>
    , boost::recursive_wrapper<ne_op>
    , boost::recursive_wrapper<neg_op>
    , boost::recursive_wrapper<if_expr>
> expression;

template <class OpTag>
struct binary_op
{
  typedef OpTag operation_type;

  expression left;
  expression right;

  binary_op(const expression& left, const expression& right)
  : left(left), right(right)
  {}

  binary_op() = default;
  binary_op(const binary_op&) = default;
};

template <class Operation, class OpTag, class Visitor>
typename Visitor::result_type visit_binary_op(const binary_op<OpTag>& expr, const Visitor& visitor)
{
  return Operation::eval(
    boost::apply_visitor(visitor, expr.left),
    boost::apply_visitor(visitor, expr.right));
}

struct neg_op
{
  expression expr;

  neg_op(const expression& expr)
  : expr(expr)
  {}

  neg_op() = default;
  neg_op(const neg_op&) = default;
};

struct if_body
{
  expression condition;
  expression expr;

  if_body(const expression& condition, const expression& expr)
  : condition(condition)
  , expr(expr)
  {}

  if_body() = default;
  if_body(const if_body&) = default;
};

struct if_expr
{
  std::vector<if_body> if_cases; // contains the if and the "else if"
  expression else_case;

  if_expr(const std::vector<if_body>& if_cases, const expression& else_case)
  : if_cases(if_cases)
  , else_case(else_case)
  {}

  if_expr() = default;
  if_expr(const if_expr&) = default;
};

}}} // namespace sash::math::ast

// Fusion AST adaptation.
// This permit Boost.Spirit to automatically construct AST from the parsing rules.
BOOST_FUSION_ADAPT_STRUCT(
  sash::math::ast::neg_op,
  (sash::math::ast::expression, expr)
);

BOOST_FUSION_ADAPT_STRUCT(
  sash::math::ast::if_body,
  (sash::math::ast::expression, condition)
  (sash::math::ast::expression, expr)
);

BOOST_FUSION_ADAPT_STRUCT(
  sash::math::ast::if_expr,
  (std::vector<sash::math::ast::if_body>, if_cases)
  (sash::math::ast::expression, else_case)
);

BOOST_FUSION_ADAPT_TPL_STRUCT(
  (OpTag),
  (sash::math::ast::binary_op) (OpTag),
  (sash::math::ast::expression, left)
  (sash::math::ast::expression, right)
);

#endif // SASH_MATH_AST_HPP
