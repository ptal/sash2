/* Copyright (c) 2013 by Pierre Talbot & Inigo Mediavilla
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#ifndef SASH_MATH_EVALUATOR_HPP
#define SASH_MATH_EVALUATOR_HPP

#include "ast.hpp"

#include <stdexcept>
#include <string>
#include <iterator>

namespace sash{
namespace math{

class divide_by_zero : std::logic_error
{
public:
  divide_by_zero();
};

template <class OpTag>
struct ArithmeticOp;

template <>
struct ArithmeticOp<ast::addTag>
{
  typedef ast::arithmetic_type value_type;
  static value_type eval(value_type v1, value_type v2)
  {
    return v1 + v2;
  }
};

template <>
struct ArithmeticOp<ast::subTag>
{
  typedef ast::arithmetic_type value_type;
  static value_type eval(value_type v1, value_type v2)
  {
    return v1 - v2;
  }
};

template <>
struct ArithmeticOp<ast::mulTag>
{
  typedef ast::arithmetic_type value_type;
  static value_type eval(value_type v1, value_type v2)
  {
    return v1 * v2;
  }
};

template <>
struct ArithmeticOp<ast::divTag>
{
  typedef ast::arithmetic_type value_type;
  static value_type eval(value_type v1, value_type v2)
  {
    if(v2 == 0)
      throw divide_by_zero();
    return v1 / v2;
  }
};

class evaluator : public boost::static_visitor<ast::arithmetic_type>
{
public:
  static const evaluator calculator;
  typedef ast::arithmetic_type value_type;

  value_type operator()(value_type value) const;

  template <class OpTag>
  value_type operator()(const ast::binary_op<OpTag>& expr) const
  {
    return ast::visit_binary_op<ArithmeticOp<OpTag> >(expr, calculator);
  }

  value_type operator()(const ast::neg_op& expr) const;
  value_type operator()(const ast::if_expr& expr) const;
};

ast::arithmetic_type eval_expression(const std::string& expr);

}} // namespace sash::math

#endif // SASH_MATH_EVALUATOR_HPP
