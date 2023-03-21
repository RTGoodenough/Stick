

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
    case FUNC:
      funcDef();
      break;
    case IF:
      ifOp();
      break;
    default:
      RuntimeError("OP Type Not Accounted For: " + std::to_string(currOp.type));
      break;
  }
}

void
Stick::Interpreter::Push() {
  printf("Push\n");
  valStack.push(getOpValue());
}

void
Stick::Interpreter::Pop() {
  printf("Pop\n");
  if (valStack.empty())
    RuntimeError("Attempt Pop on Empty Stack");

  valStack.pop();
}

void
Stick::Interpreter::Add() {
  printf("Add\n");
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
  printf("Sub\n");
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
  printf("Print\n");
  if (valStack.size() == 0) {
    std::cout << "Stack Empty\n";
  } else {
    std::cout << std::to_string(valStack.top()) << '\n';
  }
}

void
Stick::Interpreter::funcDef() {
  printf("Function Def\n");
  // TODO
}

void
Stick::Interpreter::ifOp() {
  printf("If %li %li\n", valStack.top(), getOpValue());
  if (valStack.top() != getOpValue()) {
    currOp = parser.SkipIf();
  }

  // TODO fix not skipping else if the if is true
}

int64_t
Stick::Interpreter::getOpValue() {
  if (currOp.referenceValue) {
    // TODO
    RuntimeError::Throw("Reference Values Not Implemented");
  }

  return currOp.value.number;
}