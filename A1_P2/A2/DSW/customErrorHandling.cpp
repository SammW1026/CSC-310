#include <iostream>
#include "customErrorClass.h"

using namespace std;

double division(int a, int b){
    if( b == 0 ){
        throw MyException("myerror");
    }
    return a/b;
}

int main(int argc, char* argv[]){
    int x = 50;
    int y = 0;
    double z = 0;
    MyException excp("MyError");


    try{
        z = division(x,y);
        cout<<z<<endl;
    } catch( MyException &e){
        cerr<<e.what()<<endl;
    }


    return 0;
}