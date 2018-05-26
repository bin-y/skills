#include <windows.h>
#include <stdio.h>

#define TRIGGER_EXCEPTION *((int*)0) = 0

static int ExceptionCount = 0;

static LONG CALLBACK VectoredHandler(
	_In_ PEXCEPTION_POINTERS ExceptionInfo
) {
	printf("%d\n", __LINE__);
	ExceptionCount++;
	if (ExceptionCount == 1) {
		// 'fix' the first exception
		// skip exception trigger code, move to next instrument
#ifdef _WIN64
		ExceptionInfo->ContextRecord->Rip += 11;
#else
		ExceptionInfo->ContextRecord->Eip += 10;
#endif // _WIN64
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

int main() {
	AddVectoredExceptionHandler(0, VectoredHandler);
	__try {
		__try {
			TRIGGER_EXCEPTION;
		}
		__except(1) {
			printf("won't approach");
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
		printf("won't approach");
	}
	return 0;
}