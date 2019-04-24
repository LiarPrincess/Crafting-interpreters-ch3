#include "internal.h"

static void addLocal(Token name) {
  if (current->localCount == UINT8_COUNT) {
    error("Too many local variables in function.");
    return;
  }

  Local* local = &current->locals[current->localCount++];
  local->name = name;
  local->depth = -1;
}

static void declareVariable() {
  // Global variables are implicitly declared.
  if (current->scopeDepth == 0)
    return;

  Token* name = &parser.previous;
  for (int i = current->localCount - 1; i >= 0; i--) {
    Local* local = &current->locals[i];

    if (local->depth != -1 && local->depth < current->scopeDepth)
      break;

    if (identifiersEqual(name, &local->name))
      error("Variable with this name already declared in this scope.");
  }

  addLocal(*name);
}

static void markInitialized() {
  if (current->scopeDepth == 0)
    return;

  int index = current->localCount - 1;
  current->locals[index].depth = current->scopeDepth;
}

static void defineVariable(uint8_t global) {
  if (current->scopeDepth > 0) {
    markInitialized();
    return;
  }

  emitBytes(OP_DEFINE_GLOBAL, global);
}

static uint8_t parseVariable(const char* errorMessage) {
  consume(TOKEN_IDENTIFIER, errorMessage);

  declareVariable();
  if (current->scopeDepth > 0)
    return 0;

  return identifierConstant(&parser.previous);
}

static void varDeclaration() {
  uint8_t global = parseVariable("Expect variable name.");

  if (match(TOKEN_EQUAL)) {
    expression();
  } else {
    emitByte(OP_NIL);
  }
  consume(TOKEN_SEMICOLON, "Expect ';' after variable declaration.");

  defineVariable(global);
}

void declaration() {
  if (match(TOKEN_VAR)) {
    varDeclaration();
  } else {
    statement();
  }

  if (parser.panicMode) {
    synchronize();
  }
}
