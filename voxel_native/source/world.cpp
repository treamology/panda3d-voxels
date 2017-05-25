#include <thread>

#include "asyncTaskChain.h"
#include "asyncTaskManager.h"

#include "world.h"

World::World(unsigned size_x, unsigned size_y, string done_event_name, string progress_event_name) : NodePath("World") {
	if (!task_chain_initialized) {
		setup_task_chain();
		task_chain_initialized = true;
	}
	
}

void World::setup_task_chain() {
	unsigned num_threads = std::thread::hardware_concurrency();
	if (num_threads == 0) num_threads = 1;
	World::setup_task_chain(num_threads);
}

void World::setup_task_chain(unsigned num_threads) {
	AsyncTaskManager *task_manager = AsyncTaskManager::get_global_ptr();
	AsyncTaskChain *task_chain = task_manager->make_task_chain("ChunkGenTaskChain");
	task_chain->set_num_threads(num_threads);
	task_chain->set_frame_sync(false);
}