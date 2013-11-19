/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#ifndef SASH_MATH_EVALUATOR_HPP
#define SASH_MATH_EVALUATOR_HPP

#include <stdexcept>
#include "ast.hpp"

namespace sash{
namespace math{

class divide_by_zero : std::logic_error
{
public:
  divide_by_zero();
};


class evaluator : public boost::static_visitor<arithmetic_type>
{
public:
  int operator()(arithmetic_type value) const;
  int operator()(const add_op& binary) const;
  int operator()(const sub_op& binary) const;
  int operator()(const mul_op& binary) const;
  int operator()(const div_op& binary) const;
};

}} // namespace sash::math

#endif // SASH_MATH_EVALUATOR_HPP
