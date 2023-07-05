#include "clLT.h"

void clLT::Load(int32_t thrsh)
{
	mCnt = 0;
	mThrsh = thrsh;
	mFlag = false;
	mRun = false;
}

void clLT::ReLoad()
{
	mCnt = 0;
	mFlag = false;
	mRun = false;
}

void clLT::Start()
{
	mRun = true;
}

void clLT::Restart()
{
	mCnt = 0;
	mFlag = false;
	mRun = true;
}

void clLT::Restart(int32_t thrsh)
{
	mCnt = 0;
	mThrsh = thrsh;
	mFlag = false;
	mRun = true;
}

void clLT::Stop()
{
	mRun = false;
}

bool clLT::isFlag()
{
	return mFlag;
}

bool clLT::isRun()
{
	return mRun;
}

void clLT::Work(int8_t evTick)
{
	if (mRun == true)
	{
		if (evTick == 0)
		{
			mCnt++;
			if (mCnt == mThrsh)
			{
				mCnt = 0;
				mRun = false;
				mFlag = true;
			}
		}
	}
}
