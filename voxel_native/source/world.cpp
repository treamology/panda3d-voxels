#include <thread>

#include "asyncTaskChain.h"
#include "throw_event.h"

#include "chunk_generation_task.h"
#include "world.h"

World::World(unsigned size_x, unsigned size_y, string done_event_name, string progress_event_name) : NodePath("World"),
	task_manager(*AsyncTaskManager::get_global_ptr()),
	event_handler(*EventHandler::get_global_event_handler()),
	size_x(size_x),
	size_y(size_y),
	done_event_name(done_event_name),
	progress_event_name(progress_event_name)
{
	if (!task_chain_initialized) {
		setup_task_chain();
		task_chain_initialized = true;
	}
}

void World::generate() {
	event_handler.add_hook("done_generating_chunk", chunk_done_callback, this);

	for (unsigned i = 0; i < size_x; i++) {
		for (unsigned j = 0; j < size_y; j++) {
			PT(ChunkGenerationTask) task;
			task = new ChunkGenerationTask(i, j, "done_generating_chunk");
			task->set_task_chain("ChunkGenTaskChain");
			//task->set_sort(i + j);
			task_manager.add(task);
		}
	}
}

void World::chunk_done_callback(const Event *event, void *data) {
	World *self = (World *)data;
	self->num_chunks_finished++;
	throw_event(self->progress_event_name, self->num_chunks_finished);
}

void World::setup_task_chain() {
	unsigned num_threads = std::thread::hardware_concurrency();
	if (num_threads == 0) num_threads = 1;
	World::setup_task_chain(num_threads);
}

void World::setup_task_chain(unsigned num_threads) {
	AsyncTaskManager &task_manager = *AsyncTaskManager::get_global_ptr();
	AsyncTaskChain *task_chain = task_manager.make_task_chain("ChunkGenTaskChain");
	task_chain->set_num_threads(7);
	task_chain->set_timeslice_priority(true);
	//task_chain->set_frame_budget(1.0/100.0f);
	//task_chain->set_frame_sync(true);
	//task_chain->set_thread_priority(ThreadPriority::TP_low);
}