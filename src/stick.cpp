

#include <interpreter/interpreter.hpp>

int
main(int argc, const char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: Stick *filepath*\n";
    exit(1);
  }

  Stick::Interpreter(argv[1]).RunProgram();
}