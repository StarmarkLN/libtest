#pragma once
#include "Header.h"

using namespace std::chrono;

typedef enum { eDateTime, eTime, eSeconds } eTimetype_t;

typedef struct DATETIME {
    int years;
    int months;
    int days;
    int hours;
    int minutes;
    int seconds;
    int32_t allsec;
} stDateTime_t;

#define TIM_DELTA   0.00999s
#define MULT_DELTA  100

class clTimer
{
public:
    void Tick(stDateTime_t* dttm);

    void Timer(stDateTime_t* dttm, int8_t& evTick);

    void DateTimeOut(stDateTime_t* dttm, char endch);

    void TimeOut(stDateTime_t* dttm, char endch);

    //void AllSecondsOut(stDateTime_t* dttm, char endch);

    void AllSecOut(stDateTime_t* dttm, char endch);

    void TimerOut(stDateTime_t* dttm, eTimetype_t eTimeType, char endch);

    void Tick_Reset(int8_t& evTick);

    int32_t GetTimeInSeconds(stDateTime_t* dttm);

    int32_t GetAllSeconds(stDateTime_t* dttm);

    void SetAllSeconds(stDateTime_t* dttm, int32_t sec);

private:
    int16_t ticks = 0;

protected:
};

