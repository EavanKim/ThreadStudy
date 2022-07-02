#pragma once

struct EventWaitThreadParameter
{
	HANDLE Event = INVALID_HANDLE_VALUE;
	volatile long* CalcValue = nullptr;
};

DWORD EventWaitIncrease(LPVOID _param)
{
	EventWaitThreadParameter* Parse = (EventWaitThreadParameter*)_param;

	WaitForSingleObject(Parse->Event, INFINITE);

	InterlockedAdd(Parse->CalcValue, 1);

	delete Parse;
	return 0;
}

void EventWaitBeginIncrease(void* _param)
{
	EventWaitThreadParameter* Parse = (EventWaitThreadParameter*)_param;

	WaitForSingleObject(Parse->Event, INFINITE);

	InterlockedAdd(Parse->CalcValue, 1);

	delete Parse;
	_endthread();
}

class EventWaitThreadControl
{
public:
	EventWaitThreadControl(HANDLE _event, volatile long* _Target)
	{
		EventWaitThreadParameter* Param = new EventWaitThreadParameter();
		Param->Event = _event;
		Param->CalcValue = (volatile long*)_Target;
		Thread = CreateThread(NULL, 0, EventWaitIncrease, Param, 0, &ThreadID);
	}

	~EventWaitThreadControl()
	{
		WaitForSingleObject(Thread, INFINITE);
		CloseHandle(Thread);
		Thread = INVALID_HANDLE_VALUE;
	}

	DWORD ThreadID = 0;
	HANDLE Thread = INVALID_HANDLE_VALUE;
	LPVOID Parameter = nullptr;
};

class EventWaitBeginThreadControl
{
public:
	EventWaitBeginThreadControl(HANDLE _event, volatile long* _Target)
	{
		EventWaitThreadParameter* Param = new EventWaitThreadParameter();
		Param->Event = _event;
		Param->CalcValue = (volatile long*)_Target;
		Thread = (HANDLE)_beginthread(EventWaitBeginIncrease, 0, Param);
	}

	~EventWaitBeginThreadControl()
	{
		WaitForSingleObject(Thread, INFINITE);
		//CloseHandle(Thread);
		Thread = INVALID_HANDLE_VALUE;
	}

	DWORD ThreadID = 0;
	HANDLE Thread = INVALID_HANDLE_VALUE;
	LPVOID Parameter = nullptr;
};

void EventWaitCreateThreadCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker Func(FuncTimeDelay);
	HANDLE Event = CreateEvent(NULL, TRUE, FALSE, L"EventWaitCreateThread");
	volatile long Thread_Value = 0;

	std::vector<EventWaitThreadControl*> threads;
	threads.clear();

	for (int loop = 0; _loopMax > loop; ++loop)
	{
		DWORD dwThreadID = 0;
		threads.push_back(new EventWaitThreadControl(Event, &Thread_Value));
	}

	{
		TimeChecker Calc(TimeDelay);
		SetEvent(Event);
		while (InterlockedCompareExchange(&Thread_Value, -1, _loopMax) != _loopMax) {};
	}

	for (int loop = 0; threads.size() > loop; ++loop)
	{
		delete threads[loop];
	}

	CloseHandle(Event);
	threads.clear();
}

void EventWaitBeginThreadCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker Func(FuncTimeDelay);
	HANDLE Event = CreateEvent(NULL, TRUE, FALSE, L"EventWaitCreateThread");
	volatile long Thread_Value = 0;

	std::vector<EventWaitBeginThreadControl*> threads;
	threads.clear();

	for (int loop = 0; _loopMax > loop; ++loop)
	{
		DWORD dwThreadID = 0;
		threads.push_back(new EventWaitBeginThreadControl(Event, &Thread_Value));
	}

	{
		TimeChecker Calc(TimeDelay);
		SetEvent(Event);
		while (InterlockedCompareExchange(&Thread_Value, -1, _loopMax) != _loopMax) {};
	}

	for (int loop = 0; threads.size() > loop; ++loop)
	{
		delete threads[loop];
	}

	CloseHandle(Event);
	threads.clear();
}