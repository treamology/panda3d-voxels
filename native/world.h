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
public:
	static void initial_chunk_load_event(const Event *event, void *data);
	static void mesh_done_callback(const Event *event, void *data);

private:
	AsyncTaskManager &task_manager;
	EventHandler &event_handler;

	bool task_chain_initialized = false;
	bool initial_load = true;
	int initial_chunks_finished = 0;

	int size_x, size_y;
	int initial_num_chunks;

	//std::vector<std::vector<PT(Chunk)>> chunks;
	std::map<ChunkCoord, PT(Chunk)> chunks;

	void start_initial_mesh_generation();
PUBLISHED:
	string done_event_name, progress_event_name;

PUBLISHED:
	World(int size_x, int size_y, string done_event_name, string progress_event_name);
	~World();

	Chunk& get_chunk(int x, int y);

	void start_initial_generation();
	static void setup_task_chain();
	static void setup_task_chain(unsigned num_threads);
};