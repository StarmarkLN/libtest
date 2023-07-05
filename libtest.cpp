/****************************************************************************
*
*
* libtest.cpp : Starmark collection any common modules
*
*
*
****************************************************************************/

#include "Header.h"
#include "clService.h"
#include "clGeneratorXYZ.h"
#include "clCRC16.h"
#include "ImplAver.h"
#include "ImplFifo.h"
#include "ImplStack.h"
#include "clFltr.h"
#include "clFFT.h"
#include "clMBquery.h"
#include "clwrite_read.h"
#include "clPtrFunc.h"
#include "clArrString.h"
#include "clLT.h"
#include "clTimer.h"
#include "clLogic.h"
#include "clBuffer.h"

//#include "clMath.h"

#define MAX_gXYZ	16

const float arr_db[16] = {
    2.1, 2.27, 2.22, 2.38, 
    2.44, 2.39, 2.48, 2.53, 
    2.60, 2.55, 2.47, 2.40,
    2.23, 2.35, 2.19, 2.15};

const float arr[16] = {
    2.1, 2.27, 2.22, 2.38, 
    2.44, 2.39, 2.48, 2.53, 
    2.60, 2.55, 2.47, 2.40,
    2.23, 2.35, 2.19, 2.15};

const int16_t arr_i16[16] = { 
    2, 3, 4, 5,
    6, 7, 8, 9,
    1, 2, 3, 4,
    5, 6, 7, 8 };

const int8_t arr_i8[16] = { 
    1, 2, 3, 4, 
    5, 6,  7,  8, 
    9, 10, 11, 12, 
    13,14, 15, 16 };

float arr_fft[16] = { 
    2.18, 2.27, 2.23, 2.28,
    2.30, 2.16, 8.48, 8.53,
    8.60, 8.55, 8.47, 8.40,
    8.23, 17.35, 17.29, 17.35 };


int32_t buf_i32[16] = { 0, };
double buf_double[16] = { 0.0, };

uint8_t bf8[32] = {0};  

//-------------------------------------
//--- Variables with clBuffer
//-------------------------------------
clBuffer *buff = new clBuffer(bf8, 32);

//-------------------------------------
//--- Variables with Generator
//-------------------------------------
clGeneratorXYZ gXYZ;

//-------------------------------------
//--- Variables with aver
//-------------------------------------
clAver<int16_t> Aver_int16;
clAver<int32_t> Aver_int32;
clAver<float> Aver_float;
clAver<double> Aver_double;

//-------------------------------------
//--- Variables with CRC16
//-------------------------------------
clCRC16 crc16;

//-------------------------------------
//--- Variables with fifo
//-------------------------------------
clFifo<int32_t> fifo_int32;
clFifo<double> fifo_double;

//-------------------------------------
//--- Variables with stack
//-------------------------------------
const string txt[9] = { "Hello","-","Dolly",",","Hi","!",",","Leon","Starmark" };
clStack<int>    intStack;         // stack of ints 
clStack<double> doubleStack;      // stack of doubles
clStack<string> stringStack;      // stack of strings 

//-------------------------------------
//--- Variables with filters
//-------------------------------------
clFltrLPF fltrLPF;
clFltrHPF fltrHPF;

//-------------------------------------
//--- Variables with FFT
//-------------------------------------
clFFT fft;
float res_fft[16] = { 0, };

//-------------------------------------
//--- Variables with clMBquery
//-------------------------------------
clWrite_Read wr_rd;

//-------------------------------------
//--- Variables with clPtrFunc
//-------------------------------------
clPtrFunc ptrFn;

//-------------------------------------
//--- Variables with clArrString
//-------------------------------------
clArrString arrstr;

//-------------------------------------
//--- Variables with Logic
//-------------------------------------
clLogic logic;
stDateTime_t datetime = { 21, 9, 1, 2, 10, 0, 0 };

//-------------------------------------
//--- Variables with clMBquery
//-------------------------------------
clMBquery mbquery;
uint8_t mess[32] = {0,};

//-------------------------------------
//--- Variables with clMBquery
//-------------------------------------
clMBquery mbQuery;

//-------------------------------------
//--- Variables with clMath
//-------------------------------------
//clMath mat;

//===========================================================================

