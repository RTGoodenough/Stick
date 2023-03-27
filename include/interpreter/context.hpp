/**
 * @file context.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef STICK_CONTEXT_HPP
#define STICK_CONTEXT_HPP

#include <iostream>
#include <stack>

enum Eval {
  TRUE,
  FALSE,
  SKIP,
};

struct Context {
  std::stack<int64_t> values;
  std::stack<size_t>  loops;
  std::stack<Eval>    run;
};

#endif