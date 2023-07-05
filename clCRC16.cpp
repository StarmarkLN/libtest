#include "clCRC16.h"

unsigned short clCRC16::Tabl(unsigned char* pcBlock, unsigned short len)
{
    unsigned short crc = 0xFFFF;

    while (len--)
        crc = (crc >> 8) ^ mCrc16Table[(crc & 0xFF) ^ *pcBlock++];

    return (crc >> 8) | (crc << 8);
}

unsigned short clCRC16::Calc(unsigned char* buff, unsigned short number_byte)
{
    unsigned short crc = 0xFFFF;
    unsigned char bit_counter;

    while (number_byte > 0)
    {
        crc ^= *buff;
        buff++;
        bit_counter = 0;

        while (bit_counter < 8)
        {
            if (crc & 0x0001)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }

            bit_counter++;
        }
        number_byte--;
    }
    return (crc >> 8) | (crc << 8);
}
