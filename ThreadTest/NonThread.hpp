#pragma once


volatile long LoopCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker Func(FuncTimeDelay);

	volatile long CalcValue = 0;
	{
		TimeChecker Calc(TimeDelay);

		for (int loop = 0; 10000 > loop; ++loop)
		{
			InterlockedAdd(&CalcValue, 1);
		}
	}

	return CalcValue;
}