#ifndef value_h
#define value_h

#include "common.h"

typedef double Value;

typedef struct {
  int count;
  int capacity;
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
