#pragma once

#include "pandabase.h"
#include "nodePath.h"

#include "referenceCount.h"
#include "block.h"
#include "chunk_block_data.h"
#include "nodePath.h"

class ChunkGenerationTask;
class MeshGenerationTask;

typedef std::pair<int, int> ChunkCoord;

/**
 * Stores the block and mesh information for a group of blocks in the world.
 */

class Chunk : public ReferenceCount {
	friend class ChunkGenerationTask;
	friend class MeshGenerationTask;

private:
	PT(ChunkBlockData) blocks;

public:

	void init_blocks();
	bool blocks_initialized = false;

	static const int CHUNK_WIDTH = 16;
	static const int CHUNK_HEIGHT = 256;

	NodePath mesh_NP;
	ChunkCoord chunk_coord;

PUBLISHED:
	int testValue;
	INLINE static int get_chunk_width();
	MAKE_PROPERTY(CHUNK_WIDTH, get_chunk_width);
	INLINE static int get_chunk_height();
	MAKE_PROPERTY(CHUNK_HEIGHT, get_chunk_height);

	Chunk();
	Chunk(PT(ChunkBlockData) blocks);

	~Chunk();
	
};

#include "Chunk.I"