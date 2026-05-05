#include <iostream>
#include "customErrorClass.h"

using namespace std;

MyException::MyException(void){
    this->errString = "Error: Something went wrong.";
}

MyException::MyException(const string &err){
    this->errString = err;
}

MyException::MyException(const char *err){
    this->errString = err;
}

string MyException::retrieveError(void){
    this->errString = "\033[1;31m" + this->errString + "\033[0m";

    return this->errString;
}