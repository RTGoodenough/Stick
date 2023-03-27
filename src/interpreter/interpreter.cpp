/**
 * @file interpreter.cpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

#include <interpreter/interpreter.hpp>

void
printOp(OpCall& op) {
  std::cout << "Operation: ";
  switch (op.type) {
    case NOP:
      std::cout << "OP ";
      break;
    case PUSH:
      std::cout << "PUSH " << std::to_string(op.expression.value.number);
      break;
    case POP:
      std::cout << "POP ";
      break;
    case CLOSE:
      std::cout << "CLOSE ";
      break;
    case ELSE:
      std::cout << "ELSE ";
      break;
    case LOOP:
      std::cout << "LOOP ";
      break;
    case END:
      std::cout << "END ";
      break;
  }

  std::cout << '\n';
}

Stick::Interpreter::Interpreter(const std::string& filepath) : parser(filepath) {
  callStack.push(Context{});
  callStack.top().run.push(TRUE);
}

void
Stick::Interpreter::RunProgram() {
  currOp = parser.nextOperation();
  while (currOp.type != END) {
    RunOp();
    currOp = parser.nextOperation();
  };

  outputStack();
}

void
Stick::Interpreter::RunOp() {
  handleLoops();
  handleIfs();
  if (callStack.top().run.top() == TRUE) {
    switch (currOp.type) {
      case PUSH:
        Push();
        break;
      case POP:
        Pop();
        break;
      case PRINT:
        Print();
        break;
      case SUB:
        Sub();
        break;
      case ADD:
        Add();
        break;
      case STKLEN:
        StackLen();
        break;
    }
  }
}

void
Stick::Interpreter::outputStack() {
  auto& stack = callStack.top().values;
  std::cout << "\nStack (" << std::to_string(stack.size()) << "): ";
  while (!stack.empty()) {
    std::cout << std::to_string(stack.top()) << ", ";
    stack.pop();
  }
  std::cout << '\n';
}

void
Stick::Interpreter::Pop() {
  if (callStack.top().values.size() < 1)
    RuntimeError::Throw("Attempt To Pop Empty Stack");

  callStack.top().values.pop();
}

void
Stick::Interpreter::Push() {
  callStack.top().values.push(currOp.expression.value.number);
}

void
Stick::Interpreter::IfOp() {
  if (callStack.top().run.top() == FALSE || callStack.top().run.top() == SKIP) {
    callStack.top().run.push(SKIP);
  }

  if (evalIf()) {
    callStack.top().run.push(TRUE);
  } else {
    callStack.top().run.push(FALSE);
  }
}

void
Stick::Interpreter::ElseOp() {
  auto& top = callStack.top().run.top();
  if (top == SKIP) {
    return;
  }

  if (top == TRUE) {
    top = FALSE;
  } else {
    top = TRUE;
  }
}

void
Stick::Interpreter::CloseOp() {
  if (callStack.top().run.size() < 2)
    RuntimeError::Throw("Extra CLOSE Statement");

  callStack.top().run.pop();
}

bool
Stick::Interpreter::evalIf() {
  switch (currOp.expression.boolean) {
    case BoolOp::EQ:
      return callStack.top().values.top() == currOp.expression.value.number;
      break;
    case BoolOp::GT:
      return callStack.top().values.top() > currOp.expression.value.number;
      break;
    case BoolOp::LT:
      return callStack.top().values.top() < currOp.expression.value.number;
      break;
    case BoolOp::GTE:
      return callStack.top().values.top() >= currOp.expression.value.number;
      break;
    case BoolOp::LTE:
      return callStack.top().values.top() <= currOp.expression.value.number;
      break;
  }
  return false;
}

void
Stick::Interpreter::handleIfs() {
  switch (currOp.type) {
    case IF:
      IfOp();
      break;
    case ELSE:
      ElseOp();
      break;
    case CLOSE:
      CloseOp();
      break;
  }
}

void
Stick::Interpreter::handleLoops() {
  switch (currOp.type) {
    case WHILE:
      whileOp();
      break;
    case LOOP:
      loopOp();
      break;
  }
}
void
Stick::Interpreter::whileOp() {
  if (evalIf()) {
    callStack.top().run.push(TRUE);
    callStack.top().loops.push(currOp.position);
  } else {
    callStack.top().run.push(FALSE);
    callStack.top().loops.push(currOp.position);
  }
}

void
Stick::Interpreter::loopOp() {
  if (callStack.top().loops.size() < 1)
    RuntimeError::Throw("Extra LOOP Statement");

  if (callStack.top().run.top() == TRUE) {
    auto top = callStack.top().loops.top();
    callStack.top().loops.pop();
    callStack.top().run.pop();
    parser.seek(top);
  } else {
    callStack.top().loops.pop();
    callStack.top().run.pop();
  }
}

void
Stick::Interpreter::Print() {
  if (callStack.top().values.size() > 0) {
    std::cout << std::to_string(callStack.top().values.top());
  } else {
    std::cout << "Empty Stack\n";
  }
}

void
Stick::Interpreter::Add() {
  auto& top = callStack.top().values;
  if (top.size() < 2)
    RuntimeError::Throw("Add Called With Less Than 2 Values");

  auto l = top.top();
  top.pop();
  auto r = top.top();
  top.pop();

  top.push(r);
  top.push(l);
  top.push(l + r);
}

void
Stick::Interpreter::Sub() {
  auto& top = callStack.top().values;
  if (top.size() < 2)
    RuntimeError::Throw("Add Called With Less Than 2 Values");

  auto l = top.top();
  top.pop();
  auto r = top.top();
  top.pop();

  top.push(r);
  top.push(l);
  top.push(r - l);
}

void
Stick::Interpreter::StackLen() {
  auto& top = callStack.top().values;
  top.push(top.size());
}