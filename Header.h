#pragma once


#include "Porting.h"

#define ECS gnu

#include <thread>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
//include <tchar.h>

#include <unistd.h>

#include <iostream>
//#include <format>
#include <fstream>

#include <cmath>
#include <ctime>
#include <cstdlib>


#if ECS == gnu
#include <cstring>
#define ECString string
using namespace std;
#else
#include <bstring.h>
#define ECString string
#endif

#include <vector>

#include <stdexcept>

#include "onoffmodule.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS_GLOBALS

#define DATE_CURRENT	__DATE__
#define TIME_CURRENT	__TIME__

using namespace std;
