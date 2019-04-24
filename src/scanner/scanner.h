#ifndef scanner_h
#define scanner_h

#include "token.h"

// Create new scanner for given source.
void initScanner(const char* source);

// Get single token from current source.
Token scanToken();

#endif /* scanner_h */
