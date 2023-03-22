#ifndef STICK_INTERPRETER_HPP
#define STICK_INTERPRETER_HPP

#include <stack>

#include <parser/parser.hpp>

namespace Stick {

enum IfVal {
  TRUE,
  FALSE,
  SKIP,
};

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
  OpCall currOp;

  std::stack<int64_t> valStack;
  std::stack<IfVal>   ifStack;

  void RunOp();

  void Push();
  void Pop();
  void Add();
  void Sub();
  void Print();
  void If();
  void Else();
  void Close();

  void handleIfs();

  int64_t getOpValue();
};
}  // namespace Stick

#endif