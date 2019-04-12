// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
// If a copy of the MPL was not distributed with this file,
// You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef chunk_h
#define chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_RETURN
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  ValueArray constants;
} Chunk;

// Initialize new chunk (with no data).
void initChunk(Chunk* chunk);

// Destroy the chunk.
void freeChunk(Chunk* chunk);

// Add byte(code) to the end on the chunk.
void writeChunk(Chunk* chunk, uint8_t byte);

// Add constant that can be used inside the chunk.
int addConstant(Chunk* chunk, Value value);

#endif /* chunk_h */
