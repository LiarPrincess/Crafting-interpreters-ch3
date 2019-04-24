#ifndef chunk_h
#define chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  // literals
  OP_CONSTANT,
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  // vm (stack)
  OP_POP,
  OP_GET_LOCAL,
  OP_SET_LOCAL,
  OP_DEFINE_GLOBAL,
  OP_GET_GLOBAL,
  OP_SET_GLOBAL,
  // unary
  OP_NOT,
  OP_NEGATE,
  OP_PRINT,
  // binary
  OP_EQUAL,
  OP_GREATER,
  OP_LESS,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  // return
  OP_RETURN
} OpCode;

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
