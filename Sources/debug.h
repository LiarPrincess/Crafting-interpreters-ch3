// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
// If a copy of the MPL was not distributed with this file,
// You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef debug_h
#define debug_h

#include "common.h"
#include "chunk.h"

// Print the content of the chunk.
void disassembleChunk(Chunk* chunk, const char* name);

// Print single byte(code).
int disassembleInstruction(Chunk* chunk, int offset);

#endif /* debug_h */
