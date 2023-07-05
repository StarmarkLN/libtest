#include <iostream>
#include <vector>
#include <string>

using namespace std;
 
int main()
{
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    string s = "Простая строка";
    for (const string& elem : msg)
    {
        cout << elem << " ";        
    }
    cout << endl;

    cout << s << endl;
}