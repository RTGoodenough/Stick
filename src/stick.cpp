

#include <lexer/lexer.hpp>

int
main(int argc, const char** argv) {
  Stick::Lexer lexer("test.stk");
  std::cout << "Loading OpTrie\n";
  lexer.LoadOpTrie(operations);
  std::cout << "Loaded OpTrie\n";

  Token curr;

  while (curr.type != CHAR && curr.value.number != EOF) {
    curr = lexer.nextToken();
  }
  std::cout << "Finished\n";
}