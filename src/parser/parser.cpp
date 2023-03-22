

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
    case (FUNC):
      funcDef(op);
      break;
    case (IF):
      ifOp(op);
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
Stick::Parser::funcDef(OpCall& op) {
  currToken = lexer.nextToken();

  if (currToken.type != ID) {
    SyntaxError::Throw("Expected Function Name " + lexer.getLineCol());
  }

  op.value = currToken.value;
  op.referenceValue = true;
}

void
Stick::Parser::ifOp(OpCall& op) {
  currToken = lexer.nextToken();
  op.value = currToken.value;
  op.referenceValue = (currToken.type == ID);
}

OpCall
Stick::Parser::SkipIf() {
  currToken = lexer.nextToken();
  while (!isClose()) {
    if (isEnd(currToken))
      SyntaxError::Throw("Expected CLOSE Found End of File");

    currToken = lexer.nextToken();
  }

  return nextOperation();
}

inline bool
Stick::Parser::isClose() {
  return (currToken.type == OP && currToken.value.number == CLOSE);
}