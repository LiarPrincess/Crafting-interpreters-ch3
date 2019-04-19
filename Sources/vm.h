#ifndef vm_h
#define vm_h

#include "common.h"
#include "chunk.h"
#include "value.h"
#include "table.h"

#define MAX_STACK 256

typedef struct {
  // Currently executed chunk
  Chunk* chunk;
  // Instruction pointer
  uint8_t* ip;
  // Stack
  Value stack[MAX_STACK];
  // Last entry on stack
  Value* stackTop;
  // Interned strings
  Table strings;
  // List of all heap objects
  Obj* objects;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();

void push(Value value);
Value pop();

InterpretResult interpret(const char* source);

#endif /* vm_h */
