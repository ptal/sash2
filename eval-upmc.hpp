/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include <boost/variant.hpp>
#include <stdexcept>

/* The tutorial of boost::variant provides a starting point for the 
  implementation of the arithmetic structures. We thanks the authors
  as it is a good source of inspiration.
*/

class divide_by_zero : std::logic_error
{
public:
  divide_by_zero();
};

struct addTag{};
struct subTag{};
struct mulTag{};
struct divTag{};

template <class OpTag>
class binary_op;

typedef binary_op<addTag> add_op;
typedef binary_op<subTag> sub_op;
typedef binary_op<mulTag> mul_op;
typedef binary_op<divTag> div_op;

typedef int arithmetic_type;

typedef boost::variant<
      arithmetic_type
    , boost::recursive_wrapper<add_op>
    , boost::recursive_wrapper<sub_op>
    , boost::recursive_wrapper<mul_op>
    , boost::recursive_wrapper<div_op>
> expression;

template <class OpTag>
struct binary_op
{
  expression left;
  expression right;

  binary_op(const expression& lhs, const expression& rhs)
  : left(lhs), right(rhs)
  {}
};

class calculator : public boost::static_visitor<arithmetic_type>
{
public:
  int operator()(arithmetic_type value) const;
  int operator()(const add_op& binary) const;
  int operator()(const sub_op& binary) const;
  int operator()(const mul_op& binary) const;
  int operator()(const div_op& binary) const;
};
