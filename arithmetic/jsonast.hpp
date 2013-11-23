/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#ifndef SASH_MATH_EVALUATOR_HPP
#define SASH_MATH_EVALUATOR_HPP

#include "ast.hpp"

#include <stdexcept>
#include <string>
#include <json/json.h>

namespace sash{
namespace json{

class jsonast : public boost::static_visitor<Json::Value>
{
public:
  Json::Value operator()(math::ast::arithmetic_type value) const;
  Json::Value operator()(const math::ast::add_op& expr) const;
  Json::Value operator()(const math::ast::sub_op& expr) const;
  Json::Value operator()(const math::ast::mul_op& expr) const;
  Json::Value operator()(const math::ast::div_op& expr) const;
  Json::Value operator()(const math::ast::neg_op& expr) const;
};

Json::Value eval_expression(const std::string& expr);

}} // namespace sash::json

#endif // SASH_MATH_EVALUATOR_HPP
