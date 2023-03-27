/**
 * @file interpreter.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef STICK_INTERPRETER_HPP
#define STICK_INTERPRETER_HPP

#include <interpreter/context.hpp>
#include <parser/parser.hpp>

namespace Stick {

class RuntimeError : public std::runtime_error {
 public:
  RuntimeError(const std::string& message) : std::runtime_error(message) {}
  static void Throw(const std::string& message) { throw RuntimeError(message); }
};

class Interpreter {
 public:
  Interpreter() = delete;
  Interpreter(const std::string&);

  void RunProgram();

 private:
  Parser parser;

  OpCall              currOp;
  std::stack<Context> callStack;

  void RunOp();
  void outputStack();

  void Pop();
  void Push();
  void Print();
  void Add();
  void Sub();
  void StackLen();

  void handleIfs();
  void IfOp();
  void ElseOp();
  void CloseOp();
  bool evalIf();

  void handleLoops();
  void whileOp();
  void loopOp();
};
}  // namespace Stick

#endif