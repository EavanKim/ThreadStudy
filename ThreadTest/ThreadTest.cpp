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

	printf("LoopDelay Run \n");
	printf("Result : %d \n", LoopCheck(LoopMax, &LoopFuncDelay, &LoopDelay));

	printf("LoopWaitCreateThreadCheck Run \n");
	printf("Result : %d \n", LoopWaitCreateThreadCheck(LoopMax / 10, &LoopWaitCreateThreadFuncDelay, &LoopWaitCreateThreadDelay));

	printf("LoopWaitBeginThreadCheck Run \n");
	printf("Result : %d \n", LoopWaitBeginThreadCheck(LoopMax / 10, &LoopWaitBeginThreadFuncDelay, &LoopWaitBeginThreadDelay));

	printf("EventWaitCreateThreadCheck Run \n");
	printf("Result : %d \n", EventWaitCreateThreadCheck(LoopMax / 10, &EventWaitCreateThreadFuncDelay, &EventWaitCreateThreadDelay));

	printf("EventWaitBeginThreadCheck Run \n");
	printf("Result : %d \n", EventWaitBeginThreadCheck(LoopMax / 10, &EventWaitBeginThreadFuncDelay, &EventWaitBeginThreadDelay));

	printf("microThreadCheck Run \n");
	printf("Result : %d \n", microThreadCheck(LoopMax, &microThreadFuncDelay, &microThreadDelay));

	printf("microThreadConcurrentQueueCheck Run \n");
	printf("Result : %d \n", microThreadConcurrentQueueCheck(LoopMax, &microThreadConcurrentQueueFuncDelay, &microThreadConcurrentQueueDelay));

	printf("ThreadPoolCheck Run \n");
	printf("Result : %d \n", ThreadPoolCheck(LoopMax, &ThreadPoolFuncDelay, &ThreadPoolDelay));

	printf("============================DelayResult==================================== \n");

	printf("LoopDelay | Func : %lld | Calc : %lld | \n", LoopFuncDelay, LoopDelay);
	printf("LoopWaitCreateThreadDelay | Func : %lld | Calc : %lld | \n", LoopWaitCreateThreadFuncDelay, LoopWaitCreateThreadDelay);
	printf("LoopWaitBeginThreadDelay | Func : %lld | Calc : %lld | \n", LoopWaitBeginThreadFuncDelay, LoopWaitBeginThreadDelay);
	printf("EventWaitCreateThreadDelay | Func : %lld | Calc : %lld | \n", EventWaitCreateThreadFuncDelay, EventWaitCreateThreadDelay);
	printf("EventWaitBeginThreadDelay | Func : %lld | Calc : %lld | \n", EventWaitBeginThreadFuncDelay, EventWaitBeginThreadDelay);
	printf("microThreadDelay | Func : %lld | Calc : %lld | \n", microThreadFuncDelay, microThreadDelay);
	printf("microThreadConcurrentQueueCheck | Func : %lld | Calc : %lld | \n", microThreadConcurrentQueueFuncDelay, microThreadConcurrentQueueDelay);
	printf("ThreadPoolDelay | Func : %lld | Calc : %lld | \n", ThreadPoolFuncDelay, ThreadPoolDelay);
}
