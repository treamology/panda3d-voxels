#include "chunk_block_data.h"

ChunkBlockData::ChunkBlockData(size_t dx, size_t dy, size_t dz, BlockType fill_type) :
	dx(dx), dy(dy), dz(dz), data(dx * dy * dz, Block(fill_type)) {}

Block& ChunkBlockData::operator()(size_t ix, size_t iy, size_t iz) {
	assert(ix < dx);
	assert(iy < dy);
	assert(iz < dz);
	return data[(ix * dy * dz) + (iy * dz) + iz];
}

const Block& ChunkBlockData::operator()(size_t ix, size_t iy, size_t iz) const {
	assert(ix < dx);
	assert(iy < dy);
	assert(iz < dz);
	return data[(ix * dy * dz) + (iy * dz) + iz];
}