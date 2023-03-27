/**
 * @file opcall.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

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