

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
    case CLOSE:
      break;
    default:
      RuntimeError::Throw("OP Type Not Accounted For: " + std::to_string(currOp.type));
      break;
  }
}

void
Stick::Interpreter::Push() {
  int64_t val = getOpValue();
  valStack.push(val);
}

void
Stick::Interpreter::Pop() {
  if (valStack.empty())
    RuntimeError::Throw("Attempt Pop on Empty Stack");

  valStack.pop();
}

void
Stick::Interpreter::Add() {
  if (valStack.size() < 2)
    RuntimeError::Throw("Call To Add With Less Than 2 Values");

  auto l = valStack.top();
  valStack.pop();
  auto r = valStack.top();
  valStack.pop();

  valStack.push(l + r);
}

void
Stick::Interpreter::Sub() {
  if (valStack.size() < 2)
    RuntimeError::Throw("Call To Sub With Less Than 2 Values");

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

void
Stick::Interpreter::funcDef() {
  // TODO
}

void
Stick::Interpreter::ifOp() {
  if (valStack.top() == getOpValue()) {
    currOp = parser.nextOperation();
  } else {
    currOp = parser.SkipIf();
  }

  RunOp();
}

int64_t
Stick::Interpreter::getOpValue() {
  if (currOp.referenceValue) {
    // TODO
    RuntimeError::Throw("Reference Values Not Implemented");
  }

  return currOp.value.number;
}
