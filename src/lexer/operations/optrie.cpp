/**
 * @file optrie.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <lexer/operations/optrie.hpp>

namespace Stick {

OpTrie::OpTrie() : root(new TrieNode()) {}

void
OpTrie::add(const std::string& str, OpType type) {
  TrieNode* curr = root;
  for (char c : str) {
    TrieNode* temp = curr->next[c - 'A'];
    if (temp == nullptr) {
      temp = new TrieNode();
      curr->next[c - 'A'] = temp;
    }
    curr = temp;
  }

  curr->type = type;
}

OpType
OpTrie::traverse(const char* str) const {
  TrieNode* curr = root;
  while (true) {

    if (*str == '\0') {
      return curr->type;
    }

    TrieNode* next = curr->next[*str - 'A'];
    if (next == nullptr) {
      return NOP;
    }

    curr = next;
    ++str;
  }

  return NOP;
}
}  // namespace Stick