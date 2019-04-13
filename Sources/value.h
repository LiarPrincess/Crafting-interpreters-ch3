#ifndef value_h
#define value_h

#include "common.h"

// Single remembered constant value.
typedef double Value;

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
