#include "clMBquery.h"

#ifdef clMBquery_EN

//----------------------------------------------------------------------------
//--- Формирование запроса функций {3,4,6,16} Возвр. длину сообщения в байтах
//--- Для функций 3,4: uint16_t pay - количество запрашиваемых слов
//--- Для функции 6:   uint16_t pay - значение слова для отправки
//--- Для функции 16:  uint16_t pay - количество отправляемых слов
//--- Все запросы возвращают длину сообщения в байтах
//----------------------------------------------------------------------------

uint8_t clMBquery::Mess346(uint8_t address, uint8_t fn,
                           uint16_t start, uint16_t pay,
                           uint8_t* message)
{
    message[0] = address;
    message[1] = fn;

    message[2] = (uint8_t)(start >> 8);
    message[3] = (uint8_t)start;
    message[4] = (uint8_t)(pay >> 8);
    message[5] = (uint8_t)pay;

    //unsigned short Tabl(unsigned char* pcBlock, unsigned short len);
    //OR
    //unsigned short Calc(unsigned char* buff, unsigned short number_byte);
    uint16_t crc = mCrc16query.Calc((unsigned char*)message, 6);

    message[6] = (uint8_t)(crc >> 8);
    message[7] = (uint8_t)crc;

    return 8;
}

uint8_t clMBquery::Mess16(uint8_t address, uint8_t fn,
                          uint16_t start, uint16_t pay,
                          uint16_t* data, uint8_t* message)
{
    message[0] = address;
    message[1] = fn;

    message[2] = (uint8_t)(start >> 8);
    message[3] = (uint8_t)start;
    message[4] = (uint8_t)(pay >> 8);
    message[5] = (uint8_t)pay;

    message[6] = (uint8_t)(pay * 2);
    uint8_t cnt = 7;

    for (uint16_t j = 0; j < pay; j++)
    {
        message[cnt++] = (uint8_t)(data[j] >> 8);
        message[cnt++] = (uint8_t)data[j];
    }

    //unsigned short Tabl(unsigned char* pcBlock, unsigned short len);
    //OR
    //unsigned short Calc(unsigned char* buff, unsigned short number_byte);
    uint16_t crc = mCrc16query.Calc((unsigned char*)message, cnt);

    message[cnt++] = (uint8_t)(crc >> 8);
    message[cnt++] = (uint8_t)crc;

    return cnt;
}

//--- Проверка прихода на целостность данных ---------------------------------
bool clMBquery::CheckResponse(uint8_t* response, int16_t size)
{
    uint16_t Crc_mess = ((uint16_t)response[size - 2]) << 8;
    Crc_mess |= (uint16_t)response[size - 1];

    return (mCrc16query.Calc((unsigned char*)response, size - 2) == Crc_mess);
}

#endif