int main()
{
	int testcnt = 0;

	//--------------------------------
    clService::TitleOut("<<< Program: Collection tests any class >>>", '\0');
    //--------------------------------   


    //--------------------------------
    clService::TitleOut("Hello clMBquery!" , '\0');
    //--------------------------------  
    cout << "\nПроверка правильности формирования запроса для функции 3" << endl;
	uint8_t rs = mbquery.Mess346(2, 3, 0, 4, mess);
	cout << int(rs) << endl;
    if(rs == 8){
		for(int i = 0; i < rs; i++){
			cout << int(mess[i]) << "  ";
		}
		cout << endl;
    }
    cout << endl;
    cout << "\nПроверка правильности формирования запроса для функции 4" << endl;
    rs = mbquery.Mess346(3, 4, 2, 6, mess);
	cout << int(rs) << endl;
    if(rs == 8){
		for(int i = 0; i < rs; i++){
			cout << int(mess[i]) << "  ";
		}
		cout << endl;
    }
    cout << endl;
    cout << "\nПроверка правильности формирования запроса для функции 6" << endl;
    rs = mbquery.Mess346(3, 6, 0x0008, 1024, mess);
	cout << int(rs) << endl;
    if(rs == 8){
		for(int i = 0; i < rs; i++){
			cout << int(mess[i]) << "  ";
		}
		cout << endl;
    }
    cout << endl;
    cout << "\nПроверка правильности формирования запроса для функции 16" << endl;
    uint16_t dt[4] = {1234, 2345, 3456, 4567}; 
    rs = mbquery.Mess16(3, 16, 0x0, 0x4, dt, mess);
    cout << int(rs) << endl;
    if(rs == 17){
		for(int i = 0; i < rs; i++){
			cout << int(mess[i]) << "  ";
		}
		cout << endl;
		if (mbQuery.CheckResponse(mess, 17))
    	{
        	cout << "mbQuery.CheckResponse(mess, 17) == true" << endl;
    	}
    	else
    	{
        	cout << "mbQuery.CheckResponse(mess, 17) == false" << endl;
    	}
    }
    cout << endl;

    //--------------------------------
    clService::TitleOut("Hello clBuffer! (problem)" , '\0');
    //--------------------------------  
    buff->reset();
	buff->push((uint8_t)77);
	buff->push((uint8_t)65);
	buff->push((uint8_t)66);
	buff->push((uint8_t)67);
	buff->push((uint8_t)88);

    uint8_t *dat = buff->getData();  
	uint32_t len = buff->getLength();    
    cout << "len: " << len << endl; 
	for(int i=0; i < len; i++){
		cout << "dat[" << i << "]: " << to_string(dat[i]) << endl;
    }
	cout << endl;
    len = buff->getLength();
	cout << "len: " << len << endl;   
 
	buff->push((uint32_t)0x27182818);
	buff->push((uint8_t)75);
	buff->push((uint8_t)76);
	buff->push((uint8_t)77);
	buff->push((uint8_t)78);

    len = buff->getLength();
	cout << "len: " << len << endl;
    for(int i=0; i < len; i++){
		cout << "dt[" << i << "]: " << to_string(buff->popAt(i+5)) << endl;
    }
	len = buff->getLength();
	cout << "len: " << len << endl;  
	cout << "getSize: " << buff->getSize() << endl;

    //--------------------------------
    clService::TitleOut("Hello clGeneratorXYZ!" , '\0');
    //--------------------------------    
    for(int i = 0; i < MAX_gXYZ; i++){
		gXYZ.gen(i);
		gXYZ.out();

		/* or:
        std::cout << "XYZ[" 
				  << i 
				  << "] = " 
				  << gXYZ.get().x 
				  << std::endl;
		*/
	}

    //--------------------------------
    clService::TitleOut("Hello Aver!", '\0');
    //--------------------------------
    clAver<int16_t> Aver_int16;
    //clAver<int32_t> Aver_int32;
    clAver<float> Aver_float;
    clAver<double> Aver_double;

    Aver_int16.InitAver(arr_i16[0], 4);
    for (int i = 0; i < 16; i++)
    {
        int16_t res = Aver_int16.execute(arr_i16[i]);
        cout << "arr[" << i << "] = " << arr_i16[i] << "\tAver_int16 = " << res << endl;
    }

    cout << "\n\n";

    Aver_float.InitAver(arr[0], 8);
    for (int i = 0; i < 16; i++)
    {
        float res = Aver_float.execute(arr[i]);
        cout << "arr[" << i << "] = " << arr[i] << "\tAver_float = " << res << endl;
    }


    cout << "\n\n";

    Aver_double.InitAver(arr_db[0], 8);
    for (int i = 0; i < 16; i++)
    {
        float res = Aver_double.execute(arr_db[i]);
        cout << "arr[" << i << "] = " << arr_db[i] << "\tAver_double = " << res << endl;
    }


    //-------------------------------
    clService::TitleOut("Hello CRC16!", '\0');
    //-------------------------------
    uint16_t crc = crc16.Tabl((unsigned char*)arr_i8,16);
    uint16_t calcrc = crc16.Calc((unsigned char*)arr_i8, 16);

    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    cout << "crc = 0x" << crc << endl;

    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    cout << "calcrc = 0x" << calcrc << endl;


    //-------------------------------
    clService::TitleOut("Hello fifo int32_t", '\0');
    //-------------------------------
    int32_t res = 0;
    fifo_int32.init(buf_i32, 16);

    for (int i = 0; i < 16; i++)
    {
        fifo_int32.put(i*i);
        cout << "count = " << to_string(fifo_int32.count()) << endl;
    }

    cout << endl;

    for (int i = 0; i < 16; i++)
    {        
        fifo_int32.get(&res);
        cout << "[ " << i << "] -> " << res << "\tcount = " << to_string(fifo_int32.count()) << endl;
    }

    //-------------------------------
    clService::TitleOut("Hello fifo double", '\0');
    //-------------------------------
    double dres = 0;
    fifo_double.init(buf_double, 16);

    for (int i = 0; i < 16; i++)
    {
        fifo_double.put((double)i * (double)i * (double)i);
        cout << "count = " << to_string(fifo_double.count()) << endl;
    }

    cout << endl;

    for (int i = 0; i < 16; i++)
    {
        fifo_double.get(&dres);
        cout << "[ " << i << "] -> " << dres << "\tcount = " << to_string(fifo_double.count()) << endl;
    }


    //-------------------------------
    clService::TitleOut("Hello Stack!", '\0');
    //-------------------------------
    try {
        int cnt = 0;

        for (int i = 0; i < 100; i++)
        {
            intStack.push(i);
        }

        cnt = 0;
        while (intStack.empty() == 0)
        {
            int d = intStack.top();
            cout << d << '\t';
            cnt++;
            if (cnt == 10)
            {
                cnt = 0;
                cout << endl;
            }
            intStack.pop();
        }

        cout << endl;

        double k = 0.0;
        for (int i = 0; i < 100; i++)
        {
            doubleStack.push(k);
            k += 0.01;
        }

        cnt = 0;
        while (doubleStack.empty() == 0)
        {
            double d = doubleStack.top();
            cout << d << '\t';
            cnt++;
            if (cnt == 10)
            {
                cnt = 0;
                cout << endl;
            }
            doubleStack.pop();
        }

        cout << endl;

        for (int i = 0; i < 9; i++)
        {
            stringStack.push(txt[i]);
        }

        while (stringStack.empty() == 0)
        {
            string s = stringStack.top();
            cout << s << ' ';
            stringStack.pop();
        }
    }
    catch (exception const& ex) {
        cerr << "Exception: " << ex.what() << endl;
        return -1;
    }


    //-------------------------------
    clService::TitleOut("Hello Filter LPF!", '\0');
    //-------------------------------
    fltrLPF.setAlpha(0.5);

    for (int i = 0; i < 16; i++)
    {
        float res = fltrLPF.execute(arr[i]);
        cout << "arr[" << i << "] = " << arr[i] << "\tfltrLPF = " << res << endl;
    }

    //--------------------------------
    clService::TitleOut("Hello filter HPF!",'\0');
    //--------------------------------
    fltrHPF.setAlpha(0.5);

    for (int i = 0; i < 16; i++)
    {
        float res = fltrHPF.execute(arr[i]);
        cout << "arr[" << i << "] = " << arr[i] << "\tfltrHPF = " << res << endl;
    }


    //-------------------------------
    clService::TitleOut("Hello FFT!", '\0');
    //-------------------------------
    for (int i = 0; i < 16; i++)
    {
        cout << "arr[ " << i << "] = " << arr_fft[i] << endl;
    }

    cout << endl << endl;

    fft.FFT(arr_fft, res_fft, 16, 4, FT_DIRECT);

    for (int i = 0; i < 16/2; i++)
    {
        cout << "fft[ " << i << "] = " << res_fft[i] << endl;
    }

    //-------------------------------------
    clService::TitleOut("Hello clWrite_Read", '\0');
    //-------------------------------------
	wr_rd.Test();


	//-------------------------------------
    clService::TitleOut("Hello clPtrFunc", '\0');
    //-------------------------------------
	ptrFn.Test();


	//-------------------------------------
	clService::TitleOut("Hello clArrString", '\0');
	//-------------------------------------
	arrstr.Test();


    //-------------------------------------
    clService::TitleOut("clLogic: Демо службы времени и работы лог.таймеров", '\0');
    //-------------------------------------
    //--- Запустим 4 таймера
    logic.LTimAllInit(4);    

    //--- Для демонстрации ограничим 5 секундами
    int limit_test_LT = 5* MULT_DELTA;

    //--- Демонстрация службы времени и работы лог. таймеров
    cout.unsetf(ios::dec);
    cout.setf(ios::dec);

    while (limit_test_LT-- >= 0)
    {
        logic.timer.Timer(&logic.mDttm, logic.mIsTick); //--- Служба времени (DateTime)
        
		
        if (logic.mIsTick == 0)					//--- Работают все функции по своим LT
        {
            logic.DateTimeWorker(&logic.mDttm, eDateTime, '\n', true);
            //--- or --- logic.DateTimeWorker(&logic.mDttm, eTime, '\n', true);
            //--- or --- logic.DateTimeWorker(&logic.mDttm, eSeconds, '\n', true);

            //--- Работает генератор XYZ в целых числах 
			//--- (Закомментировать после испытания)
			gXYZ.gen(limit_test_LT);
			//gXYZ.out();

            //---
            //--- и еще какие-то таймеры тут работают
            //---
        }

        logic.LTimAllWork();                	//--- Ход всех запущенных LT таймеров

        logic.timer.Tick_Reset(logic.mIsTick);	//--- Сброс тика сис. таймера
    }


    /*
    //-------------------------------------
    clService::TitleOut("Hello clMath", '\0');
    //-------------------------------------
    //---
    float val = -123.1754;
    clMath::displayFloatToInt_s out_dfti;
    clMath::floatToInt(val, (clMath::displayFloatToInt_s*)&out_dfti, 3);
    cout << "n Float = " << to_string(val) 
         << "\tsign = " << to_string(out_dfti.sign) 
         << " int = " << to_string(out_dfti.out_int)
         << " dec = " << to_string(out_dfti.out_dec) << "\n";
    cout << endl;

    //---
    int ival = 1828;
    char s[10] = {'\n'};
    clMath::intToStr(s, ival, '\n');
    cout << "ival = " << to_string(ival) << "\tstring = " << s;
    cout << endl;

    //--- https://gregstoll.com/~gregstoll/floattohex/
    float fval = 1000.0f;
    uint16_t h = clMath::GetFloatHi(fval, LITENDIAN);
    uint16_t l = clMath::GetFloatLo(fval, LITENDIAN);
    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    cout << "fval = " << to_string(fval) << "\tHI = 0x" << h << " LO = 0x" << l << endl;
    cout << endl;

    //---
    float finp = 1828.256700f;
    float fround = clMath::round(finp, 2);
    cout << "fround = " << to_string(finp) << "\tfround = " << to_string(fround) << endl;
    cout << endl;

    //---
    uint32_t val32 = 12345678;
    uint8_t arrVal32[8] = {0,};
    clMath::Val32ToARRdigit(val32, arrVal32);
    cout << "val32 = " << to_string(val32) << "\tarrVal32[] = ";
    for (int i = 0; i < 8; i++)
    {
        cout.unsetf(ios::dec);
        cout.setf(ios::hex);
        cout << to_string(arrVal32[i]) << " ";
    }
    cout << "\n" << endl;

    //--- 
    uint32_t hexval = 0x13579ABCD;
    uint8_t arrHex32[8] = { 0, };
    clMath::HEX32ToARRdigit(hexval, arrHex32);
    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    cout << "hexval = 0x" << hexval << "\tarrHex32[] = ";
    for (int i = 0; i < 8; i++)
    {
        cout << (uint32_t)arrHex32[i] << " ";
    }

    cout << endl;

    cout.unsetf(ios::hex);
    cout.setf(ios::dec);
    cout << "hexval = " << hexval << "\tarrHex32[] = ";
    for (int i = 0; i < 8; i++)
    {
        cout << (uint32_t)arrHex32[i] << " ";
    }

    cout << "\n" << endl;

    //---
    uint64_t ui64 = 0x300000000000000c;
    uint64_t res64 = clMath::Uint64Revers(ui64);
    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    cout << "ui64 = " << ui64 << "\tres64 = " << res64 << endl;

    cout << endl;

    //---
    ui64 = 0x1122334455667788;
    res64 = clMath::Uint64ReversByBytes(ui64);
    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    cout << "ui64 = " << ui64 << "\tres64 = " << res64 << endl;

    cout << endl;
    
    //---
    string str = "abcdefgh12345678iklmnop";
    cout << "str = " << str << "\n";
    str = clMath::reverstring(str);
    cout << "str = ";
    cout.unsetf(ios::dec);
    cout.setf(ios::hex);
    for (int i = 0; i < str.length() ; i++)
    {
        cout << str[i];
    }
    cout << endl;
    
    cout << endl;
    */

    //====================================
    clService::TitleOut("Конец тестов!", '\0');
    //====================================

    return 0;
}

//=============================================================================================================


