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

/**
 *  Main function that takes an expression
 *  parsed and it evaluates it.
 *
 *  @return The result of evaluation the expression.
 * */
evaluator::value_type eval_expression(const std::string& expr)
{
  static const grammar_type parser;

  // At this point we generate the iterator pair
  iterator_type first(expr.begin());
  iterator_type last(expr.end());

  ast::expression arith_ast;
  bool r = boost::spirit::qi::parse(first, last, parser, arith_ast);
  if (r && first == last)
  {
    static const evaluator calculator;
    return boost::apply_visitor(calculator, arith_ast);
  }
  else
  {
    std::string s(first, last);
    throw std::invalid_argument("The arithmetic expression is malformed (" + s + ")");
  }
}

}} // namespace sash::math
