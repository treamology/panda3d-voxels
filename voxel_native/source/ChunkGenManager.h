#pragma once

#include "pandabase.h"
#include "Block.h"
#include "geomNode.h"
#include "nodePath.h"

class ChunkGenManager : public NodePath {
PUBLISHED:
	ChunkGenManager();
	Block*** generate_blocks(int chunk_x, int chunk_y, int seed);
	PT(GeomNode) generate_mesh(Block*** block_data);
};