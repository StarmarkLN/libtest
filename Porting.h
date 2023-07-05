#pragma once
#ifndef __Porting_h__
#define __Porting_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define _WIN32

#define DISABLE_INTERRUPT() __disable_irq()
#define ENABLE_INTERRUPT()  __enable_irq()   

#define WAIT(ms)            HAL_Delay(ms)
#define TICKS()             HAL_GetTick()

bool kbhit(void);

    typedef struct {//--- ƒn работы генератора цепочки чисел
        int16_t x;	//--- значение по X
        int16_t y;	//--- значение по Y
        int16_t z;	//--- значение по Z
        uint8_t n;  //--- потоковый номер
    }stXYZ_t;

    typedef union
    {
        char     c[4];
        uint8_t  b[4];
        int16_t  i[2];
        uint16_t ui[2];
        uint32_t ul;
        int32_t  l;
        float    f;
    } union32_t;

    typedef union
    {
        char     c[2];
        uint8_t  b[2];
        int16_t  i;
        uint16_t ui;
    } union16_t;

    typedef union
    {
        char     c[8];
        uint8_t  b[8];
        uint16_t i[4];
        uint16_t ui[4];
        int32_t  l[2];
        uint32_t ul[2];
        int64_t  i64;
        uint64_t ui64;
        double   d;
    } union64_t;

    typedef void (*notify_cb_t)(void);
    typedef void (*notify_arg_cb_t)(void* arg);

#define ARRAY_SIZE(A)   (sizeof(A) / sizeof(A[0]))

#define SATURATION(N, L, H) (((N)<(L))?(L):(((N)>(H))?(H):(N)))

#define DESTROY(obj)    do { if ((obj) != nullptr) {   \
                                delete obj;            \
                                obj = nullptr;         \
                            }                          \
                        } while (0)                    \


    uint32_t getHeapSize(void);

////////////////////////////////////////////////////////////////////////////////
// Debugging config
////////////////////////////////////////////////////////////////////////////////

    void __assert_trap(const char* f, int line);

#ifdef DEBUG
#define ASSERT(cond)    do { if ((cond) == false) {                     \
                                __assert_trap(__FILENAME__, __LINE__);  \
                             }                                          \
                        } while (0)                                     \

#else
#define ASSERT(cond)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __Porting_h__ */

