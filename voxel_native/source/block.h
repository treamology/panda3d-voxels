#pragma once

#include <cinttypes>
#include "pandabase.h"
#include "block_type.h"

class Block {
PUBLISHED:
	BlockType type = BlockType_NotAir;
	Block() {}
};