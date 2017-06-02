#include <thread>

#include "asyncTaskChain.h"
#include "throw_event.h"

#include "chunk_generation_task.h"
#include "mesh_generation_task.h"
#include "world.h"

World::World(int size_x, int size_y, string done_event_name, string progress_event_name) : NodePath("World"),
task_manager(*AsyncTaskManager::get_global_ptr()),
event_handler(*EventHandler::get_global_event_handler()),
size_x(size_x),
size_y(size_y),
done_event_name(done_event_name),
progress_event_name(progress_event_name)
{
	initial_num_chunks = size_x * size_y;
	/*chunks = std::vector<std::vector<PT(Chunk)>>(size_x, std::vector<PT(Chunk)>(size_y));

	for (int x = 0; x < size_x; x++) {
		auto col = std::vector<PT(Chunk)>(size_y);
		col.resize(size_y);
		for (int y = 0; y < size_y; y++) {
			col[y] = new Chunk();
		}

		chunks[x] = col;
	}*/

	chunks = std::map<ChunkCoord, PT(Chunk)>();

	for (int x = 0; x < size_x; x++) {
		for (int y = 0; y < size_y; y++) {
			auto coord = ChunkCoord(x, y);
			chunks[coord] = new Chunk();
			chunks[coord]->chunk_coord = coord;
		}
	}

	if (!task_chain_initialized) {
		setup_task_chain();
		task_chain_initialized = true;
	}
}

Chunk& World::get_chunk(int x, int y) {
	return *chunks[ChunkCoord(x, y)];
}

World::~World() {}

/**
 * Generates the world based on the given world size by adding ChunkGenerationTasks
 * to the multithreaded task chain.
 */
void World::start_initial_generation() {
	event_handler.add_hook("done_generating_chunk", initial_chunk_load_event, this);

	for (auto& chunkKeyVal : chunks) {
		PT(ChunkGenerationTask) task = new ChunkGenerationTask(*chunkKeyVal.second, chunkKeyVal.first.first, chunkKeyVal.first.second, "done_generating_chunk");
		task->set_task_chain("ChunkGenTaskChain");
		task_manager.add(task);
	}

	//for (unsigned i = 0; i < size_x; i++) {
	//	for (unsigned j = 0; j < size_y; j++) {
	//		PT(ChunkGenerationTask) task = new ChunkGenerationTask(*chunks[i][j], i, j, "done_generating_chunk");
	//		task->set_task_chain("ChunkGenTaskChain");
	//		task_manager.add(task);
	//	}
	//}
}

void World::start_initial_mesh_generation() {
	event_handler.add_hook("done_generating_chunk_mesh", mesh_done_callback, this);

	for (auto& chunkKeyVal : chunks) {
		PT(MeshGenerationTask) mesh_task = new MeshGenerationTask(*chunkKeyVal.second, "done_generating_chunk_mesh");
		mesh_task->set_task_chain("ChunkGenTaskChain");
		task_manager.add(mesh_task);
	}
}

void World::mesh_done_callback(const Event *event, void *data) {
	World *self = (World *)data;
	MeshGenerationTask& task = (MeshGenerationTask& )*event->get_parameter(0).get_typed_ref_count_value();
	task.chunk.mesh_NP.remove_node();
	task.chunk.mesh_NP = NodePath(task.finished_geom_node);
	task.chunk.mesh_NP.set_pos(task.chunk.chunk_coord.first * Chunk::CHUNK_WIDTH, task.chunk.chunk_coord.second * Chunk::CHUNK_WIDTH, 0);
	task.chunk.mesh_NP.reparent_to(*self);
}

void World::initial_chunk_load_event(const Event *event, void *data) {
	World *self = (World *)data;
	self->initial_chunks_finished++;
	throw_event(self->progress_event_name, self->initial_chunks_finished);
	if (self->initial_chunks_finished == self->initial_num_chunks) {
		throw_event(self->done_event_name);
		self->start_initial_mesh_generation();
	}
}

/**
 * Sets up the task chain inferring the number of cores.
 */
void World::setup_task_chain() {
	unsigned num_threads = std::thread::hardware_concurrency();
	if (num_threads != 0) num_threads -= 1; // Giving a thread count of 1 spawns an additional thread, 0 is the main thread.
	World::setup_task_chain(num_threads);
}

/**
 * Sets up the task chain with the specified number of cores.
 */
void World::setup_task_chain(unsigned num_threads) {
	AsyncTaskManager &task_manager = *AsyncTaskManager::get_global_ptr();
	AsyncTaskChain *task_chain = task_manager.make_task_chain("ChunkGenTaskChain");
	task_chain->set_num_threads(num_threads);
	task_chain->set_timeslice_priority(true);
	//task_chain->set_frame_budget(1.0/100.0f);
	//task_chain->set_frame_sync(true);
	//task_chain->set_thread_priority(ThreadPriority::TP_low);
}