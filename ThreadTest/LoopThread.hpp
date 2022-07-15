#pragma once

struct LoopWaitThreadParameter
{
	volatile long* LiveControl = 0;
	volatile long* Enter = 0;
	volatile long* CalcValue = nullptr;
};

DWORD LoopWaitIncrease(LPVOID _param)
{
	LoopWaitThreadParameter* Parse = (LoopWaitThreadParameter*)_param;

	while (1 == *(Parse->LiveControl))
	{
		if (1 == *(Parse->Enter))
		{
			InterlockedAdd(Parse->CalcValue, 1);

			delete Parse;
			return 0;
		}
		Sleep(1);
	}

	delete Parse;
	return 0;
}

void LoopWaitBeginIncrease(void* _param)
{
	LoopWaitThreadParameter* Parse = (LoopWaitThreadParameter*)_param;

	while (1 == *(Parse->LiveControl))
	{
		if (1 == *(Parse->Enter))
		{
			InterlockedAdd(Parse->CalcValue, 1);

			delete Parse;
			_endthread();
			return;
		}
		Sleep(1);
	}

	delete Parse;
	_endthread();
	return;
}

// for STL Thread
class LoopWait_stl_ThreadControl
{
public:
	LoopWait_stl_ThreadControl(volatile long* _liveControl, volatile long* _enter, volatile long* _Target)
	{
		LoopWaitThreadParameter* Param = new LoopWaitThreadParameter();
		Param->LiveControl = _liveControl;
		Param->Enter = _enter;
		Param->CalcValue = (volatile long*)_Target;

		// 01: async를 이용하여 비동기로 콜러 실행. std::launch::async 옵션을 이용하여 즉시 실행.
		_f = std::async(std::launch::async, LoopWaitIncrease, Param);
	}

	~LoopWait_stl_ThreadControl()
	{
		// 02. feature<...>.wait()을 이용하여 콜러 실행이 완료 될 때까지 대기
		_f.wait();
	}

	std::future<DWORD> _f;
	LPVOID Parameter = nullptr;
};


volatile long LoopWaitStlThreadCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker Func(FuncTimeDelay);
	volatile long Thread_Value = 0;
	volatile long Thread_Live = 1;
	volatile long Thread_Enter = 0;

	std::vector<LoopWait_stl_ThreadControl*> threads;
	threads.clear();

	for (int loop = 0; _loopMax > loop; ++loop)
	{
		DWORD dwThreadID = 0;
		threads.push_back(new LoopWait_stl_ThreadControl(&Thread_Live, &Thread_Enter, &Thread_Value));
	}

	{
		TimeChecker Calc(TimeDelay);
		InterlockedExchange(&Thread_Enter, 1);
		while (InterlockedCompareExchange(&Thread_Value, _loopMax, _loopMax) != _loopMax) {};
	}

	for (int loop = 0; threads.size() > loop; ++loop)
	{
		delete threads[loop];
	}

	InterlockedExchange(&Thread_Live, 0);
	threads.clear();
	return Thread_Value;
}

class LoopWaitThreadControl
{
public:
	LoopWaitThreadControl(volatile long* _liveControl, volatile long* _enter, volatile long* _Target)
	{
		LoopWaitThreadParameter* Param = new LoopWaitThreadParameter();
		Param->LiveControl = _liveControl;
		Param->Enter = _enter;
		Param->CalcValue = (volatile long*)_Target;
		Thread = CreateThread(NULL, 0, LoopWaitIncrease, Param, 0, &ThreadID);
	}

	~LoopWaitThreadControl()
	{
		WaitForSingleObject(Thread, INFINITE);
		CloseHandle(Thread);
		Thread = INVALID_HANDLE_VALUE;
	}

	DWORD ThreadID = 0;
	HANDLE Thread = INVALID_HANDLE_VALUE;
	LPVOID Parameter = nullptr;
};

class LoopWaitBeginThreadControl
{
public:
	LoopWaitBeginThreadControl(volatile long* _liveControl, volatile long* _enter, volatile long* _Target)
	{
		LoopWaitThreadParameter* Param = new LoopWaitThreadParameter();
		Param->LiveControl = _liveControl;
		Param->Enter = _enter;
		Param->CalcValue = (volatile long*)_Target;
		Thread = (HANDLE)_beginthread(LoopWaitBeginIncrease, 0, Param);
		if ((INVALID_HANDLE_VALUE == Thread) || (0 == Thread))
		{
			throw - 1;
		}
	}

	~LoopWaitBeginThreadControl()
	{
		WaitForSingleObject(Thread, INFINITE);
		Thread = INVALID_HANDLE_VALUE;
	}

	DWORD ThreadID = 0;
	HANDLE Thread = INVALID_HANDLE_VALUE;
	LPVOID Parameter = nullptr;
};

volatile long LoopWaitCreateThreadCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker Func(FuncTimeDelay);
	volatile long Thread_Value = 0;
	volatile long Thread_Live = 1;
	volatile long Thread_Enter = 0;

	std::vector<LoopWaitThreadControl*> threads;
	threads.clear();

	for (int loop = 0; _loopMax > loop; ++loop)
	{
		DWORD dwThreadID = 0;
		threads.push_back(new LoopWaitThreadControl(&Thread_Live, &Thread_Enter, &Thread_Value));
	}

	{
		TimeChecker Calc(TimeDelay);
		InterlockedExchange(&Thread_Enter, 1);
		while (InterlockedCompareExchange(&Thread_Value, _loopMax, _loopMax) != _loopMax) {};
	}

	for (int loop = 0; threads.size() > loop; ++loop)
	{
		delete threads[loop];
	}

	InterlockedExchange(&Thread_Live, 0);
	threads.clear();
	return Thread_Value;
}

volatile long LoopWaitBeginThreadCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker Func(FuncTimeDelay);
	volatile long Thread_Value = 0;
	volatile long Thread_Live = 1;
	volatile long Thread_Enter = 0;

	std::vector<LoopWaitBeginThreadControl*> threads;
	threads.clear();

	for (int loop = 0; _loopMax > loop; ++loop)
	{
		DWORD dwThreadID = 0;
		threads.push_back(new LoopWaitBeginThreadControl(&Thread_Live, &Thread_Enter, &Thread_Value));
	}

	{
		TimeChecker Calc(TimeDelay);
		InterlockedExchange(&Thread_Enter, 1);
		while (InterlockedCompareExchange(&Thread_Value, _loopMax, _loopMax) != _loopMax) {};
	}

	for (int loop = 0; threads.size() > loop; ++loop)
	{
		delete threads[loop];
	}

	InterlockedExchange(&Thread_Live, 0);
	threads.clear();
	return Thread_Value;
}
