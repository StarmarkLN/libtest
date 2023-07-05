#include <iostream>
#include <vector>
#include <string>

#include "clArrString.h"

using namespace std;
 
void clArrString::Test(void)
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    string s = "Простая строка";

    cout << "Как распечатать" << endl;
    cout << "vector<string>  msg {'Hello', 'C++', 'World', 'from', 'VS Code', 'and the C++ extension!'};" << endl;

	cout << endl << "Вот так:" << endl;

    cout << "for (const string& elem : msg)\n{\n\t\"cout << elem << \" \";\n}";								
    cout << endl;
	cout << endl;

    for (const string& elem : msg)
    {
        cout << elem << " ";        
    }
    cout << endl;

    cout << s << endl;
}
