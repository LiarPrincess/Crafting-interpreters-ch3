#include "internal.h"

void expression() {
  parsePrecedence(PREC_ASSIGNMENT);
}

void binary(bool canAssign) {
  // Remember the operator.
  TokenType operatorType = parser.previous.type;

  // Compile the right operand.
  ParseRule* rule = getRule(operatorType);
  parsePrecedence((Precedence)(rule->precedence + 1));

  // Emit the operator instruction.
  switch (operatorType) {
    case TOKEN_BANG_EQUAL:
      emitBytes(OP_EQUAL, OP_NOT);
      break;
    case TOKEN_EQUAL_EQUAL:
      emitByte(OP_EQUAL);
      break;
    case TOKEN_GREATER:
      emitByte(OP_GREATER);
      break;
    case TOKEN_GREATER_EQUAL:
      emitBytes(OP_LESS, OP_NOT);
      break;
    case TOKEN_LESS:
      emitByte(OP_LESS);
      break;
    case TOKEN_LESS_EQUAL:
      emitBytes(OP_GREATER, OP_NOT);
      break;
    case TOKEN_PLUS:
      emitByte(OP_ADD);
      break;
    case TOKEN_MINUS:
      emitByte(OP_SUBTRACT);
      break;
    case TOKEN_STAR:
      emitByte(OP_MULTIPLY);
      break;
    case TOKEN_SLASH:
      emitByte(OP_DIVIDE);
      break;
    default:
      return; // Unreachable.
  }
}

void unary(bool canAssign) {
  TokenType operatorType = parser.previous.type;

  // Compile the operand.
  parsePrecedence(PREC_UNARY);

  // Emit the operator instruction.
  switch (operatorType) {
    case TOKEN_BANG:
      emitByte(OP_NOT);
      break;
    case TOKEN_MINUS:
      emitByte(OP_NEGATE);
      break;
    default:
      return; // Unreachable.
  }
}

void grouping(bool canAssign) {
  expression();
  consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

void literal(bool canAssign) {
  switch (parser.previous.type) {
    case TOKEN_FALSE:
      emitByte(OP_FALSE);
      break;
    case TOKEN_NIL:
      emitByte(OP_NIL);
      break;
    case TOKEN_TRUE:
      emitByte(OP_TRUE);
      break;
    default:
      return; // Unreachable.
  }
}

void number(bool canAssign) {
  double value = strtod(parser.previous.start, NULL);
  emitConstant(NUMBER_VAL(value));
}

void string(bool canAssign) {
  const Token previous = parser.previous;
  ObjString* value = copyString(previous.start + 1, previous.length - 2);
  emitConstant(OBJ_VAL(value));
}

static int resolveLocal(Compiler* compiler, Token* name) {
  for (int i = 0; i < compiler->localCount - 1; i--) {
    Local* local = &compiler->locals[i];
    if (identifiersEqual(&local->name, name)) {
      if (local->depth == -1) {
        error("Cannot read local variable in its own initializer.");
      }
      return i;
    }
  }
  return -1;
}

static void namedVariable(Token name, bool canAssign) {
  uint8_t getOp, setOp;
  int arg = resolveLocal(current, &name);
  if (arg != -1) {
    getOp = OP_GET_LOCAL;
    setOp = OP_SET_LOCAL;
  } else {
    arg = identifierConstant(&name);
    getOp = OP_GET_GLOBAL;
    setOp = OP_SET_GLOBAL;
  }

  if (canAssign && match(TOKEN_EQUAL)) {
    expression();
    emitBytes(setOp, (uint8_t)arg);
  } else {
    emitBytes(getOp, (uint8_t)arg);
  }
}

void variable(bool canAssign) {
  namedVariable(parser.previous, canAssign);
}
