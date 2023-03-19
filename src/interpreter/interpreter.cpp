

#include <interpreter/interpreter.hpp>

Stick::Interpreter::Interpreter(const std::string& filepath) : parser(filepath) {}

void
Stick::Interpreter::RunProgram() {
  currOp = parser.nextOperation();
  while (currOp.type != END) {
    RunOp();
    currOp = parser.nextOperation();
  }
}

void
Stick::Interpreter::RunOp() {
  switch (currOp.type) {
    case PUSH:
      Push();
      break;
    case POP:
      Pop();
      break;
    case ADD:
      Add();
      break;
    case SUB:
      Sub();
      break;
    case PRINT:
      Print();
      break;
    default:
      break;
  }
}

void
Stick::Interpreter::Push() {
  if (!currOp.referenceValue) {
    valStack.push(currOp.value.number);
    return;
  }

  // TODO get value from id
}

void
Stick::Interpreter::Pop() {
  if (valStack.empty())
    RuntimeError("Attempt Pop on Empty Stack");

  valStack.pop();
}

void
Stick::Interpreter::Add() {
  if (valStack.size() < 2)
    RuntimeError("Call To Add With Less Than 2 Values");

  auto l = valStack.top();
  valStack.pop();
  auto r = valStack.top();
  valStack.pop();

  valStack.push(l + r);
}

void
Stick::Interpreter::Sub() {
  if (valStack.size() < 2)
    RuntimeError("Call To Sub With Less Than 2 Values");

  auto l = valStack.top();
  valStack.pop();
  auto r = valStack.top();
  valStack.pop();

  valStack.push(l - r);
}

void
Stick::Interpreter::Print() {
  if (valStack.size() == 0) {
    std::cout << "Stack Empty\n";
  } else {
    std::cout << std::to_string(valStack.top()) << '\n';
  }
}