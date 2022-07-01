#pragma once

class TimeChecker
{
public:
	TimeChecker(uint64_t* _result)
		: Result(_result)
	{
		Start = GetTickCount64();
	}

	~TimeChecker()
	{
		(*Result) = GetTickCount64() - Start;
	}

	uint64_t Start;
	uint64_t* Result;
};