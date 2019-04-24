#include "internal.h"

/* scope */

static void beginScope() {
  current->scopeDepth++;
}

static void endScope() {
  current->scopeDepth--;

  while (current->localCount > 0 &&
         current->locals[current->localCount - 1].depth > current->scopeDepth) {
    emitByte(OP_POP);
    current->localCount--;
  }
}

/* statements */

static void printStatement() {
  expression();
  consume(TOKEN_SEMICOLON, "Expected ';' after value.");
  emitByte(OP_PRINT);
}

static void block() {
  while (!check(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF)) {
    declaration();
  }

  consume(TOKEN_RIGHT_BRACE, "Expected '}' after block.");
}

static void expressionStatement() {
  expression();
  emitByte(OP_POP);
  consume(TOKEN_SEMICOLON, "Expected ';' after value.");
}

void statement() {
  if (match(TOKEN_PRINT)) {
    printStatement();
  } else if (match(TOKEN_LEFT_BRACE)) {
    beginScope();
    block();
    endScope();
  } else {
    expressionStatement();
  }
}
