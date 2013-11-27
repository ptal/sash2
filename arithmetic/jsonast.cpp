/* Copyright (c) 2013 by Pierre Talbot & Inigo Mediavilla
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include <json/json.h>
#include "jsonast.hpp"
#include "parser.hpp"

namespace sash{
namespace math{

const std::string ArithmeticName<ast::addTag>::name("add");
const std::string ArithmeticName<ast::subTag>::name("sub");
const std::string ArithmeticName<ast::mulTag>::name("mul");
const std::string ArithmeticName<ast::divTag>::name("div");

const std::string ArithmeticName<ast::ltTag>::name("lt");
const std::string ArithmeticName<ast::gtTag>::name("gt");
const std::string ArithmeticName<ast::eqTag>::name("eq");
const std::string ArithmeticName<ast::leTag>::name("le");
const std::string ArithmeticName<ast::geTag>::name("ge");
const std::string ArithmeticName<ast::neTag>::name("ne");

} // namespace math

namespace json{

const jsonast jsonast::jsonifier;

Json::Value jsonast::operator()(math::ast::arithmetic_type value) const
{
  return Json::Value((Json::UInt)value);   
}

Json::Value jsonast::operator()(const math::ast::neg_op& expr) const
{
  Json::Value event;   
  event["op"] = "neg";
  event["val"] = boost::apply_visitor(jsonifier, expr.expr);
  return event;
}

Json::Value jsonast::operator()(const math::ast::if_expr& expr) const
{
  Json::Value event;   
  int ifcounter = 0;
  for(const math::ast::if_body& body : expr.if_cases)
  {
     event["if"+ifcounter] = boost::apply_visitor(jsonifier, body.expr);
     ifcounter++;
  }
  event["else"] = boost::apply_visitor(jsonifier, expr.else_case);
  return event;
}

}} // namespace sash::json
