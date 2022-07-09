#include <iostream>
#include <Windows.h>
#include <process.h>
#include <vector>
#include <queue>
#include <concurrent_queue.h>
#include <thread>
#include <future>

/*===============================================================================================
* 
* 
* 
===============================================================================================*/
class TimeChecker_micro_sec
{
public:
	TimeChecker_micro_sec(uint64_t* _result)
		:Result(_result), _start_tp{ std::chrono::steady_clock::now() }
	{
	}
	~TimeChecker_micro_sec()
	{
		(*Result) = elapsed(); // microsecond
	}

	uint64_t elapsed() const
	{
		return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - _start_tp)).count();
	}

	void reset()
	{
		_start_tp = std::chrono::steady_clock::now();
	}

	uint64_t* Result; // micro second    
	std::chrono::steady_clock::time_point _start_tp;
};

/*===============================================================================================
*
*
*
===============================================================================================*/
struct LoopWaitThreadParameter
{
	volatile long* LiveControl = 0;
	volatile long* Enter = 0;
	volatile long* CalcValue = nullptr;
};

/*===============================================================================================
*
*
*
===============================================================================================*/
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

/*===============================================================================================
*
*
*
===============================================================================================*/
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


/*===============================================================================================
*
*
*
===============================================================================================*/
volatile long LoopWaitStlThreadCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker_micro_sec Func(FuncTimeDelay);
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
		TimeChecker_micro_sec Calc(TimeDelay);
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


/*===============================================================================================
*
* main
*
===============================================================================================*/
int main(int argc, char* argv[])
{
	uint64_t LoopWaitStlThreadFuncDelay = 0;
	uint64_t LoopWaitStlThreadDelay = 0;

	int LoopMax = 10000;

	printf("LoopWait_STL_ThreadCheck Run \n");
	printf("Result : %d \n", LoopWaitStlThreadCheck(LoopMax / 10, &LoopWaitStlThreadFuncDelay, &LoopWaitStlThreadDelay));


	printf("============================DelayResult============================================================== \n");

	printf("LoopWait_stl_ThreadDelay        | Func : %10lld [micro sec] | Calc : %10lld [micro sec] | \n", LoopWaitStlThreadFuncDelay, LoopWaitStlThreadDelay);

	return 0;
}