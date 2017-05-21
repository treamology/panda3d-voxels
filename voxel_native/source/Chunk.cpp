#include "Chunk.h"

Chunk::Chunk() : NodePath("Chunk") {
	block_array = new Block**[CHUNK_WIDTH];
	for (int i = 0; i < CHUNK_WIDTH; i++) {
		block_array[i] = new Block*[CHUNK_WIDTH];
		for (int j = 0; j < CHUNK_WIDTH; j++) {
			block_array[i][j] = new Block[CHUNK_HEIGHT];
		}
	}
}

Chunk::~Chunk() {
	for (int i = 0; i < CHUNK_WIDTH; ++i) {
		for (int j = 0; j < CHUNK_WIDTH; ++j) {
			delete[] block_array[i][j];
		}
		delete[] block_array[i];
	}
	delete[] block_array;
}