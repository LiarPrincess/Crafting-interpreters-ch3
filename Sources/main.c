// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
// If a copy of the MPL was not distributed with this file,
// You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char * argv[]) {

  Chunk chunk;
  initChunk(&chunk);
  writeChunk(&chunk, OP_RETURN);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT);
  writeChunk(&chunk, constant);

  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);

  return 0;
}
