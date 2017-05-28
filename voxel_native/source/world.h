#pragma once

#include "pandabase.h"
#include "nodePath.h"
#include "asyncTaskManager.h"
#include "eventHandler.h"

#include "chunk.h"

/**
 * The base node of the voxel world. All chunks of the world
 * are under this node in the scene graph
 */
class World : public NodePath {
private:
	AsyncTaskManager &task_manager;
	EventHandler &event_handler;

	bool task_chain_initialized = false;
	int num_chunks_finished = 0;

	vector<vector<Chunk>> chunks;

PUBLISHED:
	unsigned size_x, size_y;
	string done_event_name, progress_event_name;

public:
	static void chunk_done_callback(const Event *event, void *data);

PUBLISHED:
	World(unsigned size_x, unsigned size_y, string done_event_name, string progress_event_name);

	void generate();
	static void setup_task_chain();
	static void setup_task_chain(unsigned num_threads);
};