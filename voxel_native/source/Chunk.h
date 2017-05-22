#pragma once

#include "pandabase.h"
#include "nodePath.h"
#include "Block.h"

class Chunk : public NodePath {
private:
	Block ***block_array;

public:
	static const int CHUNK_WIDTH = 16;
	static const int CHUNK_HEIGHT = 256;

PUBLISHED:
	int testValue;
	INLINE static int get_chunk_width();
	MAKE_PROPERTY(CHUNK_WIDTH, get_chunk_width);
	INLINE static int get_chunk_height();
	MAKE_PROPERTY(CHUNK_HEIGHT, get_chunk_height);
	Chunk(int test);
	Chunk();

	~Chunk();

	//void generate_geometry();
};

#include "Chunk.I"