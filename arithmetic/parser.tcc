/*
  Copyright (C) 2013 by Pierre Talbot <ptalbot@hyc.io>
  Part of the Battle for Wesnoth Project http://www.wesnoth.org/

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

namespace sash{
namespace math{

namespace bs = boost::spirit;
namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename Iterator>
grammar<Iterator>::grammar()
  : grammar::base_type(expression, "arithmetic expression")
{
    /**
  * These rules permit the automatic generation of semantic rules (AST
  * creation) because they are typed. (see the parser.hpp to look at the
  * type.)
  */
  expression %= add_expr | sub_expr | term;
  term       %= mul_expr | div_expr | factor;

  factor %=
        qi::ulong_
      | ('(' >> expression >> ')')
      | neg_expr
      | ('+' >> factor)
      ;

  add_expr %= (term >> '+' >> expression) ;
  sub_expr %= (term >> '-' >> expression) ;
  mul_expr %= (factor >> '*' >> term) ;
  div_expr %= (factor >> "\\" >> term) ;
  neg_expr %= ('-' >> factor) ;

  BOOST_SPIRIT_DEBUG_NODES(
          (expression)
          (term)
          (factor)
          (add_expr)
          (sub_expr)
          (mul_expr)
          (div_expr)
          (neg_expr)
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