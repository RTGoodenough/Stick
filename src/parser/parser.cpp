

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
  if (isElse() || isClose()) {
    printf("Else, next Op\n");
    return nextOperation();
  }

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

/*
need to fix, will stop at the first else
if
if
else <- will stop here
else <- should stop here
close
close

*/

OpCall
Stick::Parser::SkipIf() {
  currToken = lexer.nextToken();
  size_t ifCnt = 1;
  while (ifCnt > 0) {
    if (currToken.type == OP && currToken.value.number == IF) {
      ++ifCnt;
    } else if (isElse() || isClose()) {
      --ifCnt;
    }
    currToken = lexer.nextToken();
  }
  return nextOperation();
}

inline bool
Stick::Parser::isElse() {
  return (currToken.type == OP && currToken.value.number == ELSE);
}

inline bool
Stick::Parser::isClose() {
  return (currToken.type == OP && currToken.value.number == CLOSE);
}
