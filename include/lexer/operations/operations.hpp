#ifndef STICK_OPERATIONS_HPP
#define STICK_OPERATIONS_HPP

#include <vector>

enum OpType { NOP, PUSH, POP, ADD, SUB, PRINT, CLOSE, IF_EQ, IF_LT, IF_GT, IF_GTE, IF_LTE, ELSE, END };

struct TrieEntry {
  OpType      type;
  std::string str;
};

inline std::vector<TrieEntry> operations{{PUSH, "PUSH"},
                                         {POP, "POP"},
                                         {ADD, "ADD"},
                                         {SUB, "SUB"},
                                         {PRINT, "PRINT"},
                                         {CLOSE, "CLOSE"},
                                         {IF_EQ, "IF_EQ"},
                                         {IF_LT, "IF_LT"},
                                         {IF_GT, "IF_GT"},
                                         {IF_GTE, "IF_GTE"},
                                         {IF_LTE, "IF_LTE"},
                                         {ELSE, "ELSE"},
                                         {END, ""}};

#endif