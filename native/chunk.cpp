#include "chunk.h"

#include "block_type.h"

#include "geomVertexWriter.h"
#include "geomVertexData.h"
#include "geomVertexFormat.h"
#include "geomTriangles.h"
#include "geomNode.h"
#include "geom.h"


Chunk::Chunk() {}

Chunk::Chunk(PT(ChunkBlockData) blocks) : blocks(blocks) {}

void Chunk::init_blocks() {
	blocks = new ChunkBlockData(CHUNK_WIDTH, CHUNK_WIDTH, CHUNK_HEIGHT);
	blocks_initialized = true;
}

Chunk::~Chunk() { }