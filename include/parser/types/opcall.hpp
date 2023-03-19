#ifndef STICK_OPCALL_HPP
#define STICK_OPCALL_HPP

#include <lexer/operations/operations.hpp>
#include <lexer/types/token.hpp>

typedef TokenValue OpValue;

struct OpCall {
  OpType  type;
  OpValue value;
  bool    referenceValue;
};

#endif