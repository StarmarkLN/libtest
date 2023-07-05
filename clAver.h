#pragma once
#include  <stdint.h>
#include "onoffmodule.h"

#define AVER_DEPTH   32

#ifndef DEBUG_EN

template <class T>
class clAver
{
public:
	T execute(T dt);
	void InitAver(T dt_init, int depth_init);

private:
	int mDepth;
	int mPArr;
	T   mSumma;
	T   mArr[AVER_DEPTH];
};

#endif

#ifdef DEBUG_EN

template <class T>
class clAver
{
public:
	T execute(T dt);
	void InitAver(T dt_init, int depth_init);

private:
	typedef struct
	{
		int depth;
		int pArr;
		T   Summa;
		T   Arr[AVER_DEPTH];
	}stAVER_T;

	stAVER_T mAver;
};

#endif
