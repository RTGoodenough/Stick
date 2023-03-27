/**
 * @file stick.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <interpreter/interpreter.hpp>

int
main(int argc, const char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: Stick *filepath*\n";
    exit(1);
  }

  Stick::Interpreter(argv[1]).RunProgram();
}