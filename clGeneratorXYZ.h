#pragma once
#include "Header.h"

class clGeneratorXYZ
{
public:
    clGeneratorXYZ();

	void gen(int8_t n);
	stXYZ_t get(void);
	void out(void);

private:
	stXYZ_t xyz;

protected:
};

