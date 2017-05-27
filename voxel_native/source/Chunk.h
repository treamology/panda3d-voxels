#pragma once

#include "pandabase.h"
#include "nodePath.h"

#include "referenceCount.h"
#include "block.h"
#include "chunk_block_data.h"

class ChunkGenerationTask;

class Chunk : public ReferenceCount {
	friend class ChunkGenerationTask;

private:
	ChunkBlockData blocks;

public:
	static const int CHUNK_WIDTH = 16;
	static const int CHUNK_HEIGHT = 256;

PUBLISHED:
	int testValue;
	INLINE static int get_chunk_width();
	MAKE_PROPERTY(CHUNK_WIDTH, get_chunk_width);
	INLINE static int get_chunk_height();
	MAKE_PROPERTY(CHUNK_HEIGHT, get_chunk_height);

	Chunk();
	Chunk(ChunkBlockData blocks);

	//void generate_geometry();
	
};

#include "Chunk.I"