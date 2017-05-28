#include "chunk_generation_task.h"


//ChunkGenerationTask::ChunkGenerationTask(int chunk_x, int chunk_y, string done_event_name) : AsyncTask("ChunkGeneration"),
//	chunk_x(chunk_x), chunk_y(chunk_y), gen_chunk(new Chunk()) {
//	set_done_event(done_event_name);
//}

ChunkGenerationTask::ChunkGenerationTask(Chunk* chunk, int chunk_x, int chunk_y, string done_event_name) : AsyncTask("ChunkGeneration"),
	gen_chunk(chunk), chunk_x(chunk_x), chunk_y(chunk_y) {
	set_done_event(done_event_name);
}


/**
 * Generates the block data for a single chunk. Creates a new chunk instance
 * if none was provided.
 */
AsyncTask::DoneStatus ChunkGenerationTask::do_task() {
	if (!gen_chunk) {
		gen_chunk = new Chunk();
	}

	for (int i = 0; i < Chunk::CHUNK_WIDTH; i++) {
		for (int j = 0; j < Chunk::CHUNK_WIDTH; j++) {
			gen_chunk->blocks(i, j, 0).type = BlockType_NotAir;
		}
	}

	return AsyncTask::DS_done;
}
