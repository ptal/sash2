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
  char *envvar_raw = getenv(var_name.c_str());
  if(envvar_raw == NULL)
  {
    throw std::runtime_error("Empty environment variable \'" + var_name + "\' inside arithmetic expression.");
  }
  std::string envvar(envvar_raw, strlen(envvar_raw));
  try
  {
    return boost::lexical_cast<long>(envvar_raw);
  }
  catch(...)
  {
    throw std::runtime_error("Non-arithmetic variable inside arithmetic expression ("+var_name + " = " + envvar + ").");
  }
}

}} // namespace sash::math
