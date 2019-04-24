#include "internal.h"

/* chunk */

Chunk* currentChunk() {
  return compilingChunk;
}

/* error */

static void errorAt(Token* token, const char* message) {
  if (parser.panicMode)
    return;

  parser.panicMode = true;
  fprintf(stderr, "[line %d] Error", token->line);

  if (token->type == TOKEN_EOF) {
    fprintf(stderr, " at end");
  } else if (token->type == TOKEN_ERROR) {
    // Nothing.
  } else {
    fprintf(stderr, " at '%.*s'", token->length, token->start);
  }

  fprintf(stderr, ": %s\n", message);
  parser.hadError = true;
}

void error(const char* message) {
  errorAt(&parser.previous, message);
}

void errorAtCurrent(const char* message) {
  errorAt(&parser.current, message);
}

void synchronize() {
  parser.panicMode = false;

  while (parser.current.type != TOKEN_EOF) {
    if (parser.previous.type == TOKEN_SEMICOLON)
      return;

    switch (parser.current.type) {
      case TOKEN_CLASS:
      case TOKEN_FUN:
      case TOKEN_VAR:
      case TOKEN_FOR:
      case TOKEN_IF:
      case TOKEN_WHILE:
      case TOKEN_PRINT:
      case TOKEN_RETURN:
        return;

      default:
        break;
    }

    advance();
  }
}

/* emit */

void emitByte(uint8_t byte) {
  Chunk* chunk = currentChunk();
  writeChunk(chunk, byte, parser.previous.line);
}

void emitBytes(uint8_t byte1, uint8_t byte2) {
  emitByte(byte1);
  emitByte(byte2);
}

void emitReturn() {
  emitByte(OP_RETURN);
}

static uint8_t makeConstant(Value value) {
  Chunk* chunk = currentChunk();
  int constant = addConstant(chunk, value);

  if (constant > UINT8_MAX) {
    error("Too many constants in one chunk.");
    return 0;
  }

  return (uint8_t)constant;
}

uint8_t identifierConstant(Token* name) {
  ObjString* identifier = copyString(name->start, name->length);
  return makeConstant(OBJ_VAL(identifier));
}

void emitConstant(Value value) {
  emitBytes(OP_CONSTANT, makeConstant(value));
}

/* variables */

bool identifiersEqual(Token* a, Token* b) {
  if (a->length != b->length)
    return false;

  return memcmp(a->start, b->start, a->length) == 0;
}
