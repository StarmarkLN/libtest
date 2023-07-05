#include "clBuffer.h"

#ifdef clBUFFER_EN

clBuffer::clBuffer()
{
    mBuffer = nullptr;
    mSize = 0;
    mOffset = 0;

    mBufferIsAutoCreated = false;
}

clBuffer::~clBuffer()
{
    if (mBufferIsAutoCreated == true) {
        delete[] mBuffer;
    }
}

clBuffer::clBuffer(uint8_t* buf, uint32_t size)
{
    mBuffer = buf;
    ASSERT(mBuffer != nullptr);

    mSize = size;
    mOffset = 0;

    mBufferIsAutoCreated = false;
}

clBuffer::clBuffer(uint32_t size)
{
    mBuffer = new uint8_t[size];
    ASSERT(mBuffer != nullptr);

    mSize = size;
    mOffset = 0;

    mBufferIsAutoCreated = true;
}

/**
 * @brief Initializes buffer object
 *
 * @param[in] b    Pointer to buffer object
 * @param[in] buf  Pointer to memory
 * @param[in] size Size of memory
 */
void clBuffer::init(uint8_t* buf, uint32_t size)
{
    if (mBufferIsAutoCreated == true) {
        mBufferIsAutoCreated = false;
        delete[] mBuffer;
    }

    mBuffer = buf;
    mSize = size;
    mOffset = 0;
}

/**
 * @brief Reset all data
 * @details Memory does not released
 *
 * @param[in] b Pointer to buffer object
 */
void clBuffer::reset()
{
    mOffset = 0;
}

/**
 * @brief Pushes a byte into the buffer
 *
 * @param[in] b     Pointer to buffer object
 * @param[in] value Value
 * @return True if value was added, otherwise false.
 */
bool clBuffer::push(uint8_t value)
{
    if (mOffset >= mSize) {
        return false;
    }

    mBuffer[mOffset] = value;
    mOffset++;

    return true;
}

/**
 * @brief Pushes a char into the buffer
 *
 * @param[in] b     Pointer to buffer object
 * @param[in] value Value
 * @return True if value was added, otherwise false.
 */
bool clBuffer::push(char value)
{
    return push((uint8_t)value);
}

bool clBuffer::pushAt(uint32_t offset, uint16_t value)
{
    uint32_t oldOffset = mOffset;

    mOffset = offset;

    bool status = push(value);

    mOffset = oldOffset;

    return status;
}

bool clBuffer::pushAt(uint32_t offset, uint32_t value)
{
    uint32_t oldOffset = mOffset;

    mOffset = offset;

    bool status = push(value);

    mOffset = oldOffset;

    return status;
}

bool clBuffer::pushAt(uint32_t offset, uint64_t value)
{
    uint32_t oldOffset = mOffset;

    mOffset = offset;

    bool status = push(value);

    mOffset = oldOffset;

    return status;
}

/**
 * @brief Pushes a word into the buffer
 *
 * @param[in] b     Pointer to buffer object
 * @param[in] value Value
 * @return True if value was added, otherwise false.
 */
bool clBuffer::push(uint16_t value)
{
    if (push((uint8_t)((value >> 8) & 0xff)) == false) {
        return false;
    }

    if (push((uint8_t)(value & 0xff)) == false) {
        return false;
    }

    return true;
}

/**
 * @brief Pushes a UI32 into the buffer
 *
 * @param[in] b     Pointer to buffer object
 * @param[in] value Value
 * @return True if value was added, otherwise false.
 */
bool clBuffer::push(uint32_t value)
{
    if (push((uint8_t)((value >> 24) & 0xff)) == false) {
        return false;
    }

    if (push((uint8_t)((value >> 16) & 0xff)) == false) {
        return false;
    }

    if (push((uint8_t)((value >> 8) & 0xff)) == false) {
        return false;
    }

    if (push((uint8_t)(value & 0xff)) == false) {
        return false;
    }

    return true;
}

/**
 * @brief Pushes a UI64 into the buffer
 *
 * @param[in] b     Pointer to buffer object
 * @param[in] value Value
 * @return True if value was added, otherwise false.
 */
bool clBuffer::push(uint64_t value)
{
    if (push((uint32_t)((value >> 32) & 0xffffffff)) == false) {
        return false;
    }

    if (push((uint32_t)(value & 0xffffffff)) == false) {
        return false;
    }

    return true;
}

bool clBuffer::push(float value)
{
    union32_t v;
    v.f = value;

    return push(v.ul);
}

