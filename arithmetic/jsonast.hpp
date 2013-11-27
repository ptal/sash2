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
namespace math{

template <class OpTag>
struct ArithmeticName;

template <>
struct ArithmeticName<ast::addTag>
{
  static const std::string name;
};

template <>
struct ArithmeticName<ast::subTag>
{
  static const std::string name;
};

template <>
struct ArithmeticName<ast::mulTag>
{
  static const std::string name;
};

template <>
struct ArithmeticName<ast::divTag>
{
  static const std::string name;
};


template <>
struct ArithmeticName<ast::ltTag>
{
  static const std::string name;
};

template <>
struct ArithmeticName<ast::gtTag>
{
  static const std::string name;
};

template <>
struct ArithmeticName<ast::eqTag>
{
  static const std::string name;
};

template <>
struct ArithmeticName<ast::leTag>
{
  static const std::string name;
};

template <>
struct ArithmeticName<ast::geTag>
{
  static const std::string name;
};

template <>
struct ArithmeticName<ast::neTag>
{
  static const std::string name;
};

} // namespace math

namespace json{

template <class OpTag>
struct json_binary_op
{
  typedef Json::Value value_type;
  static value_type eval(value_type v1, value_type v2)
  {
    value_type event;
    event["op"] = math::ArithmeticName<OpTag>::name;
    event["left"] = v1;
    event["right"] = v2;
    return event;
  }
};

class jsonast : public boost::static_visitor<Json::Value>
{
  static const jsonast jsonifier;
public:
  Json::Value operator()(math::ast::arithmetic_type value) const;

	template <class OpTag>
	Json::Value operator()(const math::ast::binary_op<OpTag>& expr) const
	{
	  return math::ast::visit_binary_op<json_binary_op<OpTag> >(expr, jsonifier);
	}

  Json::Value operator()(const math::ast::neg_op& expr) const;
  Json::Value operator()(const math::ast::if_expr& expr) const;
};

}} // namespace sash::json

#endif // SASH_MATH_EVALUATOR_HPP
