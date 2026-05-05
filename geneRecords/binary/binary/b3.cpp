// reading and writing arrays using functions
#include <iostream>
#include <fstream>

using namespace std;

void writeFunc(int* arr, int size)
{
    fstream fbin("binary.dat", ios::out | ios::binary);
    if(fbin)
    {
        fbin.write(reinterpret_cast<char*>(arr), size*sizeof(int));
        fbin.close();
    } else {
        cout << "Error Opening File" << endl;
    }
}

void readFunc(int* arr, int size)
{
    fstream fbin("binary.dat", ios::in | ios::binary);
    if(fbin)
    {
        fbin.read(reinterpret_cast<char*>(arr), size*sizeof(int));
        fbin.close();
    } else {
        cout << "Error Opening File" << endl;
    }
}


int main()
{
    const int SIZE = 9;
    int array[SIZE] = { 11, 22, 33, 44, 55, 66, 77, 88, 99};
    writeFunc(array, SIZE);

    int values[SIZE];
    readFunc(values, SIZE);

    for(auto i : values)
        cout << i << " "; // print in hex with hex >>

    cout << endl;

    return 0;
}