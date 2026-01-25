# Expression Parser
## Why Parsing Is Foundational

Parsing is the boundary between raw text and structured meaning.
Every compiler, interpreter, query engine, configuration system, and protocol stack begins here.
If parsing is wrong, nothing built on top of it can be correct.

This project exists to stay close to that boundary.

---

## Executive Summary

The project emphasizes:
- Parsing as a first-class systems concern
- Explicit AST construction
- Deterministic memory ownership
- Clear error models
- Code written to be read, not just executed

This codebase is intentionally over-commented.
That choice is deliberate.

---

## Motivation

Modern software stacks hide parsing and execution behind layers of abstraction.
While productive, this distance weakens intuition about:

- How syntax becomes structure
- Where undefined behavior originates
- How memory lifetimes affect correctness
- Why simple bugs turn systemic

This project removes those layers on purpose.

---

## Design Principles

### 1. Parsing Is Not a Detail
Parsing defines what can be expressed.
Evaluation merely executes those decisions.

### 2. Structure Before Execution
All input is converted into an AST before evaluation.
This enforces separation of concerns and simplifies reasoning.

### 3. Explicit Ownership
All allocations have clear owners.
No hidden lifetimes.
No “it probably survives long enough.”

### 4. Clarity Over Cleverness
Readable code scales better than clever code.
If logic is subtle, it is documented.

### 5. Code as a Teaching Tool
I learn fastest by explaining.
Others learn by reading.
Future maintainers benefit from both.

---

## Architecture

Source Text
↓
Lexer (Token Stream)
↓
Parser (AST)
↓
Evaluator


Each stage is isolated and deterministic.

---

## Project Structure



src/
├── lexer.c # Converts raw text into tokens
├── parser.c # Builds AST using recursive descent
├── ast.h # AST node definitions
├── eval.c # Evaluates AST nodes
└── main.c # Entry point and REPL


---

## Grammar (Simplified)



stmt → IDENT '=' expr | expr
expr → term ((+ | -) term)*
term → factor ((* | /) factor)*
factor → INT | IDENT


Operator precedence is encoded structurally, not procedurally.

---

## Build & Run

# linux/ #MacOs

```bash
make
./expression-parser
```

# WINDOWS
```bash
make
expression-parser.exe
```

Warnings are treated as errors by design.

Example
> x = 3 + 4
7
> x * 2
14

# Commenting Philosophy

This codebase is intentionally heavily commented.

I learn by teaching—first to myself, then to others.
Comments capture reasoning, invariants, and tradeoffs rather than restating syntax.
Readable systems code outlives clever systems code.



# Limitations

Single-threaded by design

No optimization passes

Focused on correctness and clarity, not performance

These are conscious tradeoffs.

Future Work

Control flow (if / while)

Function calls and stack frames

Bytecode compilation

Optimizer passes

Explicit memory deallocation and leak testing



# Why This Matters

Understanding parsing and execution is foundational to:

Compilers and interpreters

Query engines

Configuration systems

Network protocols

Security tooling

Abstraction should be built on understanding, It should not replace it
