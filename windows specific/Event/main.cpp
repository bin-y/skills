#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <thread>
#include <array>
#include <memory>

#define THREAD_COUNT 5 
#define FUNNY_THREAD_ID 3

#if FUNNY_THREAD_ID >= THREAD_COUNT
#error invalid funny thread id
#endif

typedef struct {
	int32_t id;
	HANDLE do_work_event;
	HANDLE initialize_finish_event;
}THEREAD_PARAMETERS;

using std::thread;
using std::array;
using std::unique_ptr;

static void wait_thread(THEREAD_PARAMETERS& parameters) {
	auto wait_result = SignalObjectAndWait(parameters.initialize_finish_event, parameters.do_work_event, INFINITE, TRUE);
	if (wait_result != WAIT_OBJECT_0)
		return;

	if (parameters.id == FUNNY_THREAD_ID) {
		printf("won't approach\n");
	}
	printf("thread %d done.\n", parameters.id);
}


int main() {
	printf("funny thread id:%d\n", FUNNY_THREAD_ID);

	HANDLE do_work_event = CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);

	typedef struct {
		unique_ptr<thread> object;
		THEREAD_PARAMETERS parameters;
	}WORKER_THREAD;
	array<HANDLE, THREAD_COUNT> thread_initialize_finish_events;
	array<WORKER_THREAD, THREAD_COUNT> worker_threads;

	{
		int32_t id = 0;
		for (auto& worker_thread : worker_threads)
		{
			worker_thread.parameters.id = id;
			worker_thread.parameters.do_work_event = do_work_event;
			worker_thread.parameters.initialize_finish_event = CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);
			worker_thread.object.reset(new thread(wait_thread, std::ref(worker_thread.parameters)));
			thread_initialize_finish_events[id] = worker_thread.parameters.initialize_finish_event;
			id++;
		}
	}

	if (WaitForMultipleObjects(THREAD_COUNT, thread_initialize_finish_events.data(), true, INFINITE)
		!= WAIT_OBJECT_0) {
		return -__LINE__;
	}
	
	auto funny_thread = worker_threads[FUNNY_THREAD_ID].object.get();

	// signal event when funny thread is suspended, and resume the funny thread after the event is reset
	SuspendThread(funny_thread->native_handle());
	SetEvent(do_work_event);
	Sleep(1);
	ResetEvent(do_work_event);
	ResumeThread(funny_thread->native_handle());

	for (auto& worker_thread : worker_threads) {
		worker_thread.object->join(); // funnny thread won't return, it keeps waiting for do_work_event
	}
	printf("won't approach\n");
	// in case someone will pick on this:
	// I know some handle is not closed, but clean up code after this line will not execute anyway.
	return 0;
}