bool clBuffer::pushData(const uint8_t* dptr, uint32_t len)
{
    for (uint32_t index = 0; index < len; index++) {
        if (push(dptr[index]) == false) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Pushes a string into the buffer
 *
 * @param[in] b   Pointer to buffer object
 * @param[in] str pointer to the string
 * @return True if the string was added, otherwise false.
 */
bool clBuffer::pushStr(const char* str)
{
    uint32_t index = 0;

    while (true) {
        if (str[index] == '\0') {
            return true;
        }

        if (push((uint8_t)str[index]) == false) {
            return false;
        }

        index++;
    }
}

bool clBuffer::pushStrNull(const char* str)
{
    if (pushStr(str) == false) {
        return false;
    }

    return push('\0');
}

uint8_t clBuffer::popAt(uint32_t offset)
{
    if (offset >= mSize) {
        return 0;
    }

    return mBuffer[offset];
}

/**
 * @brief Popes a byte from buffer
 *
 * @param[in] b Pointer to buffer object
 * @return uint8_t
 */
uint8_t clBuffer::pop()
{
    if (mOffset >= mSize) {
        return 0;
    }

    uint8_t res = mBuffer[mOffset];
    mOffset++;

    return res;
}

/**
 * @brief Popes a data array from the buffer
 *
 * @param[in]  b   Pointer to buffer object
 * @param[out] buf Pointer to the array where data will be poped
 * @param[in]  len Number bytes which has to place into the array
 * @return True if the operation was success, otherwise false.
 */
bool clBuffer::popEx(uint8_t* buf, uint32_t len)
{
    uint32_t index;

    if ((mOffset + len) > mSize) {
        return false;
    }

    if (buf) {
        for (index = 0; index < len; index++) {
            buf[index] = mBuffer[mOffset];
            mOffset++;
        }
    }
    else {
        mOffset += len;
    }

    return true;
}

bool clBuffer::skipReading(uint32_t len)
{
    if (mOffset + len > mSize) {
        return false;
    }

    mOffset += len;

    return true;
}

/**
 * @brief Popes a word from the buffer
 *
 * @param[in] b Pointer to buffer object
 * @return uint16_t
 */
uint16_t clBuffer::pop16()
{
    uint16_t res;

    res = pop(); res <<= 8;
    res |= pop();

    return res;
}

uint16_t clBuffer::pop16At(uint32_t offset)
{
    uint16_t res;

    res = popAt(offset);     res <<= 8;
    res |= popAt(offset + 1);

    return res;
}

/**
 * @brief Popes a double word from the buffer
 *
 * @param[in] b Pointer to buffer object
 * @return uint16_t
 */
uint32_t clBuffer::pop32()
{
    uint32_t res;

    res = pop(); res <<= 8;
    res |= pop(); res <<= 8;
    res |= pop(); res <<= 8;
    res |= pop();

    return res;
}

float clBuffer::popFloat()
{
    union32_t v;
    v.ul = pop32();

    return v.f;
}

/**
 * @brief Popes a string from the buffer
 *
 * @param[in]  b      Pointer to buffer object
 * @param[out] dst    Pointer to destination memory
 * @param[in]  maxLen Max length of the string
 * @return True if the operation was success, otherwise false.
 * @return false
 */
bool clBuffer::popStr(char* dst, uint32_t maxLen)
{
    uint32_t index = 0;

    while (true) {
        if (mOffset >= mSize) {
            return false;
        }

        if (index >= maxLen) {
            return false;
        }

        if (mBuffer[mOffset] == '\0') {
            mOffset++;
            return true;
        }

        dst[index] = mBuffer[mOffset];

        mOffset++;
        index++;
    }
}

/**
 * @brief Get pointer to the very begin of the buffer
 *
 * @param[in] b    Pointer to buffer object
 * @return uint8_t*
 */
uint8_t* clBuffer::getData()
{
    return mBuffer;
}

/**
 * @brief Get pointer to the current position of the buffer
 *
 * @param[in] b Pointer to buffer object
 * @return uint8_t*
 */
uint8_t* clBuffer::getCurrData()
{
    return &mBuffer[mOffset];
}

/**
 * @brief Get current position
 *
 * @param[in] b Pointer to buffer object
 * @return uint32_t
 */
uint32_t clBuffer::getLength()
{
    return mOffset;
}

uint32_t  clBuffer::getFreeSpace()
{
    return mSize - mOffset;
}

uint32_t clBuffer::getSize()
{
    return mSize;
}

void clBuffer::shiftLeft(uint32_t steps)
{
    if (steps > mOffset) {
        return;
    }

    if (steps == 0) {
        return;
    }

    uint32_t count = (mOffset - steps);
    uint32_t indexFrom = steps;
    for (uint32_t index = 0; index < count; index++, indexFrom++) {
        mBuffer[index] = mBuffer[indexFrom];
    }

    mOffset -= steps;
}

#endif
