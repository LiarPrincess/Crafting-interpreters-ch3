#ifndef value_h
#define value_h

#include "common.h"

// Value tag
typedef enum {
  VAL_BOOL,
  VAL_NIL,
  VAL_NUMBER,
  VAL_OBJ
} ValueType;

typedef struct sObj Obj;
typedef struct sObjString ObjString;

// Single remembered constant value.
typedef struct {
  ValueType type;
  union {
    bool boolean;
    double number;
    Obj* obj;
  } as;
} Value;

// Check value type
#define IS_BOOL(value)    ((value).type == VAL_BOOL)
#define IS_NIL(value)     ((value).type == VAL_NIL)
#define IS_NUMBER(value)  ((value).type == VAL_NUMBER)
#define IS_OBJ(value)     ((value).type == VAL_OBJ)

// Unpack values
#define AS_BOOL(value)    ((value).as.boolean)
#define AS_NUMBER(value)  ((value).as.number)
#define AS_OBJ(value)     ((value).as.obj)

// Pack values
#define BOOL_VAL(value)   ((Value){ VAL_BOOL, { .boolean = value } })
#define NIL_VAL           ((Value){ VAL_NIL, { .number = 0 } })
#define NUMBER_VAL(value) ((Value){ VAL_NUMBER, { .number = value } })
#define OBJ_VAL(object)   ((Value){ VAL_OBJ, { .obj = (Obj*)object } })

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

// Is value truthy or falsy?
bool isFalsy(Value value);

// Do 2 values are equal?
bool valuesEqual(Value a, Value b);

/// Print value to stdout.
void printValue(Value value);

#endif /* value_h */
