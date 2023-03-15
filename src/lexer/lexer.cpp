
#include <lexer/lexer.hpp>

// TODO load up the optrie

Stick::Lexer::Lexer(const std::string& sourceFile) : srcStream{sourceFile, std::fstream::in} {
  if (!srcStream.is_open()) {
    Stick::LexerException::Throw("Unable To Open Source File");
  }
  srcStream >> std::skipws;
}

void
Stick::Lexer::reset() {}

Token
Stick::Lexer::nextToken() {
  const char curr = srcStream.get();
  while (curr != EOF) {
    switch (curr) {
      case '#':
        printf("Skipping Comment");
        skipComment();
        continue;
    }

    if (isalpha(curr) || curr == '_') {
      const char* str = parseString(curr);
      OpType      op = parseOp(str);

      if (op == NOP) {
        printf("%s", str);
        return {TokenType::ID, {.string = str}};
      } else {
        printf("Operation: %s", str);
        delete[] str;
        return {TokenType::OP, {.number = op}};
      }
    }
    if (isdigit(curr)) {
      long num = parseNumber(curr);
      printf("Number: %l", num);
      return {TokenType::NUMBER, {.number = num}};
    }

    printf("Char: %c", curr);
    return {TokenType::CHAR, {.number = curr}};
  }

  printf("End of File");
  return {TokenType::CHAR, {EOF}};
}

const char*
Stick::Lexer::parseString(char start) {
  DataBuilder<char> builder;
  while (isalnum(start)) {
    builder.add(start);
    start = srcStream.get();
  }
  builder.add('\0');
  return builder.get().data;
}

long
Stick::Lexer::parseNumber(char start) {
  DataBuilder<char> builder;
  while (isalnum(start)) {
    builder.add(start);
    start = srcStream.get();
  }
  long temp = std::stol(builder.get().data);
  builder.clean();
  return temp;
}

void
Stick::Lexer::skipComment() {
  char curr = srcStream.get();
  while (curr != '\n' && curr != EOF) {
    curr = srcStream.get();
  }
}