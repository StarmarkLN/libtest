#pragma once
#include "Header.h"

#define MAX_LT	8

#include "clTimer.h"
#include "clLT.h"

class clLogic
{
public:
	typedef enum { eTmCommon = 0, eTm1, eTm2, eTm3, eTm4, eTm5, eTm6, eTmTimer } eTim_t;

	//--- Variables and other structures --------------------------------------------------
	stDateTime_t mDttm;              //--- Для работы с датой и временем
	eTimetype_t mTimeType = eTime;   //--- Определяет формат вывода времени
	eTim_t mTim_N;                   //--- Номер логического таймера
	int8_t mIsTick = -1;             //--- Тик срабатывания физ-таймера (100 тиков в секунду)

	//--- Variables and other structures --------------------------------------------------
	clTimer timer;                   //--- Объект эмулятор физического таймера
	clLT LTim[MAX_LT];               //--- Логические интервальные таймеры

	void Out_TmName(eTim_t tim);	 //--- Вывод имени таймера	
	void LTimAllInit(int32_t n_sec); //--- Иниц. и старт всех задейст. логических таймеров
	void LTimAllWork(void);			 //--- Отработка LT с опорой на tick-s физического таймера

	//--- Функция показа текущего времени с интервалом в 1 секунду (для отладки)
	void DateTimeWorker(stDateTime_t* dttm, eTimetype_t TimeType, char endch, bool displayON);

private:
	const char* mERR = "Err:clLogic:";
	const char* mTmName[MAX_LT] = {"TmCommon","Tm1","Tm2","Tm3","Tm4","Tm5","Tm6","eTmTimer"};

protected:

};

