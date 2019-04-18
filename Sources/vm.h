#ifndef vm_h
#define vm_h

#include "common.h"
#include "chunk.h"
#include "value.h"

#define MAX_STACK 256

typedef struct {

  // Currently executed chunk.
  Chunk* chunk;

  // Instruction pointer.
  uint8_t* ip;

  Value stack[MAX_STACK];
  Value* stackTop;

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

InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif /* vm_h */
