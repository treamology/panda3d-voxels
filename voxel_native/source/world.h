#pragma once

#include "pandabase.h"
#include "nodePath.h"

#include "chunk.h"

class World : public NodePath {
private:
	bool task_chain_initialized;
	vector<vector<Chunk>> chunks;

PUBLISHED:
	World(unsigned size_x, unsigned size_y, string done_event_name, string progress_event_name);

	static void setup_task_chain();
	static void setup_task_chain(unsigned num_threads);
};