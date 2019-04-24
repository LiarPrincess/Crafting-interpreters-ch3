#ifndef compiler_h
#define compiler_h

#include "../chunk.h"

#define UINT8_COUNT (UINT8_MAX + 1)

bool compile(const char* source, Chunk* chunk);

#endif /* compiler_h */
