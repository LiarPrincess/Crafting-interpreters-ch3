#ifndef compiler_internal_h
#define compiler_internal_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common.h"
#include "../object.h"
#include "../scanner.h"
#include "compiler.h"

#ifdef DEBUG_PRINT_CODE
#include "../debug.h"
#endif

typedef struct {
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
} Parser;

typedef enum {
  PREC_NONE,
  PREC_ASSIGNMENT, // =
  PREC_OR, // or
  PREC_AND, // and
  PREC_EQUALITY, // == !=
  PREC_COMPARISON, // < > <= >=
  PREC_TERM, // + -
  PREC_FACTOR, // * /
  PREC_UNARY, // ! -
  PREC_CALL, // . () []
  PREC_PRIMARY
} Precedence;

typedef void (*ParseFn)(bool canAssign);

typedef struct {
  ParseFn prefix;
  ParseFn infix;
  Precedence precedence;
} ParseRule;

typedef struct {
  Token name;
  int depth;
} Local;

typedef struct {
  Local locals[UINT8_COUNT];
  // How many locals are in scope
  int localCount;
  // Number of blocks surrounding the current bit of code we’re compiling
  int scopeDepth;
} Compiler;

extern Parser parser;
extern Compiler* current;
extern Chunk* compilingChunk;

// parser
void consume(TokenType type, const char* message);
bool check(TokenType type);
void advance();
bool match(TokenType type);
void synchronize();

ParseRule* getRule(TokenType type);
void parsePrecedence(Precedence precedence);

// common
Chunk* currentChunk();

void errorAtCurrent(const char* message);
void error(const char* message);

void emitByte(uint8_t byte);
void emitBytes(uint8_t byte1, uint8_t byte2);
void emitReturn();
void emitConstant(Value value);
uint8_t identifierConstant(Token* name);

bool identifiersEqual(Token* a, Token* b);

// expressions
void expression();
void binary(bool canAssign);
void unary(bool canAssign);
void grouping(bool canAssign);
void literal(bool canAssign);
void number(bool canAssign);
void string(bool canAssign);
void variable(bool canAssign);

// statements
void statement();

// declarations
void declaration();

#endif /* compiler_internal_h */
