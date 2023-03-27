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