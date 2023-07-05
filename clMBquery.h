#pragma once
#include "Header.h"
#include "clCRC16.h"

class clMBquery
{

public:

//----------------------------------------------------------------------------
//--- Формирование запроса функций {3,4,6,16} Возвр. длину сообщения в байтах
//--- Для функций 3,4: uint16_t pay - количество запрашиваемых слов
//--- Для функции 6:   uint16_t pay - значение слова для отправки
//--- Для функции 16:  uint16_t pay - количество отправляемых слов
//----------------------------------------------------------------------------

	uint8_t Mess346(uint8_t address, uint8_t fn, uint16_t start, uint16_t pay, uint8_t* message);
	uint8_t Mess16(uint8_t address, uint8_t fn, uint16_t start, uint16_t pay, uint16_t* data, uint8_t* message);
	bool CheckResponse(uint8_t* response, int16_t size);

	clCRC16 mCrc16query;

protected:


private:

};

