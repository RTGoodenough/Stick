#ifndef STICK_OPERATIONS_HPP
#define STICK_OPERATIONS_HPP

#include <vector>

enum OpType { NOP, PUSH, POP, ADD, SUB, PRINT, FUNC, CLOSE, CALL, IF, ELSE, END };

struct TrieEntry {
  OpType      type;
  std::string str;
};

inline std::vector<TrieEntry> operations{{PUSH, "PUSH"},
                                         {POP, "POP"},
                                         {ADD, "ADD"},
                                         {SUB, "SUB"},
                                         {PRINT, "PRINT"},
                                         {FUNC, "FUNC"},
                                         {CALL, "CALL"},
                                         {CLOSE, "CLOSE"},
                                         {IF, "IF"},
                                         {ELSE, "ELSE"},
                                         {END, ""}};

#endif