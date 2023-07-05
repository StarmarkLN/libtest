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
	stDateTime_t mDttm;              //--- ��� ������ � ����� � ��������
	eTimetype_t mTimeType = eTime;   //--- ���������� ������ ������ �������
	eTim_t mTim_N;                   //--- ����� ����������� �������
	int8_t mIsTick = -1;             //--- ��� ������������ ���-������� (100 ����� � �������)

	//--- Variables and other structures --------------------------------------------------
	clTimer timer;                   //--- ������ �������� ����������� �������
	clLT LTim[MAX_LT];               //--- ���������� ������������ �������

	void Out_TmName(eTim_t tim);	 //--- ����� ����� �������	
	void LTimAllInit(int32_t n_sec); //--- ����. � ����� ���� �������. ���������� ��������
	void LTimAllWork(void);			 //--- ��������� LT � ������ �� tick-s ����������� �������

	//--- ������� ������ �������� ������� � ���������� � 1 ������� (��� �������)
	void DateTimeWorker(stDateTime_t* dttm, eTimetype_t TimeType, char endch, bool displayON);

private:
	const char* mERR = "Err:clLogic:";
	const char* mTmName[MAX_LT] = {"TmCommon","Tm1","Tm2","Tm3","Tm4","Tm5","Tm6","eTmTimer"};

protected:

};

