/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include "arithmetic/evaluator.hpp"
#include <iostream>

using namespace sash::math;

void test()
{
  expression result(add_op(5,6));
  std::cout << boost::apply_visitor(evaluator(), result) << std::endl;
}