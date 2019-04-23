#ifndef object_h
#define object_h

#include "common.h"
#include "value.h"

typedef enum {
  OBJ_STRING,
} ObjType;

struct sObj {
  ObjType type;
  struct sObj* next;
};

struct sObjString {
  Obj obj;
  int length;
  char* chars;
  uint32_t hash;
};

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

#define IS_STRING(value) isObjType(value, OBJ_STRING)

#define AS_STRING(value) ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString*)AS_OBJ(value))->chars)

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

// Take ownership of existing string
ObjString* takeString(char* chars, int length);

// Create new string based on arg and take ownership of it
ObjString* copyString(const char* chars, int length);

void printObject(Value value);

#endif /* object_h */
