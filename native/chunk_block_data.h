#pragma once

#include <vector>

#include "pandabase.h"
#include "referenceCount.h"

#include "block.h"
#include "block_type.h"

/**
 * A convenience class for storing the block data of a chunk.
 * Instead of using a 3D vector, which can be inefficient when changing
 * the size of it, a single vector is used and is abstracted away.
 */
class ChunkBlockData : public ReferenceCount {
private:
	size_t dx, dy, dz;
	std::vector<Block> data;

PUBLISHED:
	ChunkBlockData(size_t dx, size_t dy, size_t dz, BlockType fill_type = BlockType_Air);

public:

	Block& operator()(size_t ix, size_t iy, size_t iz);
	const Block& operator()(size_t ix, size_t iy, size_t iz) const;
};