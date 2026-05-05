// reading and writing with structs
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


struct data 
{
    int num1;
    int num2;
    char x[12];
};

int main()
{

    fstream fbin;
    struct data d;

    fbin.open("binary.dat", ios::binary | ios::out);
    if(fbin)
    {
        d.num1 = 1;
        d.num2 = 2;
        strncpy(d.x, "Hello World", 12);

        fbin.write(reinterpret_cast<char*>(&d), sizeof(d)); 

        d.num1 = 11;
        d.num2 = 12;
        strncpy(d.x, "Hello Binary", 12);

        fbin.write(reinterpret_cast<char*>(&d), sizeof(d)); 

        fbin.close();
    } else {
        cout <<"Error opening file" << endl;
    }

    return 0;
}