#pragma once
#include "Porting.h"

#define HEXFORMAT	1
#define DECFORMAT	0

#define DECODEFORMAT	1
#define NODECODEFORMAT	0

#define FORVARDNULL		1
#define NOFORVARDNULL	0

#define BIGENDIAN	0
#define LITENDIAN	1

class clMath
{
public:
	typedef struct displayFloatToInt_s {
		int8_t sign;
		uint32_t  out_int;
		uint32_t  out_dec;
	} displayFloatToInt_t;

	//--- �������������� float � int ------------------------
	static void floatToInt(float in, displayFloatToInt_t* out_value, int32_t dec_prec);

	//--- �������������� ������ � ������ --------------------
	static uint8_t intToStr(char* str, int16_t value, char endLine);

	//--- ����� ������� � ������� ���� ������������� float -- 
	static uint16_t GetFloatHi(float value, uint8_t dir);
	static uint16_t GetFloatLo(float value, uint8_t dir);

	//--- ���������� �� ������������ ����� ����� , ----------
	static float round(float val, int digit = 0);

	//--- ������������� ����� � �������� ������������� ------
	static void Val32ToARRdigit(uint32_t val, uint8_t* arr);
	static void HEX32ToARRdigit(uint32_t val, uint8_t* arr);

	//--- ������ ����� � 64-� ������ ����� ------------------
	static uint64_t Uint64Revers(uint64_t val);
	//--- ������ ������ � 8-�� ������� ����� ----------------
	static uint64_t Uint64ReversByBytes(uint64_t val);

	//--- reverstring �������������� ������ s �� ����� ------ 
	static string reverstring(string s);

	//--- ������� ���������� snprintf() ---------------------
	//--- reverse:  �������������� ������ s �� ����� 
	static void reverse(char s[]);	//--- ???
	//--- itoa:  ������������ n � ������� � s
	static int _itoa(int n, char s[]);
	//--- XYZ_to_str:  �������� ����� ������ {X, Y, Z\r\n} 
	static int XYZ_to_str(char buf[], char stX[], char stY[], char stZ[], char stCNT[], int szX, int szY, int szZ, int szCNT);
	//--- XYZ_to_str:  �������� ����� ������ {X, Y, Z\r\n} 
	static int XYZ_to_str_NoCNT(char buf[], char stX[], char stY[], char stZ[], int szX, int szY, int szZ);
	//--- X_to_str:  �������� ������ {X, cNT\r\n} 
	static int X_to_str(char buf[], char stX[], char stCNT[], int szX, int szCNT);

	//--- ������� ����� -------------------------------------
	static void Waite(uint16_t cntdelay);

private:

};

//--- Defines ------------------------------------------------------






void Waite(uint16_t cntdelay);

uint64_t Uint64Revers(uint64_t val);
uint64_t Uint64ReversByBytes(uint64_t val);





