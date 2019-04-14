#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "vm.h"
#include "chunk.h"
#include "debug.h"

static void repl();
static void runFile(const char* path);
static char* readFile(const char* path);
static void waitForInput();

int main(int argc, const char * argv[]) {
  initVM();

  switch (argc)
  {
    case 1:
      repl();
      break;
    case 2:
      runFile(argv[1]);
      break;
    default:
      fprintf(stderr, "Usage: Lox [path]\n");
      exit(64);
  }

  freeVM();

  waitForInput();
  return 0;
}

static void repl() {
  char line[1024];
  while (true) {
    printf("> ");

    if (!fgets(line, 1024, stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

static void runFile(const char* path) {
  char* source = readFile(path);
  InterpretResult result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR) exit(65);
  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

static char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*) malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }

  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }

  buffer[bytesRead] = '\0';

  return buffer;
}

static void waitForInput() {
  char line[1024];
  printf("Press ENTER to exit...");
  fgets(line, 1024, stdin);
}

// Chunk chunk;
// initChunk(&chunk);

// int constant = addConstant(&chunk, 1.2);
// writeChunk(&chunk, OP_CONSTANT, 123);
// writeChunk(&chunk, constant, 123);

// constant = addConstant(&chunk, 3.4);
// writeChunk(&chunk, OP_CONSTANT, 123);
// writeChunk(&chunk, constant, 123);

// writeChunk(&chunk, OP_ADD, 123);

// constant = addConstant(&chunk, 5.6);
// writeChunk(&chunk, OP_CONSTANT, 123);
// writeChunk(&chunk, constant, 123);

// writeChunk(&chunk, OP_DIVIDE, 123);
// writeChunk(&chunk, OP_NEGATE, 123);

// writeChunk(&chunk, OP_RETURN, 123);

// printf("=== Disassembling ===\n");
// disassembleChunk(&chunk, "test chunk");
// printf("\n");

// printf("=== Interpreting ===\n");
// interpret(&chunk);
// printf("\n");

// freeChunk(&chunk);
