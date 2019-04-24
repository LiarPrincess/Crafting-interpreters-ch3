#ifndef debug_h
#define debug_h

#include "chunk.h"
#include "common.h"

// Print the content of the chunk.
void disassembleChunk(Chunk* chunk, const char* name);

// Print single byte(code).
int disassembleInstruction(Chunk* chunk, int offset);

#endif /* debug_h */
