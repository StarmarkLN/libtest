#pragma once
#include  <stdint.h>
#include "onoffmodule.h"

#define FIFO_LENGHT	128
#define FIFO_MASK	(FIFO_LENGHT-1)

template <class T>
class clFifo
{
public:
	void init(T* data, uint8_t size);

	void flush(void);	// reset fifo
	int8_t put(T dt);	// add data to fifo
	int8_t get(T* dt);	// cut data from fifo
	int8_t count(void);	

	void copyTo(T* exdata);

private:
	uint8_t mHead; 		// write pointer
	uint8_t mTail; 		// read pointer
	uint8_t mSize; 		// size buffer
	T* mData;		// ptr to buffer
};

