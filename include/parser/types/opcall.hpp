#ifndef STICK_OPCALL_HPP
#define STICK_OPCALL_HPP

#include <lexer/operations/operations.hpp>
#include <lexer/types/token.hpp>

typedef TokenValue OpValue;

struct Expression {
  BoolOp  boolean;
  OpValue value;
};

struct OpCall {
  OpType     type;
  Expression expression;
  size_t     position;
};

#endif