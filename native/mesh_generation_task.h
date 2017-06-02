#pragma once

#include "pandabase.h"
#include "asyncTask.h"
#include "geomNode.h"

#include "chunk.h"

/**
 * A task that generates meshes based on a chunk's block data,
 * and returns a GeomNode ready to be parented to the chunk.
 * Only naive mesh generation is supported at the moment (vertices
 * for every block)
 */
class MeshGenerationTask : public AsyncTask {
public:
	ALLOC_DELETED_CHAIN(MeshGenerationTask);

	enum GenStrategy {
		GS_Naive = 0,
		GS_Greedy,
	};

	MeshGenerationTask(Chunk& chunk, string done_event_name);
	
	Chunk& chunk;
	PT(GeomNode) finished_geom_node;

protected:
	virtual DoneStatus do_task();

};