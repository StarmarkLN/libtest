#include "clMath.h"

//--- Преобразование float в int ------------------------
void clMath::floatToInt(float in, displayFloatToInt_t* out_value, int32_t dec_prec)
{
	if (in >= 0.0f)
	{
		out_value->sign = 0;
	}
	else
	{
		out_value->sign = 1;
		in = -in;
	}

	in = in + (0.5f / pow(10, dec_prec));
	out_value->out_int = (int32_t)in;
	in = in - (float)(out_value->out_int);
	out_value->out_dec = (int32_t)trunc(in * pow(10, dec_prec));
}

//--- Преобразование целого в строку --------------------
uint8_t clMath::intToStr(char* str, int16_t value, char endLine)
{
	uint8_t res = 0;
	char    symbols[10];
	uint8_t symbolsOffset = 0;
	bool addMinus;
	int v;

	symbols[symbolsOffset++] = endLine;
	if (value < 0) {
		v = -value;
		addMinus = true;
	}
	else {
		v = value;
		addMinus = false;
	}

	do {
		symbols[symbolsOffset++] = v % 10 + '0';
		v /= 10;
	} while (v != 0);

	if (addMinus == true) {
		symbols[symbolsOffset++] = '-';
	}

	res = symbolsOffset;
	while (symbolsOffset != 0) {
		symbolsOffset--;
		*str = symbols[symbolsOffset];
		str++;
	}
	return res;
}

//--- Взять старший и младший байт представления float -- 
uint16_t clMath::GetFloatHi(float value, uint8_t dir)
{
	union32_t un;
	un.f = value;
	return dir == 0 ? un.ui[0] : un.ui[1];
}

uint16_t clMath::GetFloatLo(float value, uint8_t dir)
{
	union32_t un;
	un.f = value; 
	return dir == 0 ? un.ui[1] : un.ui[0];
}

//--- Округление до определеннго знака после , ----------
float clMath::round(float val, int digit)
{
	int mult = 1;
	float divider = 1.0;

	switch (digit)
	{
	case 0: divider = 1.0;
		mult = 1;
		break;
	case 1: divider = 10.0;
		mult = 10;
		break;
	case 2: divider = 100.0;
		mult = 100;
		break;
	case 3: divider = 1000.0;
		mult = 1000;
		break;
	case 4: divider = 10000.0;
		mult = 10000;
		break;
	}

	if (val >= 0.0)
	{
		val = roundf(val * mult) / divider;
	}
	else
	{
		val = roundf(-val * mult) / divider;
	}

	return val;
}

//--- Преобразовать число в цепочку байт ----------------
void clMath::Val32ToARRdigit(uint32_t val, uint8_t* arr)
{
	uint32_t ttt = 0;

	arr[0] = val / 10000000;
	ttt = val % 10000000;

	arr[1] = ttt / 1000000;
	ttt = ttt % 1000000;

	arr[2] = ttt / 100000;
	ttt = ttt % 100000;

	arr[3] = ttt / 10000;
	ttt = ttt % 10000;

	arr[4] = ttt / 1000;
	ttt = ttt % 1000;

	arr[5] = ttt / 100;
	ttt = ttt % 100;

	arr[6] = ttt / 10;
	ttt = ttt % 10;

	arr[7] = ttt;
}

void clMath::HEX32ToARRdigit(uint32_t val, uint8_t* arr)
{
	uint32_t ttt = 0;

	arr[0] = val / 0x10000000;
	ttt = val % 0x10000000;

	arr[1] = ttt / 0x1000000;
	ttt = ttt % 0x1000000;

	arr[2] = ttt / 0x100000;
	ttt = ttt % 0x100000;

	arr[3] = ttt / 0x10000;
	ttt = ttt % 0x10000;

	arr[4] = ttt / 0x1000;
	ttt = ttt % 0x1000;

	arr[5] = ttt / 0x100;
	ttt = ttt % 0x100;

	arr[6] = ttt / 0x10;
	ttt = ttt % 0x10;

	arr[7] = ttt;
}

