/*
	Copyright (C) 2013 by Pierre Talbot <ptalbot@hyc.io> & Inigo Mediavilla
	Part of the Battle for Wesnoth Project http://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

#include "parser.tcc"

namespace sash{
namespace math{
template struct grammar<iterator_type>;


long envvar_to_long(const std::string& var_name)
{
  char *envvar = getenv(var_name.c_str());
  if(envvar == NULL)
  {
    throw std::runtime_error("Empty environment variable inside arithmetic expression.");
  }
  try
  {
    return boost::lexical_cast<long>(std::string(envvar, strlen(envvar)));
  }
  catch(...)
  {
    throw std::runtime_error("Non-arithmetic variable inside arithmetic expression.");
  }
}

}} // namespace sash::math
