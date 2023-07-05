#include "clMBS.h"
#include "clCRC16.h"

clCRC16 mCrc16;

//--- Инициализация структуры MB
void clMBS::Init(MB_t* mb, uint8_t id, uint8_t* ms, uint8_t* erms)
{
	mb->id = id;
	mb->fn = 3;
	mb->nbt = 0;
	mb->addr = 0;
	mb->quant = 0;

	mb->crc = 0x0000;
	mb->err = 0;		// start with err = 0

	mb->len = 0;		// рабочая переменная - счетчик
	mb->mess = ms;		// ссылка на буфер ответа
	mb->errmess = erms;	// ссылка на буфер сообщения об ошибке
}

bool clMBS::ReInit(MB_t* mb, uint8_t newID)
{
	if ((newID > MINID) && (newID < MAXID))
	{
		mb->id = newID;
		return true;
	}
	else
	{
		return false;
	}
}

void clMBS::InitBufansver(uint8_t* message, uint16_t n)
{
	for (uint16_t i = 0; i < n; i++)
	{
		message[i] = 0x00;
	}
}

//-----------------------------------------------------------------

bool clMBS::isOurFunc(uint8_t fn)
{
	//--- Поддерживаемые функции Modbus данным контроллером
	static const uint8_t FnMB[MBMAXFUNC] = { 3, 4, 6, 16, 65 };

	bool res = false;

	for (int8_t i = 0; i < MBMAXFUNC; i++)
	{
		if (fn == FnMB[i])
		{
			res = true;
			break;
		}
	}

	return res;
}

uint16_t clMBS::Func3(MB_t* mb, uint8_t* Buf, uint16_t* hldregs, uint8_t nMB)
{
	uint16_t res = 0;
	uint16_t t_crc1 = 0x0000;

	uint16_t addr = ((uint16_t)Buf[2]) << 8;
	addr |= (uint16_t)Buf[3];

	uint16_t quant = ((uint16_t)Buf[4]) << 8;
	quant |= (uint16_t)Buf[5];

	mb->nbt = (uint8_t)(quant * 2);

	if ((addr > MAXMBSHOLDINGREGISTERS - 1) || ((addr + quant) > MAXMBSHOLDINGREGISTERS))
	{
		return PrepareErrMessage(mb, eAd);
	}
	else {
		mb->mess[0] = mb->id;
		mb->mess[1] = mb->fn;
		mb->mess[2] = mb->nbt;

		for (uint16_t i = 0; i < quant; i++)
		{ //--- holding registers slave -----------------------------
			mb->mess[3 + i * 2] = (uint8_t)(hldregs[addr + i] >> 8);
			mb->mess[3 + i * 2 + 1] = (uint8_t)(hldregs[addr + i] & 0x00FF);
		}

		uint16_t n = mb->nbt + 3;

		t_crc1 = mCrc16.Calc(mb->mess, n);

		mb->mess[n] = (uint8_t)(t_crc1 >> 8);
		mb->mess[n + 1] = (uint8_t)(t_crc1 & 0x00FF);
		mb->len = n + 2;								// длина буфера посылки mb->len
	}

	return res;
}

uint16_t clMBS::Func4(MB_t* mb, uint8_t* Buf, uint16_t* inpregs, uint8_t nMB)
{
	uint16_t res = 0;
	uint16_t t_crc1 = 0x0000;

	uint16_t addr = ((uint16_t)Buf[2]) << 8;
	addr |= (uint16_t)Buf[3];

	uint16_t quant = ((uint16_t)Buf[4]) << 8;
	quant |= (uint16_t)Buf[5];

	mb->nbt = (uint8_t)(quant * 2);

	if ((addr > MAXMBSINPUTREGISTERS - 1) || ((addr + quant) > MAXMBSINPUTREGISTERS))
	{
		return PrepareErrMessage(mb, eAd);

	}
	else {

		mb->mess[0] = mb->id;
		mb->mess[1] = mb->fn;
		mb->mess[2] = mb->nbt;

		for (uint16_t i = 0; i < quant; i++)
		{ //--- holding registers slave -----------------------------
			mb->mess[3 + i * 2] = (uint8_t)(inpregs[addr + i] >> 8);
			mb->mess[3 + i * 2 + 1] = (uint8_t)(inpregs[addr + i] & 0x00FF);
		}

		uint16_t n = mb->nbt + 3;

		t_crc1 = mCrc16.Calc(mb->mess, n);

		mb->mess[n] = (uint8_t)(t_crc1 >> 8);
		mb->mess[n + 1] = (uint8_t)(t_crc1 & 0x00FF);
		mb->len = n + 2;								// длина буфера посылки mb->len
	}

	return res;
}

