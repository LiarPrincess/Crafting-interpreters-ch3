#ifndef value_h
#define value_h

#include "common.h"

// Value tag
typedef enum {
  VAL_BOOL,
  VAL_NIL,
  VAL_NUMBER,
} ValueType;

// Single remembered constant value.
typedef struct {
  ValueType type;
  union {
    bool boolean;
    double number;
  } as;
} Value;

// Check value type
#define IS_BOOL(value)    ((value).type == VAL_BOOL)
#define IS_NIL(value)     ((value).type == VAL_NIL)
#define IS_NUMBER(value)  ((value).type == VAL_NUMBER)

// Unpack values
#define AS_BOOL(value)    ((value).as.boolean)
#define AS_NUMBER(value)  ((value).as.number)

// Pack values
#define BOOL_VAL(value)   ((Value){ VAL_BOOL, { .boolean = value } })
#define NIL_VAL           ((Value){ VAL_NIL, { .number = 0 } })
#define NUMBER_VAL(value) ((Value){ VAL_NUMBER, { .number = value } })

typedef struct {
  // Number of currently held elements.
  int count;
  // Number of elements that can hold without resizing.
  int capacity;
  // Data.
  Value* values;
} ValueArray;

// Initialize new value array.
void initValueArray(ValueArray* array);

// Destroy value array.
void freeValueArray(ValueArray* array);

// Add new value to array.
void writeValueArray(ValueArray* array, Value byte);

/// Print value to stdout.
void printValue(Value value);

#endif /* value_h */
