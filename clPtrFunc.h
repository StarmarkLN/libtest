#pragma once
#include "Header.h"


class clPtrFunc
{
public:
    void Test();

	// определяем указатели на функцию
    void (*message) (void);
	int (*operation)(int, int);

    int a;
    int b;
    int result;
private:

protected:
};
