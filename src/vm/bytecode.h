#ifndef bytecode_h
#define bytecode_h

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

#endif /* bytecode_h */
