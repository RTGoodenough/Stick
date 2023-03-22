

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
    SyntaxError::Throw("Expected Operation " + lexer.getLineCol() + " Found: " + currToken.toString());
  }
  op.type = static_cast<OpType>(currToken.value.number);
}

void
Stick::Parser::getValue(OpCall& op) {
  switch (op.type) {
    case (PUSH):
      push(op);
      break;
    case IF_EQ:
    case IF_LT:
    case IF_GT:
    case IF_GTE:
    case IF_LTE:
      push(op);
      break;
    default:
      break;
  }
}

void
Stick::Parser::push(OpCall& op) {
  currToken = lexer.nextToken();
  op.value = currToken.value;
  op.referenceValue = (currToken.type == ID);
}

void
Stick::Parser::ifOp(OpCall& op) {
  currToken = lexer.nextToken();
  op.value = currToken.value;
  op.referenceValue = (currToken.type == ID);
}