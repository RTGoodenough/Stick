
#include <lexer/lexer.hpp>

Stick::Lexer::Lexer(const std::string& sourceFile) : srcStream{sourceFile, std::fstream::in}, currLine(1), currCol(0) {
  if (!srcStream.is_open()) {
    Stick::LexerException::Throw("Unable To Open Source File");
  }
  LoadOpTrie(operations);
}

void
Stick::Lexer::reset() {}

void
Stick::Lexer::LoadOpTrie(const std::vector<TrieEntry>& entries) {
  for (const auto& entry : entries) {
    optrie.add(entry.str, entry.type);
  }
}

Token
Stick::Lexer::nextToken() {
  char curr = next();
  curr = skipWhiteSpace(curr);
  while (curr != EOF) {
    switch (curr) {
      case '#':
        // printf("Skipping Comment\n");
        skipComment();
        curr = next();
        continue;
    }
    curr = skipWhiteSpace(curr);

    if (isalpha(curr) || curr == '_') {
      const char* str = parseString(curr);
      OpType      op = parseOp(str);

      if (op == NOP) {
        // printf("ID: %s\n", str);
        return {TokenType::ID, {.string = str}};
      } else {
        // printf("Operation: %s\n", str);
        delete[] str;
        return {TokenType::OP, {.number = op}};
      }
    }
    if (isdigit(curr)) {
      long num = parseNumber(curr);
      // printf("Number: %li\n", num);
      return {TokenType::NUMBER, {.number = num}};
    }

    // printf("Char: %c\n", curr);
    return {TokenType::CHAR, {.number = curr}};
  }

  // printf("End of File\n");
  return {TokenType::CHAR, {EOF}};
}

const char*
Stick::Lexer::parseString(char start) {
  DataBuilder<char> builder;
  while (isalnum(start)) {
    builder.add(start);
    start = next();
  }
  builder.add('\0');
  return builder.get().data;
}

long
Stick::Lexer::parseNumber(char start) {
  DataBuilder<char> builder;
  while (isalnum(start)) {
    builder.add(start);
    start = next();
  }
  putback(start);
  long temp = std::stol(builder.get().data);
  builder.clean();
  return temp;
}

void
Stick::Lexer::skipComment() {
  char curr = next();
  while (curr != '\n' && curr != EOF) {
    curr = next();
  }
}

char
Stick::Lexer::skipWhiteSpace(char curr) {
  while (isspace(curr)) {
    curr = next();
  }

  return curr;
}

OpType
Stick::Lexer::parseOp(const char* str) {
  OpType op = optrie.traverse(str);

  return op;
}

std::string
Stick::Lexer::getLineCol() const {
  return "Line: " + std::to_string(currLine) + " Col: " + std::to_string(currCol);
}

inline char
Stick::Lexer::next() {
  char c = srcStream.get();
  if (c == '\n') {
    ++currLine;
    currCol = 0;
  }

  return c;
}

void
Stick::Lexer::putback(char c) {
  srcStream.putback(c);
  if (c == '\n' && currLine > 0) {
    --currLine;
  } else {
    --currCol;
  }
}