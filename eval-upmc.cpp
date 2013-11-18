/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include "eval-upmc.hpp"

divide_by_zero::divide_by_zero()
: std::logic_error("Division by zero detected.")
{}

int calculator::operator()(arithmetic_type value) const
{
  return value;
}

int calculator::operator()(const add_op& binary) const
{
  return boost::apply_visitor(calculator(), binary.left)
       + boost::apply_visitor(calculator(), binary.right);
}

int calculator::operator()(const sub_op& binary) const
{
  return boost::apply_visitor(calculator(), binary.left)
       - boost::apply_visitor(calculator(), binary.right);
}

int calculator::operator()(const mul_op& binary) const
{
  return boost::apply_visitor(calculator(), binary.left)
       * boost::apply_visitor(calculator(), binary.right);
}

int calculator::operator()(const div_op& binary) const
{
  arithmetic_type right_value = boost::apply_visitor(calculator(), binary.right);
  if(right_value == 0)
    throw divide_by_zero();
  return boost::apply_visitor(calculator(), binary.left)
       / right_value;
}
