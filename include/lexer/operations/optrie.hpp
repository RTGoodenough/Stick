/**
 * @file optrie.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef STICK_OPTRIE_HPP
#define STICK_OPTRIE_HPP

#include <array>
#include <string>

#include <lexer/operations/operations.hpp>

namespace Stick {

struct TrieNode {
  OpType                    type = NOP;
  std::array<TrieNode*, 26> next;
};

class OpTrie {
 public:
  OpTrie();

  void   add(const std::string&, OpType);
  OpType traverse(const char*) const;

 private:
  TrieNode* root;
};
}  // namespace Stick

#endif  // STICK_OPTRIE_HPP