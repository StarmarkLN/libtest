#pragma once
#include "Porting.h"

#define MBMAXFUNC	5
#define MINID		0
#define MAXID		32

#define MAXMBSHOLDINGREGISTERS	32
#define MAXMBSINPUTREGISTERS	32

#define PASSWORD	0xAAAA
#define WORKCODE65	0x1828

class clMBS
{
public:
	typedef struct
	{
		uint8_t 	id;		// ID device
		uint8_t 	fn;		// Fn = {3,4,6,16,65}
		uint8_t 	nbt;    // quantity bytes data = quantity_regs * 2
		uint16_t 	addr;   // Begin addr registers block
		uint16_t 	quant;  // quantity registers query

		uint16_t 	crc;	// CRC - RTU
		uint8_t	    err;	// start with err = 0

		uint16_t  len;		// Lenght message
		uint8_t* mess;		// message array
		uint8_t* errmess;	// error message array
	}MB_t;

	void Init(MB_t* mb, uint8_t id, uint8_t* ms, uint8_t* erms);
	
	void InitBufansver(uint8_t* message, uint16_t n);

protected:

private:
	//--- Перечисления для контроллера типов ошибок и номеров функций ---------------------
	typedef enum { eE0 = 0, eFn = 1, eAd = 2, eQt = 3, eWt = 4, eCrash = 5 } eErrMB_t;

	static bool ReInit(MB_t* mb, uint8_t newID);

	//--- Реализованы эти функции ---------------------------------------------------------
	static uint16_t Func3(MB_t* mb, uint8_t* Buf, uint16_t* hldregs, uint8_t nMB);
	static uint16_t Func4(MB_t* mb, uint8_t* Buf, uint16_t* inpregs, uint8_t nMB);
	static uint16_t Func6(MB_t* mb, uint8_t* Buf, uint16_t* hldregs, uint8_t nMB);
	static uint16_t Func16(MB_t* mb, uint8_t* Buf, uint16_t* hldregs, uint8_t nMB);
	static uint16_t Func65(MB_t* mb, uint8_t* Buf, uint16_t* inpregs, uint16_t* hldregs, uint8_t nMB);

	//--- Проверка - правильная функция запрошена или нет ---------------------------------
	static bool isOurFunc(uint8_t fn);

	//--- Подготовка ответа при ошибке ----------------------------------------------------
	static uint8_t PrepareErrMessage(MB_t* mb, eErrMB_t errcode);

	
};

