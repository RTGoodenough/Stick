# Stick

**Still a WIP**

A Stick Interpreter

Stick is a minimalist stack based interpreted language.

### Compilation

The interpreter is compiled using CMake.

To compile use the command:
`cmake -B build .`
`cmake --build build`

### Running

To run the interpreter use the command:
`./Stick *path to source file*`


# Stick Language

Stick is very basic and more features, such as memory allocation and functions, are in the works.

### Operations

`PUSH *expression*` : Pushes the value of `*expression*` onto the stack

`POP` : Removes the top value from the stack

`ADD` : Adds the first two values of the stack, removing them, and pushes the result

`SUB` : Subtracts the first two values of the stack, removing them, and pushes the result

`COPY *expression*` : Copies the first `*expression*` values from the stack back onto the stack

`STKLEN` : Pushes the length of the stack

`IF *bool operator* *expression*` : Compares the value on the top of the stack with `*expression*`, running the subsequent block of code if true

`WHILE *bool operator* *expression*` : Loops, running a block of code until the boolean expression evaluates to false

### Loops

Stick only has a `WHILE` loop.

The code inside the while loop will execute until the boolean expression returns false.

**example:**
```
PUSH 5
WHILE > 0
	PRINT
	PUSH 1
	SUB
LOOP
POP

# outputs: 54321
```

### Ifs

If statements are written:
`IF *boolean operator* *expression*`

an `ELSE` statement can be used to execute code in the case that the boolean expression return false.

If's can be nested.

**example:**
```
PUSH 5

IF > 10
	PUSH 6
ELSE
	# reaches here
	IF == 5
		# reaches here
		PUSH 7
	ELSE
		PUSH 8
	CLOSE
CLOSE

ADD
PRINT

# outputs 12 (adds 5 and 7)
```

### Comments

Comments are created using `#`.

Comments are single line only.

**example:**
```
# This is a comment
this is not part of the comment
```

## Example Program:

### Fibonacci Sequence

This Stick program calculates the first 50 values of the Fibonacci sequence
(Command line parameters will be added in the future)

```
# fibonacci.stik

PUSH 1
PUSH 1

STKLEN
WHILE < 50
  POP
  
  COPY 2
  ADD
  
  STKLEN
LOOP
POP
```

