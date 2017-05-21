#ifndef BLOCK_H
#define BLOCK_H

#include <cinttypes>
#include "pandabase.h"

class Block {
PUBLISHED:
	uint8_t type = 1;
	Block() {}
};

#endif