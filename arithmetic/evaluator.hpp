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

namespace sash{
namespace math{

class divide_by_zero : std::logic_error
{
public:
  divide_by_zero();
};


class evaluator : public boost::static_visitor<ast::arithmetic_type>
{
public:
  ast::arithmetic_type operator()(ast::arithmetic_type value) const;
  ast::arithmetic_type operator()(const ast::add_op& expr) const;
  ast::arithmetic_type operator()(const ast::sub_op& expr) const;
  ast::arithmetic_type operator()(const ast::mul_op& expr) const;
  ast::arithmetic_type operator()(const ast::div_op& expr) const;
  ast::arithmetic_type operator()(const ast::neg_op& expr) const;
  ast::arithmetic_type operator()(const ast::if_expr& expr) const;
  bool operator()(const ast::boolean_expr& expr) const;
};

ast::arithmetic_type eval_expression(const std::string& expr);

}} // namespace sash::math

#endif // SASH_MATH_EVALUATOR_HPP
