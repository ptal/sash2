/* Copyright (c) 2013 by Pierre Talbot & Inigo Mediavilla
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include "evaluator.hpp"
#include "parser.hpp"
#include <functional>


namespace sash{
namespace math{

const evaluator evaluator::calculator;

divide_by_zero::divide_by_zero()
: std::logic_error("Division by zero detected.")
{}

evaluator::value_type evaluator::operator()(evaluator::value_type value) const
{
  return value;
}

evaluator::value_type evaluator::operator()(const ast::neg_op& expr) const
{
  return -boost::apply_visitor(calculator, expr.expr);
}

evaluator::value_type evaluator::operator()(const ast::if_expr& expr) const
{
  for(const ast::if_body& body : expr.if_cases)
  {
    if(body.condition)
      return boost::apply_visitor(calculator, body.expr);
  }
  return boost::apply_visitor(calculator, expr.else_case);
}

}} // namespace sash::math
