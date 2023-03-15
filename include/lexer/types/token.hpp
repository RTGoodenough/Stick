#ifndef STICK_TOKEN_HPP
#define STICK_TOKEN_HPP

#include <stdint.h>

enum TokenType { ID, STRING, NUMBER, CHAR, OP };

union TokenValue {
  int64_t     number;
  const char* string;
};

struct Token {
  TokenType  type;
  TokenValue value;
};

#endif