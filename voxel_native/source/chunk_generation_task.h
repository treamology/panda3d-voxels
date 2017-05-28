#pragma once

#include "pandabase.h"
#include "asyncTask.h"

#include "chunk.h"
#include "chunk_block_data.h"


/**
 * Task that handles the world generation for a single block.
 * For now, it's just generating a giant plane, but soon actual
 * world generation will be added.
 */ 
class ChunkGenerationTask : public AsyncTask {
public:
	ALLOC_DELETED_CHAIN(ChunkGenerationTask);

	int chunk_x, chunk_y;
	Chunk* gen_chunk;
private:

PUBLISHED:
	//ChunkGenerationTask(int chunk_x, int chunk_y, string done_event_name);
	ChunkGenerationTask(Chunk* chunk, int chunk_x, int chunk_y, string done_event_name);

protected:
	virtual DoneStatus do_task();
	
};