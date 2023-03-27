/**
 * @file parser.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef STICK_PARSER_HPP
#define STICK_PARSER_HPP

#include <lexer/lexer.hpp>
#include <parser/types/opcall.hpp>

namespace Stick {

class SyntaxError : public std::runtime_error {
 public:
  SyntaxError(const std::string& message) : std::runtime_error(message) {}
  static void Throw(const std::string& message) { throw SyntaxError(message); }
};

class Parser {
 public:
  Parser(const std::string&);

  void   seek(size_t);
  OpCall nextOperation();

 private:
  Lexer lexer;
  Token lookahead;

  void match(TokenType);
  void moveLookahead();

  OpValue evaluateExpression();
  OpValue evaluateReference();
  int64_t evaluateMath();
};
}  // namespace Stick

#endif