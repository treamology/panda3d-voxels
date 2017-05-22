#pragma once

#include <cinttypes>
#include "pandabase.h"
#include "BlockType.h"

class Block {
PUBLISHED:
	BlockType type = BlockType_NotAir;
	Block() {}
};