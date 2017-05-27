#pragma once

#include <vector>

#include "pandabase.h"

#include "block.h"
#include "block_type.h"

class ChunkBlockData {
private:
	size_t dx, dy, dz;
	std::vector<Block> data;

public:
	ChunkBlockData(size_t dx, size_t dy, size_t dz, BlockType fill_type = BlockType_Air);

	Block& operator()(size_t ix, size_t iy, size_t iz);
	const Block& operator()(size_t ix, size_t iy, size_t iz) const;
};