//--------------------------------------------------------------------------
uint64_t clMath::Uint64Revers(uint64_t val)
{
	uint64_t rev = 0;
	uint64_t mask = 0x0000000000000001;

	while (mask)
	{
		rev <<= 1;
		if (val & mask)
			rev |= 0x01;
		mask <<= 1;
	}

	return rev;
}

uint64_t clMath::Uint64ReversByBytes(uint64_t val)
{
	uint64_t rev = 0;

	for (uint8_t i = 0; i < 7; i++)
	{
		rev |= val & 0xFF;		
		val >>= 8;
		rev <<= 8;
	}
	rev |= val & 0xFF;

	return rev;
}

string clMath::reverstring(string s)
{
	int i, j;
	char c;
	int size = s.length();

	for (i = 0, j = size - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}

	return s;
}

//--- reverse:  переворачиваем строку s на месте
//--- ??? В MVS работает неправильно ???
void clMath::reverse(char s[])
{
	int i, j;
	char c;
	int size = strlen(s);

	for (i = 0, j = size - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

//--- itoa:  конвертируем n в символы в s 
int clMath::_itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)  /* записываем знак */
		n = -n;          /* делаем n положительным числом */
	i = 0;
	do {       					/* генерируем цифры в обратном порядке */
		s[i++] = n % 10 + '0';   /* берем следующую цифру */
	} while ((n /= 10) > 0);     /* удаляем */
	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';

	reverse(s);

	return i;
}

//--- XYZ_to_str:  получаем общую строку {X, Y, Z\r\n} 
int clMath::XYZ_to_str(char buf[], char stX[], char stY[], char stZ[], char stCNT[], int szX, int szY, int szZ, int szCNT)
{
	int i = 0;
	int j;

	for (j = 0; j < szX; j++)
	{
		if (stX[j] == '\0')
			break;
		buf[i++] = stX[j];
	}

	buf[i++] = ',';
	buf[i++] = ' ';

	for (j = 0; j < szY; j++)
	{
		if (stY[j] == '\0')
			break;
		buf[i++] = stY[j];
	}

	buf[i++] = ',';
	buf[i++] = ' ';

	for (j = 0; j < szZ; j++)
	{
		if (stZ[j] == '\0')
			break;
		buf[i++] = stZ[j];
	}

	buf[i++] = ',';
	buf[i++] = ' ';

	for (j = 0; j < szCNT; j++)
	{
		if (stCNT[j] == '\0')
			break;
		buf[i++] = stCNT[j];
	}

	buf[i++] = '\r';
	buf[i++] = '\n';

	return i;
}

//--- XYZ_to_str:  получаем общую строку {X, Y, Z\r\n} 
int clMath::XYZ_to_str_NoCNT(char buf[], char stX[], char stY[], char stZ[], int szX, int szY, int szZ)
{
	int i = 0;
	int j;

	for (j = 0; j < szX; j++)
	{
		if (stX[j] == '\0')
			break;
		buf[i++] = stX[j];
	}

	buf[i++] = ',';
	buf[i++] = ' ';

	for (j = 0; j < szY; j++)
	{
		if (stY[j] == '\0')
			break;
		buf[i++] = stY[j];
	}

	buf[i++] = ',';
	buf[i++] = ' ';

	for (j = 0; j < szZ; j++)
	{
		if (stZ[j] == '\0')
			break;
		buf[i++] = stZ[j];
	}

	buf[i++] = '\r';
	buf[i++] = '\n';

	return i;
}

//--- X_to_str:  получаем строку {X, cNT\r\n} 
int clMath::X_to_str(char buf[], char stX[], char stCNT[], int szX, int szCNT)
{
	int i = 0;
	int j;

	for (j = 0; j < szX; j++)
	{
		if (stX[j] == '\0')
			break;
		buf[i++] = stX[j];
	}

	buf[i++] = ',';
	buf[i++] = ' ';


	for (j = 0; j < szCNT; j++)
	{
		if (stCNT[j] == '\0')
			break;
		buf[i++] = stCNT[j];
	}

	buf[i++] = '\r';
	buf[i++] = '\n';

	return i;
}

void clMath::Waite(uint16_t cntdelay)
{
	volatile uint8_t ttt = 0;
	volatile uint16_t i = 0;
	for (i = 0; i < cntdelay; i++)
		ttt += 1;
}
