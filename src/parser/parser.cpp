

#include <parser/parser.hpp>

inline bool
isEnd(const Token& token) {
  return (token.type == CHAR && token.value.number == EOF);
}

inline bool
isSemi(const Token& token) {
  return (token.type == CHAR && token.value.number == ';');
}

Stick::Parser::Parser(const std::string& filepath) : lexer(filepath) {}

OpCall
Stick::Parser::nextOperation() {
  OpCall ret;
  currToken = lexer.nextToken();

  if (isEnd(currToken))
    return {END, {}, false};

  getOp(ret);
  getValue(ret);

  return ret;
}

void
Stick::Parser::getOp(OpCall& op) {
  if (currToken.type != OP) {
    SyntaxError::Throw("Expected Operation " + lexer.getRowCol());
  }
  op.type = static_cast<OpType>(currToken.value.number);
}

void
Stick::Parser::getValue(OpCall& op) {
  switch (op.type) {
    case (PUSH):
      currToken = lexer.nextToken();
      op.value = currToken.value;
      op.referenceValue = (currToken.type == ID);
    default:
      break;
  }
}