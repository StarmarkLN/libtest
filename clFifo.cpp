#include "clFifo.h"

template <class T>
void clFifo<T>::init(T* data, uint8_t size)
{
	mData = data;
	mSize = size;
	mHead = mTail = 0;
}


template <class T>
void clFifo<T>::flush(void)
{
	mHead = mTail = 0;
}


template <class T>
int8_t clFifo<T>::put(T dt)
{
	if (((mHead - mTail) & FIFO_MASK) >= (mSize))
	{
		mHead = mTail = 0;
		return -1;
	}

	mData[mHead++] = dt;
	mHead &= FIFO_MASK;

	return 0;
}


template <class T>
int8_t clFifo<T>::get(T* dt)
{
	if (mHead != mTail)
	{
		*dt = mData[mTail++];
		mTail &= FIFO_MASK;

		return 0;
	}
	else
	{
		return -1;
	}
}


template <class T>
int8_t clFifo<T>::count(void)
{
	if (mHead >= mTail)
		return (mHead - mTail);
	else
		return ((mSize - mTail) + mHead);

	// или так -> //return (mHead - mTail)&FIFO_MASK;
}


template <class T>
void clFifo<T>::copyTo(T* exdata)
{
	uint8_t i = 0;

	while (mTail != mHead)
	{
		exdata[i] = mData[mTail++];
		mTail &= FIFO_MASK;
		i++;
	}

	mHead = mTail = 0; // flush
}

