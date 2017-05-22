#include "Chunk.h"

#include "BlockType.h"

#include "geomVertexWriter.h"
#include "geomVertexData.h"
#include "geomVertexFormat.h"
#include "geomTriangles.h"
#include "geomNode.h"
#include "geom.h"

Chunk::Chunk(int test) : NodePath("Chunk") { 
	testValue = test;
}

Chunk::Chunk() : Chunk(15) { }

Chunk::~Chunk() {
	if (block_array) {
		for (int i = 0; i < CHUNK_WIDTH; ++i) {
			for (int j = 0; j < CHUNK_WIDTH; ++j) {
				delete[] block_array[i][j];
			}
			delete[] block_array[i];
		}
		delete[] block_array;
	}

}