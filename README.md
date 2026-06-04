# Cooke Lexical & Syntax Analyzer

A hand-written **lexical analyzer** and **recursive-descent syntax parser** for the Cooke programming language, written in C++. Built for CS 3361 at Texas Tech University.

![C++](https://img.shields.io/badge/C++-00599C?logo=cplusplus&logoColor=white)
![Make](https://img.shields.io/badge/build-make-green)

## Overview

The project is two command-line programs that make up the front end of a compiler for Cooke:

- **`cooke_analyzer`** - the lexical analyzer. Scans a Cooke source file and prints each lexeme alongside its token class.
- **`cooke_parser`** - the syntax parser. Reuses the scanning logic and a recursive-descent strategy to verify that a program
   conforms to the grammar, reporting the first syntax error if one exists.

- Source files use the `.dc` extension, named after Daniel Cooke, a Texas Tech University professor who designed SequenceL.

## The Cooke Language

### Grammar (BNF)

```
P ::= S
S ::= V := E | O | read(V) | print(E) | if C: begin S end | if C: begin S else: S end | S ; S
C ::= E < E | E > E | E = E | E <> E | E <= E | E >= E
E ::= T | E + T | E - T
T ::= F | T * F | T / F | T ** F
F ::= (E) | N | V
O ::= ++V | --V
V ::= a | b | ... | y | z | aV | bV | ... | yV | zV (identifiers)
N ::= 0 | 1 | ... | 8 | 9 | 0N | 1N | ... | 8N | 9N (integer literals)
```

### Tokens

| Lexeme | Token | Lexeme | Token | Lexeme | Token |
|--------|-------|--------|-------|--------|-------|
| `:=` | ASSIGN_OP | `+` | ADD_OP | `read` | KEY_READ |
| `<` | LESSER_OP | `-` | SUB_OP | `print` | KEY_PRINT |
| `>` | GREATER_OP | `*` | MULT_OP | `if` | KEY_IF |
| `=` | EQUAL_OP | `/` | DIV_OP | `else` | KEY_ELSE |
| `<>` | NEQUAL_OP | `**` | POW_OP | `begin` | KEY_BEGIN |
| `<=` | LEQUAL_OP | `++` | INC_OP | `end` | KEY_END |
| `>=` | GEQUAL_OP | `--` | DEC_OP | `V` | IDENT |
| `(` | LEFT_PAREN | `;` | SEMICOLON | `N` | INT_LIT |
| `)` | RIGHT_PAREN | `:` | COLON |  |  |

Any lexeme that matches no known token is reported as **`UNKNOWN`**.

## Building

You'll need a C++ compiler (`g++` or `clang++`) and `make` - no external dependencies. Clone the repo, then from its root:

```bash
make        # builds both executables: cooke_analyzer and cooke_parser
make clean  # removes the compiled binaries
```

That's all there is to it. On macOS `g++` resolves to Apple Clang and on Linux it's GNU GCC; either builds the project as-is.

## How it works

The **lexer** reads the source one character at a time, skips whitespace, and groups the remaining characters into lexemes - identifiers
and integer literals by the grammar's `V` and `N` rules, plus the fixed operators, punctuation, and keywords. Each lexeme is matched to its
token (or `UNKNOWN` if none fits), and the lexer tracks the current line number for error reporting.

The **parser** sits on top of the lexer and is recursive descent: one function per nonterminal (`statement`, `condition`, `expression`, `term`, `factor`, ...),
starting from the root `P ::= S`. It pulls tokens from the lexer one at a time, and each function either consumes its expected tokens or reports the first syntax
error - with the line number, lexeme, and token - then stops.

## Author

**Michael Leon** - Computer Science, Texas Tech University

CS 3361, Spring 2025
