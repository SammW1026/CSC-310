// reading and writing arrays
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream ftxt, fbin;

    ftxt.open("file.dat");
    if(ftxt)
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // this is 36 bytes ((9*4 for each int))
        for(auto c : arr)
            ftxt << c;
        ftxt.close();
    } else {
        cout <<"Error opening file" << endl;
    }

    fbin.open("binary.dat", ios::binary | ios::out);
    if(fbin)
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        fbin.write(reinterpret_cast<char*>(arr), sizeof(arr)); // no & since a is a pointer
        fbin.close();
    } else {
        cout <<"Error opening file" << endl;
    }

    // ------------ read it back in
    int b[9];
    fbin.open("binary.dat", ios::in | ios::binary);
    if(fbin)
    {
        fbin.read(reinterpret_cast<char*>(b), sizeof(b));
        fbin.close();
        for(int i : b)
            cout << i << " ";
        cout << endl;
    } else {
        cout << "Error opening file" << endl;
    }

    return 0;
}