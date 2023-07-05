#pragma once
#include "Header.h"

#ifdef clBUFFER_EN

class clBuffer {
    public:
        clBuffer();
        clBuffer(uint8_t* buf, uint32_t size);
        clBuffer(uint32_t size);

        ~clBuffer();

        void      init(uint8_t* buf, uint32_t size);
        void      reset();
        bool      push(char value);
        bool      push(uint8_t value);
        bool      push(uint16_t value);
        bool      push(uint32_t value);
        bool      push(uint64_t value);
        bool      push(float value);
        bool      pushData(const uint8_t* dptr, uint32_t len);
        bool      pushStr(const char* str);
        bool      pushStrNull(const char* str);

        bool      pushAt(uint32_t offset, uint16_t value);
        bool      pushAt(uint32_t offset, uint32_t value);
        bool      pushAt(uint32_t offset, uint64_t value);

        uint8_t   pop();
        uint16_t  pop16();
        uint32_t  pop32();
        float     popFloat();
        bool      popStr(char* dst, uint32_t maxLen);
        bool      popEx(uint8_t* buf, uint32_t len);

        uint8_t   popAt(uint32_t offset);
        uint16_t  pop16At(uint32_t offset);

        bool      skipReading(uint32_t len);
        uint8_t*  getData();
        uint8_t*  getCurrData();
        uint32_t  getLength();
        uint32_t  getFreeSpace();
        uint32_t  getSize();

        void shiftLeft(uint32_t positions);

    private:
        uint8_t* mBuffer;
        bool     mBufferIsAutoCreated;
        uint32_t mOffset;
        uint32_t mSize;
};

#endif


