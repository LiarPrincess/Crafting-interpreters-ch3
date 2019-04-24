#ifndef chunk_h
#define chunk_h

#include "../common.h"
#include "bytecode.h"
#include "value.h"

typedef struct {
  // Number of currently held elements.
  int count;
  // Number of elements that can hold without resizing.
  int capacity;
  // Bytecode (or operand stored as index insice this->constants).
  uint8_t* code;
  // Line in the original source code.
  int* lines;
  // Array of remebered constant values.
  ValueArray constants;
} Chunk;

// Initialize new chunk (with no data).
void initChunk(Chunk* chunk);

// Destroy the chunk.
void freeChunk(Chunk* chunk);

// Add byte(code) to the end on the chunk.
void writeChunk(Chunk* chunk, uint8_t byte, int line);

// Add constant that can be used inside the chunk.
int addConstant(Chunk* chunk, Value value);

#endif /* chunk_h */
