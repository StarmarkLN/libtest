#pragma once
#include "Header.h"

class clLT
{
public:
	clLT()
	{
		Load(0);
	}

	void Load(int32_t thrsh);

	void ReLoad();

	void Start();

	void Restart();

	void Restart(int32_t thrsh);

	void Stop();

	bool isFlag();

	bool isRun();

	void Work(int8_t evTick);

private:
	int32_t	mCnt;	//--- counter
	int32_t mThrsh;	//--- threshould
	bool    mFlag;  //--- flag = (cnt == trsh);
	bool    mRun;	//--- after Start();

protected:

};
