#include "internal.h"

Parser parser;
Compiler* current = NULL;
Chunk* compilingChunk;

static void initCompiler(Compiler* compiler) {
  compiler->localCount = 0;
  compiler->scopeDepth = 0;
  current = compiler;
}

static void endCompiler() {
  emitReturn();

#ifdef DEBUG_PRINT_CODE
  if (!parser.hadError) {
    disassembleChunk(currentChunk(), "code");
  }
#endif
}

bool compile(const char* source, Chunk* chunk) {
  initScanner(source);

  Compiler compiler;
  initCompiler(&compiler);

  compilingChunk = chunk;
  parser.hadError = false;
  parser.panicMode = false;

  advance();
  while (!match(TOKEN_EOF)) {
    declaration();
  }

  endCompiler();
  return !parser.hadError;
}
