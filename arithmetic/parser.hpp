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

#ifndef SASH_MATH_PARSER_HPP
#define SASH_MATH_PARSER_HPP

#include "ast.hpp"

#include <boost/spirit/include/qi.hpp>

namespace sash{
namespace math{

namespace bs = boost::spirit;
namespace qi = boost::spirit::qi;

template <typename Iterator>
struct grammar 
	: qi::grammar<Iterator, ast::expression()>
{
	typedef Iterator iterator_type;

	grammar();

private:
	ast::expression arithmetic_expr;

  template <typename Arg> using rule = qi::rule<iterator_type, Arg()>;
  rule<ast::expression> expression;
  rule<ast::add_op> add_expr;
  rule<ast::sub_op> sub_expr;
  rule<ast::mul_op> mul_expr;
  rule<ast::div_op> div_expr;
  rule<ast::neg_op> neg_expr;
  rule<ast::expression> term;
  rule<ast::expression> factor;
};

// iterator type used to expose the underlying input stream.
typedef std::string::const_iterator iterator_type;

typedef grammar<iterator_type> grammar_type;

}} // namespace sash::math
#endif // SASH_MATH_PARSER_HPP
