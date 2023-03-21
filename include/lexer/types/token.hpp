#ifndef STICK_TOKEN_HPP
#define STICK_TOKEN_HPP

#include <stdint.h>
#include <unordered_map>

enum TokenType { ID, STRING, NUMBER, CHAR, OP };

union TokenValue {
  int64_t     number;
  const char* string;
};

inline std::unordered_map<TokenType, std::string> TypeStrs{{ID, "Identifier"},
                                                           {STRING, "String"},
                                                           {NUMBER, "Number"},
                                                           {CHAR, "Character"},
                                                           {OP, "Operation"}};

struct Token {
  TokenType   type = OP;
  TokenValue  value = {.number = 0};
  std::string toString() const { return TypeStrs.at(type) + ", " + std::to_string(value.number); }
};

#endif