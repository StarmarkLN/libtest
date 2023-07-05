#include "clGeneratorXYZ.h"

clGeneratorXYZ::clGeneratorXYZ()
{}

void clGeneratorXYZ::gen(int8_t n)
{
	static int32_t arg = 0;

	xyz.x = (int16_t)(round(1000.0 * sinf((3 * 3.1415926 * arg) / 180 + 8.5)));
	xyz.y = (int16_t)(round(310.0 * sinf((7 * 3.1415926 * arg) / 180 + 18.5)));
	xyz.z = (int16_t)(round(56.0 * sinf((11 * 3.1415926 * arg) / 180 + 12.5)));
	xyz.n = n;

	arg++;
}

stXYZ_t clGeneratorXYZ::get(void)
{
	return xyz;
}

void clGeneratorXYZ::out(void)
{   
    char buf[100];
	int res = snprintf(buf, sizeof(buf), "XYZ[%6d] : %5d  %5d  %5d", xyz.n, xyz.x, xyz.y, xyz.z);
	std::string str = "error!";
	if (res >= 0 && res < sizeof(buf))
    	str = buf;

	std::cout << str << std::endl;
}
