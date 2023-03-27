/**
 * @file lexer.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <lexer/lexer.hpp>

Stick::Lexer::Lexer(const std::string& sourceFile)
  : srcStream{sourceFile, std::fstream::in}, currPos(0), currLine(1), currCol(0) {
  if (!srcStream.is_open()) {
    Stick::LexerException::Throw("Unable To Open Source File");
  }
  LoadOpTrie(operations);
}

void
Stick::Lexer::seek(size_t pos) {
  srcStream.clear();
  srcStream.seekg(pos, std::ios::beg);
  currPos = pos;
}

void
Stick::Lexer::LoadOpTrie(const std::vector<TrieEntry>& entries) {
  for (const auto& entry : entries) {
    optrie.add(entry.str, entry.type);
  }
}

Token
Stick::Lexer::nextToken() {
  size_t pos = getPos();

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

    size_t nPos = getPos();
    if (nPos != pos && nPos > 0)
      pos = nPos - 1;

    switch (curr) {
      case '>':
      case '<':
      case '=':
        return {TokenType::BOOL, {.number = parseBoolOp(curr)}, pos};
      default:
        break;
    }

    if (isalpha(curr) || curr == '_') {
      const char* str = parseString(curr);
      OpType      op = parseOp(str);

      if (op == NOP) {
        // printf("ID: %s\n", str);
        return {TokenType::ID, {.string = str}, pos};
      } else {
        // printf("Operation: %s\n", str);
        delete[] str;
        return {TokenType::OP, {.number = op}, pos};
      }
    }
    if (isdigit(curr)) {
      long num = parseNumber(curr);
      // printf("Number: %li\n", num);
      return {TokenType::NUMBER, {.number = num}, pos};
    }

    // printf("Char: %c\n", curr);
    return {TokenType::CHAR, {.number = curr}, pos};
  }

  // printf("End of File\n");
  return {TokenType::CHAR, {.number = EOF}, 0};
}

const char*
Stick::Lexer::parseString(char start) {
  DataBuilder<char> builder;
  while (isalnum(start) || start == '_') {
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

size_t
Stick::Lexer::getPos() {
  return currPos;
}

inline char
Stick::Lexer::next() {
  ++currPos;
  char c = srcStream.get();
  if (c == '\n') {
    ++currLine;
    currCol = 0;
  }

  return c;
}

void
Stick::Lexer::putback(char c) {
  --currPos;
  srcStream.putback(c);
  if (c == '\n' && currLine > 0) {
    --currLine;
  } else {
    --currCol;
  }
}

BoolOp
Stick::Lexer::parseBoolOp(char c) {
  switch (c) {
    case ('<'):
      return boolean(BoolOp::LT);
    case ('>'):
      return boolean(BoolOp::GT);
    case ('='):
      return boolean(BoolOp::EQ);
  }
  return BoolOp::NONE;
}

BoolOp
Stick::Lexer::boolean(BoolOp type) {
  char c = next();
  if (c == '=') {
    ++type;
  } else {
    putback(c);
  }

  return type;
}