uint16_t clMBS::Func6(MB_t* mb, uint8_t* Buf, uint16_t* hldregs, uint8_t nMB)
{
	uint16_t res = 0;
	uint16_t t_crc1 = 0x0000;

	uint16_t addr = ((uint16_t)Buf[2]) << 8;
	addr |= (uint16_t)Buf[3];

	uint16_t data = ((uint16_t)Buf[4]) << 8;
	data |= (uint16_t)Buf[5];

	// тут не проверяется входное значение на допустимость
	// по очевидной причине - транспортный протокол
	// не может знать о допустимости передаваемых данных
	// На это выделен код ошибки = 4, но будет игнорироваться

	if ((addr > MAXMBSHOLDINGREGISTERS - 1))
	{
		return PrepareErrMessage(mb, eAd);

	}
	else {

		hldregs[addr] = data;

		mb->mess[0] = mb->id;
		mb->mess[1] = mb->fn;
		mb->mess[2] = (uint8_t)(addr >> 8);
		mb->mess[3] = (uint8_t)(addr & 0x00FF);
		mb->mess[4] = (uint8_t)(data >> 8);
		mb->mess[5] = (uint8_t)(data & 0x00FF);

		t_crc1 = mCrc16.Calc(mb->mess, 6);

		mb->mess[6] = (uint8_t)(t_crc1 >> 8);
		mb->mess[7] = (uint8_t)(t_crc1 & 0x00FF);

		mb->len = 8;								// длина буфера посылки mb->len
	}

	return res;
}

uint16_t clMBS::Func16(MB_t* mb, uint8_t* Buf, uint16_t* hldregs, uint8_t nMB)
{
	uint16_t res = 0;
	uint16_t t_crc1 = 0x0000;

	uint16_t addr = ((uint16_t)Buf[2]) << 8;
	addr |= (uint16_t)Buf[3];

	uint16_t quant = ((uint16_t)Buf[4]) << 8;
	quant |= (uint16_t)Buf[5];

	// количество байт в цепочке регистров
	// uint8_t cntbt = Buf[6];

	// тут не проверяется входное значение на допустимость
	// по очевидной причине - транспортный протокол
	// не может знать о допустимости передаваемых данных
	// На это выделен код ошибки = 4, но будет игнорироваться

	if ((addr > MAXMBSHOLDINGREGISTERS - 1) || ((addr + quant) > MAXMBSHOLDINGREGISTERS))
	{
		return PrepareErrMessage(mb, eAd);

	}
	else {

		for (uint16_t i = 0; i < quant; i++)
		{
			uint16_t dt = ((uint16_t)Buf[7 + i * 2]) << 8;
			dt |= (uint16_t)Buf[7 + i * 2 + 1];
			hldregs[addr + i] = dt;
		}

		mb->mess[0] = mb->id;
		mb->mess[1] = mb->fn;
		mb->mess[2] = (uint8_t)(addr >> 8);
		mb->mess[3] = (uint8_t)(addr & 0x00FF);
		mb->mess[4] = (uint8_t)(quant >> 8);
		mb->mess[5] = (uint8_t)(quant & 0x00FF);

		t_crc1 = mCrc16.Calc(mb->mess, 6);

		mb->mess[6] = (uint8_t)(t_crc1 >> 8);
		mb->mess[7] = (uint8_t)(t_crc1 & 0x00FF);

		// не забудем длину буфера посылки mb->len ???
		mb->len = 8;
	}

	return res;
}

uint16_t clMBS::Func65(MB_t* mb, uint8_t* Buf, uint16_t* inpregs, uint16_t* hldregs, uint8_t nMB)
{
	uint16_t res = 0;

	// код действия для функции 65
	uint16_t workcode = ((uint16_t)Buf[2]) << 8;
	workcode |= (uint16_t)Buf[3];

	// пароль для действия
	uint16_t pwd = ((uint16_t)Buf[4]) << 8;
	pwd |= (uint16_t)Buf[5];

	// младшее 32 разрядное слово серийного номера
	// старшее 16 разрядное слово
	uint16_t serial_hi = ((uint16_t)Buf[6]) << 8;
	serial_hi |= (uint16_t)Buf[7];

	// младшее 16 разрядное слово
	uint16_t serial_lo = ((uint16_t)Buf[8]) << 8;
	serial_lo |= (uint16_t)Buf[9];

	// новый ID устройства для работы в сети modbus
	// подается в старшем байте слова (младший - 0x00)
	uint16_t new_ID = ((uint16_t)Buf[10]) << 8;
	new_ID |= (uint16_t)Buf[11];

	if ((workcode == WORKCODE65) && (pwd == PASSWORD) && (serial_hi == inpregs[6]) && (serial_lo == inpregs[5]))
	{
		uint8_t id = (uint8_t)(new_ID >> 8);
		if ((id > 0) && (id < MAXID))
		{
			hldregs[0] = (hldregs[0] & 0x00FF) | (new_ID & 0xFF00);
			inpregs[0] = hldregs[0];

			ReInit(mb, id);
			res = 0x0010; 	// команда на перезапись флеш
		}
	}

	return res;
}


uint8_t clMBS::PrepareErrMessage(MB_t* mb, eErrMB_t errcode)
{
	uint16_t crc = 0x0000;

	mb->errmess[0] = mb->id;
	mb->errmess[1] = (mb->fn) | 0x80;
	mb->errmess[2] = (uint8_t)errcode;

	crc = mCrc16.Calc(mb->errmess, 3);

	mb->errmess[3] = crc >> 8;
	mb->errmess[4] = crc & 0x00FF;

	return (uint8_t)errcode;
}
