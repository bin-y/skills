#include <windows.h>
#include <stdio.h>

#define TRIGGER_EXCEPTION *((int*)0) = 0

static unsigned int vectored_exception_handler_trigger_counter = 0;

static LONG CALLBACK vectored_handler(
	_In_ PEXCEPTION_POINTERS ExceptionInfo
) {
	printf("%d\n", __LINE__);
	// just in case someone will pick on counter++ ...
	auto exception_times = InterlockedIncrement(&vectored_exception_handler_trigger_counter);
	if (exception_times == 1) {
		// 'fix' the first exception
		// skip exception trigger code, move to next instrument
#ifdef _WIN64
		ExceptionInfo->ContextRecord->Rip += 11;
		// 11 = sizeof(TRIGGER_EXCEPTION)
		//    = sizeof(mov     dword ptr ds:0, 0)
		//    = sizeof(C7 04 25 00 00 00 00 00 00 00 00)
#else
		ExceptionInfo->ContextRecord->Eip += 10;
		// 10 = sizeof(TRIGGER_EXCEPTION)
		//    = sizeof(mov     large dword ptr ds:0, 0)
		//    = sizeof(C7 05 00 00 00 00 00 00 00 00)
#endif // _WIN64
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

int main() {
	AddVectoredExceptionHandler(0, vectored_handler);
	__try {
		__try {
			TRIGGER_EXCEPTION;
		}
		__except(1) {
			printf("won't approach\n");
		}
		__try {
			__try {
				TRIGGER_EXCEPTION;
			}
			__finally {
				printf("%d\n", __LINE__);
			}
		}
		__except (1) {
			printf("%d\n", __LINE__);
		}
	}
	__except (1) {
		printf("won't approach\n");
	}
	return 0;
}