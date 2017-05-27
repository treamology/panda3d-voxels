#include "chunk.h"

#include "block_type.h"

#include "geomVertexWriter.h"
#include "geomVertexData.h"
#include "geomVertexFormat.h"
#include "geomTriangles.h"
#include "geomNode.h"
#include "geom.h"


Chunk::Chunk() : blocks(CHUNK_WIDTH, CHUNK_WIDTH, CHUNK_HEIGHT) {}

Chunk::Chunk(ChunkBlockData blocks) : blocks(blocks) {}