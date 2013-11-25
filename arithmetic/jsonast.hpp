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
#include <json/json.h>

namespace sash{
namespace json{

template <struct OpTag>
struct json_binary_op
{
  typedef Json::Value value_type;
  static value_type eval(value_type v1, value_type v2)
  {
    value_type event;
    event["op"] = ArithmeticOp<OpTag>::name;
    event["left"] = v1;
    event["right"] = ;
    return event;
  }
};

class jsonast : public boost::static_visitor<Json::Value>
{
public:
  Json::Value operator()(math::ast::arithmetic_type value) const;

	template <class OpTag>
	Json::Value jsonast::operator()(const math::ast::binary_op<OpTag>& expr) const
	{
	  Json::Value event;   
	  // event["op"] = "div";
	  // event["left"] = boost::apply_visitor(jsonast(), expr.left);
	  // event["right"] = boost::apply_visitor(jsonast(), expr.right);
	  return event;
	}

  Json::Value operator()(const math::ast::neg_op& expr) const;
  Json::Value operator()(const math::ast::if_expr& expr) const;
};

Json::Value eval_expression(const std::string& expr);

}} // namespace sash::json

#endif // SASH_MATH_EVALUATOR_HPP
