/*
  Copyright (C) 2013 by Pierre Talbot <ptalbot@hyc.io> & Inigo Mediavilla

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY.

  See the COPYING file for more details.
*/

#ifndef SASH_MATH_PARSER_DEF_HPP
#define SASH_MATH_PARSER_DEF_HPP

// #define BOOST_SPIRIT_DEBUG
// #define BOOST_SPIRIT_QI_DEBUG
#include "parser.hpp"
#include <boost/spirit/include/phoenix.hpp>
#include <boost/lexical_cast.hpp>

namespace sash{
namespace math{

namespace bs = boost::spirit;
namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename Iterator>
grammar<Iterator>::grammar()
  : grammar::base_type(start, "arithmetic expression")
{
  using boost::spirit::ascii::alnum;
  using boost::spirit::ascii::string;
  /**
  * These rules permit the automatic generation of semantic rules (AST
  * creation) because they are typed. (see the parser.hpp to look at the
  * type.)
  */
  // arithmetic = function_def | expression;
  // function_def %= var_expr > '(' > list_args > ')' > '=' > expression;
  start %= relational_eq;

  relational_eq = relational_comp [qi::_val = qi::_1]
              >> *( eq_expr(qi::_val) [qi::_val = qi::_1]
                  | ne_expr(qi::_val) [qi::_val = qi::_1]);

  relational_comp = expression [qi::_val = qi::_1]
             >> *( lt_expr(qi::_val) [qi::_val = qi::_1]
                 | gt_expr(qi::_val) [qi::_val = qi::_1]
                 | ge_expr(qi::_val) [qi::_val = qi::_1]
                 | le_expr(qi::_val) [qi::_val = qi::_1]);

  expression = term [qi::_val = qi::_1] 
             >> *( add_expr(qi::_val) [qi::_val = qi::_1]
                 | sub_expr(qi::_val) [qi::_val = qi::_1]);

  term = factor [qi::_val = qi::_1] 
             >> *( mul_expr(qi::_val) [qi::_val = qi::_1]
                 | div_expr(qi::_val) [qi::_val = qi::_1]);

  factor %=
        qi::ulong_
      | envvar_expr
      | if_expr
      | ('(' >> start >> ')')
      | neg_expr
      | ('+' >> factor)
      ;

  envvar_expr =  ('$' > var_expr) [qi::_val = phx::bind(&envvar_to_long, qi::_1)];

  add_expr %= (qi::attr(qi::_r1) >> '+' >> term);
  sub_expr %= (qi::attr(qi::_r1) >> '-' >> term);
  mul_expr %= (qi::attr(qi::_r1) >> '*' >> factor);
  div_expr %= (qi::attr(qi::_r1) >> '/' >> factor);
  lt_expr %= (qi::attr(qi::_r1) >> '<' >> expression);
  gt_expr %= (qi::attr(qi::_r1) >> '>' >> expression);
  eq_expr %= (qi::attr(qi::_r1) >> "==" >> expression);
  le_expr %= (qi::attr(qi::_r1) >> "=<" >> expression);
  ge_expr %= (qi::attr(qi::_r1) >> "=>" >> relational_comp);
  ne_expr %= (qi::attr(qi::_r1) >> "!=" >> relational_comp);
  neg_expr %= ('-' >> factor);

  if_expr %= "if" >> (if_body % string("else if")) >> ("else" > start) ;
  if_body %= start >> ("then" > start);

  var_expr = qi::lexeme[(*alnum)] [qi::_val = 
    phx::construct<std::string>(phx::begin(qi::_1), phx::end(qi::_1))] ;

  BOOST_SPIRIT_DEBUG_NODES(
          (start)
          (relational_eq)
          (relational_comp)
          (expression)
          (term)
          (factor)
          (add_expr)
          (sub_expr)
          (mul_expr)
          (div_expr)
          (neg_expr)
          (lt_expr)
          (gt_expr)
          (ge_expr)
          (le_expr)
          (ne_expr)
          (eq_expr)
          (var_expr)
      );

  using namespace qi::labels;
  qi::on_error<qi::fail>
  (
    expression,
    std::cout
      << phx::val("Error! Expecting ")
      << bs::_4                               // what failed?
      << phx::val(" here: \"")
      << phx::construct<std::string>(bs::_3, bs::_2)   // iterators to error-pos, end
      << phx::val("\"")
      << std::endl
  );
}

}} // namespace sash::math

#endif // SASH_MATH_PARSER_DEF_HPP
