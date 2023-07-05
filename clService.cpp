#include "clService.h"

void clService::ClearScreen(void)
{
	system("clear"); // or "cls" for windows
	setlocale(LC_ALL, "Rus");
}

void clService::MessOut(const char* text, char endch)
{
	std::cout << text << endch;
}

void clService::TitleOut(const char* text, char endch)
{
	std::cout << endl;
	std::cout << "//-------------------------------------------------------" << endl;
	std::cout << "\t" << text << endl;
	std::cout << "//-------------------------------------------------------" << endl;
	std::cout << endl;
}

void clService::NameProgramOut(void)
{
	MessOut("==================================================================", '\n');
	MessOut(" Path to program:", '\t');
	MessOut(__FILE__, '\n');
	MessOut("==================================================================", '\n');
	MessOut("", '\n');
}

void clService::NameStageOut(const char* text)
{
	MessOut("-------------------------------------------------------", '\n');
	MessOut(text, '\n');
	MessOut("-------------------------------------------------------", '\n');
	MessOut("", '\n');
}
