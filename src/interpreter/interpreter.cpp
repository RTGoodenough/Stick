

#include <interpreter/interpreter.hpp>

Stick::Interpreter::Interpreter(const std::string& filepath) : parser(filepath) {}

void
Stick::Interpreter::RunProgram() {
  ifStack.push(TRUE);
  currOp = parser.nextOperation();
  while (currOp.type != END) {
    handleIfs();
    RunOp();
    currOp = parser.nextOperation();
  }
}

void
Stick::Interpreter::RunOp() {
  if (ifStack.top() == TRUE) {
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
        RuntimeError::Throw("OP Type Not Accounted For: " + std::to_string(currOp.type));
        break;
    }
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
    std::cout << "Empty Stack\n";
  } else {
    std::cout << std::to_string(valStack.top()) << '\n';
  }
}

void
Stick::Interpreter::If() {

  if (ifStack.top() == FALSE || ifStack.top() == SKIP) {
    ifStack.push(SKIP);
    return;
  }

  bool result;

  switch (currOp.type) {
    case IF_EQ:
      result = valStack.top() == currOp.value.number;
      break;
    case IF_LT:
      result = valStack.top() < currOp.value.number;
      break;
    case IF_GT:
      result = valStack.top() > currOp.value.number;
      break;
    case IF_GTE:
      result = valStack.top() >= currOp.value.number;
      break;
    case IF_LTE:
      result = valStack.top() <= currOp.value.number;
      break;
    default:
      RuntimeError::Throw("Unhandled If Type");
  }

  if (result) {
    ifStack.push(TRUE);
  } else {
    ifStack.push(FALSE);
  }
}

int64_t
Stick::Interpreter::getOpValue() {
  if (currOp.referenceValue) {
    // TODO
    RuntimeError::Throw("Reference Values Not Implemented");
  }

  return currOp.value.number;
}

void
Stick::Interpreter::Else() {
  auto val = ifStack.top();

  if (val == SKIP)
    return;

  if (val == TRUE) {
    ifStack.top() = FALSE;
  } else {
    ifStack.top() = TRUE;
  }
}

void
Stick::Interpreter::Close() {
  while (currOp.type == CLOSE) {
    if (ifStack.size() == 1)
      RuntimeError::Throw("Extra CLOSE");
    ifStack.pop();
    currOp = parser.nextOperation();
  }
}

void
Stick::Interpreter::handleIfs() {
  if (currOp.type == CLOSE)
    Close();

  switch (currOp.type) {
    case IF_EQ:
    case IF_LT:
    case IF_GT:
    case IF_GTE:
    case IF_LTE:
      If();
      currOp = parser.nextOperation();
      break;
    case ELSE:
      Else();
      currOp = parser.nextOperation();
      break;
  }
}