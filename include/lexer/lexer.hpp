#ifndef STICK_LEXER_HPP
#define STICK_LEXER_HPP

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

#include <lexer/operations/optrie.hpp>
#include <lexer/types/token.hpp>
#include <util/databuilder.hpp>

namespace Stick {

class LexerException : public std::runtime_error {
 public:
  LexerException(const std::string& message) : std::runtime_error(message) {}
  static void Throw(const std::string& message) { throw LexerException(message); }
};

class Lexer {
 public:
  Lexer() = default;
  ~Lexer() = default;
  Lexer(const std::string&);
  Lexer(Lexer&&) = delete;
  Lexer(Lexer&) = delete;
  Lexer& operator=(const Lexer&) = delete;
  Lexer& operator=(Lexer&&) = delete;

  void LoadOpTrie(const std::vector<TrieEntry>&);

  Token nextToken();
  void  seek(size_t);

  std::string getLineCol() const;

  size_t getPos();
  size_t getLine() const;
  size_t getCol() const;

 private:
  std::ifstream srcStream;

  size_t currPos;
  size_t currLine;
  size_t currCol;

  OpTrie optrie;

  OpType      parseOp(const char*);
  const char* parseString(char);
  long        parseNumber(char);

  char skipWhiteSpace(char);
  void skipComment();
  void putback(char);

  BoolOp parseBoolOp(char);
  BoolOp boolean(BoolOp);

  [[nodiscard]] inline char next();
};
}  // namespace Stick

#endif