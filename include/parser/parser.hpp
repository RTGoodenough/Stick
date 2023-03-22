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

  OpCall nextOperation();

  OpCall SkipIf();

 private:
  Lexer lexer;
  Token currToken;

  void getOp(OpCall&);
  void getValue(OpCall&);

  void funcDef(OpCall&);
  void push(OpCall&);
  void ifOp(OpCall&);

  inline bool isClose();

  inline OpCall SkipIfHelper(size_t);
};
}  // namespace Stick

#endif