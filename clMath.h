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

	//--- Преобразование float в int ------------------------
	static void floatToInt(float in, displayFloatToInt_t* out_value, int32_t dec_prec);

	//--- Преобразование целого в строку --------------------
	static uint8_t intToStr(char* str, int16_t value, char endLine);

	//--- Взять старший и младший байт представления float -- 
	static uint16_t GetFloatHi(float value, uint8_t dir);
	static uint16_t GetFloatLo(float value, uint8_t dir);

	//--- Округление до определеннго знака после , ----------
	static float round(float val, int digit = 0);

	//--- Преобразовать число в стрковое представление ------
	static void Val32ToARRdigit(uint32_t val, uint8_t* arr);
	static void HEX32ToARRdigit(uint32_t val, uint8_t* arr);

	//--- Реверс битов в 64-х битном числе ------------------
	static uint64_t Uint64Revers(uint64_t val);
	//--- Реверс байтов в 8-ми байтном числе ----------------
	static uint64_t Uint64ReversByBytes(uint64_t val);

	//--- reverstring переворачиваем строку s на месте ------ 
	static string reverstring(string s);

	//--- простой заменитель snprintf() ---------------------
	//--- reverse:  переворачиваем строку s на месте 
	static void reverse(char s[]);	//--- ???
	//--- itoa:  конвертируем n в символы в s
	static int _itoa(int n, char s[]);
	//--- XYZ_to_str:  получаем общую строку {X, Y, Z\r\n} 
	static int XYZ_to_str(char buf[], char stX[], char stY[], char stZ[], char stCNT[], int szX, int szY, int szZ, int szCNT);
	//--- XYZ_to_str:  получаем общую строку {X, Y, Z\r\n} 
	static int XYZ_to_str_NoCNT(char buf[], char stX[], char stY[], char stZ[], int szX, int szY, int szZ);
	//--- X_to_str:  получаем строку {X, cNT\r\n} 
	static int X_to_str(char buf[], char stX[], char stCNT[], int szX, int szCNT);

	//--- Простая пауза -------------------------------------
	static void Waite(uint16_t cntdelay);

private:

};

//--- Defines ------------------------------------------------------






void Waite(uint16_t cntdelay);

uint64_t Uint64Revers(uint64_t val);
uint64_t Uint64ReversByBytes(uint64_t val);





