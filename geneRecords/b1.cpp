// Reading and Writing with binary files
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    fstream ftxt, fbin; //ofstream will not work - text file
    //string num = "CSC310";
    unsigned short num = 31000; // size of 2 bytes

    fbin.open("binary.dat", ios::out | ios::binary); // use flags to make it binary
    ftxt.open("file.dat", ios::out); // text file
    
    // ------------------- Writing to a file
    if(ftxt)
    {
        ftxt << num;
        ftxt.close();
    } else {
        cout << "Error opening file" << endl;
    }
    if(fbin)
    {
        fbin.write(reinterpret_cast<char*>(&num), sizeof(num));
        // fbin.write(reinterpret_cast<char*>(&name), name.size()); // for string
        fbin.close();
    } else {
        cout << "Error opening file" << endl;
    }

    // // -------------------- Reading from a file
    fbin.open("binary.dat", ios::in | ios::binary);

    if(fbin)
    {
        unsigned short value;
        fbin.read(reinterpret_cast<char*>(&value), sizeof(unsigned short));
        fbin.close();
        cout << value << endl;
    } else {
        cout << "Error opening file" << endl;
    }
    
    return 0;
}