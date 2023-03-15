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
  void   add(const std::string&, OpType);
  OpType traverse(const char*) const;

 private:
  TrieNode* root;
};
}  // namespace Stick

#endif  // STICK_OPTRIE_HPP