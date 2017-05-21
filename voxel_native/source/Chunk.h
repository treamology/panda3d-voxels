#ifndef CHUNK_H
#define CHUNK_H

#include "pandabase.h"
#include "nodePath.h"
#include "Block.h"

class Chunk : public NodePath {
private:
	Block ***block_array;
	//Block *block_array;
	
PUBLISHED:
	static const int CHUNK_WIDTH = 16;
	static const int CHUNK_HEIGHT = 256;
	Chunk();
	~Chunk();
};

#endif