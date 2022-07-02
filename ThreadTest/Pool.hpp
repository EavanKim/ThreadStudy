#pragma once

volatile long SimplePoolCalcTarget = 0;

void CalcWork()
{
	InterlockedAdd(&SimplePoolCalcTarget, 1);
}

void MyWorkCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Parameter, PTP_WORK Work)
{
	UNREFERENCED_PARAMETER(Instance);
	UNREFERENCED_PARAMETER(Parameter);
	UNREFERENCED_PARAMETER(Work);

	CalcWork();
}

VOID
CALLBACK
MyTimerCallback(
	PTP_CALLBACK_INSTANCE Instance,
	PVOID                 Parameter,
	PTP_TIMER             Timer
)
{
	// Instance, Parameter, and Timer not used in this example.
	UNREFERENCED_PARAMETER(Instance);
	UNREFERENCED_PARAMETER(Parameter);
	UNREFERENCED_PARAMETER(Timer);


}

volatile long ThreadPoolCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
    BOOL bRet = FALSE;
    PTP_WORK CalcFunc = NULL;
    PTP_POOL pool = NULL;
	PTP_TIMER timer = NULL;
    PTP_WORK_CALLBACK workcallback = MyWorkCallback;
    TP_CALLBACK_ENVIRON CallBackEnviron;
    PTP_CLEANUP_GROUP cleanupgroup = NULL;
    FILETIME FileDueTime;
    ULARGE_INTEGER ulDueTime;
    UINT rollback = 0;
	TimeChecker Func(FuncTimeDelay);

	InitializeThreadpoolEnvironment(&CallBackEnviron);
	
	pool = CreateThreadpool(NULL);
	SetThreadpoolThreadMaximum(pool, 1);
	cleanupgroup = CreateThreadpoolCleanupGroup();
	SetThreadpoolCallbackPool(&CallBackEnviron, pool);
	
	CalcFunc = CreateThreadpoolWork(MyWorkCallback, NULL, &CallBackEnviron);

	for (int Count = 0; _loopMax > Count; ++Count)
		SubmitThreadpoolWork(CalcFunc);
	timer = CreateThreadpoolTimer(MyTimerCallback, NULL, &CallBackEnviron);

	ulDueTime.QuadPart = (ULONGLONG)-(1 * 10 * 1000 * 1000);
	FileDueTime.dwHighDateTime = ulDueTime.HighPart;
	FileDueTime.dwLowDateTime = ulDueTime.LowPart;
	{
		TimeChecker Calc(TimeDelay);
		SetThreadpoolTimer(timer, &FileDueTime, 0, 0);
		while (InterlockedCompareExchange(&SimplePoolCalcTarget, _loopMax, _loopMax) != _loopMax) {};
	}

	CloseThreadpoolCleanupGroupMembers(cleanupgroup, FALSE, NULL);
	CloseThreadpool(pool);

	return SimplePoolCalcTarget;
}