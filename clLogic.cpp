#include "clLogic.h"
#include "clService.h"

void clLogic::Out_TmName(eTim_t tim)
{
	if (tim > eTmTimer)
	{
		clService::MessOut(mERR, '\n');
	}
	else
	{
		clService::MessOut(mTmName[tim], '\t');
	}
}

void clLogic::LTimAllInit(int32_t n_sec)
{
	LTim[eTmCommon].Load(MULT_DELTA * n_sec);	
	LTim[eTm1].Load(MULT_DELTA * n_sec);
	LTim[eTm2].Load(MULT_DELTA * n_sec);
	LTim[eTmTimer].Load(MULT_DELTA);			

	LTim[eTmCommon].Start();
	LTim[eTm1].Start();
	LTim[eTm2].Start();
	LTim[eTmTimer].Start();
}

void clLogic::LTimAllWork(void)
{
	LTim[eTmCommon].Work(mIsTick);
	LTim[eTm1].Work(mIsTick);
	LTim[eTm2].Work(mIsTick);
	LTim[eTmTimer].Work(mIsTick);
}

void clLogic::DateTimeWorker(stDateTime_t* dttm, eTimetype_t TimeType, char endch, bool displayON)
{
	if (LTim[eTmTimer].isFlag())
	{
		if (displayON)
		{
			Out_TmName(eTmTimer);
			timer.TimerOut(dttm, TimeType, endch);			
		}

		LTim[eTmTimer].Restart();
	}
}
