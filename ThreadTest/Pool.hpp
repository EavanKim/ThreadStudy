#pragma once

void ThreadPoolCheck(int _loopMax, uint64_t* FuncTimeDelay, uint64_t* TimeDelay)
{
	TimeChecker Func(FuncTimeDelay);

	TimeChecker Calc(TimeDelay);
}