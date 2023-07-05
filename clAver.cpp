#include "clAver.h"

#ifndef DEBUG_EN

template <class T>
T clAver<T>::execute(T dt)
{
	mSumma -= mArr[mPArr];
	mSumma += dt;
	mArr[mPArr] = dt;

	mPArr++;
	if (mPArr == mDepth)
		mPArr = 0;

	return (mSumma / mDepth);
}

template <class T>
void clAver<T>::InitAver(T dt_init, int depth_init)
{
	if (mDepth > AVER_DEPTH)
	{
		mDepth = AVER_DEPTH;
	}
	else
	{
		mDepth = depth_init;
	}

	mSumma = 0.0f;

	for (int i = 0; i < mDepth; i++)
	{
		mSumma += dt_init;
		mArr[i] = dt_init;
	}

	mPArr = 0;
}

#endif

#ifdef DEBUG_EN

template <class T>
T clAver<T>::execute(T dt)
{
	mAver.Summa -= mAver.Arr[mAver.pArr];
	mAver.Summa += dt;
	mAver.Arr[mAver.pArr] = dt;

	(mAver.pArr)++;
	if (mAver.pArr == mAver.depth)
		mAver.pArr = 0;

	return (mAver.Summa / mAver.depth);
}

template <class T>
void clAver<T>::InitAver(T dt_init, int depth_init)
{
	if (depth_init > AVER_DEPTH)
	{
		mAver.depth = AVER_DEPTH;
	}
	else
	{
		mAver.depth = depth_init;
	}

	mAver.Summa = 0.0f;

	for (int i = 0; i < mAver.depth; i++)
	{
		mAver.Summa += dt_init;
		mAver.Arr[i] = dt_init;
	}

	mAver.pArr = 0;
}

#endif

