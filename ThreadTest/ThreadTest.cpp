#include "MainHeader.hpp"


int main()
{
	uint64_t LoopFuncDelay = 0;
	uint64_t LoopDelay = 0;
	uint64_t LoopWaitCreateThreadFuncDelay = 0;
	uint64_t LoopWaitCreateThreadDelay = 0;
	uint64_t LoopWaitBeginThreadFuncDelay = 0;
	uint64_t LoopWaitBeginThreadDelay = 0;
	uint64_t EventWaitCreateThreadFuncDelay = 0;
	uint64_t EventWaitCreateThreadDelay = 0;
	uint64_t EventWaitBeginThreadFuncDelay = 0;
	uint64_t EventWaitBeginThreadDelay = 0;
	uint64_t microThreadFuncDelay = 0;
	uint64_t microThreadDelay = 0;
	uint64_t microThreadConcurrentQueueFuncDelay = 0;
	uint64_t microThreadConcurrentQueueDelay = 0;
	uint64_t ThreadPoolFuncDelay = 0;
	uint64_t ThreadPoolDelay = 0;

	int LoopMax = 10000;

	LoopCheck(LoopMax, &LoopFuncDelay, &LoopDelay);
	LoopWaitCreateThreadCheck(100, &LoopWaitCreateThreadFuncDelay, &LoopWaitCreateThreadDelay);
	LoopWaitBeginThreadCheck(100, &LoopWaitBeginThreadFuncDelay, &LoopWaitBeginThreadDelay);
	EventWaitCreateThreadCheck(LoopMax, &EventWaitCreateThreadFuncDelay, &EventWaitCreateThreadDelay);
	EventWaitBeginThreadCheck(LoopMax, &EventWaitBeginThreadFuncDelay, &EventWaitBeginThreadDelay);
	microThreadCheck(LoopMax, &microThreadFuncDelay, &microThreadDelay);
	microThreadConcurrentQueueCheck(LoopMax, &microThreadConcurrentQueueFuncDelay, &microThreadConcurrentQueueDelay);
	ThreadPoolCheck(LoopMax, &ThreadPoolFuncDelay, &ThreadPoolDelay);

	printf("LoopDelay | Func : %lld | Calc : %lld | \n", LoopFuncDelay, LoopDelay);
	printf("LoopWaitCreateThreadDelay | Func : %lld | Calc : %lld | \n", LoopWaitCreateThreadFuncDelay, LoopWaitCreateThreadDelay);
	printf("LoopWaitBeginThreadDelay | Func : %lld | Calc : %lld | \n", LoopWaitBeginThreadFuncDelay, LoopWaitBeginThreadDelay);
	printf("EventWaitCreateThreadDelay | Func : %lld | Calc : %lld | \n", EventWaitCreateThreadFuncDelay, EventWaitCreateThreadDelay);
	printf("EventWaitBeginThreadDelay | Func : %lld | Calc : %lld | \n", EventWaitBeginThreadFuncDelay, EventWaitBeginThreadDelay);
	printf("microThreadDelay | Func : %lld | Calc : %lld | \n", microThreadFuncDelay, microThreadDelay);
	printf("ThreadPoolDelay | Func : %lld | Calc : %lld | \n", ThreadPoolFuncDelay, ThreadPoolDelay);
}
