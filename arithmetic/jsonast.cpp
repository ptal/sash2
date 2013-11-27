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

/**
 *  Main function that takes an expression
 *  parsed and it passes it to a visitor that generates
 *  a json representation of th AST.
 *
 *  @return Json representation of the AST.
 * */
Json::Value eval_expression(const std::string& expr)
{
  static const math::grammar_type parser;

  // At this point we generate the iterator pair
  math::iterator_type first(expr.begin());
  math::iterator_type last(expr.end());

  math::ast::expression arith_ast;
  bool r = boost::spirit::qi::phrase_parse(first, last, parser, boost::spirit::ascii::space, arith_ast);
  if (r && first == last)
  {
    static const jsonast jsonconverter;
    return boost::apply_visitor(jsonconverter, arith_ast);
  }
  else
  {
    throw std::invalid_argument("The arithmetic expression is malformed.\n");
  }
}

}} // namespace sash::json
