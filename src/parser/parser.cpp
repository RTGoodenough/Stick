

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
  // std::cout << "Start OP:\n";
  moveLookahead();

  if (isEnd(lookahead))
    return {END, {}, 0};

  match(OP);

  OpCall currOp;
  currOp.position = lookahead.position;
  currOp.type = static_cast<OpType>(lookahead.value.number);

  switch (currOp.type) {
    case IF:
    case WHILE:
      // std::cout << "IF/WHILE\n";
      moveLookahead();
      currOp.expression.boolean = static_cast<BoolOp>(lookahead.value.number);
    case PUSH:
      // std::cout << "PUSH\n";
      moveLookahead();
      currOp.expression.value = evaluateExpression();
    default:
      break;
  }

  return currOp;
}

void
Stick::Parser::seek(size_t pos) {
  lexer.seek(pos);
}

void
Stick::Parser::match(TokenType type) {
  if (lookahead.type != type) {
    SyntaxError::Throw("Expected Type: " + TypeStrs.at(type) + ", Found Token: " + lookahead.toString() +
                       "\nAt: " + lexer.getLineCol());
  }
}

void
Stick::Parser::moveLookahead() {
  lookahead = lexer.nextToken();
  // std::cout << "CurrToken: " << lookahead.toString() << "\n";
}

OpValue
Stick::Parser::evaluateExpression() {
  Expression ret;

  switch (lookahead.type) {
    case ID:
      return evaluateReference();
    case NUMBER:
      return {.number = evaluateMath()};
    default:
      SyntaxError::Throw("Evaluate Expression: Expected Type: " + TypeStrs.at(NUMBER) +
                         ", Found Token: " + lookahead.toString() + "\nAt: " + lexer.getLineCol());
  }

  return {.number = 0};
}

OpValue
Stick::Parser::evaluateReference() {
  // TODO check if should be value or string
  return {.string = lookahead.value.string};
}

int64_t
Stick::Parser::evaluateMath() {
  // TODO allow for arithmetic
  return lookahead.value.number;
}