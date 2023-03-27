#ifndef STICK_OPERATIONS_HPP
#define STICK_OPERATIONS_HPP

#include <vector>

enum OpType { NOP, PUSH, POP, IF, ELSE, CLOSE, WHILE, LOOP, FUNC, CALL, END, PRINT, ADD, SUB, STKLEN };

enum BoolOp { NONE = 0, EQ, GT, LT, GTE, LTE };

inline void
operator++(BoolOp& op) {
  switch (op) {
    case BoolOp::GT:
      op = BoolOp::GTE;
    case BoolOp::LT:
      op = BoolOp::LTE;
  }
}

struct TrieEntry {
  OpType      type;
  std::string str;
};

inline std::vector<TrieEntry> operations{{PUSH, "PUSH"},
                                         {POP, "POP"},
                                         {CLOSE, "CLOSE"},
                                         {IF, "IF"},
                                         {WHILE, "WHILE"},
                                         {LOOP, "LOOP"},
                                         {FUNC, "FUNC"},
                                         {CALL, "CALL"},
                                         {ELSE, "ELSE"},
                                         {PRINT, "PRINT"},
                                         {ADD, "ADD"},
                                         {SUB, "SUB"},
                                         {STKLEN, "STKLEN"},
                                         {END, ""}};

#endif