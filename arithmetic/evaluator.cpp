/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include "evaluator.hpp"

namespace sash{
namespace math{

divide_by_zero::divide_by_zero()
: std::logic_error("Division by zero detected.")
{}

int evaluator::operator()(arithmetic_type value) const
{
  return value;
}

int evaluator::operator()(const add_op& binary) const
{
  return boost::apply_visitor(evaluator(), binary.left)
       + boost::apply_visitor(evaluator(), binary.right);
}

int evaluator::operator()(const sub_op& binary) const
{
  return boost::apply_visitor(evaluator(), binary.left)
       - boost::apply_visitor(evaluator(), binary.right);
}

int evaluator::operator()(const mul_op& binary) const
{
  return boost::apply_visitor(evaluator(), binary.left)
       * boost::apply_visitor(evaluator(), binary.right);
}

int evaluator::operator()(const div_op& binary) const
{
  arithmetic_type right_value = boost::apply_visitor(evaluator(), binary.right);
  if(right_value == 0)
    throw divide_by_zero();
  return boost::apply_visitor(evaluator(), binary.left)
       / right_value;
}

}} // namespace sash::math
