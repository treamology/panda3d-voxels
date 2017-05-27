#pragma once

#include "pandabase.h"
#include "asyncTask.h"

#include "chunk.h"
#include "chunk_block_data.h"

class ChunkGenerationTask : public AsyncTask {
public:
	ALLOC_DELETED_CHAIN(ChunkGenerationTask);

private:
	PT(Chunk) gen_chunk;
	int chunk_x, chunk_y;

PUBLISHED:
	ChunkGenerationTask(int chunk_x, int chunk_y, string done_event_name);
	ChunkGenerationTask(PT(Chunk) chunk, int chunk_x, int chunk_y, string done_event_name);

protected:
	virtual DoneStatus do_task();
	
};