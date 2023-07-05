#include "clTimer.h"
#include "clService.h"

void clTimer::Tick(stDateTime_t* dttm)
{
    ticks++;
    if (ticks == MULT_DELTA - 1)
    {
        dttm->seconds++;
        if (dttm->seconds == 60) {
            dttm->seconds = 0;
            dttm->minutes++;
        }
        if (dttm->minutes == 60) {
            dttm->minutes = 0;
            dttm->hours++;
        }
        if (dttm->hours == 24) {
            dttm->hours = 0;
            dttm->days++;
        }
        if (dttm->days == 31) {
            dttm->days = 0;
            dttm->months++;
        }
        if (dttm->months == 12) {
            dttm->months = 0;
            dttm->years++;
        }

        dttm->allsec++;

        ticks = 0;
    }
}

void clTimer::Timer(stDateTime_t* dttm, int8_t& evTick)
{
    evTick = 0;
    Tick(dttm);

    this_thread::sleep_for(TIM_DELTA);
}

void clTimer::DateTimeOut(stDateTime_t* dttm, char endch)
{
    char str[20];
    //sprintf_s(str, "%d/%d/%d %d:%d:%d", dttm->years, dttm->months, dttm->days, dttm->hours, dttm->minutes, dttm->seconds);
	sprintf(str, "%d/%d/%d %d:%d:%d", dttm->years, dttm->months, dttm->days, dttm->hours, dttm->minutes, dttm->seconds);
    clService::MessOut(str, '\n');
}

void clTimer::TimeOut(stDateTime_t* dttm, char endch)
{
    char str[10];
    //sprintf_s(str, "%d:%d:%d", dttm->hours, dttm->minutes, dttm->seconds);
	sprintf(str, "%d:%d:%d", dttm->hours, dttm->minutes, dttm->seconds);
    clService::MessOut(str, '\n');
}

void clTimer::AllSecOut(stDateTime_t* dttm, char endch)
{
    char str[10];
    //sprintf_s(str, "%d", dttm->allsec);
	sprintf(str, "%d", dttm->allsec);
    clService::MessOut(str, '\n');
}

void clTimer::TimerOut(stDateTime_t* dttm, eTimetype_t eTimeType, char endch)
{
    switch (eTimeType)
    {
    case eDateTime: DateTimeOut(dttm, endch);
        break;
    case eTime:     TimeOut(dttm, endch);
        break;
    case eSeconds:  AllSecOut(dttm, endch);
        break;
    }
}

void clTimer::Tick_Reset(int8_t& evTick)
{
    if (evTick == 0)
    {
        evTick = -1;
    }
}

int32_t clTimer::GetTimeInSeconds(stDateTime_t* dttm)
{
    return (dttm->seconds + dttm->minutes * 60 + dttm->hours * 3600 + dttm->days * 24 * 3600 + dttm->months * 24 * 30 * 3600 + dttm->years * 24 * 30 * 12 * 3600);
}

int32_t clTimer::GetAllSeconds(stDateTime_t* dttm)
{
    return dttm->allsec;
}

void clTimer::SetAllSeconds(stDateTime_t* dttm, int32_t sec)
{
    dttm->allsec = sec;
}
