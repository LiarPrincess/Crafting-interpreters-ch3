#include <stdio.h>
#include <stdarg.h>

#include "vm.h"
#include "value.h"
#include "compiler.h"

#ifdef DEBUG_TRACE_EXECUTION
#include "debug.h"
#endif

VM vm;

static void resetStack() {
  vm.stackTop = vm.stack;
}

static InterpretResult run();

void initVM() {
  resetStack();
}

void freeVM() {

}

// stack

static Value peek(int distance) {
  return vm.stackTop[-1 - distance];
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

// errors

static void runtimeError(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fputs("\n", stderr);

  size_t instruction = vm.ip - vm.chunk->code;
  fprintf(stderr, "[line %d] in script\n", vm.chunk->lines[instruction]);

  resetStack();
}

// interpret

static InterpretResult run() {
  #define READ_BYTE() (*vm.ip++)
  #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
  #define BINARY_OP(valueType, op) \
    do { \
      if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
        runtimeError("Operands must be numbers."); \
        return INTERPRET_RUNTIME_ERROR; \
      } \
      \
      double b = AS_NUMBER(pop()); \
      double a = AS_NUMBER(pop()); \
      push(valueType(a op b)); \
    } while (false)

  while (true)
  {
    #ifdef DEBUG_TRACE_EXECUTION
      printf("          ");
      if (vm.stackTop == vm.stack) {
        printf("[]");
      }
      for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
        printf("[");
        printValue(*slot);
        printf("]");
      }
      printf("\n");
      disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
    #endif

    uint8_t instruction;
    switch (instruction = READ_BYTE())
    {
      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        push(constant);
        break;
      }

      case OP_NEGATE:
        if (!IS_NUMBER(peek(0))) {
          runtimeError("Operand must be a number.");
          return INTERPRET_RUNTIME_ERROR;
        }

        push(NUMBER_VAL(-AS_NUMBER(pop())));
        break;

      case OP_ADD:      BINARY_OP(NUMBER_VAL, +); break;
      case OP_SUBTRACT: BINARY_OP(NUMBER_VAL, -); break;
      case OP_MULTIPLY: BINARY_OP(NUMBER_VAL, *); break;
      case OP_DIVIDE:   BINARY_OP(NUMBER_VAL, /); break;

      case OP_RETURN:
        printf("          -> ");
        printValue(pop());
        printf("\n");
        return INTERPRET_OK;
      default:
        printf("Running unknown instruction %d\n", instruction);
    }
  }

  #undef BINARY_OP
  #undef READ_CONSTANT
  #undef READ_BYTE
}

InterpretResult interpret(const char* source) {
  Chunk chunk;
  initChunk(&chunk);

  if (!compile(source, &chunk)) {
    freeChunk(&chunk);
    return INTERPRET_COMPILE_ERROR;
  }

  printf("=== run ===");
  vm.chunk = &chunk;
  vm.ip = vm.chunk->code;

  InterpretResult result = run();

  freeChunk(&chunk);
  return result;
}
