#pragma once

#include <cinttypes>
#include "pandabase.h"
#include "block_type.h"

/**
 * The basic unit of data for a block. Trying to keep it as small as possible.
 * Other properties of the block can be inferred from BlockType.
 */
class Block {
PUBLISHED:
	BlockType type = BlockType_NotAir;
	Block(BlockType type);
};