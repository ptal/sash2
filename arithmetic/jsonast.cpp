/* Copyright (c) 2013 by Pierre Talbot & Inigo Mediavilla
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include <json/json.h>
#include "jsonast.hpp"
#include "parser.hpp"

namespace sash{
namespace json{

Json::Value jsonast::operator()(math::ast::arithmetic_type value) const
{
  return Json::Value((Json::UInt)value);   
}

Json::Value jsonast::operator()(const math::ast::add_op& expr) const
{
  Json::Value event;   
  event["op"] = "add";
  event["left"] = boost::apply_visitor(jsonast(), expr.left);
  event["right"] = boost::apply_visitor(jsonast(), expr.right);
  return event;
}

Json::Value jsonast::operator()(const math::ast::sub_op& expr) const
{
  Json::Value event;   
  event["op"] = "sub";
  event["left"] = boost::apply_visitor(jsonast(), expr.left);
  event["right"] = boost::apply_visitor(jsonast(), expr.right);
  return event;
}

Json::Value jsonast::operator()(const math::ast::mul_op& expr) const
{
  Json::Value event;   
  event["op"] = "mult";
  event["left"] = boost::apply_visitor(jsonast(), expr.left);
  event["right"] = boost::apply_visitor(jsonast(), expr.right);
  return event;
}

Json::Value jsonast::operator()(const math::ast::div_op& expr) const
{
  Json::Value event;   
  event["op"] = "div";
  event["left"] = boost::apply_visitor(jsonast(), expr.left);
  event["right"] = boost::apply_visitor(jsonast(), expr.right);
  return event;
}

Json::Value jsonast::operator()(const math::ast::neg_op& expr) const
{
  Json::Value event;   
  event["op"] = "neg";
  event["val"] = boost::apply_visitor(jsonast(), expr.expr);
  return event;
}

Json::Value jsonast::operator()(const math::ast::if_expr& expr) const
{
  Json::Value event;   
  int ifcounter = 0;
  for(const math::ast::if_body& body : expr.if_cases)
  {
     event["if"+ifcounter] = boost::apply_visitor(jsonast(), body.expr);
     ifcounter++;
  }
  event["else"] = boost::apply_visitor(jsonast(), expr.else_case);
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
  bool r = boost::spirit::qi::parse(first, last, parser, arith_ast);
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
