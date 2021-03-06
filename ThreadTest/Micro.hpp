#pragma once

volatile long microRunLive = 0;

struct Param_microThread
{
	void(*m_func)(volatile long*);
	volatile long* param;
};

struct Param_microThreadMain
{
	CRITICAL_SECTION* m_criticalSection = nullptr;
	std::queue<Param_microThread*>* m_funcqueue = nullptr;
	volatile long* Run_Live = nullptr;
};

class microThread
{
public:
	microThread()
	{
		m_criticalSection = new CRITICAL_SECTION();
		InitializeCriticalSection(m_criticalSection);
		InterlockedExchange(&microRunLive, 1);
		Param_microThreadMain* createParam = new Param_microThreadMain();
		createParam->m_criticalSection = m_criticalSection;
		createParam->m_funcqueue = &m_funcqueue;
		Thread = (HANDLE)_beginthread(Run, 0, createParam);
	}

	~microThread()
	{
		DeleteCriticalSection(m_criticalSection);
		delete m_criticalSection;
	}

	static void Run(void* _param)
	{
		Param_microThreadMain* MainControlValue = (Param_microThreadMain*)_param;

		while (1 == microRunLive)
		{
			if (!MainControlValue->m_funcqueue->empty())
			{
				EnterCriticalSection(MainControlValue->m_criticalSection);
				Param_microThread* GetFirst = MainControlValue->m_funcqueue->front();
				GetFirst->m_func(GetFirst->param);
				MainControlValue->m_funcqueue->pop();
				LeaveCriticalSection(MainControlValue->m_criticalSection);
				delete GetFirst;
			}
			Sleep(1);
		}

		while (!MainControlValue->m_funcqueue->empty())
		{
			EnterCriticalSection(MainControlValue->m_criticalSection);
			Param_microThread* GetFirst = MainControlValue->m_funcqueue->front();
			GetFirst->m_func(GetFirst->param);
			MainControlValue->m_funcqueue->pop();
			LeaveCriticalSection(MainControlValue->m_criticalSection);
			delete GetFirst;
		}


		delete MainControlValue;
		_endthread();
	}

	void StopJoin()
	{
		InterlockedExchange(&microRunLive, 0);
		WaitForSingleObject(Thread, INFINITE);
	}

	static void Inter_Increase(volatile long* _param)
	{
		InterlockedAdd(_param, 1);
	}

	void Increase(volatile long* _param)
	{
		Param_microThread* create = new Param_microThread();
		create->m_func = microThread::Inter_Increase;
		create->param = _param;
		EnterCriticalSection(m_criticalSection);
		m_funcqueue.push(create);
		LeaveCriticalSection(m_criticalSection);
	}

	CRITICAL_SECTION* m_criticalSection = nullptr;
	std::queue<Param_microThread*> m_funcqueue;
	volatile long Run_Live = 0;
	HANDLE Thread = INVALID_HANDLE_VALUE;
};

struct Param_ConcurrentmicroThreadMain
{
	concurrency::concurrent_queue<Param_microThread*>* m_funcqueue = nullptr;
	volatile long* Run_Live = nullptr;
};

class ConcurrentmicroThread
{
public:
	ConcurrentmicroThread()
	{
		InterlockedExchange(&microRunLive, 1);
		Param_ConcurrentmicroThreadMain* createParam = new Param_ConcurrentmicroThreadMain();
		createParam->m_funcqueue = &m_funcqueue;
		Thread = (HANDLE)_beginthread(ConcurrentmicroThread::Run, 0, createParam);
	}

	~ConcurrentmicroThread()
	{
	}

	static void Run(void* _param)
	{
		Param_ConcurrentmicroThreadMain* MainControlValue = (Param_ConcurrentmicroThreadMain*)_param;

		while (1 == microRunLive)
		{
			Param_microThread* RunTarget = nullptr;

			if (MainControlValue->m_funcqueue->try_pop(RunTarget))
			{
				RunTarget->m_func(RunTarget->param);
				delete RunTarget;
			}
			Sleep(1);
		}

		Param_microThread* ExitRunTarget = nullptr;
		while (MainControlValue->m_funcqueue->try_pop(ExitRunTarget))
		{
			ExitRunTarget->m_func(ExitRunTarget->param);
			delete ExitRunTarget;
		}


		delete MainControlValue;
		_endthread();
	}

	void StopJoin()
	{
		InterlockedExchange(&microRunLive, 0);
		WaitForSingleObject(Thread, INFINITE);
	}

	static void Inter_Increase(volatile long* _param)
	{
		InterlockedAdd(_param, 1);
	}

	void Increase(volatile long* _param)
	{
		Param_microThread* create = new Param_microThread();
		create->m_func = ConcurrentmicroThread::Inter_Increase;
		create->param = _param;
		m_funcqueue.push(create);
	}

	concurrency::concurrent_queue<Param_microThread*> m_funcqueue;
	HANDLE Thread = INVALID_HANDLE_VALUE;
};

volatile long microThreadCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker Func(FuncTimeDelay);

	microThread* Instance = new microThread();
	volatile long Value = 0;
	{
		TimeChecker Calc(TimeDelay);
		for (int loop = 0; _loopMax > loop; ++loop)
		{
			Instance->Increase(&Value);
		}
		Instance->StopJoin();
	}

	delete Instance;

	return Value;
}

volatile long microThreadConcurrentQueueCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker Func(FuncTimeDelay);

	ConcurrentmicroThread* Instance = new ConcurrentmicroThread();
	volatile long Value = 0;
	{
		TimeChecker Calc(TimeDelay);
		for (int loop = 0; _loopMax > loop; ++loop)
		{
			Instance->Increase(&Value);
		}
		Instance->StopJoin();
	}

	delete Instance;

	return Value;
}