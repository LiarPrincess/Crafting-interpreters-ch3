#include <stdio.h>

#include "value.h"
#include "debug.h"
#include "vm.h"

VM vm;

void initVM() {

}

void freeVM() {

}

static InterpretResult run();

InterpretResult interpret(Chunk* chunk) {
  vm.chunk = chunk;
  vm.ip = chunk->code;
  return run();
}

static InterpretResult run() {
  #define READ_BYTE() (*vm.ip++)
  #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for(;;)
  {
    #ifdef DEBUG_TRACE_EXECUTION
      disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
    #endif

    uint8_t instruction;
    switch (instruction = READ_BYTE())
    {
      case OP_CONSTANT: {
        Value cons = READ_CONSTANT();
        printValue(cons);
        printf("\n");
        break;
      }
      case OP_RETURN:
        return INTERPRET_OK;
      default:
        printf("Running unknown instruction %d\n", instruction);
    }
  }

  #undef READ_CONSTANT
  #undef READ_BYTE
}
