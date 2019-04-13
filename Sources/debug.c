#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int constantInstruction(const char* name, Chunk* chunk, int offset);
int simpleInstruction(const char* name, int offset);

int disassembleInstruction(Chunk* chunk, int offset) {
  printf("%04d ", offset);

  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    printf("   | ");
  } else {
    printf("%4d ", chunk->lines[offset]);
  }

  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    default:
      printf("Unknown instruction %d\n", instruction);
      return offset + 1;
  }

  return 0;
}

int constantInstruction(const char* name, Chunk* chunk, int offset) {
  uint8_t valueIndex = chunk->code[offset];
  printf("%s %d (value: ", name, valueIndex);
  printValue(chunk->constants.values[valueIndex]);
  printf(")\n");
  return offset + 2;
}

int simpleInstruction(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}
