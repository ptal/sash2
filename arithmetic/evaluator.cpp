/* Copyright (c) 2013 by Pierre Talbot & Inigo Mediavilla
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include "evaluator.hpp"
#include "parser.hpp"

namespace sash{
namespace math{

divide_by_zero::divide_by_zero()
: std::logic_error("Division by zero detected.")
{}

ast::arithmetic_type evaluator::operator()(ast::arithmetic_type value) const
{
  return value;
}

ast::arithmetic_type evaluator::operator()(const ast::add_op& expr) const
{
  return boost::apply_visitor(evaluator(), expr.left)
       + boost::apply_visitor(evaluator(), expr.right);
}

ast::arithmetic_type evaluator::operator()(const ast::sub_op& expr) const
{
  return boost::apply_visitor(evaluator(), expr.left)
       - boost::apply_visitor(evaluator(), expr.right);
}

ast::arithmetic_type evaluator::operator()(const ast::mul_op& expr) const
{
  return boost::apply_visitor(evaluator(), expr.left)
       * boost::apply_visitor(evaluator(), expr.right);
}

ast::arithmetic_type evaluator::operator()(const ast::div_op& expr) const
{
  ast::arithmetic_type right_value = boost::apply_visitor(evaluator(), expr.right);
  if(right_value == 0)
    throw divide_by_zero();
  return boost::apply_visitor(evaluator(), expr.left)
       / right_value;
}

ast::arithmetic_type evaluator::operator()(const ast::neg_op& expr) const
{
  return -boost::apply_visitor(evaluator(), expr.expr);
}

ast::arithmetic_type evaluator::operator()(const ast::if_expr& expr) const
{
  for(const ast::if_body& body : expr.if_cases)
  {
    if(body.condition) return boost::apply_visitor(evaluator(), body.expr);
  }
  return boost::apply_visitor(evaluator(), expr.else_case);
}

/**
 *  Main function that takes an expression
 *  parsed and it evaluates it.
 *
 *  @return The result of evaluation the expression.
 * */
ast::arithmetic_type eval_expression(const std::string& expr)
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
